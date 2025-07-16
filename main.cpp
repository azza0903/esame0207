#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <map>
#include <algorithm>
#include "DiarioAttivita.hpp"

using namespace std;

void pulisciSchermo() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    DiarioAttivita diario;
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

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            scelta = 0;
        }

        switch (scelta) {
            case 1: {
                pulisciSchermo();
                Attivita nuova;

                cout << "\nDescrizione attivita: ";
                cin.ignore();
                getline(cin, nuova.descrizione);

                if (nuova.descrizione.empty()) {
                    cout << "❌ La descrizione non può essere vuota!" << endl;
                    cin.get();
                    break;
                }

                cout << "Ora inizio (HH:MM): ";
                getline(cin, nuova.ora_inizio);
                if (!diario.validaOra(nuova.ora_inizio)) {
                    cout << "❌ Ora non valida!" << endl;
                    cin.get();
                    break;
                }

                cout << "Ora fine (HH:MM): ";
                getline(cin, nuova.ora_fine);
                if (!diario.validaOra(nuova.ora_fine)) {
                    cout << "❌ Ora non valida!" << endl;
                    cin.get();
                    break;
                }

                cout << "Data (YYYY-MM-DD): ";
                getline(cin, nuova.data);
                if (!diario.validaData(nuova.data)) {
                    cout << "❌ Data non valida!" << endl;
                    cin.get();
                    break;
                }

                diario.aggiungiAttivita(nuova);
                cout << "\n✅ Attivita salvata con successo!" << endl;
                cin.get();
                break;
            }

            case 2: {
                pulisciSchermo();
                string data;
                cout << "\nInserisci la data (YYYY-MM-DD): ";
                cin >> data;

                if (!diario.validaData(data)) {
                    cout << "❌ Formato data non valido!" << endl;
                } else {
                    auto attivita = diario.visualizzaAttivita(data);
                    if (attivita.empty()) {
                        cout << "\n📝 Nessuna attivita registrata per questo giorno" << endl;
                    } else {
                        for (const auto& att : attivita) {
                            cout << att.ora_inizio << " - " << att.ora_fine << ": " << att.descrizione << endl;
                        }
                    }
                }

                cin.ignore();
                cin.get();
                break;
            }

            case 3: {
                pulisciSchermo();
                auto mappa = diario.visualizzaTutteAttivita();

                if (mappa.empty()) {
                    cout << "\n📝 Nessuna attivita registrata" << endl;
                } else {
                    for (const auto& [data, lista] : mappa) {
                        cout << "\n📅 " << data << ":\n";
                        for (const auto& att : lista) {
                            cout << "  " << att.ora_inizio << " - " << att.ora_fine << ": " << att.descrizione << endl;
                        }
                    }
                }

                cin.ignore();
                cin.get();
                break;
            }

            case 4: {
                pulisciSchermo();
                const auto& elenco = diario.getAttivita();

                if (elenco.empty()) {
                    cout << "\n📝 Nessuna attivita da eliminare" << endl;
                    cin.ignore();
                    cin.get();
                    break;
                }

                for (size_t i = 0; i < elenco.size(); ++i) {
                    cout << i + 1 << ". " << elenco[i].data << " "
                         << elenco[i].ora_inizio << "-" << elenco[i].ora_fine
                         << ": " << elenco[i].descrizione << endl;
                }

                cout << "\nInserisci il numero dell'attivita da eliminare (0 per annullare): ";
                int scelta_elimina;
                cin >> scelta_elimina;

                if (scelta_elimina == 0) {
                    cout << "❎ Eliminazione annullata." << endl;
                } else if (scelta_elimina < 0 || !diario.eliminaAttivita(static_cast<size_t>(scelta_elimina - 1))) {
                    cout << "❌ Numero non valido!" << endl;
                } else {
                    cout << "✅ Attivita eliminata con successo!" << endl;
                }

                cin.ignore();
                cin.get();
                break;
            }

            case 5:
                cout << "\n👋 Arrivederci!\n";
                break;

            default:
                cout << "\n❌ Scelta non valida!\n";
                cin.ignore();
                cin.get();
                break;
        }

    } while (scelta != 5);

    return 0;
}
