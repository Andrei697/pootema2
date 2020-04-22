#include <iostream>
#include <vector>
using namespace std;

class sala
{
private:

    int total,capacitate,proiector,mese,scena;
    int *cmese;
public:
    sala()
    {
        total=0;
        capacitate=0;
        proiector=0;
        mese=0;
        scena=0;
   }
    sala(const int tot, const int capacitate, const int proiector,const int mese,const int *cm)
    {
        total=tot;
        this->capacitate=capacitate;
        this->proiector=proiector;
        this->mese=mese;
        if  (mese!=0)
            scena=0;
        else
            scena=1;
        cmese=new int[mese+1];
        for (int i=1; i<=mese; i++)
            cmese[i]=cm[i];

    }
    void operator=(int *cm)
    {
        for (int i=1; i<=mese; i++)
            cmese[i]=cm[i];
    }
    void operator=(const sala sala2)
    {
        total=sala2.total;
        this->capacitate=sala2.capacitate;
        this->proiector=sala2.proiector;
        this->mese=sala2.mese;
        if  (mese!=0)
            scena=0;
        else
            scena=1;
    }
    ~sala()
    {
        total=0;
        capacitate=0;
        proiector=0;
        mese=0;
        scena=0;
        //delete[] cmese;
    }
    void set_parametri(const int tot, const int capacitate, const int proiector,const int mese,const int *cm)
    {
        total=tot;
        this->capacitate=capacitate;
        this->proiector=proiector;
        this->mese=mese;
        if  (mese!=0)
            scena=0;
        else
            scena=1;
        cmese=new int[mese+1];
        for (int i=1; i<=mese; i++)
            cmese[i]=cm[i];

    }


    friend class hotel;



};
class restaurant
{
private:
    int capacitate;
public:
    restaurant()
    {
        capacitate=0;
    }
    restaurant(int cap)
    {
        capacitate=cap;
    }
    ~restaurant()
    {
        capacitate=0;
    }

};
class camere
{
private:
    int nr;
public:
    camere()
    {
        nr=0;
    }
    camere(int numar)
    {
        try{
        if (numar<0)
            {throw numar;}}
        catch(int x)
        {
            cout<<"Nu poti avea mai putin de 1 camera";
            return;
        }

        nr=numar;
    }
    camere(const camere &obj)
    {
        nr=obj.nr;
    }
    ~camere()
    {
        nr=0;
    }
    void operator+(const int cv)
    {
        nr+=cv;
    }
    void operator=(const camere altcv)
    {
        nr=altcv.nr;
    }

    friend class hotel;

};

class apt
{
private:
    int nr;
public:
    apt()
    {
        nr=0;
    }
    apt(int numar)
    {
        try{
        if (numar<0)
            {throw numar;}}
        catch(int x)
        {
            cout<<"Nu poti avea mai putin de 1 apartament";
            return;
        }
        nr=numar;
    }
    apt(const apt &obj)
    {
        nr=obj.nr;
    }
    ~apt()
    {
        nr=0;
    }
    void operator+(const int cv)
    {
        nr=nr+cv;
    }

    friend class hotel;

};

