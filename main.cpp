#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
using namespace std;

bool czySzukaneJestWieksza(string aktualna, string szukana);
string findSlowo(struct node* node, string szukana);

int krokomierz = 0; //usun
int licznik = 0;       // doddaj
int liczbaKrokow=0; // find
string tab[9910];

struct node
{
    string data; /// int data

    struct node *lewy;
    struct node *prawy;
    struct node *rodzic;
};

//Wskaznik na korzen
struct node *korzen = NULL;

/*
Funkcja dodawania wezla - funkcja ta przechodzi przez drzewo
w poszukiwaniu wolnego miejsca na wezel. Jesli slowo nowego wezla
jest mniejsza od aktualnego, przechodzi w lewo, w przeciwnym przypadku
przechodzimy w prawo. Gdy natkniemy sie na slowo null wstawiamy tam
nowy wezel pamietajac o przypisaniu wskaznikow.
*/

void add_node(string slowo)
{
//tworzymy wskazniki wskazujace na aktualnie rozpatrywany wezel i nowy wezel
    struct node *wskObecnyWezel = korzen;
    struct node *wskNowyWezel = new node;

//Przypisujemy wartosci do wezla
    wskNowyWezel->data = slowo;
    wskNowyWezel->lewy = NULL;
    wskNowyWezel->prawy = NULL;

//Jesli korzen ma slowo null, nowy wezel staje sie korzeniem
    if (korzen == NULL)
    {
        licznik++;
        wskNowyWezel->rodzic = NULL;
        korzen = wskNowyWezel;
        return;
    }
    else
    {

        while (wskObecnyWezel!= NULL)
        {
//slowo nowego wezla jest wieksza badz rowna od wskazywanego
            string obecny = wskObecnyWezel->data;
            string szukany = wskNowyWezel->data;
            if (czySzukaneJestWieksza(obecny, szukany))///wskObecnyWezel->data <= wskNowyWezel->data
            {
                licznik++;
//jesli po prawej jest wolne miejsce dodajemy w nie wezel
                if (wskObecnyWezel->prawy == NULL)
                {
                    licznik++;
                    wskNowyWezel->rodzic = wskObecnyWezel;
                    wskObecnyWezel->prawy = wskNowyWezel;
                    return;
                }
//w innym przypadku przechodzimy w glab drzewa
                else
                {
                    licznik++;
                    wskObecnyWezel = wskObecnyWezel->prawy;
                }
            }
//slowo nowego wezla jest mniejsza od wskazywanego
////            if (czySzukaneJestWieksza(wskObecnyWezel->data, wskNowyWezel))
            else
            {
                licznik++;
//jesli po lewej jest wolne miejsce dodajemy w nie wezel
                if (wskObecnyWezel->lewy == NULL)
                {
                    licznik++;
                    wskNowyWezel->rodzic = wskObecnyWezel;
                    wskObecnyWezel->lewy = wskNowyWezel;
                    return;
                }
//w innym przypadku przechodzimy w glab drzewa
                else
                {
                    licznik++;
                    wskObecnyWezel = wskObecnyWezel->lewy;
                }
            }
        }
    }
}

/*
Funkcja usuwania wezla - funkcja przechodzi po drzewie w poszukiwaniu
wezla o zadanej wartosci. Jesli szukana slowo jest mniejsza od wartosci
aktualnie wskazywanego wezla, przechodzi w lewo, w przeciwnym przypadku
przechodzimy w prawo. Jesli znajdziemy wezel o zadanej wartosci, usuwamy go.
W przypadku gdy posiadal jakiekolwiek dzieci, wstawiamy je w wolne miejsce.
Jesli zadana slowo nie znajduje sie w drzewie, zwracamy NULL.
*/
struct node* usunSlowo(struct node* node, string szukana)
{


    if (node == NULL)
    {
        //cout<<"node == null"<<endl;
        return node;

    }

