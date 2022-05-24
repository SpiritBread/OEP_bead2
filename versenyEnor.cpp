#include "versenyEnor.h"
#include <sstream>

using namespace std;

versenyEnor::versenyEnor(const string& path) {
    f.open(path.c_str());
    if(f.fail()) {
        throw FILE_ERROR;
    }
}


void versenyEnor::next()
{
    string line;
    getline(f , line);
    if( !f.fail() ){
        dx.nev="";
        sx = norm;
        istringstream is(line);

        string szo;
        is>>szo;
        while(!isdigit(szo[0])){
            dx.nev += szo + " ";
            is >> szo;
        }
        dx.iskola = szo;
        dx.pontszam=0;
        string verseny;
        int helyezes;
        for( is >> verseny >> helyezes ; !is.fail(); is >> verseny >> helyezes ){
            if (helyezes ==1 ){
                dx.pontszam += 12;
            }
            else if( helyezes == 2){
                dx.pontszam += 10;
            }
            else if( helyezes == 3){
                dx.pontszam += 8;
            }
            else if( helyezes == 4){
                dx.pontszam += 6;
            }
            else if( helyezes == 5){
                dx.pontszam += 4;
            }
            else if( helyezes == 6){
                dx.pontszam += 2;
            }

        }
    }else{
        sx = abnorm;
    }
}
