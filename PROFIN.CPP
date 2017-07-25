#include <iostream>
#include<windows.h>
#include<cstdlib>
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

    virtual void getdata() {};
    virtual void display() {};

};

class FCFS : public ProcessScheduling
{
public:
    //int n;
    //int bt[20],wt[20],tat[20];
    //float avwt,avtat;
    //int i,j;

    //void disAvgT(float x,float y)
    //{
    //    cout<<"\n\nAverage Waiting Time:"<<x;
    //    cout<<"\nAverage Turnaround Time:"<<y;
    //};
    void getdata()
    {
        cout<<"Enter total number of processes(maximum 20):";
        cin>>n;

        cout<<"\nEnter Process Burst Time\n";
        for(i=0; i<n; i++)
        {
            cout<<"P["<<i+1<<"]:";
            cin>>bt[i];
        }

        wt[0]=0;    //waiting time for first process is 0

        //calculating waiting time
        for(i=1; i<n; i++)
        {
            wt[i]=0;
            for(j=0; j<i; j++)
                wt[i]+=bt[j];
        }
    };
    void display()
    {
        cout<<"\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time";

        //calculating turnaround time
        for(i=0; i<n; i++)
        {
            tat[i]=bt[i]+wt[i];
            avwt+=wt[i];
            avtat+=tat[i];
            cout<<"\nP["<<i+1<<"]"<<"\t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i];
        }

        avwt=avwt/i;
        avtat=avtat/i;
        disAvgT(avwt,avtat);
    };
};
class PRIO : public ProcessScheduling
{
public:
//   int i,j;
    // int n;
    //int bt[20],p[20],wt[20],tat[20],pr[20];
    // float total;//It is not a static variable
    //int pos,temp;
    // float avwt,avtat;

    // void disAvgT(float x,float y)
    //{
    //   cout<<"\n\nAverage Waiting Time:"<<x;
    //   cout<<"\nAverage Turnaround Time:"<<y;
    //};
    void getdata()
    {
        cout<<"Enter Total Number of Process:";
        cin>>n;
        cout<<"\nEnter Burst Time and Priority\n";
        for(i=0; i<n; i++)
        {
            cout<<"\nP["<<i+1<<"]\n";
            cout<<"Burst Time:";
            cin>>bt[i];
            cout<<"Priority:";
            cin>>pr[i];
            p[i]=i+1;           //contains process number
        }

        //sorting burst time, priority and process number in ascending order using selection sort
        for(i=0; i<n; i++)
        {
            pos=i;
            for(j=i+1; j<n; j++)
            {
                if(pr[j]<pr[pos])
                    pos=j;
            }

            temp=pr[i];
            pr[i]=pr[pos];
            pr[pos]=temp;

            temp=bt[i];
            bt[i]=bt[pos];
            bt[pos]=temp;

            temp=p[i];
            p[i]=p[pos];
            p[pos]=temp;
        }

//void display(){
        wt[0]=0;            //waiting time for first process is zero

        //calculate waiting time
        for(i=1; i<n; i++)
        {
            wt[i]=0;
            for(j=0; j<i; j++)
                wt[i]+=bt[j];

            total+=wt[i];
        }
    };
    void display()
    {
        avwt=total/n;      //average waiting time
        total=0;

        cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
        for(i=0; i<n; i++)
        {
            tat[i]=bt[i]+wt[i];     //calculate turnaround time
            total+=tat[i];
            cout<<"\nP["<<p[i]<<"]\t\t  "<<bt[i]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
        }

        avtat=total/n;
        disAvgT(avwt,avtat);  //average turnaround time
    };
};

class RR : public ProcessScheduling
{
public:
    //int i,j,n
    int time,remain,flag,time_quantum;
    //float avwt=0,avtat;

