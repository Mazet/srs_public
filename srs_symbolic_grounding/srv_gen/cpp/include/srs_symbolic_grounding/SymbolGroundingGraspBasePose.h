/* Auto-generated by genmsg_cpp for file /home/beisheng/git/care-o-bot/srs_public/srs_symbolic_grounding/srv/SymbolGroundingGraspBasePose.srv */
#ifndef SRS_SYMBOLIC_GROUNDING_SERVICE_SYMBOLGROUNDINGGRASPBASEPOSE_H
#define SRS_SYMBOLIC_GROUNDING_SERVICE_SYMBOLGROUNDINGGRASPBASEPOSE_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "ros/service_traits.h"

#include "geometry_msgs/Pose.h"
#include "srs_symbolic_grounding/SRSSpatialInfo.h"
#include "srs_symbolic_grounding/SRSSpatialInfo.h"


#include "geometry_msgs/Pose2D.h"

namespace srs_symbolic_grounding
{
template <class ContainerAllocator>
struct SymbolGroundingGraspBasePoseRequest_ {
  typedef SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> Type;

  SymbolGroundingGraspBasePoseRequest_()
  : target_obj_pose()
  , parent_obj_geometry()
  , furniture_geometry_list()
  {
  }

  SymbolGroundingGraspBasePoseRequest_(const ContainerAllocator& _alloc)
  : target_obj_pose(_alloc)
  , parent_obj_geometry(_alloc)
  , furniture_geometry_list(_alloc)
  {
  }

  typedef  ::geometry_msgs::Pose_<ContainerAllocator>  _target_obj_pose_type;
   ::geometry_msgs::Pose_<ContainerAllocator>  target_obj_pose;

  typedef  ::srs_symbolic_grounding::SRSSpatialInfo_<ContainerAllocator>  _parent_obj_geometry_type;
   ::srs_symbolic_grounding::SRSSpatialInfo_<ContainerAllocator>  parent_obj_geometry;

  typedef std::vector< ::srs_symbolic_grounding::SRSSpatialInfo_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::srs_symbolic_grounding::SRSSpatialInfo_<ContainerAllocator> >::other >  _furniture_geometry_list_type;
  std::vector< ::srs_symbolic_grounding::SRSSpatialInfo_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::srs_symbolic_grounding::SRSSpatialInfo_<ContainerAllocator> >::other >  furniture_geometry_list;


  ROS_DEPRECATED uint32_t get_furniture_geometry_list_size() const { return (uint32_t)furniture_geometry_list.size(); }
  ROS_DEPRECATED void set_furniture_geometry_list_size(uint32_t size) { furniture_geometry_list.resize((size_t)size); }
  ROS_DEPRECATED void get_furniture_geometry_list_vec(std::vector< ::srs_symbolic_grounding::SRSSpatialInfo_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::srs_symbolic_grounding::SRSSpatialInfo_<ContainerAllocator> >::other > & vec) const { vec = this->furniture_geometry_list; }
  ROS_DEPRECATED void set_furniture_geometry_list_vec(const std::vector< ::srs_symbolic_grounding::SRSSpatialInfo_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::srs_symbolic_grounding::SRSSpatialInfo_<ContainerAllocator> >::other > & vec) { this->furniture_geometry_list = vec; }
private:
  static const char* __s_getDataType_() { return "srs_symbolic_grounding/SymbolGroundingGraspBasePoseRequest"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "929217c873801a8d83a0ef0a0ff55374"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getServerMD5Sum_() { return "80365e2dd1e4f246fb4542bfaa7f0518"; }
public:
  ROS_DEPRECATED static const std::string __s_getServerMD5Sum() { return __s_getServerMD5Sum_(); }

  ROS_DEPRECATED const std::string __getServerMD5Sum() const { return __s_getServerMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "geometry_msgs/Pose target_obj_pose\n\
SRSSpatialInfo parent_obj_geometry\n\
SRSSpatialInfo[] furniture_geometry_list\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of postion and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
================================================================================\n\
MSG: srs_symbolic_grounding/SRSSpatialInfo\n\
# Point point\n\
# Orientation angles\n\
float32 l\n\
float32 w\n\
float32 h\n\
\n\
geometry_msgs/Pose pose\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, target_obj_pose);
    ros::serialization::serialize(stream, parent_obj_geometry);
    ros::serialization::serialize(stream, furniture_geometry_list);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, target_obj_pose);
    ros::serialization::deserialize(stream, parent_obj_geometry);
    ros::serialization::deserialize(stream, furniture_geometry_list);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(target_obj_pose);
    size += ros::serialization::serializationLength(parent_obj_geometry);
    size += ros::serialization::serializationLength(furniture_geometry_list);
    return size;
  }

  typedef boost::shared_ptr< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct SymbolGroundingGraspBasePoseRequest
typedef  ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<std::allocator<void> > SymbolGroundingGraspBasePoseRequest;

typedef boost::shared_ptr< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest> SymbolGroundingGraspBasePoseRequestPtr;
typedef boost::shared_ptr< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest const> SymbolGroundingGraspBasePoseRequestConstPtr;


template <class ContainerAllocator>
struct SymbolGroundingGraspBasePoseResponse_ {
  typedef SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> Type;

  SymbolGroundingGraspBasePoseResponse_()
  : obstacle_check(false)
  , reach(0.0)
  , grasp_base_pose()
  {
  }

  SymbolGroundingGraspBasePoseResponse_(const ContainerAllocator& _alloc)
  : obstacle_check(false)
  , reach(0.0)
  , grasp_base_pose(_alloc)
  {
  }

