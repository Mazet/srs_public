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
#define pop  50		// max num of population
int imax=500;
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

//------------------------------random function used in the Bees algorithm-----------------------

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

//------------------------------sorting function used in the Bees algorithm-----------------------

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

//------------------------------ reward function -----------------------

void reward_tray (std::string action_name, std::string action_stage, std::string result_action, std::vector<std::vector<float> >& Vtray,double& result_tray ,int& result_traystate, Eigen::Matrix4f& T)
{
float gamma=0.1;  // define the discount factor "gamma"
	int up=0, down=1;
	int nav_pre_up=0, detect_pre_up=1,grasp_pre_up=2,put_pre_up=3,nav_post_up=4,detect_post_up=5,grasp_post_up=6,put_post_up=7;
	int nav_pre_down=8,detect_pre_down=9,grasp_pre_down=10,put_pre_down=11,nav_post_down=12,detect_post_down=13,grasp_post_down=14,put_post_down=15;
	std::vector<float> R;   //create a vector R with an unknown size
		R.resize(16);  // define the size of the vector
	Vtray.resize(2);
	for (int i=1;i>=0;i--)
	{
	Vtray[i].resize(2);
	}

//----- initialisation in order to compute the value function ----- need this part only if more than 1 next action is known
					//Vtray[1][0]=R[up];
					//Vtray[1][1]=R[down];
//----- definition of the reward -----
	R[nav_pre_up]=5;		R[detect_pre_up]=5;			R[grasp_pre_up]=5;		R[put_pre_up]=100;
	R[nav_pre_down]=100;	R[detect_pre_down]=100;		R[grasp_pre_down]=100;	R[put_pre_down]=1;
	R[nav_post_up]=5;		R[detect_post_up]=5;		R[grasp_post_up]=6;		R[put_post_up]=100;
	R[nav_post_down]=100;	R[detect_post_down]=100;	R[grasp_post_down]=5;	R[put_post_down]=1;

			if (action_name=="navigation")
			{
				if (action_stage=="pre-config")
				{
					//Vtray[0][up]=R[nav_pre_up] + gamma*(T(0,0)*(R[nav_pre_up]+R[nav_pre_down])+T(0,1)*(R[detect_pre_up]+R[detect_pre_down])+T(0,2)*(R[grasp_pre_up]+R[grasp_pre_down])+T(0,3)*(R[put_pre_up]+R[put_pre_down]));
					//Vtray[0][down]=R[nav_pre_down] + gamma*(T(0,0)*(R[nav_pre_up]+R[nav_pre_down])+T(0,1)*(R[detect_pre_up]+R[detect_pre_down])+T(0,2)*(R[grasp_pre_up]+R[grasp_pre_down])+T(0,3)*(R[put_pre_up]+R[put_pre_down]));
					Vtray[0][up]=R[nav_pre_up] + gamma*(T(0,0)*R[nav_pre_up]+T(0,1)*R[detect_pre_up]+T(0,2)*R[grasp_pre_up]+T(0,3)*R[put_pre_up]);
					Vtray[0][down]=R[nav_pre_down] + gamma*(T(0,0)*R[nav_pre_down]+T(0,1)*R[detect_pre_down]+T(0,2)*R[grasp_pre_down]+T(0,3)*R[put_pre_down]);
				}
				if (action_stage=="post-config")
				{
					//Vtray[0][up]=R[nav_post_up] + gamma*(T(0,0)*(R[nav_post_up]+R[nav_post_down])+T(0,1)*(R[detect_post_up]+R[detect_post_down])+T(0,2)*(R[grasp_post_up]+R[grasp_post_down])+T(0,3)*(R[put_post_up]+R[put_post_down]));
					//Vtray[0][down]=R[nav_post_down] + gamma*(T(0,0)*(R[nav_post_up]+R[nav_post_down])+T(0,1)*(R[detect_post_up]+R[detect_post_down])+T(0,2)*(R[grasp_post_up]+R[grasp_post_down])+T(0,3)*(R[put_post_up]+R[put_post_down]));
					Vtray[0][up]=R[nav_post_up] + gamma*(T(0,0)*R[nav_post_up]+T(0,1)*R[detect_post_up]+T(0,2)*R[grasp_post_up]+T(0,3)*R[put_post_up]);
					Vtray[0][down]=R[nav_post_down] + gamma*(T(0,0)*R[nav_post_down]+T(0,1)*R[detect_post_down]+T(0,2)*R[grasp_post_down]+T(0,3)*R[put_post_down]);
				}
			}
			if (action_name=="detection")
			{
				if (action_stage=="pre-config")
				{
					//Vtray[0][up]=R[detect_pre_up] + gamma*(T(1,0)*(R[nav_pre_up]+R[nav_pre_down])+T(1,1)*(R[detect_pre_up]+R[detect_pre_down])+T(1,2)*(R[grasp_pre_up]+R[grasp_pre_down])+T(1,3)*(R[put_pre_up]+R[put_pre_down]));
					//Vtray[0][down]=R[detect_pre_down] + gamma*(T(1,0)*(R[nav_pre_up]+R[nav_pre_down])+T(1,1)*(R[detect_pre_up]+R[detect_pre_down])+T(1,2)*(R[grasp_pre_up]+R[grasp_pre_down])+T(1,3)*(R[put_pre_up]+R[put_pre_down]));
					Vtray[0][up]=R[detect_pre_up] + gamma*(T(1,0)*R[nav_pre_up]+T(1,1)*R[detect_pre_up]+T(1,2)*R[grasp_pre_up]+T(1,3)*R[put_pre_up]);
					Vtray[0][down]=R[detect_pre_down] + gamma*(T(1,0)*R[nav_pre_down]+T(1,1)*R[detect_pre_down]+T(1,2)*R[grasp_pre_down]+T(1,3)*R[put_pre_down]);
				}
				if (action_stage=="post-config")
				{
					//Vtray[0][up]=R[detect_post_up] + gamma*(T(1,0)*(R[nav_post_up]+R[nav_post_down])+T(1,1)*(R[detect_post_up]+R[detect_post_down])+T(1,2)*(R[grasp_post_up]+R[grasp_post_down])+T(1,3)*(R[put_post_up]+R[put_post_down]));
					//Vtray[0][down]=R[detect_post_down] + gamma*(T(1,0)*(R[nav_post_up]+R[nav_post_down])+T(1,1)*(R[detect_post_up]+R[detect_post_down])+T(1,2)*(R[grasp_post_up]+R[grasp_post_down])+T(1,3)*(R[put_post_up]+R[put_post_down]));
					Vtray[0][up]=R[detect_post_up] + gamma*(T(1,0)*R[nav_post_up]+T(1,1)*R[detect_post_up]+T(1,2)*R[grasp_post_up]+T(1,3)*R[put_post_up]);
					Vtray[0][down]=R[detect_post_down] + gamma*(T(1,0)*R[nav_post_down]+T(1,1)*R[detect_post_down]+T(1,2)*R[grasp_post_down]+T(1,3)*R[put_post_down]);
				}
			}
			if (action_name=="grasp")
			{
				if (action_stage=="pre-config")
				{
					//Vtray[0][up]=R[grasp_pre_up] + gamma*(T(2,0)*(R[nav_pre_up]+R[nav_pre_down])+T(2,1)*(R[detect_pre_up]+R[detect_pre_down])+T(2,2)*(R[grasp_pre_up]+R[grasp_pre_down])+T(2,3)*(R[put_pre_up]+R[put_pre_down]));
					//Vtray[0][down]=R[grasp_pre_down] + gamma*(T(2,0)*(R[nav_pre_up]+R[nav_pre_down])+T(2,1)*(R[detect_pre_up]+R[detect_pre_down])+T(2,2)*(R[grasp_pre_up]+R[grasp_pre_down])+T(2,3)*(R[put_pre_up]+R[put_pre_down]));
					Vtray[0][up]=R[grasp_pre_up] + gamma*(T(2,0)*R[nav_pre_up]+T(2,1)*R[detect_pre_up]+T(2,2)*R[grasp_pre_up]+T(3,3)*R[put_pre_up]);
					Vtray[0][down]=R[grasp_pre_down] + gamma*(T(2,0)*R[nav_pre_down]+T(2,1)*R[detect_pre_down]+T(2,2)*R[grasp_pre_down]+T(3,3)*R[put_pre_down]);
				}
				if (action_stage=="post-config")
				{
					//Vtray[0][up]=R[grasp_post_up] + gamma*(T(2,0)*(R[nav_post_up]+R[nav_post_down])+T(2,1)*(R[detect_post_up]+R[detect_post_down])+T(2,2)*(R[grasp_post_up]+R[grasp_post_down])+T(2,3)*(R[put_post_up]+R[put_post_down]));
					//Vtray[0][down]=R[grasp_post_down] + gamma*(T(2,0)*(R[nav_post_up]+R[nav_post_down])+T(2,1)*(R[detect_post_up]+R[detect_post_down])+T(2,2)*(R[grasp_post_up]+R[grasp_post_down])+T(2,3)*(R[put_post_up]+R[put_post_down]));
					Vtray[0][up]=R[grasp_post_up] + gamma*(T(2,0)*R[nav_post_up]+T(2,1)*R[detect_post_up]+T(2,2)*R[grasp_post_up]+T(2,3)*R[put_post_up]);
					Vtray[0][down]=R[grasp_post_down] + gamma*(T(2,0)*R[nav_post_down]+T(2,1)*R[detect_post_down]+T(2,2)*R[grasp_post_down]+T(2,3)*R[put_post_down]);
				}
			}
			if (action_name=="put_on_tray")
			{
				if (action_stage=="pre-config")
				{
					//Vtray[0][up]=R[put_pre_up] + gamma*(T(3,0)*(R[nav_pre_up]+R[nav_pre_down])+T(3,1)*(R[detect_pre_up]+R[detect_pre_down])+T(3,2)*(R[grasp_pre_up]+R[grasp_pre_down])+T(3,3)*(R[put_pre_up]+R[put_pre_down]));
					//Vtray[0][down]=R[put_pre_down] + gamma*(T(3,0)*(R[nav_pre_up]+R[nav_pre_down])+T(3,1)*(R[detect_pre_up]+R[detect_pre_down])+T(3,2)*(R[grasp_pre_up]+R[grasp_pre_down])+T(3,3)*(R[put_pre_up]+R[put_pre_down]));
					Vtray[0][up]=R[put_pre_up] + gamma*(T(3,0)*R[nav_pre_up]+T(3,1)*R[detect_pre_up]+T(3,2)*R[grasp_pre_up]+T(3,3)*R[put_pre_up]);
					Vtray[0][down]=R[put_pre_down] + gamma*(T(3,0)*R[nav_pre_down]+T(3,1)*R[detect_pre_down]+T(3,2)*R[grasp_pre_down]+T(3,3)*R[put_pre_down]);
				}
				if (action_stage=="post-config")
				{
					//Vtray[0][up]=R[put_post_up] + gamma*(T(3,0)*(R[nav_post_up]+R[nav_post_down])+T(3,1)*(R[detect_post_up]+R[detect_post_down])+T(3,2)*(R[grasp_post_up]+R[grasp_post_down])+T(3,3)*(R[put_post_up]+R[put_post_down]));
					//Vtray[0][down]=R[put_post_down] + gamma*(T(3,0)*(R[nav_post_up]+R[nav_post_down])+T(3,1)*(R[detect_post_up]+R[detect_post_down])+T(3,2)*(R[grasp_post_up]+R[grasp_post_down])+T(3,3)*(R[put_post_up]+R[put_post_down]));
					Vtray[0][up]=R[put_post_up] + gamma*(T(3,0)*R[nav_post_up]+T(3,1)*R[detect_post_up]+T(3,2)*R[grasp_post_up]+T(3,3)*R[put_post_up]);
					Vtray[0][down]=R[put_post_down] + gamma*(T(3,0)*R[nav_post_down]+T(3,1)*R[detect_post_down]+T(3,2)*R[grasp_post_down]+T(3,3)*R[put_post_down]);
				}
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

//------------- Chose the best way with the Bees Algorithm-------------
		int temp2;
		double temp1 ;
		int nghx[dim]; // Neighborhood X[]-Direction ( m )
		int fit[pop],sortedFit[pop],bPos[dim][pop],bPosSort[dim][pop];
		int bNghFit[pop],bNghPos[dim][pop];
		int globalFit[pop], globalPos[dim][pop];
		int candidx[dim][pop];

		srand( (unsigned)time( NULL ) );

		for(int runs=0; runs<1; runs++)
		{	//number of runs
			//initialise with random start positions at the start of every run
			for(int i=0;i<n;i++)
			{
				for(int d=0;d<dim;d++)
				{
				bPos[d][i]= randfunc(xs, xe);
				//std::cout << "bpos " << bPos[d][i] << std::endl;
				fit[i]=func(bPos[d][i], Vtray);
				//std::cout << "fit: " << fit[i] << std::endl;
				}
			}

			// at this point bPos contains a number of randomly initialised particles
			// fit, contains the value of the fit350000ness function
			// thus forming a (fit,bPos) tuple

			//sort by fitness, preserving the (f,pos) tuple
			funcSort(fit, sortedFit, bPos, bPosSort, n); // bpossort contains all the sort position of the scout bees
			fit[bPosSort[0][0]]=func(bPosSort[0][0], Vtray);
			//std::cout << "bpossort: " << bPosSort[0][0] << std::endl;
			//std::cout << "fit: " << fit[bPosSort[0][0]] << std::endl;

			//imax number of iteration
			for(int iter=0; iter<imax ;iter++)
			{
				for(int d=0;d<dim;d++)
					nghx[d] = 1;

				int aa[50]; //50 max number of selected sites out of n

					 for(int i=0;i<m;i++)
					 {
					   if(i<e)
						   aa[i]=n2;  // Number of bees around each elite point
					   else
						   aa[i]=n1;  // Number of bees around other selected point
					   }

	// ----------------------------------------Neighbourhood search  ------------------------------------

				temp1=-INT_MAX;

				for(int k=0;k<m;k++)//k site
				{
					for(int j=0;j<aa[k];j++) //j recruited bee
					{
						for(int d=0;d<dim;d++)//d dimension
						{
							candidx[d][k]=bPosSort[d][k]; //define the candidate position
							//std::cout << "candid: " << candidx[d][k] << std::endl;
							if ((candidx[d][k]-nghx[d])<xs) // boundry check (left)
								{
								 bNghPos[d][j]=randfunc(xs,candidx[d][k]+nghx[d]);
								//std::cout << "bNghPos1: " << bNghPos[d][j] << std::endl;
								bNghFit[j]=func(bNghPos[d][j], Vtray);
								//std::cout << "bNghFit: " << bNghFit[j] << std::endl;
								}
							if ((candidx[d][k]+nghx[d])>xe)// boundry check (right)
								{
								bNghPos[d][j]=randfunc(candidx[d][k]-nghx[d],xe);
								//std::cout << "bNghPos2: " << bNghPos[d][j] << std::endl;
								bNghFit[j]=func(bNghPos[d][j], Vtray);
								//std::cout << "bNghFit: " << bNghFit[j] << std::endl;
								}
							if ((candidx[d][k]-nghx[d])>=xs and (candidx[d][k]+nghx[d])<=xe )
								{
								bNghPos[d][j]=randfunc(candidx[d][k]-nghx[d] , candidx[d][k]+nghx[d]);
								//std::cout << "bNghPos3: " << bNghPos[d][j] << std::endl;
								bNghFit[j]=func(bNghPos[d][j], Vtray);
								//std::cout << "bNghFit: " << bNghFit[j] << std::endl;
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
			//std::cout << "temp1: " <<temp1 << std::endl;
			//std::cout << "temp2: " <<temp2 << std::endl;

	// ----------------------------------------Global search  ------------------------------------

				int ranSearchBees=n-m; // Number of bees search randomly
				for(int k=0;k<ranSearchBees;k++)	//start of random search for rest of bees
					 {
						for(int d=0;d<dim;d++)
						{
							globalPos[d][k]=randfunc(xs, xe);
							//std::cout << "bposglobal " << globalPos[d][k] << std::endl;
							globalFit[k]=func(globalPos[d][k], Vtray);// evaluate the fitness of the new list
							//std::cout << "fitglobal: " << globalFit[k] << std::endl;
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

			result_traystate=bPosSort[0][0]; //bPosSort[0][0] correspond to the elite site
			result_tray = sortedFit[0]; // sortedFit[0] correspond to the value of the elite site
			std::cout << "best tray pos: " << result_traystate << std::endl;
			std::cout << "best tray Vfit: " << result_tray << std::endl;

			return;
	}
