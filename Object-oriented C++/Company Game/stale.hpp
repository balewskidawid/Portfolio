#ifndef STALE_HPP
#define STALE_HPP



namespace Stale {

    constexpr const char* DOMYSLNY_WYDZIAL_INZ = "MEiL";
    constexpr int         DOMYSLNI_FOLLOWERS_MKT = 1000;
    constexpr bool        DOMYSLNA_OBSLUGA_WOZKA = true;
    constexpr double      DOMYSLNY_ROZMIAR_BUTA_ROB = 42.0;

    constexpr double CI = 200.0;      
    constexpr double CMag = 50.0;   
    constexpr double CMkt = 40.0;   
    constexpr double CR = 10.0;      

    constexpr double PENSJA_INZ = 3000.0;   
    constexpr double PENSJA_MAG = 1500.0;   
    constexpr double PENSJA_MKT = 2000.0;   
    constexpr double PENSJA_ROB = 1250.0;   

    constexpr int MAX_PRAC = 100;           
   
	constexpr int N = 6;  // mno¿nik do obliczania wartoœci firmy na podstawie œrednich przychodów
	constexpr double M = 2.5;   // mno¿nik maksymalnego zad³u¿enia wzglêdem wartoœci firmy

    constexpr double CEL_WYGRANEJ = 100000.0;   
    constexpr double KWOTA_STARTOWA = 20000.0;  

    constexpr int MAX_KREDYT = 10;
    constexpr int MAX_OKRES_KRED = 24;

    constexpr double OPROCENTOWANIE_KROTKI_OKRES = 0.05;  
    constexpr double OPROCENTOWANIE_SREDNI_OKRES = 0.10;  
    constexpr double OPROCENTOWANIE_DLUGI_OKRES = 0.15; 

    constexpr int OKRES_KROTKI_MAX = 6;
    constexpr int OKRES_SREDNI_MAX = 12;
}

#endif 
