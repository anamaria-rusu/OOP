#ifndef HAINA_H
#define HAINA_H

#include<iostream>
#include<string>
#include<cstring>


using namespace std;

class Haina
{
protected:
    char* tip_spalare;
    double temperatura_minima;
    double temperatura_maxima;
    double durata_operatie[4];
    bool status;
    int trecere;
    double greutate;
    char* culoare; 
    const double detergent_fix=100;
    string operatie[4];
    double detergent;
    double timp_calcare;

public:
    Haina();
    Haina(const char* culoare, const char* tip_spalare,double temperatura_minima,double temperatura_maxima,double greutate);
    Haina(const Haina& haina);
    virtual ~Haina();
    Haina&operator=(const Haina &haina);
    

    friend istream& operator>>(istream& is, Haina& haina);
    friend ostream& operator<<(ostream&os, Haina& haina);
    virtual istream& read(istream& is);
    virtual ostream& print(ostream&os);
    

    
    //virtualizare + polimorfism
    virtual void calcul_timp_calcare(double greutate){this->timp_calcare=0;};
    virtual void calcul_detergent(double greutate){this->detergent=0;};


   
    //set
    void set_durata(double durata,int i);
    void set_operatie(string operatiee,int i);
    void set_trecere(int trecere);
    void set_status(bool status);


    
    //get
    char* get_tip_spalare();
    double get_temp_min();
    double get_temp_max();
    double* get_durata();
    bool get_status();
    int get_trecere();
    char* get_culoare();
    double get_greutate();
    string* get_operatie();
    double get_timp_calcare();
    double get_detergent();
    string& get_adresa_operatie(int index);



    //fct membre
    void verificare_comanda(Haina &haina,bool verificare_status);

};

class Rochie:public Haina
{
public:
    Rochie();
    Rochie(const char* culoare,const char* tip_spalare, double temperatura_minima,double temperatura_maxima,double greutate);
    Rochie(const Rochie& rochie);
    void calcul_timp_calcare(double greutate);
    void calcul_detergent(double greutate);

    //pentru RTTI + downcasting
    void afisare_tip_haina() const {cout<<"S-a introdus o rochie!\n";}
};

class Pantaloni:public Haina
{
public:
    Pantaloni();
    Pantaloni(const char* culoare,const char* tip_spalare, double temperatura_minima,double temperatura_maxima,double greutate);
    Pantaloni(const Pantaloni& pantaloni);
    void calcul_timp_calcare(double greutate);
    void calcul_detergent(double greutate);
    
    //pentru RTTI + downcasting
    void afisare_tip_haina() const {cout<<"S-a introdus o pereche de pantaloni!\n";}


    //conversie de tip -- exemplu
    Pantaloni(Rochie& rochie) 
    {
        cout<<"\nconversie pantaloni-rochie\n";
        this->culoare=new char[256];
        strcpy(this->culoare, rochie.get_culoare()); 

        this->tip_spalare=new char[256];
        strcpy(this->tip_spalare,rochie.get_tip_spalare());

        this->temperatura_maxima=rochie.get_temp_max();
        this->temperatura_minima=rochie.get_temp_min();
        this->greutate=rochie.get_greutate();

        for(int i=0;i<4;i++){this->durata_operatie[i]=rochie.get_durata()[i];}
        this->status=rochie.get_status();
        this->trecere=rochie.get_trecere();

        this->detergent-rochie.get_detergent();
        this->timp_calcare=rochie.get_timp_calcare();
        for(int i=0;i<4;i++){this->operatie[i]=rochie.get_operatie()[i];}
    }
    
    Pantaloni&operator=(Rochie &rochie)
    {
        if(rochie.get_culoare()==NULL)
        {
            if(this->culoare!=NULL)
            {
                char*del=this->culoare;
                this->culoare=NULL;
                delete[] del;
            }
        }
        else
        {
            if(this->culoare!=NULL)
                delete[] culoare;
            culoare=NULL;
            if(this->culoare==NULL)
                this->culoare=new char[256];
            strcpy(this->culoare, rochie.get_culoare());
        }


        if(rochie.get_tip_spalare()==NULL)
        {
            if(this->tip_spalare!=NULL)
            {
                char*del=this->tip_spalare;
                this->tip_spalare=NULL;
                delete[] del;
            }
        }
        else
        {
            if(this->tip_spalare!=NULL)
                delete[] tip_spalare;
            tip_spalare=NULL;
            if(this->tip_spalare==NULL)
                this->tip_spalare=new char[256];
            strcpy(this->tip_spalare, rochie.get_tip_spalare());
        }



        this->temperatura_minima=rochie.get_temp_min();
        this->temperatura_maxima=rochie.get_temp_min();
        this->greutate=rochie.get_greutate();
        for(int i=0;i<4;i++){this->durata_operatie[i]=rochie.get_durata()[i];}
        this->status=rochie.get_status();
        this->detergent=rochie.get_detergent();
        this->timp_calcare=rochie.get_timp_calcare();
        for(int i=0;i<4;i++){this->operatie[i]=rochie.get_operatie()[i];}

        return *this;
    }

};

class Camasa:public Haina
{
public:
    Camasa();
    Camasa(const char* culoare,const char* tip_spalare, double temperatura_minima,double temperatura_maxima,double greutate);
    Camasa(const Camasa&camasa);
    void calcul_timp_calcare(double greutate);
    void calcul_detergent(double greutate);

    //pentru RTTI + downcasting
    void afisare_tip_haina() const {cout<<"S-a introdus o camasa!\n";}
};

class Costum:public Haina
{
public:
    Costum();
    Costum(const char* culoare,const char* tip_spalare, double temperatura_minima,double temperatura_maxima,double greutate);
    Costum(const Costum&costum);
    void calcul_timp_calcare(double greutate);
    void calcul_detergent(double greutate);

    //pentru RTTI + downcasting
    void afisare_tip_haina() const {cout<<"S-a introdus un costum!\n";}
};

class Palton:public Haina
{
public:
    Palton();
    Palton(const char* culoare,const char* tip_spalare, double temperatura_minima,double temperatura_maxima,double greutate);
    Palton(const Palton&palton);
    void calcul_detergent(double greutate);

    //pentru RTTI + downcasting
    void afisare_tip_haina() const {cout<<"S-a introdus un palton!\n";}
    
};

class Geaca:public Haina
{
public:
    Geaca();
    Geaca(const char* culoare,const char* tip_spalare, double temperatura_minima,double temperatura_maxima,double greutate);
    Geaca(const Geaca&geaca);
    void calcul_detergent(double greutate);

    //pentru RTTI + downcasting
    void afisare_tip_haina() const {cout<<"S-a introdus o geaca!\n";}
};


#endif 