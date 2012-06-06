#!/usr/bin/env python
import roslib; roslib.load_manifest('SRS_reward_function')
import rospy
from SRS_reward_function.srv import *



def Fake(a,b):    
    rospy.wait_for_service('servernamefake')
    try:
        add_two_ints = rospy.ServiceProxy('servernamefake', servertypefake)
        rospy.loginfo("client")
        resp1 = add_two_ints(a,b)
        print resp1
        

        #rospy.loginfo(resp1.object_list)
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e
         
    
if __name__ == "__main__":
    a=2
    b=3
    Fake(a,b)