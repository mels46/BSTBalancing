#ifndef STABLO_CPP
#define STABLO_CPP
#include "stablo.h"
#include "stablo.cpp"
#include <iostream>

template<typename Tip>
double Stablo<Tip>::randomVrijednost() {
     bool srand_called = false;
    if (!srand_called) {
        srand(static_cast<unsigned>(time(0)));
        srand_called = true;
    }
    return static_cast<double>(rand()) / RAND_MAX * 100.0;
}
template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::RotirajLijevo(Stablo<Tip>::Cvor* cvor){
    cout<<"Cvor"<<cvor->vrijednost<<", prioritet"<<cvor->prioritet<<endl;
    Cvor *prethodni=cvor->rod;
    cout<<"Prethodni: "<<prethodni->vrijednost<<", prioritet: "<<prethodni->prioritet<<endl;
    if(prethodni==nullptr)
       return cvor;
    if(prethodni->rod==nullptr){
        korijen=cvor;
        cvor->rod=nullptr;
        Cvor *lijevo = cvor->ld;
        cvor->ld=prethodni;
        prethodni->dd=nullptr;
        prethodni->rod=cvor;

        cout<<"Postavljanje korijena:"<<korijen->vrijednost<<", prioritet: "<<korijen->prioritet<<endl;
        if (lijevo != nullptr) {
            cvor->ld->dd = lijevo;
            cvor->ld->dd->rod = cvor->ld;
        }
       cout<<"Mijenjanje starog korijena sa novim korijenom"<<korijen->vrijednost<<endl;
    }else {
         cvor->rod=prethodni->rod;
         if(prethodni->rod->dd==prethodni && prethodni->ld==cvor){
            prethodni->rod->dd=cvor;
            prethodni->rod=cvor;
            Cvor *desno=cvor->dd;
            cvor->dd=prethodni;
            prethodni->ld=nullptr;
            if(desno!=nullptr){
                cvor->dd->ld=desno;
                cvor->dd->ld->rod=cvor->dd;
            }

            cout<<"desno lijevo rotacija "<<endl;
        }else{
               prethodni->rod->dd=cvor;
               prethodni->rod=cvor;
               Cvor *lijevo=cvor->ld;
               prethodni->dd=nullptr;
               cvor->ld=prethodni;

               cout<<"Premjestanje lijevog djeteta"<<endl;
               if(lijevo!=nullptr){
               cvor->ld->dd=lijevo;
               cvor->ld->dd->rod=cvor->ld;
               }
           }

    }

    cout<<"Kraj lijeve rotacije"<<endl;
    return cvor;
}

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::RotirajDesno(Stablo<Tip>::Cvor* cvor){
    cout<<"Cvor"<<cvor->vrijednost<<", prioritet:"<<cvor->prioritet<<endl;
    Cvor *prethodni=cvor->rod;
    cout<<"Prethodni: "<<prethodni->vrijednost<<", prioritet: "<<prethodni->prioritet<<endl;
    if(prethodni==nullptr)
       return cvor;
    if(prethodni->rod==nullptr){
        korijen=cvor;
        Cvor *desno = cvor->dd;
        cvor->dd=prethodni;
        prethodni->ld=nullptr;
        prethodni->rod=cvor;
        cvor->rod=nullptr;
        cout<<"Postavljanje korijena:"<<korijen->vrijednost<<", prioritet: "<<korijen->prioritet<<endl;

        if (desno != nullptr) {
            cvor->dd->ld = desno;
            cvor->dd->ld->rod = cvor->dd;
        }


        cout<<"Mijenjanje starog korijena sa novim korijenom"<<korijen->vrijednost<<endl;
     }else {
        if(prethodni->rod->ld==prethodni && prethodni->ld==cvor){
           Cvor *desno = cvor->dd;
           prethodni->rod->ld=cvor;
           cvor->dd=prethodni;
           prethodni->ld=nullptr;
           cvor->rod=prethodni->rod;
           prethodni->rod=cvor;
           if (desno != nullptr) {
            cvor->dd->ld = desno;
            cvor->dd->ld->rod = cvor->dd;
           }
      }else if(prethodni->rod->ld==prethodni && prethodni->dd==cvor){
           Cvor *lijevo=cvor->ld;
           prethodni->rod->ld=cvor;
           cvor->ld=prethodni;
           prethodni->dd=nullptr;
           cvor->rod=prethodni->rod;
           prethodni->rod=cvor;

           if(lijevo!=nullptr){
            cvor->ld->dd=lijevo;
            cvor->ld->dd->rod=cvor->ld;
           }
        }
    }
    cout<<"Kraj desne rotacije"<<endl;
    return cvor;
}
template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Find(const Tip element) const {
    Cvor *trenutni = korijen;
    while(trenutni != nullptr) {
       if(trenutni->vrijednost == element)
         return trenutni;
       if(element < trenutni->vrijednost)
            trenutni = trenutni->ld;
       else trenutni = trenutni->dd;
    }
    return nullptr;
}

