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
int head_imax=500;
int head_n= pop;  // Number of Scout Bees
int head_m= 2;   // Number of selected Locations
int head_n1 =6;  // Number of Bees around each selected locations ( except the ellit location )
int head_n2 =20;  // Number of Bees around each ellit locations
int head_e =1;   // Elite point/s

int head_func( int i,std::vector<std::vector<float> > Vhead)  // Definition of Fitness Function
{
	int y;
	y=Vhead[0][i];
	return y;
}

//------------------------------random function used in the Bees algorithm-----------------------

int	head_xs = 0;
int	head_xe = 1;
int head_randfunc( int head_xs, int head_xe )  // Definition of Random number Generator Function*/
{
  double randnum;
  randnum=rand() ;
  randnum=head_xs+randnum*(head_xe-head_xs) / RAND_MAX;
  int intrandnum = randnum +0.5;	//kind of rounding in order to have only 0 or 1 random number
  return intrandnum;
}

//------------------------------sorting function used in the Bees algorithm-----------------------

void head_funcSort(int inP1[],int oP1[],int inP2[][pop],int oP2[][pop],int size)
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

void reward_head (std::string action_name, std::string action_stage,std::string result_action, std::vector<std::vector<float> >& Vhead,double& result_head ,int& result_headstate, Eigen::Matrix4f& T)
{
float gamma=0.1;  // define the discount factor "gamma"
int front=0, back=1;
int nav_pre_front=0, detect_pre_front=1,grasp_pre_front=2,put_pre_front=3,nav_post_front=4,detect_post_front=5,grasp_post_front=6,put_post_front=7;
int nav_pre_back=8,detect_pre_back=9,grasp_pre_back=10,put_pre_back=11,nav_post_back=12,detect_post_back=13,grasp_post_back=14,put_post_back=15;
std::vector<float> R;   //create a vector R with an unknown size
	R.resize(16);  // define the size of the vector
//std::vector<float> T;   //create a vector T with an unknown size
//T.resize(2);  // define the size of the vector
Vhead.resize(2);
for (int i=1;i>=0;i--)
{
Vhead[i].resize(2);
}
	//----- initialisation in order to compute the value function -----
						//Vhead[1][0]=R[front];
						//Vhead[1][1]=R[back];

	//----- definition of the reward -----
	R[nav_pre_front]=20;		R[detect_pre_front]=10;		R[grasp_pre_front]=10;	R[put_pre_front]=10;
	R[nav_pre_back]=10;			R[detect_pre_back]=20;		R[grasp_pre_back]=20;	R[put_pre_back]=20;
	R[nav_post_front]=20;		R[detect_post_front]=20;	R[grasp_post_front]=10;	R[put_post_front]=20;
	R[nav_post_back]=10;		R[detect_post_back]=10;		R[grasp_post_back]=20;	R[put_post_back]=10;

	//for (int t=4;t>=0;t--)
	//{
	if (action_name=="navigation")
	{
		if (action_stage=="pre-config")
		{
			Vhead[0][front]=R[nav_pre_front] + gamma*(T(0,0)*R[nav_pre_front]+T(0,1)*R[detect_pre_front]+T(0,2)*R[grasp_pre_front]+T(0,3)*R[put_pre_front]);
			Vhead[0][back]=R[nav_pre_back] + gamma*(T(0,0)*R[nav_pre_back]+T(0,1)*R[detect_pre_back]+T(0,2)*R[grasp_pre_back]+T(0,3)*R[put_pre_back]);
		}
		if (action_stage=="post-config")
		{
			Vhead[0][front]=R[nav_post_front] + gamma*T(0,0)*(R[nav_post_front]+T(0,1)*R[detect_post_front]+T(0,2)*R[grasp_post_front]+T(0,3)*R[put_post_front]);
			Vhead[0][back]=R[nav_post_back] + gamma*(T(0,0)*R[nav_post_back]+T(0,1)*R[detect_post_back]+T(0,2)*R[grasp_post_back]+T(0,3)*R[put_post_back]);
		}
	}
	if (action_name=="detection")
	{
		if (action_stage=="pre-config")
		{
			Vhead[0][front]=R[detect_pre_front] + gamma*(T(1,0)*R[nav_pre_front]+T(1,1)*R[detect_pre_front]+T(1,2)*R[grasp_pre_front]+T(1,3)*R[put_pre_front]);
			Vhead[0][back]=R[detect_pre_back] + gamma*(T(1,0)*R[nav_pre_back]+T(1,1)*R[detect_pre_back]+T(1,2)*R[grasp_pre_back]+T(1,3)*R[put_pre_back]);
		}
		if (action_stage=="post-config")
		{
			Vhead[0][front]=R[detect_post_front] + gamma*T(1,0)*(R[nav_post_front]+T(1,1)*R[detect_post_front]+T(1,2)*R[grasp_post_front]+T(1,3)*R[put_post_front]);
			Vhead[0][back]=R[detect_post_back] + gamma*(T(1,0)*R[nav_post_back]+T(1,1)*R[detect_post_back]+T(1,2)*R[grasp_post_back]+T(1,3)*R[put_post_back]);
		}
	}
	if (action_name=="grasp")
	{
		if (action_stage=="pre-config")
		{
			Vhead[0][front]=R[grasp_pre_front] + gamma*(T(2,0)*R[nav_pre_front]+T(2,1)*R[detect_pre_front]+T(2,2)*R[grasp_pre_front]+T(2,3)*R[put_pre_front]);
			Vhead[0][back]=R[grasp_pre_back] + gamma*(T(2,0)*R[nav_pre_back]+T(2,1)*R[detect_pre_back]+T(2,2)*R[grasp_pre_back]+T(2,3)*R[put_pre_back]);
		}
		if (action_stage=="post-config")
		{
			Vhead[0][front]=R[grasp_post_front] + gamma*T(2,0)*(R[nav_post_front]+T(2,1)*R[detect_post_front]+T(2,2)*R[grasp_post_front]+T(2,3)*R[put_post_front]);
			Vhead[0][back]=R[grasp_post_back] + gamma*(T(2,0)*R[nav_post_back]+T(2,1)*R[detect_post_back]+T(2,2)*R[grasp_post_back]+T(2,3)*R[put_post_back]);
		}
	}
	if (action_name=="put_on_tray")
	{
		if (action_stage=="pre-config")
		{
			Vhead[0][front]=R[put_pre_front] + gamma*(T(3,0)*R[nav_pre_front]+T(3,1)*R[detect_pre_front]+T(3,2)*R[grasp_pre_front]+T(3,3)*R[put_pre_front]);
			Vhead[0][back]=R[put_pre_back] + gamma*(T(3,0)*R[nav_pre_back]+T(3,1)*R[detect_pre_back]+T(3,2)*R[grasp_pre_back]+T(3,3)*R[put_pre_back]);
		}
		if (action_stage=="post-config")
		{
			Vhead[0][front]=R[put_post_front] + gamma*T(3,0)*(R[nav_post_front]+T(3,1)*R[detect_post_front]+T(3,2)*R[grasp_post_front]+T(3,3)*R[put_post_front]);
			Vhead[0][back]=R[put_post_back] + gamma*(T(3,0)*R[nav_post_back]+T(3,1)*R[detect_post_back]+T(3,2)*R[grasp_post_back]+T(3,3)*R[put_post_back]);
		}
	}

//------------- Chose the best way with the function max -------------

/*
	result_head=0;
	for (int j=1;j>=0;j--)
	{
		if(result_head<Vhead[0][j])		//function max
		{
			result_head=Vhead[0][j];
			//result_headstate=j;			// know the state where the value function is the best
		}								// if j=0=front, j=1=back
	}
*/

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

//---------------initialisation with random start positions at the start of every run------------------

			for(int i=0;i<head_n;i++)
			{
				for(int d=0;d<dim;d++)
				{
				bPos[d][i]= head_randfunc(head_xs, head_xe);
				fit[i]=head_func(bPos[d][i], Vhead);
				}
			}

			// at this point bPos contains a number of randomly initialised particles
			// fit, contains the value of the fit350000ness function
			// thus forming a (fit,bPos) tuple

			//sort by fitness, preserving the (fit,bpos) tuple
			head_funcSort(fit, sortedFit, bPos, bPosSort, head_n); // bpossort contains all the sort position of the scout bees
			fit[bPosSort[0][0]]=head_func(bPosSort[0][0], Vhead);

			//head_imax number of iteration
			for(int iter=0; iter<head_imax ;iter++)
			{
				for(int d=0;d<dim;d++)
					nghx[d] = 1;

				int aa[50]; //50 max number of selected sites out of n

					 for(int i=0;i<head_m;i++)
					 {
					   if(i<head_e)
						   aa[i]=head_n2;  // Number of bees around each elite point
					   else
						   aa[i]=head_n1;  // Number of bees around other selected point
					   }

	// ----------------------------------------Neighbourhood search  ------------------------------------

				temp1=-INT_MAX;

				for(int k=0;k<head_e;k++)//k site
				{
					for(int j=0;j<aa[k];j++) //j recruited bee
					{
						for(int d=0;d<dim;d++)//d dimension
						{
							candidx[d][k]=bPosSort[d][k]; //define the candidate position
							if ((candidx[d][k]-nghx[d])<head_xs) // boundry check (left)
								{
								 bNghPos[d][j]=head_randfunc(head_xs,candidx[d][k]+nghx[d]);
								 bNghFit[j]=head_func(bNghPos[d][j], Vhead);
								}
							if ((candidx[d][k]+nghx[d])>head_xe)// boundry check (right)
								{
								bNghPos[d][j]=head_randfunc(candidx[d][k]-nghx[d],head_xe);
								bNghFit[j]=head_func(bNghPos[d][j], Vhead);
								}
							if ((candidx[d][k]-nghx[d])>=head_xs and (candidx[d][k]+nghx[d])<=head_xe )
								{
								bNghPos[d][j]=head_randfunc(candidx[d][k]-nghx[d] , candidx[d][k]+nghx[d]);
								bNghFit[j]=head_func(bNghPos[d][j], Vhead);
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

	// ----------------------------------------Global search  ------------------------------------

				int ranSearchBees=head_n-head_m; // Number of bees search randomly
				for(int k=0;k<ranSearchBees;k++)	//start of random search for rest of bees
					 {
						for(int d=0;d<dim;d++)
						{
							globalPos[d][k]=head_randfunc(head_xs, head_xe);
							globalFit[k]=head_func(globalPos[d][k], Vhead);// evaluate the fitness of the new list
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
			std::cout << "best head pos: " << result_headstate << std::endl;
			std::cout << "best head Vfit: " << result_head << std::endl;

			return;
	}
