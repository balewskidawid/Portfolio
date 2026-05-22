#ifndef FIRMA_HPP
#define FIRMA_HPP

#include <memory>
#include <algorithm>
#include <vector>
#include <print>

#include "stale.hpp"
#include "pracownik_typy.hpp"
#include "kredyt.hpp"
#include "RandomNameGenerator.hpp"

class Firma {
private:
    double stan_konta;
    int n_kredytow;
    std::unique_ptr<Kredyt[]> kredyty;
    int n_prac;
    std::vector<pracownik_t> prac;
    std::unique_ptr<double[]> historia_przych;
    int historia_index;
    int historia_filled;

    void dodaj_pracownika(const pracownik_t& p) {
        if (static_cast<int>(prac.size()) >= Stale::MAX_PRAC) return;
        prac.push_back(p);
        ++n_prac;
    }

public:
    Firma() :
        stan_konta(Stale::KWOTA_STARTOWA),
        n_kredytow(0),
        kredyty(new Kredyt[Stale::MAX_KREDYT]),
        n_prac(0),
        prac(),
        historia_przych(new double[Stale::N]),
        historia_index(0),
        historia_filled(0)
    {
        for (int i = 0; i < Stale::N; ++i) historia_przych[i] = 0.0;

        prac.reserve(Stale::MAX_PRAC);
        dodaj_pracownika(Inz(getRandomName(), Stale::DOMYSLNY_WYDZIAL_INZ));
        dodaj_pracownika(Mkt(getRandomName(), Stale::DOMYSLNI_FOLLOWERS_MKT));
        dodaj_pracownika(Mag(getRandomName(), Stale::DOMYSLNA_OBSLUGA_WOZKA));
        dodaj_pracownika(Rob(getRandomName(), Stale::DOMYSLNY_ROZMIAR_BUTA_ROB));
    }

    void drukuj_pracownikow() const {
        if (n_prac == 0) {
            std::print("\nBrak pracowników w firmie\n");
            return;
        }
        std::print("\nZespół ({}/{}):\n", n_prac, Stale::MAX_PRAC);
        for (const auto& p : prac) std::visit(PrinterPracownikow{}, p);
    }

    bool wez_kredyt(double kwota, int czas_splaty) {
        if (n_kredytow >= Stale::MAX_KREDYT) {
            std::print("Odroczono - zbyt wiele kredytów (max {})\n", Stale::MAX_KREDYT);
            return false;
        }
        if (czas_splaty <= 0 || czas_splaty > Stale::MAX_OKRES_KRED) {
            std::print("Niepoprawny okres - dozwolone 1-{} mies.\n", Stale::MAX_OKRES_KRED);
            return false;
        }
        if (kwota <= 0) {
            std::print("Kwota musi być dodatnia\n");
            return false;
        }

        const double total_debt = get_total_debt() + kwota;
        const double company_val = wartosc_firmy();
        if (total_debt > Stale::M * company_val) {
            std::print("Przekroczono limit zadłużenia {}x wartość spółki\n", Stale::M);
            std::print("Maksymalnie możesz jeszcze pożyczyć: {} zł\n",
                (Stale::M * company_val - get_total_debt()));
            return false;
        }

        kredyty[n_kredytow++] = Kredyt(kwota, czas_splaty);
        stan_konta += kwota;
        std::print("Przyjęto kredyt: {} zł, okres: {} mies.\n", kwota, czas_splaty);
        return true;
    }

    bool zatrudnij(const pracownik_t& nowy_pracownik) {
        if (static_cast<int>(prac.size()) >= Stale::MAX_PRAC) {
            std::print("Za dużo osób w firmie - limit {}\n", Stale::MAX_PRAC);
            return false;
        }
        prac.push_back(nowy_pracownik);
        ++n_prac;
        std::print("Dodano pracownika\n");
        return true;
    }

    void zaplac_wynagrodzenie() {
        double total_payroll = 0.0;
        for (const auto& p : prac)
            total_payroll += std::visit(SalaryVisitor{}, p);
        stan_konta -= total_payroll;
        std::print("Wypłaty: -{} zł\n", total_payroll);
    }

    void otrzymaj_przychod() {
        const double przychod = oblicz_przychod();
        stan_konta += przychod;

        historia_przych[historia_index] = przychod;
        historia_index = (historia_index + 1) % Stale::N;
        if (historia_filled < Stale::N) ++historia_filled;

        std::print("Przychód: +{} zł\n", przychod);
    }

    void splac_raty() {
        double total_payment = 0.0;
        for (int i = 0; i < n_kredytow; ++i) total_payment += kredyty[i].splac_rate();
        stan_konta -= total_payment;

        int new_count = 0;
        for (int i = 0; i < n_kredytow; ++i) {
            if (!kredyty[i].is_splacony()) {
                if (new_count != i) kredyty[new_count] = std::move(kredyty[i]);
                ++new_count;
            }
        }
        n_kredytow = new_count;

        if (total_payment > 0) std::print("Spłaty rat: -{} zł\n", total_payment);
    }

    double get_stan_konta() const { return stan_konta; }

    double wartosc_firmy() const {
        if (historia_filled == 0) {
            return 0.0;
        }

        double suma = 0.0;
        for (int i = 0; i < historia_filled; ++i) {
            suma += historia_przych[i];
        }
        return suma / static_cast<double>(historia_filled);
    }


    double oblicz_przychod() const {
        int n_inz = 0, n_mkt = 0, n_mag = 0, n_rob = 0;
        for (const auto& p : prac) {
            std::visit(CountInzVisitor{ n_inz }, p);
            std::visit(CountMktVisitor{ n_mkt }, p);
            std::visit(CountMagVisitor{ n_mag }, p);
            std::visit(CountRobVisitor{ n_rob }, p);
        }
        const double pojemnosc_magazynu = static_cast<double>(n_mag) * Stale::CMag;
        const double cena_produktu = static_cast<double>(n_inz) * Stale::CI;
        const double teoretyczna_produkcja = static_cast<double>(n_rob) * Stale::CR;
        const double faktyczna_produkcja = std::min(teoretyczna_produkcja, pojemnosc_magazynu);
        const double popyt = static_cast<double>(n_mkt) * Stale::CMkt;
        const double sprzedane = std::min(faktyczna_produkcja, popyt);
        return sprzedane * cena_produktu;
    }

    void wyswietl_stan() const {
        std::print("\nStan firmy\n");
        std::print("Saldo: {:>.2f} zł\n", stan_konta);
        std::print("Wartość spółki: {:>.2f} zł\n", wartosc_firmy());
        std::print("Zatrudnienie: {}\n", n_prac);
        std::print("Kredyty aktywne: {}\n", n_kredytow);
        std::print("Dług łączny: {:>.2f} zł\n", get_total_debt());
    }

    double get_total_debt() const {
        double total = 0.0;
        for (int i = 0; i < n_kredytow; ++i) total += kredyty[i].get_dlug();
        return total;
    }
};

#endif // FIRMA_HPP
