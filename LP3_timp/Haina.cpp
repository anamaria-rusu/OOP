#include<iostream>
#include<string>
#include<cstring>
#include "Haina.h"
#include "input.h"


using namespace std;

Haina::Haina() 
{
    this->culoare=NULL;
    this->tip_spalare=NULL;
    this->temperatura_minima=0;
    this->temperatura_maxima=100;
    this->greutate=0;
    for(int i=0;i<4;i++){this->durata_operatie[i]=0;}
    this->status=false;
    this->trecere=0;
    this->detergent=0;
    this->timp_calcare=0;
    for(int i=0;i<4;i++){this->operatie[i]="X";}
}
Haina::Haina(const char* culoare, const char* tip_spalare,double temperatura_minima,double temperatura_maxima,double greutate)
{
    this->culoare=new char[256];
    strcpy(this->culoare, culoare); 

    this->tip_spalare=new char[256];
    strcpy(this->tip_spalare,tip_spalare);

    this->temperatura_maxima=temperatura_maxima;
    this->temperatura_minima=temperatura_minima;
    this->greutate=greutate;

    for(int i=0;i<4;i++){this->durata_operatie[i]=0;}
    this->status=false;
    this->trecere=0;
    this->detergent=0;
    this->timp_calcare=0;
    for(int i=0;i<4;i++){this->operatie[i]="X";}

}
Haina:: Haina(const Haina& haina)
{
    this->culoare=new char[256];
    strcpy(this->culoare, haina.culoare); 

    this->tip_spalare=new char[256];
    strcpy(this->tip_spalare,haina.tip_spalare);

    this->temperatura_maxima=haina.temperatura_maxima;
    this->temperatura_minima=haina.temperatura_minima;
    this->greutate=haina.greutate;

    for(int i=0;i<4;i++){this->durata_operatie[i]=haina.durata_operatie[i];}
    this->status=haina.status;
    this->trecere=haina.trecere;

    this->detergent=haina.detergent;
    this->timp_calcare=haina.timp_calcare;
    for(int i=0;i<4;i++){this->operatie[i]=haina.operatie[i];}

}
Haina::~Haina()
{  
    if(culoare!=NULL)
        delete[] culoare;
    culoare=NULL;


    if(tip_spalare!=NULL)
        delete[] tip_spalare;
    tip_spalare=NULL;
}
Haina&Haina::operator=(const Haina &haina)
{
    if(haina.culoare==NULL)
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
        strcpy(this->culoare, haina.culoare);
    }


    if(haina.tip_spalare==NULL)
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
        strcpy(this->tip_spalare, haina.tip_spalare);
    }



    this->temperatura_minima=haina.temperatura_minima;
    this->temperatura_maxima=haina.temperatura_minima;
    this->greutate=haina.greutate;

    for(int i=0;i<4;i++){this->durata_operatie[i]=haina.durata_operatie[i];}
    this->status=haina.status;
    this->trecere=haina.trecere;

    this->detergent=haina.detergent;
    this->timp_calcare=haina.timp_calcare;
    for(int i=0;i<4;i++){this->operatie[i]=haina.operatie[i];}

    return *this;
   
}


Rochie::Rochie():Haina()
{
    for(int i=0;i<4;i++){this->operatie[i]="X";}
    
}
Rochie::Rochie(const char* culoare,const char* tip_spalare, double temperatura_minima,double temperatura_maxima,double greutate):Haina(culoare,tip_spalare,temperatura_minima,temperatura_maxima, greutate)
{
    for(int i=0;i<4;i++){this->operatie[i]="X";}
}
Rochie::Rochie(const Rochie& rochie):Haina(rochie)
{
    for(int i=0;i<4;i++)
        this->operatie[i]=rochie.operatie[i];
}


