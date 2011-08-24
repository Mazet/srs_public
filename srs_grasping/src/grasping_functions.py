#!/usr/bin/env python


import roslib; 
roslib.load_manifest('srs_grasping')
import rospy
import simple_script_server
import sys, time
import openravepy

from xml.dom import minidom
from tf.transformations import *

from trajectory_msgs.msg import *
from geometry_msgs.msg import *
from srs_grasping.msg import *


pi = math.pi
package_path = roslib.packages.get_pkg_dir('srs_grasping')


#################################################################################################
class GraspConfig(): ############################################################################
#################################################################################################

	def __init__(self, joint_values, GraspPose, G2, MinDist, Volume):
		self.joint_values = joint_values
		self.GraspPose = GraspPose	# Para poder mostrarlo en OR.
		self.G2 = G2			# Configuracion de la mano relativa al palm link.
		self.MinDist = MinDist
		self.Volume = Volume;

	
	def __cmp__(self,other):
		if self.Volume > other.Volume:
			return 1
		elif self.Volume < other.Volume:
			return -1
		else:
			return 0


	###### [ GRASP FILTERS ] ##################################################
	def Z(self,other):
		s = self.G2.pose.position.z
		o = other.G2.pose.position.z

		if (s) >  (o):
			return -1
		elif  (s) <  (o):
			return 1;
		else:
			return 0;


	def _Z(self,other):
		s = self.G2.pose.position.z
		o = other.G2.pose.position.z

		if (s) > (o):
			return 1
		elif  (s) <  (o):
			return -1;
		else:
			return 0;


	def X(self,other):
		s = self.G2.pose.position.x
		o = other.G2.pose.position.x

		if (s) > (o):
			return 1
		elif  (s) <  (o):
			return -1;
		else:
			return 0;

	def _X(self,other):
		s = self.G2.pose.position.x
		o = other.G2.pose.position.x

		if (s) > (o):
			return -1
		elif  (s) <  (o):
			return 1;
		else:
			return 0;


	def Y(self,other):
		s = self.G2.pose.position.y
		o = other.G2.pose.position.y

		if (s) > (o):
			return 1
		elif  (s) <  (o):
			return -1;
		else:
			return 0;

	def _Y(self,other):
		s = self.G2.pose.position.y
		o = other.G2.pose.position.y

		if (s) > (o):
			return -1
		elif  (s) <  (o):
			return 1;
		else:
			return 0;

	###### [/GRASP FILTERS ] ##################################################