template <typename Tip>
pair<typename Stablo<Tip>::Cvor*, bool> Stablo<Tip>::Insert(const Tip element) {

    Cvor *trenutni = korijen, *prethodni = nullptr;
    while(trenutni != nullptr) {
       if(trenutni->vrijednost == element)
         return {trenutni, false};
       prethodni = trenutni;
       if(element < trenutni->vrijednost)
            trenutni = trenutni->ld;
       else trenutni = trenutni->dd;
    }

    Cvor *novi = new Cvor(element,randomVrijednost(), prethodni);
    if(korijen == nullptr) {
        korijen = novi;
    }
    else {
        if(prethodni ->vrijednost < novi->vrijednost)
            prethodni->dd = novi;
        else prethodni->ld = novi;
    }
    while(novi->rod!=nullptr && novi->rod->prioritet < novi->prioritet){
       if (novi->rod->rod != nullptr) {
            if (novi->rod->rod->dd == novi->rod && novi->rod->dd == novi)
                 novi=RotirajLijevo(novi);
             else if (novi->rod->rod->ld == novi->rod && novi->rod->ld == novi)
                 novi=RotirajDesno(novi);
            else if (novi->rod->rod->dd == novi->rod && novi->rod->ld == novi)
                 novi=RotirajLijevo(novi);
            else if (novi->rod->rod->ld == novi->rod && novi->rod->dd == novi)
                 novi=RotirajDesno(novi);
       }
       else if (novi->rod->rod == nullptr && novi->rod->dd == novi)
            novi= RotirajLijevo(novi);
        else if (novi->rod->rod == nullptr && novi->rod->ld == novi)
            novi= RotirajDesno(novi);

    }
    n++;
     return {novi, true};
}

template <typename Tip>
void Stablo<Tip>::InOrder(Cvor* cvor) const {
   if(cvor == nullptr) return;
   InOrder(cvor->ld);
   cout<<cvor->vrijednost<<" ";
   InOrder(cvor->dd);
}


template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Pocetak() const {
    if(korijen == nullptr)
        return korijen;
    Cvor *trenutni = korijen;
    while(trenutni->ld != nullptr)
        trenutni = trenutni->ld;
    return trenutni;

}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Sljedbenik(Stablo<Tip>::Cvor* cvor) const {
    if(cvor->dd != nullptr) {
        Cvor *trenutni = cvor->dd;
        while(trenutni->ld != nullptr)
            trenutni = trenutni->ld;
        return trenutni;
    }

    Cvor* trenutni = cvor;

    while(trenutni->rod != nullptr) {
        if(trenutni->rod->ld == trenutni)
            return trenutni->rod;
        if(trenutni->rod->dd == trenutni)
            trenutni = trenutni->rod;
    }

    return nullptr;


}

