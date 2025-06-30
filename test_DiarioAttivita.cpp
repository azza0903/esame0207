
#include "DiarioAttivita.hpp"
#include <gtest/gtest.h>

// Test per la funzione validaOra con input corretto
TEST(DiarioAttivitaTest, ValidaOra_Corretta) {
    DiarioAttivita diario;
    EXPECT_TRUE(diario.validaOra("12:30"));
    EXPECT_TRUE(diario.validaOra("00:00"));
    EXPECT_TRUE(diario.validaOra("23:59"));
    EXPECT_FALSE(diario.validaOra("24:00"));
    EXPECT_FALSE(diario.validaOra("aa:bb"));
}

// Test per la funzione validaData con input corretto
TEST(DiarioAttivitaTest, ValidaData_Corretta) {
    DiarioAttivita diario;
    EXPECT_TRUE(diario.validaData("2025-06-29"));
    EXPECT_FALSE(diario.validaData("2025-13-01"));
    EXPECT_FALSE(diario.validaData("abcd-ef-gh"));
}

// Test per salvare e caricare da file
TEST(DiarioAttivitaTest, SalvataggioCaricamentoFile) {
    DiarioAttivita diario;
    std::vector<Attivita> lista = {
        {"Studio", "10:00", "12:00", "2025-06-29"},
        {"Sport", "14:00", "15:00", "2025-06-29"}
    };
    diario.setAttivita(lista);
    diario.salvaSuFile();

    DiarioAttivita diario2;
    const auto& caricate = diario2.getAttivita();
    ASSERT_EQ(caricate.size(), 2);
    EXPECT_EQ(caricate[0].descrizione, "Studio");
    EXPECT_EQ(caricate[1].ora_inizio, "14:00");
}

// Test per eliminare un'attività (solo struttura dimostrativa)
TEST(DiarioAttivitaTest, EliminaAttivita) {
    DiarioAttivita diario;
    std::vector<Attivita> lista = {
        {"Compiti", "08:00", "09:00", "2025-06-29"},
        {"Passeggiata", "18:00", "19:00", "2025-06-29"}
    };
    diario.setAttivita(lista);
    diario.eliminaAttivita(); // Test interattivo simulato: non testabile direttamente
}
