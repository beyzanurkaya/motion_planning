#include "points.h"

using namespace std;
using namespace chrono_literals;
using placeholders::_1;

class PointsNode : public rclcpp::Node
{
public:
    PointsNode(): Node("points")
    {
        markers_publisher = this->create_publisher<visualization_msgs::msg::MarkerArray>("points", 10);
        poses_subscriber = this->create_subscription<geometry_msgs::msg::PoseArray>("sine_path" , 10, bind(&PointsNode::topic_callback, this, _1));
    }


private:
    void topic_callback(const geometry_msgs::msg::PoseArray::SharedPtr msg) const
    {
        auto message = visualization_msgs::msg::MarkerArray();
        visualization_msgs::msg::MarkerArray markerArray;
        visualization_msgs::msg::Marker marker;
        
        for(int i=0;i<=360;i++){

            marker.header.frame_id = "map";
            marker.ns = "my_namespace";
            marker.id = i;
            marker.type = visualization_msgs::msg::Marker::SPHERE;
            marker.action = visualization_msgs::msg::Marker::ADD;
            marker.pose.orientation.x = 1.0;
            marker.pose.orientation.y = 1.0;
            marker.pose.orientation.z = 0.0;
            marker.pose.orientation.w = 1.0;
            marker.scale.x = 0.3;
            marker.scale.y = 0.3;
            marker.scale.z = 0.3;
            marker.color.a = 1.0;
            marker.color.r = 0.5;
            marker.color.g = 1.0;
            marker.color.b = 0.0;

            geometry_msgs::msg::Pose p = msg->poses.at(i);
            marker.pose = p;

            markerArray.markers.push_back(marker);
        }
        message = markerArray;
        markers_publisher->publish(message);

    }

    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr markers_publisher;
    rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr poses_subscriber;

};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = make_shared<PointsNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}