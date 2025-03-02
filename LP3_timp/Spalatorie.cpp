#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include<typeinfo>
#include "Client.h"
#include "Haina.h"
#include "Masina.h"
#include "Spalatorie.h"
#include "input.h"

using namespace std;

    
bool Spalatorie::verificare_adaugare_haine(Haina&haina,Haina&haina_control,Masina&masina)
{
    if(masina.get_id()==3)//calcare
    {
        if(masina.get_capacitate_curenta()==0)//se baga in maisna
        {
            masina.set_durata(haina.get_timp_calcare());
            return true;
        }
        return false;
    }

    if(masina.get_id()==0)//verificam sa concida tipul de spalare obisnuita/speciala
    {
        const type_info& typeInfo_spalare=typeid(masina);
        if(!((typeInfo_spalare==typeid(Spalare_Obisnuita) && strcmp(haina.get_tip_spalare(),"obisnuit")==0) || (typeInfo_spalare==typeid(Spalare_Speciala) && strcmp(haina.get_tip_spalare(),"special")==0)))
            return false;
    }

    
    if(masina.get_capacitate_curenta()+haina.get_greutate()<=masina.get_capacitate())
    {
        if(masina.get_id()!=0)//pentru restul masinilor nu avem alte conditii pentru a introduce haine in masini , decat greutatea
            return true;

        if(strcmp(haina.get_culoare(),haina_control.get_culoare())==0 && (haina.get_temp_min()<=haina_control.get_temp_max() && haina.get_temp_max()>=haina.get_temp_max() ||haina.get_temp_max()>=haina_control.get_temp_min() && haina.get_temp_min()<=haina_control.get_temp_max()))
            return true;
    }
    return false;
}


void Spalatorie::adaugare_haine(int operatie,Haina&haina,istream*in)
{
    for(int i=0;i<numar_total_masini;i++)
    {
        if(masini[i]->get_capacitate_curenta()==0)
            masini[i]->set_haina_control(&haina);
        Haina*h=masini[i]->get_haina_control();
        
        if(masini[i]->get_id()==operatie && haina.get_operatie()[operatie]!="asteptare")
        {
            if(verificare_adaugare_haine(haina,*h,*masini[i]))
            {   
                if(operatie==3)//masinile de calcat au capacitate constanta 1
                    masini[i]->set_capacitate_curenta(1);
                else//restul masinilor au capacitate variabila
                    masini[i]->set_capacitate_curenta(masini[i]->get_capacitate_curenta()+haina.get_greutate());

                haina.set_durata(masini[i]->get_durata(),operatie);//setam durata hainei in masina de tip index op 
                haina.set_operatie("asteptare",operatie);//la pozitia operatie din vectorul de operatii ale hainei punem "astepatare"
                masini[i]->set_haine_continute(&haina.get_adresa_operatie(operatie),masini[i]->get_articole_continute());//memoram adresa hainei din masina
                masini[i]->set_articole_continute(masini[i]->get_articole_continute()+1);//actualizam cate articole avem in masina
            }
        }
        

        if(masini[i]->get_capacitate_curenta()>=masini[i]->get_capacitate()/2)
        {
            masini[i]->set_timp_start(Spalatorie::timp);
            Meniu(in);
        }
        else if(finalizare)
        {
            masini[i]->set_timp_start(Spalatorie::timp);
        }

    }
}


void Spalatorie::procesare_timp(double timp,istream*in)
{
    for(int i=0;i<numar_total_masini;i++)//parcuregm toate masinile si vedem ce se intampla la momentul de timp "timp"
    {
        if((masini[i]->get_timp_start()+masini[i]->get_durata()<=Spalatorie::timp  &&  masini[i]->get_capacitate_curenta()>=masini[i]->get_capacitate()/2 )|| (finalizare&&masini[i]->get_timp_start()+masini[i]->get_durata()<=Spalatorie::timp ))
        {
            for(int j=0;j<masini[i]->get_articole_continute();j++)
                *masini[i]->get_haine_continute(j)="terminat";
            masini[i]->set_articole_continute(0);
            masini[i]->set_capacitate_curenta(0);
        }
    }   
    

    int finish=0;
  
    
    for(int i=0;i<numar_clienti;i++)//parcurgem clientii
    {
        if(clienti[i]->get_status_final()==false)
        {
            for(int j=0;j<clienti[i]->get_nr_articole();j++)//parcurgem hainele clientului
            {
                bool verificare_status=true;
                for(int op=0;op<4;op++)//parcurgem fiecare operatie disponibila
                {
                if(clienti[i]->getHaina(j)->get_operatie()[op]=="asteptare" && finalizare==false)
                {
                    verificare_status=false;
                    break;
                }
                else if(clienti[i]->getHaina(j)->get_operatie()[op]=="X" && (op==0 || clienti[i]->getHaina(j)->get_operatie()[op-1]=="terminat" || clienti[i]->getHaina(j)->get_operatie()[op-1]=="Null"))
                {
                    verificare_status=false;
                    Spalatorie::adaugare_haine(op,*clienti[i]->getHaina(j),in);
                }
                else if(clienti[i]->getHaina(j)->get_operatie()[op]=="asteptare" && finalizare)
                {
                    verificare_status=false;
                    Spalatorie::adaugare_haine(op,*clienti[i]->getHaina(j),in);
                }
                }
               
                clienti[i]->getHaina(j)->verificare_comanda(*clienti[i]->getHaina(j),verificare_status);
            }
        
            if(clienti[i]->verificare_comanda(*clienti[i]))//verificam daca comanda e gata
            {
                if(clienti[i]->get_afisat()==false)
                {  
                    cout<<*(clienti[i])<<endl;
                    clienti[i]->set_afisat(true);
                }
                finish++;
            }
        }
    }
    if(finish==numar_clienti)
        std::cout<<"Toate comenzile sunt finalizate !";
}


