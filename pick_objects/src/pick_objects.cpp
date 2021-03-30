#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/UInt8.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv)
{

  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //set up publisher to broadcast if robot is at goal marker
  ros::Publisher goal_reach_pub = n.advertise<std_msgs::UInt8>("/goal_status", 1);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;		// pick-up & drop goal
  std_msgs::UInt8 status_msg;  // goal reach status

  // pick-goal setup
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Send the goal position and orientation for the robot for pick-up location
  ROS_INFO("publishing pick-up goal");
  // Define a position and orientation for the robot to reach

  n.getParam("/pickup_location/pose_x", goal.target_pose.pose.position.x);
  n.getParam("/pickup_location/pose_y", goal.target_pose.pose.position.y);
  n.getParam("/pickup_location/pose_z", goal.target_pose.pose.position.z);
  n.getParam("/pickup_location/quat_x", goal.target_pose.pose.orientation.x);
  n.getParam("/pickup_location/quat_y", goal.target_pose.pose.orientation.y);
  n.getParam("/pickup_location/quat_z", goal.target_pose.pose.orientation.z);
  n.getParam("/pickup_location/quat_w", goal.target_pose.pose.orientation.w);
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("reached PICK-UP location");

    // publish goal-reach status
    status_msg.data = 1;
    goal_reach_pub.publish(status_msg);
    // wait a bit before next message
    ros::Duration(5.0).sleep();
  }
  else {
    ROS_INFO("The robot failed to reach pick-up location");
    return 0;
  }


  // robot reached pick-up location, send drop-off location
  ROS_INFO("Sending drop-off goal");
  

  // Define a position and orientation for the robot to reach
  n.getParam("/dropoff_location/pose_x", goal.target_pose.pose.position.x);
  n.getParam("/dropoff_location/pose_y", goal.target_pose.pose.position.y);
  n.getParam("/dropoff_location/pose_z", goal.target_pose.pose.position.z);
  n.getParam("/dropoff_location/quat_x", goal.target_pose.pose.orientation.x);
  n.getParam("/dropoff_location/quat_y", goal.target_pose.pose.orientation.y);
  n.getParam("/dropoff_location/quat_z", goal.target_pose.pose.orientation.z);
  n.getParam("/dropoff_location/quat_w", goal.target_pose.pose.orientation.w);
  ac.sendGoal(goal);

  ROS_INFO("Heading to Drop-off site");
  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its drop goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    //ROS_INFO("Robot has reached DROP-OFF location");
    ROS_INFO("Dropping Package");
    // publish goal-reach status
    status_msg.data = 2;
    goal_reach_pub.publish(status_msg);
    sleep(5);
  }
  else {
    ROS_INFO("The robot failed to reach drop-off location");
  }

  return 0;
}
