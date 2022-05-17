#include <iostream>
#include <ios>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>
#include <cstddef>
#include <fstream>
#include "movie.hpp"

using namespace std;


//zla implementacja - cos nie dziala, nie uzywane
int qs_dzielenie (movie* tab, int start, int stop){ 
    movie pivot = tab[start];//ustawienie elementu z tablicy jako pivot

    int ile_mniejszych=0;
    for( int i=start+1; i<=stop; i++){  //for zlicza ile jest mniejszych wartosci od wartosci pivot zeby ustawic go w odpowiednim miejscu
        if(tab[i].rate<=pivot.rate)
            ile_mniejszych++;
    }   
    int pv_index=start+ile_mniejszych;

    cout<<"obliczenie ile mniejszych\n";
    //zamiana miejscami pivota na obliczone miejsce
    movie pomocnicza=tab[pv_index];
    tab[pv_index]=pivot;
    tab[start]=pomocnicza;
    cout<<"zamiana pivota\n";

    //sortowanie po lewej i prawej stronie pivota(ktore sa mniejsze to na lewo i na odwrot)
    int i=start, j=stop;
    while(i<pv_index && j>pv_index){
        while(tab[i].rate<=pivot.rate){
            i++;
        }
        while(tab[j].rate>pivot.rate){
            j++;   
        }
        if(i<pv_index && j>pv_index){
            pomocnicza=tab[i];
            tab[i]=tab[j];
            tab[j]=pomocnicza;
        }
    }
    cout<<"posortowanie wzg pivota\n";
    return pv_index;
};


void quicksort(movie* tab, int start, int stop){
    if(stop <= start){
        return;
    }

    int i = start -1;
    int j = stop+1;
    float pivot = tab[(start + stop)/ 2].rate;

    while(1){
        while(pivot > tab [++i].rate);

        while(pivot < tab[--j].rate);
        if( i<= j){
            movie pom =tab[i];
            tab[i]=tab[j];
            tab[j]=pom;
        }
        else{
            break;
        }
    }

    if (j>start){
        quicksort(tab, start, j);
    }
    if (i < stop){
        quicksort(tab, i, stop);
    }
    //int p=qs_dzielenie(tab, start, stop);

    //quicksort(tab, start, p+1);

   // quicksort(tab, p+1, stop);
};

void merge_sort(movie* tab, int lewy, int srodek, int prawy){
    
    //obliczenie rozmiarow tablic pomocniczych
    int lewa_tab_rozmiar = (srodek - lewy + 1 );
    int prawa_tab_rozmiar = (prawy-srodek);
    
   
    //stworzenie tablic pomocniczych
    movie* tab_pom_lewa = new movie[lewa_tab_rozmiar];
    movie* tab_pom_prawa = new movie[prawa_tab_rozmiar];

    //cout<<"zrobienie tablic pom \n";
    //przepisanie do tablic pomocniczych
    for(int i =0; i<lewa_tab_rozmiar; i++){
        tab_pom_lewa[i].name=tab[lewy+i].name;
        tab_pom_lewa[i].rate=tab[lewy+i].rate;
        //cout<<"l"<<tab_pom_lewa[i].rate<<" ";
    }
    for(int j=0; j<prawa_tab_rozmiar; j++){
        tab_pom_prawa[j].name=tab[srodek+1+j].name;
        tab_pom_prawa[j].rate=tab[srodek+1+j].rate;
        //cout<<"r"<<tab_pom_prawa[j].rate<<" ";
    }
    //cout<<"przypisanie do tablic pom\n";
    int lewy_licz = 0;
    int prawy_licz = 0;
    int tab_miejsce = lewy;

    while (lewy_licz < lewa_tab_rozmiar && prawy_licz < prawa_tab_rozmiar){
        if(tab_pom_lewa[lewy_licz].rate <= tab_pom_prawa[prawy_licz].rate){
            tab[tab_miejsce].rate = tab_pom_lewa[lewy_licz].rate;
            tab[tab_miejsce].name = tab_pom_lewa[lewy_licz].name;
            lewy_licz++;
        }
        else{
            tab[tab_miejsce].rate = tab_pom_prawa[prawy_licz].rate;
            tab[tab_miejsce].name = tab_pom_prawa[prawy_licz].name;
            prawy_licz++;
        }    
        tab_miejsce++;
        
    }
    //cout<<"wpisanie do tablicy z tab pom\n";
    
    //przypadek gdy na prawej tab elementy sie skoncza a na lewej dalej sa
    while (lewy_licz < lewa_tab_rozmiar)
    {
        tab[tab_miejsce].rate = tab_pom_lewa[lewy_licz].rate;
        tab[tab_miejsce].name = tab_pom_lewa[lewy_licz].name;
        lewy_licz++;
        tab_miejsce++;
       // cout<<"Przypadek 1\n";
    }
    

    //przypadek gdy na lewej tab elementy sie skoncza a na prawej sa jeszcze
    while (prawy_licz < prawa_tab_rozmiar)
    {
        tab[tab_miejsce].rate = tab_pom_prawa[prawy_licz].rate;
        tab[tab_miejsce].name = tab_pom_prawa[prawy_licz].name;
        prawy_licz++;
        tab_miejsce++;
       // cout<<"przypadek 2\n";
    }
    delete[] tab_pom_lewa;
    delete[] tab_pom_prawa;
};

