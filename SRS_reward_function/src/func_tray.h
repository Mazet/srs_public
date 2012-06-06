#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <fstream>

using namespace std;
#define dim 1       // Dimension of function
// Variables used
#define pop  50		// max num of population

int imax=5;
int n= pop;  // Number of Scout Bees
int m= 2;   // Number of selected Locations
int n1 =6;  // Number of Bees around each selected locations ( except the ellit location )
int n2 =20;  // Number of Bees around each ellit locations
int e =1;   // Elite point/s

int func( int i,std::vector<std::vector<float> > Vtray)  // Definition of Fitness Function
{
	int y;
	y=Vtray[0][i];
	  return y;
}

int	xs = 0;
int	xe = 1;
int randfunc( int xs, int xe )  // Definition of Random number Generator Function*/
{
  double randnum;
  randnum=rand() ;
  randnum=xs+randnum*(xe-xs) / RAND_MAX;
  int intrandnum = randnum +0.5;	//kind of rounding in order to have only 0 or 1 random number
  return intrandnum;
}

void funcSort(int inP1[],int oP1[],int inP2[][pop],int oP2[][pop],int size)
{
		double temp1=-INT_MAX;
		int temp2;

			for( int j=0;j<size;j++)	//sort
			{
				for(int k=0;k<size;k++)
					if(inP1[k]> temp1 )
					{
						temp1=inP1[k];
						temp2=k;
					}

				oP1[j]=temp1;
				for(int d=0;d<dim;d++)
				  oP2[d][j]=inP2[d][temp2];
				temp1=-INT_MAX;
				inP1[temp2]=-INT_MAX;
			}	//end sort
}