############################## GRASPING FUNCTIONS ####################################################################
# --------------------------------------------------------------------------------------------------------------------
# XML file generator.
# --------------------------------------------------------------------------------------------------------------------
def generateFile(all_grasps, targetName, gmodel, env):

	
	# ------------------------ 
	# targetName.xml
	# ------------------------ 
	"""
	img_name = raw_input("Put the image name for this configuration: \n");
	try:
		fmain = open(package_path+"/DB/"+targetName+".xml",'r+');

		xmldoc = minidom.parse(package_path+"/DB/"+targetName+".xml");
		confs = (((xmldoc.firstChild)).getElementsByTagName('configuration')).length;
		lineas = fmain.readlines();
		lineas[len(lineas)-1]="<FileName id=\""+img_name+"\">\n"+"<configuration>"+str(confs)+"</configuration>\n"+"</FileName>\n"
		lineas.append("</"+targetName+">\n");

		fmain = open(package_path+"/DB/"+targetName+".xml",'w');
		for i in range(0, len(lineas)):
			fmain.write(str(lineas[i]));

	except:
		fmain = open(package_path+"/DB/"+targetName+".xml",'w');
		fmain.write("<?xml version=\"1.0\" ?>\n");
		fmain.write("<"+targetName+">\n");
		fmain.write("<FileName id=\"" + img_name + "\">\n");
		fmain.write("<configuration>0</configuration>\n");
		fmain.write("</FileName>\n");
		fmain.write("</"+targetName+">\n");
		
	fmain.close()
	print "Created entry in the file <%s.xml>" %targetName;
	"""


	
	# ------------------------ 
	# <targetName_all_grasps>.xml
	# ------------------------ 

	f_name = targetName + "_all_grasps.xml"



	try:
		f = open(package_path+'/DB/'+f_name,'r')
		#addConfiguration(f_name, gmodel)
		print "There are a file with the same name."
		sys.exit()
	except:
		f = open(package_path+'/DB/'+f_name,'w')
		f.write("<?xml version=\"1.0\" ?>\n");
		f.write("<GraspList>\n");
		f.write("<ObjectID>"+targetName+"</ObjectID>\n");
		f.write("<HAND>SDH</HAND>\n");
		f.write("<joint_names>[sdh_knuckle_joint, sdh_finger_12_joint, sdh_finger_13_joint, sdh_finger_22_joint, sdh_finger_23_joint, sdh_thumb_2_joint, sdh_thumb_3_joint]</joint_names>\n");
		f.write("<reference_link>sdh_palm_link</reference_link>\n")
		f.write("<configuration id=\"0\">\n")


		cont = 0
		print "Adding grasps to the new XML file..."
		for i in range(0, len(gmodel.grasps)):
			print str(i+1)+"/"+str(len(gmodel.grasps))
			try:
	 			contacts,finalconfig,mindist,volume = gmodel.testGrasp(grasp=gmodel.grasps[i],translate=True,forceclosure=True)
			   	f.write("<Grasp Index=\""+str(cont)+"\">\n")


				value = (finalconfig[0])	#care-o-bot3.zae
				value = value[7:14]
				value = OR_to_ROS(value);
				f.write("<joint_values>"+str(value)+"</joint_values>\n");

			   	f.write("<GraspPose>\n");
				# [Necesario para simularlo en OR]
				t = translation_from_matrix(finalconfig[1])
				#q = quaternion_from_matrix(finalconfig[1])
				e = euler_from_matrix(finalconfig[1], axes='sxyz')
				f.write("<Translation>["+str(t[0])+", "+str(t[1])+", "+str(t[2])+"]</Translation>\n");
				#f.write("<Rotation>["+str(q[0])+", "+str(q[1])+", "+str(q[2])+", "+str(q[3])+"]</Rotation>\n");
				f.write("<Rotation>["+str(e[0])+", "+str(e[1])+", "+str(e[2])+"]</Rotation>\n");
				# [/Necesario para simularlo en OR]

				# [Valores relativos al palm_link]
				env.GetRobots()[0].GetController().Reset(0)
				env.GetRobots()[0].SetDOFValues(finalconfig[0])
				env.GetRobots()[0].SetTransform(finalconfig[1])
				env.UpdatePublishedBodies()
				conf = ((env.GetRobots()[0]).GetManipulator("arm")).GetEndEffectorTransform()

				index = ((env.GetRobots()[0]).GetLink("sdh_palm_link")).GetIndex()
				t = translation_from_matrix((((env.GetRobots()[0]).GetLinkTransformations())[index]))
				#q = quaternion_from_matrix((((env.GetRobots()[0]).GetLinkTransformations())[index]))
				e = euler_from_matrix((((env.GetRobots()[0]).GetLinkTransformations())[index]), axes='sxyz')

				f.write("<GT>["+str(t[0])+", "+str(t[1])+", "+str(t[2])+"]</GT>\n");
				#f.write("<GR>["+str(q[0])+", "+str(q[1])+", "+str(q[2])+", "+str(q[3])+"]</GR>\n");
				f.write("<GR>["+str(e[0])+", "+str(e[1])+", "+str(e[2])+"]</GR>\n");
				# [/Valores relativos al palm_link]


			   	f.write("</GraspPose>\n")


			   	f.write("<MinDist>"+str(mindist)+"</MinDist>\n")
			   	f.write("<Volume>"+str(volume)+"</Volume>\n")

			   	f.write("</Grasp>\n")

				cont += 1
			
			except:
				continue


		f.write("<NumberOfGrasps>"+str(cont)+"</NumberOfGrasps>\n");
		f.write("</configuration>\n");
		f.write("</GraspList>");
		f.close()
		print "%d grasps have been added to the XML file..." %cont;



