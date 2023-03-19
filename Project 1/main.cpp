#include <iostream>
#include<cstdlib>
#include<vector>
#include <bits/stdc++.h>
#include <cmath>
using namespace std;
ofstream out("date.out");


///INTERCHANGE----------------------------------------
void interchange(vector<int> &v,long int n)
{

        long int i,j,aux;

    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(v[i]>v[j])
                {
                   swap(v[i],v[j]);
                }

}

///RADIX----------------------------------------------
int getMax(vector<int> v, long int n)
{
    long int maxx = v[0];
    for (long int i = 1; i < n; i++)
        if (v[i] > maxx)
            maxx = v[i];
    return maxx;
}

void countSortRadix(vector<int> &v, long int n, long int exp)
{
    vector<long int> aux;
    for(long int i=0;i<v.size();i++)
        aux.push_back(0);
    long int i, digit[10];

    for(i=0;i<=9;i++)
        digit[i]=0;

    for (i = 0; i <n; i++)
        digit[(v[i] / exp) % 10]++;


    for (i = 1; i < 10; i++)
        digit[i] += digit[i - 1];


    for (i = n - 1; i >= 0; i--) {
        aux[digit[(v[i] / exp) % 10] - 1] = v[i];
        digit[(v[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        v[i] = aux[i];

}

void radixSort(vector<int> &v, long int n)
{

    long int m = getMax(v, n);

    long int exp=1;
    while(m/exp>0){

        countSortRadix(v,n,exp);
    exp*=10;
    }

}

///COUNT-----------------------------------------------
void countSort(vector<int> &v,long int n)
{
    long int i;
    long int maxx=getMax(v,n);


    ///--------------------

    vector<int> aux;
    for(long int i=0;i<maxx+1;i++)
        aux.push_back(0);

        vector<int> temp;
    for(long int i=0;i<n;i++)
        temp.push_back(0);


    for(i=0;i<n;i++)
        temp[i]=0;

    ///---------------------

    for(i=0;i<n;i++)
        aux[v[i]]++;

    for(i=1;i<maxx+1;i++)
        aux[i]+=aux[i-1];


    for(i=0;i<n;i++)
    {
        temp[aux[v[i]]]=v[i];
        aux[v[i]]--;

    }

    for(i=1;i<=n;i++)
        v[i-1]=temp[i];




}

///SHELL----------------------------------------------
void shellSort(vector<int> &v, long int n)
{
    for (long int dist=n/2; dist>0; dist/=2)
    {

        for (long int i=dist;i<n;i++)
        {
            long int temp=v[i],j;
            for (j=i; j>=dist && v[j-dist]>temp; j-=dist)
                v[j]=v[j-dist];

            v[j]=temp;
        }
    }
}

///MERGE------------------------------------------------
vector<int> a;
void mergeSort(vector<int> &v,int left,long int right)
{

    if (left<right)
{

    int mid=(left+right)/2;
    mergeSort(v,left,mid);
    mergeSort(v,mid+1,right);

    long int i=left, j=mid+1,k=0;

    while(i<=mid && j<=right)
    {
        if(v[i]<v[j])
            a[++k]=v[i++];
        else
            a[++k]=v[j++];

    }

    while(i<=mid)
        a[++k]=v[i++];

    while(j<=right)
        a[++k]=v[j++];

    for(i=left,j=1;i<=right;i++,j++)
        v[i]=a[j];
}

}

///AFISARE-----------------------------------------------
void afisare(vector<int> t,int n)
{
    for(int i=0;i<n;i++)
        cout<<t[i]<<" ";
    cout<<endl;
}

///COPY-ARRAY---------------------------------------------
void copiere(vector<int> v,vector<int> t,long int n)
{
    for(long int i=0;i<n;i++)
        t.push_back(v[i]);
}
///Validator
void valid(vector<int> v)
{
        for(int i=1;i<v.size();i++)
        if(v[i-1]>v[i])
        {
            cout<<"GRESIT"<<endl;

            break;
        }
}


int main()
{
    vector<int> v;
    vector<int> t;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    long long int n,i,x;
    int s=10000;///Numarul de date de intrare

        if(s>536500000)
    {
        cout<<"Nu duce, sorry"<<endl;
    }
    else{

 v.clear();
        t.clear();
        a.clear();

           for(i=0;i<s;i++)
            {
                ///Optional, daca vrem ca datele sa aiba un anumit numar de cifre
                /*
                x=rand()*rand()*rand()%1000000000;

                while(x<100000000)
                {
                    x=rand()*rand()%1000000000;
                }
                */

                v.push_back(x);
                a.push_back(0);
            }

            n=v.size();



            for(i=0;i<n;i++)
                t.push_back(v[i]);


            if(s<1000000)
            {
                cout<<"Interschimbare"<<endl;
                start = std::chrono::system_clock::now();
                interchange(t,n);
                end = std::chrono::system_clock::now();
                elapsed_seconds = end - start;
                //out<<elapsed_seconds.count()<<" ";
                cout<<elapsed_seconds.count()<<"seconds"<<endl;
                valid(t);
                cout<<"Gata Interschimbare"<<endl<<endl;
            }
            else
            {
                cout<<"Interschimbare.. let's not try"<<endl;
            }




            copiere(v,t,n);
            cout<<"Radix"<<endl;
            start = std::chrono::system_clock::now();
            radixSort(t,n);
            end = std::chrono::system_clock::now();
            elapsed_seconds = end - start;
            //out<<elapsed_seconds.count()<<" ";
            cout<<elapsed_seconds.count()<<"seconds"<<endl;
            valid(t);
            cout<<"Gata Radix"<<endl<<endl;



            copiere(v,t,n);
            cout<<"Shell"<<endl;
            start = std::chrono::system_clock::now();
            shellSort(t,n);
            end = std::chrono::system_clock::now();
            elapsed_seconds = end - start;
            //out<<elapsed_seconds.count()<<" ";
            cout<<elapsed_seconds.count()<<"seconds"<<endl;
            valid(t);
            cout<<"Gata shell"<<endl<<endl;



            copiere(v,t,n);
            cout<<"Count"<<endl;
            start = std::chrono::system_clock::now();
            countSort(t,n);
            end = std::chrono::system_clock::now();
            elapsed_seconds = end - start;
            //out<<elapsed_seconds.count()<<" ";
            cout<<elapsed_seconds.count()<<"seconds"<<endl;
            valid(t);
            cout<<"Gata count"<<endl<<endl;




            copiere(v,t,n);
            cout<<"Merge"<<endl;
            start = std::chrono::system_clock::now();
            mergeSort(t,0,n-1);
            end = std::chrono::system_clock::now();
            elapsed_seconds = end - start;
            //out<<elapsed_seconds.count()<<" ";
            cout<<elapsed_seconds.count()<<"seconds"<<endl;
            valid(t);
            cout<<"Gata merge"<<endl<<endl;;


            copiere(v,t,n);
            cout<<"Nativ"<<endl;
            start = std::chrono::system_clock::now();
            sort(t.begin(),t.end());
            end = std::chrono::system_clock::now();
            elapsed_seconds = end - start;
            //out<<elapsed_seconds.count()<<" ";
            cout<<elapsed_seconds.count()<<"seconds"<<endl;
            valid(t);
            cout<<"Gata nativ"<<endl;

    }

    return 0;
}
