#include "ros/ros.h"
#include "SRS_reward_function/rewardsrv.h"
#include "func_arm.h"

bool arm_reward(SRS_reward_function::rewardsrv::Request  &req,
			SRS_reward_function::rewardsrv::Response  &res)
{

	//std::cout << "input" <<std::endl;
	std::vector<std::vector<float> >  Varm;
	double result_arm;
	int result_armstate;

	reward_arm (req.action_name, req.action_stage,Varm,result_arm,result_armstate);
	//std::cout << Vs[0][0] << std::endl;
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
	std::cout << res.armstate << std::endl;
	res.bestVarm = result_arm;

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "armrewardserver");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("armrewardserver", arm_reward);
    ROS_INFO("Ready to compute arm reward function");

    ros::spin();

    return 0;
}
