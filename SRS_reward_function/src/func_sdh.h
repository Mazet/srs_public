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

int func( int i,std::vector<std::vector<float> > Vsdh)  // Definition of Fitness Function
{
	int y;
	y=Vsdh[0][i];
	  return y;
}

int	xs = 0;
int	xe = 9;
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

void reward_sdh (std::string action_name, std::string action_stage, std::vector<std::vector<float> >& Vsdh,double& result_sdh ,int& result_sdhstate)
{
float gamma=0.1;  // define the discount factor "gamma"
	int home=0, cylclosed=1, cylopen=2, cyltotalopen=3, spheropen=4, spherclosed=5,
		paropen=6, parclosed=7,point=8, fist=9;
	std::vector<float> R;   //create a vector R with an unknown size
		R.resize(10);  // define the size of the vector
	std::vector<float> T;   //create a vector T with an unknown size
		T.resize(10);  // define the size of the vector
	Vsdh.resize(6);
	for (int i=5;i>=0;i--)
	{
	Vsdh[i].resize(10);
	}
//----- initialisation in order to compute the value function -----
			Vsdh[5][0]=R[home];
			Vsdh[5][1]=R[cylclosed];
			Vsdh[5][2]=R[cylopen];
			Vsdh[5][3]=R[cyltotalopen];
			Vsdh[5][4]=R[spheropen];
			Vsdh[5][5]=R[spherclosed];
			Vsdh[5][6]=R[paropen];
			Vsdh[5][7]=R[parclosed];
			Vsdh[5][8]=R[point];
			Vsdh[5][9]=R[fist];
	for (int t=4;t>=0;t--)
	{
		if (action_name=="navigation")
		{
			if (action_stage=="pre-config")
			{
				R[home]=3000;				T[home]=0.5;
				R[cylclosed]=4;			T[cylclosed]=0.08;
				R[cylopen]=1;			T[cylopen]=0.02;
				R[cyltotalopen]=2;		T[cyltotalopen]=0.05;
				R[spheropen]=7;			T[spheropen]=0.1;
				R[spherclosed]=3;		T[spherclosed]=0.15;
				R[paropen]=5;			T[paropen]=0.12;
				R[parclosed]=6;			T[parclosed]=0.21;
				R[point]=8;				T[point]=0.06;
				R[fist]=9;				T[fist]=0.14;
			}
			if (action_stage=="post-config")
			{
				R[home]=5;				T[home]=0.4;
				R[cylclosed]=3;		T[cylclosed]=0.18;
				R[cylopen]=2;			T[cylopen]=0.12;
				R[cyltotalopen]=4;		T[cyltotalopen]=0.15;
				R[spheropen]=8;			T[spheropen]=0.11;
				R[spherclosed]=4;		T[spherclosed]=0.14;
				R[paropen]=2;			T[paropen]=0.17;
				R[parclosed]=9;			T[parclosed]=0.31;
				R[point]=4;				T[point]=0.16;
				R[fist]=600;				T[fist]=0.24;
			}
		}
		if (action_name=="detection")
		{
			if (action_stage=="pre-config")
			{
				R[home]=8;				T[home]=0.5;
				R[cylclosed]=6;			T[cylclosed]=0.2;
				R[cylopen]=4;			T[cylopen]=0.1;
				R[cyltotalopen]=1;		T[cyltotalopen]=0.18;
				R[spheropen]=9;			T[spheropen]=0.31;
				R[spherclosed]=5;		T[spherclosed]=0.04;
				R[paropen]=3;			T[paropen]=0.07;
				R[parclosed]=2;			T[parclosed]=0.14;
				R[point]=4;				T[point]=0.2;
				R[fist]=1;				T[fist]=0.3;
			}
			if (action_stage=="post-config")
			{
				R[home]=4;				T[home]=0.15;
				R[cylclosed]=5;			T[cylclosed]=0.2;
				R[cylopen]=2;			T[cylopen]=0.10;
				R[cyltotalopen]=1;		T[cyltotalopen]=0.25;
				R[spheropen]=3;			T[spheropen]=0.3;
				R[spherclosed]=7;		T[spherclosed]=0.4;
				R[paropen]=6;			T[paropen]=0.7;
				R[parclosed]=5;			T[parclosed]=0.12;
				R[point]=4;				T[point]=0.45;
				R[fist]=8;				T[fist]=0.28;
			}
		}
		if (action_name=="grasp")
		{
			if (action_stage=="pre-config")
			{
				R[home]=9;				T[home]=0.2;
				R[cylclosed]=2;			T[cylclosed]=0.5;
				R[cylopen]=3;			T[cylopen]=0.12;
				R[cyltotalopen]=4;		T[cyltotalopen]=0.1;
				R[spheropen]=6;			T[spheropen]=0.18;
				R[spherclosed]=8;		T[spherclosed]=0.22;
				R[paropen]=9;			T[paropen]=0.3;
				R[parclosed]=10;		T[parclosed]=0.41;
				R[point]=11;			T[point]=0.21;
				R[fist]=12;				T[fist]=0.12;
			}
			if (action_stage=="post-config")
			{
				R[home]=14;				T[home]=0.12;
				R[cylclosed]=15;		T[cylclosed]=0.15;
				R[cylopen]=13;			T[cylopen]=0.3;
				R[cyltotalopen]=18;		T[cyltotalopen]=0.22;
				R[spheropen]=8;			T[spheropen]=0.17;
				R[spherclosed]=9;		T[spherclosed]=0.25;
				R[paropen]=1;			T[paropen]=0.42;
				R[parclosed]=2;			T[parclosed]=0.28;
				R[point]=5;				T[point]=0.34;
				R[fist]=7;				T[fist]=0.5;
			}
		}
		if (action_name=="put_on_tray")
		{
			if (action_stage=="pre-config")
			{
				R[home]=9;				T[home]=0.1;
				R[cylclosed]=8;			T[cylclosed]=0.2;
				R[cylopen]=6;			T[cylopen]=0.3;
				R[cyltotalopen]=5;		T[cyltotalopen]=0.4;
				R[spheropen]=3;			T[spheropen]=0.5;
				R[spherclosed]=7;		T[spherclosed]=0.15;
				R[paropen]=5;			T[paropen]=0.25;
				R[parclosed]=4;			T[parclosed]=0.35;
				R[point]=2;				T[point]=0.45;
				R[fist]=1;				T[fist]=0.12;
			}
			if (action_stage=="post-config")
			{
				R[home]=4;				T[home]=0.5;
				R[cylclosed]=8;			T[cylclosed]=0.4;
				R[cylopen]=9;			T[cylopen]=0.35;
				R[cyltotalopen]=6;		T[cyltotalopen]=0.3;
				R[spheropen]=5;			T[spheropen]=0.25;
				R[spherclosed]=9;		T[spherclosed]=0.2;
				R[paropen]=7;			T[paropen]=0.10;
				R[parclosed]=10;		T[parclosed]=0.05;
				R[point]=14;			T[point]=0.02;
				R[fist]=7;				T[fist]=0.01;
			}
		}
	//-----  computing of the value function -----
		Vsdh[t][home]=R[home] + gamma*(T[home]*Vsdh[t+1][home]+T[cylclosed]*Vsdh[t+1][cylclosed]+T[cylopen]*Vsdh[t+1][cylopen]+T[cyltotalopen]*Vsdh[t+1][cyltotalopen]+T[spheropen]*Vsdh[t+1][spheropen]+T[spherclosed]*Vsdh[t+1][spherclosed]+T[paropen]*Vsdh[t+1][paropen]+T[parclosed]*Vsdh[t+1][parclosed]+T[point]*Vsdh[t+1][point]+T[fist]*Vsdh[t+1][fist]);
		Vsdh[t][cylclosed]=R[cylclosed] + gamma*(T[home]*Vsdh[t+1][home]+T[cylclosed]*Vsdh[t+1][cylclosed]+T[cylopen]*Vsdh[t+1][cylopen]+T[cyltotalopen]*Vsdh[t+1][cyltotalopen]+T[spheropen]*Vsdh[t+1][spheropen]+T[spherclosed]*Vsdh[t+1][spherclosed]+T[paropen]*Vsdh[t+1][paropen]+T[parclosed]*Vsdh[t+1][parclosed]+T[point]*Vsdh[t+1][point]+T[fist]*Vsdh[t+1][fist]);
		Vsdh[t][cylopen]=R[cylopen] + gamma*(T[home]*Vsdh[t+1][home]+T[cylclosed]*Vsdh[t+1][cylclosed]+T[cylopen]*Vsdh[t+1][cylopen]+T[cyltotalopen]*Vsdh[t+1][cyltotalopen]+T[spheropen]*Vsdh[t+1][spheropen]+T[spherclosed]*Vsdh[t+1][spherclosed]+T[paropen]*Vsdh[t+1][paropen]+T[parclosed]*Vsdh[t+1][parclosed]+T[point]*Vsdh[t+1][point]+T[fist]*Vsdh[t+1][fist]);
		Vsdh[t][cyltotalopen]=R[cyltotalopen] + gamma*(T[home]*Vsdh[t+1][home]+T[cylclosed]*Vsdh[t+1][cylclosed]+T[cylopen]*Vsdh[t+1][cylopen]+T[cyltotalopen]*Vsdh[t+1][cyltotalopen]+T[spheropen]*Vsdh[t+1][spheropen]+T[spherclosed]*Vsdh[t+1][spherclosed]+T[paropen]*Vsdh[t+1][paropen]+T[parclosed]*Vsdh[t+1][parclosed]+T[point]*Vsdh[t+1][point]+T[fist]*Vsdh[t+1][fist]);
		Vsdh[t][spheropen]=R[spheropen] + gamma*(T[home]*Vsdh[t+1][home]+T[cylclosed]*Vsdh[t+1][cylclosed]+T[cylopen]*Vsdh[t+1][cylopen]+T[cyltotalopen]*Vsdh[t+1][cyltotalopen]+T[spheropen]*Vsdh[t+1][spheropen]+T[spherclosed]*Vsdh[t+1][spherclosed]+T[paropen]*Vsdh[t+1][paropen]+T[parclosed]*Vsdh[t+1][parclosed]+T[point]*Vsdh[t+1][point]+T[fist]*Vsdh[t+1][fist]);
		Vsdh[t][spherclosed]=R[spherclosed] + gamma*(T[home]*Vsdh[t+1][home]+T[cylclosed]*Vsdh[t+1][cylclosed]+T[cylopen]*Vsdh[t+1][cylopen]+T[cyltotalopen]*Vsdh[t+1][cyltotalopen]+T[spheropen]*Vsdh[t+1][spheropen]+T[spherclosed]*Vsdh[t+1][spherclosed]+T[paropen]*Vsdh[t+1][paropen]+T[parclosed]*Vsdh[t+1][parclosed]+T[point]*Vsdh[t+1][point]+T[fist]*Vsdh[t+1][fist]);
		Vsdh[t][paropen]=R[paropen] + gamma*(T[home]*Vsdh[t+1][home]+T[cylclosed]*Vsdh[t+1][cylclosed]+T[cylopen]*Vsdh[t+1][cylopen]+T[cyltotalopen]*Vsdh[t+1][cyltotalopen]+T[spheropen]*Vsdh[t+1][spheropen]+T[spherclosed]*Vsdh[t+1][spherclosed]+T[paropen]*Vsdh[t+1][paropen]+T[parclosed]*Vsdh[t+1][parclosed]+T[point]*Vsdh[t+1][point]+T[fist]*Vsdh[t+1][fist]);
		Vsdh[t][parclosed]=R[parclosed] + gamma*(T[home]*Vsdh[t+1][home]+T[cylclosed]*Vsdh[t+1][cylclosed]+T[cylopen]*Vsdh[t+1][cylopen]+T[cyltotalopen]*Vsdh[t+1][cyltotalopen]+T[spheropen]*Vsdh[t+1][spheropen]+T[spherclosed]*Vsdh[t+1][spherclosed]+T[paropen]*Vsdh[t+1][paropen]+T[parclosed]*Vsdh[t+1][parclosed]+T[point]*Vsdh[t+1][point]+T[fist]*Vsdh[t+1][fist]);
		Vsdh[t][point]=R[point] + gamma*(T[home]*Vsdh[t+1][home]+T[cylclosed]*Vsdh[t+1][cylclosed]+T[cylopen]*Vsdh[t+1][cylopen]+T[cyltotalopen]*Vsdh[t+1][cyltotalopen]+T[spheropen]*Vsdh[t+1][spheropen]+T[spherclosed]*Vsdh[t+1][spherclosed]+T[paropen]*Vsdh[t+1][paropen]+T[parclosed]*Vsdh[t+1][parclosed]+T[point]*Vsdh[t+1][point]+T[fist]*Vsdh[t+1][fist]);
		Vsdh[t][fist]=R[fist] + gamma*(T[home]*Vsdh[t+1][home]+T[cylclosed]*Vsdh[t+1][cylclosed]+T[cylopen]*Vsdh[t+1][cylopen]+T[cyltotalopen]*Vsdh[t+1][cyltotalopen]+T[spheropen]*Vsdh[t+1][spheropen]+T[spherclosed]*Vsdh[t+1][spherclosed]+T[paropen]*Vsdh[t+1][paropen]+T[parclosed]*Vsdh[t+1][parclosed]+T[point]*Vsdh[t+1][point]+T[fist]*Vsdh[t+1][fist]);
	}
//------------- Chose the best way with the function max -------------
/*result_sdh=0;
for (int j=9;j>=0;j--)
{
	if(result_sdh<Vsdh[0][j])		//function max
	{
		result_sdh=Vsdh[0][j];
		//result_sdhstate=j;			// know the state where the value function is the best
	}								// if j=0=home, j=1=cylclosed, j=2=cylopen ,etc...
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
				fit[i]=func(bPos[d][i],Vsdh);

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
						  bNghFit[j]=func(j,Vsdh);

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
					  fit[j]=func(j,Vsdh);

			}	//end iter = imax
			result_sdhstate=bPosSort[0][0];
			std::cout << "sort: " << result_sdhstate << std::endl;
	} // end runs

		cout<<"\n n= "<<n;

		cout<<"      Time/s of Failed are ="<<fail;

		cout<<"\n finished..................\n";
		//std::cout << "bestVsdh: " << result_sdh << std::endl;


	return;
	}
