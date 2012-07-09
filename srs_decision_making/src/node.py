#!/usr/bin/env python
#import roslib; roslib.load_manifest('srs_decision_making')
#import rospy
#
#from pr2_controllers_msgs.msg import *
#from srs_monitoring_statemachines import *
#from robot_configuration import *
    
        
#def get_sdh_state(msg):
#    print 'ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo'
#    print list(msg.desired.positions)
#    global current_task_info
#    current_task_info.sdh_pos = list(msg.desired.positions)
#
#def get_arm_state(msg):
#    print 'hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh'
#    print list(msg.desired.positions)
#    global current_task_info
#    current_task_info.arm_pos = list(msg.desired.positions)
#    print current_task_info.arm_pos
#    
#def get_head_state(msg):
#    print 'pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp'
#    print list(msg.desired.positions)
#    global current_task_info
#    current_task_info.head_pos = list(msg.desired.positions)
#    
#def get_torso_state(msg):
#    print 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa'
#    print list(msg.desired.positions)
#    global current_task_info
#    current_task_info.torso_pos = list(msg.desired.positions)
#    
#def get_tray_state(msg):
#    print 'vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv'
#    print list(msg.desired.positions)
#    global current_task_info
#    current_task_info.tray_pos = list(msg.desired.positions)
    
#def listener():
#    rospy.init_node('listener')
   # sdh_state = rospy.Subscriber("/sdh_controller/state", JointTrajectoryControllerState, get_sdh_state);
    #arm_state = rospy.Subscriber("/arm_controller/state", JointTrajectoryControllerState, get_arm_state);
    #head_state = rospy.Subscriber("/head_controller/state", JointTrajectoryControllerState, get_head_state);
    #torso_state = rospy.Subscriber("/torso_controller/state", JointTrajectoryControllerState, get_torso_state);
    #tray_state = rospy.Subscriber("/tray_controller/state", JointTrajectoryControllerState, get_tray_state);
#    rospy.spin()
#   
#if __name__ == '__main__':
#    listener()