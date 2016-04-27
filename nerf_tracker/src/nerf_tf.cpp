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
	tf::StampedTransform transform; // for storing transform
	double yaw, pitch;

	// create string of tf topic based on activeUser
	std::stringstream ss;
	ss << "/torso_" << activeUser;

	try {
		listener.lookupTransform("/openni_depth_frame", ss.str(), ros::Time(0),
				transform);

		// right of kinect is negative yaw
		yaw = atan2(transform.getOrigin().y(),
					transform.getOrigin().x());
		// above kinect is negative pitch
		pitch = -atan2(transform.getOrigin().z(),
					transform.getOrigin().x());
		std::cout << "Got transform, yaw: " << yaw
				<< " pitch: " << pitch << std::endl;
	} catch (tf::TransformException ex) {
		ROS_ERROR("%s", ex.what());
		ros::Duration(1.0).sleep();
		// try another user string
		if (activeUser < 10) activeUser++;
		else activeUser = 1;
		lookupTransform();

	}
}
