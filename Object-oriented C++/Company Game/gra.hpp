#ifndef GRA_HPP
#define GRA_HPP

#include <iostream>
#include <memory>
#include <limits>
#include <string>
#include <print>
#include <iomanip>

#include "firma.hpp"
#include "stale.hpp"
#include "RandomNameGenerator.hpp"

class Gra {
private:
    bool stan;
    std::unique_ptr<Firma> firma;
    int miesiac;

public:
    Gra() : stan(true), firma(std::make_unique<Firma>()), miesiac(0) {
        wyswietl_intro();
    }

    bool get_stan() const { return stan; }

    void wyswietl_intro() const {
        std::print("\n");
        std::print("Symulacja firmy \n");
        std::print("Buduj zespół, sprzedawaj, pilnuj przepływów i wyniku.\n");
        std::print("Cel: wartość spółki > {} zł | Przegrana: saldo < 0 zł\n", Stale::CEL_WYGRANEJ);
    }

    void wyswietl_menu() const {
        std::print("\nDostępne akcje:\n");
        std::print(" lp    - pokaż pracowników\n");
        std::print(" zinz  - zatrudnij inżyniera\n");
        std::print(" zmag  - zatrudnij magazyniera\n");
        std::print(" zmkt  - zatrudnij marketera\n");
        std::print(" zrob  - zatrudnij produkcję\n");
        std::print(" kred  - zaciągnij kredyt\n");
        std::print(" kt    - zakończ turę (następny miesiąc)\n");
        std::print(" exit  - wyjdź z gry\n");
    }

    void akcja_gracza() {
        wyswietl_menu();
        firma->wyswietl_stan();

        std::print("\n> Twoja akcja: ");
        std::string komenda;
        if (!(std::cin >> komenda)) {
            std::print("Błąd wejścia. Kończę grę.\n");
            stan = false;
            return;
        }

        if (komenda == "lp") {
            firma->drukuj_pracownikow();
        }
        else if (komenda == "zinz") {
            zatrudnij_inzyniera();
        }
        else if (komenda == "zmag") {
            zatrudnij_magazyniera();
        }
        else if (komenda == "zmkt") {
            zatrudnij_marketera();
        }
        else if (komenda == "zrob") {
            zatrudnij_robotnika();
        }
        else if (komenda == "kred") {
            wez_kredyt_dialog();
        }
        else if (komenda == "kt") {
            tick();
        }
        else if (komenda == "exit") {
            std::print("\nDzięki za grę.\n");
            stan = false;
        }
        else {
            std::print("Nieznana komenda\n");
        }
    }

    void tick() {
        ++miesiac;

        std::print("\nMiesiąc {} - rozliczenie\n", miesiac);

        firma->zaplac_wynagrodzenie();
        firma->otrzymaj_przychod();
        firma->splac_raty();

        // sprawdzenie warunków końca
        if (firma->wartosc_firmy() >= Stale::CEL_WYGRANEJ) {
            std::print("\nKoniec gry - cel osiągnięty\n");
            std::print("Wartość spółki: {:.2f} zł\n", firma->wartosc_firmy());
            std::print("Liczba miesięcy: {}\n", miesiac);
            stan = false;
            return;
        }

        if (firma->get_stan_konta() < 0) {
            std::print("\nKoniec gry - bankructwo\n");
            std::print("Saldo: {:.2f} zł\n", firma->get_stan_konta());
            std::print("Liczba miesięcy: {}\n", miesiac);
            stan = false;
            return;
        }

        std::print("\nZamknięto miesiąc {}. Gramy dalej.\n", miesiac);
    }

private:
    void zatrudnij_inzyniera() {
        std::string imie = getRandomName();

        std::print("Wydział inżyniera: ");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string wydzial;
        std::getline(std::cin, wydzial);

        Inz nowy_inz(imie, wydzial);
        firma->zatrudnij(nowy_inz);
    }

    void zatrudnij_magazyniera() {
        std::string imie = getRandomName();

        std::print("Wózek widłowy 1-TAK 0-NIE: ");
        int obsl;
        std::cin >> obsl;

        Mag nowy_mag(imie, obsl == 1);
        firma->zatrudnij(nowy_mag);
    }

    void zatrudnij_marketera() {
        std::string imie = getRandomName();

        std::print("Obserwujący: ");
        int follows;
        std::cin >> follows;

        Mkt nowy_mkt(imie, follows);
        firma->zatrudnij(nowy_mkt);
    }

    void zatrudnij_robotnika() {
        std::string imie = getRandomName();

        std::print("Rozmiar buta: ");
        double but;
        std::cin >> but;

        Rob nowy_rob(imie, but);
        firma->zatrudnij(nowy_rob);
    }

    void wez_kredyt_dialog() {
        std::print("Kwota kredytu: ");
        double kwota;
        std::cin >> kwota;

        std::print("Okres spłaty [max {}]: ", Stale::MAX_OKRES_KRED);
        int okres;
        std::cin >> okres;

        firma->wez_kredyt(kwota, okres);
    }
}; 

#endif // GRA_HPP
