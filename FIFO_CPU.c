#include<stdio.h>
#include<stdlib.h>

struct process 
{
    int pid ;
    int at ;
    int bt ; 
    int wt ;
    int ct ;
    int tat ;
};

int findWaitingTime(struct process *A , int n)
{
    int sum = 0 ;
    for(int i = 0 ; i < n ; i++)
    {
        A[i].wt = A[i].tat - A[i].bt ;
        sum = sum + A[i].wt;
    }
    return sum;
}
void findCompletionTime(struct process *A , int n)
{
    A[0].ct = A[0].bt;
    for(int i = 1 ; i < n ; i++)
    {
        if(A[i-1].ct < A[i].at)
        {
           A[i].ct = A[i].at + A[i].bt;
           continue;
        }
        A[i].ct = A[i-1].ct + A[i].bt;
    }
}
int findTurnAroundTime(struct process *A , int n)
{
    int sum = 0;
    for(int i = 0 ; i < n ; i++)
    {
        A[i].tat = A[i].ct - A[i].at;
        sum = sum + A[i].tat;
    }
    return sum;
}

void sort_by_ArrivalTime(struct process *A , int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        int pos = i ;
        for(int j = i+1 ; j < n ; j++)
        {
            if(A[pos].at > A[j].at)
                pos = j ;
        }
        struct process v = A[pos];
        A[pos] = A[i];
        A[i] = v;
    }
}

void findAvgTime(struct process *A , int n)
{
    findCompletionTime(A ,n);
    int tot_tat = findTurnAroundTime(A,n);
    int tot_wt = findWaitingTime(A,n);
    printf("\nAverage waiting time : %f" , (float)tot_wt/n );
    printf("\nAverage turnaround time : %f" , (float)tot_tat/n );
}

void display(struct process *A , int n)
{
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time");
    for(int i = 0 ; i<n ; i++)
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d" , A[i].pid, A[i].at , A[i].bt , A[i].ct , A[i].tat , A[i].wt);
}
int main()
{
    //int n = 0 ;
    // printf("\nEnter the number of processes : ");
    // scanf("%d" , &n);
    // struct process proc[n] ;
    // for(int i = 0 ; i<n ; i++)
    // {
    //     printf("\nEnter the arrival time and  burst time for process id %d: " , (i+1));
    //     proc[i].pid = i+1;
    //     scanf("%d %d" , &proc[i].at , &proc[i].bt);
    //     proc[i].wt=0;
    //     proc[i].ct = 0 ;
    //     proc[i].tat = 0;
    // }
    struct process proc[] = {{1,0,4,0,0,0},{2,1,3,0,0,0},{3,2,1,0,0,0},{4,3,2,0,0,0},{5,11,5,0,0,0}};
    int n = sizeof proc / sizeof proc[0];
    printf("\nInitial State");
    display(proc,n);
    sort_by_ArrivalTime(proc,n);
    printf("\nAfter execution");
    findAvgTime(proc,n);
    display(proc,n);    
}
  
