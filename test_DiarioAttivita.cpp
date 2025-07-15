
#include "DiarioAttivita.hpp"
#include <gtest/gtest.h>

// Test: carica correttamente le attività da attivita.txt
TEST(DiarioAttivitaTest, CaricamentoAttivitaDaFile) {
    DiarioAttivita diario;
    diario.caricaDaFile();
    auto lista = diario.getAttivita();
    EXPECT_GT(lista.size(), 0);
}

// Test: verifica che tutte le attività caricate abbiano campi non vuoti
TEST(DiarioAttivitaTest, AttivitaCaricateComplete) {
    DiarioAttivita diario;
    diario.caricaDaFile();
    for (const auto& att : diario.getAttivita()) {
        EXPECT_FALSE(att.data.empty());
        EXPECT_FALSE(att.ora_inizio.empty());
        EXPECT_FALSE(att.ora_fine.empty());
        EXPECT_FALSE(att.descrizione.empty());
    }
}

// Test: verifica che la visualizzazione per ogni data esistente non sia vuota
TEST(DiarioAttivitaTest, VisualizzaAttivitaPerDatePresenti) {
    DiarioAttivita diario;
    diario.caricaDaFile();
    auto lista = diario.getAttivita();

    for (const auto& att : lista) {
        auto visualizzate = diario.visualizzaAttivita(att.data);
        EXPECT_FALSE(visualizzate.empty());
    }
}

// Test: verifica che la lista delle attività sia coerente tra più chiamate
TEST(DiarioAttivitaTest, CoerenzaListaAttivita) {
    DiarioAttivita diario;
    diario.caricaDaFile();
    auto lista1 = diario.getAttivita();
    auto lista2 = diario.getAttivita();
    EXPECT_EQ(lista1.size(), lista2.size());
}
