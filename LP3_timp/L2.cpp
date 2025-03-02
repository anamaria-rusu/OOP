#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<limits>
#include<cmath>
#include<iomanip>
#include<typeinfo>
#include "Client.h"
#include "Haina.h" 
#include "Masina.h"
#include "Spalatorie.h"
#include "input.h"



//g++ -o L2.exe L2.cpp Masina.cpp Haina.cpp Client.cpp Spalatorie.cpp && ./L2

using namespace std;


int main()
{
    int citire=0;
    std::cout<<"Introduceti modalitatea de citire a datelor:\n";
    std::cout<<"1.Tastatura\n";
    std::cout<<"2.Fisier\n";
    std::cout<<"Alegere: ";
 
    istream *in;
    ifstream fin("./date_intrare/date1.txt");
    

    try
    {
        string s="Optiune invalida!";
        cin>>citire;
        if(citire==1)
            in=&cin;
        else if(citire==2)
            in=&fin;
        else
            throw s;
    }
    catch(string s)
    {
        in=&cin;
    }
    cout<<endl;


    
    Spalatorie::getInstance()->adaugare_masini(*in);
    //Spalatorie::getInstance()->afisare_masini();
    Spalatorie::getInstance()->Meniu(in);


    /*
     try 
     {
        // Alocare a unei cantități mari de memorie
        int* arr = new int[1000000000000000];
        // Folosirea array-ului alocat
        arr[0] = 10;
        std::cout << "Memory allocated successfully\n";
        // Eliberare memoria alocată
        delete[] arr;
    } 
    catch (const std::bad_alloc& e) {
        std::cerr << "Bad allocation caught: " << e.what() << '\n';
    }
*/

   return 0;
}
