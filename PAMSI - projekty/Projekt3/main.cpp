#include <iostream>
#include <ios>
#include <string>
#include <algorithm>
#include <vector>
#define MAX_DEPTH  9;
using namespace std;

struct ruch {
    int wiersz; 
    int kolumna;
    int wynik;
};

void usun_plansze(int rozmiar, char** plansza){
    for(int i = 0; i< rozmiar; i++){
        delete[] plansza[i];
    }
    delete[] plansza;
    plansza=nullptr;
}

void zapisz_do_planszy(int wiersz, int kol,char znak, char** plansza){
    plansza[wiersz][kol] = znak;
}

char** stworz_plansze(int rozmiar){

    char** plansza = new char*[rozmiar];

    for (int i = 0; i < rozmiar; i++){
        plansza[i]=new char[rozmiar];
    }

    return plansza;
}

void wyswietl_plansze(int rozmiar, char** plansza){
    cout<<endl;
    for (int i = 0; i < rozmiar; i++){
        for (int l = 0; l < rozmiar; l++){
            cout<<plansza[i][l]<<"|";
        }
        cout<<"\n";
        for (int x = 0; x < rozmiar; x++){
            cout<<"- ";
        }
        cout<<"\n";
    }
    


}
bool czy_puste(int wiersz, int kol, char** plansza){
    if (plansza[wiersz][kol]==' '){
        return true;
    }
    else { 
        cout<<"Miejsce zajete\n"; 
        return false;
    }
}


 void wpisz_do_planszy(char znak, int rozmiar,  char** plansza){
     int wiersz, kol;

     do{
        cout<<"Wiersz: ";
        cin>>wiersz;
        while(wiersz>rozmiar || wiersz<0){
             cout<<"\nBledny wiersz podaj inny: ";
            cin>>wiersz;
        }

        cout<<"Kolumna: ";
        cin>>kol;
        while(kol>rozmiar || kol<0){
             cout<<"\nBledna kolumna podaj inna: ";
            cin>>wiersz;
        }

    }while(!czy_puste(wiersz, kol, plansza));

    zapisz_do_planszy(wiersz, kol, znak, plansza);
 }


 char sprawdz_wygrana(int rozmiar, int ilosc_win, char** plansza){
     int win = 1;
     int pom = (rozmiar-ilosc_win)+1;
    char pom_znak;

    //sprawdzanie w poziomie
    
    for (int i = 0; i < rozmiar; i++){
        for (int l = 0; l < pom; l++){
            if(plansza[i][l]!=' '){
                pom_znak = plansza[i][l];
                for(int x = 1; x < ilosc_win; x++){
                    if(plansza[i][l+x]==pom_znak){
                        win++;
                        if(win==ilosc_win){
                           return pom_znak;
                        }
                    }
                }   
            }
        }
        win=1;
    }
    
     win = 1;
    

    //sprawdzenie w pionie


    for (int i = 0; i < rozmiar; i++){
        for (int l = 0; l < pom; l++){
            if(plansza[l][i]!=' '){
                pom_znak = plansza[l][i];
                for(int x = 1; x < ilosc_win; x++){
                    if(plansza[l+x][i]==pom_znak){
                        win++;
                        if(win==ilosc_win){
                           return pom_znak;
                        }
                    }
                }   
            }
        }
        win=1;
    }
    
    win = 1;

    //sprawdzenie ukos "\" //
    for (int i = 0; i < pom; i++){
        for (int l = 0; l < pom; l++){
            if(plansza[i][l]!=' '){
                pom_znak = plansza[i][l];
                for(int x = 1; x < ilosc_win; x++){
                    if(plansza[i+x][l+x]==pom_znak){
                        win++;
                        if(win==ilosc_win){
                           return pom_znak;
                        }
                    }
                }   
            }
        }
        win=1;
    }
    
     win = 1;

      //sprawdzenie ukos "/" //
    
    for (int i = 0; i < pom; i++){
        for (int l = rozmiar; l > pom; l--){
            if(plansza[i][l]!=' '){
                pom_znak = plansza[i][l];
                for(int x = 1; x < ilosc_win; x++){
                    if(plansza[i+x][l-x]==pom_znak){
                        win++;
                        if(win==ilosc_win){
                           return pom_znak;
                        }
                    }
                }   
            }
        }
        win=1;
    }
    
     win = 1;



    return 'n';
 }

