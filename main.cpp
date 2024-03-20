#include <iostream>
#include<set>
#include "stablo.h"
using namespace std;

int main() {

    Stablo<int> s;
    s.Insert(20);
    s.Insert(10);
    s.Insert(30);
    s.Insert(140);
    s.Insert(100);
    s.Insert(160);
    s.Insert(135);
    s.Insert(415);
    s.Insert(170);


    for(auto trenutni = s.Pocetak(); trenutni != nullptr; trenutni = s.Sljedbenik(trenutni))
        cout<<trenutni->vrijednost<<" ";
    cout<<endl;
    s.Erase(10);
    s.Erase(140);
    s.Erase(170);
    //s.Erase(100);
    //s.Erase(15);
    //s.Erase(0);
    //s.Erase(60);
    s.Insert(211);


    for(auto trenutni = s.Pocetak(); trenutni != nullptr; trenutni = s.Sljedbenik(trenutni))
        cout<<trenutni->vrijednost<<" ";

    auto rezultat=s.Razdvajanje(s,50);
    Stablo<int>s1=rezultat.first;
    Stablo<int>s2=rezultat.second;

     for(auto trenutni = s1.Pocetak(); trenutni != nullptr; trenutni = s1.Sljedbenik(trenutni))
        cout<<trenutni->vrijednost<<" ";
    cout<<endl;
     for(auto trenutni = s2.Pocetak(); trenutni != nullptr; trenutni = s2.Sljedbenik(trenutni))
        cout<<trenutni->vrijednost<<" ";
    cout<<endl<<"Unija:"<<endl;
    Stablo<int> unija=s1.unija(s1,s2);
    for(auto trenutni = unija.Pocetak(); trenutni != nullptr; trenutni = unija.Sljedbenik(trenutni))
        cout<<trenutni->vrijednost<<" ";


   //Stablo<int> novo=s.Spajanje(manje,vece);
   //cout<<"Korijen novog stabla "<<novo.Korijen();
   //cout<<endl;
   //cout<<"Stablo nastalo spajanjem: "<<endl;
   //for(auto trenutni = novo.Pocetak(); trenutni != nullptr; trenutni = novo.Sljedbenik(trenutni))
     //   cout<<trenutni->vrijednost<<" ";





}