# --------------------------------------------------------------------------------------------------------------------
# XML file depurator. (obsolet)
# --------------------------------------------------------------------------------------------------------------------
def generaFicheroDepurado(targetName, grasps):

	# ------------------------ 
	# <targetName_D>.xml
	# ------------------------ 

	f_name = targetName + "_D.xml"



	try:
		f = open(package_path+'/DB/'+f_name,'r')
		addDepurateConfiguration(f_name, grasps)
	except:
		f = open(package_path+'/DB/'+f_name,'w')
		f.write("<?xml version=\"1.0\" ?>\n");
		f.write("<GraspList>\n");
		f.write("<ObjectID>"+targetName+"</ObjectID>\n");
		f.write("<HAND>SDH</HAND>\n");
		f.write("<joint_names>[sdh_knuckle_joint, sdh_finger_12_joint, sdh_finger_13_joint, sdh_finger_22_joint, sdh_finger_23_joint, sdh_thumb_2_joint, sdh_thumb_3_joint]</joint_names>\n");
		f.write("<reference_link>sdh_palm_link</reference_link>\n")
		f.write("<configuration id=\"0\">\n")


		cont = 0
		print "Adding grasps to the NEW depurated file..."
		for i in range(0, len(grasps)):
			try:
			   	f.write("<Grasp Index=\""+str(i)+"\">\n")

				f.write("<joint_values>"+grasps[i].joint_values+"</joint_values>\n");

			   	f.write("<GraspPose>\n");

				tr = []
				tr.append(grasps[i].GraspPose.pose.position.x)
				tr.append(grasps[i].GraspPose.pose.position.y)
				tr.append(grasps[i].GraspPose.pose.position.z)

				rt = []
				rt.append(grasps[i].GraspPose.pose.orientation.x)
				rt.append(grasps[i].GraspPose.pose.orientation.y)
				rt.append(grasps[i].GraspPose.pose.orientation.z)
				rt.append(grasps[i].GraspPose.pose.orientation.w)

				f.write("<Translation>"+str(tr)+"</Translation>\n");
				f.write("<Rotation>"+str(rt)+"</Rotation>\n");
			   	f.write("</GraspPose>\n")

			   	f.write("<MinDist>"+str(grasps[i].MinDist)+"</MinDist>\n")
			   	f.write("<Volume>"+str(grasps[i].Volume)+"</Volume>\n")

			   	f.write("</Grasp>\n")

				cont += 1
			
			except:
				continue




		f.write("<NumberOfGrasps>"+str(cont)+"</NumberOfGrasps>\n");
		f.write("</configuration>\n");
		f.write("</GraspList>");
		f.close()
		print "%d have been added to the depurated file..." %cont;






# --------------------------------------------------------------------------------------------------------------------
# OpenRAVE/Gazebo to Gazebo/OpenRAVE transformation joint values. (obsolet)
# --------------------------------------------------------------------------------------------------------------------
def OR_to_ROS(OR):
	"""
	pi = math.pi
	ROS = OR;
	#ROS = [[OR[0]+pi/3, OR[3]-pi/2,OR[4] ,OR[1]-pi/2,OR[2], OR[5]-pi/2, OR[6]]]
	ROS[7] = OR[7]+pi/3 
	ROS[8] = OR[10]-pi/2
	ROS[9] = OR[11]
	ROS[10] = OR[8]-pi/2
	ROS[11] = OR[9]
	ROS[12] = OR[12]-pi/2
	ROS[13] = OR[13]
	return [ROS]
	"""

	return [OR[2], OR[3], OR[4], OR[0], OR[1], OR[5], OR[6]]

def ROS_to_OR(OR):
	"""
	OR = eval(OR)
	for i in range (0,len(OR)):
		OR[i] = float(OR[i])
	pi = math.pi
	ROS = OR;
	#ROS = [OR[0]-pi/3, OR[3]+pi/2, OR[4], OR[1]+pi/2, OR[2], OR[5]+pi/2, OR[6]]

	ROS[7] = OR[7]-pi/3 
	ROS[8] = OR[10]+pi/2
	ROS[9] = OR[11]
	ROS[10] = OR[8]+pi/2
	ROS[11] = OR[9]
	ROS[12] = OR[12]+pi/2
	ROS[13] = OR[13]
	return ROS
	"""

	return [OR[3], OR[4], OR[0], OR[1], OR[2], OR[5], OR[6]]

