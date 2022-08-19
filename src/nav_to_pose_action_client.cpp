#include <memory>
#include <rclcpp/rclcpp.hpp>
#include "../include/path_planner_server/nav_to_pose_action_client.hpp"

namespace path_planner_server
{
NavToPoseActionClient::NavToPoseActionClient():
    Node("nav_to_pose_action_client")
{
    auto ret = rcutils_logging_set_logger_level(
        get_logger().get_name(), RCUTILS_LOG_SEVERITY_DEBUG);
    if (ret != RCUTILS_RET_OK) {
        RCLCPP_ERROR(get_logger(), "Error setting severity: %s", rcutils_get_error_string().str);
        rcutils_reset_error();
    }
}
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