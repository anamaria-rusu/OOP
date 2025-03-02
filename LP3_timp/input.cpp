
#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<limits>
#include<cmath>
#include<iomanip>
#include<typeinfo>
#include "input.h"


using namespace std;

int Input_int(istream &in)
{
    //https://stackoverflow.com/questions/53451531/what-is-cin-peek-and-what-does-it-do
    int numar;
    
    while(true)
    {
        try
        {
            in>>numar;
            if(in.fail() || in.peek() != '\n' || numar<0)
                throw std::invalid_argument("Input gresit! Introduceti o valoare numerica pozitiva(int): ");
            break;
        }
        
        catch (const std::invalid_argument &e) {
            std::cerr << e.what();
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return numar;
}



double Input_double(istream &in)
{
    double numar;
    
    while(true)
    {
        try
        {
            in>>numar;
            if(in.fail() ||  numar<0)
                throw std::invalid_argument("Input gresit! Introduceti o valoare numerica pozitiva(int/double): ");
            break;
        }
        
        catch (const std::invalid_argument &e) {
            std::cerr << e.what();
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return numar;
}
