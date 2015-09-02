#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
import socket

from kaken_msgs.msg import RelativePoseStamped
from std_msgs.msg import Header
from geometry_msgs.msg import Twist, Pose

DEFAULT_NODE_NAME = 'camera_node'
IP_ADDRESS = '192.168.0.3'
PORT = 5555
BUFFER_SIZE = 1024


class RelativePosePublisher(object):
    def __init__(self):
        self._pose_publisher = rospy.Publisher('/position_kohga3_1',
                                               RelativePoseStamped,
                                               queue_size=5)
        self._kohga3_1_pose = RelativePoseStamped(header=Header(stamp=rospy.Time.now()),
                                                  target='kohga3_1')
        self._clientsock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._clientsock.bind((IP_ADDRESS, PORT))


    def activate(self):
        rospy.Subscriber('kohga3_1_twist', Twist, self._twist_callback)
        rospy.loginfo('RelativePosePublisher is activated!')
        return self

    def _twist_callback(self, twist):
        self._kohga3_1_pose.header.stamp = rospy.Time.now()
        self._kohga3_1_pose.pose.position.x += twist.linear.x
        self._kohga3_1_pose.pose.position.y += twist.linear.y
        self._kohga3_1_pose.pose.position.z += twist.linear.z

    def update(self):
        recv_str, addr = self._clientsock.recv(BUFFER_SIZE)
        print(recv_str)
        # self._kohga3_1_pose.header.stamp = rospy.Time.now()
        # self._kohga3_1_pose.pose = self._unpack_recv_str(recv_str)
        return self

    def _unpack_recv_str(self, str):
        return Pose()

    def publish_data(self):
        self._pose_publisher.publish(self._kohga3_1_pose)

    def close(self):
        self._clientsock.close()

# --------------------------------------------
if __name__ == '__main__':
    rospy.init_node(DEFAULT_NODE_NAME, anonymous=True)
    rate_mgr = rospy.Rate(100)  # Hz

    relative_pose_pub = RelativePosePublisher().activate()

    while not rospy.is_shutdown():
        relative_pose_pub.update().publish_data()
        rate_mgr.sleep()

    relative_pose_pub.close()