Pantaloni::Pantaloni():Haina()
{
    for(int i=0;i<4;i++){this->operatie[i]="X";}
}
Pantaloni::Pantaloni(const char* culoare,const char* tip_spalare, double temperatura_minima,double temperatura_maxima,double greutate):Haina(culoare,tip_spalare,temperatura_minima,temperatura_maxima, greutate)
{
    for(int i=0;i<4;i++){this->operatie[i]="X";}
}
Pantaloni::Pantaloni(const Pantaloni& pantaloni):Haina(pantaloni)
{
    for(int i=0;i<4;i++)
        this->operatie[i]=pantaloni.operatie[i];
}


Camasa::Camasa():Haina()
{
    for(int i=0;i<4;i++){this->operatie[i]="X";}
}
Camasa::Camasa(const char* culoare,const char* tip_spalare, double temperatura_minima,double temperatura_maxima,double greutate):Haina(culoare,tip_spalare,temperatura_minima,temperatura_maxima, greutate)
{
    for(int i=0;i<4;i++){this->operatie[i]="X";}
}
Camasa::Camasa(const Camasa&camasa):Haina(camasa)
{ 
for(int i=0;i<4;i++)
    this->operatie[i]=camasa.operatie[i];
}


Costum::Costum():Haina()
{
    for(int i=0;i<4;i++){this->operatie[i]="X";}
}
Costum::Costum(const char* culoare,const char* tip_spalare, double temperatura_minima,double temperatura_maxima,double greutate):Haina(culoare,tip_spalare,temperatura_minima,temperatura_maxima, greutate)
{
    for(int i=0;i<4;i++){this->operatie[i]="X";}
}
Costum::Costum(const Costum&costum):Haina(costum)
{
for(int i=0;i<4;i++)
    this->operatie[i]=costum.operatie[i];
}


Palton::Palton():Haina()
{
    for(int i=0;i<4;i++){if(i%2)this->operatie[i]="Null"; else this->operatie[i]="X";} 
}
Palton::Palton(const char* culoare,const char* tip_spalare, double temperatura_minima,double temperatura_maxima,double greutate):Haina(culoare,tip_spalare,temperatura_minima,temperatura_maxima, greutate)
{
    for(int i=0;i<4;i++){if(i%2)this->operatie[i]="Null"; else this->operatie[i]="X";}
}
Palton::Palton(const Palton&palton):Haina(palton)
{   
    for(int i=0;i<4;i++)
        this->operatie[i]=palton.operatie[i];
}


Geaca::Geaca():Haina()
{  
    for(int i=0;i<4;i++){if(i%2)this->operatie[i]="Null"; else this->operatie[i]="X";}
}
Geaca::Geaca(const char* culoare,const char* tip_spalare, double temperatura_minima,double temperatura_maxima,double greutate):Haina(culoare,tip_spalare,temperatura_minima,temperatura_maxima, greutate)
{
    for(int i=0;i<4;i++){if(i%2)this->operatie[i]="Null"; else this->operatie[i]="X";}
}
Geaca::Geaca(const Geaca&geaca):Haina(geaca)
{
    for(int i=0;i<4;i++)
        this->operatie[i]=geaca.operatie[i];
}




