#include <iostream>
#include <new>
#include <utility>
#include <string.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

ifstream fin ("date.in");


struct Alf
{
    int nrS; // nr. de stari in care trece litera alf mentionata mai jos
    int *qf; // starile de tranzitie posibile
    char litera;
};

struct Tranzitie
{
    int qi; // starea initiala
    int nrL; // nr. de litere care " pleaca " din starea initiala
    Alf *alfabet;
};
void creareFunctie ( Tranzitie **D, int &nr ) // creez functia de tranzitie sub forma unui vector
{
    //cout<<"Dati nr de tranzitii posibile ale AFN: ";
    //cin >> nr;
    fin>>nr;
    if(nr==0) cout<<"AFN vid. ";

    else
    {
        int i;
    *D =new Tranzitie [nr];
     Tranzitie d;
    for( i=0; i< nr; i++)
    {
        //cout<<"Dati starea initiala a tranzitiei ( numar intreg): ";
        fin>> d.qi;

        //cout<<"Dati numarul de litere care pleaca din aceasta stare: ";
        fin>>d.nrL;
        d.alfabet= new Alf [d.nrL];
        //cout<<"Dati litera, numarul de stari si starile in care se poate trece dupa efectuarea fiecarei tranzitii: "<<endl;
        for( int j =0; j< d.nrL; j++)
        {
            //cout<<"Dati litera:";
            fin>>d.alfabet[j].litera;
            //cout<< "Dati numarul de stari in care trece: ";
            fin>>d.alfabet[j].nrS;
            d.alfabet[j].qf= new int [d.alfabet[j].nrS];
            //cout<< "Dati starile in care se face tranzitia: ";
            for( int k=0; k< d.alfabet[j].nrS ; k++ )
                fin>>d.alfabet[j].qf[k];

        }
        (*D)[i]=d;
    }
    }
}
void verificare( int stare, char *cuvant, Tranzitie *D, int nrTranzitii, int **verif, int &nrVerif, int &ok )
{
    //ok=0;
   /// if(nrTranzitii==0) ok=0;
    ///else{
    int i=0, j=0, k=0;
    //if (strlen(cuvant)==0) return stare;///?
    //else{
   while(( i< nrTranzitii )&&((D)[i].qi!=stare)) i++;
    if(i>=nrTranzitii) {//ok=0;
                           return;}
        while((j<(D)[i].nrL)&&((D)[i].alfabet[j].litera!=cuvant[0])) j++;
        if(j>=(D)[i].nrL) {//ok=0;
                           return;}
            if(strlen(cuvant)==1) {
                    ok=1;
               // cout<<endl<<"Litera ramasa in IF : "<<cuvant;
                nrVerif=(D)[i].alfabet[j].nrS;
                ///cout<<nrVerif<<endl<<"???????????";
                *verif=new int [nrVerif];
                //cout<<endl<<"Vectorul verficare: ";
                for(k=0; k<nrVerif; k++)
                    {(*verif)[k]=(D)[i].alfabet[j].qf[k];
                     //cout<<(*verif)[k];
                    }

                //return;
            }
            else{
                //cout<<"VERIFICARE CUVANT IN else :"<<cuvant<<endl;
                //ok=1;
                //cout<<"ok IN else"<<ok;
                strcpy(cuvant, cuvant+1);
                for(k=0; k< (D)[i].alfabet[j].nrS; k++)
                    verificare((D)[i].alfabet[j].qf[k],cuvant, D,nrTranzitii, verif, nrVerif, ok);
            }
            /*
            for(k=0; k<nrTranzitii; k++)
                    //{(verif)[k]=1;
                    cout<<"verficare "<<D[k].qi;//}*/
    ///}
//cout<<endl<<"WORD "<<cuvant<<" ANSWER: "<<ok<<endl;

    }

void done (char *cuvant, int &stareInitiala)
{
    int nrTranzitii, nrVerif, *verif, nrFinale, *finale, ok1=0, ok=0;
    Tranzitie *D;
    creareFunctie(&D, nrTranzitii);
    if(nrTranzitii==0) ok1=0;
    else{
     //cout<<"!!!!!!!!!!!!!!"<<endl;
    //for(int i=0; i<nrTranzitii;i++)
       // cout<<D[i].qi<<" ";
    //cout<<"Dati starea initiala a automatului: ";
    fin>>stareInitiala;
    //cout<<"Dati cuvantul: ";
    fin>>cuvant;
    if(cuvant[0]=='-'){
   // cout<<"Dati numarul de stari finale: ";
    fin>>nrFinale;
     finale=new int [nrFinale];
     //cout<<"Dati starile finale: ";
    for(int i=0; i<nrFinale; i++)
        fin>>finale[i];
    int i=0;
    while((i<nrFinale)&&(finale[i]!=stareInitiala)) i++;
    if( i< nrFinale) cout<<"Cuvantul vid este acceptat.";
    else cout<<"Cuvantul vid nu este acceptat.";

    }
    else
    {
   verificare(stareInitiala, cuvant, D, nrTranzitii, &verif, nrVerif, ok);
   //cout<<"VERIFICARE OK1  "<<ok1<<"    OK: "<<ok;
   if(ok==0) ok1=0;
   else{
    //if(nrVerif!=0) return 9;
    //cout<<"Dati numarul de stari finale: ";
    fin>>nrFinale;
     finale=new int [nrFinale];
    // cout<<"Dati starile finale: ";
    for(int i=0; i<nrFinale; i++)
        fin>>finale[i];
    int i=0;
    while(i<nrVerif){
        int j=0;
        while(j<nrFinale){
            if(finale[j]==verif[i]) ok1=1;
            j++;
        }
        i++;
    }
    }
    cout<<endl;
    if(ok1==1)
    cout<<"Cuvatul este acceptat";
    if (ok1==0) cout<<"Cuvantul nu este acceptat";
       // return 0;
    }
}}

int main()
{
    cout<<"Cuvantul vid este reprezentat ca: - "<<endl;
    int q0; //starea initiala este data in fisierul date.in
    char s[255];

    cin>>s;
    done(s, q0);
    return 0;
}


