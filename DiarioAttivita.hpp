#ifndef DIARIO_ATTIVITA_HPP
#define DIARIO_ATTIVITA_HPP

#include <string>
#include <vector>

struct Attivita {
    std::string descrizione;
    std::string ora_inizio;
    std::string ora_fine;
    std::string data;

    Attivita(const std::string& desc = "", const std::string& inizio = "",
             const std::string& fine = "", const std::string& d = "");
};

class DiarioAttivita {
private:
    std::vector<Attivita> attivita;
    std::string nome_file;

    void pulisciSchermo();
   
    friend class DiarioAttivitaTest;// Permette l'accesso ai membri privati per i test

public:
    DiarioAttivita();
    ~DiarioAttivita();// Distruttore per salvare le attività su file
    bool validaOra(const std::string& ora); // Controlla se l'ora è valida nel formato HH:MM
    bool validaData(const std::string& data); // Controlla se la data è valida nel formato YYYY-MM-DD
    void aggiungiAttivita(); // Aggiunge una nuova attività al diario
    void visualizzaAttivita();// Visualizza le attività di un giorno specifico
    void visualizzaTutteAttivita();// Visualizza tutte le attività registrate
    void eliminaAttivita();// Elimina un'attività specifica dal diario
    void mostraMenu();// Mostra il menu principale del diario

    void salvaSuFile();//   Salva le attività su un file
    void caricaDaFile();// Carica le attività da un file

    // Accesso per i test
    const std::vector<Attivita>& getAttivita() const { return attivita; } // Restituisce la lista delle attività
    void setAttivita(const std::vector<Attivita>& lista) { attivita = lista; }// Imposta la lista delle attività

};

#endif
