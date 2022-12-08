/**
 * @file turtlebot3_drive.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 1
 * @date 2022-12-07
 * e
 * @copyright Copyright (c) 2022
 * 
 */
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>

using std::placeholders::_1;
using namespace std::chrono_literals;

/**
 * @brief Class for turtlebot movement and lidar scan
 * 
 */
class Turtlebot : public rclcpp::Node {
 public:
/**
 * @brief Construct a new Turtlebot object with a velocity publisher and lidar subscriber * 
 */
  Turtlebot(): Node("Turtle") {
    velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(
    "cmd_vel", 10);

    lidar_subscriber_ = this->create_subscription<sensor_msgs::msg::LaserScan> (
     "trtl_lidar", 5, std::bind(&Turtlebot::scanAndMove , this, _1));
}

 private:
 /**
  * @brief Velocity publisher and lidar subscriber 
  * 
  */
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::
  SharedPtr lidar_subscriber_;

  /**
   * @brief Allows the turtlebot scan its surroundings and move accordingly 
   * 
   * @param msg A lidar's scan
   */
  void scanAndMove(sensor_msgs::msg::LaserScan::UniquePtr msg) {
    /// By default, there is no obstacle detected
    bool obstacle = false;
    /// Object's distance must be less than .7,
    // for it to be considered to be an obstacle
    float obstacle_distance = 0.7;
    /// Lidar's point directly infront of the turtlebot
    int lidar_angle = 0;
    /// turtle bots velocity
    auto velocity = geometry_msgs::msg::Twist();
    /// if the range in front of the turtbot is less than .7,
    /// then there is an obstacle
    if (msg->ranges.at(lidar_angle) < obstacle_distance) {
      obstacle = true;
    } else {
      obstacle = false;
    }
    /// If there is an obstacle,
    // then the bot will turn. Else, it will move foward
    if (obstacle) {
      velocity.linear.x = 0.0;
      velocity.angular.z = 0.5;
    } else {
      velocity.linear.x = 0.5;
      velocity.angular.z = 0.0;
    }
    velocity_publisher_-> publish(velocity);
    }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_unique<Turtlebot>());
  rclcpp::shutdown();
  return 0;
}