int ile_wolnych(int rozmiar, char** plansza){
    int licz=0;
    for (int i = 0; i < rozmiar; i++){
        for (int l = 0; l < rozmiar; l++){
            if(plansza[i][l]==' ')
            licz++;
        }
    }
    return licz;
}

ruch * jakie_wolne(int rozmiar, char** plansza){
   int ilosc_wolnych = ile_wolnych(rozmiar, plansza);
   ruch * tab_ruchow = new ruch[ilosc_wolnych];
   int  x= 0;
   for (int i = 0; i < rozmiar; i++){
        for (int l = 0; l < rozmiar; l++){
            if(plansza[i][l]==' '){
            tab_ruchow[x].wiersz = i;
            tab_ruchow[x].kolumna = l;
            tab_ruchow[x].wynik = 0; 
            x++;
            }
        }
    }
    return tab_ruchow;
}

char** przepisz_tablice(int rozmiar, char** plansza){

    char** nowa_plansza;
    nowa_plansza = stworz_plansze(rozmiar);
    for (int i = 0; i < rozmiar; i++){
        for (int l = 0; l < rozmiar; l++){
            nowa_plansza[i][l] = plansza[i][l];
        }     
    }  
    return nowa_plansza;
}   

ruch minimax(int ilosc_win, int rozmiar,int depth,  int alpha, int beta, bool gracz,char marker, char** plansza){

    //cout<<"MINIMAX START ";
    char pmarker;
    int best_score;
    if(marker == 'x'){
        pmarker = 'o';
    }
    if(marker == 'o'){
        pmarker = 'x';
    }

    //int depth =(rozmiar*rozmiar) - ile_wolnych(rozmiar, plansza);

     // cout<<depth<<" Ile wolnych:"<<ile_wolnych(rozmiar, plansza)<<" "; 

    ruch best_move;
    best_move.kolumna = -1;
    best_move.wiersz = -1;
    if(gracz){
        best_score = -10000;
    }
    else{
        best_score = 10000;
    }
   // cout<<"DEKLARACJA BEST_MOVE ";

    if ((ile_wolnych(rozmiar, plansza) == 0) || sprawdz_wygrana(rozmiar, ilosc_win, plansza)!='n' || depth >= 9  ){
        //cout<<"KONIEC ";
        if(sprawdz_wygrana(rozmiar, ilosc_win, plansza)==marker)
        best_score=  100;
        if((sprawdz_wygrana(rozmiar, ilosc_win, plansza)!=marker) && (sprawdz_wygrana(rozmiar, ilosc_win, plansza)!='n'))
        best_score= -100;
        if(sprawdz_wygrana(rozmiar, ilosc_win, plansza)=='n')
        best_score= 0;
        
        best_move.wynik = best_score;
        return best_move;
    }
    //cout<<"MIN/MAX ";
    ruch* tab_wolnych_ruchow;
   
    tab_wolnych_ruchow = jakie_wolne(rozmiar, plansza);
    
    for(int i =0; i< ile_wolnych(rozmiar,plansza); i++){
        ruch curr_move = tab_wolnych_ruchow[i];
        
        zapisz_do_planszy(curr_move.wiersz, curr_move.kolumna, marker, plansza);

        if(gracz){
            int score = minimax(ilosc_win, rozmiar,depth+1,  alpha, beta, false, pmarker, plansza).wynik;// + ile_wolnych(rozmiar, plansza);
            //score-=depth;
            if(best_score < (score - 10*depth )){
                best_score = score - 10*depth;
                best_move = curr_move;

                alpha = max(alpha, best_score);
                zapisz_do_planszy(curr_move.wiersz, curr_move.kolumna, ' ', plansza);
                if(beta <= alpha){
                    break;
                }
            }
        }
        else{
            int score = minimax(ilosc_win, rozmiar,depth+1, alpha, beta, true, marker, plansza).wynik;// - ile_wolnych(rozmiar, plansza);
            //score+=depth;
            if(best_score > (score +10*depth)){
                best_score = score + 10*depth  ;
                best_move = curr_move;

                beta = min(beta, best_score);
                zapisz_do_planszy(curr_move.wiersz, curr_move.kolumna, ' ', plansza);
                if(beta <= alpha){
                    break;
                }
            }
        }
        zapisz_do_planszy(curr_move.wiersz, curr_move.kolumna, ' ', plansza);
    }
    best_move.wynik = best_score;
    return best_move;

   
   /* 
    char** temp_plansza;
    temp_plansza = przepisz_tablice(rozmiar, plansza);
    ruch move, curr_move;
    

    //cout<<"DEKLARACJA TABLIC ";
    //MAX
    if(gracz){
       // cout<<"MAXX ";
        //best_move.wynik = -10000;
        for (int i = 0; i < depth; i++){
            zapisz_do_planszy(tab_wolnych_ruchow[i].wiersz, tab_wolnych_ruchow[i].kolumna, pmarker, temp_plansza);
            move = minimax(ilosc_win, rozmiar, alpha, beta, false, pmarker, temp_plansza);
            if(best_score < move.wynik){
                best_move.wiersz= tab_wolnych_ruchow[i].wiersz;
                best_move.kolumna= tab_wolnych_ruchow[i].kolumna;
                best_score= move.wynik - depth;
            }
            alpha = max(best_score, alpha);
            if(beta<= alpha)
                break;
           
        }
         return   best_move;
    }
    //MIN
    else{
       // cout<<"MIN ";
        int best_score = 10000;
        for(int i = 0; i < depth; i++){
            zapisz_do_planszy(tab_wolnych_ruchow[i].wiersz, tab_wolnych_ruchow[i].kolumna, pmarker, temp_plansza);
            move = minimax(ilosc_win, rozmiar, alpha, beta, true, marker, temp_plansza);
            if(move.wynik < best_move.wynik){
                best_move.wiersz= tab_wolnych_ruchow[i].wiersz;
                best_move.kolumna= tab_wolnych_ruchow[i].kolumna;
                best_score = move.wynik + depth;
            }
            beta = min(best_score, beta);
            if(beta<= alpha)
                break;
           
        }
         return   best_move;
    }

    delete[] tab_wolnych_ruchow;
    usun_plansze(rozmiar, temp_plansza);
*/  
    delete[] tab_wolnych_ruchow;
}

