#include<stdio.h>
#include<stdlib.h>

struct process 
{
    int pid ; 
    int at ; 
    int bt ;
    int copy_bt ;
    int wt ;
    int tat ;
};

void display(struct process *A , int n)
{
    printf("\nProcess ID\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time");
    for(int i = 0 ; i<n ; i++)
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d" , A[i].pid, A[i].at , A[i].copy_bt, A[i].tat , A[i].wt);
}
void findAvgTime(struct process *A , int n)
{
    int tot_wt = 0;
    int tot_tat = 0;
    for(int i = 0 ; i < n ; i++)
    {
        tot_wt = tot_wt + A[i].wt;
        tot_tat = tot_tat + A[i].tat;
    }
    printf("\nAverage waiting time : %f" , (float)tot_wt/n );
    printf("\nAverage turnaround time : %f" , (float)tot_tat/n );
}
void srtf(struct process *A , int n)
{
    int count = 0 ;
    int smallest ;
    for(int time = 0 ; count !=n ; time++)
    {
        smallest = n+1;
        for(int i = 0 ; i < n ; i++)
        {
            if(A[i].at <= time && A[i].bt < A[smallest].bt && A[i].bt > 0)
                smallest = i;
        }
        A[smallest].bt--;
        if(A[smallest].bt == 0)
        {
            A[smallest].tat = ( time + 1 ) - A[smallest].at;
            A[smallest].wt = A[smallest].tat - A[smallest].copy_bt;
            count++ ;
        }
    }
}
int main()
{
    int n = 0 ;
    //Input
    printf("\nEnter the number of processes : ");
    scanf("%d" , &n);
    int size = n + 1;
    struct process proc[size];
    for(int i = 0 ; i<n ; i++)
    {
        printf("\nEnter the arrival time and the burst time for process id %d: " , (i+1));
        proc[i].pid = i+1;
        scanf("%d %d" , &proc[i].at , &proc[i].bt);
        proc[i].copy_bt = proc[i].bt;
        proc[i].wt=0;
        proc[i].tat = 0;
    }
    proc[size-1].bt = 10000;
    proc[size-1].at = proc[size-1].tat = proc[size-1].wt = proc[size-1].copy_bt = proc[size-1].pid = 0;
    //struct process proc[] = {{1,0,7,7,0,0},{2,1,5,5,0,0},{3,2,3,3,0,0},{4,3,1,1,0,0},{5,4,2,2,0,0},{6,5,1,1,0,0},{0,0,10000,0,0,0}};
    //int n = sizeof proc / sizeof proc[0];
    printf("\nInitial State");
    display(proc,n);
    srtf(proc,n);
    printf("\nAfter execution");
    display(proc,n);    
    findAvgTime(proc,n);
    return 0;
}
  
    

    
    




    




