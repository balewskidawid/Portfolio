#ifndef KREDYT_HPP
#define KREDYT_HPP

#include "stale.hpp"

class Kredyt {
private:
    double dlug;            
    int pozostale_raty;     
public:
    Kredyt() : dlug(0.0), pozostale_raty(0) {}
    
    Kredyt(double kwota, int okres) : pozostale_raty(okres) {
        double interest_rate = calculate_interest_rate(okres);
        dlug = kwota * (1.0 + interest_rate);
    }
    
    double splac_rate() {
        if (pozostale_raty <= 0) return 0.0;
        
        double rata = dlug / static_cast<double>(pozostale_raty);
        dlug -= rata;
        pozostale_raty--;
        
        return rata;
    }
    
    bool is_splacony() const {
        return pozostale_raty <= 0;
    }

    double get_dlug() const {
        return dlug;
    }

    int get_pozostale_raty() const {
        return pozostale_raty;
    }
    
private:
    static double calculate_interest_rate(int okres) {
        if (okres <= Stale::OKRES_KROTKI_MAX) {
            return Stale::OPROCENTOWANIE_KROTKI_OKRES;
        }
        else if (okres <= Stale::OKRES_SREDNI_MAX) {
            return Stale::OPROCENTOWANIE_SREDNI_OKRES;
        }
        else {
            return Stale::OPROCENTOWANIE_DLUGI_OKRES;
        }
    }
};

#endif 
