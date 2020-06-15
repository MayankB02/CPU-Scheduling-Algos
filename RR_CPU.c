#include<stdio.h>
#include<stdlib.h>


struct process 
{
    int pid ; 
    int at ; 
    int bt ;
    int copy_bt ;
    int ct;
    int wt ;
    int tat ;
};

struct node
{
    struct process* data ; 
    struct node* next ; 
};

void In_Queue(struct node **start , struct process *v)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->data = v; 
    new->next = NULL ;
    if(*start == NULL)
        *start = new ;
    else
    {
        struct node *t = *start ;
        while(t->next!=NULL)
        {
            if(t->data == v || t->next->data == v)
                return;
            t = t->next;
        }
        t->next = new ;
    }
}

int IsEmpty(struct node **start)
{
    if(*start==NULL)
        return 1 ;
    return 0 ;
}


struct process* De_Queue(struct node **start)
{
    if(!IsEmpty(start))
    {
        struct node* t = *start ;
        *start = t->next ;
        return t->data;
    }
}

void display(struct process *A , int n)
{
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time");
    for(int i = 0 ; i<n ; i++)
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d" , A[i].pid, A[i].at , A[i].copy_bt, A[i].ct ,A[i].tat , A[i].wt);
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

void rr(struct node **start , struct process *A , int n , int time_quantum)
{
    int count = 0 ;
    int time = A[0].at;
    In_Queue(start , &A[0]);
    while(!IsEmpty(start))
    {
        struct process *current = De_Queue(start);
        if(((*current).bt - time_quantum) <= 0)
        {
            time = time + (*current).bt;
            (*current).bt = 0 ;
            (*current).ct = time ;
            (*current).tat = time - (*current).at;
            (*current).wt = (*current).tat - (*current).copy_bt;
            count++;
        }
        else
        {
            time = time + time_quantum;
            (*current).bt = (*current).bt - time_quantum ;
        }
        for(int i = 0 ; i < n ; i++)
        {
            if(A[i].at <= time && A[i].bt > 0 && current!=&A[i])
                In_Queue(start , &A[i]);
        }
        if((*current).bt > 0)
            In_Queue(start , current);
        if(IsEmpty(start))
        {
            for(int i = 0 ; i < n ; i++)
            {
                if(A[i].bt > 0)
                {
                    time = A[i].at;
                    In_Queue(start , &A[i]);
                    break;
                }
            }
        }
    }
}

int main()
{
    struct node *start = NULL ; 
    int n = 0 , time_quantum = 0 ;
    //Input
    printf("\nEnter the number of processes : ");
    scanf("%d" , &n);
    struct process proc[n] ;
    for(int i = 0 ; i<n ; i++)
    {
        printf("\nEnter the arrival time and the burst time for process id %d: " , (i+1));
        proc[i].pid = i+1;
        scanf("%d %d" , &proc[i].at , &proc[i].bt);
        proc[i].copy_bt = proc[i].bt;
        proc[i].ct = 0;
        proc[i].wt=0;
        proc[i].tat = 0;
    }
     printf("\nEnter the time quantum : ");
     scanf("%d" , &time_quantum);
    //struct process proc[] = {{1,0,4,4,0,0,0},{2,1,5,5,0,0,0},{3,2,2,2,0,0,0},{4,3,1,1,0,0,0},{5,4,6,6,0,0,0},{6,6,3,3,0,0,0}};
    //struct process proc[] = {{4,1,9,9,0,0,0},{5,2,2,2,0,0,0},{3,3,7,7,0,0,0},{2,4,6,6,0,0,0},{1,5,5,5,0,0,0},{6,6,3,3,0,0,0}};
    //int n = sizeof proc / sizeof proc[0];
    printf("\nInitial State");
    display(proc,n);
    rr(&start,proc,n,time_quantum);
    printf("\nAfter execution");
    display(proc,n);    
    findAvgTime(proc,n);
    return 0;
    
}
  
    

    
    




    



