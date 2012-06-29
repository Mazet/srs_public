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
int torso_imax=500;
int torso_n= pop;  // Number of Scout Bees
int torso_m= 2;   // Number of selected Locations
int torso_n1 =6;  // Number of Bees around each selected locations ( except the ellit location )
int torso_n2 =20;  // Number of Bees around each ellit locations
int torso_e =1;   // Elite point/s

int torso_func( int i,std::vector<std::vector<float> > Vtorso)  // Definition of Fitness Function
{
	int y;
	y=Vtorso[0][i];
	  return y;
}

//------------------------------random function used in the Bees algorithm-----------------------

int	torso_xs = 0;
int	torso_xe = 15;
int torso_randfunc( int torso_xs, int torso_xe )  // Definition of Random number Generator Function*/
{
  double randnum;
  randnum=rand() ;
  randnum=torso_xs+randnum*(torso_xe-torso_xs) / RAND_MAX;
  int intrandnum = randnum +0.5;	//kind of rounding in order to have only 0 or 1 random number
  return intrandnum;
}

//------------------------------sorting function used in the Bees algorithm-----------------------

void torso_funcSort(int inP1[],int oP1[],int inP2[][pop],int oP2[][pop],int size)
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

void reward_torso (std::string action_name, std::string action_stage, std::string result_action, std::vector<std::vector<float> >& Vtorso,double& result_torso ,int& result_torsostate,Eigen::Matrix4f& T)
{
float gamma=0.1;  // define the discount factor "gamma"
	int home=0, left=1, right=2, front=3,front_left=4, front_right=5,back=6,back_extreme=7,back_left=8,back_left_extreme=9, back_right=10,back_right_extreme=11,nod=12,lookontray=13,bow=14,shake=15;
	int nav_pre_home=0,nav_pre_left=1,nav_pre_right=2,nav_pre_front=3,nav_pre_front_left=4,nav_pre_front_right=5,nav_pre_back=6,nav_pre_back_extreme=7,nav_pre_back_left=8,nav_pre_back_left_extreme=9,nav_pre_back_right=10,nav_pre_back_right_extreme=11,nav_pre_lookontray=12;
	int detect_pre_home=13,detect_pre_left=14,detect_pre_right=15,detect_pre_front=16,detect_pre_front_left=17,detect_pre_front_right=18,detect_pre_back=19,detect_pre_back_extreme=20,detect_pre_back_left=21,detect_pre_back_left_extreme=22,detect_pre_back_right=23,detect_pre_back_right_extreme=24,detect_pre_lookontray=25;
	int grasp_pre_home=26,grasp_pre_left=27,grasp_pre_right=28,grasp_pre_front=29,grasp_pre_front_left=30,grasp_pre_front_right=31,grasp_pre_back=32,grasp_pre_back_extreme=33,grasp_pre_back_left=34,grasp_pre_back_left_extreme=35,grasp_pre_back_right=36,grasp_pre_back_right_extreme=37,grasp_pre_lookontray=38;
	int put_pre_home=39,put_pre_left=40,put_pre_right=41,put_pre_front=42,put_pre_front_left=43,put_pre_front_right=44,put_pre_back=45,put_pre_back_extreme=46,put_pre_back_left=47,put_pre_back_left_extreme=48,put_pre_back_right=49,put_pre_back_right_extreme=50,put_pre_lookontray=51;
	int nav_post_home=52,nav_post_left=53,nav_post_right=54,nav_post_front=55,nav_post_front_left=56,nav_post_front_right=57,nav_post_back=58,nav_post_back_extreme=59,nav_post_back_left=60,nav_post_back_left_extreme=61,nav_post_back_right=62,nav_post_back_right_extreme=63,nav_post_lookontray=64;
	int detect_post_home=65,detect_post_left=66,detect_post_right=67,detect_post_front=68,detect_post_front_left=69,detect_post_front_right=70,detect_post_back=71,detect_post_back_extreme=72,detect_post_back_left=73,detect_post_back_left_extreme=74,detect_post_back_right=75,detect_post_back_right_extreme=76,detect_post_lookontray=77;
	int grasp_post_home=78,grasp_post_left=79,grasp_post_right=80,grasp_post_front=81,grasp_post_front_left=82,grasp_post_front_right=83,grasp_post_back=84,grasp_post_back_extreme=85,grasp_post_back_left=86,grasp_post_back_left_extreme=87,grasp_post_back_right=88,grasp_post_back_right_extreme=89,grasp_post_lookontray=90;
	int put_post_home=91,put_post_left=92,put_post_right=93,put_post_front=94,put_post_front_left=95,put_post_front_right=96,put_post_back=97,put_post_back_extreme=98,put_post_back_left=99,put_post_back_left_extreme=100,put_post_back_right=101,put_post_back_right_extreme=102,put_post_lookontray=103;

	std::vector<float> R;   //create a vector R with an unknown size
		R.resize(104);  // define the size of the vector
	Vtorso.resize(2);
	for (int i=1;i>=0;i--)
	{
	Vtorso[i].resize(16);
	}

/*	//----- initialisation in order to compute the value function -----
				Vtorso[5][0]=R[home];
				Vtorso[5][1]=R[left];
				Vtorso[5][2]=R[right];
				Vtorso[5][3]=R[front];
				Vtorso[5][4]=R[front_left];
				Vtorso[5][5]=R[front_right];
				Vtorso[5][6]=R[back];
				Vtorso[5][7]=R[back_extreme];
				Vtorso[5][8]=R[back_left];
				Vtorso[5][9]=R[back_left_extreme];
				Vtorso[5][10]=R[back_right];
				Vtorso[5][11]=R[back_right_extreme];
				Vtorso[5][12]=R[nod];
				Vtorso[5][13]=R[lookontray];
				Vtorso[5][14]=R[bow];
				Vtorso[5][15]=R[shake];*/
	//for (int t=4;t>=0;t--)
		//{

	//----- definition of the reward -----
				R[nav_pre_home]=20;					R[detect_pre_home]=20;					R[grasp_pre_home]=20;				R[put_pre_home]=20;
				R[nav_pre_left]=8;					R[detect_pre_left]=2;					R[grasp_pre_left]=3;				R[put_pre_left]=2;
				R[nav_pre_right]=3;					R[detect_pre_right]=5;					R[grasp_pre_right]=4;				R[put_pre_right]=4;
				R[nav_pre_front]=4;					R[detect_pre_front]=7;					R[grasp_pre_front]=7;				R[put_pre_front]=6;
				R[nav_pre_front_left]=6;			R[detect_pre_front_left]=9;				R[grasp_pre_front_left]=5;			R[put_pre_front_left]=8;
				R[nav_pre_front_right]=2;			R[detect_pre_front_right]=4;			R[grasp_pre_front_right]=6;			R[put_pre_front_right]=10;
				R[nav_pre_back]=9;					R[detect_pre_back]=6;					R[grasp_pre_back]=4;				R[put_pre_back]=8;
				R[nav_pre_back_extreme]=5;			R[detect_pre_back_extreme]=12;			R[grasp_pre_back_extreme]=3;		R[put_pre_back_extreme]=6;
				R[nav_pre_back_left]=7;				R[detect_pre_back_left]=1;				R[grasp_pre_back_left]=1;			R[put_pre_back_left]=4;
				R[nav_pre_back_left_extreme]=1;		R[detect_pre_back_left_extreme]=2;		R[grasp_pre_back_left_extreme]=2;	R[put_pre_back_left_extreme]=2;
				R[nav_pre_back_right]=6;			R[detect_pre_back_right]=3;				R[grasp_pre_back_right]=6;			R[put_pre_back_right]=1;
				R[nav_pre_back_right_extreme]=7;	R[detect_pre_back_right_extreme]=4;		R[grasp_pre_back_right_extreme]=5;	R[put_pre_back_right_extreme]=5;
				R[nav_pre_lookontray]=6;			R[detect_pre_lookontray]=7;				R[grasp_pre_lookontray]=3;			R[put_pre_lookontray]=3;

				R[nav_post_home]=20;				R[detect_post_home]=20;					R[grasp_post_home]=20;				R[put_post_home]=20;
				R[nav_post_left]=2;					R[detect_post_left]=2;					R[grasp_post_left]=4;				R[put_post_left]=1;
				R[nav_post_right]=1;				R[detect_post_right]=3;					R[grasp_post_right]=2;				R[put_post_right]=8;
				R[nav_post_front]=3;				R[detect_post_front]=4;					R[grasp_post_front]=1;				R[put_post_front]=6;
				R[nav_post_front_left]=5;			R[detect_post_front_left]=5;			R[grasp_post_front_left]=3;			R[put_post_front_left]=4;
				R[nav_post_front_right]=8;			R[detect_post_front_right]=6;			R[grasp_post_front_right]=7;		R[put_post_front_right]=2;
				R[nav_post_back]=3;					R[detect_post_back]=7;					R[grasp_post_back]=6;				R[put_post_back]=1;
				R[nav_post_back_extreme]=4;			R[detect_post_back_extreme]=7;			R[grasp_post_back_extreme]=3;		R[put_post_back_extreme]=3;
				R[nav_post_back_left]=5;			R[detect_post_back_left]=6;				R[grasp_post_back_left]=4;			R[put_post_back_left]=6;
				R[nav_post_back_left_extreme]=2;	R[detect_post_back_left_extreme]=1;		R[grasp_post_back_left_extreme]=2;	R[put_post_back_left_extreme]=9;
				R[nav_post_back_right]=8;			R[detect_post_back_right]=1;			R[grasp_post_back_right]=3;			R[put_post_back_right]=1;
				R[nav_post_back_right_extreme]=4;	R[detect_post_back_right_extreme]=2;	R[grasp_post_back_right_extreme]=1;	R[put_post_back_right_extreme]=6;
				R[nav_post_lookontray]=6;			R[detect_post_lookontray]=4;			R[grasp_post_lookontray]=2;			R[put_post_lookontray]=4;

			if (action_name=="navigation")
			{
				if (action_stage=="pre-config")
				{
					Vtorso[0][home]=R[nav_pre_home] + gamma*(T(0,0)*R[nav_pre_home]+T(0,1)*R[detect_pre_home]+T(0,2)*R[grasp_pre_home]+T(0,3)*R[put_pre_home]);
					Vtorso[0][left]=R[nav_pre_left] + gamma*(T(0,0)*R[nav_pre_left]+T(0,1)*R[detect_pre_left]+T(0,2)*R[grasp_pre_left]+T(0,3)*R[put_pre_left]);
					Vtorso[0][right]=R[nav_pre_right] + gamma*(T(0,0)*R[nav_pre_right]+T(0,1)*R[detect_pre_right]+T(0,2)*R[grasp_pre_right]+T(0,3)*R[put_pre_right]);
					Vtorso[0][front]=R[nav_pre_front] + gamma*(T(0,0)*R[nav_pre_front]+T(0,1)*R[detect_pre_front]+T(0,2)*R[grasp_pre_front]+T(0,3)*R[put_pre_front]);
					Vtorso[0][front_left]=R[nav_pre_front_left] + gamma*(T(0,0)*R[nav_pre_front_left]+T(0,1)*R[detect_pre_front_left]+T(0,2)*R[grasp_pre_front_left]+T(0,3)*R[put_pre_front_left]);
					Vtorso[0][front_right]=R[nav_pre_front_right] + gamma*(T(0,0)*R[nav_pre_front_right]+T(0,1)*R[detect_pre_front_right]+T(0,2)*R[grasp_pre_front_right]+T(0,3)*R[put_pre_front_right]);
					Vtorso[0][back]=R[nav_pre_back] + gamma*(T(0,0)*R[nav_pre_back]+T(0,1)*R[detect_pre_back]+T(0,2)*R[grasp_pre_back]+T(0,3)*R[put_pre_back]);
					Vtorso[0][back_extreme]=R[nav_pre_back_extreme] + gamma*(T(0,0)*R[nav_pre_back_extreme]+T(0,1)*R[detect_pre_back_extreme]+T(0,2)*R[grasp_pre_back_extreme]+T(0,3)*R[put_pre_back_extreme]);
					Vtorso[0][back_left]=R[nav_pre_back_left] + gamma*(T(0,0)*R[nav_pre_back_left]+T(0,1)*R[detect_pre_back_left]+T(0,2)*R[grasp_pre_back_left]+T(0,3)*R[put_pre_back_left]);
					Vtorso[0][back_left_extreme]=R[nav_pre_back_left_extreme] + gamma*(T(0,0)*R[nav_pre_back_left_extreme]+T(0,1)*R[detect_pre_back_left_extreme]+T(0,2)*R[grasp_pre_back_left_extreme]+T(0,3)*R[put_pre_back_left_extreme]);
					Vtorso[0][back_right]=R[nav_pre_back_right] + gamma*(T(0,0)*R[nav_pre_back_right]+T(0,1)*R[detect_pre_back_right]+T(0,2)*R[grasp_pre_back_right]+T(0,3)*R[put_pre_back_right]);
					Vtorso[0][back_right_extreme]=R[nav_pre_back_right_extreme] + gamma*(T(0,0)*R[nav_pre_back_right_extreme]+T(0,1)*R[detect_pre_back_right_extreme]+T(0,2)*R[grasp_pre_back_right_extreme]+T(0,3)*R[put_pre_back_right_extreme]);
					Vtorso[0][lookontray]=R[nav_pre_lookontray] + gamma*(T(0,0)*R[nav_pre_lookontray]+T(0,1)*R[detect_pre_lookontray]+T(0,2)*R[grasp_pre_lookontray]+T(0,3)*R[put_pre_lookontray]);
				}
				if (action_stage=="post-config")
				{
					Vtorso[0][home]=R[nav_post_home] + gamma*(T(0,0)*R[nav_post_home]+T(0,1)*R[detect_post_home]+T(0,2)*R[grasp_post_home]+T(0,3)*R[put_post_home]);
					Vtorso[0][left]=R[nav_post_left] + gamma*(T(0,0)*R[nav_post_left]+T(0,1)*R[detect_post_left]+T(0,2)*R[grasp_post_left]+T(0,3)*R[put_post_left]);
					Vtorso[0][right]=R[nav_post_right] + gamma*(T(0,0)*R[nav_post_right]+T(0,1)*R[detect_post_right]+T(0,2)*R[grasp_post_right]+T(0,3)*R[put_post_right]);
					Vtorso[0][front]=R[nav_post_front] + gamma*(T(0,0)*R[nav_post_front]+T(0,1)*R[detect_post_front]+T(0,2)*R[grasp_post_front]+T(0,3)*R[put_post_front]);
					Vtorso[0][front_left]=R[nav_post_front_left] + gamma*(T(0,0)*R[nav_post_front_left]+T(0,1)*R[detect_post_front_left]+T(0,2)*R[grasp_post_front_left]+T(0,3)*R[put_post_front_left]);
					Vtorso[0][front_right]=R[nav_post_front_right] + gamma*(T(0,0)*R[nav_post_front_right]+T(0,1)*R[detect_post_front_right]+T(0,2)*R[grasp_post_front_right]+T(0,3)*R[put_post_front_right]);
					Vtorso[0][back]=R[nav_post_back] + gamma*(T(0,0)*R[nav_post_back]+T(0,1)*R[detect_post_back]+T(0,2)*R[grasp_post_back]+T(0,3)*R[put_post_back]);
					Vtorso[0][back_extreme]=R[nav_post_back_extreme] + gamma*(T(0,0)*R[nav_post_back_extreme]+T(0,1)*R[detect_post_back_extreme]+T(0,2)*R[grasp_post_back_extreme]+T(0,3)*R[put_post_back_extreme]);
					Vtorso[0][back_left]=R[nav_post_back_left] + gamma*(T(0,0)*R[nav_post_back_left]+T(0,1)*R[detect_post_back_left]+T(0,2)*R[grasp_post_back_left]+T(0,3)*R[put_post_back_left]);
					Vtorso[0][back_left_extreme]=R[nav_post_back_left_extreme] + gamma*(T(0,0)*R[nav_post_back_left_extreme]+T(0,1)*R[detect_post_back_left_extreme]+T(0,2)*R[grasp_post_back_left_extreme]+T(0,3)*R[put_post_back_left_extreme]);
					Vtorso[0][back_right]=R[nav_post_back_right] + gamma*(T(0,0)*R[nav_post_back_right]+T(0,1)*R[detect_post_back_right]+T(0,2)*R[grasp_post_back_right]+T(0,3)*R[put_post_back_right]);
					Vtorso[0][back_right_extreme]=R[nav_post_back_right_extreme] + gamma*(T(0,0)*R[nav_post_back_right_extreme]+T(0,1)*R[detect_post_back_right_extreme]+T(0,2)*R[grasp_post_back_right_extreme]+T(0,3)*R[put_post_back_right_extreme]);
					Vtorso[0][lookontray]=R[nav_post_lookontray] + gamma*(T(0,0)*R[nav_post_lookontray]+T(0,1)*R[detect_post_lookontray]+T(0,2)*R[grasp_post_lookontray]+T(0,3)*R[put_post_lookontray]);
				}
			}
			if (action_name=="detection")
			{
				if (action_stage=="pre-config")
				{
					Vtorso[0][home]=R[detect_pre_home] + gamma*(T(1,0)*R[nav_pre_home]+T(1,1)*R[detect_pre_home]+T(1,2)*R[grasp_pre_home]+T(1,3)*R[put_pre_home]);
					Vtorso[0][left]=R[detect_pre_left] + gamma*(T(1,0)*R[nav_pre_left]+T(1,1)*R[detect_pre_left]+T(1,2)*R[grasp_pre_left]+T(1,3)*R[put_pre_left]);
					Vtorso[0][right]=R[detect_pre_right] + gamma*(T(1,0)*R[nav_pre_right]+T(1,1)*R[detect_pre_right]+T(1,2)*R[grasp_pre_right]+T(1,3)*R[put_pre_right]);
					Vtorso[0][front]=R[detect_pre_front] + gamma*(T(1,0)*R[nav_pre_front]+T(1,1)*R[detect_pre_front]+T(1,2)*R[grasp_pre_front]+T(1,3)*R[put_pre_front]);
					Vtorso[0][front_left]=R[detect_pre_front_left] + gamma*(T(1,0)*R[nav_pre_front_left]+T(1,1)*R[detect_pre_front_left]+T(1,2)*R[grasp_pre_front_left]+T(1,3)*R[put_pre_front_left]);
					Vtorso[0][front_right]=R[detect_pre_front_right] + gamma*(T(1,0)*R[nav_pre_front_right]+T(1,1)*R[detect_pre_front_right]+T(1,2)*R[grasp_pre_front_right]+T(1,3)*R[put_pre_front_right]);
					Vtorso[0][back]=R[detect_pre_back] + gamma*(T(1,0)*R[nav_pre_back]+T(1,1)*R[detect_pre_back]+T(1,2)*R[grasp_pre_back]+T(1,3)*R[put_pre_back]);
					Vtorso[0][back_extreme]=R[detect_pre_back_extreme] + gamma*(T(1,0)*R[nav_pre_back_extreme]+T(1,1)*R[detect_pre_back_extreme]+T(1,2)*R[grasp_pre_back_extreme]+T(1,3)*R[put_pre_back_extreme]);
					Vtorso[0][back_left]=R[detect_pre_back_left] + gamma*(T(1,0)*R[nav_pre_back_left]+T(1,1)*R[detect_pre_back_left]+T(1,2)*R[grasp_pre_back_left]+T(1,3)*R[put_pre_back_left]);
					Vtorso[0][back_left_extreme]=R[detect_pre_back_left_extreme] + gamma*(T(1,0)*R[nav_pre_back_left_extreme]+T(1,1)*R[detect_pre_back_left_extreme]+T(1,2)*R[grasp_pre_back_left_extreme]+T(1,3)*R[put_pre_back_left_extreme]);
					Vtorso[0][back_right]=R[detect_pre_back_right] + gamma*(T(1,0)*R[nav_pre_back_right]+T(1,1)*R[detect_pre_back_right]+T(1,2)*R[grasp_pre_back_right]+T(1,3)*R[put_pre_back_right]);
					Vtorso[0][back_right_extreme]=R[detect_pre_back_right_extreme] + gamma*(T(1,0)*R[nav_pre_back_right_extreme]+T(1,1)*R[detect_pre_back_right_extreme]+T(1,2)*R[grasp_pre_back_right_extreme]+T(1,3)*R[put_pre_back_right_extreme]);
					Vtorso[0][lookontray]=R[detect_pre_lookontray] + gamma*(T(1,0)*R[nav_pre_lookontray]+T(1,1)*R[detect_pre_lookontray]+T(1,2)*R[grasp_pre_lookontray]+T(1,3)*R[put_pre_lookontray]);
				}
				if (action_stage=="post-config")
				{
					Vtorso[0][home]=R[detect_post_home] + gamma*(T(1,0)*R[nav_post_home]+T(1,1)*R[detect_post_home]+T(1,2)*R[grasp_post_home]+T(1,3)*R[put_post_home]);
					Vtorso[0][left]=R[detect_post_left] + gamma*(T(1,0)*R[nav_post_left]+T(1,1)*R[detect_post_left]+T(1,2)*R[grasp_post_left]+T(1,3)*R[put_post_left]);
					Vtorso[0][right]=R[detect_post_right] + gamma*(T(1,0)*R[nav_post_right]+T(1,1)*R[detect_post_right]+T(1,2)*R[grasp_post_right]+T(1,3)*R[put_post_right]);
					Vtorso[0][front]=R[detect_post_front] + gamma*(T(1,0)*R[nav_post_front]+T(1,1)*R[detect_post_front]+T(1,2)*R[grasp_post_front]+T(1,3)*R[put_post_front]);
					Vtorso[0][front_left]=R[detect_post_front_left] + gamma*(T(1,0)*R[nav_post_front_left]+T(1,1)*R[detect_post_front_left]+T(1,2)*R[grasp_post_front_left]+T(1,3)*R[put_post_front_left]);
					Vtorso[0][front_right]=R[detect_post_front_right] + gamma*(T(1,0)*R[nav_post_front_right]+T(1,1)*R[detect_post_front_right]+T(1,2)*R[grasp_post_front_right]+T(1,3)*R[put_post_front_right]);
					Vtorso[0][back]=R[detect_post_back] + gamma*(T(1,0)*R[nav_post_back]+T(1,1)*R[detect_post_back]+T(1,2)*R[grasp_post_back]+T(1,3)*R[put_post_back]);
					Vtorso[0][back_extreme]=R[detect_post_back_extreme] + gamma*(T(1,0)*R[nav_post_back_extreme]+T(1,1)*R[detect_post_back_extreme]+T(1,2)*R[grasp_post_back_extreme]+T(1,3)*R[put_post_back_extreme]);
					Vtorso[0][back_left]=R[detect_post_back_left] + gamma*(T(1,0)*R[nav_post_back_left]+T(1,1)*R[detect_post_back_left]+T(1,2)*R[grasp_post_back_left]+T(1,3)*R[put_post_back_left]);
					Vtorso[0][back_left_extreme]=R[detect_post_back_left_extreme] + gamma*(T(1,0)*R[nav_post_back_left_extreme]+T(1,1)*R[detect_post_back_left_extreme]+T(1,2)*R[grasp_post_back_left_extreme]+T(1,3)*R[put_post_back_left_extreme]);
					Vtorso[0][back_right]=R[detect_post_back_right] + gamma*(T(1,0)*R[nav_post_back_right]+T(1,1)*R[detect_post_back_right]+T(1,2)*R[grasp_post_back_right]+T(1,3)*R[put_post_back_right]);
					Vtorso[0][back_right_extreme]=R[detect_post_back_right_extreme] + gamma*(T(1,0)*R[nav_post_back_right_extreme]+T(1,1)*R[detect_post_back_right_extreme]+T(1,2)*R[grasp_post_back_right_extreme]+T(1,3)*R[put_post_back_right_extreme]);
					Vtorso[0][lookontray]=R[detect_post_lookontray] + gamma*(T(1,0)*R[nav_post_lookontray]+T(1,1)*R[detect_post_lookontray]+T(1,2)*R[grasp_post_lookontray]+T(1,3)*R[put_post_lookontray]);
				}
			}
			if (action_name=="grasp")
			{
				if (action_stage=="pre-config")
				{
					Vtorso[0][home]=R[grasp_pre_home] + gamma*(T(2,0)*R[nav_pre_home]+T(2,1)*R[detect_pre_home]+T(2,2)*R[grasp_pre_home]+T(2,3)*R[put_pre_home]);
					Vtorso[0][left]=R[grasp_pre_left] + gamma*(T(2,0)*R[nav_pre_left]+T(2,1)*R[detect_pre_left]+T(2,2)*R[grasp_pre_left]+T(2,3)*R[put_pre_left]);
					Vtorso[0][right]=R[grasp_pre_right] + gamma*(T(2,0)*R[nav_pre_right]+T(2,1)*R[detect_pre_right]+T(2,2)*R[grasp_pre_right]+T(2,3)*R[put_pre_right]);
					Vtorso[0][front]=R[grasp_pre_front] + gamma*(T(2,0)*R[nav_pre_front]+T(2,1)*R[detect_pre_front]+T(2,2)*R[grasp_pre_front]+T(2,3)*R[put_pre_front]);
					Vtorso[0][front_left]=R[grasp_pre_front_left] + gamma*(T(2,0)*R[nav_pre_front_left]+T(2,1)*R[detect_pre_front_left]+T(2,2)*R[grasp_pre_front_left]+T(2,3)*R[put_pre_front_left]);
					Vtorso[0][front_right]=R[grasp_pre_front_right] + gamma*(T(2,0)*R[nav_pre_front_right]+T(2,1)*R[detect_pre_front_right]+T(2,2)*R[grasp_pre_front_right]+T(2,3)*R[put_pre_front_right]);
					Vtorso[0][back]=R[grasp_pre_back] + gamma*(T(2,0)*R[nav_pre_back]+T(2,1)*R[detect_pre_back]+T(2,2)*R[grasp_pre_back]+T(2,3)*R[put_pre_back]);
					Vtorso[0][back_extreme]=R[grasp_pre_back_extreme] + gamma*(T(2,0)*R[nav_pre_back_extreme]+T(2,1)*R[detect_pre_back_extreme]+T(2,2)*R[grasp_pre_back_extreme]+T(2,3)*R[put_pre_back_extreme]);
					Vtorso[0][back_left]=R[grasp_pre_back_left] + gamma*(T(2,0)*R[nav_pre_back_left]+T(2,1)*R[detect_pre_back_left]+T(2,2)*R[grasp_pre_back_left]+T(2,3)*R[put_pre_back_left]);
					Vtorso[0][back_left_extreme]=R[grasp_pre_back_left_extreme] + gamma*(T(2,0)*R[nav_pre_back_left_extreme]+T(2,1)*R[detect_pre_back_left_extreme]+T(2,2)*R[grasp_pre_back_left_extreme]+T(2,3)*R[put_pre_back_left_extreme]);
					Vtorso[0][back_right]=R[grasp_pre_back_right] + gamma*(T(2,0)*R[nav_pre_back_right]+T(2,1)*R[detect_pre_back_right]+T(2,2)*R[grasp_pre_back_right]+T(2,3)*R[put_pre_back_right]);
					Vtorso[0][back_right_extreme]=R[grasp_pre_back_right_extreme] + gamma*(T(2,0)*R[nav_pre_back_right_extreme]+T(2,1)*R[detect_pre_back_right_extreme]+T(2,2)*R[grasp_pre_back_right_extreme]+T(2,3)*R[put_pre_back_right_extreme]);
					Vtorso[0][lookontray]=R[grasp_pre_lookontray] + gamma*(T(2,0)*R[nav_pre_lookontray]+T(2,1)*R[detect_pre_lookontray]+T(2,2)*R[grasp_pre_lookontray]+T(2,3)*R[put_pre_lookontray]);
				}
				if (action_stage=="post-config")
				{
					Vtorso[0][home]=R[grasp_post_home] + gamma*(T(2,0)*R[nav_post_home]+T(2,1)*R[detect_post_home]+T(2,2)*R[grasp_post_home]+T(2,3)*R[put_post_home]);
					Vtorso[0][left]=R[grasp_post_left] + gamma*(T(2,0)*R[nav_post_left]+T(2,1)*R[detect_post_left]+T(2,2)*R[grasp_post_left]+T(2,3)*R[put_post_left]);
					Vtorso[0][right]=R[grasp_post_right] + gamma*(T(2,0)*R[nav_post_right]+T(2,1)*R[detect_post_right]+T(2,2)*R[grasp_post_right]+T(2,3)*R[put_post_right]);
					Vtorso[0][front]=R[grasp_post_front] + gamma*(T(2,0)*R[nav_post_front]+T(2,1)*R[detect_post_front]+T(2,2)*R[grasp_post_front]+T(2,3)*R[put_post_front]);
					Vtorso[0][front_left]=R[grasp_post_front_left] + gamma*(T(2,0)*R[nav_post_front_left]+T(2,1)*R[detect_post_front_left]+T(2,2)*R[grasp_post_front_left]+T(2,3)*R[put_post_front_left]);
					Vtorso[0][front_right]=R[grasp_post_front_right] + gamma*(T(2,0)*R[nav_post_front_right]+T(2,1)*R[detect_post_front_right]+T(2,2)*R[grasp_post_front_right]+T(2,3)*R[put_post_front_right]);
					Vtorso[0][back]=R[grasp_post_back] + gamma*(T(2,0)*R[nav_post_back]+T(2,1)*R[detect_post_back]+T(2,2)*R[grasp_post_back]+T(2,3)*R[put_post_back]);
					Vtorso[0][back_extreme]=R[grasp_post_back_extreme] + gamma*(T(2,0)*R[nav_post_back_extreme]+T(2,1)*R[detect_post_back_extreme]+T(2,2)*R[grasp_post_back_extreme]+T(2,3)*R[put_post_back_extreme]);
					Vtorso[0][back_left]=R[grasp_post_back_left] + gamma*(T(2,0)*R[nav_post_back_left]+T(2,1)*R[detect_post_back_left]+T(2,2)*R[grasp_post_back_left]+T(2,3)*R[put_post_back_left]);
					Vtorso[0][back_left_extreme]=R[grasp_post_back_left_extreme] + gamma*(T(2,0)*R[nav_post_back_left_extreme]+T(2,1)*R[detect_post_back_left_extreme]+T(2,2)*R[grasp_post_back_left_extreme]+T(2,3)*R[put_post_back_left_extreme]);
					Vtorso[0][back_right]=R[grasp_post_back_right] + gamma*(T(2,0)*R[nav_post_back_right]+T(2,1)*R[detect_post_back_right]+T(2,2)*R[grasp_post_back_right]+T(2,3)*R[put_post_back_right]);
					Vtorso[0][back_right_extreme]=R[grasp_post_back_right_extreme] + gamma*(T(2,0)*R[nav_post_back_right_extreme]+T(2,1)*R[detect_post_back_right_extreme]+T(2,2)*R[grasp_post_back_right_extreme]+T(2,3)*R[put_post_back_right_extreme]);
					Vtorso[0][lookontray]=R[grasp_post_lookontray] + gamma*(T(2,0)*R[nav_post_lookontray]+T(2,1)*R[detect_post_lookontray]+T(2,2)*R[grasp_post_lookontray]+T(2,3)*R[put_post_lookontray]);
				}
			}
			if (action_name=="put_on_tray")
			{
				if (action_stage=="pre-config")
				{
					Vtorso[0][home]=R[put_pre_home] + gamma*(T(3,0)*R[nav_pre_home]+T(3,1)*R[detect_pre_home]+T(3,2)*R[grasp_pre_home]+T(3,3)*R[put_pre_home]);
					Vtorso[0][left]=R[put_pre_left] + gamma*(T(3,0)*R[nav_pre_left]+T(3,1)*R[detect_pre_left]+T(3,2)*R[grasp_pre_left]+T(3,3)*R[put_pre_left]);
					Vtorso[0][right]=R[put_pre_right] + gamma*(T(3,0)*R[nav_pre_right]+T(3,1)*R[detect_pre_right]+T(3,2)*R[grasp_pre_right]+T(3,3)*R[put_pre_right]);
					Vtorso[0][front]=R[put_pre_front] + gamma*(T(3,0)*R[nav_pre_front]+T(3,1)*R[detect_pre_front]+T(3,2)*R[grasp_pre_front]+T(3,3)*R[put_pre_front]);
					Vtorso[0][front_left]=R[put_pre_front_left] + gamma*(T(3,0)*R[nav_pre_front_left]+T(3,1)*R[detect_pre_front_left]+T(3,2)*R[grasp_pre_front_left]+T(3,3)*R[put_pre_front_left]);
					Vtorso[0][front_right]=R[put_pre_front_right] + gamma*(T(3,0)*R[nav_pre_front_right]+T(3,1)*R[detect_pre_front_right]+T(3,2)*R[grasp_pre_front_right]+T(3,3)*R[put_pre_front_right]);
					Vtorso[0][back]=R[put_pre_back] + gamma*(T(3,0)*R[nav_pre_back]+T(3,1)*R[detect_pre_back]+T(3,2)*R[grasp_pre_back]+T(3,3)*R[put_pre_back]);
					Vtorso[0][back_extreme]=R[put_pre_back_extreme] + gamma*(T(3,0)*R[nav_pre_back_extreme]+T(3,1)*R[detect_pre_back_extreme]+T(3,2)*R[grasp_pre_back_extreme]+T(3,3)*R[put_pre_back_extreme]);
					Vtorso[0][back_left]=R[put_pre_back_left] + gamma*(T(3,0)*R[nav_pre_back_left]+T(3,1)*R[detect_pre_back_left]+T(3,2)*R[grasp_pre_back_left]+T(3,3)*R[put_pre_back_left]);
					Vtorso[0][back_left_extreme]=R[put_pre_back_left_extreme] + gamma*(T(3,0)*R[nav_pre_back_left_extreme]+T(3,1)*R[detect_pre_back_left_extreme]+T(3,2)*R[grasp_pre_back_left_extreme]+T(3,3)*R[put_pre_back_left_extreme]);
					Vtorso[0][back_right]=R[put_pre_back_right] + gamma*(T(3,0)*R[nav_pre_back_right]+T(3,1)*R[detect_pre_back_right]+T(3,2)*R[grasp_pre_back_right]+T(3,3)*R[put_pre_back_right]);
					Vtorso[0][back_right_extreme]=R[put_pre_back_right_extreme] + gamma*(T(3,0)*R[nav_pre_back_right_extreme]+T(3,1)*R[detect_pre_back_right_extreme]+T(3,2)*R[grasp_pre_back_right_extreme]+T(3,3)*R[put_pre_back_right_extreme]);
					Vtorso[0][lookontray]=R[put_pre_lookontray] + gamma*(T(3,0)*R[nav_pre_lookontray]+T(3,1)*R[detect_pre_lookontray]+T(3,2)*R[grasp_pre_lookontray]+T(3,3)*R[put_pre_lookontray]);
				}
				if (action_stage=="post-config")
				{
					Vtorso[0][home]=R[put_post_home] + gamma*(T(3,0)*R[nav_post_home]+T(3,1)*R[detect_post_home]+T(3,2)*R[grasp_post_home]+T(3,3)*R[put_post_home]);
					Vtorso[0][left]=R[put_post_left] + gamma*(T(3,0)*R[nav_post_left]+T(3,1)*R[detect_post_left]+T(3,2)*R[grasp_post_left]+T(3,3)*R[put_post_left]);
					Vtorso[0][right]=R[put_post_right] + gamma*(T(3,0)*R[nav_post_right]+T(3,1)*R[detect_post_right]+T(3,2)*R[grasp_post_right]+T(3,3)*R[put_post_right]);
					Vtorso[0][front]=R[put_post_front] + gamma*(T(3,0)*R[nav_post_front]+T(3,1)*R[detect_post_front]+T(3,2)*R[grasp_post_front]+T(3,3)*R[put_post_front]);
					Vtorso[0][front_left]=R[put_post_front_left] + gamma*(T(3,0)*R[nav_post_front_left]+T(3,1)*R[detect_post_front_left]+T(3,2)*R[grasp_post_front_left]+T(3,3)*R[put_post_front_left]);
					Vtorso[0][front_right]=R[put_post_front_right] + gamma*(T(3,0)*R[nav_post_front_right]+T(3,1)*R[detect_post_front_right]+T(3,2)*R[grasp_post_front_right]+T(3,3)*R[put_post_front_right]);
					Vtorso[0][back]=R[put_post_back] + gamma*(T(3,0)*R[nav_post_back]+T(3,1)*R[detect_post_back]+T(3,2)*R[grasp_post_back]+T(3,3)*R[put_post_back]);
					Vtorso[0][back_extreme]=R[put_post_back_extreme] + gamma*(T(3,0)*R[nav_post_back_extreme]+T(3,1)*R[detect_post_back_extreme]+T(3,2)*R[grasp_post_back_extreme]+T(3,3)*R[put_post_back_extreme]);
					Vtorso[0][back_left]=R[put_post_back_left] + gamma*(T(3,0)*R[nav_post_back_left]+T(3,1)*R[detect_post_back_left]+T(3,2)*R[grasp_post_back_left]+T(3,3)*R[put_post_back_left]);
					Vtorso[0][back_left_extreme]=R[put_post_back_left_extreme] + gamma*(T(3,0)*R[nav_post_back_left_extreme]+T(3,1)*R[detect_post_back_left_extreme]+T(3,2)*R[grasp_post_back_left_extreme]+T(3,3)*R[put_post_back_left_extreme]);
					Vtorso[0][back_right]=R[put_post_back_right] + gamma*(T(3,0)*R[nav_post_back_right]+T(3,1)*R[detect_post_back_right]+T(3,2)*R[grasp_post_back_right]+T(3,3)*R[put_post_back_right]);
					Vtorso[0][back_right_extreme]=R[put_post_back_right_extreme] + gamma*(T(3,0)*R[nav_post_back_right_extreme]+T(3,1)*R[detect_post_back_right_extreme]+T(3,2)*R[grasp_post_back_right_extreme]+T(3,3)*R[put_post_back_right_extreme]);
					Vtorso[0][lookontray]=R[put_post_lookontray] + gamma*(T(3,0)*R[nav_post_lookontray]+T(3,1)*R[detect_post_lookontray]+T(3,2)*R[grasp_post_lookontray]+T(3,3)*R[put_post_lookontray]);
				}
			}
		//}

//------------- Chose the best way with the function max -------------

/*	result_torso=0;
	for (int j=15;j>=0;j--)
	{
		if(result_torso<Vtorso[0][j])		//function max
		{
			result_torso=Vtorso[0][j];
			//result_torsostate=j;			// know the state where the value function is the best
		}								// if j=0=home, j=1=cylclosed, j=2=cylopen ,etc...
	}*/

	//------------- Chose the best way with the Bees Algorithm-------------
		int temp2;
		double temp1 ;
		int nghx[dim]; // Neighborhood
		int fit[pop],sortedFit[pop],bPos[dim][pop],bPosSort[dim][pop];
		int bNghFit[pop],bNghPos[dim][pop];
		int globalFit[pop], globalPos[dim][pop];
		int candidx[dim][pop];

		srand( (unsigned)time( NULL ) );

		for(int runs=0; runs<1; runs++)
		{	//number of runs
			//initialise with random start positions at the start of every run
			for(int i=0;i<torso_n;i++)
			{
				for(int d=0;d<dim;d++)
				{
				bPos[d][i]= torso_randfunc(torso_xs, torso_xe);
				fit[i]=torso_func(bPos[d][i], Vtorso);
				}
			}

			// at this point bPos contains a number of randomly initialised particles
			// fit, contains the value of the fit350000ness function
			// thus forming a (fit,bPos) tuple

			//sort by fitness, preserving the (f,pos) tuple
			torso_funcSort(fit, sortedFit, bPos, bPosSort, torso_n); // bpossort contains all the sort position of the scout bees
			fit[bPosSort[0][0]]=torso_func(bPosSort[0][0], Vtorso);

			//imax number of iteration
			for(int iter=0; iter<torso_imax ;iter++)
			{
				for(int d=0;d<dim;d++)
					nghx[d] = 1;

				int aa[50]; //50 max number of selected sites out of n

					 for(int i=0;i<torso_m;i++)
					 {
					   if(i<torso_e)
						   aa[i]=torso_n2;  // Number of bees around each elite point
					   else
						   aa[i]=torso_n1;  // Number of bees around other selected point
					   }

	// ----------------------------------------Neighbourhood search  ------------------------------------

				temp1=-INT_MAX;

				for(int k=0;k<torso_e;k++)//k site
				{
					for(int j=0;j<aa[k];j++) //j recruited bee
					{
						for(int d=0;d<dim;d++)//d dimension
						{
							candidx[d][k]=bPosSort[d][k]; //define the candidate position
							if ((candidx[d][k]-nghx[d])<torso_xs) // boundry check (left)
								{
								 bNghPos[d][j]=torso_randfunc(torso_xs,candidx[d][k]+nghx[d]);
								 bNghFit[j]=torso_func(bNghPos[d][j], Vtorso);
								}
							if ((candidx[d][k]+nghx[d])>torso_xe)// boundry check (right)
								{
								bNghPos[d][j]=torso_randfunc(candidx[d][k]-nghx[d],torso_xe);
								bNghFit[j]=torso_func(bNghPos[d][j], Vtorso);
								}
							if ((candidx[d][k]-nghx[d])>=torso_xs and (candidx[d][k]+nghx[d])<=torso_xe )
								{
								bNghPos[d][j]=torso_randfunc(candidx[d][k]-nghx[d] , candidx[d][k]+nghx[d]);
								bNghFit[j]=torso_func(bNghPos[d][j], Vtorso);
								}
							if(bNghFit[j]>= temp1 )
							{
								temp1=bNghFit[j];
								temp2=bNghPos[d][j];
							}// end of choosing the rep bee
						}
					}// end of recruitment

				}// end of  elite Neighbourhood Search

				 //Sort
			if (sortedFit[0]<= temp1)
			{
				sortedFit[0]=temp1;
				bPosSort[0][0]=temp2;
			}

	// ----------------------------------------Global search  ------------------------------------

				int ranSearchBees=torso_n-torso_m; // Number of bees search randomly
				for(int k=0;k<ranSearchBees;k++)	//start of random search for rest of bees
					 {
						for(int d=0;d<dim;d++)
						{
							globalPos[d][k]=torso_randfunc(torso_xs, torso_xe);
							globalFit[k]=torso_func(globalPos[d][k], Vtorso);// evaluate the fitness of the new list
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

			result_torsostate=bPosSort[0][0]; //bPosSort[0][0] correspond to the elite site
			result_torso = sortedFit[0]; // sortedFit[0] correspond to the value of the elite site
			std::cout << "best torso pos: " << result_torsostate << std::endl;
			std::cout << "best torso Vfit: " << result_torso<< std::endl;

		return;
	}
