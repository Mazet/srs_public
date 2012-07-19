#!/usr/bin/python
#################################################################
##\file
#
# \note
# Copyright (c) 2011 \n
# Cardiff University \n\n
#
#################################################################
#
# \note
# Project name: Multi-Role Shadow Robotic System for Independent Living
# \note
# ROS stack name: srs
# \note
# ROS package name: srs_decision_making
#
# \author
# Author: Renxi Qiu, email: renxi.qiu@gmail.com
#
# \date Date of creation: Oct 2011
#
# \brief
# Task coordination and interfacing for SRS decision making
#
#################################################################
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# - Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer. \n
#
# - Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution. \n
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License LGPL as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License LGPL for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License LGPL along with this program.
# If not, see <http://www.gnu.org/licenses/>.
#
#################################################################

from srs_monitoring_statemachines import *
from robot_configuration import *
import roslib; roslib.load_manifest('SRS_reward_function')
import rospy
from SRS_reward_function.srv import *
from geometry_msgs.msg import *
from pr2_controllers_msgs.msg import *
flag='true'
"""
This file contains state machines for robot configuration checking during the operation
The pause and resume generic state are also included in the file

The actual robot configuration pre post condition are imported from robot_configuration.py

Please note that:
As minimal control unit of the DM is generic state, therefore the pause and resume of the generic states may not be the same as the pause and resume of the real actions of robot.
and, it will be useful to check the pause within the generic state to avoid unnecessary time out.

"""

# Checking during robot is paused
class state_checking_during_paused (smach.State):
    def __init__(self):
        smach.State.__init__(self , outcomes =['resume', 'stopped', 'preempted'])
    
    
    def execute (self, userdata):

        global current_task_info
        
        
        while not self.preempt_requested():
            #if stop command has been received during the pause
            if current_task_info.get_stop_required():
                #reset the flag to normal
                current_task_info.set_stop_acknowledged(True)
                try:
                    sss.say([current_task_info.speaking_language['Stop']],False)
                except:
                    print sys.exc_info()
                    
                #complete the state and return stop
                return 'stopped'
            
            #if another command with higher priority received during the pause
            elif current_task_info.get_customised_preempt_required():
                #reset the flag to normal
                current_task_info.set_customised_preempt_acknowledged(True)
                #complete the state and return customised_preempted
                return 'preempted'
            
            #if task is resumed
            elif not current_task_info.get_pause_required():
                #return to last operation
                try:
                    sss.say([current_task_info.speaking_language['Resume']],False)
                except:
                    print sys.exc_info()
                return 'resume'
                        
            #elif rospy.is_shutdown:
            # return 'preempted'
            
            #sleep 1 sec and check again
            rospy.sleep(1)
            
        self.service_preempt()
        
        return 'preempted'
    
################################################################################################

def get_sdh_state(msg):
    global sdh_pos
    sdh_pos = list(msg.desired.positions)
    #print sdh_pos
    
def get_arm_state(msg):
    global arm_pos
    arm_pos = list(msg.desired.positions)
    #rospy.spin();
        
def get_head_state(msg):
    global head_pos
    head_pos = list(msg.desired.positions)
#    rospy.spin();
    
def get_torso_state(msg):
    global torso_pos
    torso_pos = list(msg.desired.positions)
#    rospy.spin();
    
def get_tray_state(msg):
    global tray_pos
    tray_pos = list(msg.desired.positions)
#    rospy.spin();

