#include "sine_path.h"


SinePath::SinePath() : Node("sinePath"){

    poses_publisher = this->create_publisher<geometry_msgs::msg::PoseArray>("sine_path", 10);
    timer = this->create_wall_timer(500ms, std::bind(&SinePath::timer_callback, this));

}

void SinePath::timer_callback()
{
    auto message = geometry_msgs::msg::PoseArray();

    poseArray.header.frame_id = "map";
    poseArray.header.stamp = this->now();

    for(int i=0;i<=360;i++){

        p.position.x  = static_cast<float>(i);
        p.position.y = 10*sin(static_cast<float>(i) * M_PI / 5);
        poseArray.poses.push_back(p);
    }
    for(int i=0;i<poseArray.poses.size()-1;i++){

        geometry_msgs::msg::Pose &pose = poseArray.poses.at(i);
        geometry_msgs::msg::Pose &pose_next = poseArray.poses.at(i+1);
        double angle = atan2(pose_next.position.y - pose.position.y, pose_next.position.x - pose.position.x);

        q = Eigen::AngleAxisf(0, Eigen::Vector3f::UnitX())
                * Eigen::AngleAxisf(0, Eigen::Vector3f::UnitY())
                * Eigen::AngleAxisf(angle, Eigen::Vector3f::UnitZ());

        pose.orientation.x = q.x();
        pose.orientation.y = q.y();
        pose.orientation.z = q.z();
        pose.orientation.w = q.w();
    }
    poses_publisher->publish(poseArray);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SinePath>());
    rclcpp::shutdown();
    return 0;
}