#include <iostream>
#include <ios>
#include <string>
#include <algorithm>
#include <vector>
#include "message.hpp"


using namespace std;

// funkcja dzieli stringa na n mniejszych i zwraca tablice z zapisanymi w nimi message z danego stringa
message * podzial(string wiadWE, int n){
    message * tab = new message[n];
    int i =0;

    message pom;
    int dlugosc= wiadWE.length();
    int czesci= dlugosc/n;
    int start = 0;
    int reszta= dlugosc % n;

    //cout<<"Faza 1";
   if(reszta == 0){
       //cout<<"Podzielna"; 
       //spr czy wiadomosc jest podzielna na n czesci 
     while(start < dlugosc){
            pom.nr=i+1;
            pom.wiadomosc=wiadWE.substr(start, czesci); // funkcja substr zwraca stringa, ktory jest czescia argumentu od miejsca start do start + czesci
            tab[i]=pom;
            start+=czesci;
            i++;
        }
        //cout<<"Podzielna udane";
   }else{ 
        //cout<<"niepodzielna";
         //jesli nie do pierwszej czesci jest dodawane tyle znakow by reszta byla podzielna
        do//gdy wiadomosc jest niepodzielna funkcja dodaje po jednym znaku do pierwszych czesci podzielonej wiadomosci az do zniwelowania reszty z dzielenia
        {
        pom.nr=i+1;
        pom.wiadomosc=wiadWE.substr(start, (czesci+1)); 
        tab[i]=pom;
        start+=(czesci+1);
        i++;
        reszta--;
        }while(reszta);
        //cout<<"Faza2";
        while(start < dlugosc){
            pom.nr=i+1;
            pom.wiadomosc=wiadWE.substr(start, czesci); 
            tab[i]=pom;
            start+=czesci;
            i++;

        }
       // cout<<"Niepodzielna udane";
   }
    return tab;
}

string scalenie(message tab_wej[], int wielkosc_tab){
    string wynik;
    for (int i = 0; i < wielkosc_tab; i++)
    {
        wynik+=tab_wej[i].wiadomosc;
    }
    
    return wynik;
}

void sort_table(message tab_wej[], int wielkosc_tab){
    message * tab_pom = new message[wielkosc_tab];
    int nr_wiad = 1;

    for (int i = 0; i < wielkosc_tab; i++){
        int k=0;
        while (tab_wej[k].nr != nr_wiad)
        {
            k++;
        }
        tab_pom[i]=tab_wej[k];
        nr_wiad++;

    }
    for (int i = 0; i < wielkosc_tab; i++)
    {
        tab_wej[i]= tab_pom[i];
    }
    delete[] tab_pom;
}

void shuffle_table(message tab_wej[], int wielkosc_tab ){
    
    vector<message> wektor;
    for (int i = 0; i < wielkosc_tab ; i++)
    {
        wektor.push_back(tab_wej[i]);
    }

    random_shuffle(begin(wektor), end(wektor)); //funkcja do 'potasowania' elementow wektora

    for (int i = 0; i < wielkosc_tab; i++)
    {
       tab_wej[i] = wektor[i];
    }
    wektor.clear();


}

int main(){
    
    string wiadomosc_we;
    string wiadomosc_wy;
    int ilosc_czesci;
    
    cout<<"________________________________________________________________________________________________________\n"
    <<"Program rozbija wiadomosc wejsciowa na mniejsze wiadomosci. \n"
    <<"Nastepnie symuluje wyslanie tych wiadomosci w ponumerowanych paczkach. \n"
    <<"Pozniej program segreguje wiadomosci w odpowiedniej kolejnosci i scala w jedna wiadomosc wyjsciowa. \n"
    <<"Program rowniez pokazuje wszystkie etapy swojej pracy w terminalu. \n"
    <<"Wcisnij ENTER aby rozpoczac. \n";
    cin.get();

    cout<<"Wpisz wiadomosc do przeslania \n";
    getline(cin, wiadomosc_we);


    cout<<"Wpisz na ile czesci podzielic ta wiadomosc \n";
    do
    {
        cin>>ilosc_czesci;
        if (ilosc_czesci>wiadomosc_we.length()||ilosc_czesci<1)
        {
            cout<<"Podano nieprawidlowa ilosc czesci - sprobuj jescze raz:\n";
        }
        
    } while (ilosc_czesci>wiadomosc_we.length());
    
    
    message * tablica=podzial(wiadomosc_we, ilosc_czesci);

   
   

    //sprawdzenie poprawnosci zapisu na tablicy
    cout<<"Tablica przed shuffle"<<endl;
    for (int i = 0; i < ilosc_czesci; i++)
    {
        cout<<tablica[i].wiadomosc<<" nr:"<<tablica[i].nr<<endl;
    }
    
    shuffle_table(tablica, ilosc_czesci);
    cout<<"Tablica po shuffle"<<endl;
     for (int i = 0; i < ilosc_czesci; i++)
    {
        cout<<tablica[i].wiadomosc<<" nr:"<<tablica[i].nr<<endl;
    }
   
   sort_table(tablica, ilosc_czesci);
   cout<<"Tablica po sortowaniu"<<endl;
    for (int i = 0; i < ilosc_czesci; i++)
    {
        cout<<tablica[i].wiadomosc<<" nr:"<<tablica[i].nr<<endl;
    }

    wiadomosc_wy=scalenie(tablica, ilosc_czesci);
    cout<<"Wiadmosc wyjsciowa:\n"<<wiadomosc_wy<<endl;

    cout<<"Enter by zakonczyc";
    cin.get();

    delete[] tablica;

    return 0;
}