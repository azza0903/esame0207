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
    bool validaOra(const std::string& ora);
    bool validaData(const std::string& data);

public:
    DiarioAttivita();
    ~DiarioAttivita();

    void aggiungiAttivita();
    void visualizzaAttivita();
    void visualizzaTutteAttivita();
    void eliminaAttivita();
    void mostraMenu();

    void salvaSuFile();
    void caricaDaFile();
};

#endif