void reward_tray (std::string action_name, std::string action_stage, std::vector<std::vector<float> >& Vtray,double& result_tray ,int& result_traystate)
{
float gamma=0.1;  // define the discount factor "gamma"
	int up=0, down=1;
	std::vector<float> R;   //create a vector R with an unknown size
		R.resize(2);  // define the size of the vector
	std::vector<float> T;   //create a vector T with an unknown size
			T.resize(2);  // define the size of the vector
	Vtray.resize(6);
	for (int i=5;i>=0;i--)
	{
	Vtray[i].resize(2);
	}
	//----- initialisation in order to compute the value function -----
					Vtray[5][0]=R[up];
					Vtray[5][1]=R[down];
	for (int t=4;t>=0;t--)
	{
			if (action_name=="navigation")
			{
				if (action_stage=="pre-config")
				{
					R[up]=4;		T[up]=0.81;
					R[down]=20;		T[down]=0.19;
				}
				if (action_stage=="post-config")
				{
					R[up]=5;		T[up]=0.63;
					R[down]=20;		T[down]=0.37;
				}
			}
			if (action_name=="detection")
			{
				if (action_stage=="pre-config")
				{
					R[up]=8;		T[up]=0.7;
					R[down]=20;		T[down]=0.3;
				}
				if (action_stage=="post-config")
				{
					R[up]=2;		T[up]=0.55;
					R[down]=20;		T[down]=0.45;
				}
			}
			if (action_name=="grasp")
			{
				if (action_stage=="pre-config")
				{
					R[up]=7;		T[up]=0.66;
					R[down]=20;		T[down]=0.34;
				}
				if (action_stage=="post-config")
				{
					R[up]=5.5;		T[up]=0.74;
					R[down]=6;		T[down]=0.26;
				}
			}
			if (action_name=="put_on_tray")
			{
				if (action_stage=="pre-config")
				{
					R[up]=100;		T[up]=0.83;
					R[down]=6;		T[down]=0.17;
				}
				if (action_stage=="post-config")
				{
					R[up]=100;		T[up]=0.28;
					R[down]=5;		T[down]=0.72;
				}
			}
	//-----  computing of the value function -----
			Vtray[t][up]=R[up] + gamma*(T[up]*Vtray[t+1][up]+T[down]*Vtray[t+1][down]);
			Vtray[t][down]=R[down] + gamma*(T[up]*Vtray[t+1][up]+T[down]*Vtray[t+1][down]);
	}
	//------------- Chose the best way with the function max -------------
/*result_tray=0;
for (int j=1;j>=0;j--)
{
	if(result_tray<Vtray[0][j])		//function max
	{
		result_tray=Vtray[0][j];
		//result_traystate=j;			// know the state where the value function is the best
	}								// if j=0=front, j=1=back
}*/

//------------- Chose the best way with the Bees algorithm -------------

cout<<"Started..................\n";

	int i,d,j,k,temp2,aa[50],ranSearchBees,counter1,runs,fail,iter;
	//50 max number of selected sites out of n


	double temp1 ;

	int nghx[dim]; // Neighborhood X[]-Direction ( m )

	int bPos[dim][pop],bNghPos[dim][pop],fit[pop],bNghFit[pop],sortedFit[pop];
	int candidx[dim][pop];
	int bPosSort[dim][pop];

	srand( (unsigned)time( NULL ) );

	fail=0;

	for(runs=0; runs<1; runs++)
	{
		//number of runs
		//initialise with random start positions at the start of every run
		for(i=0;i<n;i++)
		{
			for(d=0;d<dim;d++)
			{
			bPos[d][i]= randfunc(xs, xe);
			//std::cout << "bpos " << bPos[d][i] << std::endl;
			fit[i]=func(bPos[d][i],Vtray);

			//std::cout << "fit: " << fit[i] << std::endl;
			}
		}

		ranSearchBees=n-m; // Number of bees search randomly

		// at this point bPos contains a number of randomly initialised particles
		// fit, contains the value of the fitness function
		// thus forming a (fit,bPos) tuple

		//sort by fitness, preserving the (f,pos) tuple
		funcSort(fit, sortedFit, bPos, bPosSort, n); // bpossort contains all the sort position of the scout bees
		 //bPosSort[0][0] correspond to the elite site
		//imax number of iteration
		for(iter=0; iter<imax ;iter++)
		{
			for(d=0;d<dim;d++)
			{
				nghx[d] = 1;
			}

			//changing number of bees around each selected point
			//condition for max values of n1 & n2
			if (n1>(n-m-e)) n1 = n-m;

			if (n2>(n-m-e)) n2 = n-m;

				 for(i=0;i<m;i++)
				 {
				   if(i<e)
					   aa[i]=n2;  // Number of bees around each ellite point/s
				   else
					   aa[i]=n1;  // Number of bees around other selected point
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
						 candidx[d][k]=bPosSort[d][k];
						 if ((candidx[d][k]-nghx[d])<xs) // boundry check (left)
							 bNghPos[d][j]=randfunc(xs,candidx[d][k]+nghx[d]);
						 else if ((candidx[d][k]+nghx[d])>xe)// boundry check (right)
							 bNghPos[d][j]=randfunc(candidx[d][k]-nghx[d],xe);
						 else
							 bNghPos[d][j]=randfunc(candidx[d][k]-nghx[d] , candidx[d][k]+nghx[d]);
					}

				}// end of recruitment

				  for(j=0;j<aa[k];j++)	// evaluate fitness for recruited bees
					  bNghFit[j]=func(j,Vtray);

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
						bPos[d][counter1]=randfunc(xs, xe);

					counter1++;

					}
///////////////////////////////////////////////////////////////////////////////////
			 for(j=0;j<n;j++)		// evalute the fitness of the new list
				  fit[j]=func(j,Vtray);

		}	//end iter = imax
		result_traystate=bPosSort[0][0];
		std::cout << "sort: " << result_traystate << std::endl;
} // end runs

	cout<<"\n n= "<<n;

	cout<<"      Time/s of Failed are ="<<fail;

	cout<<"\n finished..................\n";
	//std::cout << "bestVtray: " << result_trayorso << std::endl;


return;
}
