# Diario delle Attività 

Questo è un progetto C++ per la gestione di un diario di attività giornaliere.

## Funzionalità
- Aggiungi attività con descrizione, orario e data
- Visualizza attività per un giorno specifico
- Visualizza tutte le attività registrate
- Elimina attività
- Salvataggio automatico su file `attivita.txt`

## Compilazione

Assicurati di avere CMake installato. Poi esegui:

```bash
cmake -S . -B build
cmake --build build
./build/DiarioAttivita
```

## Struttura dei File

- `main.cpp`: Funzione principale del programma
- `DiarioAttivita.hpp`: Definizione della classe e struct
- `DiarioAttivita.cpp`: Implementazione completa della logica
- `attivita.txt`: File dati delle attività
- `CMakeLists.txt`: Configurazione del progetto

Creato da Azouza 
