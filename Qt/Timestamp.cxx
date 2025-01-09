#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <chrono>
#include <vector>
#include <algorithm>
#include <ctime>

namespace fs = std::filesystem;
namespace chr = std::chrono;

std::time_t fileTimeToTimeT(const fs::file_time_type& fileTime) {
    auto sctp = chr::time_point_cast<chr::system_clock::duration>(
    fileTime - fs::file_time_type::clock::now() + chr::system_clock::now());

    return chr::system_clock::to_time_t(sctp);
}

enum Action {Nothing, Modified, Added, Deleted};

struct PackedFile {
    std::string fileName;
    Action action;
    std::time_t timestamp;

    PackedFile()
    : fileName(""), action(Nothing), timestamp(0)
    {}

    PackedFile(std::string fileName, Action action, std::time_t timestamp)
    : fileName(""), action(Nothing), timestamp(0)
    {
        this->fileName = fileName;
        this->action = action;
        this->timestamp = timestamp;
    }

    ~PackedFile() {}

    void swap(PackedFile& other)
    {
        std::swap(this->fileName, other.fileName);
        std::swap(this->action, other.action);
        std::swap(this->timestamp, other.timestamp);
    }

    PackedFile(const PackedFile& other)
    : fileName(""), action(Nothing), timestamp(0)
    {
        this->fileName = other.fileName;
        this->action = other.action;
        this->timestamp = other.timestamp;
    }

    PackedFile& operator=(const PackedFile& other)
    {
        if (this != &other) {
            PackedFile temp(other);
            this->swap(temp);
        }

        return *this;
    }
};

struct CmpDecreasingFileName {
    bool operator()(PackedFile a, PackedFile b) const {
        return a.fileName <= b.fileName;
    }
};

struct CmpIncreasingFileName {
    bool operator()(PackedFile a, PackedFile b) const {
        return a.fileName > b.fileName;
    }
};

struct CmpDecreasingAction {
    bool operator()(PackedFile a, PackedFile b) const {
        return a.action <= b.action;
    }
};

struct CmpIncreasingAction {
    bool operator()(PackedFile a, PackedFile b) const {
        return a.action > b.action;
    }
};

struct CmpDecreasingTimestamp {
    bool operator()(PackedFile a, PackedFile b) const {
        return a.timestamp <= b.timestamp;
    }
};

struct CmpIncreasingTimestamp {
    bool operator()(PackedFile a, PackedFile b) const {
        return a.timestamp > b.timestamp;
    }
};

std::ostream& operator<<(std::ostream& os, const PackedFile& p) {
    os << p.fileName << "," << p.action << "," << p.timestamp << std::endl;
    return os;
}

// Vettore con le triplette [nome del file, tipo di modifica, timestamp]
static std::vector<PackedFile> Modifications;

// Mappa che ha per chiave il file e per valore il suo timestamp
// Non possono esistere due file con lo stesso nome quindi non é
// un problema
static std::map<std::string, std::time_t> DirectoryStructure;

// File log di output
static const std::string logPath = "/home/shania/Documents/log.csv"; 

void exportLogToFile()
{
    std::ofstream logFile;
    logFile.open(logPath);

    std::vector<PackedFile>::iterator start = Modifications.begin();
    std::vector<PackedFile>::iterator finish = Modifications.end();

    while (start != finish) {
        logFile << *start;
        ++start;
    }

    logFile.close();
}

void loadLogFromFile()
{
    std::fstream logFile;
    logFile.open(logPath);

    std::string thisLine;
    while (std::getline(logFile, thisLine)) {
        std::stringstream ss(thisLine);
        std::string a, b, c;

        std::getline(ss, a, ',');
        std::getline(ss, b, ',');
        std::getline(ss, c, ',');

        Action b_p = Action(std::stoi(b));
        std::time_t c_p = std::time_t(std::stoi(c));
        PackedFile p(a, b_p, c_p);
        Modifications.push_back(p);
    }

    logFile.close();
}

void filesystemInspection()
{
    // Controlla se i file nella directory corrente sono nella mappa oppure no
    fs::directory_iterator it(fs::current_path());
    while (it != fs::directory_iterator()) {
        fs::path thisFile = *it;
        if (DirectoryStructure.count(thisFile) <= 0) {
            std::time_t thisTm = fileTimeToTimeT(fs::last_write_time(thisFile));
            PackedFile p(thisFile, Added, thisTm);
            Modifications.push_back(p);
            DirectoryStructure[thisFile] = thisTm;
            break;
        }
        ++it;
    }

    // Controlla se i file nella mappa sono nella directory corrente oppure no
    std::map<std::string, std::time_t>::iterator start = DirectoryStructure.begin();
    std::map<std::string, std::time_t>::iterator finish = DirectoryStructure.end();

    while (start != finish) {
        fs::path thisFile = start->first;
        if (!fs::exists(thisFile)) {
            std::time_t thisTm = start->second;
            PackedFile p(thisFile, Deleted, thisTm);
            Modifications.push_back(p);
            DirectoryStructure.erase(start);
            break;
        } 
        ++start;
    }

    // Compara i timestamp
    start = DirectoryStructure.begin();

    while (start != finish) {
        fs::path thisFile = start->first;
        if (fs::exists(thisFile)) {
            std::time_t ts_in_the_map = start->second;            
            std::time_t ts_in_the_dir = fileTimeToTimeT(fs::last_write_time(thisFile));

            if (ts_in_the_dir != ts_in_the_map) {
                PackedFile p(thisFile, Modified, ts_in_the_dir);
                Modifications.push_back(p);
                DirectoryStructure[thisFile] = ts_in_the_dir;
                break;
            }
        }
        ++start;
    }
}

int main(int argc, char* argv[])
{
    // Itera lungo la directory e aggiungi ogni file con il suo timestamp
    // alla mappa
    fs::directory_iterator it(fs::current_path());
    while (it != fs::directory_iterator()) {
        fs::path thisFile = *it;
        DirectoryStructure[thisFile] = fileTimeToTimeT(fs::last_write_time(thisFile));
        ++it;
    }

    std::cout << "Loading from " << logPath << std::endl;
    loadLogFromFile();

    // Inizia il loop
    while (true) {
        filesystemInspection();

        std::sort(Modifications.begin(), Modifications.end(), CmpIncreasingTimestamp());

        exportLogToFile();
    }

    return 0;
}