# --------------------------------------------------------------------------------------------------------------------
# String list to float list converters
# --------------------------------------------------------------------------------------------------------------------
def format(OR):

	OR = eval(OR)
	for i in range (0,len(OR)):
		OR[i] = float(OR[i])

	return OR


# Needed to show the configurations in OR
def format2(OR):
	res = [0 for i in range(28)]	

	OR = ROS_to_OR(eval(OR))

	for i in range (0,len(OR)):
		res[i+7] = float(OR[i])

	return res


# --------------------------------------------------------------------------------------------------------------------
# Get grasps
# --------------------------------------------------------------------------------------------------------------------
def getGrasps(file_name, pose=None, num=0, msg=False):

	xmldoc = minidom.parse(file_name)  
	padres = ((xmldoc.firstChild)).getElementsByTagName('configuration');

	res = []
	for j in range(0, len(padres)):
		hijos = (((xmldoc.firstChild)).getElementsByTagName('configuration'))[j].getElementsByTagName('Grasp');
		grasps = []
		for i in range(0,len(hijos)):

			joint_values = ((hijos[i].getElementsByTagName('joint_values'))[0]).firstChild.nodeValue;

			aux = ((hijos[i].getElementsByTagName('GraspPose'))[0]);
			Translation = eval((aux.getElementsByTagName('Translation')[0]).firstChild.nodeValue);
			Rotation = eval((aux.getElementsByTagName('Rotation')[0]).firstChild.nodeValue);
			g = PoseStamped()
			g.pose.position.x = float(Translation[0])
			g.pose.position.y = float(Translation[1])
			g.pose.position.z = float(Translation[2])
			Rotation =  quaternion_from_euler(Rotation[0], Rotation[1], Rotation[2], axes='sxyz')
			g.pose.orientation.x = float(Rotation[0])
			g.pose.orientation.y = float(Rotation[1])
			g.pose.orientation.z = float(Rotation[2])
			g.pose.orientation.w = float(Rotation[3])


			GT = eval((aux.getElementsByTagName('GT')[0]).firstChild.nodeValue);
			GR = eval((aux.getElementsByTagName('GR')[0]).firstChild.nodeValue);
			g2 = PoseStamped()
			g2.pose.position.x = float(GT[0])
			g2.pose.position.y = float(GT[1])
			g2.pose.position.z = float(GT[2])
			GR =  quaternion_from_euler(GR[0], GR[1], GR[2], axes='sxyz')
			g2.pose.orientation.x = float(GR[0])
			g2.pose.orientation.y = float(GR[1])
			g2.pose.orientation.z = float(GR[2])
			g2.pose.orientation.w = float(GR[3])


			

			MinDist = ((hijos[i].getElementsByTagName('MinDist'))[0]).firstChild.nodeValue;
			Volume = ((hijos[i].getElementsByTagName('Volume'))[0]).firstChild.nodeValue;



			grasps.append(GraspConfig(joint_values, g, g2, MinDist, Volume));




		if pose=="Z":
			grasps.sort(GraspConfig.Z)
		elif pose=="_Z":	
			grasps.sort(GraspConfig._Z)
		elif pose=="X":	
			grasps.sort(GraspConfig.X)
		elif pose=="_X":	
			grasps.sort(GraspConfig._X)
		elif pose=="Y":	
			grasps.sort(GraspConfig.Y)
		elif pose=="_Y":	
			grasps.sort(GraspConfig._Y)
		else:
			grasps.sort()
		
		if num==0:
			num=len(grasps)
		

		res.append(grasp_filter(grasps[0:num]));
		#res.append(grasps[0:num])

	if msg==False:
		return res;					#returns a graspconfig list (openrave viewer)
	else:
		return 	graspConfig_to_MSG(res);		#returns a msg list (server/service)