def my_movement(action_name, action_stage, result_action, object_in_hand, object_on_tray, msg):
    global current_task_info, arm_pos, sdh_pos
    len_step_info = len(current_task_info.last_step_info)
    result_action = current_task_info.last_step_info[len_step_info - 1].outcome
          
    #sdh_state = rospy.Subscriber("/sdh_controller/state", JointTrajectoryControllerState, get_sdh_state);
    arm_state = rospy.Subscriber("/arm_controller/state", JointTrajectoryControllerState, get_arm_state);
    head_state = rospy.Subscriber("/head_controller/state", JointTrajectoryControllerState, get_head_state);
    torso_state = rospy.Subscriber("/torso_controller/state", JointTrajectoryControllerState, get_torso_state);
    tray_state = rospy.Subscriber("/tray_controller/state", JointTrajectoryControllerState, get_tray_state);
    
    rospy.wait_for_service('rewardserver',10)
    try:
        reward = rospy.ServiceProxy('rewardserver', rewardsrv)
        rospy.loginfo("client")
        
        reqsrv=rewardsrvRequest()
        reqsrv.action_name=action_name
        reqsrv.action_stage=action_stage
        reqsrv.result_action=result_action
        reqsrv.x0y0=current_task_info.probability[0][0]
        reqsrv.x0y1=current_task_info.probability[0][1]
        reqsrv.x0y2=current_task_info.probability[0][2]
        reqsrv.x0y3=current_task_info.probability[0][3]
        reqsrv.x1y0=current_task_info.probability[1][0]
        reqsrv.x1y1=current_task_info.probability[1][1]
        reqsrv.x1y2=current_task_info.probability[1][2]
        reqsrv.x1y3=current_task_info.probability[1][3]
        reqsrv.x2y0=current_task_info.probability[2][0]
        reqsrv.x2y1=current_task_info.probability[2][1]
        reqsrv.x2y2=current_task_info.probability[2][2]
        reqsrv.x2y3=current_task_info.probability[2][3]
        reqsrv.x3y0=current_task_info.probability[3][0]
        reqsrv.x3y1=current_task_info.probability[3][1]
        reqsrv.x3y2=current_task_info.probability[3][2]
        reqsrv.x3y3=current_task_info.probability[3][3]
        
        resp = reward(reqsrv)
        current_task_info.probability[0][0]=resp.X0Y0
        current_task_info.probability[0][1]=resp.X0Y1
        current_task_info.probability[0][2]=resp.X0Y2
        current_task_info.probability[0][3]=resp.X0Y3
        current_task_info.probability[1][0]=resp.X1Y0
        current_task_info.probability[1][1]=resp.X1Y1
        current_task_info.probability[1][2]=resp.X1Y2
        current_task_info.probability[1][3]=resp.X1Y3
        current_task_info.probability[2][0]=resp.X2Y0
        current_task_info.probability[2][1]=resp.X2Y1
        current_task_info.probability[2][2]=resp.X2Y2
        current_task_info.probability[2][3]=resp.X2Y3
        current_task_info.probability[3][0]=resp.X3Y0
        current_task_info.probability[3][1]=resp.X3Y1
        current_task_info.probability[3][2]=resp.X3Y2
        current_task_info.probability[3][3]=resp.X3Y3
        
        if current_task_info.object_on_tray == True :
            current_task_info.probability = [[0.1,0.7,0.2,0],[1,0,0,0],[0.7,0,0.3,0],[1,0,0,0]]
        
        """
        # sdhstate define only by the name    
        sdhstate=resp.sdhstate
        # sdhstate define by the coordinates 
        if sdhstate =='home':
            sdhstate = [[0.0,0.0,0.0,0.0,0.0,0.0,0.0]]
        if sdhstate =='cylclosed':
            sdhstate = [[0.0,0.0,1.0472,0.0,1.0472,0.0,1.0472]]
        if sdhstate =='cylopen':
            sdhstate = [[0.0,-0.9854,0.9472,-0.9854,0.9472,-0.9854,0.9472]]
        if sdhstate =='cyltotalopen':
            sdhstate = [[0.0,-1.57,-1.57,-1.57,-1.57,-1.57,-1.57]]
        if sdhstate =='spheropen':
            sdhstate = [[1.047,-0.785,1.047,-0.785,1.047,-0.785,1.047]]
        if sdhstate =='spherclosed':
            sdhstate = [[1.047,-0.262,1.047,-0.262,1.047,-0.262,1.047]]
        if sdhstate =='paropen':
            sdhstate = [[-0.524,0,0,1.57,0.524,-0.524,0.524]]
        if sdhstate =='parclosed':
            sdhstate = [[1.57,0,1.57,0,0,0,0]]
        if sdhstate =='point':
            sdhstate = [[0,0,1.57,0,1.57,0,0]]
        if sdhstate =='fist':
            sdhstate = [[0,0,1.57,0,1.57,0,1.57]]                 
        if current_task_info.object_in_hand == False :
            # threshold to define if the robot need to move or not
            print sdhstate
            print '------------------------------------------------------------'
            print sdh_pos
            print '--------------------------------'
            print sdh_pos[0] - sdhstate[0][0]
            print sdh_pos[1] - sdhstate[0][1]
            print sdh_pos[2] - sdhstate[0][2]
            print sdh_pos[3] - sdhstate[0][3]
            print sdh_pos[4] - sdhstate[0][4]
            print sdh_pos[5] - sdhstate[0][5]
            print sdh_pos[6] - sdhstate[0][6]
               
            if -0.01 < sdh_pos[0] - sdhstate[0][0] > 0.01 or -0.01 < sdh_pos[1] - sdhstate[0][1] > 0.01 or-0.01 < sdh_pos[2] - sdhstate[0][2] > 0.01 or -0.01 < sdh_pos[3] - sdhstate[0][3] > 0.01 or -0.01 < sdh_pos[4] - sdhstate[0][4] > 0.01 or -0.01 < sdh_pos[5] - sdhstate[0][5] > 0.01 or -0.01 < sdh_pos[6] - sdhstate[0][6] > 0.01:  
               sss.move("sdh",sdhstate)
        """
  
        # armstate define only by the name      
        armstate=resp.armstate
        #armstate define by the coordinates
        if armstate =='folded':
            armstate = [[-1.1572567240035734, -1.9104664691761568, -2.5334780195730255, -1.7853311980377056, -0.072798739390243047, 0.91767934923272776, -1.8876618005378798]]
        if armstate =='look_at_table':
            armstate = [[-1.90413007129692, -0.43676863707511047, -2.8670597283903604, -1.2371477849958294, 0.078324145463379971, 1.1674038268438356, 1.7663080901665025]]
        if armstate =='hold':
            armstate = [[-1.4622220395387109, -1.483421172261264, -2.5722112955751717, -2.0406781220494987, 0.40775763876802901, 1.8094765570595979, -2.8368191660629205]]
        if armstate =='home':
            armstate = [[0,0,0,0,0,0,0]]
        if armstate =='pregrasp':
            armstate = [[-1.3813422735995828, -1.9312548399287899, -1.7251153715474463, -1.4565057632094409, 0.7169946808744756, 1.0560171841958719, -2.1230019199424044]]
        if armstate =='pregrasp_top':
            armstate = [[-0.87587967265669509, -0.98765406924023813, -2.019365717487724, -0.86609658321908944, -0.14251239921016767, 1.5534633142745486, -2.1222931407940107]]
        if armstate =='grasp':
            armstate = [[-0.94338446021682099, -1.987128639793466, -1.6757425957025061, -1.2319960038941786, 0.92698961598913809, 0.7957495543301375, -2.2609604309432707]]
        if armstate =='pre_look_at_table':
            armstate = [[-1.4117332144741783, -1.0933802021501384, -2.8143842535448362, -2.0943951023931953, 0.32534573315130511, 1.5282712545442345, 1.7578776443176236]]
        if armstate =='overtray':
            armstate = [[2.9670597283903604, -1.0850245914937158, -2.8517849530558705, -1.490963271231841, 0.69903542231877758, 1.0647794507576016, -1.9565543563358203]]
        if armstate =='overtray_top':
            armstate = [[2.9670597283903604, -1.3250728580096636, -1.8056213630534641, -1.4889849497870824, -1.3344558436999245, 2.0897956106166564, -1.9597330892331219]]
        if armstate =='tray':
            armstate = [[2.8545925371816212, -1.1411602564796222, -2.879793265790644, -1.4768269321056455, 0.55049237134044171, 1.0657754724693511, -2.029771517204098]]
        if armstate =='intermediateback':
            armstate = [[-0.92723326226047276, -1.0878091156907497, -1.7511329390916868, -2.0350967789643617, 0.75547017562671237, 1.55547223138452, -2.6139619402066767]]
        if armstate =='intermediatebacklow':
            armstate = [[0.34600003337848573, -1.6400000103328185, -1.8149999713886731, -1.6349999713897863, -2.9670597283903604, -0.95000002861023169, 1.9699999904632339]]
        if armstate =='intermediatefront':
            armstate = [[2.567286997401903, -0.76650447903842134, -2.879793265790644, -1.3169067774275871, 0.59769801545593759, 1.3751587638740583, -1.9299075952888678]]
        if armstate =='intermediatefront_top':
            armstate = [[2.8247824942616617, -0.98670392150558073, -1.5027014062658048, -1.4649695735385015, -1.2100522103232669, 1.5809503007832906, -2.8119176816695504]]
        if armstate =='wavein':
            armstate = [[1.5, 0.5, 0.0, -0.5, 0.0, 0.5, 0.0]]
        if armstate =='waveout':
            armstate = [[1.5, 0.5, 0.0, 0.5, 0.0, -0.5, 0.0]]
            
        # threshold to define if the robot need to move or not
        
