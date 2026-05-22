#ifndef PRACOWNIK_TYPY_HPP
#define PRACOWNIK_TYPY_HPP

#include <variant>
#include <print>

#include "pracownik.hpp"

using pracownik_t = std::variant<Inz, Mkt, Mag, Rob>;

struct PrinterPracownikow {
    void operator()(const Inz& p) const { p.print(); }
    void operator()(const Mkt& p) const { p.print(); }
    void operator()(const Mag& p) const { p.print(); }
    void operator()(const Rob& p) const { p.print(); }
};

struct SalaryVisitor {
    double operator()(const Inz&) const { return Inz::get_pensja(); }
    double operator()(const Mkt&) const { return Mkt::get_pensja(); }
    double operator()(const Mag&) const { return Mag::get_pensja(); }
    double operator()(const Rob&) const { return Rob::get_pensja(); }
};

struct CountInzVisitor {
    int& n;
    void operator()(const Inz&) const { ++n; }
    void operator()(const Mkt&) const {}
    void operator()(const Mag&) const {}
    void operator()(const Rob&) const {}
};

struct CountMktVisitor {
    int& n;
    void operator()(const Inz&) const {}
    void operator()(const Mkt&) const { ++n; }
    void operator()(const Mag&) const {}
    void operator()(const Rob&) const {}
};

struct CountMagVisitor {
    int& n;
    void operator()(const Inz&) const {}
    void operator()(const Mkt&) const {}
    void operator()(const Mag&) const { ++n; }
    void operator()(const Rob&) const {}
};

struct CountRobVisitor {
    int& n;
    void operator()(const Inz&) const {}
    void operator()(const Mkt&) const {}
    void operator()(const Mag&) const {}
    void operator()(const Rob&) const { ++n; }
};

#endif 