  typedef uint8_t _obstacle_check_type;
  uint8_t obstacle_check;

  typedef float _reach_type;
  float reach;

  typedef  ::geometry_msgs::Pose2D_<ContainerAllocator>  _grasp_base_pose_type;
   ::geometry_msgs::Pose2D_<ContainerAllocator>  grasp_base_pose;


private:
  static const char* __s_getDataType_() { return "srs_symbolic_grounding/SymbolGroundingGraspBasePoseResponse"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "1166b4429d4bb491f620326781fed922"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getServerMD5Sum_() { return "80365e2dd1e4f246fb4542bfaa7f0518"; }
public:
  ROS_DEPRECATED static const std::string __s_getServerMD5Sum() { return __s_getServerMD5Sum_(); }

  ROS_DEPRECATED const std::string __getServerMD5Sum() const { return __s_getServerMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "bool obstacle_check\n\
float32 reach\n\
geometry_msgs/Pose2D grasp_base_pose\n\
\n\
\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose2D\n\
# This expresses a position and orientation on a 2D manifold.\n\
\n\
float64 x\n\
float64 y\n\
float64 theta\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, obstacle_check);
    ros::serialization::serialize(stream, reach);
    ros::serialization::serialize(stream, grasp_base_pose);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, obstacle_check);
    ros::serialization::deserialize(stream, reach);
    ros::serialization::deserialize(stream, grasp_base_pose);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(obstacle_check);
    size += ros::serialization::serializationLength(reach);
    size += ros::serialization::serializationLength(grasp_base_pose);
    return size;
  }

  typedef boost::shared_ptr< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct SymbolGroundingGraspBasePoseResponse
typedef  ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<std::allocator<void> > SymbolGroundingGraspBasePoseResponse;

typedef boost::shared_ptr< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse> SymbolGroundingGraspBasePoseResponsePtr;
typedef boost::shared_ptr< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse const> SymbolGroundingGraspBasePoseResponseConstPtr;

struct SymbolGroundingGraspBasePose
{

typedef SymbolGroundingGraspBasePoseRequest Request;
typedef SymbolGroundingGraspBasePoseResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct SymbolGroundingGraspBasePose
} // namespace srs_symbolic_grounding

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "929217c873801a8d83a0ef0a0ff55374";
  }

  static const char* value(const  ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x929217c873801a8dULL;
  static const uint64_t static_value2 = 0x83a0ef0a0ff55374ULL;
};

template<class ContainerAllocator>
struct DataType< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "srs_symbolic_grounding/SymbolGroundingGraspBasePoseRequest";
  }

  static const char* value(const  ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "geometry_msgs/Pose target_obj_pose\n\
SRSSpatialInfo parent_obj_geometry\n\
SRSSpatialInfo[] furniture_geometry_list\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of postion and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
================================================================================\n\
MSG: srs_symbolic_grounding/SRSSpatialInfo\n\
# Point point\n\
# Orientation angles\n\
float32 l\n\
float32 w\n\
float32 h\n\
\n\
geometry_msgs/Pose pose\n\
\n\
";
  }

  static const char* value(const  ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "1166b4429d4bb491f620326781fed922";
  }

  static const char* value(const  ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x1166b4429d4bb491ULL;
  static const uint64_t static_value2 = 0xf620326781fed922ULL;
};

template<class ContainerAllocator>
struct DataType< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "srs_symbolic_grounding/SymbolGroundingGraspBasePoseResponse";
  }

  static const char* value(const  ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "bool obstacle_check\n\
float32 reach\n\
geometry_msgs/Pose2D grasp_base_pose\n\
\n\
\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose2D\n\
# This expresses a position and orientation on a 2D manifold.\n\
\n\
float64 x\n\
float64 y\n\
float64 theta\n\
";
  }

  static const char* value(const  ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.target_obj_pose);
    stream.next(m.parent_obj_geometry);
    stream.next(m.furniture_geometry_list);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct SymbolGroundingGraspBasePoseRequest_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.obstacle_check);
    stream.next(m.reach);
    stream.next(m.grasp_base_pose);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct SymbolGroundingGraspBasePoseResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<srs_symbolic_grounding::SymbolGroundingGraspBasePose> {
  static const char* value() 
  {
    return "80365e2dd1e4f246fb4542bfaa7f0518";
  }

  static const char* value(const srs_symbolic_grounding::SymbolGroundingGraspBasePose&) { return value(); } 
};

template<>
struct DataType<srs_symbolic_grounding::SymbolGroundingGraspBasePose> {
  static const char* value() 
  {
    return "srs_symbolic_grounding/SymbolGroundingGraspBasePose";
  }

  static const char* value(const srs_symbolic_grounding::SymbolGroundingGraspBasePose&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "80365e2dd1e4f246fb4542bfaa7f0518";
  }

  static const char* value(const srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "srs_symbolic_grounding/SymbolGroundingGraspBasePose";
  }

  static const char* value(const srs_symbolic_grounding::SymbolGroundingGraspBasePoseRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "80365e2dd1e4f246fb4542bfaa7f0518";
  }

  static const char* value(const srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "srs_symbolic_grounding/SymbolGroundingGraspBasePose";
  }

  static const char* value(const srs_symbolic_grounding::SymbolGroundingGraspBasePoseResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // SRS_SYMBOLIC_GROUNDING_SERVICE_SYMBOLGROUNDINGGRASPBASEPOSE_H