    string aktualna = node->data;
    if ( czySzukaneJestWieksza(aktualna,szukana)) ///szukana >= node->data
    {
        krokomierz++;
        if(aktualna == szukana)
        {
            //Jeœli drzewo sk³ada sie z samego korzenia
            if (korzen->lewy == NULL && korzen->prawy == NULL)
            {
                delete(korzen);
                krokomierz++;
                //cout<<"usuwam korzen "<<endl;
                korzen = NULL;
                return NULL;
            }
//Wsuniêcie prawego syna na miejsce aktualnie wskazywanego
            if (node->lewy == NULL)
            {
                struct node *tmp = node->prawy;
                //cout<<"usuwam prawy "<<node->data<<endl;
                krokomierz++;
                delete(node);
                return tmp;
            }
//Wsuniêcie lewego syna na miejsce aktualnie wskazywanego
            else if (node->prawy == NULL)
            {
                struct node *tmp = node->lewy;
                //cout<<"usuwam lewy "<<node->data<<endl;
                krokomierz++;
                delete(node);
                return tmp;
            }

//Przypadek gdy wskazywany wêze³ ma dwóch synów
            struct node* tmp = node->prawy;

            node->data = tmp->data;
            while (tmp->lewy != NULL)
            {
                tmp = tmp->lewy;
                krokomierz++;
            }

//Znalezienie nastêpcy
            node->prawy = usunSlowo(node->prawy, tmp->data);
        }
        else
        {
            krokomierz++;
            //cout<<"ide w prawo "<<endl;
            node->prawy = usunSlowo(node->prawy, szukana);
        }

    }
    else /// szukana < obecny
    {
        krokomierz++;
        //cout<<"ide w lewo "<<endl;
        node->lewy = usunSlowo(node->lewy, szukana); //Rekurencyjne przejœcie do szukanej wartoœci
    }

    if (szukana == node->data)
    {
//Jeœli drzewo sk³ada sie z samego korzenia
        if (korzen->lewy == NULL && korzen->prawy == NULL)
        {
            krokomierz++;
            delete(korzen);
            //cout<<"usuwam korzen "<<endl;
            korzen = NULL;
            return NULL;
        }
//Wsuniêcie prawego syna na miejsce aktualnie wskazywanego
        if (node->lewy == NULL)
        {
            krokomierz++;
            struct node *tmp = node->prawy;
            //cout<<"usuwam prawy "<<node->data<<endl;
            delete(node);
            return tmp;
        }
//Wsuniêcie lewego syna na miejsce aktualnie wskazywanego
        else if (node->prawy == NULL)
        {
            krokomierz++;
            struct node *tmp = node->lewy;
            //cout<<"usuwam lewy "<<node->data<<endl;
            delete(node);
            return tmp;
        }

//Przypadek gdy wskazywany wêze³ ma dwóch synów
        struct node* tmp = node->prawy;

        node->data = tmp->data;
        while (tmp->lewy != NULL)
        {
            tmp = tmp->lewy;
            krokomierz++;
        }

//Znalezienie nastêpcy
        node->prawy = usunSlowo(node->prawy, tmp->data);
    }


    return node;
}


string findSlowo(struct node* node, string szukana)
{

    struct node*aktualny=node;
    int x = 0;

    while(aktualny!=nullptr && aktualny->data!=szukana)
    {

        if(czySzukaneJestWieksza(aktualny->data,szukana))
        {
            aktualny=aktualny->prawy;
            liczbaKrokow++;
        }
        else
        {
            aktualny=aktualny->lewy;
            liczbaKrokow++;
        }

        if(aktualny == nullptr)
        {
            x = 1;
            break;
        }

    }
    if(x==1)
    {
        string niema = "nie znaleziono";
        return niema;
    }

    // cout<<aktualny->data<<" ";
    //cout<<"liczba krokow = "<<liczbaKrokow<<endl;

    return aktualny->data;
}

bool operator!=(string a, string b)
{
    int dla=a.length();
    int dlb=b.length();
    if(dla!=dlb)
    {
        return true;
    }
    else
    {
        for(int i=0; i<dla; i++)
        {
            if(a[i]!=b[i])
            {
                return true;
            }
        }
    }
    return false;

}


/// funkcja ktora zwraca 2/1/0 w zaleznosci czy nasze slowo jest wieksze od tego we drzewie
bool czySzukaneJestWieksza(string aktualna, string szukana)
{

    if(aktualna>szukana)
    {
        //cout<<"aktualna wieksze od szukana"<<endl;
        return false;
    }
    else if(aktualna<=szukana)
    {
        //cout<<"szukana wieksze od aktualna"<<endl;
        return true;
    }
}



        int height(node* node)
        {
            int maxmaxow = 0;
            if (node == nullptr)
            {
                return 0;
            }
            else
            {
                int leftHeight = height(node->lewy);
                int rightHeight = height(node->prawy);

                if(leftHeight<rightHeight)
                {
                    //cout<<rightHeight<<endl;
                    maxmaxow=rightHeight;
                }
                else
                {
                    //cout<<leftHeight<<endl;
                    maxmaxow=leftHeight;
                }
                //cout<<"maks "<<maxmaxow<<endl;


        fstream plikZapisHeight;

        plikZapisHeight.open("plikWynikiWysokosc.txt", ios::out | ios::trunc);
        plikZapisHeight<<maxmaxow<<endl;
        plikZapisHeight.close();


                return 1 + max(leftHeight, rightHeight);
            }

        }



