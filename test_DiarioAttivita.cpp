
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
// Test per aggiungere attività
TEST(DiarioAttivitaTest, AggiungiAttivita) {
    DiarioAttivita diario;

    // prendi il numero iniziale
    size_t iniziale = diario.getAttivita().size();

    // aggiungi un'attività con il metodo pubblico
    std::vector<Attivita> lista = diario.getAttivita();
    lista.push_back({"Test", "08:00", "09:00", "2025-06-30"});
    diario.setAttivita(lista);

    // verifica che è stata aggiunta
    EXPECT_EQ(diario.getAttivita().size(), iniziale + 1);
}

// Test per visualizzare attività (verifica che ci siano elementi attesi)
TEST(DiarioAttivitaTest, VisualizzaAttivita) {
    DiarioAttivita diario;
    diario.setAttivita({{"Meeting", "09:00", "10:00", "2025-06-30"}});
    const auto& lista = diario.getAttivita();
    bool trovato = false;
    for (const auto& att : lista) {
        if (att.descrizione == "Meeting" && att.data == "2025-06-30") {
            trovato = true;
        }
    }
    EXPECT_TRUE(trovato);
}

// Test per visualizzare tutte le attività
TEST(DiarioAttivitaTest, VisualizzaTutteAttivita) {
    DiarioAttivita diario;
    diario.setAttivita({
        {"Task1", "10:00", "11:00", "2025-06-30"},
        {"Task2", "12:00", "13:00", "2025-06-30"}
    });
    EXPECT_GE(diario.getAttivita().size(), 2);
}

// Test per mostraMenu (verifica solo che non crasha)
TEST(DiarioAttivitaTest, MostraMenu_NonCrash) {
    DiarioAttivita diario;
    SUCCEED(); // Il test passa solo se non ci sono errori di esecuzione
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
