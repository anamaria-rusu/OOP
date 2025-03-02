#ifndef SPALATORIE_H
#define SPALATORI_H
#include <iostream>
#include <string>
#include <vector>
#include "Client.h"
#include "Haina.h"
#include "Masina.h"


//Singleton
class Spalatorie
{

private:
    Spalatorie();
    Spalatorie(const Spalatorie &spalatorie)=delete;
    Spalatorie(Spalatorie && spalatorie)=delete;
    Spalatorie &operator=(const Spalatorie &spalatorie)=delete;
    Spalatorie &operator=(Spalatorie && spalatorie)=delete;
    ~Spalatorie();

    inline static Spalatorie *spalatorie;

    double timp=0;
    bool finalizare=false;
    int numar_total_masini=0;
    int numar_clienti=0;
    static const int dimensiune=20;
    Masina* masini[dimensiune];
    Client* clienti[dimensiune];
    Haina* haine[dimensiune];

public:
    static Spalatorie* getInstance()
    {
        if(spalatorie==nullptr)
            spalatorie=new Spalatorie();
        return spalatorie;
    }

//meniul
    void Meniu(istream*in);


//fct membre
    void procesare_timp(double timp,istream*in);
    void adauga_timp();
    void adaugare_masini(istream&is);
    void afisare_masini();
    void adauga_comanda(istream&in);
    void afisare_clienti(istream&in);
    void adaugare_haine(int operatie,Haina&haina,istream*in);
    bool verificare_adaugare_haine(Haina&haina,Haina&h,Masina&masina);


//set+get
    void set_timp(double timp);
    int get_timp();
    void set_finalizare(bool valoare);
    int get_numar_total_masini();
    void set_numar_total_masini(int numar);
    int get_numar_clienti();
    void set_numar_client(int numar);

};


#endif
