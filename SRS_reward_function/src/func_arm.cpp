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

int arm_imax=500;
int arm_n= pop;  // Number of Scout Bees
int arm_m= 2;   // Number of selected Locations
int arm_n1 =6;  // Number of Bees around each selected locations ( except the ellit location )
int arm_n2 =20;  // Number of Bees around each ellit locations
int arm_e =1;   // Elite point/s

int arm_func( int i,std::vector<std::vector<float> > Varm)  // Definition of Fitness Function
{
	int y;
	y=Varm[0][i];
	  return y;
}

//------------------------------random function used in the Bees algorithm-----------------------

int	arm_xs = 0;
int	arm_xe = 16;
int arm_randfunc( int xs, int xe )  // Definition of Random number Generator Function*/
{
  double randnum;
  randnum=rand() ;
  randnum=arm_xs+randnum*(arm_xe-arm_xs) / RAND_MAX;
  int intrandnum = randnum +0.5;	//kind of rounding in order to have only 0 or 1 random number
  return intrandnum;
}

//------------------------------sorting function used in the Bees algorithm-----------------------

void arm_funcSort(int inP1[],int oP1[],int inP2[][pop],int oP2[][pop],int size)
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

void reward_arm (std::string action_name, std::string action_stage,std::string result_action, std::vector<std::vector<float> >& Varm, double& result_arm ,int& result_armstate,Eigen::Matrix4f& T)

