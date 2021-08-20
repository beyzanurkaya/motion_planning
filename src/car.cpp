#include "car.h"

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

                auto message = visualization_msgs::msg::Marker();
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

                do {

                    geometry_msgs::msg::Pose &pose = msg->poses.at(i);
                    geometry_msgs::msg::Pose &pose_next = msg->poses.at(i+1);
                    geometry_msgs::msg::Pose &new_pose = msg->poses.at(i);
                    geometry_msgs::msg::Pose &new_pose_next = msg->poses.at(i+1);
                    if(i==0){
                        marker.pose = pose;
                        marker.pose.position.y = 2.0;
                    }else{
                        auto new_angle = atan2(new_pose_next.position.y - new_pose.position.y, new_pose_next.position.x - new_pose.position.x);
                        double dx = cos(new_angle)*2;
                        double dy = sin(new_angle)*2;
                        new_pose.position.x = dx + pose.position.x;
                        new_pose.position.y = dy + pose.position.y;
                        marker.pose = new_pose;
                    }

                    i++;
                    message = marker;
                    marker_publisher->publish(message);
                    rclcpp::sleep_for(1s);
                    marker_publisher->publish(markerD);



                }while(i < 180);

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

