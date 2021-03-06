cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_find_ros_package(actionlib_msgs)
include(${actionlib_msgs_PACKAGE_PATH}/cmake/actionbuild.cmake)
genaction()

rosbuild_init()
rosbuild_add_boost_directories()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

rosbuild_add_executable(but_arm_manipulation_node src/but_arm_manipulation_node.cpp src/but_arm_manip_action.cpp src/but_arm_manip_collobj_methods.cpp src/but_arm_manip_services.cpp)
#rosbuild_link_boost(but_arm_manipulation_node thread)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

# BUT rviz display
set( DISPLAY_SOURCE_FILES src/but_display/but_arm_manipulation.cpp
                          src/but_display/but_cob_display.cpp
                          src/but_display/init.cpp )

set( BUT_DISPLAY_PROJECT_NAME but_cob_gui )
include_directories(include/but_display)
rosbuild_add_library( ${BUT_DISPLAY_PROJECT_NAME} ${DISPLAY_SOURCE_FILES} )

# Add wx widgets
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})
include_directories( ${wxWidgets_INCLUDE_DIRS} )

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)

#
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

# some checks of launch files
rosbuild_add_roslaunch_check(launch)
