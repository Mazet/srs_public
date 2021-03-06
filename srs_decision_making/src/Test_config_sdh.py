
from srs_monitoring_statemachines import *
from robot_configuration import *
import roslib; roslib.load_manifest('SRS_reward_function')
import rospy
from SRS_reward_function.srv import *
from geometry_msgs.msg import *
from pr2_controllers_msgs.msg import *
flag='true'


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
        
#def get_head_state(msg):
#    global head_pos
#    head_pos = list(msg.desired.positions)


def my_movement(action_name, action_stage, msg):
    global current_task_info, arm_pos, head_pos
    len_step_info = len(current_task_info.last_step_info)
    result_action = current_task_info.last_step_info[len_step_info - 1].outcome
          
    sdh_state = rospy.Subscriber("/sdh_controller/state", JointTrajectoryControllerState, get_sdh_state);
    #head_state = rospy.Subscriber("/head_controller/state", JointTrajectoryControllerState, get_head_state);
    
    rospy.wait_for_service('rewardserver',10)
    try:
        reward = rospy.ServiceProxy('rewardserver', rewardsrv)
        rospy.loginfo("client")
        
        reqsrv=rewardsrvRequest()
        reqsrv.action_name=action_name
        reqsrv.action_stage=action_stage   
        
        resp = reward(reqsrv)     
 #       """
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
#        """
  
#        # headstate define only by the name      
#        headstate=resp.headstate
#        # headstate define by the coordinates
#        if headstate =='front':
#            headstate = [[-3.1415926]]
#        if headstate =='back':
#            headstate = [[0.0]]
#        # threshold to define if the robot need to move or not
##        print headstate
##        print '*********************************************************'
##        print head_pos
##        print '*******************************'
##        print head_pos[0] - headstate[0][0]
#        if -0.00001 < head_pos[0] - headstate[0][0] > 0.00001 :
#            sss.move("head",headstate)
                 
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e
                   
################################################################################################

def robot_configuration(parent, action_name, action_stage, msg):
    
    global current_task_info
    global component_list
    global robot_config
    global robot_config_need_no_action
    
    handles = list()

################################################################################################

    my_movement(action_name, action_stage, msg)

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
        return robot_configuration(self, userdata.action_name, 'pre-config','')
    
        
class post_conf(smach.State):
    def __init__(self):
        smach.State.__init__(self , outcomes=['succeeded', 'failed', 'preempted'], input_keys=['action_name'])
    
    def execute (self, userdata):
        return robot_configuration(self, userdata.action_name, 'post-config','')


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