#include<stdio.h>
#include<stdlib.h>

struct process 
{
    int pid ; 
    int bt ; 
    int wt ;
    int tat ;
};

int findWaitingTime(struct process *A , int n)
{
    A[0].wt = 0 ;
    int sum = 0 ;
    for(int i = 1 ; i < n ; i++)
    {
        A[i].wt = A[i-1].wt + A[i-1].bt;
        sum = sum + A[i].wt;
    }
    return sum;
}
int findTurnAroundTime(struct process *A , int n)
{
    int sum = 0;
    for(int i = 0 ; i < n ; i++)
    {
        A[i].tat = A[i].wt + A[i].bt;
        sum = sum + A[i].tat;
    }
    return sum;
}
void display(struct process *A , int n)
{
    printf("\nProcess ID\tBurst Time\tTurnaround Time\tWaiting Time");
    for(int i = 0 ; i<n ; i++)
        printf("\n%d\t\t%d\t\t%d\t\t%d" , A[i].pid, A[i].bt , A[i].tat , A[i].wt);
}
void findAvgTime(struct process *A , int n)
{
    int tot_wt = findWaitingTime(A,n);
    int tot_tat = findTurnAroundTime(A,n);
    printf("\nAverage waiting time : %f" , (float)tot_wt/n );
    printf("\nAverage turnaround time : %f" , (float)tot_tat/n );
}

void sort_by_BurstTime(struct process *A , int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        int pos = i ;
        for(int j = i+1 ; j < n ; j++)
        {
            if(A[pos].bt > A[j].bt)
                pos = j ;
        }
        struct process v = A[pos];
        A[pos] = A[i];
        A[i] = v;
    }
}

int main()
{
    int n = 0 ;
    //Input
    printf("\nEnter the number of processes : ");
    scanf("%d" , &n);
    struct process proc[n] ;
    for(int i = 0 ; i<n ; i++)
    {
        printf("\nEnter the burst time for process id %d: " , (i+1));
        proc[i].pid = i+1;
        scanf("%d" , &proc[i].bt);
        proc[i].wt=0;
        proc[i].tat = 0;
    }
    // struct process proc[] = {{1,7,0,0},{2,5,0,0},{3,1,0,0},{4,2,0,0},{5,8,0,0}};
    // int n = sizeof proc / sizeof proc[0];
    printf("\nInitial State");
    display(proc,n);
    sort_by_BurstTime(proc,n);
    printf("\nAfter execution");
    findAvgTime(proc,n);
    display(proc,n);    
}
  
    

    
    




    




