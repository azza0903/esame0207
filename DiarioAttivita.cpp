#include "DiarioAttivita.hpp"
#include <fstream>
#include <sstream>

Attivita::Attivita(const std::string& desc, const std::string& inizio, const std::string& fine, const std::string& d)
    : descrizione(desc), ora_inizio(inizio), ora_fine(fine), data(d) {}

DiarioAttivita::DiarioAttivita() {
    nome_file = "attivita.txt";
    caricaDaFile();
}

DiarioAttivita::~DiarioAttivita() {
    salvaSuFile();
}

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

void DiarioAttivita::aggiungiAttivita() {
   
}

void DiarioAttivita::visualizzaAttivita() const{

}

void DiarioAttivita::visualizzaTutteAttivita() const {
    
}

void DiarioAttivita::eliminaAttivita() {

}

void DiarioAttivita::salvaSuFile() {
    std::ofstream file(nome_file);
    for (const auto& att : attivita) {
        file << att.data << "|" << att.ora_inizio << "|"
             << att.ora_fine << "|" << att.descrizione << std::endl;
    }
}

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
