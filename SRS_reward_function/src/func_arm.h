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

int func( int i,std::vector<std::vector<float> > Varm)  // Definition of Fitness Function
{
	int y;
	y=Varm[0][i];
	  return y;
}

int	xs = 0;
int	xe = 16;
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

void reward_arm (std::string action_name, std::string action_stage, std::vector<std::vector<float> >& Varm, double& result_arm ,int& result_armstate)

{
	float gamma=0.1;  // define the discount factor "gamma"
	int home=0, folded=1, pregrasp=2, pregrasp_top=3, grasp=4, hold=5,pre_look_at_table=6, look_at_table=7,
	overtray=8, overtray_top=9, tray=10,intermediateback=11, intermediatebacklow=12, intermediatefront=13,
	intermediatefront_top=14,wavein=15, waveout=16;
	std::vector<float> R;   //create a vector R with an unknown size
		R.resize(17);  // define the size of the vector
	std::vector<float> T;   //create a vector R with an unknown size
		T.resize(17);  // define the size of the vector
	Varm.resize(6);
	for (int i=5;i>=0;i--)
		{
		Varm[i].resize(17);
		}
	//----- initialisation in order to compute the value function -----
				Varm[5][0]=R[home];
				Varm[5][1]=R[folded];
				Varm[5][2]=R[pregrasp];
				Varm[5][3]=R[pregrasp_top];
				Varm[5][4]=R[grasp];
				Varm[5][5]=R[hold];
				Varm[5][6]=R[pre_look_at_table];
				Varm[5][7]=R[look_at_table];
				Varm[5][8]=R[overtray];
				Varm[5][9]=R[overtray_top];
				Varm[5][10]=R[tray];
				Varm[5][11]=R[intermediateback];
				Varm[5][12]=R[intermediatebacklow];
				Varm[5][13]=R[intermediatefront];
				Varm[5][14]=R[intermediatefront_top];
				Varm[5][15]=R[wavein];
				Varm[5][16]=R[waveout];
	for (int t=4;t>=0;t--)
	{
		if (action_name=="navigation")
		{
			if (action_stage=="pre-config")
			{
				R[home]=3000;					T[home]=0.05;
				R[folded]=5;					T[folded]=0.1;
				R[pregrasp]=3;					T[pregrasp]=0.15;
				R[pregrasp_top]=2;				T[pregrasp_top]=0.2;
				R[grasp]=4;						T[grasp]=0.25;
				R[hold]=1;						T[hold]=0.3;
				R[pre_look_at_table]=6;			T[pre_look_at_table]=0.35;
				R[look_at_table]=7;				T[look_at_table]=0.4;
				R[overtray]=8;					T[overtray]=0.45;
				R[overtray_top]=9;				T[overtray_top]=0.5;
				R[tray]=11;						T[tray]=0.55;
				R[intermediateback]=12;			T[intermediateback]=0.6;
				R[intermediatebacklow]=13;		T[intermediatebacklow]=0.65;
				R[intermediatefront]=14;		T[intermediatefront]=0.7;
				R[intermediatefront_top]=15;	T[intermediatefront_top]=0.75;
				R[wavein]=16;					T[wavein]=0.8;
				R[waveout]=17;					T[waveout]=0.85;
			}
			if (action_stage=="post-config")
			{
				R[home]=5;						T[home]=0.1;
				R[folded]=2;					T[folded]=0.13;
				R[pregrasp]=3;					T[pregrasp]=0.23;
				R[pregrasp_top]=4;				T[pregrasp_top]=0.18;
				R[grasp]=5;						T[grasp]=0.27;
				R[hold]=600;						T[hold]=0.33;
				R[pre_look_at_table]=7;			T[pre_look_at_table]=0.4;
				R[look_at_table]=8;				T[look_at_table]=0.25;
				R[overtray]=9;					T[overtray]=0.01;
				R[overtray_top]=10;				T[overtray_top]=0.04;
				R[tray]=9;						T[tray]=0.08;
				R[intermediateback]=8;			T[intermediateback]=0.42;
				R[intermediatebacklow]=7;		T[intermediatebacklow]=0.28;
				R[intermediatefront]=6;			T[intermediatefront]=0.19;
				R[intermediatefront_top]=5;		T[intermediatefront_top]=0.22;
				R[wavein]=4;					T[wavein]=0.35;
				R[waveout]=3;					T[waveout]=0.38;
			}
		}
		if (action_name=="detection")
		{
			if (action_stage=="pre-config")
			{
				R[home]=4;						T[home]=0.12;
				R[folded]=8;					T[folded]=0.14;
				R[pregrasp]=7;					T[pregrasp]=0.16;
				R[pregrasp_top]=1;				T[pregrasp_top]=0.18;
				R[grasp]=2;						T[grasp]=0.2;
				R[hold]=8;						T[hold]=0.22;
				R[pre_look_at_table]=4;			T[pre_look_at_table]=0.25;
				R[look_at_table]=5;				T[look_at_table]=0.28;
				R[overtray]=1;					T[overtray]=0.32;
				R[overtray_top]=2;				T[overtray_top]=0.36;
				R[tray]=8;						T[tray]=0.4;
				R[intermediateback]=7;			T[intermediateback]=0.42;
				R[intermediatebacklow]=1;		T[intermediatebacklow]=0.44;
				R[intermediatefront]=4;			T[intermediatefront]=0.5;
				R[intermediatefront_top]=5;		T[intermediatefront_top]=0.05;
				R[wavein]=6;					T[wavein]=0.1;
				R[waveout]=7;					T[waveout]=0.19;
			}
			if (action_stage=="post-config")
			{
				R[home]=12;						T[home]=0.01;
				R[folded]=6;					T[folded]=0.05;
				R[pregrasp]=4;					T[pregrasp]=0.09;
				R[pregrasp_top]=2;				T[pregrasp_top]=0.1;
				R[grasp]=1;						T[grasp]=0.13;
				R[hold]=3;						T[hold]=0.17;
				R[pre_look_at_table]=9;			T[pre_look_at_table]=0.15;
				R[look_at_table]=14;			T[look_at_table]=0.2;
				R[overtray]=7;					T[overtray]=0.21;
				R[overtray_top]=5;				T[overtray_top]=0.24;
				R[tray]=3;						T[tray]=0.27;
				R[intermediateback]=1;			T[intermediateback]=0.3;
				R[intermediatebacklow]=4;		T[intermediatebacklow]=0.33;
				R[intermediatefront]=5;			T[intermediatefront]=0.35;
				R[intermediatefront_top]=8;		T[intermediatefront_top]=0.38;
				R[wavein]=9;					T[wavein]=0.42;
				R[waveout]=11;					T[waveout]=0.5;
			}
		}
		if (action_name=="grasp")
		{
			if (action_stage=="pre-config")
			{
				R[home]=7;						T[home]=0.5;
				R[folded]=2;					T[folded]=0.12;
				R[pregrasp]=9;					T[pregrasp]=0.28;
				R[pregrasp_top]=3;				T[pregrasp_top]=0.21;
				R[grasp]=1;						T[grasp]=0.3;
				R[hold]=5;						T[hold]=0.14;
				R[pre_look_at_table]=7;			T[pre_look_at_table]=0.17;
				R[look_at_table]=9;				T[look_at_table]=0.15;
				R[overtray]=2;					T[overtray]=0.27;
				R[overtray_top]=4;				T[overtray_top]=0.19;
				R[tray]=5;						T[tray]=0.24;
				R[intermediateback]=8;			T[intermediateback]=0.13;
				R[intermediatebacklow]=7;		T[intermediatebacklow]=0.36;
				R[intermediatefront]=4;			T[intermediatefront]=0.45;
				R[intermediatefront_top]=5;		T[intermediatefront_top]=0.55;
				R[wavein]=4;					T[wavein]=0.6;
				R[waveout]=7;					T[waveout]=0.2;
			}
			if (action_stage=="post-config")
			{
				R[home]=4;						T[home]=0.32;
				R[folded]=6;					T[folded]=0.27;
				R[pregrasp]=4;					T[pregrasp]=0.24;
				R[pregrasp_top]=1;				T[pregrasp_top]=0.19;
				R[grasp]=2;						T[grasp]=0.17;
				R[hold]=3;						T[hold]=0.22;
				R[pre_look_at_table]=7;			T[pre_look_at_table]=0.3;
				R[look_at_table]=8;				T[look_at_table]=0.21;
				R[overtray]=9;					T[overtray]=0.12;
				R[overtray_top]=10;				T[overtray_top]=0.1;
				R[tray]=7;						T[tray]=0.03;
				R[intermediateback]=8;			T[intermediateback]=0.07;
				R[intermediatebacklow]=6;		T[intermediatebacklow]=0.09;
				R[intermediatefront]=5;			T[intermediatefront]=0.29;
				R[intermediatefront_top]=4;		T[intermediatefront_top]=0.35;
				R[wavein]=3;					T[wavein]=0.38;
				R[waveout]=2;					T[waveout]=0.42;
			}
		}
		if (action_name=="put_on_tray")
		{
			if (action_stage=="pre-config")
			{
				R[home]=4;						T[home]=0.4;
				R[folded]=3;					T[folded]=0.13;
				R[pregrasp]=8;					T[pregrasp]=0.2;
				R[pregrasp_top]=9;				T[pregrasp_top]=0.34;
				R[grasp]=1;						T[grasp]=0.38;
				R[hold]=2;						T[hold]=0.42;
				R[pre_look_at_table]=5;			T[pre_look_at_table]=0.45;
				R[look_at_table]=4;				T[look_at_table]=0.48;
				R[overtray]=3;					T[overtray]=0.49;
				R[overtray_top]=2;				T[overtray_top]=0.01;
				R[tray]=1;						T[tray]=0.12;
				R[intermediateback]=7;			T[intermediateback]=0.17;
				R[intermediatebacklow]=9;		T[intermediatebacklow]=0.33;
				R[intermediatefront]=11;		T[intermediatefront]=0.36;
				R[intermediatefront_top]=6;		T[intermediatefront_top]=0.09;
				R[wavein]=9;					T[wavein]=0.19;
				R[waveout]=3;					T[waveout]=0.1;
			}
			if (action_stage=="post-config")
			{
				R[home]=1;						T[home]=0.19;
				R[folded]=8;					T[folded]=0.15;
				R[pregrasp]=7;					T[pregrasp]=0.2;
				R[pregrasp_top]=4;				T[pregrasp_top]=0.24;
				R[grasp]=6;						T[grasp]=0.28;
				R[hold]=3;						T[hold]=0.23;
				R[pre_look_at_table]=2;			T[pre_look_at_table]=0.04;
				R[look_at_table]=1;				T[look_at_table]=0.09;
				R[overtray]=9;					T[overtray]=0.07;
				R[overtray_top]=4;				T[overtray_top]=0.17;
				R[tray]=5;						T[tray]=0.3;
				R[intermediateback]=2;			T[intermediateback]=0.5;
				R[intermediatebacklow]=7;		T[intermediatebacklow]=0.08;
				R[intermediatefront]=8;			T[intermediatefront]=0.12;
				R[intermediatefront_top]=3;		T[intermediatefront_top]=0.19;
				R[wavein]=5;					T[wavein]=0.42;
				R[waveout]=9;					T[waveout]=0.37;
			}
		}
	//-----  computing of the value function -----
		Varm[t][home]=R[home] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][folded]=R[folded] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][pregrasp]=R[pregrasp] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);				Varm[t][folded]=R[folded] + gamma*(0.3*Varm[t+1][0]+0.15*Varm[t+1][1]+0.12*Varm[t+1][2]+0.13*Varm[t+1][3]+0.13*Varm[t+1][4]+0.13*Varm[t+1][5]+0.13*Varm[t+1][6]+0.13*Varm[t+1][7]+0.13*Varm[t+1][8]+0.13*Varm[t+1][9]+0.13*Varm[t+1][10]+0.13*Varm[t+1][11]+0.13*Varm[t+1][12]+0.13*Varm[t+1][12]+0.13*Varm[t+1][13]+0.13*Varm[t+1][14]+0.13*Varm[t+1][15]+0.13*Varm[t+1][16]);
		Varm[t][pregrasp_top]=R[pregrasp_top] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][grasp]=R[grasp] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][hold]=R[hold] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][pre_look_at_table]=R[pre_look_at_table] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][look_at_table]=R[look_at_table] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][overtray]=R[overtray] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][overtray_top]=R[overtray_top] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][tray]=R[tray] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][intermediateback]=R[intermediateback] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][intermediatebacklow]=R[intermediatebacklow] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][intermediatefront]=R[intermediatefront] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][intermediatefront_top]=R[intermediatefront_top] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][wavein]=R[wavein] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
		Varm[t][waveout]=R[waveout] + gamma*(T[home]*Varm[t+1][home]+T[folded]*Varm[t+1][folded]+T[pregrasp]*Varm[t+1][pregrasp]+T[pregrasp_top]*Varm[t+1][pregrasp_top]+T[grasp]*Varm[t+1][grasp]+T[hold]*Varm[t+1][hold]+T[pre_look_at_table]*Varm[t+1][pre_look_at_table]+T[look_at_table]*Varm[t+1][look_at_table]+T[overtray]*Varm[t+1][overtray]+T[overtray_top]*Varm[t+1][overtray_top]+T[tray]*Varm[t+1][tray]+T[intermediateback]*Varm[t+1][intermediateback]+T[intermediatebacklow]*Varm[t+1][intermediatebacklow]+T[intermediatefront]*Varm[t+1][intermediatefront]+T[intermediatefront_top]*Varm[t+1][intermediatefront_top]+T[wavein]*Varm[t+1][wavein]+T[waveout]*Varm[t+1][waveout]);
	}
//------------- Chose the best way with the function max -------------
	/*result_arm=0;
	for (int j=16;j>=0;j--)
	{
		if(result_arm<Varm[0][j])		//function max
		{
			result_arm=Varm[0][j];
			//result_armstate=j;			// know the state where the value function is the bes
		}								// if j=0=home, j=1=folded, j=2=pregrasp ,etc...
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
				fit[i]=func(bPos[d][i],Varm);

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

				result_arm=0;
					for (int j=16;j>=0;j--)
					{
						if(result_arm<Varm[0][j])		//function max
						{
							result_arm=Varm[0][j];
							//result_armstate=j;			// know the state where the value function is the bes
						}								// if j=0=home, j=1=folded, j=2=pregrasp ,etc...
					}	 for(i=0;i<m;i++)
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
						  bNghFit[j]=func(j,Varm);

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
					  fit[j]=func(j,Varm);

			}	//end iter = imax
			result_armstate=bPosSort[0][0];
			std::cout << "sort: " << result_armstate << std::endl;
	} // end runs

		cout<<"\n n= "<<n;

		cout<<"      Time/s of Failed are ="<<fail;

		cout<<"\n finished..................\n";
		//std::cout << "bestVarm: " << result_arm << std::endl;


	return;
	}
