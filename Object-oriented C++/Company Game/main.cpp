#include "gra.hpp"
#include <windows.h> 
#include <locale.h>  

int main() {

    setlocale(LC_ALL, "pl_PL.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Gra gra;

    while (gra.get_stan()) {
        gra.akcja_gracza();
    }

    return 0;
}