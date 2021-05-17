# Project 4: Map My World
In this project I have created a 2D occupancy grid and 3D octomap from a simulated environment using my own robot with the RTAB-Map package.

RTAB-Map (Real-Time Appearance-Based Mapping) is a popular solution for SLAM to develop robots that can map environments in 3D. RTAB-Map has good speed and memory management, and it provides custom developed tools for information analysis

## The project flow will be as follows:
1. Develop my own package to interface with the rtabmap_ros package.
2. Build upon my localization project to make the necessary changes to interface the robot with RTAB-Map. An example of this is the addition of an RGB-D camera.
3. Ensure that all files are in the appropriate places, all links are properly connected, naming is properly setup and topics are correctly mapped. Furthermore you will need to generate the appropriate launch files to launch the robot and map its surrounding environment.
4. When robot is launched I will teleop around the room to generate a proper map of the environment.

## Procedure which was followed to build the project
1. creating project workspace
```
mkdir src
cd src
catkin_init_workspace
cd ../
catkin_make
source devel/setup.bash
```
2. cloning project3 packages and launching the files
```
catkin_make
source devel/setup.bash
roslaunch my_robot world.launch
```
3. adding 3D camera to the project 3

RTAB map package uses a 2D Laser, providing sensor_msgs/LaserScan messages, Odometry sensors, providing nav_msgs/Odometry messages, 3D Camera, compatible with openni_launch, openni2_launch or freenect_launch ROS packages

4. adding launch for RTAB map
assign the correct topic to be remapped to the topics required by rtabmap.

- scan
- rgb/image
- depth/image
- rgb/camera_info

5. adding rtabmapviz node to the mapping.launch file
download this
```
sudo apt install ros-melodic-rtabmap-ros
```
6. run teleop, world and mapping in 3 different terminal

