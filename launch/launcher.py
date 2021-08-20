from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="rviz2",
            executable="rviz2",
            name="rviz2"
        ),
        Node(
            package='motion_planning',
            executable='sine_path_exe',
            output='screen'
        ),
        Node(
            package='motion_planning',
            executable='points_exe',
            output='screen'
        ),
        Node(
            package='motion_planning',
            executable='car_exe',
            output='screen'
        )
    ])
