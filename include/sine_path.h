//
// Created by beyza on 19.08.2021.
//

#ifndef BUILD_SINE_PATH_H
#define BUILD_SINE_PATH_H


#include <memory>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/pose_array.hpp"
#include "Eigen/Dense"
#include <Eigen/Geometry>

using namespace std;
using namespace chrono_literals;

/*! This class contains a publisher named poses_publisher, a timer and a callback function named timer_callback() */

class SinePath : public rclcpp::Node
        {
        public:


            SinePath();


        private:

            /*!
             *  @brief poseArray is a variable of type PoseArray that is a member of geometry_msgs.
             *    - what's inside
             *         - poses
             *    - Why is this variable used?
             *         - this variable keeps inside poses of sine path
             */

            geometry_msgs::msg::PoseArray poseArray;

            /*!
             *  @brief p is a variable of type Pose that is a member of geometry_msgs.
             *    - what's inside
             *         - positions
             *              - x,y,z
             *         - orientations
             *              - x,y,z,w
             *    - Why is this variable used?
             *         - this variable keeps inside positions and orientations of sine path
             */

            geometry_msgs::msg::Pose p;

            /*!
             *  @brief q is a variable of type Quaternionf that is a member of Eigen library.
             *    - what's inside
             *         - quaternions
             *              - x,y,z,w
             *    - Why is this variable used?
             *         - this variable is used to rotate the orientations of the sine path
             *         - after rotation on this variable, new orientation values appear
             *         - these new orientations are now the orientations of the sine path
             */

            Eigen::Quaternionf q;


            void timer_callback();
            /** @fn void SinePath::timer_callback()
             *  @brief The timer_callback function is where the message data is set and the messages are actually published.
             *      - timer is initialized, which causes the timer_callback function to be executed twice a second.
             */

            /**
           *  @brief a publisher is a ROS node that publishes a specific type of ROS message over a given ROS topic. “Interested” nodes (Subscribers) can access messages so published.
                  - what is published?
           *         - poses_publisher publishes a poseArray with positions and orientations specified.
           */

            rclcpp::Publisher<geometry_msgs::msg::PoseArray>::SharedPtr poses_publisher;

            /**
              *  @brief Timers let you schedule a callback to happen at a specified rate.
              *      - timer is initialized, which causes the timer_callback function to be executed twice a second.
              */

            rclcpp::TimerBase::SharedPtr timer;


        };

#endif //BUILD_SINE_PATH_H

