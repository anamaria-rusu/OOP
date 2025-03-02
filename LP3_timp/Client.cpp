#include<iostream>
#include<string>
#include<cstring>
#include<typeinfo>
#include<iomanip>
#include "Client.h"
#include "Haina.h" 
#include "input.h"

using namespace std;

Client::Client()
{
    this->id=0;
    this->nr_articole=0;
    this->status_final=false;
    for (int i = 0; i < max_haine_client; ++i) 
        this->haina[i] = nullptr; 
}

Client::Client(int nr_articole,const Haina& haina)
{
    this->id=0;
    this->status_final=false;
    this->nr_articole=nr_articole;
    for (int i = 0; i < max_haine_client; ++i)
    try{
        this->haina[i] = new Haina(haina);
    }
    catch(std::bad_alloc &e){
        std::cerr<<"bad alloc";
    }
    
}

Client::Client(const Client& client)
{
    this->id=client.id;
    this->nr_articole=client.nr_articole;
    this->status_final=client.status_final;
    for(int i=0;i<max_haine_client;i++)
    {
        try{
            this->haina[i]=new Haina;
            this->haina[i]=client.haina[i];
        }
        catch(std::bad_alloc &e){
            std::cerr<<"bad alloc";
        }
    }
}

Client::~Client()
{
    for (int i = 0; i < max_haine_client; ++i) 
    {
        if (haina[i] !=NULL) 
            delete haina[i];
        haina[i] = NULL;
    }         
}

Client& Client::operator=(const Client& client)
{
    this->id=client.id;
    this->nr_articole=client.nr_articole;
    this->status_final=client.status_final;
    for(int i=0;i<max_haine_client;i++){
    if(client.haina[i]==NULL)
    {
        if(this->haina[i]!=NULL)
        {
            Haina*del=this->haina[i];
            this->haina[i]=NULL;
            delete del;
        }
    }
    else
    {
        if(this->haina[i]!=NULL)
            delete haina[i];
        haina[i]=NULL;
        if(this->haina[i]==NULL)
            this->haina[i]=new Haina;
        this->haina[i]=client.haina[i];
    }
    }
    return *this;
}

