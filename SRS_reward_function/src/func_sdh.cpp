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
int sdh_imax=500;
int sdh_n= pop;  // Number of Scout Bees
int sdh_m= 2;   // Number of selected Locations
int sdh_n1 =6;  // Number of Bees around each selected locations ( except the ellit location )
int sdh_n2 =20;  // Number of Bees around each ellit locations
int sdh_e =1;   // Elite point/s

int sdh_func( int i,std::vector<std::vector<float> > Vsdh)  // Definition of Fitness Function
{
	int y;
	y=Vsdh[0][i];
	  return y;
}

//------------------------------random function used in the Bees algorithm-----------------------

int	sdh_xs = 0;
int	sdh_xe = 9;
int sdh_randfunc( int sdh_xs, int sdh_xe )  // Definition of Random number Generator Function*/
{
  double randnum;
  randnum=rand() ;
  randnum=sdh_xs+randnum*(sdh_xe-sdh_xs) / RAND_MAX;
  int intrandnum = randnum +0.5;	//kind of rounding in order to have only 0 or 1 random number
  return intrandnum;
}

//------------------------------sorting function used in the Bees algorithm-----------------------

void sdh_funcSort(int inP1[],int oP1[],int inP2[][pop],int oP2[][pop],int size)
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

void reward_sdh (std::string action_name, std::string action_stage, std::string result_action, std::vector<std::vector<float> >& Vsdh,double& result_sdh ,int& result_sdhstate,Eigen::Matrix4f& T)
{
float gamma=0.1;  // define the discount factor "gamma"
	int home=0, cylclosed=1, cylopen=2, cyltotalopen=3, spheropen=4, spherclosed=5,paropen=6, parclosed=7,point=8, fist=9;
	int nav_pre_home=0,nav_pre_cylclosed=1,nav_pre_cylopen=2,nav_pre_cyltotalopen=3,nav_pre_spheropen=4,nav_pre_spherclosed=5,nav_pre_paropen=6,nav_pre_parclosed=7,nav_pre_point=8,nav_pre_fist=9;
	int nav_post_home=10,nav_post_cylclosed=11,nav_post_cylopen=12,nav_post_cyltotalopen=13,nav_post_spheropen=14,nav_post_spherclosed=15,nav_post_paropen=16,nav_post_parclosed=17,nav_post_point=18,nav_post_fist=19;
	int detect_pre_home=20,detect_pre_cylclosed=21,detect_pre_cylopen=22,detect_pre_cyltotalopen=23,detect_pre_spheropen=24,detect_pre_spherclosed=25,detect_pre_paropen=26,detect_pre_parclosed=27,detect_pre_point=28,detect_pre_fist=29;
	int detect_post_home=30,detect_post_cylclosed=31,detect_post_cylopen=32,detect_post_cyltotalopen=33,detect_post_spheropen=34,detect_post_spherclosed=35,detect_post_paropen=36,detect_post_parclosed=37,detect_post_point=38,detect_post_fist=39;
	int grasp_pre_home=40,grasp_pre_cylclosed=41,grasp_pre_cylopen=42,grasp_pre_cyltotalopen=43,grasp_pre_spheropen=44,grasp_pre_spherclosed=45,grasp_pre_paropen=46,grasp_pre_parclosed=47,grasp_pre_point=48,grasp_pre_fist=49;
	int grasp_post_home=50,grasp_post_cylclosed=51,grasp_post_cylopen=52,grasp_post_cyltotalopen=53,grasp_post_spheropen=54,grasp_post_spherclosed=55,grasp_post_paropen=56,grasp_post_parclosed=57,grasp_post_point=58,grasp_post_fist=59;
	int put_pre_home=60,put_pre_cylclosed=61,put_pre_cylopen=62,put_pre_cyltotalopen=63,put_pre_spheropen=64,put_pre_spherclosed=65,put_pre_paropen=66,put_pre_parclosed=67,put_pre_point=68,put_pre_fist=69;
	int put_post_home=70,put_post_cylclosed=71,put_post_cylopen=72,put_post_cyltotalopen=73,put_post_spheropen=74,put_post_spherclosed=75,put_post_paropen=76,put_post_parclosed=77,put_post_point=78,put_post_fist=79;

	std::vector<float> R;   //create a vector R with an unknown size
		R.resize(80);  // define the size of the vector
	Vsdh.resize(2);
	for (int i=1;i>=0;i--)
	{
	Vsdh[i].resize(10);
	}

	//----- definition of the reward -----
		R[nav_pre_home]=3;				R[detect_pre_home]=8;				R[grasp_pre_home]=9;			R[put_pre_home]=9;
		R[nav_pre_cylclosed]=20;		R[detect_pre_cylclosed]=20;			R[grasp_pre_cylclosed]=20;		R[put_pre_cylclosed]=20;
		R[nav_pre_cylopen]=10;			R[detect_pre_cylopen]=10;			R[grasp_pre_cylopen]=10;		R[put_pre_cylopen]=10;
		R[nav_pre_cyltotalopen]=2;		R[detect_pre_cyltotalopen]=1;		R[grasp_pre_cyltotalopen]=4;	R[put_pre_cyltotalopen]=5;
		R[nav_pre_spheropen]=7;			R[detect_pre_spheropen]=9;			R[grasp_pre_spheropen]=3;		R[put_pre_spheropen]=3;
		R[nav_pre_spherclosed]=3;		R[detect_pre_spherclosed]=5;		R[grasp_pre_spherclosed]=8;		R[put_pre_spherclosed]=7;
		R[nav_pre_paropen]=5;			R[detect_pre_paropen]=3;			R[grasp_pre_paropen]=6;			R[put_pre_paropen]=5;
		R[nav_pre_parclosed]=6;			R[detect_pre_parclosed]=2;			R[grasp_pre_parclosed]=5;		R[put_pre_parclosed]=4;
		R[nav_pre_point]=8;				R[detect_pre_point]=4;				R[grasp_pre_point]=7;			R[put_pre_point]=2;
		R[nav_pre_fist]=2;				R[detect_pre_fist]=2;				R[grasp_pre_fist]=3;			R[put_pre_fist]=1;

		R[nav_post_home]=5;				R[detect_post_home]=4;				R[grasp_post_home]=4;			R[put_post_home]=4;
		R[nav_post_cylclosed]=20;		R[detect_post_cylclosed]=20;		R[grasp_post_cylclosed]=20;		R[put_post_cylclosed]=20;
		R[nav_post_cylopen]=10;			R[detect_post_cylopen]=10;			R[grasp_post_cylopen]=10;		R[put_post_cylopen]=10;
		R[nav_post_cyltotalopen]=4;		R[detect_post_cyltotalopen]=1;		R[grasp_post_cyltotalopen]=8;	R[put_post_cyltotalopen]=6;
		R[nav_post_spheropen]=8;		R[detect_post_spheropen]=3;			R[grasp_post_spheropen]=3;		R[put_post_spheropen]=5;
		R[nav_post_spherclosed]=4;		R[detect_post_spherclosed]=7;		R[grasp_post_spherclosed]=9;	R[put_post_spherclosed]=9;
		R[nav_post_paropen]=2;			R[detect_post_paropen]=6;			R[grasp_post_paropen]=1;		R[put_post_paropen]=7;
		R[nav_post_parclosed]=9;		R[detect_post_parclosed]=5;		R[grasp_post_parclosed]=2;		R[put_post_parclosed]=8;
		R[nav_post_point]=4;			R[detect_post_point]=4;				R[grasp_post_point]=5;			R[put_post_point]=4;
		R[nav_post_fist]=6;				R[detect_post_fist]=2;				R[grasp_post_fist]=7;			R[put_post_fist]=2;

		if (action_name=="navigation")
		{
			if (action_stage=="pre-config")
			{
				Vsdh[0][home]=R[nav_pre_home] + gamma*(T(0,0)*R[nav_pre_home]+T(0,1)*R[detect_pre_home]+T(0,2)*R[grasp_pre_home]+T(0,3)*R[put_pre_home]);
				Vsdh[0][cylclosed]=R[nav_pre_cylclosed] + gamma*(T(0,0)*R[nav_pre_cylclosed]+T(0,1)*R[detect_pre_cylclosed]+T(0,2)*R[grasp_pre_cylclosed]+T(0,3)*R[put_pre_cylclosed]);
				Vsdh[0][cylopen]=R[nav_pre_cylopen] + gamma*(T(0,0)*R[nav_pre_cylopen]+T(0,1)*R[detect_pre_cylopen]+T(0,2)*R[grasp_pre_cylopen]+T(0,3)*R[put_pre_cylopen]);
				Vsdh[0][cyltotalopen]=R[nav_pre_cyltotalopen] + gamma*(T(0,0)*R[nav_pre_cyltotalopen]+T(0,1)*R[detect_pre_cyltotalopen]+T(0,2)*R[grasp_pre_cyltotalopen]+T(0,3)*R[put_pre_cyltotalopen]);
				Vsdh[0][spheropen]=R[nav_pre_spheropen] + gamma*(T(0,0)*R[nav_pre_spheropen]+T(0,1)*R[detect_pre_spheropen]+T(0,2)*R[grasp_pre_spheropen]+T(0,3)*R[put_pre_spheropen]);
				Vsdh[0][spherclosed]=R[nav_pre_spherclosed] + gamma*(T(0,0)*R[nav_pre_spherclosed]+T(0,1)*R[detect_pre_spherclosed]+T(0,2)*R[grasp_pre_spherclosed]+T(0,3)*R[put_pre_spherclosed]);
				Vsdh[0][paropen]=R[nav_pre_paropen] + gamma*(T(0,0)*R[nav_pre_paropen]+T(0,1)*R[detect_pre_paropen]+T(0,2)*R[grasp_pre_paropen]+T(0,3)*R[put_pre_paropen]);
				Vsdh[0][parclosed]=R[nav_pre_parclosed] + gamma*(T(0,0)*R[nav_pre_parclosed]+T(0,1)*R[detect_pre_parclosed]+T(0,2)*R[grasp_pre_parclosed]+T(0,3)*R[put_pre_parclosed]);
				Vsdh[0][point]=R[nav_pre_point] + gamma*(T(0,0)*R[nav_pre_point]+T(0,1)*R[detect_pre_point]+T(0,2)*R[grasp_pre_point]+T(0,3)*R[put_pre_point]);
				Vsdh[0][fist]=R[nav_pre_fist] + gamma*(T(0,0)*R[nav_pre_fist]+T(0,1)*R[detect_pre_fist]+T(0,2)*R[grasp_pre_fist]+T(0,3)*R[put_pre_fist]);
			}
			if (action_stage=="post-config")
			{
				Vsdh[0][home]=R[nav_post_home] + gamma*(T(0,0)*R[nav_post_home]+T(0,1)*R[detect_post_home]+T(0,2)*R[grasp_post_home]+T(0,3)*R[put_post_home]);
				Vsdh[0][cylclosed]=R[nav_post_cylclosed] + gamma*(T(0,0)*R[nav_post_cylclosed]+T(0,1)*R[detect_post_cylclosed]+T(0,2)*R[grasp_post_cylclosed]+T(0,3)*R[put_post_cylclosed]);
				Vsdh[0][cylopen]=R[nav_post_cylopen] + gamma*(T(0,0)*R[nav_post_cylopen]+T(0,1)*R[detect_post_cylopen]+T(0,2)*R[grasp_post_cylopen]+T(0,3)*R[put_post_cylopen]);
				Vsdh[0][cyltotalopen]=R[nav_post_cyltotalopen] + gamma*(T(0,0)*R[nav_post_cyltotalopen]+T(0,1)*R[detect_post_cyltotalopen]+T(0,2)*R[grasp_post_cyltotalopen]+T(0,3)*R[put_post_cyltotalopen]);
				Vsdh[0][spheropen]=R[nav_post_spheropen] + gamma*(T(0,0)*R[nav_post_spheropen]+T(0,1)*R[detect_post_spheropen]+T(0,2)*R[grasp_post_spheropen]+T(0,3)*R[put_post_spheropen]);
				Vsdh[0][spherclosed]=R[nav_post_spherclosed] + gamma*(T(0,0)*R[nav_post_spherclosed]+T(0,1)*R[detect_post_spherclosed]+T(0,2)*R[grasp_post_spherclosed]+T(0,3)*R[put_post_spherclosed]);
				Vsdh[0][paropen]=R[nav_post_paropen] + gamma*(T(0,0)*R[nav_post_paropen]+T(0,1)*R[detect_post_paropen]+T(0,2)*R[grasp_post_paropen]+T(0,3)*R[put_post_paropen]);
				Vsdh[0][parclosed]=R[nav_post_parclosed] + gamma*(T(0,0)*R[nav_post_parclosed]+T(0,1)*R[detect_post_parclosed]+T(0,2)*R[grasp_post_parclosed]+T(0,3)*R[put_post_parclosed]);
				Vsdh[0][point]=R[nav_post_point] + gamma*(T(0,0)*R[nav_post_point]+T(0,1)*R[detect_post_point]+T(0,2)*R[grasp_post_point]+T(0,3)*R[put_post_point]);
				Vsdh[0][fist]=R[nav_post_fist] + gamma*(T(0,0)*R[nav_post_fist]+T(0,1)*R[detect_post_fist]+T(0,2)*R[grasp_post_fist]+T(0,3)*R[put_post_fist]);
			}
		}
		if (action_name=="detection")
		{
			if (action_stage=="pre-config")
			{
				Vsdh[0][home]=R[detect_pre_home] + gamma*(T(1,0)*R[nav_pre_home]+T(1,1)*R[detect_pre_home]+T(1,2)*R[grasp_pre_home]+T(1,3)*R[put_pre_home]);
				Vsdh[0][cylclosed]=R[detect_pre_cylclosed] + gamma*(T(1,0)*R[nav_pre_cylclosed]+T(1,1)*R[detect_pre_cylclosed]+T(1,2)*R[grasp_pre_cylclosed]+T(1,3)*R[put_pre_cylclosed]);
				Vsdh[0][cylopen]=R[detect_pre_cylopen] + gamma*(T(1,0)*R[nav_pre_cylopen]+T(1,1)*R[detect_pre_cylopen]+T(1,2)*R[grasp_pre_cylopen]+T(1,3)*R[put_pre_cylopen]);
				Vsdh[0][cyltotalopen]=R[detect_pre_cyltotalopen] + gamma*(T(1,0)*R[nav_pre_cyltotalopen]+T(1,1)*R[detect_pre_cyltotalopen]+T(1,2)*R[grasp_pre_cyltotalopen]+T(1,3)*R[put_pre_cyltotalopen]);
				Vsdh[0][spheropen]=R[detect_pre_spheropen] + gamma*(T(1,0)*R[nav_pre_spheropen]+T(1,1)*R[detect_pre_spheropen]+T(1,2)*R[grasp_pre_spheropen]+T(1,3)*R[put_pre_spheropen]);
				Vsdh[0][spherclosed]=R[detect_pre_spherclosed] + gamma*(T(1,0)*R[nav_pre_spherclosed]+T(1,1)*R[detect_pre_spherclosed]+T(1,2)*R[grasp_pre_spherclosed]+T(1,3)*R[put_pre_spherclosed]);
				Vsdh[0][paropen]=R[detect_pre_paropen] + gamma*(T(1,0)*R[nav_pre_paropen]+T(1,1)*R[detect_pre_paropen]+T(1,2)*R[grasp_pre_paropen]+T(1,3)*R[put_pre_paropen]);
				Vsdh[0][parclosed]=R[detect_pre_parclosed] + gamma*(T(1,0)*R[nav_pre_parclosed]+T(1,1)*R[detect_pre_parclosed]+T(1,2)*R[grasp_pre_parclosed]+T(1,3)*R[put_pre_parclosed]);
				Vsdh[0][point]=R[detect_pre_point] + gamma*(T(1,0)*R[nav_pre_point]+T(1,1)*R[detect_pre_point]+T(1,2)*R[grasp_pre_point]+T(1,3)*R[put_pre_point]);
				Vsdh[0][fist]=R[detect_pre_fist] + gamma*(T(1,0)*R[nav_pre_fist]+T(1,1)*R[detect_pre_fist]+T(1,2)*R[grasp_pre_fist]+T(1,3)*R[put_pre_fist]);
			}
			if (action_stage=="post-config")
			{
				Vsdh[0][home]=R[detect_post_home] + gamma*(T(1,0)*R[nav_post_home]+T(1,1)*R[detect_post_home]+T(1,2)*R[grasp_post_home]+T(1,3)*R[put_post_home]);
				Vsdh[0][cylclosed]=R[detect_post_cylclosed] + gamma*(T(1,0)*R[nav_post_cylclosed]+T(1,1)*R[detect_post_cylclosed]+T(1,2)*R[grasp_post_cylclosed]+T(1,3)*R[put_post_cylclosed]);
				Vsdh[0][cylopen]=R[detect_post_cylopen] + gamma*(T(1,0)*R[nav_post_cylopen]+T(1,1)*R[detect_post_cylopen]+T(1,2)*R[grasp_post_cylopen]+T(1,3)*R[put_post_cylopen]);
				Vsdh[0][cyltotalopen]=R[detect_post_cyltotalopen] + gamma*(T(1,0)*R[nav_post_cyltotalopen]+T(1,1)*R[detect_post_cyltotalopen]+T(1,2)*R[grasp_post_cyltotalopen]+T(1,3)*R[put_post_cyltotalopen]);
				Vsdh[0][spheropen]=R[detect_post_spheropen] + gamma*(T(1,0)*R[nav_post_spheropen]+T(1,1)*R[detect_post_spheropen]+T(1,2)*R[grasp_post_spheropen]+T(1,3)*R[put_post_spheropen]);
				Vsdh[0][spherclosed]=R[detect_post_spherclosed] + gamma*(T(1,0)*R[nav_post_spherclosed]+T(1,1)*R[detect_post_spherclosed]+T(1,2)*R[grasp_post_spherclosed]+T(1,3)*R[put_post_spherclosed]);
				Vsdh[0][paropen]=R[detect_post_paropen] + gamma*(T(1,0)*R[nav_post_paropen]+T(1,1)*R[detect_post_paropen]+T(1,2)*R[grasp_post_paropen]+T(1,3)*R[put_post_paropen]);
				Vsdh[0][parclosed]=R[detect_post_parclosed] + gamma*(T(1,0)*R[nav_post_parclosed]+T(1,1)*R[detect_post_parclosed]+T(1,2)*R[grasp_post_parclosed]+T(1,3)*R[put_post_parclosed]);
				Vsdh[0][point]=R[detect_post_point] + gamma*(T(1,0)*R[nav_post_point]+T(1,1)*R[detect_post_point]+T(1,2)*R[grasp_post_point]+T(1,3)*R[put_post_point]);
				Vsdh[0][fist]=R[detect_post_fist] + gamma*(T(1,0)*R[nav_post_fist]+T(1,1)*R[detect_post_fist]+T(1,2)*R[grasp_post_fist]+T(1,3)*R[put_post_fist]);
			}
		}
		if (action_name=="grasp")
		{
			if (action_stage=="pre-config")
			{
				Vsdh[0][home]=R[grasp_pre_home] + gamma*(T(2,0)*R[nav_pre_home]+T(2,1)*R[detect_pre_home]+T(2,2)*R[grasp_pre_home]+T(2,3)*R[put_pre_home]);
				Vsdh[0][cylclosed]=R[grasp_pre_cylclosed] + gamma*(T(2,0)*R[nav_pre_cylclosed]+T(2,1)*R[detect_pre_cylclosed]+T(2,2)*R[grasp_pre_cylclosed]+T(2,3)*R[put_pre_cylclosed]);
				Vsdh[0][cylopen]=R[grasp_pre_cylopen] + gamma*(T(2,0)*R[nav_pre_cylopen]+T(2,1)*R[detect_pre_cylopen]+T(2,2)*R[grasp_pre_cylopen]+T(2,3)*R[put_pre_cylopen]);
				Vsdh[0][cyltotalopen]=R[grasp_pre_cyltotalopen] + gamma*(T(2,0)*R[nav_pre_cyltotalopen]+T(2,1)*R[detect_pre_cyltotalopen]+T(2,2)*R[grasp_pre_cyltotalopen]+T(2,3)*R[put_pre_cyltotalopen]);
				Vsdh[0][spheropen]=R[grasp_pre_spheropen] + gamma*(T(2,0)*R[nav_pre_spheropen]+T(2,1)*R[detect_pre_spheropen]+T(2,2)*R[grasp_pre_spheropen]+T(2,3)*R[put_pre_spheropen]);
				Vsdh[0][spherclosed]=R[grasp_pre_spherclosed] + gamma*(T(2,0)*R[nav_pre_spherclosed]+T(2,1)*R[detect_pre_spherclosed]+T(2,2)*R[grasp_pre_spherclosed]+T(2,3)*R[put_pre_spherclosed]);
				Vsdh[0][paropen]=R[grasp_pre_paropen] + gamma*(T(2,0)*R[nav_pre_paropen]+T(2,1)*R[detect_pre_paropen]+T(2,2)*R[grasp_pre_paropen]+T(2,3)*R[put_pre_paropen]);
				Vsdh[0][parclosed]=R[grasp_pre_parclosed] + gamma*(T(2,0)*R[nav_pre_parclosed]+T(2,1)*R[detect_pre_parclosed]+T(2,2)*R[grasp_pre_parclosed]+T(2,3)*R[put_pre_parclosed]);
				Vsdh[0][point]=R[grasp_pre_point] + gamma*(T(2,0)*R[nav_pre_point]+T(2,1)*R[detect_pre_point]+T(2,2)*R[grasp_pre_point]+T(2,3)*R[put_pre_point]);
				Vsdh[0][fist]=R[grasp_pre_fist] + gamma*(T(2,0)*R[nav_pre_fist]+T(2,1)*R[detect_pre_fist]+T(2,2)*R[grasp_pre_fist]+T(2,3)*R[put_pre_fist]);
			}
			if (action_stage=="post-config")
			{
				Vsdh[0][home]=R[grasp_post_home] + gamma*(T(2,0)*R[nav_post_home]+T(2,1)*R[detect_post_home]+T(2,2)*R[grasp_post_home]+T(2,3)*R[put_post_home]);
				Vsdh[0][cylclosed]=R[grasp_post_cylclosed] + gamma*(T(2,0)*R[nav_post_cylclosed]+T(2,1)*R[detect_post_cylclosed]+T(2,2)*R[grasp_post_cylclosed]+T(2,3)*R[put_post_cylclosed]);
				Vsdh[0][cylopen]=R[grasp_post_cylopen] + gamma*(T(2,0)*R[nav_post_cylopen]+T(2,1)*R[detect_post_cylopen]+T(2,2)*R[grasp_post_cylopen]+T(2,3)*R[put_post_cylopen]);
				Vsdh[0][cyltotalopen]=R[grasp_post_cyltotalopen] + gamma*(T(2,0)*R[nav_post_cyltotalopen]+T(2,1)*R[detect_post_cyltotalopen]+T(2,2)*R[grasp_post_cyltotalopen]+T(2,3)*R[put_post_cyltotalopen]);
				Vsdh[0][spheropen]=R[grasp_post_spheropen] + gamma*(T(2,0)*R[nav_post_spheropen]+T(2,1)*R[detect_post_spheropen]+T(2,2)*R[grasp_post_spheropen]+T(2,3)*R[put_post_spheropen]);
				Vsdh[0][spherclosed]=R[grasp_post_spherclosed] + gamma*(T(2,0)*R[nav_post_spherclosed]+T(2,1)*R[detect_post_spherclosed]+T(2,2)*R[grasp_post_spherclosed]+T(2,3)*R[put_post_spherclosed]);
				Vsdh[0][paropen]=R[grasp_post_paropen] + gamma*(T(2,0)*R[nav_post_paropen]+T(2,1)*R[detect_post_paropen]+T(2,2)*R[grasp_post_paropen]+T(2,3)*R[put_post_paropen]);
				Vsdh[0][parclosed]=R[grasp_post_parclosed] + gamma*(T(2,0)*R[nav_post_parclosed]+T(2,1)*R[detect_post_parclosed]+T(2,2)*R[grasp_post_parclosed]+T(2,3)*R[put_post_parclosed]);
				Vsdh[0][point]=R[grasp_post_point] + gamma*(T(2,0)*R[nav_post_point]+T(2,1)*R[detect_post_point]+T(2,2)*R[grasp_post_point]+T(2,3)*R[put_post_point]);
				Vsdh[0][fist]=R[grasp_post_fist] + gamma*(T(2,0)*R[nav_post_fist]+T(2,1)*R[detect_post_fist]+T(2,2)*R[grasp_post_fist]+T(2,3)*R[put_post_fist]);
			}
		}
		if (action_name=="put_on_tray")
		{
			if (action_stage=="pre-config")
			{
				Vsdh[0][home]=R[put_pre_home] + gamma*(T(3,0)*R[nav_pre_home]+T(3,1)*R[detect_pre_home]+T(3,2)*R[grasp_pre_home]+T(3,3)*R[put_pre_home]);
				Vsdh[0][cylclosed]=R[put_pre_cylclosed] + gamma*(T(3,0)*R[nav_pre_cylclosed]+T(3,1)*R[detect_pre_cylclosed]+T(3,2)*R[grasp_pre_cylclosed]+T(3,3)*R[put_pre_cylclosed]);
				Vsdh[0][cylopen]=R[put_pre_cylopen] + gamma*(T(3,0)*R[nav_pre_cylopen]+T(3,1)*R[detect_pre_cylopen]+T(3,2)*R[grasp_pre_cylopen]+T(3,3)*R[put_pre_cylopen]);
				Vsdh[0][cyltotalopen]=R[put_pre_cyltotalopen] + gamma*(T(3,0)*R[nav_pre_cyltotalopen]+T(3,1)*R[detect_pre_cyltotalopen]+T(3,2)*R[grasp_pre_cyltotalopen]+T(3,3)*R[put_pre_cyltotalopen]);
				Vsdh[0][spheropen]=R[put_pre_spheropen] + gamma*(T(3,0)*R[nav_pre_spheropen]+T(3,1)*R[detect_pre_spheropen]+T(3,2)*R[grasp_pre_spheropen]+T(3,3)*R[put_pre_spheropen]);
				Vsdh[0][spherclosed]=R[put_pre_spherclosed] + gamma*(T(3,0)*R[nav_pre_spherclosed]+T(3,1)*R[detect_pre_spherclosed]+T(3,2)*R[grasp_pre_spherclosed]+T(3,3)*R[put_pre_spherclosed]);
				Vsdh[0][paropen]=R[put_pre_paropen] + gamma*(T(3,0)*R[nav_pre_paropen]+T(3,1)*R[detect_pre_paropen]+T(3,2)*R[grasp_pre_paropen]+T(3,3)*R[put_pre_paropen]);
				Vsdh[0][parclosed]=R[put_pre_parclosed] + gamma*(T(3,0)*R[nav_pre_parclosed]+T(3,1)*R[detect_pre_parclosed]+T(3,2)*R[grasp_pre_parclosed]+T(3,3)*R[put_pre_parclosed]);
				Vsdh[0][point]=R[put_pre_point] + gamma*(T(3,0)*R[nav_pre_point]+T(3,1)*R[detect_pre_point]+T(3,2)*R[grasp_pre_point]+T(3,3)*R[put_pre_point]);
				Vsdh[0][fist]=R[put_pre_fist] + gamma*(T(3,0)*R[nav_pre_fist]+T(3,1)*R[detect_pre_fist]+T(3,2)*R[grasp_pre_fist]+T(3,3)*R[put_pre_fist]);
			}
			if (action_stage=="post-config")
			{
				Vsdh[0][home]=R[put_post_home] + gamma*(T(3,0)*R[nav_post_home]+T(3,1)*R[detect_post_home]+T(3,2)*R[grasp_post_home]+T(3,3)*R[put_post_home]);
				Vsdh[0][cylclosed]=R[put_post_cylclosed] + gamma*(T(3,0)*R[nav_post_cylclosed]+T(3,1)*R[detect_post_cylclosed]+T(3,2)*R[grasp_post_cylclosed]+T(3,3)*R[put_post_cylclosed]);
				Vsdh[0][cylopen]=R[put_post_cylopen] + gamma*(T(3,0)*R[nav_post_cylopen]+T(3,1)*R[detect_post_cylopen]+T(3,2)*R[grasp_post_cylopen]+T(3,3)*R[put_post_cylopen]);
				Vsdh[0][cyltotalopen]=R[put_post_cyltotalopen] + gamma*(T(3,0)*R[nav_post_cyltotalopen]+T(3,1)*R[detect_post_cyltotalopen]+T(3,2)*R[grasp_post_cyltotalopen]+T(3,3)*R[put_post_cyltotalopen]);
				Vsdh[0][spheropen]=R[put_post_spheropen] + gamma*(T(3,0)*R[nav_post_spheropen]+T(3,1)*R[detect_post_spheropen]+T(3,2)*R[grasp_post_spheropen]+T(3,3)*R[put_post_spheropen]);
				Vsdh[0][spherclosed]=R[put_post_spherclosed] + gamma*(T(3,0)*R[nav_post_spherclosed]+T(3,1)*R[detect_post_spherclosed]+T(3,2)*R[grasp_post_spherclosed]+T(3,3)*R[put_post_spherclosed]);
				Vsdh[0][paropen]=R[put_post_paropen] + gamma*(T(3,0)*R[nav_post_paropen]+T(3,1)*R[detect_post_paropen]+T(3,2)*R[grasp_post_paropen]+T(3,3)*R[put_post_paropen]);
				Vsdh[0][parclosed]=R[put_post_parclosed] + gamma*(T(3,0)*R[nav_post_parclosed]+T(3,1)*R[detect_post_parclosed]+T(3,2)*R[grasp_post_parclosed]+T(3,3)*R[put_post_parclosed]);
				Vsdh[0][point]=R[put_post_point] + gamma*(T(3,0)*R[nav_post_point]+T(3,1)*R[detect_post_point]+T(3,2)*R[grasp_post_point]+T(3,3)*R[put_post_point]);
				Vsdh[0][fist]=R[put_post_fist] + gamma*(T(3,0)*R[nav_post_fist]+T(3,1)*R[detect_post_fist]+T(3,2)*R[grasp_post_fist]+T(3,3)*R[put_post_fist]);
			}
		}
//-----------------------Chose the best way with the function max -------------

/*result_sdh=0;
for (int j=9;j>=0;j--)
{
	if(result_sdh<Vsdh[0][j])		//function max
	{
		result_sdh=Vsdh[0][j];
		//result_sdhstate=j;			// know the state where the value function is the best
	}								// if j=0=home, j=1=cylclosed, j=2=cylopen ,etc...
}*/

//----------------------- Chose the best way with the Bees Algorithm-------------
	int temp2;
	double temp1 ;
	int nghx[dim]; // Neighborhood
	int fit[pop],sortedFit[pop],bPos[dim][pop],bPosSort[dim][pop];
	int bNghFit[pop],bNghPos[dim][pop];
	int globalFit[pop], globalPos[dim][pop];
	int candidx[dim][pop];

	srand( (unsigned)time( NULL ) );

	for(int runs=0; runs<1; runs++)
	{
		//initialise with random start positions at the start of every run
		for(int i=0;i<sdh_n;i++)
		{
			for(int d=0;d<dim;d++)
			{
			bPos[d][i]= sdh_randfunc(sdh_xs, sdh_xe);
			fit[i]=sdh_func(bPos[d][i], Vsdh);
			}
		}

		// at this point bPos contains a number of randomly initialised particles
		// fit, contains the value of the fitness function
		// thus forming a (fit,bPos) tuple

		//sort by fitness, preserving the (f,pos) tuple
		sdh_funcSort(fit, sortedFit, bPos, bPosSort, sdh_n); // bpossort contains all the sort position of the scout bees
		fit[bPosSort[0][0]]=sdh_func(bPosSort[0][0], Vsdh);

		for(int iter=0; iter<sdh_imax ;iter++)//imax number of iteration
		{
			for(int d=0;d<dim;d++)
				nghx[d] = 1;

			int aa[50]; //50 max number of selected sites out of n

				 for(int i=0;i<sdh_m;i++)
				 {
				   if(i<sdh_e)
					   aa[i]=sdh_n2;  // Number of bees around each elite point
				   else
					   aa[i]=sdh_n1;  // Number of bees around other selected point
				   }

// ----------------------------------------Neighbourhood search  ------------------------------------

			temp1=-INT_MAX;

			for(int k=0;k<sdh_e;k++)//k site
			{
				for(int j=0;j<aa[k];j++) //j recruited bee
				{
					for(int d=0;d<dim;d++)//d dimension
					{
						candidx[d][k]=bPosSort[d][k]; //define the candidate position
						if ((candidx[d][k]-nghx[d])<sdh_xs) // boundry check (left)
							{
							 bNghPos[d][j]=sdh_randfunc(sdh_xs,candidx[d][k]+nghx[d]);
							 bNghFit[j]=sdh_func(bNghPos[d][j], Vsdh);
							}
						if ((candidx[d][k]+nghx[d])>sdh_xe)// boundry check (right)
							{
							bNghPos[d][j]=sdh_randfunc(candidx[d][k]-nghx[d],sdh_xe);
							bNghFit[j]=sdh_func(bNghPos[d][j], Vsdh);
							}
						if ((candidx[d][k]-nghx[d])>=sdh_xs and (candidx[d][k]+nghx[d])<=sdh_xe )
							{
							bNghPos[d][j]=sdh_randfunc(candidx[d][k]-nghx[d] , candidx[d][k]+nghx[d]);
							bNghFit[j]=sdh_func(bNghPos[d][j], Vsdh);
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

			int ranSearchBees=sdh_n-sdh_m; // Number of bees search randomly
			for(int k=0;k<ranSearchBees;k++)	//start of random search for rest of bees
				 {
					for(int d=0;d<dim;d++)
					{
						globalPos[d][k]=sdh_randfunc(sdh_xs, sdh_xe);
						globalFit[k]=sdh_func(globalPos[d][k], Vsdh);// evaluate the fitness of the new list
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

		result_sdhstate=bPosSort[0][0]; //bPosSort[0][0] correspond to the elite site
		result_sdh = sortedFit[0]; // sortedFit[0] correspond to the value of the elite site
		std::cout << "best sdh pos: " << result_sdhstate << std::endl;
		std::cout << "best sdh fit: " << result_sdh << std::endl;

	return;
}
