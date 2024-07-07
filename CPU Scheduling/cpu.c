#include <stdio.h>

struct process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turn_around_time;
    int completion_time;
    int priority;
    int remaining_time;
    int completed;
}proc[20],temp;

void fcfs(struct process proc[], int n)
{
   printf("\t\tFCFS\n");
   int i,sum;
   float total_waiting_time=0,total_turn_around_time=0;

   sum=proc[0].arrival_time;
   for(i=0;i<n;i++)
   {
      sum+=proc[i].burst_time;
      proc[i].completion_time=sum;

      proc[i].turn_around_time=proc[i].completion_time-proc[i].arrival_time;
      total_turn_around_time+=proc[i].turn_around_time;

      proc[i].waiting_time=proc[i].turn_around_time-proc[i].burst_time;
      total_waiting_time+=proc[i].waiting_time;
   }

   printf("Process Execution Order: ");
   for(i=0;i<n;i++)
   {
      printf("P%d ",proc[i].process_id);
   }

   printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
   for (int i = 0; i < n; i++)
   {
       printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", proc[i].process_id, proc[i].arrival_time, proc[i].burst_time, proc[i].completion_time, proc[i].turn_around_time, proc[i].waiting_time);
   }
       printf("Average waiting time: %f\n", (float)total_waiting_time/n);
       printf("Average turn around time: %f\n",(float)total_turn_around_time/n);
}

void sjf(struct process proc[], int n)
{
    printf("\t\tSJF\n");
    printf("Process Execution Order: ");
    int i,j,totalburst,total=0,completed=0,time=0;
    float total_turn_around_time=0,total_waiting_time=0;
    for(i=0;i<n;i++)
    {
        totalburst+=proc[i].burst_time;
    }

    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
             if(proc[j].arrival_time>proc[j+1].arrival_time)
             {
                   temp=proc[j];
                   proc[j]=proc[j+1];
                   proc[j+1]=temp;
             }
        }
     }
     for(i=0;i<n-1;i++)
     {
        for(j=0;j<n-i-1;j++)
        {
             if(proc[j].arrival_time==proc[j+1].arrival_time && proc[j].burst_time>proc[j+1].burst_time)
             {
                    temp=proc[j];
                    proc[j]=proc[j+1];
                    proc[j+1]=temp;
             }
         }
     }

    while(completed!=n)
    {
        int min_index=-1;
        int minimum=totalburst;

        for(i=0;i<n;i++)
        {
           if(proc[i].arrival_time<=time && proc[i].completed==0)
           {
              if(proc[i].burst_time<minimum)
              {
                 minimum=proc[i].burst_time;
                 min_index=i;
              }
              if(proc[i].burst_time=minimum)
              {
                 if(proc[i].arrival_time<proc[min_index].arrival_time)
                 {
                    minimum=proc[i].burst_time;
                    min_index=i;
                 }
              }
           }
        }
        if(min_index==-1)
        {
           time++;
        }
        else
        {
           completed++;
           proc[min_index].completed=1;
           proc[min_index].completion_time=time+proc[min_index].burst_time;
           proc[min_index].turn_around_time=proc[min_index].completion_time-proc[min_index].arrival_time;
           proc[min_index].waiting_time=proc[min_index].turn_around_time-proc[min_index].burst_time;
           time=proc[min_index].completion_time;
           total_waiting_time+=proc[min_index].waiting_time;
           total_turn_around_time+=proc[min_index].turn_around_time;
           printf("P%d ",proc[min_index].process_id);
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", proc[i].process_id, proc[i].arrival_time, proc[i].burst_time, proc[i].completion_time, proc[i].turn_around_time, proc[i].waiting_time);
    }
    printf("Average waiting time: %f\n", total_waiting_time/n);
    printf("Average turn around time: %f\n", total_turn_around_time/n);
}

void srtf(struct process proc[], int n)
{
    printf("\t\tSRTF\n");
    printf("Process Execution Order: ");
    int i,j,completed=0,time=0;
    float total_turn_around_time=0,total_waiting_time=0;

    for(i=0;i<n;i++)
    {
       proc[i].remaining_time=proc[i].burst_time;
    }

    while(completed!=n)
    {
       int min_burst_time=9999;
       int shortest=-1;

       for(i=0;i<n;i++)
       {
          if(proc[i].arrival_time<=time && proc[i].remaining_time<min_burst_time && proc[i].remaining_time>0)
          {
              min_burst_time=proc[i].remaining_time;
              shortest=i;
          }
       }

       if(shortest==-1)
       {
           time++;
           continue;
       }

       time++;
       proc[shortest].remaining_time--;

       if(proc[shortest].remaining_time==0)
       {
           completed++;
           proc[shortest].completion_time=time+1;
           proc[shortest].turn_around_time=proc[shortest].completion_time-proc[shortest].arrival_time;
           proc[shortest].waiting_time=proc[shortest].turn_around_time-proc[shortest].burst_time;
           total_turn_around_time+=proc[shortest].turn_around_time;
           total_waiting_time+=proc[shortest].waiting_time;
           printf("P%d ",proc[shortest].process_id);
       }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", proc[i].process_id, proc[i].arrival_time, proc[i].burst_time, proc[i].completion_time, proc[i].turn_around_time, proc[i].waiting_time);
    }
    printf("Average waiting time: %f\n", total_waiting_time/n);
    printf("Average turn around time: %f\n", total_turn_around_time/n);
}

