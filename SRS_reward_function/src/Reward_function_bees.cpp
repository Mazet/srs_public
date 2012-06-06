/*
 * Reward_function_bees.cpp
 *
 *  Created on: 16 Apr 2012
 *      Author: srs
 */

#include "Reward_function_bees.h"
#include <stdlib.h>
#include <ctime>


Reward_function_bees::Reward_function_bees() {
	// TODO Auto-generated constructor stub

}

Reward_function_bees::~Reward_function_bees() {
	// TODO Auto-generated destructor stub
}


void reward_tray() //(std::string action_name, std::string action_stage, std::vector<std::vector<float> >& Vtray,double& result_tray ,int& result_traystate)
{
	std::vector<std::vector<float> > Vtray;
	double result_tray;
	int result_traystate;
	float gamma=0.1;  // define the discount factor "gamma"
	int up=0, down=1;
	std::vector<float> R;   //create a vector R with an unknown size
	R.resize(2);  // define the size of the vector
	std::vector<float> T;   //create a vector T with an unknown size
	T.resize(2);  // define the size of the vector
	Vtray.resize(6);
	for (int i=5;i>=0;i--)
	{
	Vtray[i].resize(2);
	}
	int action_name=0;
	int action_stage = 0;
	srand(time(0));
	int x=rand()%2 ;
	std::cout << "x " << x << std::endl;
	for (int t=4;t>=0;t--)
		{
			if (action_name==0)
			{
				if (action_stage==0)
				{
					R[up]=10;		T[up]=0.8;
					R[down]=5;		T[down]=0.3;
	//----- initialisation in order to compute the value function -----
					Vtray[5][0]=R[up];
					Vtray[5][1]=R[down];
	//-----  computing of the value function -----
					Vtray[t][x]=R[x] + gamma*(T[up]*Vtray[t+1][up]+T[down]*Vtray[t+1][down]);
//------------- Chose the best way with the result of value function -------------
					std::cout << "random Vtray" << Vtray[t][x] << std::endl;
					result_tray=0;
					for (int j=1;j>=0;j--)
					{
						if(result_tray<Vtray[0][j])		//function max
						{
							result_tray=Vtray[0][j];
							result_traystate=j;			// know the state where the value function is the best
						}								// if j=0=up, j=1=down
					}
				}
			}
		}

	std::cout << "bestVtray: " << result_tray << std::endl;

return;
}

int main(void)
{
	reward_tray ();
}

