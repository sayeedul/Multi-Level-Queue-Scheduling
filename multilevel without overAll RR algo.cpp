#include<stdio.h>

struct process
{
	int pid,bt,wt,tat,priority;
};

int main()
{
  int n,i,n1=0,n2=0,n3=0,j=1,k=1,l=1;
  int total_wt=0,total_tat=0, quantum=4,QUANTUM=10 ;
  
  printf("ENTER THE NUMBER of processes : ");
  scanf("%d",&n);
  printf("\nPRIORITY RANGE OF QUEUES : ");
  printf("\n \tQueue3 : 1 - 10 ");
  printf("\n \tQueue2 : 11 - 20 ");
  printf("\n \tQueue1 : 21 - 30 \n");
 struct process queue1[n],queue2[n],queue3[n];
  printf("\nENTER Process Number , Priority , and Burst Time : \n");
  for( i=1;i<=n;i++)
  {
  	struct process pd;
  	printf("\n  process no : ");
  	scanf("%d",&pd.pid);
  	printf("  priority : ");
  	scanf("%d",&pd.priority);
  	printf("  Burst Time : ");
  	scanf("%d",&pd.bt);
  	if(pd.priority>=1 && pd.priority<=10)
  	{
  		queue3[j++]=pd; n3++;  //n1 size of queue1 
	  }
	else if(pd.priority>=11 && pd.priority<=20)
  	{
  		queue2[k++]=pd; n2++;    //n2 size of queue2
	  }
	else if(pd.priority>=21 && pd.priority<=30)
  	{
  		queue1[l++]=pd; n1++; //n3 size of queue3
	  }
  }
  
//------------------------------------------------------------------------------------------------------------------------------------

struct process q1[n1],q2[n2],q3[n3]; int sum1=0,sum2=0,sum3=0;

    for (int i = 1 ; i <= n1 ; i++)
    {
    	q1[i]= queue1[i]; sum1+=q1[i].bt;
	}
	for (int i = 1 ; i <= n2 ; i++)
    {
    	q2[i]= queue2[i]; sum2+=q2[i].bt;
	}
	for (int i = 1 ; i <= n3 ; i++)
    {
    	q3[i]= queue3[i]; sum3+=q3[i].bt;
	}


                // RR with HIGHEST PRIORITY QUEUE i.e Queue1 =========================================================================

 					int rem_bt[n1] ;
    				for (int i = 1 ; i <= n1 ; i++)
        				  rem_bt[i] =  q1[i].bt ;
  
    				int t = 0 ; // Current time

   					 while (1)
    				 {
      				  bool done = true;
        			  for (int i = 1 ; i <=n1; i++) // to traverse each process of Q1.
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
                    			q1[i].wt = t - q1[i].bt; 
                    			rem_bt[i] = 0;
                	      	}
            		    }
        		      }
                       if (done == true)
                           break;
                    } // end of inner RR while loop.
                    //CALCLUATING TURN around time
					for (int i = 1; i <= n1 ; i++)
					{
        				q1[i].tat = q1[i].bt + q1[i].wt; 
					}		
				 // end of Queue1 highest priority.=================================================================================
               
	
			 	//sorting the process based on priority-------------------------------------------
				 struct process temp; int pos,J;
				 for(i=1;i<=n2;i++)
   				 {
      			  		pos=i;
        				for(J=i+1;J<=n2;J++)
        				{
            				if(q2[J].priority>q2[pos].priority)
                					pos=J;
        				}
        				temp=q2[i];
        				q2[i]=q2[pos];
        				q2[pos]=temp;
    			  }
      
                //-CALCULATING WAITING TIME---------------------------------------------------------------------------------------------------------------
     			q2[1].wt = sum1 ; // Ist process wt is sum1.
    			for (i=2; i<=n2 ; i++ )
        			q2[i].wt =  q2[i-1].bt + q2[i-1].wt ;
        
				// Calculating turnaround time by adding bt[i] + wt[i]
   				 for (i = 1; i <= n2 ; i++)
   				 {
        			q2[i].tat = q2[i].bt + q2[i].wt;
        			
     			 }

		        // end of QUEUE2  

            	// QUEUE3 CALCULATING WAITING TIME---------------------------------------------------------------------------------------------------------------
     				q3[1].wt = sum1+sum2 ; // Ist process wt is sum1+sum2.
   				 	for (i=2; i<=n3 ; i++ )
        			  q3[i].wt =  q3[i-1].bt + q3[i-1].wt ;
        
				// Calculating turnaround time by adding bt[i] + wt[i]
    			for (i = 1; i <= n3 ; i++)
   				 {
        			q3[i].tat = q3[i].bt + q3[i].wt;
     			  }
            	
			     // end of QUEUE3
           
		   
 //  TO PRINT EACH QUEUE details...

printf("\nProcess Number \tPriority \tBurst Time \tWaiting Time \tTurn Around Time");
printf("\nQUEUE1 : ");
 for (int i = 1; i <= n1 ; i++)
 {
	printf("\n%d \t\t%d \t\t%d \t\t%d \t\t%d",q1[i].pid,q1[i].priority,q1[i].bt,q1[i].wt,q1[i].tat);
 }
 
printf("\nQUEUE2 : ");
//printf("\nProcess Number \tPriority \tBurst Time \tWaiting Time \tTurn Around Time");
 for (int i = 1; i <= n2 ; i++)
 {
	printf("\n%d \t\t%d \t\t%d \t\t%d \t\t%d",q2[i].pid,q2[i].priority,q2[i].bt,q2[i].wt,q2[i].tat);
 }

printf("\nQUEUE3 : ");
//printf("\nProcess Number \tPriority \tBurst Time \tWaiting Time \tTurn Around Time");
 for (int i = 1; i <= n3 ; i++)
 {
	printf("\n%d \t\t%d \t\t%d \t\t%d \t\t%d",q3[i].pid,q3[i].priority,q3[i].bt,q3[i].wt,q3[i].tat);
 }


        
                   


}//End of main()
