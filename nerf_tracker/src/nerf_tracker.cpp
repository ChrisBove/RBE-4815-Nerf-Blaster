#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "stdlib.h"
#include "tf/tf.h"

#include <sstream>

#include "nerf_tracker/nerf_tf.hpp"
#include "nerf_tracker/nerf_shooter.hpp"

bool shoot;

void shootCallback(std_msgs::Bool status){
	shoot = true;
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "nerf_tracker");

	ros::NodeHandle n;

	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
	ros::Subscriber statSub = n.subscribe("/shoot", 1, shootCallback);

	ros::Rate loop_rate(10);

	Shooter shooter;
	NerfTF nerfTF;
	ros::Duration(1.0).sleep();
	ros::spinOnce();
	shooter.spinDown();

	bool isSpinning = false;

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

		if(nerfTF.lookupTransform()){
			shooter.spinUp();
			if (!isSpinning){
				ros::Duration(1.5).sleep();
				isSpinning = true;
			}

			while(!shoot && ros::ok()){
				ros::spinOnce();
				loop_rate.sleep();
			}
			shooter.fire();
			shoot = false;
		}
		else{
			shooter.spinDown();
			shoot = false;
			isSpinning = false;
		}

		//chatter_pub.publish(msg);

		ros::spinOnce();

		loop_rate.sleep();
		++count;
	}

	return 0;
}