void Spalatorie::adauga_comanda(istream&in)
{
    std::cout<<"\nIntroduceti timpul la care a avenit clientul:  ";
    double timp_client;in>>timp_client;
    std::cout<<"\nIntroduceti datele despre comanda numarul: "<<numar_clienti<<endl;
    clienti[numar_clienti]=new Client;
    clienti[numar_clienti]->set_id(numar_clienti);
    in>>*(clienti[numar_clienti]);

    if(clienti[numar_clienti]->get_nr_articole()!=0)
    {
        numar_clienti++;
        Spalatorie::timp=timp_client;
        Spalatorie::procesare_timp(timp,&in);
    }
     
    cout<<endl;
}


void Spalatorie::adauga_timp()
{
    Spalatorie::getInstance()->set_timp(0.5);
}

void Spalatorie::adaugare_masini(istream&is)
{
   int numar_masini;

   cout<<"Introduceti datele pentru masinile din spalatorie: \n"<<endl;
   cout<<"Numarul masinilor de spalat obisnuit: "; is>>numar_masini;
   for(int i=0;i<numar_masini;i++)
   {
       masini[i+numar_total_masini]=new Spalare_Obisnuita;
       is>>*(masini[i+numar_total_masini]);
       masini[i+numar_total_masini]->set_id();
   }
   numar_total_masini+=numar_masini;


   cout<<"Numarul masinilor de spalat special: "; is>>numar_masini;
   for(int i=0;i<numar_masini;i++)
   {
       masini[i+numar_total_masini]=new Spalare_Speciala;
       is>>*(masini[i+numar_total_masini]);
       masini[i+numar_total_masini]->set_id();
   }
   numar_total_masini+=numar_masini;



   cout<<"Numarul masinilor de stors: "; is>>numar_masini;
   for(int i=0;i<numar_masini;i++)
   {
       masini[i+numar_total_masini]=new Stoarcere;
       is>>*(masini[i+numar_total_masini]);
       masini[i+numar_total_masini]->set_id();
   }
   numar_total_masini+=numar_masini;



   cout<<"Numarul masinilor de uscat: "; is>>numar_masini;
   for(int i=0;i<numar_masini;i++)
   {
       masini[i+numar_total_masini]=new Uscare;
       is>>*(masini[i+numar_total_masini]);
       masini[i+numar_total_masini]->set_id();
   }
   numar_total_masini+=numar_masini;



   cout<<"Numarul masinilor de calcat: "; is>>numar_masini;
   for(int i=0;i<numar_masini;i++)
   {
       masini[i+numar_total_masini]=new Calcare;
       masini[i+numar_total_masini]->set_id();
   }
   numar_total_masini+=numar_masini;

}

void Spalatorie::afisare_masini()
{

    for(int i=0;i<numar_total_masini;i++)
    {
        cout<<*(masini[i]);
        cout<<endl;
    }

}

void Spalatorie::afisare_clienti(istream&in)
{

try{
    cout<<"\n1.Afisarea toturor clientilor\n2.Afisarea unui anume client\n";
    cout<<"Optiune :";
    int optiune;
    in>>optiune;
    switch (optiune) 
    {
        case 1: {
            try{
                for(int i=0;i<numar_clienti;i++)
                {
                    cout<<*(clienti[i]);
                    cout<<endl; 
                }
            }
            catch (const std::exception &ex)
            {
                std::cout<<ex.what();
            }
        }
        break;
        case 2: {
            try
            {
                int index_client;
                cout<<"Index Client: ";
                try 
                {
                    index_client=Input_int(in);
                    if (index_client < 0 || index_client>numar_clienti) {
                        throw std::out_of_range("Index out of range");
                    }
                    clienti[index_client]->afisare_haina();
                } 
                catch (const std::out_of_range& e) {
                    std::cerr << "Error: " << e.what() << '\n';
                }
            
            }
            catch (const std::exception &ex) {
                std::cout<<ex.what();
            }
        }
        break;
        default:
            try
            {
                cout<<"\nInput gresit! Reintroduceti :\n";
                Spalatorie::getInstance()->afisare_clienti(in);
            }
            catch (const std::exception &ex) {
                    std::cout<<ex.what();
            }
            break;
    }
   
    }
    catch (const std::exception &ex) 
    {
        std::cout <<ex.what();
    }
   
}



