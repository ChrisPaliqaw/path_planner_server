#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include "../include/path_planner_server/nav_to_pose_action_client.hpp"
#include "rclcpp/logging.hpp"


/*
user:~$ ros2 interface show geometry_msgs/msg/PoseStamped
# A Pose with reference coordinate frame and timestamp

std_msgs/Header header
Pose pose
*/

/*
user:~$ ros2 interface show geometry_msgs/msg/Pose
# A representation of pose in free space, composed of position and orientation.

Point position
Quaternion orientation
user:~$
*/

/*
user:~$ ros2 interface list | grep geometry_msgs/msg/Point
    geometry_msgs/msg/Point
    geometry_msgs/msg/Point32
    geometry_msgs/msg/PointStamped
*/

/*
user:~$ ros2 interface show geometry_msgs/msg/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
*/

/*
user:~$ ros2 interface show geometry_msgs/msg/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x 0
float64 y 0
float64 z 0
float64 w 1
*/

namespace path_planner_server
{
NavToPoseActionClient::NavToPoseActionClient():
    Node("nav_to_pose_action_client")
{
    auto ret = rcutils_logging_set_logger_level(
        get_logger().get_name(), RCUTILS_LOG_SEVERITY_DEBUG);

    goal_pose_publisher_ =
      create_publisher<geometry_msgs::msg::PoseStamped>(kGoalPoseTopic, 10);
    goal_pose_ = std::make_shared<geometry_msgs::msg::PoseStamped>();

    PublishGoalPose();

    if (ret != RCUTILS_RET_OK) {
        RCLCPP_ERROR(get_logger(), "Error setting severity: %s", rcutils_get_error_string().str);
        rcutils_reset_error();
    }
}

void NavToPoseActionClient::PublishGoalPose() {
  RCLCPP_INFO(get_logger(), "Publishing goal pose");
  // https://docs.ros.org/en/foxy/Tutorials/Intermediate/Tf2/Learning-About-Tf2-And-Time-Cpp.html
  goal_pose_->header.stamp = this->get_clock()->now();
  goal_pose_->header.frame_id = "world";
  goal_pose_publisher_->publish(*goal_pose_);
}

const std::string NavToPoseActionClient::kGoalPoseTopic = "goal_pose";

} // namespace path_planner_server

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  
  auto nav_to_pose_action_client =
      std::make_shared<path_planner_server::NavToPoseActionClient>();

  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(nav_to_pose_action_client);
  executor.spin();

  // Shutdown and exit.
  rclcpp::shutdown();
  return 0;
}