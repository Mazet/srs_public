#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <fstream>
#include <Eigen/Core>

using namespace std;
#define dim 1       // Dimension of function
// Variables used
#define pop  50		// max num of population

int imax=50;
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
int	xe = 59;
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
	Vhead.resize(6);
	for (int i=5;i>=0;i--)
	{
	Vhead[i].resize(60);
	}
	Vhead[0][0]=10000;		Vhead[0][10]=2200;		Vhead[0][20]=3200;		Vhead[0][30]=4200;		Vhead[0][40]=5200;		Vhead[0][50]=6200;
	Vhead[0][1]=50000;		Vhead[0][11]=2300;		Vhead[0][21]=3300;		Vhead[0][31]=4300;		Vhead[0][41]=5300;		Vhead[0][51]=6300;
	Vhead[0][2]=1000;		Vhead[0][12]=2400;		Vhead[0][22]=3400;		Vhead[0][32]=4400;		Vhead[0][42]=5400;		Vhead[0][52]=6400;
	Vhead[0][3]=1500;		Vhead[0][13]=2500;		Vhead[0][23]=350000;	Vhead[0][33]=4500;		Vhead[0][43]=5500;		Vhead[0][53]=6500;
	Vhead[0][4]=1600;		Vhead[0][14]=2600;		Vhead[0][24]=3600;		Vhead[0][34]=4600;		Vhead[0][44]=5600;		Vhead[0][54]=6600;
	Vhead[0][5]=1700;		Vhead[0][15]=2700;		Vhead[0][25]=3700;		Vhead[0][35]=4700;		Vhead[0][45]=5700;		Vhead[0][55]=6700;
	Vhead[0][6]=1800;		Vhead[0][16]=2800;		Vhead[0][26]=3800;		Vhead[0][36]=4800;		Vhead[0][46]=5800;		Vhead[0][56]=6800;
	Vhead[0][7]=1900;		Vhead[0][17]=2900;		Vhead[0][27]=3900;		Vhead[0][37]=4900;		Vhead[0][47]=5900;		Vhead[0][57]=6900;
	Vhead[0][8]=2000;		Vhead[0][18]=3000;		Vhead[0][28]=4000;		Vhead[0][38]=5000;		Vhead[0][48]=6000;		Vhead[0][58]=7000;
	Vhead[0][9]=2100;		Vhead[0][19]=3100;		Vhead[0][29]=4100;		Vhead[0][39]=5100;		Vhead[0][49]=6100;		Vhead[0][59]=7100;

//------------- Chose the best way with the result of value function with function max -------------
/*	result_head=0;
	for (int j=59;j>=0;j--)
	{
		if(result_head<Vhead[0][j])		//function max
		{
			result_head=Vhead[0][j];
			//result_headstate=j;			// know the state where the value function is the best
		}								// if j=0=front, j=1=back
	}*/