template <typename Tip>
void Stablo<Tip>::Erase(const Tip element) {
    Cvor* cvor = Find(element);
    if(cvor == nullptr) return;

    if(cvor->ld == nullptr && cvor->dd == nullptr) { //ako je list
        if(cvor->rod == nullptr) //ako je korijen
           korijen = nullptr;
        else {
            if(cvor->rod->ld == cvor)
                cvor->rod->ld = nullptr;
            else cvor->rod->dd = nullptr;
        }

    }
    else if(cvor->ld == nullptr) { //ako nema lijevo dijete
        cvor->dd->rod = cvor->rod;
        if(cvor->rod == nullptr) //ako je korijen
           korijen = cvor->dd;
        else {
            if(cvor->rod->ld == cvor)
                cvor->rod->ld = cvor->dd;
            else cvor->rod->dd = cvor->dd;
        }
    }
    else if(cvor->dd == nullptr) { //ako nema desno dijete
        cvor->ld->rod = cvor->rod;
        if(cvor->rod == nullptr) //ako je korijen
           korijen = cvor->ld;
        else {
            if(cvor->rod->ld == cvor)
                cvor->rod->ld = cvor->ld;
            else cvor->rod->dd = cvor->ld;
        }
    }
    else { //ako ima oba djeteta
        Cvor* sljedbenik = Sljedbenik(cvor);
        sljedbenik->ld = cvor->ld;
        cvor->ld->rod = sljedbenik;
        cvor->dd->rod = cvor->rod;
        if(cvor->rod == nullptr) //ako je korijen
           korijen = cvor->dd;
        else {
            if(cvor->rod->ld == cvor)
                cvor->rod->ld = cvor->dd;
            else cvor->rod->dd = cvor->dd;
        }
         //rotacije
       while(sljedbenik->rod!=nullptr && sljedbenik->rod->prioritet < sljedbenik->prioritet){
         if (sljedbenik->rod->rod != nullptr) {
             if (sljedbenik->rod->rod->dd == sljedbenik->rod && sljedbenik->rod->dd == sljedbenik)
                 sljedbenik=RotirajLijevo(sljedbenik);
             else if (sljedbenik->rod->rod->ld == sljedbenik->rod && sljedbenik->rod->ld == sljedbenik)
                 sljedbenik=RotirajDesno(sljedbenik);
             else if (sljedbenik->rod->rod->dd == sljedbenik->rod && sljedbenik->rod->ld == sljedbenik)
                 sljedbenik=RotirajLijevo(sljedbenik);
             else if (sljedbenik->rod->rod->ld == sljedbenik->rod && sljedbenik->rod->dd == sljedbenik)
                 sljedbenik=RotirajDesno(sljedbenik);
       }
       else if (sljedbenik->rod->rod == nullptr && sljedbenik->rod->dd == sljedbenik)
            sljedbenik= RotirajLijevo(sljedbenik);
       else if (sljedbenik->rod->rod == nullptr && sljedbenik->rod->ld == sljedbenik)
            sljedbenik= RotirajDesno(sljedbenik);


    }
    }

    delete cvor;

    n--;
}

