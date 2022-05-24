#pragma once
#include <fstream>

struct verseny {
    std::string nev;
    std::string iskola;
    int pontszam;
};

class versenyEnor {
public:
    enum Status { norm, abnorm };
    enum Exceptions {FILE_ERROR,EMPTYFILE,POINTERR};

    versenyEnor(const std::string& path);

    void first() { next(); }
    void next();
    verseny current() const {return dx;}
    bool end() const { return sx==abnorm; }

private:
    verseny dx;
    std::ifstream f;
    Status sx;
};
