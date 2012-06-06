/*
 * trayrewardserver.cpp
 *
 *  Created on: 30 Apr 2012
 *      Author: srs
 */

#include "ros/ros.h"
#include "SRS_reward_function/rewardsrv.h"
#include "func_tray.h"

bool tray_reward(SRS_reward_function::rewardsrv::Request  &req,
			SRS_reward_function::rewardsrv::Response  &res)
{
	std::vector<std::vector<float> >  Vtray;
	double result_tray;
	int result_traystate;
	reward_tray (req.action_name, req.action_stage, Vtray,result_tray,result_traystate);
	switch (result_traystate)
	{
		case 0: res.traystate="up";break;
		case 1: res.traystate="down";break;
	}
	std::cout << res.traystate << std::endl;
	res.bestVtray = result_tray;
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "trayrewardserver");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("trayrewardserver", tray_reward);
    ROS_INFO("Ready to compute tray reward function");

    ros::spin();

    return 0;
}

