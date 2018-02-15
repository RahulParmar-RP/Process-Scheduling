#include  <iostream>
using namespace std;
class FCFS;
class RR;
class PRIO;
class SJF;
class ProcessScheduling
{
public:
    int n;
    int i,j;
    int bt[20],wt[20],tat[20],pr[20],p[20],at[20],rt[20];
    int pos,temp;

    float avwt=0,avtat;
    float total;//It is not a static variable


public:
    void disAvgT(float x,float y)
    {
        cout<<"\n\nAverage Waiting Time:"<<x;
        cout<<"\nAverage Turnaround Time:"<<y;
    };
    virtual void getdata(){};
    virtual void display(){};

};
int main(){return 0;}
