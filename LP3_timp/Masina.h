#ifndef MASINA_H
#define MASINA_H
#include<iostream>
#include<string>
#include "Client.h"
#include "Haina.h"
using namespace std;


class Client;

class Masina
{

private:
    double durata;
    double capacitate;
    double capacitate_curenta;
    static const int max_articole_continute=10;
    int articole_continute;
    string** haine_continute;
    Haina* haina_control;
    double timp_start=9999999;
    

protected:
    int id;

public:

    Masina();
    Masina(double durata, double capacitate);
    Masina(const Masina&masina);
    virtual ~Masina();
    Masina &operator=(const Masina&masina);
    
//set
    void set_articole_continute(double articole_continute);
    virtual void set_durata(double durata);
    void set_capacitate_curenta(double capacitate_cureanta);
    void set_haine_continute(string*operatie,int index);
    string* get_haine_continute(int index);
    void set_timp_start(double timp);

//get
    void set_haina_control(Haina* haina);
    int get_articole_continute();
    const double get_durata();
    const double get_capacitate();
    const double get_capacitate_curenta();
    Haina* get_haina_control();
    int get_timp_start();
    int get_id(){return this->id;}


//interfata
    virtual void set_id() = 0; 


    friend istream& operator>>(istream& is, Masina& masina);
    friend ostream& operator<<(ostream&os, Masina& masina);
    virtual istream& read(istream& is);
    virtual ostream& print(ostream&os);

};

class Spalare_Obisnuita:public Masina
{
    public:
    void set_id(){this->id=0;}
};

class Spalare_Speciala:public Masina
{ 
    public:
    void set_id(){this->id=0;}
};

class Stoarcere:public Masina
{
  public:
  void set_id(){this->id=1;}
};

class Uscare:public Masina
{
   public:
   void set_id(){this->id=2;}
};

class Calcare:public Masina
{
    public:
    void set_id(){this->id=3;}
};


#endif