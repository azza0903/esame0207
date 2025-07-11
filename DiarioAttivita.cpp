#include "DiarioAttivita.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

// Costruttore Attivita
Attivita::Attivita(const std::string& desc, const std::string& inizio, const std::string& fine, const std::string& d)
    : descrizione(desc), ora_inizio(inizio), ora_fine(fine), data(d) {}

// Costruttore Diario
DiarioAttivita::DiarioAttivita() {
    nome_file = "attivita.txt";
    caricaDaFile();
}


// Distruttore
DiarioAttivita::~DiarioAttivita() {
    salvaSuFile();
}

// Validazione ora
bool DiarioAttivita::validaOra(const std::string& ora) {
    if (ora.length() != 5 || ora[2] != ':') return false;
    try {
        int ore = std::stoi(ora.substr(0, 2));
        int minuti = std::stoi(ora.substr(3, 2));
        return (ore >= 0 && ore <= 23 && minuti >= 0 && minuti <= 59);
    } catch (...) {
        return false;
    }
}

// Validazione data
bool DiarioAttivita::validaData(const std::string& data) {
    if (data.length() != 10 || data[4] != '-' || data[7] != '-') return false;
    try {
        int anno = std::stoi(data.substr(0, 4));
        int mese = std::stoi(data.substr(5, 2));
        int giorno = std::stoi(data.substr(8, 2));
        return (anno >= 2020 && anno <= 2030 && mese >= 1 && mese <= 12 && giorno >= 1 && giorno <= 31);
    } catch (...) {
        return false;
    }
}

// Aggiungi attività
void DiarioAttivita::aggiungiAttivita(const Attivita& nuova) {
    attivita.push_back(nuova);
    salvaSuFile();
}

// Visualizza attività di una data
std::vector<Attivita> DiarioAttivita::visualizzaAttivita(const std::string& data) const {
    std::vector<Attivita> risultato;
    for (const auto& att : attivita) {
        if (att.data == data) {
            risultato.push_back(att);
        }
    }
    std::sort(risultato.begin(), risultato.end(), [](const Attivita& a, const Attivita& b) {
        return a.ora_inizio < b.ora_inizio;
    });
    return risultato;
}

// Visualizza tutte le attività per data ordinate per ora
std::map<std::string, std::vector<Attivita>> DiarioAttivita::visualizzaTutteAttivita() const {
    std::map<std::string, std::vector<Attivita>> risultato;
    for (const auto& att : attivita) {
        risultato[att.data].push_back(att);
    }
    for (auto& [_, lista] : risultato) {
        std::sort(lista.begin(), lista.end(), [](const Attivita& a, const Attivita& b) {
            return a.ora_inizio < b.ora_inizio;
        });
    }
    return risultato;
}

// Elimina attività tramite indice
bool DiarioAttivita::eliminaAttivita(size_t indice) {
    if (indice >= attivita.size()) return false;
    attivita.erase(attivita.begin() + indice);
    salvaSuFile();
    return true;
}

// Salva su file
void DiarioAttivita::salvaSuFile() {
    std::ofstream file(nome_file);
    for (const auto& att : attivita) {
        file << att.data << "|" << att.ora_inizio << "|"
             << att.ora_fine << "|" << att.descrizione << std::endl;
    }
}

// Carica da file
void DiarioAttivita::caricaDaFile() {
    std::ifstream file(nome_file);
    std::string linea;
    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string data, ora_inizio, ora_fine, descrizione;

        if (std::getline(ss, data, '|') &&
            std::getline(ss, ora_inizio, '|') &&
            std::getline(ss, ora_fine, '|') &&
            std::getline(ss, descrizione)) {
            attivita.emplace_back(descrizione, ora_inizio, ora_fine, data);
        }
    }
}
