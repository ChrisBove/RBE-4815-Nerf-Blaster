import rospy
import serial
from geometry_msgs.msg import Point
from std_msgs.msg import Bool

def callback(msg):
    x = msg.x
    y = msg.y
    
    #ser.write("%+01.3f"%x + "%+01.3f"%y)
    print "%+01.3f"%x + "%+01.3f"%y
    
    raw_input("enter anything to simulate arm completing motion...")
    #ser.readline();
    pub.publish(Bool(True));
    

if __name__ == '__main__':
    global ser
    rospy.init_node('arm_fwd')
    #ser= serial.Serial('/dev/ttyUSB1', 9600)
    
    sub = rospy.Subscriber("/arm", Point, callback)
    pub = rospy.Publisher("/shoot", Bool, queue_size = 1)
    
    rospy.spin();