void mgs_dziel(movie* tab, int start, int stop){
    if(start >= stop){
       //cout<<"koniec mgs_dziel\n";
        return;
        
    }
    int sr = start + (stop - start) / 2;
    ///cout<<"srodek: "<<sr<<"\n";
    mgs_dziel(tab, start, sr);
    mgs_dziel(tab, sr+1, stop);
    merge_sort(tab, start, sr, stop);
};

void bucket_sort(movie* tab, int dlugosc){
    movie** bucket = new movie* [5]; //storzenie tablic dwuwymiarowych, dzielenie tablicy na 5 bucketow
    int pierwszy_licz = 0;
    int drugi_licz = 0;
    int trzeci_licz = 0;
    int czwarty_licz = 0;
    int piaty_licz = 0;
    //zliczanie elementow dla poszczegolnych wiader
    for(int i = 0; i< dlugosc; i++){
        if(tab[i].rate == 1 || tab[i].rate == 2){
            pierwszy_licz++;
        }
        if(tab[i].rate == 3 || tab[i].rate == 4){
            drugi_licz++;
        }
        if(tab[i].rate == 5 || tab[i].rate == 6){
            trzeci_licz++;
        }
        if(tab[i].rate == 7 || tab[i].rate == 8){
            czwarty_licz++;
        }
        if(tab[i].rate == 9 || tab[i].rate == 10){
            piaty_licz++;
        }
    }

    //tworzenie wiader o zadanym rozmiarze
    bucket[0] = new movie[pierwszy_licz];
    bucket[1] = new movie[drugi_licz];
    bucket[2] = new movie[trzeci_licz];
    bucket[3] = new movie[czwarty_licz];
    bucket[4] = new movie[piaty_licz];
    //cout<<"stworzenie kublow\n";

    //zerowanie licznikow do wpisywania do wiader
    pierwszy_licz = 0;
    drugi_licz = 0;
    trzeci_licz = 0;
    czwarty_licz = 0;
    piaty_licz = 0;
    

     for(int k = 0; k< dlugosc; k++){
        if(tab[k].rate == 1 || tab[k].rate == 2){
            bucket[0][pierwszy_licz].rate=tab[k].rate;
            bucket[0][pierwszy_licz++].name=tab[k].name;
        }
        if(tab[k].rate == 3 || tab[k].rate == 4){
            bucket[1][drugi_licz].rate=tab[k].rate;
            bucket[1][drugi_licz++].name=tab[k].name;
        }
        if(tab[k].rate == 5 || tab[k].rate == 6){
            bucket[2][trzeci_licz].rate=tab[k].rate;
            bucket[2][trzeci_licz++].name=tab[k].name;
        }
        if(tab[k].rate == 7 || tab[k].rate == 8){
            bucket[3][czwarty_licz].rate=tab[k].rate;
            bucket[3][czwarty_licz++].name=tab[k].name;
        }
        if(tab[k].rate == 9 || tab[k].rate == 10){
            bucket[4][piaty_licz].rate=tab[k].rate;
            bucket[4][piaty_licz++].name=tab[k].name;
        }
    }
    //cout<<"LOOL\n";
    //sortowania quicsort dla kazdego wiadra
    quicksort(bucket[0], 0, pierwszy_licz-1);
    quicksort(bucket[1], 0, drugi_licz-1);
    quicksort(bucket[2], 0, trzeci_licz-1);
    quicksort(bucket[3], 0, czwarty_licz-1);
    quicksort(bucket[4], 0, piaty_licz-1);
    //cout<<"posortowanie kubluw\n";

    //wpisywanie posortowanych wiader do tablicy
   // cout<<"pierwszy licz "<<pierwszy_licz<<endl; 
   // cout<<"drugi licz "<<drugi_licz<<endl; 
   // cout<<"trzeci licz "<<trzeci_licz<<endl; 
   // cout<<"czwarty licz "<<czwarty_licz<<endl;        
   // cout<<"piaty licz "<<piaty_licz<<endl;
    //cout<<bucket[0][0].rate<<endl; 
    
    int z = 0;
    int j = 0;

  
        while (pierwszy_licz >0){
            tab[j].rate = bucket[0][z].rate;
            tab[j].name = bucket[0][z].name;
            j++;
            z++;
            pierwszy_licz--;
           // cout<<"1 -1\n";
        }
        z=0;
        //cout<<"pierwszy oprozniony\n";
        while (drugi_licz >0){
            tab[j].rate = bucket[1][z].rate;
            tab[j].name = bucket[1][z].name;
            j++;
            z++;
            drugi_licz--;
        }
        z=0;
        //cout<<"2 oprozniony\n";
        while (trzeci_licz >0){
            tab[j].rate = bucket[2][z].rate;
            tab[j].name = bucket[2][z].name;
            j++;
            z++;
            trzeci_licz--;
        }
        //cout<<"3 oprozniony\n";
        //cout<<j<<endl;
        z=0;
        while (czwarty_licz >0){
            tab[j].rate = bucket[3][z].rate;
            tab[j].name = bucket[3][z].name;
            j++;
            z++;
            czwarty_licz--;
        }
        z=0;
        //cout<<"4 oprozniony\n";
        while (piaty_licz >0){
            tab[j].rate = bucket[4][z].rate;
            tab[j].name = bucket[4][z].name;
            j++;
            z++;
            piaty_licz--;
        }
       // cout<<"5 oprozniony\n";
      

    //zwolnienie pamieci tablicy
    delete[] bucket[0];
    delete[] bucket[1];
    delete[] bucket[2];
    delete[] bucket[3];
    delete[] bucket[4];
    delete[] bucket;
};