# --------------------------------------------------------------------------------------------------------------------
# Shows the grasps in OpenRAVE
# --------------------------------------------------------------------------------------------------------------------
def showOR(env, grasps, delay=0.5, depurador=False):
	g = []

	env.SetViewer('qtcoin')
	time.sleep(1.0)

	if depurador==True:
		print "Write <save> to save the current configuration and <end> to finish."

	#with gmodel.GripperVisibility(((env.GetRobots()[0]).GetManipulator("arm"))):
	with openravepy.databases.grasping.GraspingModel.GripperVisibility(((env.GetRobots()[0]).GetManipulator("arm"))):
		for i in range(0,len(grasps)):

			print 'grasp %d/%d'%(i,len(grasps))
			env.GetRobots()[0].GetController().Reset(0)
			env.GetRobots()[0].SetDOFValues(format2(grasps[i].joint_values))
			env.GetRobots()[0].SetTransform(matrix_from_graspPose(grasps[i].GraspPose))
			env.UpdatePublishedBodies()

			x1 = eval(grasps[i].joint_values)[1]
			x2 = eval(grasps[i].joint_values)[3]
			x3 = eval(grasps[i].joint_values)[5]

			if abs(x1)>=(pi/2.4) or abs(x2)>=(pi/2.4) or abs(x3)>=(pi/2.4):
				print "AAAAAAAAATENCION!"

			print "--------------------"
				
			if depurador==True:
				res = raw_input("?: " )
				if res=="save":
					g.append(grasps[i]);
				if res=="end":
					return g;
			else:
				if delay is None:
					raw_input('Next config.')
				elif delay > 0:
					time.sleep(delay)

	return g;


# --------------------------------------------------------------------------------------------------------------------
# Returns a homogeneus matrix.
# --------------------------------------------------------------------------------------------------------------------
def matrix_from_graspPose(gp):

	q = []
	q.append(gp.pose.orientation.x)
	q.append(gp.pose.orientation.y)
	q.append(gp.pose.orientation.z)
	q.append(gp.pose.orientation.w
)
	e = euler_from_quaternion(q, axes='sxyz')

	matrix = euler_matrix(e[0],e[1],e[2] ,axes='sxyz')
	matrix[0][3] = gp.pose.position.x
	matrix[1][3] = gp.pose.position.y
	matrix[2][3] = gp.pose.position.z

	return matrix;
	

# --------------------------------------------------------------------------------------------------------------------
# Add a new configuration to the XML file. (obsolet)
# --------------------------------------------------------------------------------------------------------------------
def addConfiguration(file_name, gmodel):

	# ------------------------ 
	# <targetName_all_grasps>.xml
	# ------------------------ 


	f = open(package_path+'/DB/'+file_name,'r+')
	lines = f.readlines();
	f = open(package_path+'/DB/'+file_name,'w')
	xmldoc = minidom.parse(package_path+"/DB/"+file_name[0:-15]+".xml");
	confs = (((xmldoc.firstChild)).getElementsByTagName('configuration')).length;
	lines[len(lines)-1] = "<configuration id=\""+str(confs-1)+"\">\n"
	for i in range(0, len(lines)):
		f.write(str(lines[i]));
	
	cont = 0
	print "Adding a new configuration to the old XML file..."
	for i in range(0, len(gmodel.grasps)):
		try:
 			contacts,finalconfig,mindist,volume = gmodel.testGrasp(grasp=gmodel.grasps[i],translate=True,forceclosure=True)
		   	f.write("<Grasp Index=\""+str(cont)+"\">\n")

			value = (finalconfig[0])	#care-o-bot3.zae
			value = value[7:14]
			value = OR_to_ROS(value);
			f.write("<joint_values>"+str(value)+"</joint_values>\n");

		   	f.write("<GraspPose>\n");
			t = translation_from_matrix(finalconfig[1])
			f.write("<Translation>["+str(t[0])+", "+str(t[1])+", "+str(t[2])+"]</Translation>\n");
			q = quaternion_from_matrix(finalconfig[1])
			f.write("<Rotation>["+str(q[0])+", "+str(q[1])+", "+str(q[2])+", "+str(q[3])+"]</Rotation>\n");
		   	f.write("</GraspPose>\n")

		   	f.write("<MinDist>"+str(mindist)+"</MinDist>\n")
		   	f.write("<Volume>"+str(volume)+"</Volume>\n")

		   	f.write("</Grasp>\n")

			cont += 1
			
		except:
			continue




	f.write("<NumberOfGrasps>"+str(cont)+"</NumberOfGrasps>\n");
	f.write("</configuration>\n");
	f.write("</GraspList>");
	f.close()
	print "%d have been added to the XML file..." %cont;