void multiplayer(int rozmiar, int ilosc_wygranych){
    char** mapa = stworz_plansze(rozmiar);
    char znak='o';
    ruch AImove;

    for (int i = 0; i < rozmiar; i++){
        for (int l = 0; l < rozmiar; l++){
            zapisz_do_planszy(i, l, ' ', mapa);
        }
    }

    for (int i = 0; i < (rozmiar*rozmiar); i++){
        if(i%2==0){
            znak='o';
        }
        else{
            znak='x';
        }
        wyswietl_plansze(rozmiar, mapa);
        cout<<"TURA GRACZA: "<<znak<<"\n";
        wpisz_do_planszy(znak, rozmiar, mapa);
        if(sprawdz_wygrana(rozmiar, ilosc_wygranych, mapa)=='x'){
            cout<<"Wygral x!\n";
        break;
        }
        if(sprawdz_wygrana(rozmiar, ilosc_wygranych, mapa)=='o'){
        cout<<"Wygral o!\n";   
        break;
        }
    }

    if(sprawdz_wygrana(rozmiar, ilosc_wygranych, mapa)=='n'){
        cout<<"REMIS!\n";
    }
     wyswietl_plansze(rozmiar, mapa);

    usun_plansze(rozmiar, mapa);

}
void singleplayer(int rozmiar, int ilosc_wygranych){
    char** mapa = stworz_plansze(rozmiar);
    char znak='o';
    ruch AImove;

    for (int i = 0; i < rozmiar; i++){
        for (int l = 0; l < rozmiar; l++){
            zapisz_do_planszy(i, l, ' ', mapa);
        }
    }

    cout<<"Wybierasz O(1) czy X(2): ";
    int wybor_gracza;
    cin>>wybor_gracza;
    cout<<endl;
    while (wybor_gracza!=1 && wybor_gracza!=2){
        cout<<"Zly wybor, wybierz O(1) lub X(2): ";
        cin>>wybor_gracza;
        cout<<endl;
    }


    if(wybor_gracza==1){
        for (int i = 0; i < (rozmiar*rozmiar); i++){
            if(i%2==0){
                znak='o';
            }
            else{
                znak='x';
            }   

            wyswietl_plansze(rozmiar, mapa);
            cout<<"TURA GRACZA: "<<znak<<"\n";
            if(i%2==0){
                wpisz_do_planszy(znak, rozmiar, mapa);
            }
            else{
                AImove = minimax(ilosc_wygranych, rozmiar,0 , -10000, 10000, true, znak, mapa);
                zapisz_do_planszy(AImove.wiersz, AImove.kolumna, znak, mapa);
            }
            
            if(sprawdz_wygrana(rozmiar, ilosc_wygranych, mapa)=='x'){
                cout<<"Wygral x!\n";
                break;
            }
            if(sprawdz_wygrana(rozmiar, ilosc_wygranych, mapa)=='o'){
                cout<<"Wygral o!\n";   
            break;


            }
        }

            if(sprawdz_wygrana(rozmiar, ilosc_wygranych, mapa)=='n'){
                cout<<"REMIS!\n";
            }
    wyswietl_plansze(rozmiar, mapa);

    usun_plansze(rozmiar, mapa);
    }
    
    else{
        for (int i = 0; i < (rozmiar*rozmiar); i++){
            if(i%2==0){
                znak='o';
            }
            else{
                znak='x';
            }   

            wyswietl_plansze(rozmiar, mapa);
            cout<<"TURA GRACZA: "<<znak<<"\n";
            if(i%2==0){
                //cout<<"TURA KOMPA";
                AImove = minimax(ilosc_wygranych, rozmiar,0,  -10000, 10000, true, znak, mapa); 
                //cout<<"POLE KOMPA: "<<AImove.wiersz<<" "<<AImove.kolumna<<" "<<AImove.wynik;
                zapisz_do_planszy(AImove.wiersz, AImove.kolumna, znak, mapa);
            }
            else{
                wpisz_do_planszy(znak, rozmiar, mapa);
                
            }
            
            if(sprawdz_wygrana(rozmiar, ilosc_wygranych, mapa)=='x'){
                cout<<"Wygral x!\n";
                break;
            }
            if(sprawdz_wygrana(rozmiar, ilosc_wygranych, mapa)=='o'){
                cout<<"Wygral o!\n";   
            break;


            }
        }

            if(sprawdz_wygrana(rozmiar, ilosc_wygranych, mapa)=='n'){
                cout<<"REMIS!\n";
            }
    wyswietl_plansze(rozmiar, mapa);

    usun_plansze(rozmiar, mapa);

    }
}

   

int main(){
    int roz, wygrane, wybor_gry;
    
    cout<<"Podaj rozmiar pola (X na X)\nMin 3 Max 10\nX = ";
    cin>>roz;

    while (roz<3 || roz>10){
        cout<<"\nZly rozmiar pola, podaj inny rozmiar\nX = ";
        cin>>roz;
    }

    cout<<"Podaj ilosc pol do wygranej\n(Min 3 Max "<<roz<<") :";
    cin>>wygrane;

    while (wygrane<3 || wygrane>roz){
        cout<<"\nZla ilosc, podaj poprawna: ";
        cin>>wygrane;
    }


    cout<<"MULTIPLAYER - 1\nSINGLEPLAYER - 2\nWYBOR: ";
    cin>>wybor_gry;
    cout<<endl;
    while (wybor_gry!=1&&wybor_gry!=2){
        cout<<"Zly wybor trybu gry, podaj poprawny (1 lub 2): ";
        cin>>wybor_gry;
        cout<<endl;
    }
    
    if (wybor_gry ==1 ){
        multiplayer(roz, wygrane);
    }
    else{
        singleplayer(roz, wygrane);
    }
    
    
  
    return 0;
}