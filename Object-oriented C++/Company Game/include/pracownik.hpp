#ifndef PRACOWNIK_HPP
#define PRACOWNIK_HPP

#include <string>
#include <print>

#include "stale.hpp"

class Pracownik {
protected:
    std::string imie;

public:
    explicit Pracownik(std::string name) : imie(std::move(name)) {}
    virtual ~Pracownik() = default;

    const std::string& get_imie() const { return imie; }
};

class Inz : public Pracownik {
private:
    std::string wydzial;

public:
    Inz(std::string name, std::string dept)
        : Pracownik(std::move(name)), wydzial(std::move(dept)) {
    }

    void print() const {
        std::print("  [Inżynier] {} | Wydział: {} | Pensja: {} zł\n",
            imie, wydzial, Stale::PENSJA_INZ);
    }

    static constexpr double get_pensja() { return Stale::PENSJA_INZ; }
    const std::string& get_wydzial() const { return wydzial; }
};

class Mkt : public Pracownik {
private:
    int follows;

public:
    Mkt(std::string name, int followers)
        : Pracownik(std::move(name)), follows(followers) {
    }

    void print() const {
        std::print("  [Marketer] {} | Obserwujący: {} | Pensja: {} zł\n",
            imie, follows, Stale::PENSJA_MKT);
    }

    static constexpr double get_pensja() { return Stale::PENSJA_MKT; }
    int get_follows() const { return follows; }
};

class Mag : public Pracownik {
private:
    bool obsl_widl;

public:
    Mag(std::string name, bool forklift)
        : Pracownik(std::move(name)), obsl_widl(forklift) {
    }

    void print() const {
        std::print("  [Magazynier] {} | Wózek widłowy: {} | Pensja: {} zł\n",
            imie, (obsl_widl ? "TAK" : "NIE"), Stale::PENSJA_MAG);
    }

    static constexpr double get_pensja() { return Stale::PENSJA_MAG; }
    bool get_obsl_widl() const { return obsl_widl; }
};

class Rob : public Pracownik {
private:
    double but;

public:
    Rob(std::string name, double shoe_size)
        : Pracownik(std::move(name)), but(shoe_size) {
    }

    void print() const {
        std::print("  [Robotnik] {} | Rozmiar buta: {} | Pensja: {} zł\n",
            imie, but, Stale::PENSJA_ROB);
    }

    static constexpr double get_pensja() { return Stale::PENSJA_ROB; }
    double get_but() const { return but; }
};

#endif
