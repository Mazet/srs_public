/*
 * headrewardserver.cpp
 *
 *  Created on: 30 Apr 2012
 *      Author: srs
 */

#include "ros/ros.h"
#include "SRS_reward_function/rewardsrv.h"
#include "func_head.h"

bool head_reward(SRS_reward_function::rewardsrv::Request  &req,
			SRS_reward_function::rewardsrv::Response  &res)
{
	std::vector<std::vector<float> >  Vhead;
	double result_head;
	int result_headstate;
	reward_head (req.action_name, req.action_stage, Vhead,result_head,result_headstate);
	switch (result_headstate)
		{
		case 0: res.headstate="front";break;
		case 1: res.headstate="back";break;
		}
		std::cout << res.headstate << std::endl;
		res.bestVhead = result_head;
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "headrewardserver");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("headrewardserver", head_reward);
    ROS_INFO("Ready to compute head reward function");
    ros::spin();
    return 0;
}