//------------- Chose the best way with the result of value function and Bees Algorithm-------------
	cout<<"Started..................\n";

	int temp2;

	double temp1 ;
	int nghx[dim]; // Neighborhood X[]-Direction ( m )
	int fit[pop],sortedFit[pop],bPos[dim][pop],bPosSort[dim][pop];
	int bNghFit[pop],bNghPos[dim][pop];
	int globalFit[pop], globalPos[dim][pop];
	int candidx[dim][pop];

	srand( (unsigned)time( NULL ) );

	int fail=0;

	for(int runs=0; runs<1; runs++)
	{	//number of runs
		//initialise with random start positions at the start of every run
		for(int i=0;i<n;i++)
		{
			for(int d=0;d<dim;d++)
			{
			bPos[d][i]= randfunc(xs, xe);
			//std::cout << "bpos " << bPos[d][i] << std::endl;
			fit[i]=func(bPos[d][i]);
			//std::cout << "fit: " << fit[i] << std::endl;
			}
		}

		// at this point bPos contains a number of randomly initialised particles
		// fit, contains the value of the fit350000ness function
		// thus forming a (fit,bPos) tuple

		//sort by fitness, preserving the (f,pos) tuple
		funcSort(fit, sortedFit, bPos, bPosSort, n); // bpossort contains all the sort position of the scout bees
		fit[bPosSort[0][0]]=func(bPosSort[0][0]);
		std::cout << "bpossort: " << bPosSort[0][0] << std::endl;
		std::cout << "fit: " << fit[bPosSort[0][0]] << std::endl;

		//imax number of iteration
		for(int iter=0; iter<imax ;iter++)
		{
			for(int d=0;d<dim;d++)
				nghx[d] = 2;

			int aa[50]; //50 max number of selected sites out of n

				 for(int i=0;i<m;i++)
				 {
				   if(i<e)
					   aa[i]=n2;  // Number of bees around each elite point
				   else
					   aa[i]=n1;  // Number of bees around other selected point
				   }

// ----------------------------------------Neighbourhood search  ------------------------------------

			//temp1=-INT_MAX;

			for(int k=0;k<m;k++)//k site
			{
				for(int j=0;j<aa[k];j++) //j recruited bee
				{
					for(int d=0;d<dim;d++)//d dimension
					{
						candidx[d][k]=bPosSort[d][k]; //define the candidate position
						std::cout << "candid: " << candidx[d][k] << std::endl;
						if ((candidx[d][k]-nghx[d])<xs) // boundry check (left)
							{
							 bNghPos[d][j]=randfunc(xs,candidx[d][k]+nghx[d]);
							std::cout << "bNghPos1: " << bNghPos[d][j] << std::endl;
							bNghFit[j]=func(bNghPos[d][j]);
							std::cout << "bNghFit: " << bNghFit[j] << std::endl;
							}
						if ((candidx[d][k]+nghx[d])>xe)// boundry check (right)
							{
							bNghPos[d][j]=randfunc(candidx[d][k]-nghx[d],xe);
							std::cout << "bNghPos2: " << bNghPos[d][j] << std::endl;
							bNghFit[j]=func(bNghPos[d][j]);
							std::cout << "bNghFit: " << bNghFit[j] << std::endl;
							}
						if ((candidx[d][k]-nghx[d])>=xs and (candidx[d][k]+nghx[d])<=xe )
							{
							bNghPos[d][j]=randfunc(candidx[d][k]-nghx[d] , candidx[d][k]+nghx[d]);
							std::cout << "bNghPos3: " << bNghPos[d][j] << std::endl;
							bNghFit[j]=func(bNghPos[d][j]);
							std::cout << "bNghFit: " << bNghFit[j] << std::endl;
							}
						if(bNghFit[j]>= temp1 )
						{
							temp1=bNghFit[j];
							temp2=bNghPos[d][j];
						}  // end of choosing the rep bee
					}
				}// end of recruitment
			}	// end of  elite Neighbourhood Search

			 //Sort
		if (sortedFit[0]<= temp1)
		{
			sortedFit[0]=temp1;
			bPosSort[0][0]=temp2;
		}
		std::cout << "temp1: " <<temp1 << std::endl;
		std::cout << "temp2: " <<temp2 << std::endl;



// ----------------------------------------Global search  ------------------------------------

			int ranSearchBees=n-m; // Number of bees search randomly
			for(int k=0;k<ranSearchBees;k++)	//start of random search for rest of bees
				 {
					for(int d=0;d<dim;d++)
					{
						globalPos[d][k]=randfunc(xs, xe);
						std::cout << "bposglobal " << globalPos[d][k] << std::endl;
						globalFit[k]=func(globalPos[d][k]);// evaluate the fitness of the new list
						std::cout << "fitglobal: " << globalFit[k] << std::endl;
					 	if(globalFit[k]>= temp1 )
						{
							temp1=globalFit[k];
							temp2=globalPos[d][k];
						}
					}
				 }
				 //Sort
			if (sortedFit[0]<= temp1)
			{
				sortedFit[0]=temp1;
				bPosSort[0][0]=temp2;
			}
		}	//end iter = imax

	} // end runs

		result_headstate=bPosSort[0][0]; //bPosSort[0][0] correspond to the elite site
		result_head = sortedFit[0]; // sortedFit[0] correspond to the value of the elite site
		std::cout << "bestpos: " << result_headstate << std::endl;
		std::cout << "bestVfit: " << sortedFit[0] << std::endl;

	return 0;
}