//funkcja do stworzenia pliku bez pustych ocen
//wykorzystana tylko raz
void stworz_plik(){
    string tmp;
    ifstream MyReadfile("projekt2_dane.csv");
    ofstream newplik("dane.txt");
    while(getline(MyReadfile, tmp)){
        if (tmp[tmp.length()-1] == '0'){
            newplik << tmp <<endl;    
        }
    }
    newplik.close();
    MyReadfile.close();
}

//funkcja do stworzenia tablicy z filmami i ich ocenami z pliku txt otrzymanego za pomoca funkcji stworz plik
// argument rozmiar to rozmiar tablicy jaka chcemy stworzyc
movie* stworz_tablice(int rozmiar){
    string tmp;
    ifstream MyReadFile("dane.txt");
    movie* tab = new movie[rozmiar];

    if (!MyReadFile.is_open()){
        cout<<"Blad otwarcia pliku\n";
        delete[] tab;
        exit(0);
    }
    else{
        for (int i = 0; i<rozmiar; i++){
            getline(MyReadFile, tmp);
            char buffer[1000];
            int dlugosc = tmp.length();
            size_t length = tmp.copy(buffer, 4, dlugosc - 4);
            buffer[length] = '\0';


            tmp.erase(dlugosc-4, length);

            if (buffer[0] == ','){
                char tmp_buffer[4];
                for(int i = 0; i<3; i++){
                    tmp_buffer[i]=buffer[i+1];
                }
            tmp_buffer[3]='\0';
            float rate = atof(tmp_buffer);
            tab[i].name = tmp;
            tab[i].rate = rate;
            }
            else{
                float ratio1 = atof(buffer);
                tab[i].name = tmp;
                tab[i].rate = ratio1;
            }

        }
        return tab;
    }
}

main(){
int roz;
while(1){
    cout<<"Podaj liczbe danych do posortowania\n MAX:962902; Wyjscie z programu - podaj 0\n Liczba danych do posortowania: ";
    cin>>roz;
    if(roz<=0||roz>=962902){
        break;
    }
    else{
   // stworz_plik();
    movie* tablica = new movie[7];
    tablica[0].name='a';tablica[0].rate=6;
    tablica[1].name='a';tablica[1].rate=2;
    tablica[2].name='a';tablica[2].rate=2;
    tablica[3].name='a';tablica[3].rate=4;
    tablica[4].name='a';tablica[4].rate=8;
    tablica[5].name='a';tablica[5].rate=10;
    tablica[6].name='a';tablica[6].rate=9;
    movie* tablica1 = stworz_tablice(roz);
    movie* tablica2 = stworz_tablice(roz);
    movie* tablica3 = stworz_tablice(roz);

    //for(int i =0; i <roz; i++){
    //    cout<<tablica1[i].name<<" rate:"<<tablica1[i].rate<<endl;
    //}


    //-----------ALGORYTM QUICKSORT-------------------------
    double time_start = (double)clock();

    quicksort(tablica1, 0, (roz-1));
  

    double time_end = (double)clock();
    cout<<"Algorytmowi quicksort posortowanie zajelo: "<<(time_end - time_start)/(CLOCKS_PER_SEC)<<" sekund."<<endl;
    delete[] tablica1;

    //-------------ALGORYTM BUCKETSORT-----------------------
    time_start = (double)clock();

    
    bucket_sort(tablica2, roz);
    

    time_end = (double)clock();
    cout<<"Algorytmowi bucketsort posortowanie zajelo: "<<(time_end - time_start)/(CLOCKS_PER_SEC)<<" sekund."<<endl;
    delete[] tablica2;



    //------------ALGORYTM MERGE SORT--------------------------
    time_start = (double)clock();

    
    
    mgs_dziel(tablica3, 0, roz-1);

    time_end = (double)clock();
    cout<<"Algorytmowi mergesort posortowanie zajelo: "<<(time_end - time_start)/(CLOCKS_PER_SEC)<<" sekund."<<endl;
    delete[] tablica3;
    }
}

    return 0;
};