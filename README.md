# Queue Simulation

Design of a M/M/Y/Y queue simulation. The project has been developed using C language. Documentation is at the moment of writing only written in Italian, as well as in code comments, as it was developed during the second year of a Bachelor Degree in Italian.

## SIMULAZIONE DI UN SISTEMA A CODA M/M/Y/Y (IT)

Progetto di un Sistema a Coda M/M/Y/Y per il corso di Reti di Telecomunicazioni tenuto dal professor Andrea Conti, Corso di Laurea Triennale in Informatica, A.A. 2019 - 2020.

Mebri del gruppo: Martina Tenani, Alberto Paparella.


Il progetto e' stato sviluppato in piu' files per migliorarne la leggibilita', sia in fase di lavoro e di debugging che per la lettura di terzi, nonche' per assicurarne un miglior riutilizzo.

### Overview e scelte implementative

E' stato scelto di utilizzare come struttura dati per l'implementazione della coda una Lista Collegata, ottima per la simulazione di una coda virtualmente "infinita" (seppur non necessaria nel sistema in questione, essendo almeno teoricamente sempre vuota, ma con occhio al riutilizzo per la simulazione ad altri sistemi) grazie all'allocazione dinamica della memoria, non necessitando di una dichiarazione a posteriori della capacita'. Le operazioni svolte su di essa sono quelle classiche di enqueue (inserimento in coda) e dequeue (eliminazione in testa). Oltre a queste, in funzione della simulazione e del debugging, vengono aggiungte una funzione per la stampa del numero di elementi presenti nella coda o eventualmente degli id degli stessi pacchetti in coda.
Un miglioramento potrebbe essere tener conto dell'indirizzo dell'ultimo elemento in coda, la cosiddetta "tail" della coda. Viene comunque inserita una funzione per il calcolo di questo indirizzo, seppur non sfruttata nella simulazione.

### Generazione degli arrivi

La generazione dei tempi di interarrivo e di intersevizio (numeri pseudo-casuali) sfrutta la tecnica di trasformazione inversa, ricavando dalla formula di densita' di probabilita' dei processi markoviani 1 - e^(-f(t)) la seguente formula: t = -(1/lambda)*log(1-u) dove per log si intende il logaritmo naturale e per u una variabile aleatoria distribuita uniformemente fra 0 e 1. Ovviamente, per il calcolo dei tempi di interservizio basti invertire lambda con mu. A questo calcolo viene infine sommato 1 per evitare di generare il valore 0 (testato sperimentalmente, il cambiamento che questo comporta e' trascurabile).

### Descrizione dei files

- **pacchetto.h**: viene definita una struttura dati Pacchetto il cui unico campo non e' altro che un intero contenente l'id del pacchetto.

- **servitore.h**: viene definita una struttura dati Servitore di campi pacchetto di tipo post-definito Pacchetto, utile per conoscere l'ID del pacchetto che sta venendo servito, una campo Occupato che funge da valore booleano per conoscere se il servitore sta servendo un pacchetto (1) o meno (0), e un campo tServizio di tipo intero che indica fra quanti cicli il servitore tornera' ad essere libero.

- **coda.h**: viene definita la struttura dati della Coda (sfruttando in realta' le conoscenze sulle Liste Collegate e la loro implementazione in C) puntatore a Nodo, quest'ultimo definito con come campi un pacchetto di tipo definito Pacchetto e un campo next puntatore al nodo successivo (l'indirizzo a cui si trova l'elemento successivo della coda). In pratica, sfruttando l'allocazione dinamica della memoria del C, cosa che torna molto utile nella definizione delle funzioni che operano sulla coda. Sono inoltre definite le interfaccie per le funzioni che operano sulla coda visibili al cliente, in particolare:
  - **nuovaCoda(Coda\* pc)** prende come argomento un puntatore a coda e serve ad inizializzare la coda
  - **enqueue(Coda*pc, Pacchetto p)** prende come argomenti un puntatore a coda e un pacchetto ed effettua l'inserimento in coda del pacchetto
  - **dequeue(Coda\* pc)** prende come argomento un puntatore a coda ed effettua l'eliminazione del pacchetto in testa alla coda
  - **getHead(Coda c)** prende come argomento una coda e ne stampa il pacchetto in testa
  - **getTail(Coda c)** prende come argomento una coda e ne stampa l'ultimo pacchetto entrato nella coda
  - **getStato(Coda c)** prende come argomento una coda e restituisce il numero di elementi presenti nella coda, di tipo intero
  - **stampaCoda(Coda c)** prende come argomento una coda e stampa gli id dei pacchetti in coda, nell'ordine dal prossimo che verra' servito fino all'ultimo pacchetto entrato in coda (a livello grafico a specchio rispetto ad una rappresentazione canone di coda)

- **coda.c**: contiene l'implementazione delle funzioni che operano sulla coda. Si evidenzia la presenza di due funzioni, insTesta e ricerca, nascoste al cliente in quanto vengono solo sfruttate nell'implementazione di altre funzioni (l'operazione di enqueue). In particolare:
  - **insTesta(Coda\* pc, Pacchetto pacchetto)** che prende come argomenti un puntatore a coda e un pacchetto, ed effettua l'inserimento in testa di un pacchetto nella coda (trattandosi di una lista collegata, l'inserimento in testa al nodo della coda)
  - **ricerca(Coda\* pc, pacchetto p)** che prende come argomenti un puntatore a coda e un pacchetto e scorre gli elementi della coda sino a che non ne trova uno che punti a NULL (l'ultimo elemento, quello attualmente in "coda alla coda").

- **poisgen.h**: contiene semplicemente il prototipo della funzione per la generazione di numeri pseudo-casuali da una legge di distribuzione poissoniana con parameotro x (sia esso lmabda o mu).

- **poisgen.c**: contiene l'implementazione della funzione per la generazione di numeri pseudo-casuali che seguono la legge poissoniana (sfruttati come tempi di interarrivo e interservizio).

- **main.c**: il cliente della simulazione.

### Funzionamento di enqueue

L'operazione di enqueue, o di inserimento in coda, sfrutta la ricerca sulla coda dell'ultimo elemento della coda (quello che nel campo next contiene un puntatore a NULL), crea un nuovo Nodo ausiliario che conterra' il nuovo pacchetto e avra' nel campo next un puntatore a NULL, e l'indirizzo del pacchetto ausiliario verra' sostituito a quello nel campo next dell'ultimo pacchetto della coda, che conteneva un puntatore a NULL.

### Risultati sperimentali

Misurazione del parametro E{k} (stato del sistema) al variare del numero di servitori. Le misurazioni sono state effettuate per valori di λ che variano tra 0.001 e 0.2, con un incremento di
0.001. Il tasso di morte μ è rimasto fisso a 0.01 per tutta la durata dell’esperimento.

![results](https://github.com/alberto-paparella/QueueSimulation/blob/master/images/results.png?raw=true)