int main()
{


    int x=0;
    string linia1;
    ifstream plik1;
    plik1.open("slowa_do_4_poprawione.txt", ios::in | ios::app);
    ///plik1.open("cale_slowa_krzyzakow.txt", ios::in | ios::app);
    ///plik1.open("AlaOlaKosPies.txt", ios::in | ios::app);
    if(plik1.good()==false)
    {
        cout<<"Nie udalo sie otworzyc pliku!";
        exit(0);
    }
    while(getline(plik1,linia1))
    {
        x++;
    }
    cout<<"dlugosc pliku: "<<x<<endl;

    plik1.close();


    int liczDo4=0;
    int licz=0;
    int sumaLicznika=0;
    srand(time(NULL));

    node *drzewo;
    int g=0;



   int j = 100;




    for(int y=0; y<1; y++)
    {
        //drzewo = new node();

        for(int k=0; k<j; k++)
        {
            string liniaDo4;
            ifstream plikDo4;
            plikDo4.open("slowa_do_4_poprawione.txt", ios::in | ios::app);
            ///plikDo4.open("cale_slowa_krzyzakow.txt", ios::in | ios::app);
            ///plikDo4.open("AlaOlaKosPies.txt", ios::in | ios::app);
            if(plikDo4.good()==false)
            {
                cout<<"Nie udalo sie otworzyc pliku!";
                exit(0);
            }

            int wylosowanaLiczbaDla = rand()%x+1;

            //cout<<wylosowanaLiczbaDla<<endl;
            while(getline(plikDo4,liniaDo4))
            {
                if(licz==wylosowanaLiczbaDla)
                {
                    add_node(liniaDo4);
                    //tab[g]=liniaDo4;
                    //g++;
                    //cout<<"liniaDo4 -> "<<liniaDo4<<endl;
                    break;
                }
                else
                {
                    licz++;
                }
            }
            licz=0;

            plikDo4.close();
        }

        cout<<"Dodalem "<<j<<" slow"<<endl;

        licznik=0;
/*
height(korzen);

            string wynik;
            string liniaPoprawne;
            ifstream plikPoprawne;
            plikPoprawne.open("plikWynikiWysokosc.txt", ios::in | ios::app);

            if(plikPoprawne.good()==false)
            {
                cout<<"Nie udalo sie otworzyc pliku!";
                exit(0);
            }
            while(getline(plikPoprawne,liniaPoprawne))
            {
                //cout<<liniaPoprawne<<endl;
                wynik=liniaPoprawne;
            }


            plikPoprawne.close();



        fstream plikZapisPoprawneWyniki;
        ///plikZapisPoprawneWyniki.open("plikSlowaDo4Dlugosc.txt", ios::out | ios::app);
        ///plikZapisPoprawneWyniki.open("plikSlowaCale.txt", ios::out | ios::app);
        plikZapisPoprawneWyniki.open("plikSlowaPies.txt", ios::out | ios::app);
        plikZapisPoprawneWyniki<<wynik<<endl;
        plikZapisPoprawneWyniki.close();

*/








        //dodanie 10

        for(int i=0; i<10; i++)
        {
            string linia;
            ifstream plik;
            plik.open("slowa_do_4_poprawione.txt", ios::in | ios::app);
            ///plik.open("cale_slowa_krzyzakow.txt", ios::in | ios::app);
            ///plik.open("AlaOlaKosPies.txt", ios::in | ios::app);
            if(plik.good()==false)
            {
                cout<<"Nie udalo sie otworzyc pliku!";
                exit(0);
            }

            int wylosowanaLiczba = rand()%x+1;

            while(getline(plik,linia))
            {
                if(licz==wylosowanaLiczba)
                {
                    //cout<<"g"<<g<<endl;
                    //tab[g]=linia;
                    add_node(linia);
                    //g++;
                    //cout<<"linia -> "<<linia<<endl;
                    //cout<<"licz -> "<<licz<<endl;
                    cout<<"kroki = "<<licznik<<endl;
                    sumaLicznika=sumaLicznika+licznik;
                    break;
                }
                else
                {
                    licz++;
                }
            }
            licznik=0;
            licz=0;


            plik.close();
        }
        g=0;
        //cout<<sumaLicznika/10<<endl;
        cout<<"suma licznikow (dodaj) = "<<sumaLicznika<<"/10 = "<<sumaLicznika/10<<endl;
        //cout<<sumaLicznika/10<<endl;
        int srednia = sumaLicznika/10;
        sumaLicznika=0;

//
////        //usuwanie 10

        for(int i=0; i<10; i++)
        {
            string linia3;
            ifstream plik3;
            plik3.open("slowa_do_4_poprawione.txt", ios::in | ios::app);
            ///plik3.open("cale_slowa_krzyzakow.txt", ios::in | ios::app);
            ///plik3.open("AlaOlaKosPies.txt", ios::in | ios::app);
            if(plik3.good()==false)
            {
                cout<<"Nie udalo sie otworzyc pliku!";
                exit(0);
            }

            int wylosowanaLiczba = rand()%x+1;

            while(getline(plik3,linia3))
            {
                if(licz==wylosowanaLiczba)
                {
                    //cout<<"g"<<g<<endl;
                    //tab[g]=linia;
                    usunSlowo(korzen,linia3);
                    //g++;
                    //cout<<"linia -> "<<linia<<endl;
                    //cout<<"licz -> "<<licz<<endl;
                    cout<<"kroki (usun) = "<<krokomierz<<endl;
                    sumaLicznika=sumaLicznika+krokomierz;
                    break;
                }
                else
                {
                    licz++;
                }
            }
            krokomierz=0;
            licz=0;


            plik3.close();
        }
        g=0;
        //cout<<sumaLicznika/10<<endl;
        cout<<"suma licznikow (usun)= "<<sumaLicznika<<"/10 = "<<sumaLicznika/10<<endl;
        //cout<<sumaLicznika/10<<endl;
        int srednia2 = sumaLicznika/10;
        sumaLicznika=0;

//
//        // wyszukiwanie 10

        for(int i=0; i<10; i++)
        {
            string linia4;
            ifstream plik4;
            plik4.open("slowa_do_4_poprawione.txt", ios::in | ios::app);
            ///plik4.open("cale_slowa_krzyzakow.txt", ios::in | ios::app);
            ///plik4.open("AlaOlaKosPies.txt", ios::in | ios::app);
            if(plik4.good()==false)
            {
                cout<<"Nie udalo sie otworzyc pliku!";
                exit(0);
            }

            int wylosowanaLiczba = rand()%x+1;

            while(getline(plik4,linia4))
            {
                if(licz==wylosowanaLiczba)
                {
                    //cout<<"g"<<g<<endl;
                    //tab[g]=linia;
                    findSlowo(korzen,linia4);
                    //g++;
                    //cout<<"linia -> "<<linia<<endl;
                    //cout<<"licz -> "<<licz<<endl;
                    cout<<"kroki (wyszukaj) = "<<liczbaKrokow<<endl;
                    sumaLicznika=sumaLicznika+liczbaKrokow;
                    break;
                }
                else
                {
                    licz++;
                }
            }
            liczbaKrokow=0;
            licz=0;


            plik4.close();
        }
        g=0;
        //cout<<sumaLicznika/10<<endl;
        cout<<"suma licznikow (wyszukaj) = "<<sumaLicznika<<"/10 = "<<sumaLicznika/10<<endl;
        //cout<<sumaLicznika/10<<endl;
        int srednia3 = sumaLicznika/10;
        if(srednia3<1)
        {
            srednia3 = 1;
        }
        sumaLicznika=0;


        fstream plikZapisD;
        ///plikZapisD.open("plikWynikiSlowaDo4Dodanie.txt", ios::out | ios::app);
        ///plikZapisD.open("plikWynikiSlowaDodanie.txt", ios::out | ios::app);
        plikZapisD.open("plikWynikiAniaPiesDodanie.txt", ios::out | ios::app);
        plikZapisD<<srednia<<endl;
        srednia=0;
        plikZapisD.close();

        fstream plikZapisU;
        ///plikZapisU.open("plikWynikiSlowaDo4Usun.txt", ios::out | ios::app);
        ///plikZapisU.open("plikWynikiSlowaUsun.txt", ios::out | ios::app);
        plikZapisU.open("plikWynikiAniaPiesUsun.txt", ios::out | ios::app);
        plikZapisU<<srednia2<<endl;
        srednia2=0;
        plikZapisU.close();

        fstream plikZapisW;
        ///plikZapisW.open("plikWynikiSlowaDo4Wyszukaj.txt", ios::out | ios::app);
        ///plikZapisW.open("plikWynikiSlowaWyszukaj.txt", ios::out | ios::app);
        plikZapisW.open("plikWynikiAniaPiesWyszukaj.txt", ios::out | ios::app);
        plikZapisW<<srednia3<<endl;
        srednia3=0;
        plikZapisW.close();



    }



    return 0;
}

