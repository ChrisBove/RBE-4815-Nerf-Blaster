/* does all the transforms necessary for the nerf gun
 * nerf_tf.cpp
 *
 *  Created on: Apr 27, 2016
 *      Author: christopher
 */


#include <ros/ros.h>
#include <nerf_tracker/nerf_tf.hpp>
#include <ros/duration.h>
#include <ros/init.h>
#include <ros/node_handle.h>
#include <ros/time.h>
#include <rosconsole/macros_generated.h>
#include <tf/exceptions.h>
#include <tf/LinearMath/Quaternion.h>
#include <tf/LinearMath/Transform.h>
#include <tf/LinearMath/Vector3.h>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Char.h>

#include "math.h"
//#include <nerf_tracker/nerf_shooter.hpp>

NerfTF::NerfTF(){
	//poseSub = nh.subscribe("/tf", 10, poseCallback);
	armPub = nh.advertise<geometry_msgs::Point>("/arm", 10);
	activeUser = 0; // start at 0 since the first check always fails
	timer = nh.createTimer(ros::Duration(0.1), &NerfTF::broadcastTransform, this);
}

void NerfTF::poseCallback(tf2_msgs::TFMessage msg){
	std::cout << "Callback" << std::endl;

}

void NerfTF::broadcastTransform(const ros::TimerEvent&){
	//std::cout << "Broadcasting again" << std::endl;

	ros::Time time = ros::Time::now();

	tf::Transform tfToBase;
	tfToBase.setOrigin(tf::Vector3(-1.335, -1.03, 0.057));
	tfToBase.setRotation(tf::Quaternion(0, 0, 1, 1));
	broadcaster.sendTransform(
			tf::StampedTransform(tfToBase, time, "/openni_depth_frame",
					"/abb_base"));
	ros::spinOnce();
	tf::Transform tfToWrist;
	tfToWrist.setOrigin(tf::Vector3(-0.15, 0.0, 1.39));
	//tfToWrist.setOrigin(tf::Vector3(0.75, 0.0, 1.187)); // for 0 pose
	tfToWrist.setRotation(tf::Quaternion(0, 0, 0, 1));
	broadcaster.sendTransform(
			tf::StampedTransform(tfToWrist, time, "/abb_base",
					"/abb_wrist"));
	ros::spinOnce();
	tf::Transform tfToGun;
	tfToGun.setOrigin(tf::Vector3(0.15, 0.0, 0.0));
	tfToGun.setRotation(tf::Quaternion(0, 0, -1, 1));
	broadcaster.sendTransform(
			tf::StampedTransform(tfToGun, time, "/abb_wrist",
					"/nerf"));
	ros::spinOnce();

}

bool NerfTF::lookupTransform(){
	tf::StampedTransform transform; // for storing transform

	// create string of tf topic based on activeUser
	std::stringstream ss;
	ss << "/torso_" << activeUser;

	if (ros::ok()) {
		try {
			listener.lookupTransform("/nerf", ss.str(),
					ros::Time(0), transform);

			userX = transform.getOrigin().x();
			userY = transform.getOrigin().y();
			// right of kinect is negative yaw
			yaw = atan2(transform.getOrigin().y(), transform.getOrigin().x()) * 180.0/3.14159;
			// above kinect is negative pitch
			pitch = -atan2(transform.getOrigin().z()+0.8,
					transform.getOrigin().x()) * 180.0/3.14159;
			std::cout << "Got transform, yaw: " << yaw << " pitch: " << pitch
					<< std::endl;

			// since we got a transform, let's pipe that over
			//sendJointAngles();
			return true;


		} catch (tf::TransformException ex) {
			//ROS_ERROR("%s", ex.what());
			ros::spinOnce();
			ros::Duration(0.25).sleep();
			// try another user string
			if (activeUser < 10)
				activeUser++;
			else
				activeUser = 1;

			return false;

		}
	} else
		return false;
}

void NerfTF::sendJointAngles(){
	geometry_msgs::Point point;
	point.x = (yaw) - 90;
	point.y = pitch + 180;
	armPub.publish(point);
}

double NerfTF::getUserX(){
	return userX;
}

double NerfTF::getUserY(){
	return userY;
}