#        print armstate
#        print '======================================================================================='
#        print arm_pos
#        print '=============================='
#        print arm_pos[0] - armstate[0][0]
#        print arm_pos[1] - armstate[0][1]
#        print arm_pos[2] - armstate[0][2]
#        print arm_pos[3] - armstate[0][3]
#        print arm_pos[4] - armstate[0][4]
#        print arm_pos[5] - armstate[0][5]
#        print arm_pos[6] - armstate[0][6]
        if -0.0000000001 < arm_pos[0] - armstate[0][0] > 0.0000000001 or -0.0000000001 < arm_pos[1] - armstate[0][1] > 0.0000000001 or-0.0000000001 < arm_pos[2] - armstate[0][2] > 0.0000000001 or -0.0000000001 < arm_pos[3] - armstate[0][3] > 0.0000000001 or -0.0000000001 < arm_pos[4] - armstate[0][4] > 0.0000000001 or -0.0000000001 < arm_pos[5] - armstate[0][5] > 0.0000000001 or -0.0000000001 < arm_pos[6] - armstate[0][6] > 0.0000000001:
        #if -0.0000000001 < current_task_info.arm_pos[0] - armstate[0][0] > 0.0000000001 or -0.0000000001 < current_task_info.arm_pos[1] - armstate[0][1] > 0.0000000001 or-0.0000000001 < current_task_info.arm_pos[2] - armstate[0][2] > 0.0000000001 or -0.0000000001 < current_task_info.arm_pos[3] - armstate[0][3] > 0.0000000001 or -0.0000000001 < current_task_info.arm_pos[4] - armstate[0][4] > 0.0000000001 or -0.0000000001 < current_task_info.arm_pos[5] - armstate[0][5] > 0.0000000001 or -0.0000000001 < current_task_info.arm_pos[6] - armstate[0][6] > 0.0000000001:
            sss.move("arm",armstate)
            
        # headstate define only by the name      
        headstate=resp.headstate
        # headstate define by the coordinates
        if headstate =='front':
            headstate = [[-3.1415926]]
        if headstate =='back':
            headstate = [[0.0]]
            
        # threshold to define if the robot need to move or not
        