int Spalatorie::get_numar_total_masini(){return this->numar_total_masini;}
void Spalatorie::set_numar_total_masini(int numar){this->numar_total_masini=+numar;}
int Spalatorie::get_numar_clienti(){return this->numar_clienti;}
void Spalatorie::set_numar_client(int numar){this->numar_clienti=numar;}
void Spalatorie::set_finalizare(bool valoare){this->finalizare=valoare;}
void Spalatorie::set_timp(double timp){this->timp+=timp;}
int Spalatorie::get_timp(){return this->timp;}



void Exemplu_conversie_tip()
{
    Rochie rochie("inchis","obisnuit",30,100,13);
    Pantaloni pantaloni(rochie);//constructorul de copiere in Haina.h --> pantaloni
    cout<<pantaloni;
}

void Ajutor()
{
    std::cout<<endl;
    std::cout<<"------------------------------------Ajutor-----------------------------------\n";
    std::cout<<"| ->Tipuri de haine: rochie , pantaloni , camasa, paltoan, gececa , costum  |\n";
    std::cout<<"| ->Spalare obisnuita: rochie , pantaloni, costum , camasa                  |\n";
    std::cout<<"| ->Spalare speciala: paltoni , geaca, costum                               |\n";
    std::cout<<"| ->Stoarcere: rochie , pantaloni, costum , camasa                          |\n";
    std::cout<<"| ->Uscare: rochie , pantaloni, costum , camasa ,palton, geaca              |\n";
    std::cout<<"| ->Calcare: rochie , pantaloni, costume, camasa                            |\n";
    std::cout<<"-----------------------------------------------------------------------------\n";
    std::cout<<endl;
}

void Iesire(istream*in)
{
   std::cout<<"Doriti sa iesiti din program? Toate datele vor fi sterse! (da/nu) "<<endl;
   string optiune; *in>>optiune;
   if (optiune=="da")
   {
       std::cout<<"Programul s-a incheiat!";
       exit(1);
   }
}

void Finalizare()
{ 
    std::cout<<endl;
    std::cout<<"Se vor finaliza toate comenzile ! Spalatoria nu mai preia altele !\n";
    std::cout<<endl;
}

void Spalatorie::Meniu(istream *in)
{
    try{
        cout<<"\n-------------------\n";
        cout<<"\nTimp: "<<timp<<endl;
        cout<<"\n-------------------\n";
        cout<< "\nAlege operatie: \n1.Comanda_noua\n2.Afisare status comenzi(clienti) \n3.Finalizare\n4.Iesire\n5.Ajutor\n6.Adauga timp(0.5h)\n7*. Exemplu Conversie Tip\n";
        cout<<"Optiune :";
        int optiune;
        *in>>optiune;

        if(timp==19.5)
            cout<<"\nSe apropie ora inchiderii! Toate comenzile ar trebui finalizate!\n";


        switch (optiune) 
        {
            case 1: {
                try{
                   Spalatorie::getInstance()->adauga_comanda(*in);
                   Meniu(in);
                }catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 2: {
                try{
                   Spalatorie::getInstance()->afisare_clienti(*in);
                   Meniu(in);
                }catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 3:{
                try{
                    Spalatorie::getInstance()->set_finalizare(true);
                    Finalizare();
                    Meniu(in);
                }catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 4:{
                try{
                   Iesire(in);
                } catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 5:{
                try{
                   Ajutor();
                } catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 6:{
                try{
                    Spalatorie::getInstance()->adauga_timp();
                    Spalatorie::procesare_timp(Spalatorie::getInstance()->get_timp(),in);
                    Meniu(in);
                }catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 7:{
                try{
                    Exemplu_conversie_tip();
                    Meniu(in);
                }catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            default:
                try{
                    if(in==&cin)
                    {cout<<"\nInput gresit! Reintroduceti :\n";
                    Meniu(in);}
                    else
                    break;
                }
                catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
                break;
        }
    }
    catch (const std::exception &ex) 
    {
        std::cout <<ex.what();
    }

}



Spalatorie::Spalatorie()
{
    for (int i = 0; i < dimensiune; ++i) 
    { 
        this->haine[i] = nullptr;
        this->masini[i]=nullptr;
        this->clienti[i]=nullptr;
     }
}

Spalatorie::~Spalatorie()
{
     for (int i = 0; i < dimensiune; ++i) 
    { 
        if(haine[i]!=NULL)
            delete this->haine[i];
        haine[i]=NULL;

        if(masini[i]!=NULL)
            delete this->masini[i];
        masini[i]=NULL;

        if(clienti[i]!=NULL)
            delete this->clienti[i];
        clienti[i]=NULL;
    }

}