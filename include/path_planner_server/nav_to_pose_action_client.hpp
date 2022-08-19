#ifndef PATH_PLANNER_SERVER_NAV_TO_POSE_ACTION_CLIENT_HPP_
#define PATH_PLANNER_SERVER_NAV_TO_POSE_ACTION_CLIENT_HPP_

#include <memory>
#include <rclcpp/rclcpp.hpp>

namespace path_planner_server
{
class NavToPoseActionClient: public rclcpp::Node
{
public:
    explicit NavToPoseActionClient();
private:
    /*rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr
      laser_subscription_;*/
};
} // namespace path_planner_server
#endif // PATH_PLANNER_SERVER_NAV_TO_POSE_ACTION_CLIENT_HPP_