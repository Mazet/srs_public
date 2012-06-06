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

int func( int i,std::vector<std::vector<float> > Vtorso)  // Definition of Fitness Function
{
	int y;
	y=Vtorso[0][i];
	  return y;
}

int	xs = 0;
int	xe = 15;
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

void reward_torso (std::string action_name, std::string action_stage, std::vector<std::vector<float> >& Vtorso,double& result_torso ,int& result_torsostate)
{
float gamma=0.1;  // define the discount factor "gamma"
	int home=0, left=1, right=2, front=3,front_left=4, front_right=5,back=6,back_extreme=7,back_left=8,
		back_left_extreme=9, back_right=10,back_right_extreme=11,nod=12,lookontray=13,bow=14,shake=15;
	std::vector<float> R;   //create a vector R with an unknown size
		R.resize(16);  // define the size of the vector
	std::vector<float> T;   //create a vector T with an unknown size
		T.resize(16);  // define the size of the vector
	Vtorso.resize(6);
	for (int i=5;i>=0;i--)
	{
	Vtorso[i].resize(16);
	}
	//----- initialisation in order to compute the value function -----
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
				Vtorso[5][15]=R[shake];
	for (int t=4;t>=0;t--)
		{
			if (action_name=="navigation")
			{
				if (action_stage=="pre-config")
				{
					R[home]=3000;						T[home]=0.1;
					R[left]=8;						T[left]=0.2;
					R[right]=3;						T[right]=0.3;
					R[front]=4;						T[front]=0.4;
					R[front_left]=6;				T[front_left]=0.41;
					R[front_right]=2;				T[front_right]=0.43;
					R[back]=9;						T[back]=0.45;
					R[back_extreme]=5;				T[back_extreme]=0.47;
					R[back_left]=7;					T[back_left]=0.5;
					R[back_left_extreme]=1;			T[back_left_extreme]=0.52;
					R[back_right]=10;				T[back_right]=0.54;
					R[back_right_extreme]=7;		T[back_right_extreme]=0.56;
					R[nod]=5;						T[nod]=0.58;
					R[lookontray]=6;				T[lookontray]=0.6;
					R[bow]=3;						T[bow]=0.65;
					R[shake]=8;						T[shake]=0.68;
				}
				if (action_stage=="post-config")
				{
					R[home]=5;						T[home]=0.15;
					R[left]=2;						T[left]=0.21;
					R[right]=1;						T[right]=0.18;
					R[front]=3;						T[front]=0.25;
					R[front_left]=5;				T[front_left]=0.32;
					R[front_right]=800;				T[front_right]=0.38;
					R[back]=3;						T[back]=0.41;
					R[back_extreme]=4;				T[back_extreme]=0.24;
					R[back_left]=5;					T[back_left]=0.32;
					R[back_left_extreme]=2;			T[back_left_extreme]=0.17;
					R[back_right]=8;				T[back_right]=0.12;
					R[back_right_extreme]=4;		T[back_right_extreme]=0.26;
					R[nod]=10;						T[nod]=0.5;
					R[lookontray]=6;				T[lookontray]=0.37;
					R[bow]=2;						T[bow]=0.18;
					R[shake]=3;						T[shake]=0.38;
				}
			}
			if (action_name=="detection")
			{
				if (action_stage=="pre-config")
				{
					R[home]=7;						T[home]=0.2;
					R[left]=2;						T[left]=0.15;
					R[right]=5;						T[right]=0.13;
					R[front]=7;						T[front]=0.17;
					R[front_left]=9;				T[front_left]=0.24;
					R[front_right]=4;				T[front_right]=0.33;
					R[back]=6;						T[back]=0.26;
					R[back_extreme]=12;				T[back_extreme]=0.17;
					R[back_left]=1;					T[back_left]=0.25;
					R[back_left_extreme]=2;			T[back_left_extreme]=0.32;
					R[back_right]=3;				T[back_right]=0.13;
					R[back_right_extreme]=4;		T[back_right_extreme]=0.42;
					R[nod]=8;						T[nod]=0.24;
					R[lookontray]=7;				T[lookontray]=0.48;
					R[bow]=1;						T[bow]=0.10;
					R[shake]=4;						T[shake]=0.08;
				}
				if (action_stage=="post-config")
				{
					R[home]=1;						T[home]=0.24;
					R[left]=2;						T[left]=0.12;
					R[right]=3;						T[right]=0.42;
					R[front]=4;						T[front]=0.23;
					R[front_left]=5;				T[front_left]=0.18;
					R[front_right]=6;				T[front_right]=0.16;
					R[back]=7;						T[back]=0.14;
					R[back_extreme]=8;				T[back_extreme]=0.23;
					R[back_left]=9;					T[back_left]=0.12;
					R[back_left_extreme]=10;		T[back_left_extreme]=0.17;
					R[back_right]=11;				T[back_right]=0.2;
					R[back_right_extreme]=12;		T[back_right_extreme]=0.34;
					R[nod]=13;						T[nod]=0.38;
					R[lookontray]=14;				T[lookontray]=0.1;
					R[bow]=15;						T[bow]=0.5;
					R[shake]=16;					T[shake]=0.3;
				}
			}
			if (action_name=="grasp")
			{
				if (action_stage=="pre-config")
				{
					R[home]=10;						T[home]=0.13;
					R[left]=9;						T[left]=0.17;
					R[right]=8;						T[right]=0.2;
					R[front]=7;						T[front]=0.22;
					R[front_left]=5;				T[front_left]=0.25;
					R[front_right]=6;				T[front_right]=0.28;
					R[back]=4;						T[back]=0.31;
					R[back_extreme]=3;				T[back_extreme]=0.14;
					R[back_left]=1;					T[back_left]=0.35;
					R[back_left_extreme]=2;			T[back_left_extreme]=0.04;
					R[back_right]=6;				T[back_right]=0.08;
					R[back_right_extreme]=5;		T[back_right_extreme]=0.06;
					R[nod]=4;						T[nod]=0.12;
					R[lookontray]=3;				T[lookontray]=0.17;
					R[bow]=2;						T[bow]=0.28;
					R[shake]=1;						T[shake]=0.37;
				}
				if (action_stage=="post-config")
				{
					R[home]=6;						T[home]=0.28;
					R[left]=4;						T[left]=0.24;
					R[right]=2;						T[right]=0.2;
					R[front]=1;						T[front]=0.04;
					R[front_left]=3;				T[front_left]=0.12;
					R[front_right]=7;				T[front_right]=0.18;
					R[back]=6;						T[back]=0.3;
					R[back_extreme]=3;				T[back_extreme]=0.15;
					R[back_left]=4;					T[back_left]=0.1;
					R[back_left_extreme]=2;			T[back_left_extreme]=0.2;
					R[back_right]=3;				T[back_right]=023;
					R[back_right_extreme]=1;		T[back_right_extreme]=0.41;
					R[nod]=8;						T[nod]=0.36;
					R[lookontray]=2;				T[lookontray]=0.29;
					R[bow]=1;						T[bow]=0.31;
					R[shake]=10;					T[shake]=0.19;
				}
			}
			if (action_name=="put_on_tray")
			{
				if (action_stage=="pre-config")
				{
					R[home]=1;						T[home]=0.31;
					R[left]=2;						T[left]=0.35;
					R[right]=4;						T[right]=0.24;
					R[front]=6;						T[front]=0.27;
					R[front_left]=8;				T[front_left]=0.3;
					R[front_right]=10;				T[front_right]=0.12;
					R[back]=8;						T[back]=0.15;
					R[back_extreme]=6;				T[back_extreme]=0.17;
					R[back_left]=4;					T[back_left]=0.19;
					R[back_left_extreme]=2;			T[back_left_extreme]=0.24;
					R[back_right]=1;				T[back_right]=0.31;
					R[back_right_extreme]=5;		T[back_right_extreme]=0.36;
					R[nod]=4;						T[nod]=0.38;
					R[lookontray]=3;				T[lookontray]=0.4;
					R[bow]=2;						T[bow]=0.42;
					R[shake]=1;						T[shake]=0.48;
				}
				if (action_stage=="post-config")
				{
					R[home]=12;						T[home]=0.12;
					R[left]=10;						T[left]=0.21;
					R[right]=8;						T[right]=0.32;
					R[front]=6;						T[front]=0.44;
					R[front_left]=4;				T[front_left]=0.11;
					R[front_right]=2;				T[front_right]=0.15;
					R[back]=1;						T[back]=0.24;
					R[back_extreme]=3;				T[back_extreme]=0.28;
					R[back_left]=6;					T[back_left]=0.33;
					R[back_left_extreme]=9;			T[back_left_extreme]=0.35;
					R[back_right]=1;				T[back_right]=0.37;
					R[back_right_extreme]=6;		T[back_right_extreme]=0.39;
					R[nod]=8;						T[nod]=0.42;
					R[lookontray]=4;				T[lookontray]=0.13;
					R[bow]=5;						T[bow]=0.07;
					R[shake]=2;						T[shake]=0.02;
				}
			}
	//-----  computing of the value function -----
			Vtorso[t][home]=R[home] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][left]=R[left] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][right]=R[right] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][front]=R[front] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][front_left]=R[front_left] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][front_right]=R[front_right] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][back]=R[back] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][back_extreme]=R[back_extreme] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][back_left]=R[back_left] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][back_left_extreme]=R[back_left_extreme] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][back_right]=R[back_right] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][back_right_extreme]=R[back_right_extreme] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][nod]=R[nod] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][lookontray]=R[lookontray] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][bow]=R[bow] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
			Vtorso[t][shake]=R[shake] + gamma*(T[home]*Vtorso[t+1][home]+T[left]*Vtorso[t+1][left]+T[right]*Vtorso[t+1][right]+T[front]*Vtorso[t+1][front]+T[front_left]*Vtorso[t+1][front_left]+T[front_right]*Vtorso[t+1][front_right]+T[back]*Vtorso[t+1][back]+T[back_extreme]*Vtorso[t+1][back_extreme]+T[back_left]*Vtorso[t+1][back_left]+T[back_left_extreme]*Vtorso[t+1][back_left_extreme]+T[back_right]*Vtorso[t+1][back_right]+T[back_right_extreme]*Vtorso[t+1][back_right_extreme]+T[nod]*Vtorso[t+1][nod]+T[lookontray]*Vtorso[t+1][lookontray]+T[bow]*Vtorso[t+1][bow]+T[shake]*Vtorso[t+1][shake]);
		}
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
					fit[i]=func(bPos[d][i],Vtorso);

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
							  bNghFit[j]=func(j,Vtorso);

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
						  fit[j]=func(j,Vtorso);

				}	//end iter = imax
				result_torsostate=bPosSort[0][0];
				std::cout << "sort: " << result_torsostate << std::endl;
		} // end runs

			cout<<"\n n= "<<n;

			cout<<"      Time/s of Failed are ="<<fail;

			cout<<"\n finished..................\n";
			//std::cout << "bestVtorso: " << result_torso << std::endl;


		return;
		}
