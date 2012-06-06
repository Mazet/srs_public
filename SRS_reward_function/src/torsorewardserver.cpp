/*
 * torsorewardserver.cpp
 *
 *  Created on: 30 Apr 2012
 *      Author: srs
 */

#include "ros/ros.h"
#include "SRS_reward_function/rewardsrv.h"
#include "func_torso.h"

bool torso_reward(SRS_reward_function::rewardsrv::Request  &req,
			SRS_reward_function::rewardsrv::Response  &res)
{

	//std::cout << "input" <<std::endl;
	std::vector<std::vector<float> >  Vtorso;
	double result_torso;
	int result_torsostate;
	reward_torso (req.action_name, req.action_stage,Vtorso,result_torso,result_torsostate);
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
	std::cout << res.torsostate << std::endl;
	res.bestVtorso = result_torso;
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "torsorewardserver");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("torsorewardserver", torso_reward);
    ROS_INFO("Ready to compute torso reward function");

    ros::spin();

    return 0;
}
