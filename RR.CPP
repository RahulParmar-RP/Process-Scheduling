
#include<iostream>
using namespace std;

class RR
{
public:
    int i,j,n,time,remain,flag,time_quantum;
    float avwt=0,avtat;
    int at[10],bt[10],rt[10];
    void disAvgT(float x,float y)
    {
        cout<<"\n\nAverage Waiting Time:"<<x;
        cout<<"\nAverage Turnaround Time:"<<y;
    };
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
        //cout<<"\nAverage Waiting Time="<<avwt*1.0/n<<endl;
        //cout<<"Avg Turnaround Time ="<<avtat*1.0/n;
    };
};

int main()
{
    RR rr;
    rr.getdata();
    rr.display();
    return 0;
}
