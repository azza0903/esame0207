#ifndef DIARIOATTIVITA_HPP
#define DIARIOATTIVITA_HPP

#include <string>
#include <vector>
#include <map>

struct Attivita {
    std::string descrizione;
    std::string ora_inizio;
    std::string ora_fine;
    std::string data;

    Attivita(const std::string& desc, const std::string& inizio, const std::string& fine, const std::string& d);
};

class DiarioAttivita {
private:
    std::vector<Attivita> attivita;
    std::string nome_file;

public:
    DiarioAttivita();
    ~DiarioAttivita();

    bool validaOra(const std::string& ora);// Validazione dell'ora nel formato HH:MM
    bool validaData(const std::string& data);// Validazione della data nel formato YYYY-MM-DD
    // Aggiunge un'attività al diario

    void aggiungiAttivita(const Attivita& nuova);// Aggiunge un'attività al diario e la salva su file
    std::vector<Attivita> visualizzaAttivita(const std::string& data) const; // Visualizza le attività di una data specifica, ordinate per ora di inizio
    std::map<std::string, std::vector<Attivita>> visualizzaTutteAttivita() const;// Visualizza tutte le attività, raggruppate per data e ordinate per ora di inizio
    bool eliminaAttivita(size_t indice);// Elimina un'attività specificata dall'indice e salva su file

    void salvaSuFile();// Salva le attività su un file
    void caricaDaFile();//  Carica le attività da un file

    std::vector<Attivita> getAttivita() const { return attivita; }// Restituisce l'elenco delle attività
    void setAttivita(const std::vector<Attivita>& nuove) { attivita = nuove; }// Imposta l'elenco delle attività
};

#endif