#        print headstate
#        print '*********************************************************'
#        print head_pos
#        print '*******************************'
#        print head_pos[0] - headstate[0][0]
        if -0.00001 < head_pos[0] - headstate[0][0] > 0.00001 :
            sss.move("head",headstate)
            
        # torsostate define only by the name
        torsostate=resp.torsostate
        # torsostate define by the coordinates 
        if torsostate =='home':
            torsostate = [[0.0,0.0,0.0]]
        if torsostate =='left':
            torsostate = [[0.0,-0.1,0.0]]
        if torsostate =='right':
            torsostate = [[0.0,0.1,0.0]]
        if torsostate =='front':
            torsostate = [[-0.1,0.0,-0.15]]
        if torsostate =='front_left':
            torsostate = [[-0.1,-0.1,-0.15]]
        if torsostate =='front_right':
            torsostate = [[-0.1,0.1,-0.15]]
        if torsostate =='back':
            torsostate = [[0.1,0.0,0.15]]
        if torsostate =='back_extreme':
            torsostate = [[0.20,0.0,0.35]]
        if torsostate =='back_left':
            torsostate = [[0.1,-0.1,0.15]]
        if torsostate =='back_left_extreme':
            torsostate = [[0.20,-0.1,0.35]]
        if torsostate =='back_right':
            torsostate = [[0.1,0.1,0.15]]
        if torsostate =='back_right_extreme':
            torsostate = [[0.20,0.1,0.35]]
        if torsostate =='lookontray':
            torsostate = [[-0.174,0,-0.262]]
            
        # threshold to define if the robot need to move or not

#        print torsostate
#        print '+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++'
#        print torso_pos
#        print '+++++++++++++++++++++++++++++++++++++++++++++'
#        print torso_pos[0] - torsostate[0][0]
#        print torso_pos[1] - torsostate[0][1]
#        print torso_pos[2] - torsostate[0][2]
        if -0.01 < torso_pos[0] - torsostate[0][0] > 0.01 or -0.01 < torso_pos[1] - torsostate[0][1] > 0.01 or-0.01 < torso_pos[2] - torsostate[0][2] > 0.01 :       
            sss.move("torso",torsostate)
            
        # traystate define only by the name    
        traystate=resp.traystate    
        # traystate define by the coordinates
        if traystate =='up':
            traystate = [[0.0]]
        if traystate =='down':
            traystate = [[-3.1415926]]
        
        if current_task_info.object_on_tray == False :
            
            # threshold to define if the robot need to move or not
            
#            print traystate
#            print '///////////////////////////////////////////////////////////////'
#            print tray_pos
#            print '////////////////////////////////'
#            print tray_pos[0] - traystate[0][0]
            if -0.00001 < tray_pos[0] - traystate[0][0] > 0.0001 :
                sss.move("tray",traystate)
           
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e
                   
