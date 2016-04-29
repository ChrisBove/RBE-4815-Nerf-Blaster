import rospy
import serial
from std_msgs.msg import Char

def callback(msg):
    ser.write(chr(msg.data))

if __name__ == '__main__':
    global ser
    rospy.init_node('serial_fwd')
    ser= serial.Serial('/dev/ttyUSB0', 9600)
    
    sub = rospy.Subscriber("/nerf", Char, callback)
    
    rospy.spin()
