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
#include "serial/serial.h"



//#include <boost/asio.hpp>
//using namespace::boost::asio;

Shooter::Shooter(){
	//serial::Serial thingy("dev/ttyUSB0", 9600, serial::Timeout::simpleTimeout(1000));
	//usbPort << "dev/ttyUSB0";
	// http://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
	std::string str("dev/ttyUSB0");
	std::cout << "starting com setup" << std::endl;
	port.setBaudrate(9600);
	port.setPort(str);
	port.open();
	//arduino.open("dev/ttyUSB0");
	std::cout << "Sleeping to wait for Arduino reset" << std::endl;
	ros::Duration(3.0).sleep();
	std::cout << "Done Sleeping" << std::endl;
}

Shooter::~Shooter(){
	//arduino.close();
	port.close();
}

void Shooter::spinUp(){
	//arduino << "w";
	//arduino << SPIN_UP;
	port.write("w");
}

void Shooter::spinDown(){
	//arduino << SPIN_DOWN;
}

void Shooter::fire(){
	//arduino << SHOOT_ONCE;
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