################################################################################################

def robot_configuration(parent, action_name, action_stage, result_action, object_in_hand, object_on_tray, msg):
    
    global current_task_info
    global component_list
    global robot_config
    global robot_config_need_no_action
    
    handles = list()

################################################################################################

    my_movement(action_name, action_stage, result_action, object_in_hand,object_on_tray, msg)

################################################################################################
    
    if action_name == 'navigation':
        if current_task_info.object_on_tray:
            if current_task_info.object_in_hand:
                action_name = 'navigation_object_on_tray'
            else:
                action_name = 'navigation_object_on_tray_and_sdh'
        else:
            if current_task_info.object_in_hand:
                action_name = 'navigation_object_in_sdh'
            else:
                action_name = 'navigation_no_object'
                
    try:
        #bring robot into the pre-configuration state
        if action_stage == 'pre-config':
            #initial the sss handles
            for index in range(len(component_list)):
                if robot_config_pre[action_name][component_list[index]] in robot_config_need_no_action:
                    handles.append(None)
                else:
                    if component_list[index] == "arm":
                        #handles.append(sss.move_planned(component_list[index], robot_config_pre[action_name][component_list[index]], False))
                        handles.append(sss.move(component_list[index], robot_config_pre[action_name][component_list[index]], False))
                    else:
                        handles.append(sss.move(component_list[index], robot_config_pre[action_name][component_list[index]], False))
                    
        #bring robot into the post-configuration state
        if action_stage == 'post-config':
            #initial the sss handles
            for index in range(len(component_list)):
                if robot_config_post[action_name][component_list[index]] in robot_config_need_no_action:
                    handles.append(None)
                else:
                    if component_list[index] == "arm":
                        handles.append(sss.move(component_list[index], robot_config_post[action_name][component_list[index]], False))
                    else:
                        handles.append(sss.move(component_list[index], robot_config_post[action_name][component_list[index]], False))
                    
    except KeyError:
        print("dictionary key is not found in the set of existing keys")
        return failed
    except IndexError:
        print("Index is out of range")
        return failed
    except:
        print("unexpected error during %s and %s",action_name,action_stage)
        return failed
        
    #wait for action to finish
    for index in range(len(component_list)):
        if handles[index] != None:
            if parent.preempt_requested():
                parent.service_preempt()
                return 'preempted'
            else:
                handles[index].wait()
                ###########################################################################
                #TO DO
                #need check the state of the handles. return failed after the handles fails.
                #
                ############################################################################

    return 'succeeded'
    
                    
            
             


class pre_conf(smach.State):
    def __init__(self):
        smach.State.__init__(self , outcomes=['succeeded', 'failed', 'preempted'], input_keys=['action_name'])
    
    def execute (self, userdata):
        return robot_configuration(self, userdata.action_name, 'pre-config','','','','')
    
        
class post_conf(smach.State):
    def __init__(self):
        smach.State.__init__(self , outcomes=['succeeded', 'failed', 'preempted'], input_keys=['action_name'])
    
    def execute (self, userdata):
        return robot_configuration(self, userdata.action_name, 'post-config','','','','')


co_sm_pre_conf = smach.Concurrence (outcomes=['succeeded', 'failed', 'stopped', 'preempted', 'paused'],
                 default_outcome='failed',
                 input_keys=['action_name'],
                 child_termination_cb = common_child_term_cb,
                 outcome_cb = common_out_cb)
with co_sm_pre_conf:
            smach.Concurrence.add('State_Checking_During_Operation', state_checking_during_operation())
            smach.Concurrence.add('MAIN_OPERATION', pre_conf(),
                                  remapping={'action_name':'action_name'})
            
co_sm_post_conf = smach.Concurrence (outcomes=['succeeded', 'failed', 'stopped', 'preempted', 'paused'],
                 default_outcome='failed',
                 input_keys=['action_name'],
                 child_termination_cb = common_child_term_cb,
                 outcome_cb = common_out_cb)
with co_sm_post_conf:
            smach.Concurrence.add('State_Checking_During_Operation', state_checking_during_operation())
            smach.Concurrence.add('MAIN_OPERATION', post_conf(),
                                  remapping={'action_name':'action_name'})