{
	float gamma=0.1;  // define the discount factor "gamma"
	int home=0, folded=1, pregrasp=2, pregrasp_top=3, grasp=4, hold=5,pre_look_at_table=6, look_at_table=7,overtray=8, overtray_top=9, tray=10,intermediateback=11, intermediatebacklow=12, intermediatefront=13,intermediatefront_top=14,wavein=15, waveout=16;
	int nav_pre_home=17,nav_pre_folded=18,nav_pre_pregrasp=19,nav_pre_pregrasp_top=20,nav_pre_grasp=21,nav_pre_hold=22,nav_pre_pre_look_at_table=23,nav_pre_look_at_table=24,nav_pre_overtray=25,nav_pre_overtray_top=26,nav_pre_tray=27,nav_pre_intermediateback=28,nav_pre_intermediatebacklow=29,nav_pre_intermediatefront=30,nav_pre_intermediatefront_top=31,nav_pre_wavein=32,nav_pre_waveout=33;
	int detect_pre_home=34,detect_pre_folded=35,detect_pre_pregrasp=36,detect_pre_pregrasp_top=37,detect_pre_grasp=38,detect_pre_hold=39,detect_pre_pre_look_at_table=40,detect_pre_look_at_table=41,detect_pre_overtray=42,detect_pre_overtray_top=43,detect_pre_tray=44,detect_pre_intermediateback=45,detect_pre_intermediatebacklow=46,detect_pre_intermediatefront=47,detect_pre_intermediatefront_top=48,detect_pre_wavein=49,detect_pre_waveout=50;
	int grasp_pre_home=51,grasp_pre_folded=52,grasp_pre_pregrasp=53,grasp_pre_pregrasp_top=54,grasp_pre_grasp=55,grasp_pre_hold=56,grasp_pre_pre_look_at_table=57,grasp_pre_look_at_table=58,grasp_pre_overtray=59,grasp_pre_overtray_top=60,grasp_pre_tray=61,grasp_pre_intermediateback=62,grasp_pre_intermediatebacklow=63,grasp_pre_intermediatefront=64,grasp_pre_intermediatefront_top=65,grasp_pre_wavein=66,grasp_pre_waveout=67;
	int put_pre_home=68,put_pre_folded=69,put_pre_pregrasp=70,put_pre_pregrasp_top=71,put_pre_grasp=72,put_pre_hold=73,put_pre_pre_look_at_table=74,put_pre_look_at_table=75,put_pre_overtray=76,put_pre_overtray_top=77,put_pre_tray=78,put_pre_intermediateback=79,put_pre_intermediatebacklow=80,put_pre_intermediatefront=81,put_pre_intermediatefront_top=82,put_pre_wavein=83,put_pre_waveout=84;
	int nav_post_home=85,nav_post_folded=86,nav_post_pregrasp=87,nav_post_pregrasp_top=88,nav_post_grasp=89,nav_post_hold=90,nav_post_pre_look_at_table=91,nav_post_look_at_table=92,nav_post_overtray=93,nav_post_overtray_top=94,nav_post_tray=95,nav_post_intermediateback=96,nav_post_intermediatebacklow=97,nav_post_intermediatefront=98,nav_post_intermediatefront_top=99,nav_post_wavein=100,nav_post_waveout=101;
	int detect_post_home=102,detect_post_folded=103,detect_post_pregrasp=104,detect_post_pregrasp_top=105,detect_post_grasp=106,detect_post_hold=107,detect_post_pre_look_at_table=108,detect_post_look_at_table=109,detect_post_overtray=110,detect_post_overtray_top=111,detect_post_tray=112,detect_post_intermediateback=113,detect_post_intermediatebacklow=114,detect_post_intermediatefront=115,detect_post_intermediatefront_top=116,detect_post_wavein=117,detect_post_waveout=118;
	int grasp_post_home=119,grasp_post_folded=120,grasp_post_pregrasp=121,grasp_post_pregrasp_top=122,grasp_post_grasp=123,grasp_post_hold=124,grasp_post_pre_look_at_table=125,grasp_post_look_at_table=126,grasp_post_overtray=127,grasp_post_overtray_top=128,grasp_post_tray=129,grasp_post_intermediateback=130,grasp_post_intermediatebacklow=131,grasp_post_intermediatefront=132,grasp_post_intermediatefront_top=133,grasp_post_wavein=134,grasp_post_waveout=135;
	int put_post_home=0,put_post_folded=1,put_post_pregrasp=2,put_post_pregrasp_top=3,put_post_grasp=4,put_post_hold=5,put_post_pre_look_at_table=6,put_post_look_at_table=7,put_post_overtray=8,put_post_overtray_top=9,put_post_tray=10,put_post_intermediateback=11,put_post_intermediatebacklow=12,put_post_intermediatefront=13,put_post_intermediatefront_top=14,put_post_wavein=15,put_post_waveout=16;
	std::vector<float> R;   //create a vector R with an unknown size
		R.resize(136);  // define the size of the vector
	Varm.resize(2);
	for (int i=1;i>=0;i--)
	{
	Varm[i].resize(16);
	}

	//----- definition of the reward -----
			R[nav_pre_home]=3;					R[detect_pre_home]=4;					R[grasp_pre_home]=7;					R[put_pre_home]=4;
			R[nav_pre_folded]=131;				R[detect_pre_folded]=10;				R[grasp_pre_folded]=10;					R[put_pre_folded]=3;
			R[nav_pre_pregrasp]=3;				R[detect_pre_pregrasp]=7;				R[grasp_pre_pregrasp]=2;				R[put_pre_pregrasp]=8;
			R[nav_pre_pregrasp_top]=2;			R[detect_pre_pregrasp_top]=1;			R[grasp_pre_pregrasp_top]=3;			R[put_pre_pregrasp_top]=9;
			R[nav_pre_grasp]=4;					R[detect_pre_grasp]=2;					R[grasp_pre_grasp]=1;					R[put_pre_grasp]=1;
			R[nav_pre_hold]=3;					R[detect_pre_hold]=7;					R[grasp_pre_hold]=50;					R[put_pre_hold]=20;
			R[nav_pre_pre_look_at_table]=1;		R[detect_pre_pre_look_at_table]=4;		R[grasp_pre_pre_look_at_table]=1;		R[put_pre_pre_look_at_table]=7;
			R[nav_pre_look_at_table]=100;		R[detect_pre_look_at_table]=300;		R[grasp_pre_look_at_table]=500;			R[put_pre_look_at_table]=3;
			R[nav_pre_overtray]=3;				R[detect_pre_overtray]=1;				R[grasp_pre_overtray]=2;				R[put_pre_overtray]=2;
			R[nav_pre_overtray_top]=4;			R[detect_pre_overtray_top]=2;			R[grasp_pre_overtray_top]=4;			R[put_pre_overtray_top]=3;
			R[nav_pre_tray]=1;					R[detect_pre_tray]=8;					R[grasp_pre_tray]=5;					R[put_pre_tray]=5;
			R[nav_pre_intermediateback]=2;		R[detect_pre_intermediateback]=7;		R[grasp_pre_intermediateback]=8;		R[put_pre_intermediateback]=8;
			R[nav_pre_intermediatebacklow]=3;	R[detect_pre_intermediatebacklow]=1;	R[grasp_pre_intermediatebacklow]=7;		R[put_pre_intermediatebacklow]=7;
			R[nav_pre_intermediatefront]=4;		R[detect_pre_intermediatefront]=4;		R[grasp_pre_intermediatefront]=4;		R[put_pre_intermediatefront]=4;
			R[nav_pre_intermediatefront_top]=5;	R[detect_pre_intermediatefront_top]=5;	R[grasp_pre_intermediatefront_top]=5;	R[put_pre_intermediatefront_top]=5;
			R[nav_pre_wavein]=2;				R[detect_pre_wavein]=6;					R[grasp_pre_wavein]=7;					R[put_pre_wavein]=4;
			R[nav_pre_waveout]=1;				R[detect_pre_waveout]=7;				R[grasp_pre_waveout]=1;					R[put_pre_waveout]=7;

			R[nav_post_home]=5;					R[detect_post_home]=2;					R[grasp_post_home]=4;					R[put_post_home]=4;
			R[nav_post_folded]=69;				R[detect_post_folded]=6;				R[grasp_post_folded]=6;					R[put_post_folded]=181;
			R[nav_post_pregrasp]=3;				R[detect_post_pregrasp]=5;				R[grasp_post_pregrasp]=4;				R[put_post_pregrasp]=4;
			R[nav_post_pregrasp_top]=4;			R[detect_post_pregrasp_top]=2;			R[grasp_post_pregrasp_top]=1;			R[put_post_pregrasp_top]=1;
			R[nav_post_grasp]=5;				R[detect_post_grasp]=1;					R[grasp_post_grasp]=2;					R[put_post_grasp]=2;
			R[nav_post_hold]=3;					R[detect_post_hold]=5;					R[grasp_post_hold]=64;					R[put_post_hold]=4;
			R[nav_post_pre_look_at_table]=7;	R[detect_post_pre_look_at_table]=6;		R[grasp_post_pre_look_at_table]=7;		R[put_post_pre_look_at_table]=7;
			R[nav_post_look_at_table]=70;		R[detect_post_look_at_table]=14;		R[grasp_post_look_at_table]=50;			R[put_post_look_at_table]=179;
			R[nav_post_overtray]=9;				R[detect_post_overtray]=1;				R[grasp_post_overtray]=6;				R[put_post_overtray]=9;
			R[nav_post_overtray_top]=50;		R[detect_post_overtray_top]=5;			R[grasp_post_overtray_top]=5;			R[put_post_overtray_top]=50;
			R[nav_post_tray]=9;					R[detect_post_tray]=3;					R[grasp_post_tray]=7;					R[put_post_tray]=7;
			R[nav_post_intermediateback]=8;		R[detect_post_intermediateback]=1;		R[grasp_post_intermediateback]=8;		R[put_post_intermediateback]=8;
			R[nav_post_intermediatebacklow]=7;	R[detect_post_intermediatebacklow]=4;	R[grasp_post_intermediatebacklow]=6;	R[put_post_intermediatebacklow]=6;
			R[nav_post_intermediatefront]=6;	R[detect_post_intermediatefront]=5;		R[grasp_post_intermediatefront]=6;		R[put_post_intermediatefront]=5;
			R[nav_post_intermediatefront_top]=5;R[detect_post_intermediatefront_top]=2;	R[grasp_post_intermediatefront_top]=5;	R[put_post_intermediatefront_top]=4;
			R[nav_post_wavein]=4;				R[detect_post_wavein]=6;				R[grasp_post_wavein]=4;					R[put_post_wavein]=3;
			R[nav_post_waveout]=3;				R[detect_post_waveout]=5;				R[grasp_post_waveout]=3;				R[put_post_waveout]=2;

		if (action_name=="navigation")
		{
			if (action_stage=="pre-config")
			{
				Varm[0][home]=R[nav_pre_home] + gamma*(T(0,0)*R[nav_pre_home]+T(0,1)*R[detect_pre_home]+T(0,2)*R[grasp_pre_home]+T(0,3)*R[put_pre_home]);
				Varm[0][folded]=R[nav_pre_folded] + gamma*(T(0,0)*R[nav_pre_folded]+T(0,1)*R[detect_pre_folded]+T(0,2)*+R[grasp_pre_folded]+T(0,3)*R[put_pre_folded]);
				Varm[0][pregrasp]=R[nav_pre_pregrasp] + gamma*(T(0,0)*R[nav_pre_pregrasp]+T(0,1)*R[detect_pre_pregrasp]+T(0,2)*R[grasp_pre_pregrasp]+T(0,3)*R[put_pre_pregrasp]);
				Varm[0][pregrasp_top]=R[nav_pre_pregrasp_top] + gamma*(T(0,0)*R[nav_pre_pregrasp_top]+T(0,1)*R[detect_pre_pregrasp_top]+T(0,2)*R[grasp_pre_pregrasp_top]+T(0,3)*R[put_pre_pregrasp_top]);
				Varm[0][grasp]=R[nav_pre_grasp] + gamma*(T(0,0)*R[nav_pre_grasp]+T(0,1)*R[detect_pre_grasp]+T(0,2)*R[grasp_pre_grasp]+T(0,3)*R[put_pre_grasp]);
				Varm[0][hold]=R[nav_pre_hold] + gamma*(T(0,0)*R[nav_pre_hold]+T(0,1)*R[detect_pre_hold]+T(0,2)*R[grasp_pre_hold]+T(0,3)*R[put_pre_hold]);
				Varm[0][pre_look_at_table]=R[nav_pre_pre_look_at_table] + gamma*(T(0,0)*R[nav_pre_pre_look_at_table]+T(0,1)*R[detect_pre_pre_look_at_table]+T(0,2)*R[grasp_pre_pre_look_at_table]+T(0,3)*R[put_pre_pre_look_at_table]);
				Varm[0][look_at_table]=R[nav_pre_look_at_table] + gamma*(T(0,0)*R[nav_pre_look_at_table]+T(0,1)*R[detect_pre_look_at_table]+T(0,2)*R[grasp_pre_look_at_table]+T(0,3)*R[put_pre_look_at_table]);
				Varm[0][overtray]=R[nav_pre_overtray] + gamma*(T(0,0)*R[nav_pre_overtray]+T(0,1)*R[detect_pre_overtray]+T(0,2)*R[grasp_pre_overtray]+T(0,3)*R[put_pre_overtray]);
				Varm[0][overtray_top]=R[nav_pre_overtray_top] + gamma*(T(0,0)*R[nav_pre_overtray_top]+T(0,1)*R[detect_pre_overtray_top]+T(0,2)*R[grasp_pre_overtray_top]+T(0,3)*R[put_pre_overtray_top]);
				Varm[0][tray]=R[nav_pre_tray] + gamma*(T(0,0)*R[nav_pre_tray]+T(0,1)*R[detect_pre_tray]+T(0,2)*R[grasp_pre_tray]+T(0,3)*R[put_pre_tray]);
				Varm[0][intermediateback]=R[nav_pre_intermediateback] + gamma*(T(0,0)*R[nav_pre_intermediateback]+T(0,1)*R[detect_pre_intermediateback]+T(0,2)*R[grasp_pre_intermediateback]+T(0,3)*R[put_pre_intermediateback]);
				Varm[0][intermediatebacklow]=R[nav_pre_intermediatebacklow] + gamma*(T(0,0)*R[nav_pre_intermediatebacklow]+T(0,1)*R[detect_pre_intermediatebacklow]+T(0,2)*R[grasp_pre_intermediatebacklow]+T(0,3)*R[put_pre_intermediatebacklow]);
				Varm[0][intermediatefront]=R[nav_pre_intermediatefront] + gamma*(T(0,0)*R[nav_pre_intermediatefront]+T(0,1)*R[detect_pre_intermediatefront]+T(0,2)*R[grasp_pre_intermediatefront]+T(0,3)*R[put_pre_intermediatefront]);
				Varm[0][intermediatefront_top]=R[nav_pre_intermediatefront_top] + gamma*(T(0,0)*R[nav_pre_intermediatefront_top]+T(0,1)*R[detect_pre_intermediatefront_top]+T(0,2)*R[grasp_pre_intermediatefront_top]+T(0,3)*R[put_pre_intermediatefront_top]);
				Varm[0][wavein]=R[nav_pre_wavein] + gamma*(T(0,0)*R[nav_pre_wavein]+T(0,1)*R[detect_pre_wavein]+T(0,2)*R[grasp_pre_wavein]+T(0,3)*R[put_pre_wavein]);
				Varm[0][waveout]=R[nav_pre_waveout] + gamma*(T(0,0)*R[nav_pre_waveout]+T(0,1)*R[detect_pre_waveout]+T(0,2)*R[grasp_pre_waveout]+T(0,3)*R[put_pre_waveout]);
			}
			if (action_stage=="post-config")
			{
				Varm[0][home]=R[nav_post_home] + gamma*(T(0,0)*R[nav_post_home]+T(0,1)*R[detect_post_home]+T(0,2)*R[grasp_post_home]+T(0,3)*R[put_post_home]);
				Varm[0][folded]=R[nav_post_folded] + gamma*(T(0,0)*R[nav_post_folded]+T(0,1)*R[detect_post_folded]+T(0,2)*R[grasp_post_folded]+T(0,3)*R[put_post_folded]);
				Varm[0][pregrasp]=R[nav_post_pregrasp] + gamma*(T(0,0)*R[nav_post_pregrasp]+T(0,1)*R[detect_post_pregrasp]+T(0,2)*R[grasp_post_pregrasp]+T(0,3)*R[put_post_pregrasp]);
				Varm[0][pregrasp_top]=R[nav_post_pregrasp_top] + gamma*(T(0,0)*R[nav_post_pregrasp_top]+T(0,1)*R[detect_post_pregrasp_top]+T(0,2)*R[grasp_post_pregrasp_top]+T(0,3)*R[put_post_pregrasp_top]);
				Varm[0][grasp]=R[nav_post_grasp] + gamma*(T(0,0)*R[nav_post_grasp]+T(0,1)*R[detect_post_grasp]+T(0,2)*R[grasp_post_grasp]+T(0,3)*R[put_post_grasp]);
				Varm[0][hold]=R[nav_post_hold] + gamma*(T(0,0)*R[nav_post_hold]+T(0,1)*R[detect_post_hold]+T(0,2)*R[grasp_post_hold]+T(0,3)*R[put_post_hold]);
				Varm[0][pre_look_at_table]=R[nav_post_pre_look_at_table] + gamma*(T(0,0)*R[nav_post_pre_look_at_table]+T(0,1)*R[detect_post_pre_look_at_table]+T(0,2)*R[grasp_post_pre_look_at_table]+T(0,3)*R[put_post_pre_look_at_table]);
				Varm[0][look_at_table]=R[nav_post_look_at_table] + gamma*(T(0,0)*R[nav_post_look_at_table]+T(0,1)*R[detect_post_look_at_table]+T(0,2)*R[grasp_post_look_at_table]+T(0,3)*R[put_post_look_at_table]);
				Varm[0][overtray]=R[nav_post_overtray] + gamma*(T(0,0)*R[nav_post_overtray]+T(0,1)*R[detect_post_overtray]+T(0,2)*R[grasp_post_overtray]+T(0,3)*R[put_post_overtray]);
				Varm[0][overtray_top]=R[nav_post_overtray_top] + gamma*(T(0,0)*R[nav_post_overtray_top]+T(0,1)*R[detect_post_overtray_top]+T(0,2)*R[grasp_post_overtray_top]+T(0,3)*R[put_post_overtray_top]);
				Varm[0][tray]=R[nav_post_tray] + gamma*(T(0,0)*R[nav_post_tray]+T(0,1)*R[detect_post_tray]+T(0,2)*R[grasp_post_tray]+T(0,3)*R[put_post_tray]);
				Varm[0][intermediateback]=R[nav_post_intermediateback] + gamma*(T(0,0)*R[nav_post_intermediateback]+T(0,1)*R[detect_post_intermediateback]+T(0,2)*R[grasp_post_intermediateback]+T(0,3)*R[put_post_intermediateback]);
				Varm[0][intermediatebacklow]=R[nav_post_intermediatebacklow] + gamma*(T(0,0)*R[nav_post_intermediatebacklow]+T(0,1)*R[detect_post_intermediatebacklow]+T(0,2)*R[grasp_post_intermediatebacklow]+T(0,3)*R[put_post_intermediatebacklow]);
				Varm[0][intermediatefront]=R[nav_post_intermediatefront] + gamma*(T(0,0)*R[nav_post_intermediatefront]+T(0,1)*R[detect_post_intermediatefront]+T(0,2)*R[grasp_post_intermediatefront]+T(0,3)*R[put_post_intermediatefront]);
				Varm[0][intermediatefront_top]=R[nav_post_intermediatefront_top] + gamma*(T(0,0)*R[nav_post_intermediatefront_top]+T(0,1)*R[detect_post_intermediatefront_top]+T(0,2)*R[grasp_post_intermediatefront_top]+T(0,3)*R[put_post_intermediatefront_top]);
				Varm[0][wavein]=R[nav_post_wavein] + gamma*(T(0,0)*R[nav_post_wavein]+T(0,1)*R[detect_post_wavein]+T(0,2)*R[grasp_post_wavein]+T(0,3)*R[put_post_wavein]);
				Varm[0][waveout]=R[nav_post_waveout] + gamma*(T(0,0)*R[nav_post_waveout]+T(0,1)*R[detect_post_waveout]+T(0,2)*R[grasp_post_waveout]+T(0,3)*R[put_post_waveout]);
			}
		}
		if (action_name=="detection")
		{
			if (action_stage=="pre-config")
			{
				Varm[0][home]=R[detect_pre_home] + gamma*(T(1,0)*R[nav_pre_home]+T(1,1)*R[detect_pre_home]+T(1,2)*R[grasp_pre_home]+T(1,3)*R[put_pre_home]);
				Varm[0][folded]=R[detect_pre_folded] + gamma*(T(1,0)*R[nav_pre_folded]+T(1,1)*R[detect_pre_folded]+T(1,2)*+R[grasp_pre_folded]+T(1,3)*R[put_pre_folded]);
				Varm[0][pregrasp]=R[detect_pre_pregrasp] + gamma*(T(1,0)*R[nav_pre_pregrasp]+T(1,1)*R[detect_pre_pregrasp]+T(1,2)*R[grasp_pre_pregrasp]+T(1,3)*R[put_pre_pregrasp]);
				Varm[0][pregrasp_top]=R[detect_pre_pregrasp_top] + gamma*(T(1,0)*R[nav_pre_pregrasp_top]+T(1,1)*R[detect_pre_pregrasp_top]+T(1,2)*R[grasp_pre_pregrasp_top]+T(1,3)*R[put_pre_pregrasp_top]);
				Varm[0][grasp]=R[detect_pre_grasp] + gamma*(T(1,0)*R[nav_pre_grasp]+T(1,1)*R[detect_pre_grasp]+T(1,2)*R[grasp_pre_grasp]+T(1,3)*R[put_pre_grasp]);
				Varm[0][hold]=R[detect_pre_hold] + gamma*(T(1,0)*R[nav_pre_hold]+T(1,1)*R[detect_pre_hold]+T(1,2)*R[grasp_pre_hold]+T(1,3)*R[put_pre_hold]);
				Varm[0][pre_look_at_table]=R[detect_pre_pre_look_at_table] + gamma*(T(1,0)*R[nav_pre_pre_look_at_table]+T(1,1)*R[detect_pre_pre_look_at_table]+T(1,2)*R[grasp_pre_pre_look_at_table]+T(1,3)*R[put_pre_pre_look_at_table]);
				Varm[0][look_at_table]=R[detect_pre_look_at_table] + gamma*(T(1,0)*R[nav_pre_look_at_table]+T(1,1)*R[detect_pre_look_at_table]+T(1,2)*R[grasp_pre_look_at_table]+T(1,3)*R[put_pre_look_at_table]);
				Varm[0][overtray]=R[detect_pre_overtray] + gamma*(T(1,0)*R[nav_pre_overtray]+T(1,1)*R[detect_pre_overtray]+T(1,2)*R[grasp_pre_overtray]+T(1,3)*R[put_pre_overtray]);
				Varm[0][overtray_top]=R[detect_pre_overtray_top] + gamma*(T(1,0)*R[nav_pre_overtray_top]+T(1,1)*R[detect_pre_overtray_top]+T(1,2)*R[grasp_pre_overtray_top]+T(1,3)*R[put_pre_overtray_top]);
				Varm[0][tray]=R[detect_pre_tray] + gamma*(T(1,0)*R[nav_pre_tray]+T(1,1)*R[detect_pre_tray]+T(1,2)*R[grasp_pre_tray]+T(1,3)*R[put_pre_tray]);
				Varm[0][intermediateback]=R[detect_pre_intermediateback] + gamma*(T(1,0)*R[nav_pre_intermediateback]+T(1,1)*R[detect_pre_intermediateback]+T(1,2)*R[grasp_pre_intermediateback]+T(1,3)*R[put_pre_intermediateback]);
				Varm[0][intermediatebacklow]=R[detect_pre_intermediatebacklow] + gamma*(T(1,0)*R[nav_pre_intermediatebacklow]+T(1,1)*R[detect_pre_intermediatebacklow]+T(1,2)*R[grasp_pre_intermediatebacklow]+T(1,3)*R[put_pre_intermediatebacklow]);
				Varm[0][intermediatefront]=R[detect_pre_intermediatefront] + gamma*(T(1,0)*R[nav_pre_intermediatefront]+T(1,1)*R[detect_pre_intermediatefront]+T(1,2)*R[grasp_pre_intermediatefront]+T(1,3)*R[put_pre_intermediatefront]);
				Varm[0][intermediatefront_top]=R[detect_pre_intermediatefront_top] + gamma*(T(1,0)*R[nav_pre_intermediatefront_top]+T(1,1)*R[detect_pre_intermediatefront_top]+T(1,2)*R[grasp_pre_intermediatefront_top]+T(1,3)*R[put_pre_intermediatefront_top]);
				Varm[0][wavein]=R[detect_pre_wavein] + gamma*(T(1,0)*R[nav_pre_wavein]+T(1,1)*R[detect_pre_wavein]+T(1,2)*R[grasp_pre_wavein]+T(1,3)*R[put_pre_wavein]);
				Varm[0][waveout]=R[detect_pre_waveout] + gamma*(T(1,0)*R[nav_pre_waveout]+T(1,1)*R[detect_pre_waveout]+T(1,2)*R[grasp_pre_waveout]+T(1,3)*R[put_pre_waveout]);
			}
			if (action_stage=="post-config")
			{
				Varm[0][home]=R[detect_post_home] + gamma*(T(1,0)*R[nav_post_home]+T(1,1)*R[detect_post_home]+T(1,2)*R[grasp_post_home]+T(1,3)*R[put_post_home]);
				Varm[0][folded]=R[detect_post_folded] + gamma*(T(1,0)*R[nav_post_folded]+T(1,1)*R[detect_post_folded]+T(1,2)*R[grasp_post_folded]+T(1,3)*R[put_post_folded]);
				Varm[0][pregrasp]=R[detect_post_pregrasp] + gamma*(T(1,0)*R[nav_post_pregrasp]+T(1,1)*R[detect_post_pregrasp]+T(1,2)*R[grasp_post_pregrasp]+T(1,3)*R[put_post_pregrasp]);
				Varm[0][pregrasp_top]=R[detect_post_pregrasp_top] + gamma*(T(1,0)*R[nav_post_pregrasp_top]+T(1,1)*R[detect_post_pregrasp_top]+T(1,2)*R[grasp_post_pregrasp_top]+T(1,3)*R[put_post_pregrasp_top]);
				Varm[0][grasp]=R[detect_post_grasp] + gamma*(T(1,0)*R[nav_post_grasp]+T(1,1)*R[detect_post_grasp]+T(1,2)*R[grasp_post_grasp]+T(1,3)*R[put_post_grasp]);
				Varm[0][hold]=R[detect_post_hold] + gamma*(T(1,0)*R[nav_post_hold]+T(1,1)*R[detect_post_hold]+T(1,2)*R[grasp_post_hold]+T(1,3)*R[put_post_hold]);
				Varm[0][pre_look_at_table]=R[detect_post_pre_look_at_table] + gamma*(T(1,0)*R[nav_post_pre_look_at_table]+T(1,1)*R[detect_post_pre_look_at_table]+T(1,2)*R[grasp_post_pre_look_at_table]+T(1,3)*R[put_post_pre_look_at_table]);
				Varm[0][look_at_table]=R[detect_post_look_at_table] + gamma*(T(1,0)*R[nav_post_look_at_table]+T(1,1)*R[detect_post_look_at_table]+T(1,2)*R[grasp_post_look_at_table]+T(1,3)*R[put_post_look_at_table]);
				Varm[0][overtray]=R[detect_post_overtray] + gamma*(T(1,0)*R[nav_post_overtray]+T(1,1)*R[detect_post_overtray]+T(1,2)*R[grasp_post_overtray]+T(1,3)*R[put_post_overtray]);
				Varm[0][overtray_top]=R[detect_post_overtray_top] + gamma*(T(1,0)*R[nav_post_overtray_top]+T(1,1)*R[detect_post_overtray_top]+T(1,2)*R[grasp_post_overtray_top]+T(1,3)*R[put_post_overtray_top]);
				Varm[0][tray]=R[detect_post_tray] + gamma*(T(1,0)*R[nav_post_tray]+T(1,1)*R[detect_post_tray]+T(1,2)*R[grasp_post_tray]+T(1,3)*R[put_post_tray]);
				Varm[0][intermediateback]=R[detect_post_intermediateback] + gamma*(T(1,0)*R[nav_post_intermediateback]+T(1,1)*R[detect_post_intermediateback]+T(1,2)*R[grasp_post_intermediateback]+T(1,3)*R[put_post_intermediateback]);
				Varm[0][intermediatebacklow]=R[detect_post_intermediatebacklow] + gamma*(T(1,0)*R[nav_post_intermediatebacklow]+T(1,1)*R[detect_post_intermediatebacklow]+T(1,2)*R[grasp_post_intermediatebacklow]+T(1,3)*R[put_post_intermediatebacklow]);
				Varm[0][intermediatefront]=R[detect_post_intermediatefront] + gamma*(T(1,0)*R[nav_post_intermediatefront]+T(1,1)*R[detect_post_intermediatefront]+T(1,2)*R[grasp_post_intermediatefront]+T(1,3)*R[put_post_intermediatefront]);
				Varm[0][intermediatefront_top]=R[detect_post_intermediatefront_top] + gamma*(T(1,0)*R[nav_post_intermediatefront_top]+T(1,1)*R[detect_post_intermediatefront_top]+T(1,2)*R[grasp_post_intermediatefront_top]+T(1,3)*R[put_post_intermediatefront_top]);
				Varm[0][wavein]=R[detect_post_wavein] + gamma*(T(1,0)*R[nav_post_wavein]+T(1,1)*R[detect_post_wavein]+T(1,2)*R[grasp_post_wavein]+T(1,3)*R[put_post_wavein]);
				Varm[0][waveout]=R[detect_post_waveout] + gamma*(T(1,0)*R[nav_post_waveout]+T(1,1)*R[detect_post_waveout]+T(1,2)*R[grasp_post_waveout]+T(1,3)*R[put_post_waveout]);
			}
		}
		if (action_name=="grasp")
		{
			if (action_stage=="pre-config")
			{
				Varm[0][home]=R[grasp_pre_home] + gamma*(T(2,0)*R[nav_pre_home]+T(2,1)*R[detect_pre_home]+T(2,2)*R[grasp_pre_home]+T(2,3)*R[put_pre_home]);
				Varm[0][folded]=R[grasp_pre_folded] + gamma*(T(2,0)*R[nav_pre_folded]+T(2,1)*R[detect_pre_folded]+T(2,2)*+R[grasp_pre_folded]+T(2,3)*R[put_pre_folded]);
				Varm[0][pregrasp]=R[grasp_pre_pregrasp] + gamma*(T(2,0)*R[nav_pre_pregrasp]+T(2,1)*R[detect_pre_pregrasp]+T(2,2)*R[grasp_pre_pregrasp]+T(2,3)*R[put_pre_pregrasp]);
				Varm[0][pregrasp_top]=R[grasp_pre_pregrasp_top] + gamma*(T(2,0)*R[nav_pre_pregrasp_top]+T(2,1)*R[detect_pre_pregrasp_top]+T(2,2)*R[grasp_pre_pregrasp_top]+T(2,3)*R[put_pre_pregrasp_top]);
				Varm[0][grasp]=R[grasp_pre_grasp] + gamma*(T(2,0)*R[nav_pre_grasp]+T(2,1)*R[detect_pre_grasp]+T(2,2)*R[grasp_pre_grasp]+T(2,3)*R[put_pre_grasp]);
				Varm[0][hold]=R[grasp_pre_hold] + gamma*(T(2,0)*R[nav_pre_hold]+T(2,1)*R[detect_pre_hold]+T(2,2)*R[grasp_pre_hold]+T(2,3)*R[put_pre_hold]);
				Varm[0][pre_look_at_table]=R[grasp_pre_pre_look_at_table] + gamma*(T(2,0)*R[nav_pre_pre_look_at_table]+T(2,1)*R[detect_pre_pre_look_at_table]+T(2,2)*R[grasp_pre_pre_look_at_table]+T(2,3)*R[put_pre_pre_look_at_table]);
				Varm[0][look_at_table]=R[grasp_pre_look_at_table] + gamma*(T(2,0)*R[nav_pre_look_at_table]+T(2,1)*R[detect_pre_look_at_table]+T(2,2)*R[grasp_pre_look_at_table]+T(2,3)*R[put_pre_look_at_table]);
				Varm[0][overtray]=R[grasp_pre_overtray] + gamma*(T(2,0)*R[nav_pre_overtray]+T(2,1)*R[detect_pre_overtray]+T(2,2)*R[grasp_pre_overtray]+T(2,3)*R[put_pre_overtray]);
				Varm[0][overtray_top]=R[grasp_pre_overtray_top] + gamma*(T(2,0)*R[nav_pre_overtray_top]+T(2,1)*R[detect_pre_overtray_top]+T(2,2)*R[grasp_pre_overtray_top]+T(2,3)*R[put_pre_overtray_top]);
				Varm[0][tray]=R[grasp_pre_tray] + gamma*(T(2,0)*R[nav_pre_tray]+T(2,1)*R[detect_pre_tray]+T(2,2)*R[grasp_pre_tray]+T(2,3)*R[put_pre_tray]);
				Varm[0][intermediateback]=R[grasp_pre_intermediateback] + gamma*(T(2,0)*R[nav_pre_intermediateback]+T(2,1)*R[detect_pre_intermediateback]+T(2,2)*R[grasp_pre_intermediateback]+T(2,3)*R[put_pre_intermediateback]);
				Varm[0][intermediatebacklow]=R[grasp_pre_intermediatebacklow] + gamma*(T(2,0)*R[nav_pre_intermediatebacklow]+T(2,1)*R[detect_pre_intermediatebacklow]+T(2,2)*R[grasp_pre_intermediatebacklow]+T(2,3)*R[put_pre_intermediatebacklow]);
				Varm[0][intermediatefront]=R[grasp_pre_intermediatefront] + gamma*(T(2,0)*R[nav_pre_intermediatefront]+T(2,1)*R[detect_pre_intermediatefront]+T(2,2)*R[grasp_pre_intermediatefront]+T(2,3)*R[put_pre_intermediatefront]);
				Varm[0][intermediatefront_top]=R[grasp_pre_intermediatefront_top] + gamma*(T(2,0)*R[nav_pre_intermediatefront_top]+T(2,1)*R[detect_pre_intermediatefront_top]+T(2,2)*R[grasp_pre_intermediatefront_top]+T(2,3)*R[put_pre_intermediatefront_top]);
				Varm[0][wavein]=R[grasp_pre_wavein] + gamma*(T(2,0)*R[nav_pre_wavein]+T(2,1)*R[detect_pre_wavein]+T(2,2)*R[grasp_pre_wavein]+T(2,3)*R[put_pre_wavein]);
				Varm[0][waveout]=R[grasp_pre_waveout] + gamma*(T(2,0)*R[nav_pre_waveout]+T(2,1)*R[detect_pre_waveout]+T(2,2)*R[grasp_pre_waveout]+T(2,3)*R[put_pre_waveout]);
			}
			if (action_stage=="post-config")
			{
				Varm[0][home]=R[grasp_post_home] + gamma*(T(2,0)*R[nav_post_home]+T(2,1)*R[detect_post_home]+T(2,2)*R[grasp_post_home]+T(2,3)*R[put_post_home]);
				Varm[0][folded]=R[grasp_post_folded] + gamma*(T(2,0)*R[nav_post_folded]+T(2,1)*R[detect_post_folded]+T(2,2)*R[grasp_post_folded]+T(2,3)*R[put_post_folded]);
				Varm[0][pregrasp]=R[grasp_post_pregrasp] + gamma*(T(2,0)*R[nav_post_pregrasp]+T(2,1)*R[detect_post_pregrasp]+T(2,2)*R[grasp_post_pregrasp]+T(2,3)*R[put_post_pregrasp]);
				Varm[0][pregrasp_top]=R[grasp_post_pregrasp_top] + gamma*(T(2,0)*R[nav_post_pregrasp_top]+T(2,1)*R[detect_post_pregrasp_top]+T(2,2)*R[grasp_post_pregrasp_top]+T(2,3)*R[put_post_pregrasp_top]);
				Varm[0][grasp]=R[grasp_post_grasp] + gamma*(T(2,0)*R[nav_post_grasp]+T(2,1)*R[detect_post_grasp]+T(2,2)*R[grasp_post_grasp]+T(2,3)*R[put_post_grasp]);
				Varm[0][hold]=R[grasp_post_hold] + gamma*(T(2,0)*R[nav_post_hold]+T(2,1)*R[detect_post_hold]+T(2,2)*R[grasp_post_hold]+T(2,3)*R[put_post_hold]);
				Varm[0][pre_look_at_table]=R[grasp_post_pre_look_at_table] + gamma*(T(2,0)*R[nav_post_pre_look_at_table]+T(2,1)*R[detect_post_pre_look_at_table]+T(2,2)*R[grasp_post_pre_look_at_table]+T(2,3)*R[put_post_pre_look_at_table]);
				Varm[0][look_at_table]=R[grasp_post_look_at_table] + gamma*(T(2,0)*R[nav_post_look_at_table]+T(2,1)*R[detect_post_look_at_table]+T(2,2)*R[grasp_post_look_at_table]+T(2,3)*R[put_post_look_at_table]);
				Varm[0][overtray]=R[grasp_post_overtray] + gamma*(T(2,0)*R[nav_post_overtray]+T(2,1)*R[detect_post_overtray]+T(2,2)*R[grasp_post_overtray]+T(2,3)*R[put_post_overtray]);
				Varm[0][overtray_top]=R[grasp_post_overtray_top] + gamma*(T(2,0)*R[nav_post_overtray_top]+T(2,1)*R[detect_post_overtray_top]+T(2,2)*R[grasp_post_overtray_top]+T(2,3)*R[put_post_overtray_top]);
				Varm[0][tray]=R[grasp_post_tray] + gamma*(T(2,0)*R[nav_post_tray]+T(2,1)*R[detect_post_tray]+T(2,2)*R[grasp_post_tray]+T(2,3)*R[put_post_tray]);
				Varm[0][intermediateback]=R[grasp_post_intermediateback] + gamma*(T(2,0)*R[nav_post_intermediateback]+T(2,1)*R[detect_post_intermediateback]+T(2,2)*R[grasp_post_intermediateback]+T(2,3)*R[put_post_intermediateback]);
				Varm[0][intermediatebacklow]=R[grasp_post_intermediatebacklow] + gamma*(T(2,0)*R[nav_post_intermediatebacklow]+T(2,1)*R[detect_post_intermediatebacklow]+T(2,2)*R[grasp_post_intermediatebacklow]+T(2,3)*R[put_post_intermediatebacklow]);
				Varm[0][intermediatefront]=R[grasp_post_intermediatefront] + gamma*(T(2,0)*R[nav_post_intermediatefront]+T(2,1)*R[detect_post_intermediatefront]+T(2,2)*R[grasp_post_intermediatefront]+T(2,3)*R[put_post_intermediatefront]);
				Varm[0][intermediatefront_top]=R[grasp_post_intermediatefront_top] + gamma*(T(2,0)*R[nav_post_intermediatefront_top]+T(2,1)*R[detect_post_intermediatefront_top]+T(2,2)*R[grasp_post_intermediatefront_top]+T(2,3)*R[put_post_intermediatefront_top]);
				Varm[0][wavein]=R[grasp_post_wavein] + gamma*(T(2,0)*R[nav_post_wavein]+T(2,1)*R[detect_post_wavein]+T(2,2)*R[grasp_post_wavein]+T(2,3)*R[put_post_wavein]);
				Varm[0][waveout]=R[grasp_post_waveout] + gamma*(T(2,0)*R[nav_post_waveout]+T(2,1)*R[detect_post_waveout]+T(2,2)*R[grasp_post_waveout]+T(2,3)*R[put_post_waveout]);
			}
		}
		if (action_name=="put_on_tray")
		{
			if (action_stage=="pre-config")
			{
				Varm[0][home]=R[put_pre_home] + gamma*(T(3,0)*R[nav_pre_home]+T(3,1)*R[detect_pre_home]+T(3,2)*R[grasp_pre_home]+T(3,3)*R[put_pre_home]);
				Varm[0][folded]=R[put_pre_folded] + gamma*(T(3,0)*R[nav_pre_folded]+T(3,1)*R[detect_pre_folded]+T(3,2)*+R[grasp_pre_folded]+T(3,3)*R[put_pre_folded]);
				Varm[0][pregrasp]=R[put_pre_pregrasp] + gamma*(T(3,0)*R[nav_pre_pregrasp]+T(3,1)*R[detect_pre_pregrasp]+T(3,2)*R[grasp_pre_pregrasp]+T(3,3)*R[put_pre_pregrasp]);
				Varm[0][pregrasp_top]=R[put_pre_pregrasp_top] + gamma*(T(3,0)*R[nav_pre_pregrasp_top]+T(3,1)*R[detect_pre_pregrasp_top]+T(3,2)*R[grasp_pre_pregrasp_top]+T(3,3)*R[put_pre_pregrasp_top]);
				Varm[0][grasp]=R[put_pre_grasp] + gamma*(T(3,0)*R[nav_pre_grasp]+T(3,1)*R[detect_pre_grasp]+T(3,2)*R[grasp_pre_grasp]+T(3,3)*R[put_pre_grasp]);
				Varm[0][hold]=R[put_pre_hold] + gamma*(T(3,0)*R[nav_pre_hold]+T(3,1)*R[detect_pre_hold]+T(3,2)*R[grasp_pre_hold]+T(3,3)*R[put_pre_hold]);
				Varm[0][pre_look_at_table]=R[put_pre_pre_look_at_table] + gamma*(T(3,0)*R[nav_pre_pre_look_at_table]+T(3,1)*R[detect_pre_pre_look_at_table]+T(3,2)*R[grasp_pre_pre_look_at_table]+T(3,3)*R[put_pre_pre_look_at_table]);
				Varm[0][look_at_table]=R[put_pre_look_at_table] + gamma*(T(3,0)*R[nav_pre_look_at_table]+T(3,1)*R[detect_pre_look_at_table]+T(3,2)*R[grasp_pre_look_at_table]+T(3,3)*R[put_pre_look_at_table]);
				Varm[0][overtray]=R[put_pre_overtray] + gamma*(T(3,0)*R[nav_pre_overtray]+T(3,1)*R[detect_pre_overtray]+T(3,2)*R[grasp_pre_overtray]+T(3,3)*R[put_pre_overtray]);
				Varm[0][overtray_top]=R[put_pre_overtray_top] + gamma*(T(3,0)*R[nav_pre_overtray_top]+T(3,1)*R[detect_pre_overtray_top]+T(3,2)*R[grasp_pre_overtray_top]+T(3,3)*R[put_pre_overtray_top]);
				Varm[0][tray]=R[put_pre_tray] + gamma*(T(3,0)*R[nav_pre_tray]+T(3,1)*R[detect_pre_tray]+T(3,2)*R[grasp_pre_tray]+T(3,3)*R[put_pre_tray]);
				Varm[0][intermediateback]=R[put_pre_intermediateback] + gamma*(T(3,0)*R[nav_pre_intermediateback]+T(3,1)*R[detect_pre_intermediateback]+T(3,2)*R[grasp_pre_intermediateback]+T(3,3)*R[put_pre_intermediateback]);
				Varm[0][intermediatebacklow]=R[put_pre_intermediatebacklow] + gamma*(T(3,0)*R[nav_pre_intermediatebacklow]+T(3,1)*R[detect_pre_intermediatebacklow]+T(3,2)*R[grasp_pre_intermediatebacklow]+T(3,3)*R[put_pre_intermediatebacklow]);
				Varm[0][intermediatefront]=R[put_pre_intermediatefront] + gamma*(T(3,0)*R[nav_pre_intermediatefront]+T(3,1)*R[detect_pre_intermediatefront]+T(3,2)*R[grasp_pre_intermediatefront]+T(3,3)*R[put_pre_intermediatefront]);
				Varm[0][intermediatefront_top]=R[put_pre_intermediatefront_top] + gamma*(T(3,0)*R[nav_pre_intermediatefront_top]+T(3,1)*R[detect_pre_intermediatefront_top]+T(3,2)*R[grasp_pre_intermediatefront_top]+T(3,3)*R[put_pre_intermediatefront_top]);
				Varm[0][wavein]=R[put_pre_wavein] + gamma*(T(3,0)*R[nav_pre_wavein]+T(3,1)*R[detect_pre_wavein]+T(3,2)*R[grasp_pre_wavein]+T(3,3)*R[put_pre_wavein]);
				Varm[0][waveout]=R[put_pre_waveout] + gamma*(T(3,0)*R[nav_pre_waveout]+T(3,1)*R[detect_pre_waveout]+T(3,2)*R[grasp_pre_waveout]+T(3,3)*R[put_pre_waveout]);
			}
			if (action_stage=="post-config")
			{
				Varm[0][home]=R[put_post_home] + gamma*(T(3,0)*R[nav_post_home]+T(3,1)*R[detect_post_home]+T(3,2)*R[grasp_post_home]+T(3,3)*R[put_post_home]);
				Varm[0][folded]=R[put_post_folded] + gamma*(T(3,0)*R[nav_post_folded]+T(3,1)*R[detect_post_folded]+T(3,2)*R[grasp_post_folded]+T(3,3)*R[put_post_folded]);
				Varm[0][pregrasp]=R[put_post_pregrasp] + gamma*(T(3,0)*R[nav_post_pregrasp]+T(3,1)*R[detect_post_pregrasp]+T(3,2)*R[grasp_post_pregrasp]+T(3,3)*R[put_post_pregrasp]);
				Varm[0][pregrasp_top]=R[put_post_pregrasp_top] + gamma*(T(3,0)*R[nav_post_pregrasp_top]+T(3,1)*R[detect_post_pregrasp_top]+T(3,2)*R[grasp_post_pregrasp_top]+T(3,3)*R[put_post_pregrasp_top]);
				Varm[0][grasp]=R[put_post_grasp] + gamma*(T(3,0)*R[nav_post_grasp]+T(3,1)*R[detect_post_grasp]+T(3,2)*R[grasp_post_grasp]+T(3,3)*R[put_post_grasp]);
				Varm[0][hold]=R[put_post_hold] + gamma*(T(3,0)*R[nav_post_hold]+T(3,1)*R[detect_post_hold]+T(3,2)*R[grasp_post_hold]+T(3,3)*R[put_post_hold]);
				Varm[0][pre_look_at_table]=R[put_post_pre_look_at_table] + gamma*(T(3,0)*R[nav_post_pre_look_at_table]+T(3,1)*R[detect_post_pre_look_at_table]+T(3,2)*R[grasp_post_pre_look_at_table]+T(3,3)*R[put_post_pre_look_at_table]);
				Varm[0][look_at_table]=R[put_post_look_at_table] + gamma*(T(3,0)*R[nav_post_look_at_table]+T(3,1)*R[detect_post_look_at_table]+T(3,2)*R[grasp_post_look_at_table]+T(3,3)*R[put_post_look_at_table]);
				Varm[0][overtray]=R[put_post_overtray] + gamma*(T(3,0)*R[nav_post_overtray]+T(3,1)*R[detect_post_overtray]+T(3,2)*R[grasp_post_overtray]+T(3,3)*R[put_post_overtray]);
				Varm[0][overtray_top]=R[put_post_overtray_top] + gamma*(T(0,0)*R[nav_post_overtray_top]+T(3,1)*R[detect_post_overtray_top]+T(3,2)*R[grasp_post_overtray_top]+T(3,3)*R[put_post_overtray_top]);
				Varm[0][tray]=R[put_post_tray] + gamma*(T(3,0)*R[nav_post_tray]+T(3,1)*R[detect_post_tray]+T(3,2)*R[grasp_post_tray]+T(3,3)*R[put_post_tray]);
				Varm[0][intermediateback]=R[put_post_intermediateback] + gamma*(T(3,0)*R[nav_post_intermediateback]+T(3,1)*R[detect_post_intermediateback]+T(3,2)*R[grasp_post_intermediateback]+T(3,3)*R[put_post_intermediateback]);
				Varm[0][intermediatebacklow]=R[put_post_intermediatebacklow] + gamma*(T(3,0)*R[nav_post_intermediatebacklow]+T(3,1)*R[detect_post_intermediatebacklow]+T(3,2)*R[grasp_post_intermediatebacklow]+T(3,3)*R[put_post_intermediatebacklow]);
				Varm[0][intermediatefront]=R[put_post_intermediatefront] + gamma*(T(3,0)*R[nav_post_intermediatefront]+T(3,1)*R[detect_post_intermediatefront]+T(3,2)*R[grasp_post_intermediatefront]+T(3,3)*R[put_post_intermediatefront]);
				Varm[0][intermediatefront_top]=R[put_post_intermediatefront_top] + gamma*(T(3,0)*R[nav_post_intermediatefront_top]+T(3,1)*R[detect_post_intermediatefront_top]+T(3,2)*R[grasp_post_intermediatefront_top]+T(3,3)*R[put_post_intermediatefront_top]);
				Varm[0][wavein]=R[put_post_wavein] + gamma*(T(3,0)*R[nav_post_wavein]+T(3,1)*R[detect_post_wavein]+T(3,2)*R[grasp_post_wavein]+T(3,3)*R[put_post_wavein]);
				Varm[0][waveout]=R[put_post_waveout] + gamma*(T(3,0)*R[nav_post_waveout]+T(3,1)*R[detect_post_waveout]+T(3,2)*R[grasp_post_waveout]+T(3,3)*R[put_post_waveout]);
			}
		}

//------------- Chose the best way with the function max -------------

/*	result_arm=0;
	for (int j=16;j>=0;j--)
	{
		if(result_arm<Varm[0][j])		//function max
		{
			result_arm=Varm[0][j];
			//result_armstate=j;			// know the state where the value function is the bes
		}								// if j=0=home, j=1=folded, j=2=pregrasp ,etc...
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
			for(int i=0;i<arm_n;i++)
			{
				for(int d=0;d<dim;d++)
				{
				bPos[d][i]= arm_randfunc(arm_xs, arm_xe);
				//std::cout << "bpos " << bPos[d][i] << std::endl;
				fit[i]=arm_func(bPos[d][i], Varm);
				//std::cout << "fit: " << fit[i] << std::endl;
				}
			}

			// at this point bPos contains a number of randomly initialised particles
			// fit, contains the value of the fitness function
			// thus forming a (fit,bPos) tuple

			//sort by fitness, preserving the (fit,bpos) tuple
			arm_funcSort(fit, sortedFit, bPos, bPosSort, arm_n); // bpossort contains all the sort position of the scout bees
			fit[bPosSort[0][0]]=arm_func(bPosSort[0][0], Varm);
			//std::cout << "bpossort: " << bPosSort[0][0] << std::endl;
			//std::cout << "fit: " << fit[bPosSort[0][0]] << std::endl;

			//arm_imax number of iteration
			for(int iter=0; iter<arm_imax ;iter++)
			{
				for(int d=0;d<dim;d++)
					nghx[d] = 1;

				int aa[50]; //50 max number of selected sites out of n

					 for(int i=0;i<arm_m;i++)
					 {
					   if(i<arm_e)
						   aa[i]=arm_n2;  // Number of bees around each elite point
					   else
						   aa[i]=arm_n1;  // Number of bees around other selected point
					   }

	// ----------------------------------------Neighbourhood search  ------------------------------------

				temp1=-INT_MAX;

				for(int k=0;k<arm_m;k++)//k site
				{
					for(int j=0;j<aa[k];j++) //j recruited bee
					{
						for(int d=0;d<dim;d++)//d dimension
						{
							candidx[d][k]=bPosSort[d][k]; //define the candidate position

							if ((candidx[d][k]-nghx[d])<arm_xs) // boundry check (left)
								{
								 bNghPos[d][j]=arm_randfunc(arm_xs,candidx[d][k]+nghx[d]);
								 bNghFit[j]=arm_func(bNghPos[d][j], Varm);
								}
							if ((candidx[d][k]+nghx[d])>arm_xe)// boundry check (right)
								{
								bNghPos[d][j]=arm_randfunc(candidx[d][k]-nghx[d],arm_xe);
								bNghFit[j]=arm_func(bNghPos[d][j], Varm);
								}
							if ((candidx[d][k]-nghx[d])>=arm_xs and (candidx[d][k]+nghx[d])<=arm_xe )
								{
								bNghPos[d][j]=arm_randfunc(candidx[d][k]-nghx[d] , candidx[d][k]+nghx[d]);
								bNghFit[j]=arm_func(bNghPos[d][j], Varm);
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

				int ranSearchBees=arm_n-arm_m; // Number of bees search randomly
				for(int k=0;k<ranSearchBees;k++)	//start of random search for rest of bees
					 {
						for(int d=0;d<dim;d++)
						{
							globalPos[d][k]=arm_randfunc(arm_xs, arm_xe);
							globalFit[k]=arm_func(globalPos[d][k], Varm);// evaluate the fitness of the new list

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

			}	//end iter = arm_imax

		} // end runs

			result_armstate=bPosSort[0][0]; //bPosSort[0][0] correspond to the elite site
			result_arm = sortedFit[0]; // sortedFit[0] correspond to the value of the elite site
			std::cout << "best arm pos: " << result_armstate << std::endl;
			std::cout << "best arm fit: " << result_arm << std::endl;

		return;
	}
