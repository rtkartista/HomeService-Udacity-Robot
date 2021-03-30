#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/UInt8.h>

uint8_t status = 0;

void statusCallback(const std_msgs::UInt8::ConstPtr& msg)
{
   status = msg->data;
   return;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");

  ros::NodeHandle n;
  ros::Rate r(5);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("/goal_status", 1, statusCallback);
  bool dropoff_done = false;

  uint32_t shape = visualization_msgs::Marker::CUBE;

  // for continuous subscription
  while (ros::ok()) {

    visualization_msgs::Marker marker;

    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();


    marker.ns = "add_markers";
    marker.id = 0;

    marker.type = shape;

    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

      if(status == 0) // pick-up marker until robot reaches and completes the task
        {
          marker.action = visualization_msgs::Marker::ADD;
          n.getParam("/pickup_location/pose_x", marker.pose.position.x);
          n.getParam("/pickup_location/pose_y", marker.pose.position.y);
          n.getParam("/pickup_location/pose_z", marker.pose.position.z);
          n.getParam("/pickup_location/quat_x", marker.pose.orientation.x);
          n.getParam("/pickup_location/quat_y", marker.pose.orientation.y);
          n.getParam("/pickup_location/quat_z", marker.pose.orientation.z);
          n.getParam("/pickup_location/quat_w", marker.pose.orientation.w);
          break;
        }

        else if(status == 1)   // after the robot has picked up the object
          {
            sleep(2);
            marker.action = visualization_msgs::Marker::DELETE;
            break;
          }
        else if(status == 2)   // drop-off marker at drop off location
          {
            marker.action = visualization_msgs::Marker::ADD;
            n.getParam("/dropoff_location/pose_x", marker.pose.position.x);
            n.getParam("/dropoff_location/pose_y", marker.pose.position.y);
            n.getParam("/dropoff_location/pose_z", marker.pose.position.z);
            n.getParam("/dropoff_location/quat_x", marker.pose.orientation.x);
            n.getParam("/dropoff_location/quat_y", marker.pose.orientation.y);
            n.getParam("/dropoff_location/quat_z", marker.pose.orientation.z);
            n.getParam("/dropoff_location/quat_w", marker.pose.orientation.w);
            dropoff_done = true;
            break;
          }  

    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    //publish the marker
    marker_pub.publish(marker);


    if (dropoff_done) {
      ROS_INFO("drop off successful");
      r.sleep();
      return 0;
      }

    ros::spinOnce();
    r.sleep();
  }

  return 0;
}
