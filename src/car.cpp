#include "car.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include <geometry_msgs/msg/pose2_d.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <Eigen/Geometry>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2_eigen/tf2_eigen.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/impl/utils.h>

using namespace std;
using namespace chrono_literals;
using placeholders::_1;

class CarNode : public rclcpp::Node
        {
        public:
            CarNode(): Node("car")
            {
                marker_publisher = this->create_publisher<visualization_msgs::msg::Marker>("car", 10);
                poses_subscriber = this->create_subscription<geometry_msgs::msg::PoseArray>("sine_path" , 10, bind(&CarNode::topic_callback, this, _1));

            }


        private:

            void topic_callback(const geometry_msgs::msg::PoseArray::SharedPtr msg) const
            {

                int i = 0;

                visualization_msgs::msg::Marker markerD;
                markerD.header.frame_id = "map";
                markerD.action = visualization_msgs::msg::Marker::DELETEALL;

                visualization_msgs::msg::Marker marker;
                marker.header.frame_id = "map";
                marker.ns = "my_namespace";
                marker.id = 0;
                marker.type = visualization_msgs::msg::Marker::CUBE;
                marker.action = visualization_msgs::msg::Marker::ADD;

                marker.scale.x = 4.0;
                marker.scale.y = 1.5;
                marker.scale.z = 1.0;

                marker.color.r = 0.0f;
                marker.color.g = 0.0f;
                marker.color.b = 1.0f;
                marker.color.a = 1.0;

                geometry_msgs::msg::Pose2D pose2d;
                pose2d.x = msg->poses.at(i).position.x;
                pose2d.y = msg->poses.at(i).position.y;


                do {
                    auto p = msg->poses.at(i);
                    double x = p.orientation.x;
                    double y = p.orientation.y;
                    double z = p.orientation.z;
                    double w = p.orientation.w;
                    double yaw = atan2(2.0f * (w * z + x * y), w * w + x * x - y * y - z * z);
                    cout << "yaw: " << yaw*180 / M_PI << endl;

                    double dx = cos(yaw)*2;
                    double dy = sin(yaw)*2;

                    p.position.x = dx + p.position.x;
                    p.position.y = dy + p.position.y;

                    if(i==0){
                        marker.pose = p;
                        marker.pose.position.y = 2.0;
                    }else
                        marker.pose = p;

                    i++;
                    marker_publisher->publish(marker);
                    rclcpp::sleep_for(1s);
                    marker_publisher->publish(markerD);
                }while(i < 360);

            }

            rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_publisher;
            rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr poses_subscriber;

        };

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = make_shared<CarNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

//geometry_msgs::msg::Pose2D pose2d;
//                    auto const &my_pose = msg->poses.at(i);
//                    auto const &my_next_pose = msg->poses.at(i);
//                    auto marker_pose = my_pose;
//                    auto angle = atan2(my_next_pose.position.y - my_pose.position.y, my_next_pose.position.x - my_pose.position.x);
//                    if(i == 0){
//                        marker.pose = marker_pose;
//                        marker_pose.position.y = 2.0;
//                    }else
//                        marker.pose = marker_pose;
//
//
//
//                    double dx = cos(angle)*2;
//                    double dy = sin(angle)*2;
//
//
//                    marker_pose.position.x = dx + marker_pose.position.x;
//                    marker_pose.position.y = dy + marker_pose.position.y;
//                    marker.pose = marker_pose;
//
//                    i++;
//                    marker_publisher->publish(marker);
//                    rclcpp::sleep_for(1s);
//                    marker_publisher->publish(markerD);