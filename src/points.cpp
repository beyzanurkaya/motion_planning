#include "points.h"


PointsNode::PointsNode(): Node("points")
{
    markers_publisher = this->create_publisher<visualization_msgs::msg::MarkerArray>("points", 10);
    poses_subscriber = this->create_subscription<geometry_msgs::msg::PoseArray>("sine_path" , 10, bind(&PointsNode::topic_callback, this, _1));
}

void PointsNode::topic_callback(geometry_msgs::msg::PoseArray::SharedPtr msg)
{

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
        marker.color.r = 1.0;
        marker.color.g = 0.0;
        marker.color.b = 0.0;


        geometry_msgs::msg::Pose p = msg->poses.at(i);
        marker.pose = p;

        markerArray.markers.push_back(marker);
    }

    markers_publisher->publish(markerArray);

}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = make_shared<PointsNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}