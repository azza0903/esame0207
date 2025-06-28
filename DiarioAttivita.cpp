
#include "DiarioAttivita.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>

using namespace std;

Attivita::Attivita(const string& desc, const string& inizio, const string& fine, const string& d)
    : descrizione(desc), ora_inizio(inizio), ora_fine(fine), data(d) {}

DiarioAttivita::DiarioAttivita() {
    nome_file = "attivita.txt";
    caricaDaFile();
}

DiarioAttivita::~DiarioAttivita() {
    salvaSuFile();
}

void DiarioAttivita::pulisciSchermo() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool DiarioAttivita::validaOra(const string& ora) {
    if (ora.length() != 5 || ora[2] != ':') return false;
    try {
        int ore = stoi(ora.substr(0, 2));
        int minuti = stoi(ora.substr(3, 2));
        return (ore >= 0 && ore <= 23 && minuti >= 0 && minuti <= 59);
    } catch (...) {
        return false;
    }
}

bool DiarioAttivita::validaData(const string& data) {
    if (data.length() != 10 || data[4] != '-' || data[7] != '-') return false;
    try {
        int anno = stoi(data.substr(0, 4));
        int mese = stoi(data.substr(5, 2));
        int giorno = stoi(data.substr(8, 2));
        return (anno >= 2020 && anno <= 2030 && mese >= 1 && mese <= 12 && giorno >= 1 && giorno <= 31);
    } catch (...) {
        return false;
    }
}

void DiarioAttivita::aggiungiAttivita() {
    pulisciSchermo();
    Attivita nuova_attivita;

    cout << "\nDescrizione attivita: ";
    cin.ignore();
    getline(cin, nuova_attivita.descrizione);

    if (nuova_attivita.descrizione.empty()) {
        cout << "❌ Errore: La descrizione non puo essere vuota!" << endl;
        cin.get();
        return;
    }

    do {
        cout << "Ora inizio (HH:MM): ";
        getline(cin, nuova_attivita.ora_inizio);
    } while (!validaOra(nuova_attivita.ora_inizio));

    do {
        cout << "Ora fine (HH:MM): ";
        getline(cin, nuova_attivita.ora_fine);
    } while (!validaOra(nuova_attivita.ora_fine));

    do {
        cout << "Data (YYYY-MM-DD): ";
        getline(cin, nuova_attivita.data);
    } while (!validaData(nuova_attivita.data));

    attivita.push_back(nuova_attivita);
    salvaSuFile();

    cout << "\n✅ Attivita salvata con successo!" << endl;
    cin.get();
}

void DiarioAttivita::visualizzaAttivita() {
    pulisciSchermo();
    string data;

    do {
        cout << "\nInserisci la data (YYYY-MM-DD): ";
        cin >> data;
        if (!validaData(data)) {
            cout << "❌ Formato data non valido!" << endl;
        }
    } while (!validaData(data));

    vector<Attivita> attivita_giorno;
    for (const auto& att : attivita) {
        if (att.data == data) {
            attivita_giorno.push_back(att);
        }
    }

    if (attivita_giorno.empty()) {
        cout << "\n📝 Nessuna attivita registrata per questo giorno" << endl;
    } else {
        sort(attivita_giorno.begin(), attivita_giorno.end(),
             [](const Attivita& a, const Attivita& b) {
                 return a.ora_inizio < b.ora_inizio;
             });

        for (const auto& att : attivita_giorno) {
            cout << att.ora_inizio << " - " << att.ora_fine << ": " << att.descrizione << endl;
        }
    }

    cin.ignore();
    cin.get();
}

void DiarioAttivita::visualizzaTutteAttivita() {
    pulisciSchermo();

    if (attivita.empty()) {
        cout << "\n📝 Nessuna attivita registrata" << endl;
    } else {
        map<string, vector<Attivita>> attivita_per_data;
        for (const auto& att : attivita) {
            attivita_per_data[att.data].push_back(att);
        }

        for (auto& [data, lista_att] : attivita_per_data) {
            cout << "\n📅 " << data << ":" << endl;

            sort(lista_att.begin(), lista_att.end(),
                 [](const Attivita& a, const Attivita& b) {
                     return a.ora_inizio < b.ora_inizio;
                 });

            for (const auto& att : lista_att) {
                cout << "  " << att.ora_inizio << " - " << att.ora_fine
                     << ": " << att.descrizione << endl;
            }
        }
    }

    cin.ignore();
    cin.get();
}

void DiarioAttivita::eliminaAttivita() {
    pulisciSchermo();

    if (attivita.empty()) {
        cout << "\n📝 Nessuna attivita da eliminare" << endl;
        cin.ignore();
        cin.get();
        return;
    }

    for (size_t i = 0; i < attivita.size(); ++i) {
        cout << i + 1 << ". " << attivita[i].data << " "
             << attivita[i].ora_inizio << "-" << attivita[i].ora_fine
             << ": " << attivita[i].descrizione << endl;
    }

    cout << "\nInserisci il numero dell'attivita da eliminare (0 per annullare): ";
    int scelta;
    cin >> scelta;

    if (scelta > 0 && scelta <= static_cast<int>(attivita.size())) {
        attivita.erase(attivita.begin() + scelta - 1);
        salvaSuFile();
        cout << "✅ Attivita eliminata con successo!" << endl;
    } else if (scelta != 0) {
        cout << "❌ Numero non valido!" << endl;
    }

    cin.ignore();
    cin.get();
}

void DiarioAttivita::salvaSuFile() {
    ofstream file(nome_file);
    for (const auto& att : attivita) {
        file << att.data << "|" << att.ora_inizio << "|"
             << att.ora_fine << "|" << att.descrizione << endl;
    }
}

void DiarioAttivita::caricaDaFile() {
    ifstream file(nome_file);
    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string data, ora_inizio, ora_fine, descrizione;

        if (getline(ss, data, '|') &&
            getline(ss, ora_inizio, '|') &&
            getline(ss, ora_fine, '|') &&
            getline(ss, descrizione)) {
            attivita.emplace_back(descrizione, ora_inizio, ora_fine, data);
        }
    }
}

void DiarioAttivita::mostraMenu() {
    int scelta;

    do {
        pulisciSchermo();

        cout << "\n📓 Diario delle Attivita\n";
        cout << "1. ➕ Aggiungi nuova attivita\n";
        cout << "2. 👁️  Visualizza attivita di un giorno\n";
        cout << "3. 📋 Visualizza tutte le attivita\n";
        cout << "4. 🗑️  Elimina attivita\n";
        cout << "5. 🚪 Esci\n";
        cout << "\n🎯 Scegli un'opzione (1-5): ";
        cin >> scelta;

        switch (scelta) {
            case 1: aggiungiAttivita(); break;
            case 2: visualizzaAttivita(); break;
            case 3: visualizzaTutteAttivita(); break;
            case 4: eliminaAttivita(); break;
            case 5: cout << "\n👋 Arrivederci!\n"; break;
            default:
                cout << "\n❌ Scelta non valida!\n";
                cin.ignore();
                cin.get();
                break;
        }
    } while (scelta != 5);
}
