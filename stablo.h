#ifndef STABLO_H
#define STABLO_H
#include<iostream>
#include <cstdlib>
#include <ctime>

using namespace std;



template <typename Tip>
class Stablo{
 public:
     struct Cvor{
       Tip vrijednost;
       double prioritet;
       Cvor *rod, *ld,*dd;
       Cvor(Tip vrijednost,double prioritet,Cvor *rod=nullptr, Cvor* ld=nullptr,Cvor* dd=nullptr):vrijednost(vrijednost),prioritet(prioritet),rod(rod),ld(ld),dd(dd){}

     };

     private:
      int n;
      Cvor *korijen;
      double  randomVrijednost();
      void Ispis(Cvor* cvor) const;
      Cvor* RotirajDesno(Cvor*);
      Cvor* RotirajLijevo(Cvor*);
      Stablo Spajanje(Stablo s1,Stablo s2);



     public:
        Stablo():n(0),korijen(nullptr){}
        int Size()const {return n;}
        bool Empty() const {return n==0;}
        Cvor* Find(const Tip element) const;
        pair<Cvor*, bool> Insert(const Tip );
        void Erase (const Tip element);
        Cvor* Pocetak() const;
        void Ispis() const { Ispis(korijen); } //za testiranje
        static pair<Stablo, Stablo> Razdvajanje( Stablo stablo ,const Tip k);
        Cvor *Sljedbenik(Cvor * cvor) const;
        Tip Korijen(){return korijen->vrijednost;}
        Stablo unija(Stablo s1,Stablo s2);
        void InOrder(Cvor* cvor) const;




};

#include "stablo.cpp"
#endif // STABLO_H

