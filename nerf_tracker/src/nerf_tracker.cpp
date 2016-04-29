#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "stdlib.h"
#include "tf/tf.h"

#include <sstream>

#include "nerf_tracker/nerf_tf.hpp"
#include "nerf_tracker/nerf_shooter.hpp"

volatile bool shoot;

void shootCallback(std_msgs::Bool status){
	shoot = true;
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "nerf_tracker");

	ros::NodeHandle n;

	ros::Subscriber statSub = n.subscribe("/shoot", 1, shootCallback);

	ros::Rate loop_rate(100);

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

	double userX = 0;
	double userY = 0;
	double lastX = userX;
	double lastY = userY;

	while (ros::ok()) {

		if(nerfTF.lookupTransform()){
			nerfTF.sendJointAngles();
			shooter.spinUp();
			if (!isSpinning){
				ros::Duration(1.5).sleep();
				isSpinning = true;
			}

			lastX = nerfTF.getUserX();
			lastY = nerfTF.getUserY();

			//std::cout << "lastX: " << lastX << " lastY: " << lastY << std::endl;

			shoot = false;
			// wait for arm to get in place
			while(!shoot && ros::ok()){
				ros::spinOnce();
				loop_rate.sleep();
			}

			nerfTF.lookupTransform();

			std::cout << "diffX: " << lastX - nerfTF.getUserX() << " diffY: " << lastY - nerfTF.getUserY() << std::endl;

			// if haven't moved too much
			if((fabs(lastX - nerfTF.getUserX()) < 0.01) && (fabs(lastY - nerfTF.getUserY()) < 0.01) ){
				shooter.fire();
			}
			else{
				std::cout << "SKIPPING A FIRE!!" << std::endl;
				// do nothing, need to run again
			}
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
	}

	return 0;
}
