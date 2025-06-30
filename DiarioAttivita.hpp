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
   
    friend class DiarioAttivitaTest;

public:
    DiarioAttivita();
    ~DiarioAttivita();
    bool validaOra(const std::string& ora);
    bool validaData(const std::string& data);
    void aggiungiAttivita();
    void visualizzaAttivita();
    void visualizzaTutteAttivita();
    void eliminaAttivita();
    void mostraMenu();

    void salvaSuFile();
    void caricaDaFile();

    // Accesso per i test
    const std::vector<Attivita>& getAttivita() const { return attivita; }
    void setAttivita(const std::vector<Attivita>& lista) { attivita = lista; }

};

#endif
