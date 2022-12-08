# Ros2 Turtlebot3 project
Submission for Week 12 Assigment  

### **Results**
Rosbag2, Cpplint and Cppcheck results are saved in the results folder  

### **Dependencies:**
| Name | Version |  
|ROS2 | Humble |  
|Python3 | 3.10 |  

### **Steps to Build:** 
In the root of the package (/ros_ws), run this in a terminal:
```
colcon build 
```
### **Steps to launch and run Turtlebot with world ** 
In /ros_ws
```
export TURTLEBOT3_MODEL=burger
ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py
#Or
ros2 launch ./src/turtlebot3_gazebo/launch/turtlebot3_world.launch.py
```
To launch with rosbag2 
```
export TURTLEBOT3_MODEL=burger
ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py record:=true
#Or
ros2 launch ./src/turtlebot3_gazebo/launch/turtlebot3_world.launch.py record:=true
```
To run turtlebot program 
```
ros2 run turtlebot3_gazebo turtlebot3_drive
```

### **Know Issues**
- This package is based of the Robotis' Turtlebot package. Because of this, the computer might get confused with the same package in /opt/ros/humble.  
- Because of this, the launch file might run the turtlebot package found in /opt/ros/humble, not the one in ros_ws
- This means that the launch file cannot use rosbag or the excutable properly.
- Rosbag2 recording was taken with this cmd: ros2 bag record -o recording -a



