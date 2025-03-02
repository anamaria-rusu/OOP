#ifndef CLIENT_H
#define CLIENT_H

#include<iostream>
#include<string>
#include<cstring>
#include "Haina.h" 

using namespace std;

class Haina;
class Client
{
private:
    int id;
    int nr_articole;
    bool status_final;
    static const int max_haine_client=20;
    Haina* haina[max_haine_client];
    bool afisat=false;

public:
    Client();
    Client(int nr_articole,const Haina& haina);
    Client(const Client& client);
    virtual ~Client();

    Client&operator=(const Client &client); 

    friend istream& operator>>(istream& is, Client& client);
    friend ostream& operator<<(ostream&os, Client& client);
    virtual istream& read(istream& is);
    virtual ostream& print(ostream&os);


    //get
    bool get_afisat();
    int get_nr_articole();
    bool get_status_final();
    Haina* getHaina(int index);


    //set
    void set_status_final(bool status_final);
    void set_id(int id);
    void set_afisat(bool afisat);


    //functii membre
    bool verificare_comanda(Client &client);


    //supraincarcare de functii
    void afisare_haina(int i);
    void afisare_haina();
   
};

#endif