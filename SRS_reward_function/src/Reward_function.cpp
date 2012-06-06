/*
 * Reward_function.cpp
 *
 *  Created on: 16 Apr 2012
 *      Author: srs
 */

#include "Reward_function.h"
Reward_function::Reward_function() {
	// TODO Auto-generated constructor stub

}

Reward_function::~Reward_function() {
	// TODO Auto-generated destructor stub
}

void reward_arm (std::string action_name, std::string action_stage, std::vector<std::vector<float> >& Varm, double& result_arm ,int& result_armstate)

{
	float gamma=0.1;  // define the discount factor "gamma"
	int home=0, folded=1, pregrasp=2, pregrasp_top=3, grasp=4, hold=5,pre_look_at_table=6, look_at_table=7,
	overtray=8, overtray_top=9, tray=10,intermediateback=11, intermediatebacklow=12, intermediatefront=13,
	intermediatefront_top=14,wavein=15, waveout=16;
	//std::cout << "begin reward function" << std::endl;
	std::vector<float> R;   //create a vector R with an unknown size
		R.resize(17);  // define the size of the vector
	std::vector<float> T;   //create a vector R with an unknown size
		T.resize(17);  // define the size of the vector
	Varm.resize(6);
	for (int i=5;i>=0;i--)
		{
		Varm[i].resize(17);
		}

	for (int t=4;t>=0;t--)
	{
		if (action_name=="navigation")
		{
			if (action_stage=="pre-config")
			{
				R[home]=1000;					T[home]=0.05;
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

				}
			if (action_stage=="post-config")
			{
				R[home]=1;						T[home]=0.1;
				R[folded]=2;					T[folded]=0.13;
				R[pregrasp]=3;					T[pregrasp]=0.23;
				R[pregrasp_top]=4;				T[pregrasp_top]=0.18;
				R[grasp]=5;						T[grasp]=0.27;
				R[hold]=6;						T[hold]=0.33;
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
//------------- Chose the best way with the result of value function -------------
	result_arm=0;
	for (int j=16;j>=0;j--)
	{
		if(result_arm<Varm[0][j])		//function max
		{
			result_arm=Varm[0][j];
			result_armstate=j;			// know the state where the value function is the bes
		}								// if j=0=home, j=1=folded, j=2=pregrasp ,etc...
	}
//------------- Define the result of value function -------------
std::cout << "bestVarm: " << result_arm << std::endl;

return;
}

void reward_head (std::string action_name, std::string action_stage, std::vector<std::vector<float> >& Vhead,double& result_head ,int& result_headstate)
{
float gamma=0.1;  // define the discount factor "gamma"
	int front=0, back=1;
	std::vector<float> R;   //create a vector R with an unknown size
		R.resize(2);  // define the size of the vector
	std::vector<float> T;   //create a vector T with an unknown size
			T.resize(2);  // define the size of the vector
	Vhead.resize(6);
	for (int i=5;i>=0;i--)
	{
	Vhead[i].resize(2);
	}
	for (int t=4;t>=0;t--)
	{
			if (action_name=="navigation")
			{
				if (action_stage=="pre-config")
				{
					R[front]=10;		T[front]=0.38;
					R[back]=5;			T[back]=0.62;
	//----- initialisation in order to compute the value function -----
					Vhead[5][0]=R[front];
					Vhead[5][1]=R[back];
				}
				if (action_stage=="post-config")
				{
					R[front]=2;		T[front]=0.45;
					R[back]=8;		T[back]=0.55;
	//----- initialisation in order to compute the value function -----
					Vhead[5][0]=R[front];
					Vhead[5][1]=R[back];
				}
			}

			if (action_name=="detection")
			{
				if (action_stage=="pre-config")
				{
					R[front]=8;		T[front]=0.58;
					R[back]=2;		T[back]=0.42;
	//----- initialisation in order to compute the value function -----
					Vhead[5][0]=R[front];
					Vhead[5][1]=R[back];
				}
				if (action_stage=="post-config")
				{
					R[front]=5;		T[front]=0.63;
					R[back]=4;		T[back]=0.37;

	//----- initialisation in order to compute the value function -----
					Vhead[5][0]=R[front];
					Vhead[5][1]=R[back];
				}
			}
			if (action_name=="grasp")
			{
				if (action_stage=="pre-config")
				{
					R[front]=7;		T[front]=0.72;
					R[back]=4;		T[back]=0.28;
	//----- initialisation in order to compute the value function -----
					Vhead[5][0]=R[front];
					Vhead[5][1]=R[back];
				}
				if (action_stage=="post-config")
				{
					R[front]=8;		T[front]=0.21;
					R[back]=6;		T[back]=0.79;

	//----- initialisation in order to compute the value function -----
					Vhead[5][0]=R[front];
					Vhead[5][1]=R[back];
				}
			}
			if (action_name=="put_on_tray")
			{
				if (action_stage=="pre-config")
				{
					R[front]=4;		T[front]=0.35;
					R[back]=3;		T[back]=0.65;
	//----- initialisation in order to compute the value function -----
					Vhead[5][0]=R[front];
					Vhead[5][1]=R[back];
				}
				if (action_stage=="post-config")
				{
					R[front]=9;		T[front]=0.48;
					R[back]=1;		T[back]=0.52;
	//----- initialisation in order to compute the value function -----
					Vhead[5][0]=R[front];
					Vhead[5][1]=R[back];
				}
			}
	//-----  computing of the value function -----
			Vhead[t][front]=R[front] + gamma*(T[front]*Vhead[t+1][front]+T[back]*Vhead[t+1][back]);
			Vhead[t][back]=R[back] + gamma*(T[front]*Vhead[t+1][front]+T[back]*Vhead[t+1][back]);
		}
//------------- Chose the best way with the result of value function -------------
	result_head=0;
	for (int j=1;j>=0;j--)
	{
		if(result_head<Vhead[0][j])		//function max
		{
			result_head=Vhead[0][j];
			result_headstate=j;			// know the state where the value function is the best
		}								// if j=0=front, j=1=back
	}
	std::cout << "bestVhead: " << result_head << std::endl;

return;
}

void reward_tray (std::string action_name, std::string action_stage, std::vector<std::vector<float> >& Vtray,double& result_tray ,int& result_traystate)
{
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
	for (int t=4;t>=0;t--)
		{
			if (action_name=="navigation")
			{
				if (action_stage=="pre-config")
				{
					R[up]=10;		T[up]=0.81;
					R[down]=5;		T[down]=0.19;
	//----- initialisation in order to compute the value function -----
					Vtray[5][0]=R[up];
					Vtray[5][1]=R[down];
				}
				if (action_stage=="post-config")
				{
					R[up]=1;		T[up]=0.63;
					R[down]=3;		T[down]=0.37;
	//----- initialisation in order to compute the value function -----
					Vtray[5][0]=R[up];
					Vtray[5][1]=R[down];
				}
			}
			if (action_name=="detection")
			{
				if (action_stage=="pre-config")
				{
					R[up]=8;		T[up]=0.7;
					R[down]=3;		T[down]=0.3;
	//----- initialisation in order to compute the value function -----
					Vtray[5][0]=R[up];
					Vtray[5][1]=R[down];
				}
				if (action_stage=="post-config")
				{
					R[up]=2;		T[up]=0.55;
					R[down]=4;		T[down]=0.45;
	//----- initialisation in order to compute the value function -----
					Vtray[5][0]=R[up];
					Vtray[5][1]=R[down];
				}
			}
			if (action_name=="grasp")
			{
				if (action_stage=="pre-config")
				{
					R[up]=7;		T[up]=0.66;
					R[down]=4;		T[down]=0.34;
	//----- initialisation in order to compute the value function -----
					Vtray[5][0]=R[up];
					Vtray[5][1]=R[down];
				}
				if (action_stage=="post-config")
				{
					R[up]=4;		T[up]=0.74;
					R[down]=6;		T[down]=0.26;
	//----- initialisation in order to compute the value function -----
					Vtray[5][0]=R[up];
					Vtray[5][1]=R[down];
				}
			}
			if (action_name=="put_on_tray")
			{
				if (action_stage=="pre-config")
				{
					R[up]=100;		T[up]=0.83;
					R[down]=6;		T[down]=0.17;
	//----- initialisation in order to compute the value function -----
					Vtray[5][0]=R[up];
					Vtray[5][1]=R[down];
				}
				if (action_stage=="post-config")
				{
					R[up]=50;		T[up]=0.28;
					R[down]=5;		T[down]=0.72;
	//----- initialisation in order to compute the value function -----
					Vtray[5][0]=R[up];
					Vtray[5][1]=R[down];
				}
			}
	//-----  computing of the value function -----
			Vtray[t][up]=R[up] + gamma*(T[up]*Vtray[t+1][up]+T[down]*Vtray[t+1][down]);
			Vtray[t][down]=R[down] + gamma*(T[up]*Vtray[t+1][up]+T[down]*Vtray[t+1][down]);
		}
	//------------- Chose the best way with the result of value function -------------
result_tray=0;
for (int j=1;j>=0;j--)
{
	if(result_tray<Vtray[0][j])		//function max
	{
		result_tray=Vtray[0][j];
		result_traystate=j;			// know the state where the value function is the best
	}								// if j=0=front, j=1=back
}
	std::cout << "bestVtray: " << result_tray << std::endl;

return;
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
	for (int t=4;t>=0;t--)
	{
		if (action_name=="navigation")
		{
			if (action_stage=="pre-config")
			{
				R[home]=7;				T[home]=0.5;
				R[cylclosed]=4;			T[cylclosed]=0.08;
				R[cylopen]=1;			T[cylopen]=0.02;
				R[cyltotalopen]=2;		T[cyltotalopen]=0.05;
				R[spheropen]=7;			T[spheropen]=0.1;
				R[spherclosed]=3;		T[spherclosed]=0.15;
				R[paropen]=5;			T[paropen]=0.12;
				R[parclosed]=6;			T[parclosed]=0.21;
				R[point]=8;				T[point]=0.06;
				R[fist]=9;				T[fist]=0.14;
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
			}
			if (action_stage=="post-config")
			{
				R[home]=5;				T[home]=0.4;
				R[cylclosed]=3;			T[cylclosed]=0.18;
				R[cylopen]=2;			T[cylopen]=0.12;
				R[cyltotalopen]=4;		T[cyltotalopen]=0.15;
				R[spheropen]=8;			T[spheropen]=0.11;
				R[spherclosed]=4;		T[spherclosed]=0.14;
				R[paropen]=2;			T[paropen]=0.17;
				R[parclosed]=9;			T[parclosed]=0.31;
				R[point]=4;				T[point]=0.16;
				R[fist]=6;				T[fist]=0.24;
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
//------------- Chose the best way with the result of value function -------------
result_sdh=0;
for (int j=9;j>=0;j--)
{
	if(result_sdh<Vsdh[0][j])		//function max
	{
		result_sdh=Vsdh[0][j];
		result_sdhstate=j;			// know the state where the value function is the best
	}								// if j=0=home, j=1=cylclosed, j=2=cylopen ,etc...
}
	std::cout << "bestVsdh: " << result_sdh << std::endl;

return;

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
	for (int t=4;t>=0;t--)
		{
			if (action_name=="navigation")
			{
				if (action_stage=="pre-config")
				{
					R[home]=5;						T[home]=0.1;
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
						}
				if (action_stage=="post-config")
				{
					R[home]=4;						T[home]=0.15;
					R[left]=2;						T[left]=0.21;
					R[right]=1;						T[right]=0.18;
					R[front]=3;						T[front]=0.25;
					R[front_left]=5;				T[front_left]=0.32;
					R[front_right]=8;				T[front_right]=0.38;
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
//------------- Chose the best way with the result of value function -------------
	result_torso=0;
	for (int j=15;j>=0;j--)
	{
		if(result_torso<Vtorso[0][j])		//function max
		{
			result_torso=Vtorso[0][j];
			result_torsostate=j;			// know the state where the value function is the best
		}								// if j=0=home, j=1=cylclosed, j=2=cylopen ,etc...
	}
	std::cout << "bestVtorso: " << result_torso << std::endl;

return;
}