void priority(struct process proc[],int n)
{
   printf("\t\tPRIORITY\n");
   printf("Process Execution Order: ");
   int i,j,completed=0,time=0;
   float total_waiting_time=0, total_turn_around_time=0;

   for(i=0;i<n;i++)
   {
      proc[i].completed=0;
   }

   for(i=0;i<n-1;i++)
   {
      for(j=0;j<n-i-1;j++)
      {
         if(proc[j].arrival_time>proc[j+1].arrival_time || proc[j].arrival_time==proc[j+1].arrival_time && proc[j].burst_time>proc[j+1].burst_time)
         {
            temp=proc[j];
            proc[j]=proc[j+1];
            proc[j+1]=temp;
         }
      }
   }

   for (i = 0; i < n - 1; i++)
   {
      for (j = 0; j < n - i - 1; j++)
      {
         if (proc[j].priority > proc[j + 1].priority)
         {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

   while(completed!=n)
   {
      int max_priority=9999;
      int min_index=-1;

      for(i=0;i<n;i++)
      {
         if(proc[i].arrival_time<=time && proc[i].completed==0)
         {
            if(proc[i].priority<max_priority)
            {
               max_priority=proc[i].priority;
               min_index=i;
            }
         }
      }

      if(min_index==-1)
      {
         time++;
      }
      else
      {
         completed++;
         proc[min_index].completed=1;
         proc[min_index].completion_time=time+proc[min_index].burst_time;
         proc[min_index].turn_around_time=proc[min_index].completion_time-proc[min_index].arrival_time;
         proc[min_index].waiting_time=proc[min_index].turn_around_time-proc[min_index].burst_time;
         time=proc[min_index].completion_time;
         total_waiting_time+=proc[min_index].waiting_time;
         total_turn_around_time+=proc[min_index].turn_around_time;
         printf("P%d ",proc[min_index].process_id);
      }
   }

   for (i = 0; i < n - 1; i++)
   {
      for (j = 0; j < n - i - 1; j++)
      {
         if (proc[j].process_id > proc[j + 1].process_id)
         {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

   printf("\nProcess\tPriority \tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
   for (int i = 0; i < n; i++)
   {
      printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", proc[i].process_id,proc[i].priority, proc[i].arrival_time, proc[i].burst_time, proc[i].completion_time, proc[i].turn_around_time,proc[i].waiting_time);
   }
   printf("Average waiting time: %f\n", total_waiting_time/n);
   printf("Average turn around time: %f\n", total_turn_around_time/n);
}

void roundrobin(struct process proc[],int n)
{
   printf("\t\tROUND ROBIN\n");
   int i,j,slice,time,remain=n,flag=0;
   float total_waiting_time=0,total_turn_around_time=0;
   printf("Enter time slice: ");
   scanf("%d",&slice);
   printf("Process Execution Order: ");

   for(i=0;i<n;i++)
   {
      proc[i].remaining_time=proc[i].burst_time;
   }

   for(i=0;i<n-1;i++)
   {
      for(j=0;j<n-i-1;j++)
      {
         if(proc[j].arrival_time>proc[j+1].arrival_time)
         {
            temp=proc[j];
            proc[j]=proc[j+1];
            proc[j+1]=temp;
         }
      }
   }

   for(time=0,i=0;remain!=0;)
   {
      if(proc[i].remaining_time<=slice && proc[i].remaining_time>0)
      {
         time+=proc[i].remaining_time;
         proc[i].remaining_time=0;
         flag=1;
      }
      else if(proc[i].remaining_time>0)
      {
         time+=slice;
         proc[i].remaining_time-=slice;
      }

      if(proc[i].remaining_time==0 && flag==1)
      {
         remain--;
         proc[i].completion_time=time;
         proc[i].turn_around_time=time-proc[i].arrival_time;
         proc[i].waiting_time=proc[i].turn_around_time-proc[i].burst_time;
         total_waiting_time+=proc[i].waiting_time;
         total_turn_around_time+=proc[i].turn_around_time;
         printf("P%d ",proc[i].process_id);
         flag=0;
      }

      if(i==(n-1))
      {
         i=0;
      }
      else if(proc[i+1].arrival_time<=time)
      {
         i++;
      }
      else
      {
         i=0;
      }
   }

   for (i = 0; i < n - 1; i++)
   {
      for (j = 0; j < n - i - 1; j++)
      {
         if (proc[j].process_id > proc[j + 1].process_id)
         {
            temp = proc[j];
            proc[j] = proc[j + 1];
            proc[j + 1] = temp;
         }
      }
   }

   printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
   for (int i = 0; i < n; i++)
   {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", proc[i].process_id, proc[i].arrival_time, proc[i].burst_time, proc[i].completion_time, proc[i].turn_around_time,proc[i].waiting_time);
   }
   printf("Average waiting time: %f\n", total_waiting_time/n);
   printf("Average turn around time: %f\n", total_turn_around_time/n);
}

int main()
{
   int n, i, j;
   printf("Enter the no. of processes : ");
   scanf("%d", &n);

   for (i = 0; i < n; i++)
   {
      proc[i].process_id = i+1;
      printf("Enter the arival time,burst time and priority for Process %d in order: ", i+1);
      scanf("%d %d %d",&proc[i].arrival_time, &proc[i].burst_time,&proc[i].priority);
   }

   fcfs(proc,n);
   sjf(proc,n);
   srtf(proc,n);
   priority(proc,n);
   roundrobin(proc,n);

   return 0;
}
