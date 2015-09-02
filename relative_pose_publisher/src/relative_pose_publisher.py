#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from kaken_msgs.msg import RelativePoseStamped
from std_msgs.msg import Header
from geometry_msgs.msg import Twist

DEFAULT_NODE_NAME = 'camera_node'


class RelativePosePublisher(object):
    def __init__(self):
        self._pose_publisher = rospy.Publisher('/position_kohga3_1',
                                               RelativePoseStamped,
                                               queue_size=5)
        self._kohga3_1_pose = RelativePoseStamped(header=Header(stamp=rospy.Time.now()),
                                                  target='kohga3_1')

    def activate(self):
        rospy.Subscriber('kohga3_1_twist', Twist, self._twist_callback)
        return self

    def _twist_callback(self, twist):
        self._kohga3_1_pose.header.stamp = rospy.Time.now()
        self._kohga3_1_pose.pose.position.x += twist.linear.x
        self._kohga3_1_pose.pose.position.y += twist.linear.y
        self._kohga3_1_pose.pose.position.z += twist.linear.z

    def update(self):
        return self

    def publish_data(self):
        self._pose_publisher.publish(self._kohga3_1_pose)

# --------------------------------------------
if __name__ == '__main__':
    rospy.init_node(DEFAULT_NODE_NAME, anonymous=True)
    rate_mgr = rospy.Rate(100)  # Hz

    relative_pose_pub = RelativePosePublisher().activate()

    while not rospy.is_shutdown():
        relative_pose_pub.update().publish_data()
        rate_mgr.sleep()
