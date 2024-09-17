// Esercizio

/*
    Inserisci in un vettore VALORI i valori di N misurazioni.
    Calcola la media di questi valori e sucessivamente inserisci 
    nell'Array SCARTI la differenza in valore assoluto di ciascun 
    elemento di VALORI con la media. Calcola infine lo scarto quadratico
    medio, dato dalla radice quadrata della somma dei quadrati degli scarti
    di i-ennesimi divisa per il numero di valori considerati
*/

#include<iostream>
#include<cmath>

using namespace std;

// Prototipi
int menu();
bool carica_valori(double valori[],int &x);
void controllo_valori(int x);
void copy(double valori[],double copy_valori[],int x);
int menu_stampa();
void menu_stampa(double valori[],double scarti[],double copy_valori[],int x);
void stampa(double valori[],int x);
double media_valori(double valori[],int x);
void scarti_(double valori[],double scarti[],int x,double media);
void ordina(double copy_valori[],int x);
void ricerca(double copy_valori[],int x,double chiave);
double scarto_quadrato(double scarti[],int x);

// Colori
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

// Costanti
const int dim=100;


int main(){

    double valori[dim],copy_valori[dim], scarti[dim], media;
    bool c,c1,c2;
    int s,s1,x,sq;
    c=c1=c2=false;

    do{
        s=menu();
        switch (s){

            case 1:{
                c=carica_valori(valori,x);
                cout<<GREEN<<"Valori caricati!"<<RESET<<endl;
                copy(valori,copy_valori,x);
                break;
            }

            case 2:{
    if(!c){
        cout<<RED<<"Valori non caricati!"<<RESET<<endl;
        break;
    }
    s1 = menu_stampa();
    switch(s1){
        case 1:{
            stampa(valori, x);
            break;
        }
        case 2:{
            ordina(copy_valori, x);
            stampa(copy_valori, x);
            break;
        }
        case 3:{
            if(!c2){
                media = media_valori(valori, x);
            }
            scarti_(valori, scarti, x, media);
            stampa(scarti, x);
            break;
        }
        case 0:{
            // Torna indietro
            break;
        }
        default:{
            cout<<RED<<"Scelta non valida!"<<RESET<<endl;
            break;
        }
    }
    break;
}


            case 3:{
                if(!c){
                    cout<<RED<<"Valori non caricati!"<<RESET<<endl;
                    break;
                }
                if(!c2){
                    media=media_valori(valori,x);
                }
                cout<<GREEN<<"Media: "<<media<<RESET<<endl;
                scarti_(valori,scarti,x,media);
                break;
            }

            case 4:{
                if(!c){
                    cout<<RED<<"Valori non caricati!"<<RESET<<endl;
                    break;
                }
                sq=scarto_quadrato(scarti,x);
                cout<<"Scarto quadratico medio: "<<sq<<endl;
                break;
            }

            case 5:{
                double chiave;
                c1=true;
                if(!c){
                    cout<<RED<<"Valori non caricati!"<<RESET<<endl;
                    break;
                }
                ordina(copy_valori,x);
                cout<<"Inserisci valore da cercare: ";
                cin>>chiave;
                ricerca(copy_valori,x,chiave);
                break;
            }

            case 0:{
                cout<<GREEN<<"Arrivederci!"<<RESET<<endl;
            }

            default:{
                cout<<RED<<"Scelta non valida!"<<RESET<<endl;
                break;
            }
        }

    }while(s!=0);

    system ("pause");
    return 0;
}


// Procedure e funzioni
int menu(){
    int s;

    cout<<"\t-----Menu-----"<<endl;
    cout<<"1. Carica valori"<<endl;
    cout<<"2. Stampa valori"<<endl;
    cout<<"3. Stampa media"<<endl;
    cout<<"4. Calcola scarto quadratico medio"<<endl;
    cout<<"5. Ricerca valore"<<endl;
    cout<<"0. Esci"<<endl;

    cout<<"\nInserisci scelta: ";
    cin>>s;

    return s;
}


bool carica_valori(double valori[],int &x){

    char ris;
    int i=0;

    do{
        cout<<"Inserisci valore ["<<i+1<<"]: ";
        cin>>valori[i];

        i++;

        cout<<"Inserire un altro valore? (S/N): ";
        cin>>ris;

        ris=toupper(ris);

        controllo_valori(i+1);
    }while(ris=='S' && i<dim);

    x=i;
    return true;
}

void controllo_valori(int x){

    if(x>=dim){
        cout<<YELLOW<<"ATTENZIONE! Puoi inserire massimo altri "<<dim-x<<" valori!"<<RESET<<endl;
    }

}

void copy(double valori[],double copy_valori[],int x){
    for(int i=0;i<x;i++){
        copy_valori[i]=valori[i];
    }
}

int menu_stampa(){
    int s;

    cout<<"1. Stampa valori"<<endl;
    cout<<"2. Stampa valori in ordine"<<endl;
    cout<<"3. Stampa scarti"<<endl;
    cout<<"0. Torna indietro"<<endl;
    cout<<"\nInserisci scelta: ";

    cin>>s;
    return s;
}

void stampa(double valori[],int x){
    for(int i=0;i<x;i++){
        cout<<valori[i]<<" "<<endl;
    }
}

double media_valori(double valori[],int x){
    double media=0;
    for(int i=0;i<x;i++){
        media+=valori[i];
    }
    return media/x;
}

void scarti_(double valori[],double scarti[],int x,double media){
    for(int i=0;i<x;i++){
        scarti[i]=abs(valori[i]-media);
    }
}

void ordina(double copy_valori[],int x){
    double t;
    for(int i=0;i<x;i++){
        for(int j=i+1;j<x;j++){
            if(copy_valori[i]>copy_valori[j]){
                t=copy_valori[i];
                copy_valori[i]=copy_valori[j];
                copy_valori[j]=t;
            }
        }
    }
}

void ricerca(double copy_valori[],int x,double chiave){
    int i=0,inizio=0,fine=x-1;
    bool t=false;

    while(inizio<=fine && !t){
        i=(inizio+fine)/2;
        if(copy_valori[i]==chiave){
            t=true;
        }else if(copy_valori[i]<chiave){
            inizio=i+1;
        }else{
            fine=i-1;
        }
    }

    if(t){
        cout<<GREEN<<"Valore presente!"<<RESET<<endl;
    }else{
        cout<<RED<<"Valore assente!"<<RESET<<endl;
    }
}


double scarto_quadrato(double scarti[],int x){
    double sum=0;
    for(int i=0;i<x;i++){
        sum+=pow(scarti[i],2);
    }
    sum/=(x-1);
    return sqrt(sum);
}