"""
#It is impossible to reach paused state as the sss used in pre/post conf checking the pause by itself, and will never return time-out
class co_sm_pre_conf(smach.Concurrence):
def __init__(self, action_name=''):
smach.Concurrence.__init__(outcomes=['succeeded', 'failed', 'stopped', 'preempted', 'paused'],
default_outcome='failed',
child_termination_cb = common_child_term_cb,
outcome_cb = common_out_cb)
self.action_name=action_name
with self:
smach.Concurrence.add('State_Checking_During_Operation', state_checking_during_operation())
smach.Concurrence.add('MAIN_OPERATION', preconf(self.action_name))
#It is impossible to reach paused state as the sss used in pre/post conf checking the pause by itself, and will never return time-out
class co_sm_post_conf(smach.Concurrence):
def __init__(self, action_name=''):
smach.Concurrence.__init__(outcomes=['succeeded', 'failed', 'stopped', 'preempted', 'paused'],
default_outcome='failed',
child_termination_cb = common_child_term_cb,
outcome_cb = common_out_cb)
self.action_name=action_name
with self:
smach.Concurrence.add('State_Checking_DurinTg_Operation', state_checking_during_operation())
smach.Concurrence.add('MAIN_OPERATION', post_conf(self.action_name))
"""


"""
def add_common_states(parent):
with parent:
smach.StateMachine.add('PRE_CONFIG', co_sm_pre_conf,
transitions={'succeeded':'ACTION', 'paused':'PAUSED_DURING_PRE_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
remapping={'action_name':'action_name'})
smach.StateMachine.add('POST_CONFIG', co_sm_post_conf,
transitions={'succeeded':'succeeded', 'paused':'PAUSED_DURING_POST_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
remapping={'action_name':'action_name'})
smach.StateMachine.add('PAUSED_DURING_PRE_CONFIG', state_checking_during_paused(),
transitions={'resume':'PRE_CONFIG','preempted':'preempted', 'stopped':'stopped'})
smach.StateMachine.add('PAUSED_DURING_ACTION', state_checking_during_paused(),
transitions={'resume':'ACTION','preempted':'preempted', 'stopped':'stopped'})
smach.StateMachine.add('PAUSED_DURING_POST_CONFIG', state_checking_during_paused(),
transitions={'resume':'POST_CONFIG','preempted':'preempted', 'stopped':'stopped'})
"""


