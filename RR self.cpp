#include<stdio.h>
#include<unistd.h>
struct process
{
	int pid,bt,wt,tat;
};

int main()
{
  int n,i,quantum=4;
  int total_wt=0,total_tat=0;
  
  printf("ENTER THE NUMBER of processes : ");
  scanf("%d",&n);
  printf("\nENTER PROCESS AND THEIR BURST TIME : ");
  struct process a[n];
  for( i=1;i<=n;i++)
  {
  	struct process pd;
  	printf("\n process no : ");
  	scanf("%d",&pd.pid);
  	printf("\n Burst time : ");
  	scanf("%d",&pd.bt);
  	a[i] = pd;
  }
  
  //calculating WAiTING TIME.-------------------------------------------------------------------------------------
  int rem_bt[n];
    for (int i = 1 ; i <= n ; i++)
        rem_bt[i] =  a[i].bt;
  
  
    int t = 0; // Current time

    while (1)
    {
        bool done = true;
        for (int i = 1 ; i <=n; i++) // to traverse each process.
        {

            if (rem_bt[i] > 0)
            {
                done = false; // There is a pending process
 
                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {

                    t = t + rem_bt[i];
                    a[i].wt = t - a[i].bt;
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == true)
          break;
    }
  
//-------------------------------------------------------------------------------------------------------------------
//CALCLUATING TURN around time
for (int i = 1; i <= n ; i++)
{
        a[i].tat = a[i].bt + a[i].wt;
        
        total_wt = total_wt + a[i].wt;   //SUM waiting and TURn around Time.
        total_tat = total_tat + a[i].tat;
}

//-------------------------------------------------------------------------------------------------------------------
 // printing all details : 
 printf("\nProcess Number \tBurst Time \tWaiting Time \tTurn Around Time");
 for (int i = 1; i <= n ; i++)
 {
	printf("\n%d \t\t%d \t\t%d \t\t%d",a[i].pid,a[i].bt,a[i].wt,a[i].tat);
 }
//-----------------------------------------------------------------------------------------------------------------
printf("\n\n AVERAGE WAITING TIME : %f",(float)total_wt/(float)n);
printf("\n\n AVERAGE TURN AROUND TIME : %f",(float)total_tat/(float)n);
}
