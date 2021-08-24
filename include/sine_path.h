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

class SinePath : public rclcpp::Node
        {
        public:

            SinePath();

        private:
            geometry_msgs::msg::PoseArray poseArray;
            geometry_msgs::msg::Pose p;
            Eigen::Quaternionf q;

            void timer_callback();
            rclcpp::Publisher<geometry_msgs::msg::PoseArray>::SharedPtr poses_publisher;
            rclcpp::TimerBase::SharedPtr timer;

        };

#endif //BUILD_SINE_PATH_H

