#!/bin/sh
xterm  -e  " source devel/setup.bash; export SVGA_VGPU10=0; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/worlds/new.world" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/rtk/p5/src/map/mymap.yaml" &
sleep 5
xterm  -e  " source devel/setup.bash;  export SVGA_VGPU10=0; rosrun rviz rviz -d /home/rtk/p5/src/rvizConfig/project.rviz"
