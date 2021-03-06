#include "car.h"

using namespace std;
using namespace chrono_literals;
using placeholders::_1;

CarNode::CarNode(): Node("car")
{
    marker_publisher = this->create_publisher<visualization_msgs::msg::Marker>("car", 10);
    poses_subscriber = this->create_subscription<geometry_msgs::msg::PoseArray>("sine_path" , 10, bind(&CarNode::topic_callback, this, _1));

}

void CarNode::topic_callback(const geometry_msgs::msg::PoseArray::SharedPtr msg)
{

    markerD.header.frame_id = "map";
    markerD.action = visualization_msgs::msg::Marker::DELETEALL;

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

    for (int i = 0; i < 360; i++) {

        auto p = msg->poses.at(i);
        double x = p.orientation.x;
        double y = p.orientation.y;
        double z = p.orientation.z;
        double w = p.orientation.w;
        double yaw = atan2(2.0f * (w * z + x * y), w * w + x * x - y * y - z * z);

        double dx = cos(yaw)*2;
        double dy = sin(yaw)*2;

        p.position.x = dx + p.position.x;
        p.position.y = dy + p.position.y;

        if(i==0){
            marker.pose = p;
            marker.pose.position.y = 2.0;
        }else
            marker.pose = p;

        marker_publisher->publish(marker);
        rclcpp::sleep_for(1s);
        marker_publisher->publish(markerD);

    }
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = make_shared<CarNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