istream& operator>>(istream& is, Haina& haina)
{
    return haina.read(is);
}
ostream& operator<<(ostream&os, Haina& haina)
{
    return haina.print(os);
}
istream& Haina::read(istream& is)
{
    cout<<"Culoare: ";
    if(culoare==NULL)
        culoare=new char[256];
    is.getline(culoare,256);

    if(strcmp(culoare,"inchis")!=0 && strcmp(culoare,"deschis")!=0)
    {
        do
        {
            cout<<"Incorect! Reintroduceti optiunea(inchis/deschis):";
            is.getline(culoare,256);
        }while (strcmp(culoare,"deschis")!=0 && strcmp(culoare,"inchis")!=0);
    }


    cout<<"Tip spalare: ";
    if(tip_spalare==NULL)
        tip_spalare=new char[256];
    is.getline(tip_spalare,256);

    if(strcmp(tip_spalare,"special")!=0 && strcmp(tip_spalare,"obisnuit")!=0)
    {
        do
        {
            cout<<"Incorect! Reintroduceti optiunea(obisnuit/special):";
            is.getline(tip_spalare,256);
        } while (strcmp(tip_spalare,"special")!=0 && strcmp(tip_spalare,"obisnuit")!=0);
    }


    cout<<"Temperatura minima: ";
    temperatura_minima=Input_double(is);

    cout<<"Temperatura maxima: ";
    temperatura_maxima=Input_double(is);

    cout<<"Greutate: ";
    greutate=Input_double(is);

    is.get();
    return is;
}
ostream& Haina::print(ostream&os)
{
    cout<<endl;
    cout<<"Informatii introduse pentru haina:\n";
    cout<<"tip spalare: "<<tip_spalare<<endl;
    cout<<"temp min: "<<temperatura_minima<<endl;
    cout<<"temp max: "<<temperatura_maxima<<endl;
    cout<<"greutate: "<<greutate<<endl;
    cout<<"culoare: "<<culoare<<endl;
    //cout<<"status: "<<status<<endl;
    //cout<<"timp calcare: "<<timp_calcare<<endl;
    //cout<<"detergent: "<<detergent<<endl;
    //cout<<"operatiile si duratele lor "<<endl;
    //for(int i=0;i<4;i++){if(operatie[i]!="Null") cout<<operatie[i]<<' '<<durata_operatie[i]<<endl;}
    return os;
}



//calcul timp calcare
void Rochie::calcul_timp_calcare(double greutate){this->timp_calcare=(double)(.1*(100*greutate)/3600);}
void Camasa::calcul_timp_calcare(double greutate){this->timp_calcare=(double)(.1*(120*greutate)/3600);}
void Costum::calcul_timp_calcare(double greutate){this->timp_calcare=(double)(.1*(240*greutate)/3600);}
void Pantaloni::calcul_timp_calcare(double greutate){this->timp_calcare=(double)((90*greutate )/3600);}


//calcul detergent
void Rochie::calcul_detergent(double greutate){this->detergent=detergent_fix;}
void Pantaloni::calcul_detergent(double greutate){if(strcmp(this->culoare,"inchis")==0) this->detergent=detergent_fix*2; else this->detergent=detergent_fix;}
void Camasa::calcul_detergent(double greutate){this->detergent=detergent_fix;}
void Costum::calcul_detergent(double greutate){this->detergent=100*greutate;}
void Palton::calcul_detergent(double greutate){this->detergent=100*greutate;}
void Geaca::calcul_detergent(double greutate){this->detergent=100*greutate;}



//get
char* Haina::get_tip_spalare(){return this->tip_spalare;}
double Haina::get_temp_min(){return this->temperatura_minima;}
double Haina::get_temp_max(){return this->temperatura_maxima;}
double* Haina::get_durata(){return this->durata_operatie;}
bool Haina::get_status(){return this->status;}
int Haina::get_trecere(){return this->trecere;}
char* Haina::get_culoare(){return this->culoare;}
double Haina::get_greutate(){return this->greutate;}
string* Haina::get_operatie(){return this->operatie;}
double Haina::get_timp_calcare(){return this->timp_calcare;}
double Haina::get_detergent(){return this->detergent;}
string& Haina::get_adresa_operatie(int index){return this->operatie[index];}


//set
void Haina::set_trecere(int trecere){this->trecere=trecere;}
void Haina::set_durata(double durata,int i){durata_operatie[i]=durata;}
void Haina::set_operatie(string operatiee,int i){operatie[i]=operatiee;}
void Haina::set_status(bool status){this->status=status;}


//fct membre
void Haina::verificare_comanda( Haina &haina,bool verificare_status)
{
    if(verificare_status)
        haina.set_status(true);
}

