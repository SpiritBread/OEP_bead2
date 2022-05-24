#include <iostream>
#include "versenyEnor.h"

using namespace std;

string harmincpont(const string &name){
    versenyEnor enor(name);

    bool vanadat=false;
    for(enor.first(); !enor.end(); enor.next()){
        verseny dx = enor.current();
        if (dx.pontszam >= 30){
            return dx.nev;
        }
        vanadat=true;
    }
    if (vanadat){   //ha le tudott futni a ciklusunk legalabb egyszer akkor volt benne adat, de eljutottunk idaig, szoval senkinek nem volt 30 pontszama vagy tobb
        throw versenyEnor::POINTERR;
    }else{          //ha nem futott le a ciklusunk, nem volt adat a fileban, azaz ures fajl volt
        throw versenyEnor::EMPTYFILE;
    }
}

string gyoztessuli(const string &name){
    versenyEnor enor(name);
    enor.first();
    if (enor.end()){
        throw versenyEnor::EMPTYFILE;
    }

    bool elsovizsgalat=true;
    int sulipont;   //ezeknek kesobb adunk erteket, itt meg nem kell
    int maxsulipont;
    string gyoztessuli;
    string elozosuli;
    while(!enor.end()){
        verseny dx = enor.current();    //beallitjuk az aktualis sort
        if (elsovizsgalat){
            elsovizsgalat=false;
            elozosuli= dx.iskola;
            sulipont=dx.pontszam;
            maxsulipont=sulipont;
            gyoztessuli=dx.iskola;
        }else{
            //cout << "elozo suli: " << elozosuli << " aktsuli: " << dx.iskola <<endl;
            if(elozosuli == dx.iskola){
                sulipont+=dx.pontszam;
                if(sulipont>maxsulipont){
                    maxsulipont=sulipont;
                    gyoztessuli=dx.iskola;
                }
            }else{
                sulipont=dx.pontszam;
            }
        }
        elozosuli = dx.iskola;
        enor.next();
    }

    return gyoztessuli;
}

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main() {
    //1. feladatresz
    try{
        string a=harmincpont("infile.txt");
        // Eddig tartott valójában amit try-oltam
        cout << a << "legalabb 30 pontot szerzett." <<endl;
    }catch(versenyEnor::Exceptions e){
        if (e== versenyEnor::FILE_ERROR){
            cerr<< "Nincs ilyen fajl!" <<endl;
        }
        else if (versenyEnor::EMPTYFILE == e){
            cerr << "Ures fajl!" <<endl;
        }
        else if (versenyEnor::POINTERR == e){
            cerr << "Nem volt olyan versenyzo, akinek legalabb 30 pontja lett volna" <<endl;
        }
    }

    //2. feladatresz
    try{
        string  b=gyoztessuli("infile.txt");
        // Eddig tartott valójában amit try-oltam
        cout << "A pontszamversenyt, a(z): " << b << " nyerte!" <<endl;
    }catch(versenyEnor::Exceptions e){
        if (e== versenyEnor::FILE_ERROR){
            cerr<< "Nincs ilyen fajl!" <<endl;
        }
        else if (versenyEnor::EMPTYFILE == e){
            cerr << "Ures fajl!" <<endl;
        }
    }
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Rossz faljnev") {
    SECTION("harmincpont"){
        CHECK_THROWS(harmincpont("heble.txt"));
    }

    SECTION("gyoztessuli"){
        CHECK_THROWS(gyoztessuli("heble.txt"));
    }
}

TEST_CASE("Ures fajl") {
    SECTION("harmincpont"){
        CHECK_THROWS(harmincpont("uresfajl.txt"));
    }

    SECTION("gyoztessuli"){
        CHECK_THROWS(gyoztessuli("uresfajl.txt"));
    }
}

TEST_CASE("Egy sornyi adat"){
    SECTION("nincsharmincpont"){
        CHECK_THROWS(harmincpont("egysorteszt1.txt"));
    }

    SECTION("mindenpatent"){
        //Az egyetlen ember aki benne van: Kicsitsem Kincso
        CHECK("Kicsitsem Kincso " == harmincpont("egysorteszt2.txt"));
    }
}

TEST_CASE("Normalis adatok"){
    SECTION("3 soros adat"){
        CHECK("Egy Alma " == harmincpont("teszt1.txt"));
        CHECK("2000Templomdombi" == gyoztessuli("teszt1.txt"));
    }

    SECTION("peldabemenetem"){
        CHECK("Utod Elod " == harmincpont("infile.txt"));
        CHECK ("1084Radnoti" == gyoztessuli("infile.txt"));
    }
}

TEST_CASE("Enor"){
    SECTION("first-next"){
        versenyEnor a("infile.txt");
        CHECK_NOTHROW(a.first());
    }

    SECTION("end"){
        versenyEnor a("egysorteszt2.txt");
        a.first();
        CHECK_FALSE(a.end());

        a.next();
        CHECK(a.end());
    }

    SECTION("current"){
        versenyEnor a("egysorteszt2.txt");
        a.first();
        verseny dx = a.current();
        CHECK(dx.nev == harmincpont("egysorteszt2.txt"));
        CHECK(dx.iskola == gyoztessuli("egysorteszt2.txt"));
    }
}

#endif
