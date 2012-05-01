"""autogenerated by genmsg_py from SymbolGroundingScanBasePoseRequest.msg. Do not edit."""
import roslib.message
import struct

import geometry_msgs.msg
import srs_symbolic_grounding.msg

class SymbolGroundingScanBasePoseRequest(roslib.message.Message):
  _md5sum = "23cc208c15dce6f450656fc4c209b68c"
  _type = "srs_symbolic_grounding/SymbolGroundingScanBasePoseRequest"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """SRSFurnitureGeometry parent_obj_geometry
SRSFurnitureGeometry[] furniture_geometry_list

================================================================================
MSG: srs_symbolic_grounding/SRSFurnitureGeometry
# Point point
# Orientation angles
float32 l
float32 w
float32 h

geometry_msgs/Pose pose

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of postion and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

"""
  __slots__ = ['parent_obj_geometry','furniture_geometry_list']
  _slot_types = ['srs_symbolic_grounding/SRSFurnitureGeometry','srs_symbolic_grounding/SRSFurnitureGeometry[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.
    
    The available fields are:
       parent_obj_geometry,furniture_geometry_list
    
    @param args: complete set of field values, in .msg order
    @param kwds: use keyword arguments corresponding to message field names
    to set specific fields. 
    """
    if args or kwds:
      super(SymbolGroundingScanBasePoseRequest, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.parent_obj_geometry is None:
        self.parent_obj_geometry = srs_symbolic_grounding.msg.SRSFurnitureGeometry()
      if self.furniture_geometry_list is None:
        self.furniture_geometry_list = []
    else:
      self.parent_obj_geometry = srs_symbolic_grounding.msg.SRSFurnitureGeometry()
      self.furniture_geometry_list = []

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    @param buff: buffer
    @type  buff: StringIO
    """
    try:
      _x = self
      buff.write(_struct_3f7d.pack(_x.parent_obj_geometry.l, _x.parent_obj_geometry.w, _x.parent_obj_geometry.h, _x.parent_obj_geometry.pose.position.x, _x.parent_obj_geometry.pose.position.y, _x.parent_obj_geometry.pose.position.z, _x.parent_obj_geometry.pose.orientation.x, _x.parent_obj_geometry.pose.orientation.y, _x.parent_obj_geometry.pose.orientation.z, _x.parent_obj_geometry.pose.orientation.w))
      length = len(self.furniture_geometry_list)
      buff.write(_struct_I.pack(length))
      for val1 in self.furniture_geometry_list:
        _x = val1
        buff.write(_struct_3f.pack(_x.l, _x.w, _x.h))
        _v1 = val1.pose
        _v2 = _v1.position
        _x = _v2
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
        _v3 = _v1.orientation
        _x = _v3
        buff.write(_struct_4d.pack(_x.x, _x.y, _x.z, _x.w))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    @param str: byte array of serialized message
    @type  str: str
    """
    try:
      if self.parent_obj_geometry is None:
        self.parent_obj_geometry = srs_symbolic_grounding.msg.SRSFurnitureGeometry()
      end = 0
      _x = self
      start = end
      end += 68
      (_x.parent_obj_geometry.l, _x.parent_obj_geometry.w, _x.parent_obj_geometry.h, _x.parent_obj_geometry.pose.position.x, _x.parent_obj_geometry.pose.position.y, _x.parent_obj_geometry.pose.position.z, _x.parent_obj_geometry.pose.orientation.x, _x.parent_obj_geometry.pose.orientation.y, _x.parent_obj_geometry.pose.orientation.z, _x.parent_obj_geometry.pose.orientation.w,) = _struct_3f7d.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.furniture_geometry_list = []
      for i in range(0, length):
        val1 = srs_symbolic_grounding.msg.SRSFurnitureGeometry()
        _x = val1
        start = end
        end += 12
        (_x.l, _x.w, _x.h,) = _struct_3f.unpack(str[start:end])
        _v4 = val1.pose
        _v5 = _v4.position
        _x = _v5
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        _v6 = _v4.orientation
        _x = _v6
        start = end
        end += 32
        (_x.x, _x.y, _x.z, _x.w,) = _struct_4d.unpack(str[start:end])
        self.furniture_geometry_list.append(val1)
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    @param buff: buffer
    @type  buff: StringIO
    @param numpy: numpy python module
    @type  numpy module
    """
    try:
      _x = self
      buff.write(_struct_3f7d.pack(_x.parent_obj_geometry.l, _x.parent_obj_geometry.w, _x.parent_obj_geometry.h, _x.parent_obj_geometry.pose.position.x, _x.parent_obj_geometry.pose.position.y, _x.parent_obj_geometry.pose.position.z, _x.parent_obj_geometry.pose.orientation.x, _x.parent_obj_geometry.pose.orientation.y, _x.parent_obj_geometry.pose.orientation.z, _x.parent_obj_geometry.pose.orientation.w))
      length = len(self.furniture_geometry_list)
      buff.write(_struct_I.pack(length))
      for val1 in self.furniture_geometry_list:
        _x = val1
        buff.write(_struct_3f.pack(_x.l, _x.w, _x.h))
        _v7 = val1.pose
        _v8 = _v7.position
        _x = _v8
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
        _v9 = _v7.orientation
        _x = _v9
        buff.write(_struct_4d.pack(_x.x, _x.y, _x.z, _x.w))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    @param str: byte array of serialized message
    @type  str: str
    @param numpy: numpy python module
    @type  numpy: module
    """
    try:
      if self.parent_obj_geometry is None:
        self.parent_obj_geometry = srs_symbolic_grounding.msg.SRSFurnitureGeometry()
      end = 0
      _x = self
      start = end
      end += 68
      (_x.parent_obj_geometry.l, _x.parent_obj_geometry.w, _x.parent_obj_geometry.h, _x.parent_obj_geometry.pose.position.x, _x.parent_obj_geometry.pose.position.y, _x.parent_obj_geometry.pose.position.z, _x.parent_obj_geometry.pose.orientation.x, _x.parent_obj_geometry.pose.orientation.y, _x.parent_obj_geometry.pose.orientation.z, _x.parent_obj_geometry.pose.orientation.w,) = _struct_3f7d.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.furniture_geometry_list = []
      for i in range(0, length):
        val1 = srs_symbolic_grounding.msg.SRSFurnitureGeometry()
        _x = val1
        start = end
        end += 12
        (_x.l, _x.w, _x.h,) = _struct_3f.unpack(str[start:end])
        _v10 = val1.pose
        _v11 = _v10.position
        _x = _v11
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        _v12 = _v10.orientation
        _x = _v12
        start = end
        end += 32
        (_x.x, _x.y, _x.z, _x.w,) = _struct_4d.unpack(str[start:end])
        self.furniture_geometry_list.append(val1)
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

_struct_I = roslib.message.struct_I
_struct_4d = struct.Struct("<4d")
_struct_3f = struct.Struct("<3f")
_struct_3f7d = struct.Struct("<3f7d")
_struct_3d = struct.Struct("<3d")
"""autogenerated by genmsg_py from SymbolGroundingScanBasePoseResponse.msg. Do not edit."""
import roslib.message
import struct

import geometry_msgs.msg

class SymbolGroundingScanBasePoseResponse(roslib.message.Message):
  _md5sum = "66b4de75c1cdba6b484a2621de9dc0d6"
  _type = "srs_symbolic_grounding/SymbolGroundingScanBasePoseResponse"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """geometry_msgs/Pose2D[] scan_base_pose_list





================================================================================
MSG: geometry_msgs/Pose2D
# This expresses a position and orientation on a 2D manifold.

float64 x
float64 y
float64 theta
"""
  __slots__ = ['scan_base_pose_list']
  _slot_types = ['geometry_msgs/Pose2D[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.
    
    The available fields are:
       scan_base_pose_list
    
    @param args: complete set of field values, in .msg order
    @param kwds: use keyword arguments corresponding to message field names
    to set specific fields. 
    """
    if args or kwds:
      super(SymbolGroundingScanBasePoseResponse, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.scan_base_pose_list is None:
        self.scan_base_pose_list = []
    else:
      self.scan_base_pose_list = []

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    @param buff: buffer
    @type  buff: StringIO
    """
    try:
      length = len(self.scan_base_pose_list)
      buff.write(_struct_I.pack(length))
      for val1 in self.scan_base_pose_list:
        _x = val1
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.theta))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    @param str: byte array of serialized message
    @type  str: str
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.scan_base_pose_list = []
      for i in range(0, length):
        val1 = geometry_msgs.msg.Pose2D()
        _x = val1
        start = end
        end += 24
        (_x.x, _x.y, _x.theta,) = _struct_3d.unpack(str[start:end])
        self.scan_base_pose_list.append(val1)
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    @param buff: buffer
    @type  buff: StringIO
    @param numpy: numpy python module
    @type  numpy module
    """
    try:
      length = len(self.scan_base_pose_list)
      buff.write(_struct_I.pack(length))
      for val1 in self.scan_base_pose_list:
        _x = val1
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.theta))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    @param str: byte array of serialized message
    @type  str: str
    @param numpy: numpy python module
    @type  numpy: module
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.scan_base_pose_list = []
      for i in range(0, length):
        val1 = geometry_msgs.msg.Pose2D()
        _x = val1
        start = end
        end += 24
        (_x.x, _x.y, _x.theta,) = _struct_3d.unpack(str[start:end])
        self.scan_base_pose_list.append(val1)
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

_struct_I = roslib.message.struct_I
_struct_3d = struct.Struct("<3d")
class SymbolGroundingScanBasePose(roslib.message.ServiceDefinition):
  _type          = 'srs_symbolic_grounding/SymbolGroundingScanBasePose'
  _md5sum = '5b734f5eb1ee3323ec23158f8e5349f6'
  _request_class  = SymbolGroundingScanBasePoseRequest
  _response_class = SymbolGroundingScanBasePoseResponse