# --------------------------------------------------------------------------------------------------------------------
# Add a new configuration to the XML depurated file. (obsolet)
# --------------------------------------------------------------------------------------------------------------------
def addDepurateConfiguration(file_name, grasps):

	# ------------------------ 
	# <targetName_D>.xml
	# ------------------------ 


	f = open(package_path+'/DB/'+file_name,'r+')
	lines = f.readlines();
	f = open(package_path+'/DB/'+file_name,'w')
	xmldoc = minidom.parse(package_path+"/DB/"+file_name[0:-6]+".xml");
	confs = (((xmldoc.firstChild)).getElementsByTagName('configuration')).length;
	lines[len(lines)-1] = "<configuration id=\""+str(confs-1)+"\">\n"
	for i in range(0, len(lines)):
		f.write(str(lines[i]));
	
	cont = 0
	print "Adding a new configuration to the old depurated XML file..."
	for i in range(0, len(grasps)):
		try:
		   	f.write("<Grasp Index=\""+str(cont)+"\">\n")


			f.write("<joint_values>"+grasps[i].joint_values+"</joint_values>\n");

		   	f.write("<GraspPose>\n");
			f.write("<Translation>"+grasps[i].GraspPose.pose.position+"</Translation>\n");
			f.write("<Rotation>"+grasps[i].GraspPose.pose.orientation+"</Rotation>\n");
		   	f.write("</GraspPose>\n")

		   	f.write("<MinDist>"+grasps[i].MinDist+"</MinDist>\n")
		   	f.write("<Volume>"+grasps[i].Volume+"</Volume>\n")

		   	f.write("</Grasp>\n")

			cont += 1
			
		except:
			continue




	f.write("<NumberOfGrasps>"+str(cont)+"</NumberOfGrasps>\n");
	f.write("</configuration>\n");
	f.write("</GraspList>");
	f.close()
	print "%d have been added to the XML depurated file..." %cont;



# -------------------------------------------------------------------------------------------------------------------
# Grasp function
# -------------------------------------------------------------------------------------------------------------------
def graspIt(objectID, poseID):

	file_name = package_path+'/DB/'+objectID+"_all_grasps.xml"

	GRASPS = getGrasps(file_name, poseID)
	grasps = GRASPS[0];

	
	rospy.init_node("grasping_node")
	sss = simple_script_server.simple_script_server()

	
	fail = False;
	for i in range(0,len(grasps)):
		values = eval(grasps[i].joint_values)

		for j in range(0,len(values)):
			values[j] = float(values[j]);
		
			if j==0:
				if values[j]<0:
					values[j] = 0;

		res = sss.move("sdh", [values])
		if res.get_error_code() == 0:
			print "Grasp valido."
			break;
		else:
			print "Grasp no valido."


# -------------------------------------------------------------------------------------------------------------------
# Convert to msg format.
# -------------------------------------------------------------------------------------------------------------------
def graspConfig_to_MSG(res):
	aux = []
	res = res[0]
	for i in range(0,len(res)):
		aux.append(grasp(str(res[i].joint_values), res[i].G2, float(res[i].MinDist), float(res[i].Volume)));

	return [aux]


# -------------------------------------------------------------------------------------------------------------------
# Remove grasps in wich the fingers are in a extrange position.
# -------------------------------------------------------------------------------------------------------------------
def grasp_filter(g):
	grasps = []
	for i in range(0,len(g)):
		j = eval(g[i].joint_values)
		if abs(j[1])<=pi/2.75 and abs(j[3])<=pi/2.75 and abs(j[5])<=pi/2.45:
			grasps.append(g[i])

	return grasps


