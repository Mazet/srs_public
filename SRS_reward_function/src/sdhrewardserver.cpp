/*
 * sdhrewardserver.cpp
 *
 *  Created on: 30 Apr 2012
 *      Author: srs
 */

#include "ros/ros.h"
#include "SRS_reward_function/rewardsrv.h"
#include "func_sdh.h"

bool sdh_reward(SRS_reward_function::rewardsrv::Request  &req,
			SRS_reward_function::rewardsrv::Response  &res)
{

	//std::cout << "input" <<std::endl;
	std::vector<std::vector<float> >  Vsdh;
	double result_sdh;
	int result_sdhstate;

	reward_sdh (req.action_name, req.action_stage,Vsdh,result_sdh,result_sdhstate);
	//std::cout << Vs[0][0] << std::endl;
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
	std::cout << res.sdhstate << std::endl;
	res.bestVsdh = result_sdh;
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "sdhrewardserver");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("sdhrewardserver", sdh_reward);
    ROS_INFO("Ready to compute sdh reward function");

    ros::spin();

    return 0;
}