istream& operator>>(istream& is, Client& client)
{
    return client.read(is);
}
ostream& operator<<(ostream&os, Client& client)
{
    return client.print(os);
}
istream& Client::read(istream& is)
{

    cout<<"Numar articole: ";nr_articole=Input_int(is);
    cout<<endl;
    
    for(int i=0;i<nr_articole;i++)
    {
        if(!i)
            is.get();

        string tip_haina;
        cout<<"Tipul hainei: ";
        is>>tip_haina;

        while(tip_haina!="rochie" && tip_haina!="pantaloni" && tip_haina!="palton" &&tip_haina!="geaca" &&tip_haina!="camasa" &&tip_haina!="costum")
        {
            cout<<"Incorect! Introduceti un tip de haina valid(rochie/pantaloni/camasa/costum/palton/geaca): ";
            is>>tip_haina;
        }
        
        if(tip_haina=="rochie")
        {
            try{
                haina[i]=new Rochie;
                //haina[i]->afisare_tip_haina();//eroare dynamic cast
                Rochie*rochie=dynamic_cast<Rochie*>(haina[i]);//pt a apela afisare_tip_haina care e daor in derivata 
                if(rochie)
                    rochie->afisare_tip_haina();
            }catch(const std::bad_cast&e)
            {
                std::cerr << "Bad cast " << e.what() << '\n';
            }
        }
        else if(tip_haina=="pantaloni")
        {
            try{
                haina[i]=new Pantaloni;
                Pantaloni*pantaloni=dynamic_cast<Pantaloni*>(haina[i]);
                if(pantaloni)
                    pantaloni->afisare_tip_haina();
            }catch(const std::bad_cast&e)
            {
                std::cerr << "Bad cast " << e.what() << '\n';
            }
           
        }   
        else if(tip_haina=="costum")
        {
            try{
                haina[i]=new Costum;
                Costum*costum=dynamic_cast<Costum*>(haina[i]);
                if(costum)
                    costum->afisare_tip_haina();
            }catch(const std::bad_cast&e)
            {
                std::cerr << "Bad cast  " << e.what() << '\n';
            }
           
        }   
        else if(tip_haina=="camasa")
        {
            try{
                haina[i]=new Camasa;
                Camasa*camasa=dynamic_cast<Camasa*>(haina[i]);
                if(camasa)
                    camasa->afisare_tip_haina();
            }catch(const std::bad_cast&e)
            {
                std::cerr << "Bad cast " << e.what() << '\n';
            }
            
        }   
        else if(tip_haina=="palton")
        {
            try{
                haina[i]=new Palton;
                Palton*palton=dynamic_cast<Palton*>(haina[i]);
                if(palton)
                    palton->afisare_tip_haina();
            }catch(const std::bad_cast&e)
            {
                std::cerr << "Bad cast " << e.what() << '\n';
            }
           
        }
        else if(tip_haina=="geaca")
        {
            try{
                haina[i]=new Geaca;
                Geaca*geaca=dynamic_cast<Geaca*>(haina[i]);
                if(geaca)
                    geaca->afisare_tip_haina();
            }catch(const std::bad_cast&e)
            {
                std::cerr << "Bad cast " << e.what() << '\n';
            }
        }

        is.get();
        is>>*(haina[i]); 
        haina[i]->calcul_timp_calcare(haina[i]->get_greutate());
        haina[i]->calcul_detergent(haina[i]->get_greutate());
        
        
        string confirmare_haina;
        cout<<"Doriti sa confirmati inregistrarea hainei(da/nu)? ";is>>confirmare_haina;
        if(confirmare_haina=="da")
            cout<<"Haina inregistrata!"<<endl;
        else
        {
            cout<<"Haina stearsa!"<<endl;
            delete haina[i];
            cout<<"Reintroduceti alte date pentru haina numarul "<<i+1<<" (da/nu) ";is>>confirmare_haina;
            if(confirmare_haina=="da")
                i--;
            else
                nr_articole--,i--;
        }

    }


    string confirmare;
    cout<<"Doriti sa confirmati comanda(da/nu)? ";is>>confirmare;
    if(confirmare=="da")
        cout<<"Comanda confirmata!"<<endl;
    else
    {
        for(int i=0;i<nr_articole;i++)
            if(haina[i]!=NULL)
                delete haina[i];
        nr_articole=0;
    }

    return is;
}
ostream& Client::print(ostream&os)
{
    double suma=0;
    double timp=0;
    std::cout<<endl;
    std::cout<<"--------------------------------------- Comanda "<<id<<" ---------------------------------------"<<endl;
    if(status_final==1)
    std::cout<<"Comanda a fost finalizata !\n";
    std::cout<<endl;
    std::cout<<"Detaliile comenzii sunt : \n";
    for(int j=0;j<nr_articole;j++)
    {
        std::cout<<"Haina numarul "<<j+1<<" : "<<endl;
        std::cout<<"Cantitate detergent folosita pentru acest articol : "<<haina[j]->get_detergent()<<" grame\n"<<endl;
        std::cout<<"Operatii efectuate | durata operatiei : \n";


        std::cout<<"spalare   | durata: "<<haina[j]->get_durata()[0]<<"    status:" <<haina[j]->get_operatie()[0]<<endl;
        timp+=haina[j]->get_durata()[0];
        
        if(haina[j]->get_operatie()[1]!="Null")
        {
            cout<<"stoarcere | durata: "<<haina[j]->get_durata()[1]<<"     status:" <<haina[j]->get_operatie()[1]<<endl;
            timp+=haina[j]->get_durata()[1]; 
        }
        
        
        std::cout<<"uscare    | durata: "<<haina[j]->get_durata()[2]<<"    status:" <<haina[j]->get_operatie()[2]<<endl;
        timp+=haina[j]->get_durata()[2];



        if(haina[j]->get_operatie()[3]!="Null")
        {
            cout<<"calcare   | durata: "<<std::fixed << std::setprecision(3)<<haina[j]->get_durata()[3]<<"   status:" <<haina[j]->get_operatie()[3]<<endl;
            std::cout<<endl;timp+=haina[j]->get_durata()[3];
        }
        
        suma+=haina[j]->get_detergent();
        std::cout<<endl;
        
    }
    std::cout<<"Cantitatea de detergent totala este : "<<suma<<" grame\n";
    std::cout<<"Timpul total petrecut in masini este aproximativ : "<< std::fixed << std::setprecision(2)<<timp<<" ore\n";
    std::cout<<"-----------------------------------------------------------------------------------------"<<endl;

    return os;

}



//get
int Client::get_nr_articole(){return this->nr_articole;}
bool Client::get_status_final(){return this->status_final;}
Haina* Client::getHaina(int index){return this->haina[index];}
bool Client::get_afisat(){return this->afisat;}

//set
void Client::set_status_final(bool status_final){this->status_final=status_final;}
void Client::set_id(int id){this->id=id;}
void Client::set_afisat(bool afisat){this->afisat=true;}



//functii membre
bool Client::verificare_comanda( Client& client)
{
    for(int i=0;i<client.get_nr_articole();i++)
        if(client.getHaina(i)->get_status()==false)
           return false;
    client.set_status_final(true);
    return true;

}

void Client::afisare_haina(int i)
{ 
    try 
    {
        if (i < 0 || i>nr_articole) {
            throw std::out_of_range("Index out of range");
        }
        cout<<*haina[i];
    } 
    catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void Client::afisare_haina()
{
    for(int i=0;i<nr_articole;i++) 
        cout<<*haina[i];
};