class hotel
{
private:
    camere came;
    int **cam;
    apt apartam;
    int **apar;
    sala sali[100];
    int **sal;
    restaurant rest;
    int restaur;
    //double **v;
public:
    friend class client;
    hotel()
    {
        came=0;
        apartam=0;
        rest=0;
    }
    hotel(const camere c, const apt a, const sala s2[3], const restaurant r)
    {
        came=c;
        apartam=a;
        for (int i=1; i<=10; i++)
            sali[i]=s2[i];

        rest=r;
        try{

        cam=new int *[came.nr+1];
        for (int i=1; i<=came.nr; i++)
            cam[i]=new int[365];
        for(int i=1; i<=came.nr; i++)
            for (int j=1; j<=365; j++)
                cam[i][j]=0;

        apar=new int*[apartam.nr+1];
        for (int i=1; i<=apartam.nr; i++)
            apar[i]=new int[365];
        for (int i=1; i<=apartam.nr; i++)
            for(int j=1; j<=365; j++)
                apar[i][j]=0;

        sal=new int * [11];
        for (int i=1; i<=11; i++)
            sal[i]=new int [365];
        for (int i=1; i<=11; i++)
            for(int j=1; j<=365; j++)
                sal[i][j]=0;
        }
        catch(bad_alloc&)
        {
            cout<<"Alocare deficitara a memoriei";
        }
        restaur=0;

    }
    ~hotel()
    {
        came=0;
        apartam=0;
        rest=0;

    }
    void cerere(const int r, const int s, const int scen, const int pers, const int sedere)
    {
        int minc[100]= {366},minzc[366]= {366},mina[100]= {366},minza[366]= {366},k=1,maxim=0,p, mintot[20],mintip[20]= {0}, minim=365,salaocup=2;
        if (pers>came.nr*2+apartam.nr*4)
            {cout<<"locuri insuficiente";
            return;}
        for (int i=1; i<=came.nr; i++)
        {
            minc[k]=i;
            for (int j=1; j<=365; j++)
                if (cam[i][j]==0)
                {
                    minc[k]=i;
                    minzc[k]=j;
                    k++;
                    break;
                }
        }
        int y;
        int ji;
        for (y=1; y<=came.nr+1; y++)
            for (ji=y; ji<=came.nr; ji++)
                if (minzc[y]>minzc[ji])
                {
                    int aux=minc[y];
                    minc[y]=minc[ji];
                    minc[ji]=aux;


                    aux=minzc[y];
                    minzc[y]=minzc[ji];
                    minzc[ji]=aux;
                }
        k=1;
        for (int i=1; i<=apartam.nr; i++)
        {
            mina[k]=i;
            for (int j=1; j<=365; j++)
                if (apar[i][j]==0)
                {
                    mina[k]=i;
                    minza[k]=j;
                    k++;
                    break;
                }
        }
        y=1;
        ji=1;
        for (y=1; y<=apartam.nr+1; y++)
            for (ji=y; ji<=apartam.nr; ji++)
                if (minza[y]>minza[ji])
                {

                    int aux=mina[y];
                    mina[y]=mina[ji];
                    mina[ji]=aux;


                    aux=minza[y];
                    minza[y]=minza[ji];
                    minza[ji]=aux;
                }

        int indicec=1,indicea=1,indicetot=1;
        cout<<"veti fi cazati in: ";
        p=0;
        while (p<pers)
        {
            if (cam[minc[indicec]][minzc[indicec]]<apar[mina[indicea]][minza[indicea]])
            {
                mintot[indicetot]=minc[indicec];
                mintip[indicetot]=2;
                cout<<"camera: "<<minc[indicec];
                indicec++;
                indicetot++;
                p+=2;
            }
            else if (cam[minc[indicec]][minzc[indicec]]>apar[mina[indicea]][minza[indicea]])
            {
                mintot[indicetot]=mina[indicea];
                mintip[indicetot]=4;
                cout<<"apartamentul: "<<mina[indicea];
                indicea++;
                indicetot++;
                p+=4;
            }
            else
            {
                if (pers-p<=2)
                {
                    mintot[indicetot]=minc[indicec];
                    mintip[indicetot]=2;
                    cout<<"camera: "<<minc[indicec];
                    indicec++;
                    indicetot++;
                    p+=2;
                }
                if (pers-p<=4 and pers-p>2)
                {
                    mintot[indicetot]=mina[indicea];
                    mintip[indicetot]=4;
                    cout<<"apartamentul: "<<mina[indicea];
                    indicea++;
                    indicetot++;
                    p+=4;
                }
                if (pers-p>4)
                {
                    mintot[indicetot]=minc[indicec];
                    mintip[indicetot]=2;
                    cout<<"camera: "<<minc[indicec];
                    indicec++;
                    indicetot++;
                    p+=2;
                    mintot[indicetot]=mina[indicea];
                    mintip[indicetot]=4;
                    cout<<"apartamentul: "<<mina[indicea];
                    indicea++;
                    indicetot++;
                    p+=4;
                }
            }

        }
        int maximal=max(minzc[indicec-1],minza[indicea-1]);
        if(s==1)
        {
            for (int i=1; i<=sali[1].total; i++)
            {
                if(sali[i].scena==scen && sali[i].capacitate<=pers)
                {
                    for (int j=1; j<=365; j++)
                        if (sal[i][j]==0 and j<minim)
                        {
                            minim=sal[i][j];
                            salaocup=i;
                            maxim=j;
                            break;
                        }
                }

            }
        }
        cout<<"veti avea sala:";
        minim=max(maximal,maxim);
        cout<<salaocup<<endl;
        for (int i=1; i<indicetot; i++)
            for (int j=1; j<=minim+sedere; j++)
            {
                if (mintip[i]==2)
                {
                    cam[mintot[i]][j]=1;

                }
                else
                    apar[mintot[i]][j]=1;
                sal[salaocup][j]=1;


            }
        if (r==1)
            cout<<"cu mic dejun la restaurant"<<endl;
        else
            cout<<"cu mic dejun in camera"<<endl;
        cout<<"incepand cu data de: "<<minim<<"pana la data de: "<<minim+sedere<<endl;

    }




};
class client: public hotel, public camere, public apt
{
private:
    int nrclient, restaurant,sala, scena, persoane, sedere;
public:
    client()
    {
        nrclient=0;
        restaurant=0;
        sala=0;
        scena=0;
        persoane=0;
        sedere=0;
    }
    client (int nrc, int rest, int sal,int scen, int pers, int sed)
    {
        nrclient=nrc;
        restaurant=rest;
        sala=sal;
        scena=scen;
        persoane=pers;
        sedere=sed;
    }
    ~client()
    {
        nrclient=0;
        restaurant=0;
        sala=0;
        scena=0;
        persoane=0;
        sedere=0;
    }



};

int main()
{
    camere c(5);
    apt a(2);
    int fh[3]= {0,1,2};
    sala s2[3];
    restaurant r(1);
    for(int i=1; i<=2; i++)
        s2[i].set_parametri(2,10,1,0,fh);
    hotel h(c,a,s2,r);
    client cl(1,1,1,1,10,2);
    h.cerere(1,1,1,10,2);
    h.cerere(1,1,1,8,3);
    h.cerere(1,1,1,13,3);
}
