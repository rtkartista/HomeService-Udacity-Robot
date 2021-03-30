#!/bin/sh
xterm  -e  " source devel/setup.bash; export SVGA_VGPU10=0; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/rtk/p5/src/worlds/new.world" &
sleep 15
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/rtk/p5/src/map/mymap.yaml initial_pose_x:=-1.057 initial_pose_y:=0.002 initial_pose_a:=-0.014" &
sleep 15
xterm  -e  " source devel/setup.bash;  export SVGA_VGPU10=0; rosrun rviz rviz -d /home/rtk/p5/src/rvizConfig/project.rviz" &
sleep 15
xterm  -e  " source devel/setup.bash; rosparam load /home/rtk/p5/src/config/locations.yaml; rosrun pick_objects pick_objects" &
sleep 1
xterm  -e  " source devel/setup.bash; rosparam load /home/rtk/p5/src/config/locations.yaml; rosrun add_markers add_markers "
