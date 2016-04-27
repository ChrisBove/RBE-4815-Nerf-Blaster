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
#include "tf2_msgs/TFMessage.h"

class NerfTF {
public:
	NerfTF();

	void lookupTransform();

private:
	void poseCallback(tf2_msgs::TFMessage msg);

	//ros::NodeHandle nh;
	//ros::Subscriber poseSub;

	//ros::Publisher armTF;

	tf::TransformListener listener;

	unsigned int activeUser;
};

#endif
