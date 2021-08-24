//
// Created by beyza on 20.08.2021.
//

#ifndef BUILD_CAR_H
#define BUILD_CAR_H

#include <memory>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_array.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "tf2/LinearMath/Quaternion.h"

/*! This class contains a publisher named marker_publisher, a subscriber named poses_subscriber and callback function named topic_callback() */

class CarNode : public rclcpp::Node
        {
        public:
            CarNode();

        private:

            /*!
             *  @brief markerD is a variable of type Marker that is a member of visualization_msgs.
             *    - what's inside?
             *         - frame_id
             *         - ns
             *         - id
             *         - type
             *         - action
             *         - color
             *         - scale
             *         - pose
             *            - position
             *                - x,y,z
             *            - orientation
             *                - x,y,z,w
             *    - Why is this variable used?
             *         - this variable's action is DELETEALL, which means this marker's job is delete all markers in the particular Rviz display.
             */

            visualization_msgs::msg::Marker markerD;
            /*!
             *  @brief marker is a variable of type Marker that is a member of visualization_msgs.
             *    - what's inside?
             *         - frame_id
             *         - ns
             *         - id
             *         - type
             *         - action
             *         - color
             *         - scale
             *         - pose
             *            - position
             *                - x,y,z
             *            - orientation
             *                - x,y,z,w
             *    - Why is this variable used?
             *         - this variable represents a car
             *         - orientation of this marker came from poses_subscriber
             */


            visualization_msgs::msg::Marker marker;

            /** @fn void CarNode::topic_callback()
              *  @brief The topic_callback function receives the message data published over the topic.

              */

            void topic_callback(geometry_msgs::msg::PoseArray::SharedPtr msg);

            /**
              *  @brief the publisher is a ROS node that publishes a specific type of ROS message over a given ROS topic. “Interested” nodes (Subscribers) can access messages so published.
                   - what is published?
              *         - marker_publisher publishes a marker with color, action, scale, positions and orientations specified.
              *         - but this publisher publish only and only marker.
              */
            rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_publisher;

            /**
             *  @brief the subscriber subscribes to the topic so that it receives the messages whenever any message is published to the topic.
             *      - poses_subscriber gets position information for markers by subscribing to the PoseArray message of the sinus path node.
             */
            
            rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr poses_subscriber;

        };


#endif //BUILD_CAR_H
