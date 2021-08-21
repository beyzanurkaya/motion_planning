# ROS2-Simple-Planning
**Dependencies**

* Ubuntu 20.04
* ROS2 Foxy

**Package Description**

* This package contains 3 node.
  * The first node publishes a pose array (geometry msgs/PoseArray) that represents a sine wave path with a 10 m amplitude and a 10 m period, and is consists of points at regular intervals. The points in this array are expected to be in the x,y plane (z=0), and the point's vector orientation is the position vector relative to the next point.
  
  ![Screenshot from 2021-08-22 00-20-21](https://user-images.githubusercontent.com/32412808/130335093-af61e768-d0c5-46b8-b675-2c1ded1c4d11.png)

  * The second node subscribes to the output of the first node and publishes the marker array to visualize the route consisting of points in rviz2. Dots and vector markers pointing to the next point appear in Rviz2.
   
  ![Screenshot from 2021-08-22 00-20-33](https://user-images.githubusercontent.com/32412808/130335112-b2bae015-bfa2-443f-aaee-6383ada1e223.png)

  
  * The third node should gets the route information as a subscript to the first node output and publish a 4 m x 1.5 m rectangular marker, which represents a car that changes its position to the next point every second, that is, it moves on the route. The car's orientation is the same as the orientation of the point it is now on, and the starting point of this rectangle is the middle of the rear bumper.
  
  ![Screenshot from 2021-08-22 00-20-46](https://user-images.githubusercontent.com/32412808/130335148-851102bf-c0ac-4e28-88bf-e9cad92b33d2.png)
 


**Run motion_planning package**

* ros2 launch motion_planning launcher.py







  
