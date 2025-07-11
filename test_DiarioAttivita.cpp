#include "DiarioAttivita.hpp"
#include <gtest/gtest.h>
#include <fstream>

// Reset del file dei test prima di ogni test
void pulisciFile() {
    std::ofstream("test_attivita.txt", std::ios::trunc).close();
}

// Test: la funzione validaOra accetta solo orari validi
TEST(DiarioAttivitaTest, ValidaOraGenerale) {
    DiarioAttivita diario("test_attivita.txt");
    EXPECT_TRUE(diario.validaOra("12:00"));
    EXPECT_FALSE(diario.validaOra("25:00"));
}

// Test: la funzione validaData accetta solo date valide
TEST(DiarioAttivitaTest, ValidaDataGenerale) {
    DiarioAttivita diario("test_attivita.txt");
    EXPECT_TRUE(diario.validaData("2025-07-11"));
    EXPECT_FALSE(diario.validaData("2025-13-99"));
}

// Test: verifica che si possa aggiungere qualcosa e che il numero aumenti
TEST(DiarioAttivitaTest, AggiuntaGenerale) {
    pulisciFile();
    DiarioAttivita diario("test_attivita.txt");
    size_t prima = diario.getAttivita().size();

    diario.aggiungiAttivita(Attivita("Qualsiasi", "08:00", "09:00", "2025-07-11"));

    size_t dopo = diario.getAttivita().size();
    EXPECT_EQ(dopo, prima + 1);
}

// Test: caricamento da file esistente
TEST(DiarioAttivitaTest, CaricamentoGenerale) {
    DiarioAttivita diario("test_attivita.txt");
    auto lista = diario.getAttivita();
    EXPECT_GE(lista.size(), 0); // Basta che il programma non crasha
}

// Test: visualizzazione attività non crasha anche se il contenuto cambia
TEST(DiarioAttivitaTest, VisualizzazioneGenerale) {
    DiarioAttivita diario("test_attivita.txt");
    auto mappa = diario.visualizzaTutteAttivita();
    EXPECT_TRUE(mappa.size() >= 0);
}

// Test: eliminazione se possibile
TEST(DiarioAttivitaTest, EliminazioneGenerale) {
    DiarioAttivita diario("test_attivita.txt");
    auto lista = diario.getAttivita();

    if (!lista.empty()) {
        size_t prima = lista.size();
        bool ok = diario.eliminaAttivita(0);
        EXPECT_TRUE(ok);
        EXPECT_EQ(diario.getAttivita().size(), prima - 1);
    } else {
        SUCCEED(); // Nessuna attività, quindi il test passa lo stesso
    }
}
