# CPlusPlus-Unimib-Progetto
Progetto per l'esame _Programmazione C++_ dell'anno accademico 2024/25, _Universitá degli Studi di Milano-Bicocca_.

I file presenti nella repo sono i seguenti:

- `Stack.hpp` contiene il codice del progetto vero e proprio;
- `Stack.cxx` contiene il codice per testare il progetto;
- `Report.pdf` é un report che descrive le scelte implementative che sono state fatte nel progetto;
- `Report.typ` é un file scritto nel linguaggio [Typst](https://typst.app), che genera il report in formato PDF;
- `Makefile` contiene la recipe per fare la build del progetto e/o della documentazione;
- `Doxyfile` contiene il template per costruire la documentazione del progetto.

Il report é stato pre-generato, di modo da non dover avere `typst` installato (non é comunque un file che andrebbe modificato, se non dall'autore).

Per generare solo il codice:

```
make
```

Per generare solo il codice e testarlo subito:

```
make run
```

Per generare solo la documentazione:

```
make doc
```

Per generare sia il codice che la documentazione:

```
make all
```
