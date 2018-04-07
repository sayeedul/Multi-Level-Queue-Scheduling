#include<stdio.h>
                                        //FCFS SELF done algorithm...
struct process
{
	int pid,bt,wt,tat;
};

int main()
{
  int n,i,j;
  int total_wt=0,total_tat=0;
  
  printf("ENTER THE NUMBER of processes : ");
  scanf("%d",&n);
  printf("\nENTER PROCESS and Burst Time : ");
  struct process a[n];
  for( i=1;i<=n;i++)
  {
  	struct process pd;
  	printf("\n\t process no : ");
  	scanf("%d",&pd.pid);
  	printf("\n\t Burst Time : ");
  	scanf("%d",&pd.bt);
  	a[i] = pd;
  }
//-CALCULATING WAITING TIME---------------------------------------------------------------------------------------------------------------
     a[1].wt = 0 ; // Ist process wt is 0.
    for (i=2; i<=n ; i++ )
        a[i].wt =  a[i-1].bt + a[i-1].wt ;
        
// Calculating turnaround time by adding bt[i] + wt[i]
    for (i = 1; i <= n ; i++)
    {
        a[i].tat = a[i].bt + a[i].wt;
        
        total_wt = total_wt + a[i].wt;   //SUM waiting and TURn around Time.
        total_tat = total_tat + a[i].tat;
     }
//------------------------------------------------------------------------------------------------------------------------
// printing all details : 
 printf("\nProcess Number \tBurst Time \tWaiting Time \tTurn Around Time");
 for (int i = 1; i <= n ; i++)
 {
	printf("\n%d \t\t%d \t\t%d \t\t%d",a[i].pid,a[i].bt,a[i].wt,a[i].tat);
 }
//-----------------------------------------------------------------------------------------------------------------
printf("\n\n AVERAGE WAITING TIME : %.2f",(float)total_wt/(float)n);
printf("\n\n AVERAGE TURN AROUND TIME : %.2f",(float)total_tat/(float)n);

}
