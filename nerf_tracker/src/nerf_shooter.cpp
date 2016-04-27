/*
 * nerf_shooter.cpp
 *
 *  Created on: Apr 27, 2016
 *      Author: christopher
 */

#include "nerf_tracker/nerf_shooter.hpp"

#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <string>

//#include <boost/asio.hpp>
//using namespace::boost::asio;

Shooter::Shooter(){
	arduino.open("dev/ttyUSB0");
	std::cout << "Sleeping to wait for Arduino reset" << std::endl;
	ros::Duration(5.0).sleep();
	std::cout << "Done Sleeping" << std::endl;
}

Shooter::~Shooter(){
	arduino.close();
}

void Shooter::spinUp(){
	arduino << SPIN_UP;
}

void Shooter::spinDown(){
	arduino << SPIN_DOWN;
}

void Shooter::fire(){
	arduino << SHOOT_ONCE;
}

//void Shooter::SendDataViaSerialPort(const std::string& to_write)
//{
//        io_service io;
//        serial_port port(io, usbPort);
//
//        port.set_option(BAUD);
//        port.set_option(PARITY);
//        port.set_option(STOP);
//
//        write(port, buffer(to_write,1));
//}
