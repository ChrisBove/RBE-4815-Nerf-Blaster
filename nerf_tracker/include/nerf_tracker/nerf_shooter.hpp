/*
 * nerf_shooter.hpp
 *
 *  Created on: Apr 27, 2016
 *      Author: christopher
 */

#ifndef NERF_SHOOTER_HPP_
#define NERF_SHOOTER_HPP_


#include <iostream>
#include <fstream>
#include <string>
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

	std::ofstream arduino;

	const char SPIN_UP = 'w';
	const char SPIN_DOWN = 's';
	const char SHOOT_ONCE = 'q';
	const char AUTOFIRE_START = 'a';
	const char AUTOFIRE_STOP = 'z';

	const int baudrate = 9600;

	//static const std::string usbPort;
//	boost::shared_ptr<serial_port_base::baud_rate>
//	serial_port_base::baud_rate BAUD(baudrate);
//	serial_port_base::parity PARITY(serial_port_base::parity::none);
//	serial_port_base::stop_bits STOP(serial_port_base::stop_bits::one);
};



#endif /* NERF_NERF_TRACKER_INCLUDE_NERF_TRACKER_NERF_SHOOTER_HPP_ */
