// Bee2D.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
//#include <conio>
#include <iostream>
#include <limits.h>
#include <fstream>

#include "func_arm.h"

using namespace std;





int main()
{
	cout<<"Started..................\n";

	int i,d,j,k,temp2,aa[50],ranSearchBees,counter1,runs,fail,iter,loop1; 
    //50 max number of selected sites out of n
	
	
	double temp1 ;
	double nb,sum_fit;
	double randselection;

	int a=20;

	
	int nghx[dim]; // Neighborhood X[]-Direction ( m )
	
	double q;      // random number which indicates Exploration or Exploitation 


    int Flag_a = 1;   // 1: Equal distribution of bees in selected sites and more in ellit sites
                      // 2: Proportion to fitness distribution of bees in selected sites
                     	

	double bPos[dim][pop],bNghPos[dim][pop],fit[pop],bNghFit[pop],sortedFit[pop];
    double percentsort[pop],candidx[dim][pop];
	double total = 0.0,shiftSortedFit[pop],sumsort[pop],bPosSort[dim][pop],shift,shift_it;
	
	ofstream Result;
	//Result.open("Result.txt");
	//Result<<"Iteration"<<"\t" <<"Generated Points"<<"\t" <<"para"<<"\t"<<"n"<<"\t"<<"Fittest"<<endl;
	Result.open("result_arm.csv");
	Result<<"Iteration"<<"," <<"Generated Points"<<"," <<"para"<<","<<"n"<<","<<"Fittest"<<endl;
	// Different random number each time

	srand( (unsigned)time( NULL ) );

	fail=0;


	for(runs=0; runs<1; runs++) {	//number of runs

		//initialise with random start positions at the start of every run
		for(i=0;i<n;i++)
		{
			for(d=0;d<dim;d++)
				bPos[d][i]=randfunc(start_x[d],end_x[d]) ;
			fit[i]=func(bPos,i);
		}

		ranSearchBees=n-m-e; // Number of bees search randomly
		
        // at this point bPos contains a number of randmoly initialised particles
        // fit, contains the value of the fitness function 
        // thus forming a (fit,bPos) tuple

		//imax number of iteration
		for(iter=0; iter<imax ;iter++)
		{	
			for(d=0;d<dim;d++)
			    nghx[d] = 1;

    		//sort by fitness, preserving the (f,pos) tuple
    		funcSort(fit, sortedFit, bPos, bPosSort, n);

    		for(k=0;k<e;k++)
                for(d=0;d<dim;d++)  bPos[d][k]=bPosSort[d][k];

    		//Roulette wheel selection to choose sites or choosing best sites
    		q=randfunc(start_x[d],end_x[d]); // choose a number b/w 0 and 1
           
		//cout << (sortedFit[n-1]<0.0);
            shift_it = (sortedFit[n-1]<0.0);

            //initialise sumsort

            shift = sortedFit[n-1] + 1;
            for (i=0;i<=n;i++) {
               sumsort[i] = 0.0;
               if( shift_it ) sortedFit[i] -= sortedFit[n-1] + 1;
               total += sortedFit[i];
            }

            		
            if(q < q0)	{	// Choosing best m
            	for(i=0;i<m;i++)
            		for(d=0;d<dim;d++)
            			candidx[d][i] = bPosSort[d][i];

            } else {			
                // Choosing sites probabilistically
                // some kind of normalised values
       			for (k=1;k<=n;k++) sumsort[k] = sumsort[k-1] + sortedFit[k]/total;

            	for (i=0;i<m;i++)
            	   {
            			if( i < e ) // choosing the best (e) sites
            			{
            				for(d=0;d<dim;d++) candidx[d][i] = bPosSort[d][i];					
            				sortedFit[i]=0.0;
            			}

            			// choosing the (m-e) sites using ( R/W)
            			randselection = randfunc(start_x[d],end_x[d]);

                        //loop, yet again through n values, if the current is under the threshold and 
                        //next is above or equal -- IMO, this adds 1 site, not m-e sites
                        //this is simply bizarre!!!
            			for (temp2=0;temp2<n;temp2++)
            			{
            			  if (sumsort[temp2]<randselection && sumsort[temp2+1]>=randselection)
            			  {
                			  for(d=0;d<dim;d++) candidx[d][i] = bPosSort[d][temp2];					
                              sortedFit[temp2] = 0.0;
                              break; //does this break out of the loop or the if?
            			  }
            			}
            	
            	  }
                }

    		///////////////////////////////
    		//     changing number of bees around each selected point 
   			//condition for max values of n1 & n2
    		if (n1>(n-m-e)) n1 = n-m-e;
    			
    		if (n2>(n-m-e)) n2 = n-m-e;

            if(Flag_a == 1)   //   Equal distribution of bees in selected sites
    		{
    			 for(i=0;i<m;i++)
    			 {
    			   if(i<e)
    				   aa[i]=n2;  // Number of bees around each ellite point/s
    			   else
    				   aa[i]=n1;  // Number of bees around other selected point
    			   }
    		 }

    		 else  //   Proportion to fitness distribution of bees in selected sites
    		 {
    			 sum_fit=0;

    			 if (sortedFit[n-1]<0.0)
    			 {
 ////////////////////////////////////////////////////////////////////////////////////////////////
    				 for(i=0;i<m;i++)
    					 sum_fit=sum_fit+func(candidx,i)-sortedFit[n-1];
    				 
    				 for(i=0;i<m;i++)
    				  {
    					 nb=((func(candidx,i)-sortedFit[n-1])/sum_fit)*a+.5;
    					  aa[i]=nb;  // Number of bees around each selected point
    					  if(aa[i] < 1)
    					  aa[i]=1;
    					}
    				}
    			  else
    			  { 
    				  for(i=0;i<m;i++)
    		  			sum_fit=sum_fit+func(candidx,i);

    				  for(i=0;i<m;i++)
    				  {
    					  nb=(func(candidx,i)/sum_fit)*a+.5;
    					  aa[i]=nb;  // Number of bees around each selected point
    			          if(aa[i]<1) aa[i]=1;
    				  }
    				}
    			  }
    		 

    		// Search in the neighbourhood
    			
    		 temp1=-INT_MAX;
		counter1=0;  //I CAN HAZ SEGMENTATION FAULT - I HAVE NO IDEA IF THIS IS WHAT IT SHOULD BE, but without it you get seg fault 

    		for(k=0;k<m;k++)//k site
    		{
    			  for(j=0;j<aa[k];j++) //j recruited bee
    			  {
    				 for(d=0;d<dim;d++)//d dimension
    				 {
    					 if ((candidx[d][k]-nghx[d])<start_x[d]) // boundry check (left)
    						 bNghPos[d][j]=randfunc(start_x[d],candidx[d][k]+nghx[d]);
    					 else if ((candidx[d][k]+nghx[d])>end_x[d])// boundry check (right)
    						 bNghPos[d][j]=randfunc(candidx[d][k]-nghx[d],end_x[d]);
    					 else 
    						 bNghPos[d][j]=randfunc(candidx[d][k]-nghx[d] , candidx[d][k]+nghx[d]);
    					 }

    				 }// end of recruitment

    			  for(j=0;j<aa[k];j++)	// evaluate fitness for recruited bees
    				  bNghFit[j]=func(bNghPos,j); 

    			  for(j=0;j<aa[k];j++)			// choosing the rep bee
    				  if(bNghFit[j]>= temp1 )
    					  {

    							temp1=bNghFit[j];
    							temp2=j;

    							}  // end of choosing the rep bee


    			for(d=0;d<dim;d++)
    				bPos[d][counter1]=bNghPos[d][temp2];
	
    			counter1++; // next member of the new list

    			temp1=-INT_MAX;		//

    		}	// end of  Neighbourhood Search

    		 for(k=0;k<ranSearchBees;k++)	//start of rand search for rest of bees
    			 {
    				for(d=0;d<dim;d++)
    					bPos[d][counter1]=randfunc(start_x[d],end_x[d]);

    				counter1++;

    				}
///////////////////////////////////////////////////////////////////////////////////
    		 for(j=0;j<n;j++)		// evalute the fitness of the new list
    		 	  fit[j]=func(bPos,j);
    		  
		}	//end iter = imax

} // end runs

 
	cout<<"\n n= "<<n;

	cout<<"      Time/s of Failed are ="<<fail;

	Result.close();

	cout<<"\n finished..................\n";

}