class srs_navigation_operation(smach.StateMachine):
    
    def __init__(self):
        smach.StateMachine.__init__(self, outcomes=['succeeded', 'not_completed', 'failed', 'stopped', 'preempted'],
                                    input_keys=['target_base_pose','semi_autonomous_mode'])
        #self.action_name = 'navigation'
        self.userdata.action_name = 'navigation'
        #add_common_states(self)
        
        with self:

            smach.StateMachine.add('PRE_CONFIG', co_sm_pre_conf,
                    transitions={'succeeded':'ACTION', 'paused':'PAUSED_DURING_PRE_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'action_name':'action_name'})
            
            smach.StateMachine.add('ACTION', co_sm_navigation,
                    transitions={'succeeded':'POST_CONFIG', 'not_completed':'not_completed', 'paused':'PAUSED_DURING_ACTION', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'semi_autonomous_mode':'semi_autonomous_mode','target_base_pose':'target_base_pose'})
            
            smach.StateMachine.add('POST_CONFIG', co_sm_post_conf,
                    transitions={'succeeded':'succeeded', 'paused':'PAUSED_DURING_POST_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'action_name':'action_name'})
            
            smach.StateMachine.add('PAUSED_DURING_PRE_CONFIG', state_checking_during_paused(),
                    transitions={'resume':'PRE_CONFIG','preempted':'preempted', 'stopped':'stopped'})
            
            smach.StateMachine.add('PAUSED_DURING_ACTION', state_checking_during_paused(),
                    transitions={'resume':'ACTION','preempted':'preempted', 'stopped':'stopped'})
            
            smach.StateMachine.add('PAUSED_DURING_POST_CONFIG', state_checking_during_paused(),
                    transitions={'resume':'POST_CONFIG','preempted':'preempted', 'stopped':'stopped'})
    
class srs_put_on_tray_operation(smach.StateMachine):
    
    def __init__(self):
        smach.StateMachine.__init__(self, outcomes=['succeeded', 'not_completed', 'failed', 'stopped', 'preempted'],
                                    input_keys=['grasp_categorisation'])
        self.userdata.action_name = 'put_on_tray'
        #add_common_states(self)
        
        with self:
            smach.StateMachine.add('PRE_CONFIG', co_sm_pre_conf,
                    transitions={'succeeded':'ACTION', 'paused':'PAUSED_DURING_PRE_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'action_name':'action_name'})
            
            smach.StateMachine.add('ACTION', co_sm_transfer_to_tray,
                    transitions={'succeeded':'POST_CONFIG', 'not_completed':'not_completed', 'paused':'PAUSED_DURING_ACTION', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'grasp_categorisation':'grasp_categorisation'})

        
            smach.StateMachine.add('POST_CONFIG', co_sm_post_conf,
                    transitions={'succeeded':'succeeded', 'paused':'PAUSED_DURING_POST_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'action_name':'action_name'})
            
            smach.StateMachine.add('PAUSED_DURING_PRE_CONFIG', state_checking_during_paused(),
                    transitions={'resume':'PRE_CONFIG','preempted':'preempted', 'stopped':'stopped'})
            
            smach.StateMachine.add('PAUSED_DURING_ACTION', state_checking_during_paused(),
                    transitions={'resume':'ACTION','preempted':'preempted', 'stopped':'stopped'})
            
            smach.StateMachine.add('PAUSED_DURING_POST_CONFIG', state_checking_during_paused(),
                    transitions={'resume':'POST_CONFIG','preempted':'preempted', 'stopped':'stopped'})

class srs_enviroment_update_operation(smach.StateMachine):
    
    def __init__(self):
        smach.StateMachine.__init__(self, outcomes=['succeeded', 'not_completed', 'failed', 'stopped', 'preempted'],
                                    input_keys=['scan_pose_list'])
        self.userdata.action_name = 'enviroment_update'
        #add_common_states(self)
        
        with self:
            smach.StateMachine.add('PRE_CONFIG', co_sm_pre_conf,
                    transitions={'succeeded':'ACTION', 'paused':'PAUSED_DURING_PRE_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'action_name':'action_name'})

            smach.StateMachine.add('ACTION', co_sm_enviroment_update,
                    transitions={'succeeded':'POST_CONFIG', 'not_completed':'not_completed', 'paused':'PAUSED_DURING_ACTION', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'scan_pose_list':'scan_pose_list'})
        
            smach.StateMachine.add('POST_CONFIG', co_sm_post_conf,
                    transitions={'succeeded':'succeeded', 'paused':'PAUSED_DURING_POST_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'action_name':'action_name'})
            
            smach.StateMachine.add('PAUSED_DURING_PRE_CONFIG', state_checking_during_paused(),
                    transitions={'resume':'PRE_CONFIG','preempted':'preempted', 'stopped':'stopped'})
            
            smach.StateMachine.add('PAUSED_DURING_ACTION', state_checking_during_paused(),
                    transitions={'resume':'ACTION','preempted':'preempted', 'stopped':'stopped'})
            
            smach.StateMachine.add('PAUSED_DURING_POST_CONFIG', state_checking_during_paused(),
                    transitions={'resume':'POST_CONFIG','preempted':'preempted', 'stopped':'stopped'})

            

class srs_detection_operation(smach.StateMachine):
    
    def __init__(self):
        smach.StateMachine.__init__(self, outcomes=['succeeded', 'not_completed', 'failed', 'stopped', 'preempted'],
                                    input_keys=['target_object_name','target_object_id', 'target_workspace_name','semi_autonomous_mode'],
                                    output_keys=['target_object_pose','target_object'])
        self.userdata.action_name = 'detection'
        self.userdata.target_object_pose = Pose()
        #add_common_states(self)
        
        with self:
                
            smach.StateMachine.add('PRE_CONFIG', co_sm_pre_conf,
                    transitions={'succeeded':'ACTION', 'paused':'PAUSED_DURING_PRE_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'action_name':'action_name'})
            
            smach.StateMachine.add('ACTION', co_sm_detection,
                    transitions={'succeeded':'POST_CONFIG', 'not_completed':'not_completed', 'paused':'PAUSED_DURING_ACTION', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'target_object_name':'target_object_name',
                                'target_object_id':'target_object_id',
                                'target_workspace_name':'target_workspace_name',
                                'semi_autonomous_mode':'semi_autonomous_mode',
                                'target_object_pose':'target_object_pose',
                                'target_object':'target_object'})
        
            smach.StateMachine.add('POST_CONFIG', co_sm_post_conf,
                    transitions={'succeeded':'succeeded', 'paused':'PAUSED_DURING_POST_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'action_name':'action_name'})
            
            smach.StateMachine.add('PAUSED_DURING_PRE_CONFIG', state_checking_during_paused(),
                    transitions={'resume':'PRE_CONFIG','preempted':'preempted', 'stopped':'stopped'})
            
            smach.StateMachine.add('PAUSED_DURING_ACTION', state_checking_during_paused(),
                    transitions={'resume':'ACTION','preempted':'preempted', 'stopped':'stopped'})
            
            smach.StateMachine.add('PAUSED_DURING_POST_CONFIG', state_checking_during_paused(),
                    transitions={'resume':'POST_CONFIG','preempted':'preempted', 'stopped':'stopped'})

class srs_grasp_operation(smach.StateMachine):
    
    def __init__(self):
        smach.StateMachine.__init__(self, outcomes=['succeeded', 'not_completed', 'failed', 'stopped', 'preempted'],
                                    input_keys=['target_object_name','target_object_id','target_object','target_workspace_name','semi_autonomous_mode'],
                                    output_keys=['grasp_categorisation'])
        self.userdata.action_name = 'grasp'
        self.userdata.grasp_categorisation = ""
        self.userdata.target_object_old_pose = Pose()
        
        #add_common_states(self)
        
        with self:
            smach.StateMachine.add('PRE_CONFIG', co_sm_pre_conf,
                    transitions={'succeeded':'ACTION', 'paused':'PAUSED_DURING_PRE_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'action_name':'action_name'})
            
            smach.StateMachine.add('ACTION', co_sm_new_grasp,
                    transitions={'succeeded':'POST_CONFIG', 'not_completed':'not_completed', 'paused':'PAUSED_DURING_ACTION', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'target_object_name':'target_object_name',
                                'semi_autonomous_mode':'semi_autonomous_mode',
                                'target_object_id':'target_object_id',
                                'target_object':'target_object',
                                'target_workspace_name':'target_workspace_name',
                                'grasp_categorisation':'grasp_categorisation'})
             
            smach.StateMachine.add('POST_CONFIG', co_sm_post_conf,
                    transitions={'succeeded':'succeeded', 'paused':'PAUSED_DURING_POST_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'action_name':'action_name'})
            
            smach.StateMachine.add('PAUSED_DURING_PRE_CONFIG', state_checking_during_paused(),
                    transitions={'resume':'PRE_CONFIG','preempted':'preempted', 'stopped':'stopped'})
            
            smach.StateMachine.add('PAUSED_DURING_ACTION', state_checking_during_paused(),
                    transitions={'resume':'ACTION','preempted':'preempted', 'stopped':'stopped'})
            
            smach.StateMachine.add('PAUSED_DURING_POST_CONFIG', state_checking_during_paused(),
                    transitions={'resume':'POST_CONFIG','preempted':'preempted', 'stopped':'stopped'})


class srs_old_grasp_operation(smach.StateMachine):
    
    def __init__(self):
        smach.StateMachine.__init__(self, outcomes=['succeeded', 'not_completed', 'failed', 'stopped', 'preempted'],
                                    input_keys=['target_object_name','target_object_id','target_object','semi_autonomous_mode'],
                                    output_keys=['grasp_categorisation'])
        self.userdata.action_name = 'grasp'
        self.userdata.grasp_categorisation = ""
        self.userdata.target_object_old_pose = Pose()
        
        #add_common_states(self)
        
        with self:
            smach.StateMachine.add('PRE_CONFIG', co_sm_pre_conf,
                    transitions={'succeeded':'ACTION', 'paused':'PAUSED_DURING_PRE_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'action_name':'action_name'})
            
            smach.StateMachine.add('ACTION', co_sm_old_grasp,
                    transitions={'succeeded':'POST_CONFIG', 'not_completed':'not_completed', 'paused':'PAUSED_DURING_ACTION', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'target_object_name':'target_object_name',
                                'semi_autonomous_mode':'semi_autonomous_mode',
                                'target_object_id':'target_object_id',
                                'target_object':'target_object',
                                'grasp_categorisation':'grasp_categorisation'})
             
            smach.StateMachine.add('POST_CONFIG', co_sm_post_conf,
                    transitions={'succeeded':'succeeded', 'paused':'PAUSED_DURING_POST_CONFIG', 'failed':'failed', 'preempted':'preempted', 'stopped':'stopped'},
                    remapping={'action_name':'action_name'})
            
            smach.StateMachine.add('PAUSED_DURING_PRE_CONFIG', state_checking_during_paused(),
                    transitions={'resume':'PRE_CONFIG','preempted':'preempted', 'stopped':'stopped'})
            
            smach.StateMachine.add('PAUSED_DURING_ACTION', state_checking_during_paused(),
                    transitions={'resume':'ACTION','preempted':'preempted', 'stopped':'stopped'})
            
            smach.StateMachine.add('PAUSED_DURING_POST_CONFIG', state_checking_during_paused(),
                    transitions={'resume':'POST_CONFIG','preempted':'preempted', 'stopped':'stopped'}) 