#!/usr/bin/env python
import roslib; roslib.load_manifest('SRS_reward_function')

from SRS_reward_function.srv import *
import rospy


def sum(req):
     #print "Returning [%s + %s = %s]"%(req.a, req.b, (req.a + req.b))
     #print "returning [%s - %s = %s]"%(req.a, req.b, (req.a - req.b))
     respons=servertypefakeResponse()
     respons.sum=req.a + req.b
     respons.sub=req.a - req.b
     return respons
 
 
def result():
    rospy.init_node('fake node')
    s = rospy.Service('servernamefake', servertypefake, sum)
    rospy.loginfo("servernamefake ready.")
    rospy.spin()
    return 
 
if __name__ == "__main__":
     result()
     