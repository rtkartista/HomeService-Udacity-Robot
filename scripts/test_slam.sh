#!/bin/sh
xterm  -e  " source devel/setup.bash; export SVGA_VGPU10=0; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/rtk/p5/src/worlds/new.world" &
sleep 15
xterm  -e  " source devel/setup.bash; rosrun gmapping slam_gmapping" &
sleep 15
xterm  -e  " source devel/setup.bash;  export SVGA_VGPU10=0; rosrun rviz rviz -d /home/rtk/p5/src/rvizConfig/project.rviz" &
sleep 15
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch"
