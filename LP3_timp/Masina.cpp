#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<limits>
#include<cmath>
#include<iomanip>
#include<typeinfo>
#include "Masina.h"
#include "input.h"

using namespace std;


Masina::Masina()
{
    this->durata=0;
    this->capacitate=1;
    this->capacitate_curenta=0;
    this->articole_continute=0;
    this->haine_continute=new string*[max_articole_continute];
    for(int i=0;i<max_articole_continute;i++)
        this->haine_continute[i]=new string;
    this->haina_control=new Haina;
}

Masina::Masina(double durata, double capacitate)
{
    this->durata=durata;
    this->capacitate=capacitate;
    this->capacitate_curenta=0;
    this->articole_continute=0;
    this->haine_continute=new string*[max_articole_continute];
    for(int i=0;i<max_articole_continute;i++)
        this->haine_continute[i]=new string;
    this->haina_control=new Haina;
}

Masina::Masina(const Masina&masina)
{
    this->durata=masina.durata;
    this->capacitate=masina.capacitate;
    this->capacitate_curenta=masina.capacitate_curenta;
    this->articole_continute=masina.articole_continute;
    this->haine_continute=new string*[max_articole_continute];
    for(int i=0;i<max_articole_continute;i++)
    {
        this->haine_continute[i]=new string;
        this->haine_continute[i]=masina.haine_continute[i];
    }
    this->haina_control=masina.haina_control;
}

Masina:: ~Masina()
{
    for(int i=0;i<max_articole_continute;i++)
    {
        if(haine_continute[i]!=NULL)
            delete haine_continute[i];
        haine_continute[i]=NULL;
    } 
    delete[]haine_continute;
    haine_continute=NULL;
}

Masina& Masina::operator=(const Masina& masina)
{
    this->durata=masina.durata;
    this->capacitate=masina.capacitate;
    this->capacitate_curenta=masina.capacitate_curenta;
    this->articole_continute=masina.articole_continute;

    for(int i=0;i<max_articole_continute;i++)
    {  
        if(masina.haine_continute[i]==NULL)
        {
            if(this->haine_continute[i]!=NULL)
            {
                string* del=this->haine_continute[i];
                this->haine_continute[i]=NULL;
                delete del;
            }
        }
        else
        {
            if(this->haine_continute[i]!=NULL)
                delete haine_continute[i];
            haine_continute[i]=NULL;
            if(this->haine_continute[i]==NULL)
                this->haine_continute[i]=new string;
           
        }
    } 

    if(masina.haina_control==NULL)
    {
        if(this->haina_control!=NULL)
        {
            Haina*del =this->haina_control;
            this->haina_control=NULL;
            delete[] del;
        }
        else
        {
            if(this->haina_control!=NULL)
                delete[] haina_control;
            haina_control=NULL;
            if(this->haina_control=NULL)
                this->haina_control=new Haina;
            this->haina_control=masina.haina_control;
        }
    }
    
    return *this;
}


//set
void Masina::set_durata(double durata){ this->durata=durata;}
void Masina::set_capacitate_curenta(double capacitate_curenta){this->capacitate_curenta=capacitate_curenta;}
void Masina::set_haina_control(Haina* haina){this->haina_control=haina;}
void Masina::set_haine_continute(string*operatie,int index){haine_continute[index]=operatie;}
void Masina::set_timp_start(double timp){this->timp_start=timp;}

//get
const double Masina::get_durata(){return this->durata;}
const double Masina::get_capacitate(){return this->capacitate;}
const double Masina::get_capacitate_curenta(){return this->capacitate_curenta;}
string* Masina::get_haine_continute(int index){return haine_continute[index];}
void Masina::set_articole_continute(double articole_continute){this->articole_continute=articole_continute;}
int Masina::get_articole_continute(){return this->articole_continute;}
Haina* Masina::get_haina_control(){return this->haina_control;}
int Masina::get_timp_start(){return this->timp_start;}



istream& operator>>(istream& is, Masina& masina)
{
    return masina.read(is);
}
ostream& operator<<(ostream&os, Masina& masina)
{
    return masina.print(os);
}
istream& Masina::read(istream& is)
{
    cout<<"Durata: ";durata=Input_double(is);
    cout<<"Capacitate: ";capacitate=Input_double(is);
    return is;
}
ostream& Masina::print(ostream&os)
{
    os<<"Informatii Masina:\n";
    os<<"Durata "<<durata<<' '<<"Capacitate "<<capacitate<<' '<<"Capacitate curenta "<<capacitate_curenta<<'\n';
    return os;
}



