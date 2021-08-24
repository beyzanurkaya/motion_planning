//
// Created by beyza on 20.08.2021.
//

#ifndef BUILD_POINTS_H
#define BUILD_POINTS_H

#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/pose_array.hpp"
#include "visualization_msgs/msg/marker_array.hpp"

using namespace std;
using placeholders::_1;

/*! This class contains a publisher named markers_publisher, a subscriber named poses_subscriber and callback function named topic_callback() */

class PointsNode : public rclcpp::Node
        {
        public:
            PointsNode();

        private:

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
             *         - this variable keeps positions came from sine_path node
             */

            visualization_msgs::msg::Marker marker;

            /*!
            *  @brief markerArray is a variable of type markerArray that is a member of visualization_msgs.
            *    - what's inside?
            *         - markers
            *    - Why is this variable used?
            *         - this variable keeps points of sine path
            */

            visualization_msgs::msg::MarkerArray markerArray;

            void topic_callback(geometry_msgs::msg::PoseArray::SharedPtr msg);

            /** @fn void PointsNode::topic_callback()
             *  @brief The topic_callback function receives the message data published over the topic.
             */

            /**
             *  @brief the publisher is a ROS node that publishes a specific type of ROS message over a given ROS topic. “Interested” nodes (Subscribers) can access messages so published.
                  - what is published?
             *         - markers_publisher publishes a markerArray with color, action, scale, positions and orientations specified.
             */

            rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr markers_publisher;

            /**
              *  @brief the subscriber subscribes to the topic so that it receives the messages whenever any message is published to the topic.
              *      - poses_subscriber gets position information for markers by subscribing to the PoseArray message of the sinus path node.
              */

            rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr poses_subscriber;

        };

#endif //BUILD_POINTS_H