    //void disAvgT(float x,float y)
    //{
    //   cout<<"\n\nAverage Waiting Time:"<<x;
    //  cout<<"\nAverage Turnaround Time:"<<y;
    //};
    void getdata()
    {
        cout<<"Enter Total Process:\t ";
        cin>>n;
        remain=n;
        for(i=0; i<n; i++)
        {
            cout<<"P["<<i+1<<"]";
            cout<<"Arrival Time:";
            cin>>at[i];
            cout<<"Burst Time:";
            cin>>bt[i];
            rt[i]=bt[i];
        }
        cout<<"Enter Time Quantum:\t";
        cin>>time_quantum;

    }

    void display()
    {
        cout<<"\n\nProcess\tTurnaround Time\tWaiting Time\n\n";
        for(time=0,i=0; remain!=0;)
        {
            if(rt[i]<=time_quantum && rt[i]>0)
            {
                time+=rt[i];
                rt[i]=0;
                flag=1;
            }
            else if(rt[i]>0)
            {
                rt[i]-=time_quantum;
                time+=time_quantum;
            }
            if(rt[i]==0 && flag==1)
            {
                remain--;
                cout<<"P["<<i+1<<"]"<<"\t\t"<<time-at[i]<<"\t\t"<<time-at[i]-bt[i]<<endl;
                avwt+=time-at[i]-bt[i];
                avtat+=time-at[i];
                flag=0;
            }
            if(i==n-1)
                i=0;
            else if(at[i+1]<=time)
                i++;
            else
                i=0;
        }
        avwt=avwt/n;
        avtat=avtat/n;
        disAvgT(avwt,avtat);
    };
};

class SJF : public ProcessScheduling
{
public:
    //int bt[20],p[20],wt[20],tat[20],i,j,n,
    //int total=0,pos,temp;
    //float avwt,avtat;


    //void disAvgT(float x,float y)
    //{
    //   cout<<"\n\nAverage Waiting Time:"<<x;
    //  cout<<"\nAverage Turnaround Time:"<<y;
    //};

    void getdata()
    {

        cout<<"Enter number of process:";
        cin>>n;

        cout<<"\nEnter Burst Time:\n";
        for(i=0; i<n; i++)
        {
            cout<<"P["<<i+1<<"]";
            cin>>bt[i];
            p[i]=i+1;           //contains process number
        }

        //sorting burst time in ascending order using selection sort
        for(i=0; i<n; i++)
        {
            pos=i;
            for(j=i+1; j<n; j++)
            {
                if(bt[j]<bt[pos])
                    pos=j;
            }

            temp=bt[i];
            bt[i]=bt[pos];
            bt[pos]=temp;

            temp=p[i];
            p[i]=p[pos];
            p[pos]=temp;
        }

        wt[0]=0;            //waiting time for first process will be zero

        //calculate waiting time
        for(i=1; i<n; i++)
        {
            wt[i]=0;
            for(j=0; j<i; j++)
                wt[i]+=bt[j];

            total+=wt[i];
        }
    };
    void dislay()
    {


        avwt=(float)total/n;      //average waiting time
        total=0;

        cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
        for(i=0; i<n; i++)
        {
            tat[i]=bt[i]+wt[i];     //calculate turnaround time
            total+=tat[i];
            cout<<"\np"<<p[i]<<"\t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t\t"<<tat[i];
        }

        avtat=(float)total/n;
        disAvgT(avwt,avtat);    //average turnaround time
    };

};


int main ()
{
    FCFS f;
    PRIO pr;
    RR rr;
    SJF sj;
    int choice;


    system("cls");
    cout << "Types of Processes:\n1)FCFS\n2)Priority Scheduling \n3)Round Robin\n4)Shortest Job First";
    cout << "\nEnter Your Choice:";
    cin  >> choice;

    switch(choice)
    {


    case 1:
        f.getdata();
        f.display();
        break;
    case 2:
        pr.getdata();
        pr.display();


        break;
    case 3:
        rr.getdata();
        rr.display();

        break;
    case 4:
        sj.getdata();
        sj.dislay();
        break;

    default :
        cout << "Invalid Choice!! " << endl;
    }

    cout << "\nYour Choice was " << choice << endl;

    return 0;
}
