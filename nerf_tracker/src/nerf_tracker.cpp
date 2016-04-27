#include "ros/ros.h"
#include "std_msgs/String.h"
#include "stdlib.h"
#include "tf/tf.h"

#include <sstream>

#include "nerf_tracker/nerf_tf.hpp"
#include "nerf_tracker/nerf_shooter.hpp"

int main(int argc, char **argv) {
	ros::init(argc, argv, "nerf_tracker");

	ros::NodeHandle n;

	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

	ros::Rate loop_rate(10);

	Shooter shooter;
	NerfTF nerfTF;
	ros::spinOnce();
	shooter.spinUp();

	// subscribe to the tf getting published of the user
	// create a tf from kinect to the arm frames

	// wait for valid target
	// calculate the angle between the EOAT and the user torso
	// limit the angles to the joint angles
	// send the joint angle in radians command to the arm

	int count = 0;
	while (ros::ok()) {

		std_msgs::String msg;

		std::stringstream ss;
		ss << "hello world " << count;
		msg.data = ss.str();

		//ROS_INFO("%s", msg.data.c_str());

		nerfTF.lookupTransform();
		//chatter_pub.publish(msg);

		ros::spinOnce();

		loop_rate.sleep();
		++count;
	}

	return 0;
}
