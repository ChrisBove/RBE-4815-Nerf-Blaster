/*
 * nerf_shooter.hpp
 *
 *  Created on: Apr 27, 2016
 *      Author: christopher
 */

#ifndef NERF_SHOOTER_HPP
#define NERF_SHOOTER_HPP


#include <ros/ros.h>
#include <std_msgs/Char.h>
#include <fstream>
#include <iostream>
#include <string>

//#include "serial/serial.h"
//#include <boost/asio.hpp>
//using namespace::boost::asio;


class Shooter {
public:
	Shooter();
	~Shooter();

	void spinUp();
	void spinDown();
	void fire();
	//void SendDataViaSerialPort(const std::string& to_write);

private:

	ros::NodeHandle nh;
	ros::Publisher nerfPub;
	//std::ofstream arduino;
	//serial::Serial port;

	std_msgs::Char SPIN_UP;
	std_msgs::Char SPIN_DOWN;
	std_msgs::Char SHOOT_ONCE;
	std_msgs::Char AUTOFIRE_START;
	std_msgs::Char AUTOFIRE_STOP;

	const int baudrate = 9600;

	static const std::string usbPort;
//	boost::shared_ptr<serial_port_base::baud_rate>
//	serial_port_base::baud_rate BAUD(baudrate);
//	serial_port_base::parity PARITY(serial_port_base::parity::none);
//	serial_port_base::stop_bits STOP(serial_port_base::stop_bits::one);
};



#endif /* NERF_NERF_TRACKER_INCLUDE_NERF_TRACKER_NERF_SHOOTER_HPP_ */
