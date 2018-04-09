#include<stdio.h>

struct process
{
	int pid,bt,wt,tat,priority;
};

int main()
{
  int n,i,n1=0,n2=0,n3=0,p=1,q=1,r=1;
  int total_wt=0,total_tat=0, quantum=4,QUANTUM=10 ;
  
  printf("ENTER THE NUMBER of processes : ");
  scanf("%d",&n);
  printf("\nPRIORITY RANGE OF QUEUES : ");
  printf("\n \tQueue1 : 1 - 10 ");
  printf("\n \tQueue2 : 11 - 20 ");
  printf("\n \tQueue3 : 21 - 30 \n");
  struct process queue1[n],queue2[n],queue3[n];
  printf("\nENTER Process Number , Priority , and Burst Time : \n");
  for( i=1;i<=n;i++)
  {
  	struct process pd;
  	printf("\n  process no : ");
  	scanf("%d",&pd.pid);
  	printf("  Burst Time : ");
  	scanf("%d",&pd.bt);
  	A:
  	printf("  priority : ");
  	scanf("%d",&pd.priority);
  	
  	if(pd.priority>=1 && pd.priority<=10)
  	{
  		queue3[p++]=pd; n3++;   //n1 size of queue1 
	  }
	else if(pd.priority>=11 && pd.priority<=20)
  	{
  		queue2[q++]=pd; n2++;   //n2 size of queue2
	  }
	else if(pd.priority>=21 && pd.priority<=30)
  	{
  		queue1[r++]=pd; n1++;  //n3 size of queue3
	  }
    else
    {
    	printf("\n\t| >PRIORITY OUT OF RANGE< |\n\n");  // PRIORITY HANDLING .
  		goto A;
	}
	
  }
  
//------------------------------------------------------------------------------------------------------------------------------------

struct process copy[3],q1[n1],q2[n2],q3[n3]; int sum1=0,sum2=0,sum3=0;

    for (int i = 1 ; i <= n1 ; i++)
    {
    	q1[i]= queue1[i]; sum1+=q1[i].bt; q1[i].wt=0;
	}
	for (int i = 1 ; i <= n2 ; i++)
    {
    	q2[i]= queue2[i]; sum2+=q2[i].bt; q2[i].wt=0;
	}
	for (int i = 1 ; i <= n3 ; i++)
    {
    	q3[i]= queue3[i]; sum3+=q3[i].bt; q3[i].wt=0;
	}
	int Rem_bt[3];
     Rem_bt[1]=sum1; Rem_bt[2]=sum2; Rem_bt[3]=sum3;

// ------------------------------------------------------------------------------------------------------------------------------------
 
    int curr_time = 0,count_time; // Current time
    int rem1_bt[n1] , rem2_bt[n2] , rem3_bt[n3] ;
    for (int i = 1 ; i <= n1 ; i++)
        rem1_bt[i] =  q1[i].bt ;
    for (int i = 1 ; i <= n2 ; i++)
        rem2_bt[i] =  q2[i].bt ;
    for (int i = 1 ; i <= n3 ; i++)
        rem3_bt[i] =  q3[i].bt ;
        
  //sorting the process in QUEUE2 based on priority-------------------------------------------
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
             int c1=0,c2=0,c3=0; int t; // for waiting times.		  
 //---------------------------------------------------------------------------------------------------------------------
     
    while (1) // OUTER while loop
    {
        bool Done = true;   
        for (int k = 1 ; k <=3; k++) // To traverse each queue.
        {
		  count_time=0;
		  
		 if(Rem_bt[k]>0)  
		  { 
		    Done = false ; // There is a pending queue 
		    
        //======================= OUTER Rem_bt[k] Begining. =================================================================================
		    
		     	
			if(Rem_bt[k]>QUANTUM)
			{
			  if(k==1) // queue1 RR with HIGHEST PRIORITY  ---------
			  {
        		//curr_time+= c1;  
    			 t += c1 ; // t += c1 ; // Current time
                 count_time=0;
   				 while (1)
    			 {
      			  bool done = true;
        		  for (int i=1 ; i<=n1 ; i++) // to traverse each process of Queue1.
       			   {
             		if (rem1_bt[i] > 0)
            		 {
                			done = false; // There is a pending process
 
                		    if (rem1_bt[i] > quantum)
                		    {
                  				if(count_time+quantum>10)
                  				{
                  					rem1_bt[i]-= 10-count_time ; break;
								  }
								t += quantum; count_time += quantum;
                    			rem1_bt[i] -= quantum;
                    			//sum1 -= quantum;  
                			 }
                			else
                			{
                				if(count_time+q1[i].bt>10)
                  				{
                  					rem1_bt[i]-= 10-count_time ; break;
								  }
                    			t = t + rem1_bt[i];
                    			q1[i].wt += t - q1[i].bt;  count_time+=q1[i].bt;   //sum1-= q1[i].bt;
                    			rem1_bt[i] = 0;
                	      	}
            		 }
            		  if(count_time>10)
            		   {
            		     break; //Rem_bt[1]=sum1;
					   }
        		     }
                     if (done == true || count_time>10)
                        break;
                    } // end of inner RR while loop.
 					
 					//curr_time += QUANTUM;
 					Rem_bt[k] -= QUANTUM; //count_time=0;
 					c1=0; c2+=QUANTUM; c3+=QUANTUM;
 					
				 } // end of Queue1 highest priority.--------------------------------------------------------------
               	
			  
			  else if(k==2)  // QUEUE2 STARTING Priority Algo.
				{
                 //calculating WAITING TIME....
     			   count_time=0;
        		   for(i=1; i<=n2 ; i++)
        		   {
        		       if(rem2_bt[i]<=0 && rem2_bt[i+1]<=0 ) 
        		       {
        		       	 continue;
					   }
					   else if(rem2_bt[i]<=0 && rem2_bt[i+1]>0 ) 
        		       {
        		       	// q2[i].wt += c2 ; 
							q2[i+1].wt += q2[i].bt + q2[i].wt +c2 ; continue;
					   }
					     q2[i].wt += c2 ;
					   while(rem2_bt[i]!=0)
					   {
					       if(count_time==10)
					          break;
						   rem2_bt[i]-= 1;
					       count_time++;
						}				   
					   if(count_time>10)
					          break;
					    if(i==n2)
					    {
					      break;	
						}
						if(rem2_bt[i]==0)
						{
							q2[i+1].wt = q2[i].bt + q2[i].wt ;
						}
				     }

                   //curr_time+=QUANTUM;
                   Rem_bt[k] -= QUANTUM;
                   c2=0; //count_time=0;
                   c1+=QUANTUM; c3+=QUANTUM;
		          }  // end of QUEUE2  
			   
              else if(k==3)  // QUEUE3 STARTING FCFS Algo.
				{
                 //calculating WAITING TIME-------------------------
     			   count_time=0;
        		   for(i=1; i<=n3 ; i++)
        		   {
        		       if(rem3_bt[i]<=0 && rem3_bt[i+1]<=0 ) 
        		       {
        		       	 continue;
					   }
					   else if(rem3_bt[i]<=0 && rem3_bt[i+1]>0 ) 
        		       {
        		       	     //q3[i].wt += c3 ;
							 q3[i+1].wt += q3[i].bt + q3[i].wt +c3 ; continue;
					   }
					     q3[i].wt += c3 ;
					   while(rem3_bt[i]!=0)
					   {
					       if(count_time==10)
					          break;
						   rem3_bt[i]-= 1;
					       count_time+= 1;
						}				   
					    if(count_time>10)
					          break;
					    if(i==n3)
					    {
					      break;	
						}
						if(rem3_bt[i]==0)
						{
					    q3[i+1].wt = q3[i].bt + q3[i].wt ;
					    }
				     }

                   //curr_time+=QUANTUM;
                   Rem_bt[k] -= QUANTUM; //count_time=0;
                   c1+= QUANTUM; c2+=QUANTUM; c3=0;
		          }  // end of QUEUE3 ========================================

              }//end of iF-Rem_bt[k]>QUANTUM
   		    
        //======================= OUTER Rem_bt[k] END. ==============================================================================
         
         else
		 { 
		   
		 
		   if(k==1)  // QUEUE1
		   {
		         //curr_time+= c1;  
    			t += c1;  	
		    	while (1)
    			{
        			bool done = true;
        			for (int i = 1 ; i <=n1; i++) // to traverse each process.
        			{

           			 	if (rem1_bt[i] > 0)
            			{
                			done = false; // There is a pending process in queue1
 
                			if (rem1_bt[i] > quantum)
                				{
                    				t += quantum;
                    				rem1_bt[i] -= quantum;
                				}
                			else
                				{
                    				t = t + rem1_bt[i];
                    				q1[i].wt = t - q1[i].bt;
                    				rem1_bt[i] = 0;
                				}
            			}
        			}
        			if(done == true)
          			   break;
    			}
		    	c1=0; c2 += Rem_bt[k]; c3+= Rem_bt[k];
		    	Rem_bt[k]=0;
						       
		      } // End of queue1.
		      
		  else if(k==2)  // QUEUE2
		  {
		  	 for(i=1; i<=n2 ; i++)
        		   {
        		       if(i==1 && n2==1)
					    {
					    	q2[i].wt+=c2 ;rem2_bt[k]=0; break;
						}
						if(i==n2)
						{
							rem2_bt[i]=0; break;
						}
					   if(rem2_bt[i]<=0 && rem2_bt[i+1]<=0 ) 
        		       {
        		       	 continue;
					   }
					   else if(rem2_bt[i]<=0 && rem2_bt[i+1]>0 ) 
        		       {
        		       	 // q2[i].wt += c2 ;
							 q2[i+1].wt = q2[i].bt + q2[i].wt +c2 ; continue; //cHANGED += here q2[i+1].wt = q2[i].bt + q2[i].wt
					   }
					     q2[i].wt += c2 ;
					     rem2_bt[i]=0;
						   	
					     q2[i+1].wt = q2[i].bt + q2[i].wt ;
				    }
				    
			 c2=0; c3+= Rem_bt[k]; c1+= Rem_bt[k];
			 Rem_bt[k]=0;
		   }
		   
		   else if(k==3)  // QUEUE3 
		  {
		  	 for(i=1; i<=n3 ; i++)
        		   {
        		       if(i==1 && n3==1)
					    {
					    	q3[i].wt+=c3 ;rem3_bt[k]=0; break;
						}
						if(i==n3)
						{
							rem3_bt[i]=0; break;
						}
					   if(rem3_bt[i]<=0 && rem3_bt[i+1]<=0 ) 
        		       {
        		       	 continue;
					   }
					   else if(rem3_bt[i]<=0 && rem3_bt[i+1]>0 ) 
        		       {
        		       	 // q3[i].wt += c3 ;
							 q3[i+1].wt = q3[i].bt + q3[i].wt +c3 ; continue; //cHANGED += here q2[i+1].wt = q2[i].bt + q2[i].wt
					   }
					     q3[i].wt += c3 ;
					     rem3_bt[i]=0;
					       	
					     q3[i+1].wt = q3[i].bt + q3[i].wt ;
				    }
			 c3=0; c2+= Rem_bt[k]; c1+= Rem_bt[k];
			 Rem_bt[k]=0;
		   }
		 	
		}  //end of Else : Rem_bt[k]>QUANTUM 
     		    
        //========================================================================================================
       
            
	   } //end of Rem_bt[k]>0
      
	} // end of OUTER i-loop. 

		if (Done == true)
            break;
	
  }//END OF OUTER WHILE for queue.
  
 //----Turn Around Time for Queue1 , Queue2 , Queue3============================
 
 for (int i = 1; i <= n1 ; i++)
  { q1[i].tat = q1[i].bt + q1[i].wt; }
 for (int i = 1; i <= n2 ; i++)
  { q2[i].tat = q2[i].bt + q2[i].wt; }
 for (int i = 1; i <= n3 ; i++)
  { q3[i].tat = q3[i].bt + q3[i].wt; }
 
//==============================================================================
//  TO PRINT EACH QUEUE details...

printf("\nProcess Number \tPriority \tBurst Time \tWaiting Time \tTurn Around Time");
printf("\n\nQUEUE1 : \n");
 for (int i = 1; i <= n1 ; i++)
 {
	printf("\n%d \t\t%d \t\t%d \t\t%d \t\t%d",q1[i].pid,q1[i].priority,q1[i].bt,q1[i].wt,q1[i].tat);
 }
 
printf("\nQUEUE2 : \n");
//printf("\nProcess Number \tPriority \tBurst Time \tWaiting Time \tTurn Around Time");
 for (int i = 1; i <= n2 ; i++)
 {
	printf("\n%d \t\t%d \t\t%d \t\t%d \t\t%d",q2[i].pid,q2[i].priority,q2[i].bt,q2[i].wt,q2[i].tat);
 }

printf("\nQUEUE3 : \n");
//printf("\nProcess Number \tPriority \tBurst Time \tWaiting Time \tTurn Around Time");
 for (int i = 1; i <= n3 ; i++)
 {
	printf("\n%d \t\t%d \t\t%d \t\t%d \t\t%d",q3[i].pid,q3[i].priority,q3[i].bt,q3[i].wt,q3[i].tat);
 }

}//End of main()
