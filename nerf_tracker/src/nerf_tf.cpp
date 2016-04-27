/* does all the transforms necessary for the nerf gun
 * nerf_tf.cpp
 *
 *  Created on: Apr 27, 2016
 *      Author: christopher
 */

#include <ros/ros.h>
#include "nerf_tracker/nerf_tf.hpp"
#include "std_msgs/String.h"
#include "tf2_msgs/TFMessage.h"
#include "geometry_msgs/Transform.h"
#include "math.h"
#include <tf/transform_listener.h>

NerfTF::NerfTF(){
	//poseSub = nh.subscribe("/tf", 10, poseCallback);
	activeUser = 1;
}

void NerfTF::poseCallback(tf2_msgs::TFMessage msg){
	std::cout << "Callback" << std::endl;

}

void NerfTF::lookupTransform(){
	tf::StampedTransform transform;

	std_msgs::String msg;

	std::stringstream ss;
	ss << "/torso_" << activeUser;
	msg.data = ss.str();

	try {
		listener.lookupTransform("/openni_depth_frame", ss.str(), ros::Time(0),
				transform);
		std::cout << "Got transform" << std::endl;
	} catch (tf::TransformException ex) {
		ROS_ERROR("%s", ex.what());
		ros::Duration(1.0).sleep();
		// try another user string
		if (activeUser < 10) activeUser++;
		else activeUser = 1;
		lookupTransform();

	}
}