template <typename Tip>
 pair<Stablo<Tip>, Stablo<Tip>> Stablo<Tip>::Razdvajanje( Stablo<Tip> stablo ,const Tip k){
     Stablo<Tip>::Cvor* noviKorijen=((stablo.Insert(k)).first);
     noviKorijen->prioritet=stablo.randomVrijednost() + 1000;

      while(noviKorijen->rod!=nullptr && noviKorijen->rod->prioritet < noviKorijen->prioritet){
         if (noviKorijen->rod->rod != nullptr) {
             if (noviKorijen->rod->rod->dd == noviKorijen->rod && noviKorijen->rod->dd == noviKorijen)
                 noviKorijen=stablo.RotirajLijevo(noviKorijen);
             else if (noviKorijen->rod->rod->ld == noviKorijen->rod && noviKorijen->rod->ld == noviKorijen)
                 noviKorijen=stablo.RotirajDesno(noviKorijen);
             else if (noviKorijen->rod->rod->dd == noviKorijen->rod && noviKorijen->rod->ld == noviKorijen)
                 noviKorijen=stablo.RotirajLijevo(noviKorijen);
             else if (noviKorijen->rod->rod->ld == noviKorijen->rod && noviKorijen->rod->dd == noviKorijen)
                 noviKorijen=stablo.RotirajDesno(noviKorijen);
     }
       else if (noviKorijen->rod->rod == nullptr && noviKorijen->rod->dd == noviKorijen)
            noviKorijen= stablo.RotirajLijevo(noviKorijen);
       else if (noviKorijen->rod->rod == nullptr && noviKorijen->rod->ld == noviKorijen)
            noviKorijen= stablo.RotirajDesno(noviKorijen);


    }

     cout<<"Novi korijen: "<<stablo.korijen->vrijednost<<endl;


    Stablo<Tip>manje;
    Stablo<Tip>vece;
    manje.korijen=stablo.korijen->ld;
    vece.korijen=stablo.korijen->dd;
    return {manje,vece};
 }

template<typename Tip>
Stablo<Tip> Stablo<Tip>::Spajanje(Stablo<Tip> s1,Stablo<Tip> s2){
   Tip noviKorijen=(s2.korijen->vrijednost)-(s1.korijen->vrijednost);
   Stablo<Tip>novo;
   Cvor *novi=new Cvor(noviKorijen,randomVrijednost()*(-1));
   novo.korijen=novi;
   novo.korijen->ld=s1.korijen;
   novo.korijen->dd=s2.korijen;

   while(novi->rod!=nullptr && novi->rod->prioritet < novi->prioritet){
         if (novi->rod->rod != nullptr) {
             if (novi->rod->rod->dd == novi->rod && novi->rod->dd == novi)
                 novi=novo.RotirajLijevo(novi);
             else if (novi->rod->rod->ld == novi->rod && novi->rod->ld == novi)
                 novi=novo.RotirajDesno(novi);
             else if (novi->rod->rod->dd == novi->rod && novi->rod->ld == novi)
                 novi=novo.RotirajLijevo(novi);
             else if (novi->rod->rod->ld == novi->rod && novi->rod->dd == novi)
                 novi=novo.RotirajDesno(novi);
       }
       else if (novi->rod->rod == nullptr && novi->rod->dd == novi)
            novi= novo.RotirajLijevo(novi);
       else if (novi->rod->rod == nullptr && novi->rod->ld == novi)
            novi=novo.RotirajDesno(novi);


    }

   return novo;

}

template<typename Tip>
Stablo<Tip> Stablo<Tip>::unija(Stablo<Tip> s1, Stablo<Tip> s2) {
    Stablo<Tip> prvo;
    Stablo<Tip> drugo;
    Stablo<Tip> pom1=s1;
    Stablo<Tip> pom2=s2;

  if(s1.korijen!=nullptr &&s2.korijen!=nullptr){
      if (s1.korijen->prioritet > s2.korijen->prioritet) {
        pom1.korijen = s1.korijen->ld;
        prvo = unija(pom1, Razdvajanje(s2, s1.korijen->vrijednost).first);
        pom2.korijen = s1.korijen->dd;
        drugo = unija(pom2, Razdvajanje(s2, s1.korijen->vrijednost).second);
    } else {

        pom1.korijen = s2.korijen->ld;
        prvo = unija(pom1, Razdvajanje(s1, s2.korijen->vrijednost).first);
        pom2.korijen = s2.korijen->dd;
        drugo = unija(pom2, Razdvajanje(s1, s2.korijen->vrijednost).second);
    }

       return Spajanje(prvo, drugo);
    }


}
/*Funkcija unija je rekurzivna funkcija koja koristi 2 metode vremenske slozenosti O(logn).
Pošto je stablo balansirano vremenska složenost ove funkcije je O(logn *H) gdje je H visina stabla u sluèaju
kada prolazi kroz èitavu visinu stabla*/


#endif // STABLO_CPP

