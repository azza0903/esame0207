#include "DiarioAttivita.hpp"

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    DiarioAttivita diario;
    diario.mostraMenu();
    return 0;
}
