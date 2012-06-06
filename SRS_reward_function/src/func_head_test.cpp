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
int n1 =6;  // Number of Bees around each selected locations ( except the elite location )
int n2 =20;  // Number of Bees around each elite locations
int e =1;   // Elite point/s

std::vector<std::vector<float> > Vhead;
int result_headstate;


int func( int i)  // Definition of Fitness Function
{
	int y;
	y=Vhead[0][i];
  return y;
}

int	xs = 0;
int	xe = 3;
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
				//std::cout << "oP2: " << oP2[0][j] << std::endl;
			}	//end sort
}

int main ()
{
double result_head;
	int front=0, back=1, folded=2, home=3;
	Vhead.resize(6);
	for (int i=5;i>=0;i--)
	{
	Vhead[i].resize(4);
	}
	Vhead[0][front]=100;
	Vhead[0][back]=500;
	Vhead[0][folded]=1000;
	Vhead[0][home]=1500;
//------------- Chose the best way with the result of value function with function max -------------
	result_head=0;
	for (int j=3;j>=0;j--)
	{
		if(result_head<Vhead[0][j])		//function max
		{
			result_head=Vhead[0][j];
			//result_headstate=j;			// know the state where the value function is the best
		}								// if j=0=front, j=1=back
	}

//------------- Chose the best way with the result of value function and Bees Algorithm-------------
	cout<<"Started..................\n";

	int i,d,j,k,temp2,aa[50],ranSearchBees,counter1,runs,fail,iter;
	//50 max number of selected sites out of n


	double temp1 ;

	int nghx[dim]; // Neighborhood X[]-Direction ( m )

	int bPos[dim][pop],bNghPos[dim][pop],fit[pop],bNghFit[pop],sortedFit[pop];
	int candidx[dim][pop];
	int bPosSort[dim][pop];

	ofstream Result;
	//Result.open("Result.txt");
	//Result<<"Iteration"<<"\t" <<"Generated Points"<<"\t" <<"para"<<"\t"<<"n"<<"\t"<<"Fittest"<<endl;
	Result.open("result_head.csv");
	Result<<"Iteration"<<"," <<"Generated Points"<<"," <<"para"<<","<<"n"<<","<<"Fittest"<<endl;
	// Different random number each time

	srand( (unsigned)time( NULL ) );

	fail=0;

	for(runs=0; runs<1; runs++)
	{	//number of runs
		//initialise with random start positions at the start of every run
		for(i=0;i<n;i++)
		{
			for(d=0;d<dim;d++)
			{
			bPos[d][i]= randfunc(xs, xe);
			//std::cout << "bpos " << bPos[d][i] << std::endl;
			fit[i]=func(bPos[d][i]);
			//std::cout << "fit: " << fit[i] << std::endl;
			}
		}

		ranSearchBees=n-m; // Number of bees search randomly

		// at this point bPos contains a number of randomly initialised particles
		// fit, contains the value of the fitness function
		// thus forming a (fit,bPos) tuple

		//sort by fitness, preserving the (f,pos) tuple
		funcSort(fit, sortedFit, bPos, bPosSort, n); // bpossort contains all the sort position of the scout bees

		//imax number of iteration
		for(iter=0; iter<imax ;iter++)
		{
			for(d=0;d<dim;d++)
			{
				nghx[d] = 1;
			}

			//changing number of bees around each selected point
			//condition for max values of n1 & n2
			if (n1>(n-m)) n1 = n-m;

			if (n2>(n-m)) n2 = n-m;

				 for(i=0;i<m;i++)
				 {
				   if(i<e)
					   aa[i]=n2;  // Number of bees around each ellite point/s
				   else
					   aa[i]=n1;  // Number of bees around other selected point
				   }

			// Search in the neighbourhood

			// temp1=-INT_MAX;
		counter1=0;  //I CAN HAZ SEGMENTATION FAULT - I HAVE NO IDEA IF THIS IS WHAT IT SHOULD BE, but without it you get seg fault

			for(k=0;k<m;k++)//k site
			{

				for(j=0;j<aa[k];j++) //j recruited bee
				{
					for(d=0;d<dim;d++)//d dimension
					{
						candidx[d][k]=bPosSort[d][k];
						 //std::cout << "candid: " << candidx[d][k] << std::endl;
						if ((candidx[d][k]-nghx[d])<xs) // boundry check (left)
							bNghPos[d][j]=randfunc(xs,candidx[d][k]+nghx[d]);
						else if ((candidx[d][k]+nghx[d])>xe)// boundry check (right)
							bNghPos[d][j]=randfunc(candidx[d][k]-nghx[d],xe);
						else
							bNghPos[d][j]=randfunc(candidx[d][k]-nghx[d] , candidx[d][k]+nghx[d]);
						 //std::cout << "bNghPos: " << bNghPos[d][j] << std::endl;
					 }
				  }// end of recruitment

				  for(j=0;j<aa[k];j++)	// evaluate fitness for recruited bees
					  bNghFit[j]=func(bNghPos[d][j]);

				  for(j=0;j<aa[k];j++)			// choosing the rep bee
//if(bNghFit[j]>= fit[j] ) //I think this line is better
					  if(bNghFit[j]>= temp1)
						  {
 //fit[j]=bNghFit[j]; //I think this line is better
							  temp1=bNghFit[j];
							  temp2=j;

						  }  // end of choosing the rep bee

 // don't understand these lines
				for(d=0;d<dim;d++)
					bPos[d][counter1]=bNghPos[d][temp2];

				counter1++; // next member of the new list

				temp1=-INT_MAX;		//

			}	// end of  Neighbourhood Search

			// Global search

			 for(k=0;k<ranSearchBees;k++)	//start of rand search for rest of bees
				 {
					for(d=0;d<dim;d++)
						bPos[d][counter1]=randfunc(xs, xe);

					counter1++;
					}

			 for(j=0;j<n;j++)		// evalute the fitness of the new list
				  fit[j]=func(j);

		}	//end iter = imax
		result_headstate=bPosSort[0][0]; //bPosSort[0][0] correspond to the elite site
		std::cout << "sort: " << result_headstate << std::endl;
	} // end runs

		cout<<"\n n= "<<n;

		cout<<"      Time/s of Failed are ="<<fail;

		Result.close();

		cout<<"\n finished..................\n";
		std::cout << "bestVhead: " << result_head << std::endl;


	return 0;
}
