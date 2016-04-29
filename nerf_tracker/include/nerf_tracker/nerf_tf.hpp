/*
 * nerf_tf.hpp
 *
 *  Created on: Apr 27, 2016
 *      Author: christopher
 */

#ifndef NERF_TF_HPP
#define NERF_TF_HPP

#include "ros/ros.h"
#include "tf/tf.h"
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>
#include "tf2_msgs/TFMessage.h"

class NerfTF {
public:
	NerfTF();

	bool lookupTransform();
	void broadcastTransform(const ros::TimerEvent&);
	void sendJointAngles();

	double getUserX();
	double getUserY();

private:
	void poseCallback(tf2_msgs::TFMessage msg);

	ros::NodeHandle nh;
	ros::Timer timer;
	//ros::Subscriber poseSub;

	ros::Publisher armPub;

	tf::TransformListener listener;
	tf::TransformBroadcaster broadcaster;

	double yaw, pitch;

	unsigned int activeUser;
	double userX, userY;
};

#endif
