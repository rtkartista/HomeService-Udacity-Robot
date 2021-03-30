#!/bin/sh
# xterm  -e  " source devel/setup.bash; export SVGA_VGPU10=0; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/worlds/new.world" &
xterm  -e  " source devel/setup.bash; export SVGA_VGPU10=0; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/rtk/p5/src/worlds/new.world" &
sleep 20
# xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/map/map_new.yaml initial_pose_x:=0.028 initial_pose_y:=0.019 initial_pose_a:=-1.558" &
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/rtk/p5/src/map/mymap.yaml initial_pose_x:=-1.057 initial_pose_y:=0.002 initial_pose_a:=-0.014" &
sleep 10
xterm  -e  " source devel/setup.bash; rosrun add_markers add_markers" &
sleep 20
# xterm  -e  " source devel/setup.bash; rosrun rviz rviz -d /home/workspace/catkin_ws/src/rvizConfig/project.rviz"
xterm  -e  " source devel/setup.bash; rosrun rviz rviz -d /home/rtk/p5/src/rvizConfig/project.rviz"
