#include<stdio.h>
#include<stdlib.h>

struct process 
{
    int pid ; 
    int at ; 
    int bt ;
    int completed ;
    int wt ;
    int tat ;
};

void display(struct process *A , int n)
{
    printf("\nProcess ID\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time");
    for(int i = 0 ; i<n ; i++)
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d" , A[i].pid, A[i].at , A[i].bt, A[i].tat , A[i].wt);
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
void hrrn(struct process *A , int n)
{
    int sum_bt = 0 ;
    for(int i = 0 ; i< n ; i++)
        sum_bt = sum_bt + A[i].bt;
    for(int time = A[0].at ; time < sum_bt;)
    {
        float hrr = -9999 ;
        float temp ;
        int loc; 
        for(int i = 0 ; i < n ; i++)
        {
            if(A[i].at <= time && A[i].completed != 1)
            {
                temp = (A[i].bt + (time - A[i].at))/A[i].bt;
                if(temp > hrr)
                {
                    hrr = temp ; 
                    loc = i;
                }
            }   
        }
        time += A[loc].bt;
        A[loc].tat = time - A[loc].at;
        A[loc].wt = A[loc].tat - A[loc].bt ;
        A[loc].completed = 1;
    }
}
int main()
{
    int n = 0 ;
    printf("\nEnter the number of processes : ");
    scanf("%d" , &n);
    int size = n;
    struct process proc[n];
    for(int i = 0 ; i<n ; i++)
    {
        printf("\nEnter the arrival time and the burst time for process id %d: " , (i+1));
        proc[i].pid = i+1;
        scanf("%d %d" , &proc[i].at , &proc[i].bt);
        proc[i].completed = 0 ;
        proc[i].wt=0;
        proc[i].tat = 0;
    }
    printf("\nInitial State");
    display(proc,n);
    hrrn(proc,n);
    printf("\nAfter execution");
    display(proc,n);    
    findAvgTime(proc,n);
    return 0;
}
  
    

    
    




    




