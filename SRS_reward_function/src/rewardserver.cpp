#include "ros/ros.h"
#include "SRS_reward_function/rewardsrv.h"
#include "func_arm.cpp"
#include "func_head.cpp"
#include "func_tray.cpp"
#include "func_sdh.cpp"
#include "func_torso.cpp"
#include "func_probability.cpp"


bool reward(SRS_reward_function::rewardsrv::Request  &req,SRS_reward_function::rewardsrv::Response  &res)
{
//--------------------------probability initialisation---------------------

	Eigen::Matrix4f T;
	T(0,0)=req.x0y0;	T(0,1)=req.x0y1;	T(0,2)=req.x0y2;	T(0,3)=req.x0y3;
	T(1,0)=req.x1y0;	T(1,1)=req.x1y1;	T(1,2)=req.x1y2;	T(1,3)=req.x1y3;
	T(2,0)=req.x2y0;	T(2,1)=req.x2y1;	T(2,2)=req.x2y2;	T(2,3)=req.x2y3;
	T(3,0)=req.x3y0;	T(3,1)=req.x3y1;	T(3,2)=req.x3y2;	T(3,3)=req.x3y3;
	probability(req.action_name, req.result_action, T);

//------------------------probability result---------------------

	res.X0Y0=T(0,0);	res.X0Y1=T(0,1);	res.X0Y2=T(0,2);	res.X0Y3=T(0,3);
	res.X1Y0=T(1,0);	res.X1Y1=T(1,1);	res.X1Y2=T(1,2);	res.X1Y3=T(1,3);
	res.X2Y0=T(2,0);	res.X2Y1=T(2,1);	res.X2Y2=T(2,2);	res.X2Y3=T(2,3);
	res.X3Y0=T(3,0);	res.X3Y1=T(3,1);	res.X3Y2=T(3,2);	res.X3Y3=T(3,3);

//-----------------------------sdh result-------------------------

		std::vector<std::vector<float> > Vsdh;
		double result_sdh;
		int result_sdhstate;

		reward_sdh (req.action_name, req.action_stage, req.result_action, Vsdh,result_sdh,result_sdhstate,T);
		switch (result_sdhstate)
		{
		case 0: res.sdhstate="home";break;
		case 1: res.sdhstate="cylclosed";break;
		case 2: res.sdhstate="cylopen";break;
		case 3: res.sdhstate="cyltotalopen";break;
		case 4: res.sdhstate="spheropen";break;
		case 5: res.sdhstate="spherclosed";break;
		case 6: res.sdhstate="paropen";break;
		case 7: res.sdhstate="parclosed";break;
		case 8: res.sdhstate="point";break;
		case 9: res.sdhstate="fist";break;
		}
		std::cout << "best sdh state: " << res.sdhstate << std::endl;
		res.bestVsdh = result_sdh;

//--------------------------arm result-------------------------------

	std::vector<std::vector<float> >  Varm;
	double result_arm;
	int result_armstate;

	reward_arm (req.action_name, req.action_stage,req.result_action, Varm,result_arm,result_armstate,T);
	switch (result_armstate)
	{
	case 0: res.armstate="home";break;
	case 1: res.armstate="folded";break;
	case 2: res.armstate="pregrasp";break;
	case 3: res.armstate="pregrasp_top";break;
	case 4: res.armstate="grasp";break;
	case 5: res.armstate="hold";break;
	case 6: res.armstate="pre_look_at_table";break;
	case 7: res.armstate="look_at_table";break;
	case 8: res.armstate="overtray";break;
	case 9: res.armstate="overtray_top";break;
	case 10: res.armstate="tray";break;
	case 11: res.armstate="intermediateback";break;
	case 12: res.armstate="intermediatebacklow";break;
	case 13: res.armstate="intermediatefront";break;
	case 14: res.armstate="intermediatefront_top";break;
	case 15: res.armstate="wavein";break;
	case 16: res.armstate="waveout";break;
	}
	std::cout << "best arm state: " << res.armstate << std::endl;
	res.bestVarm = result_arm;

//-----------------------------head result-------------------------

	std::vector<std::vector<float> >  Vhead;
	double result_head;
	int result_headstate;

	reward_head (req.action_name, req.action_stage,req.result_action, Vhead, result_head, result_headstate, T);
	switch (result_headstate)
		{
		case 0: res.headstate="front";break;
		case 1: res.headstate="back";break;
		}
		std::cout << "best head state: " << res.headstate << std::endl;
		res.bestVhead = result_head;

//-----------------------------torso result-------------------------

	std::vector<std::vector<float> >  Vtorso;
	double result_torso;
	int result_torsostate;

	reward_torso (req.action_name, req.action_stage, req.result_action, Vtorso,result_torso,result_torsostate,T);
	switch (result_torsostate)
	{
	case 0: res.torsostate="home";break;
	case 1: res.torsostate="left";break;
	case 2: res.torsostate="right";break;
	case 3: res.torsostate="front";break;
	case 4: res.torsostate="front_left";break;
	case 5: res.torsostate="front_right";break;
	case 6: res.torsostate="back";break;
	case 7: res.torsostate="back_extreme";break;
	case 8: res.torsostate="back_left";break;
	case 9: res.torsostate="back_left_extreme";break;
	case 10: res.torsostate="back_right";break;
	case 11: res.torsostate="back_right_extreme";break;
	case 12: res.torsostate="nod";break;
	case 13: res.torsostate="lookontray";break;
	case 14: res.torsostate="bow";break;
	case 15: res.torsostate="shake";break;
	}
	std::cout << "best torso state: " << res.torsostate << std::endl;
	res.bestVtorso = result_torso;

//-----------------------------tray result-------------------------

		std::vector<std::vector<float> >  Vtray;
		double result_tray;
		int result_traystate;

		reward_tray (req.action_name, req.action_stage, req.result_action, Vtray,result_tray,result_traystate,T);
		switch (result_traystate)
		{
			case 0: res.traystate="up";break;
			case 1: res.traystate="down";break;
		}
		std::cout << "best tray state: " << res.traystate << std::endl;
		res.bestVtray = result_tray;

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "rewardserver");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("rewardserver", reward);
    ROS_INFO("Ready to compute arm reward function");
    ROS_INFO("Ready to compute head reward function");
    ROS_INFO("Ready to compute tray reward function");
    ROS_INFO("Ready to compute sdh reward function");
    ROS_INFO("Ready to compute torso reward function");

    ros::spin();

    return 0;
}
