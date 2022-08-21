#ifndef PATH_PLANNER_SERVER_NAV_TO_POSE_ACTION_CLIENT_HPP_
#define PATH_PLANNER_SERVER_NAV_TO_POSE_ACTION_CLIENT_HPP_

#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

namespace path_planner_server
{
class NavToPoseActionClient: public rclcpp::Node
{
public:
    explicit NavToPoseActionClient();
private:
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr goal_pose_publisher_;
    std::shared_ptr<geometry_msgs::msg::PoseStamped> goal_pose_;

    void PublishGoalPose();

    static const std::string kGoalPoseTopic;
};
} // namespace path_planner_server
#endif // PATH_PLANNER_SERVER_NAV_TO_POSE_ACTION_CLIENT_HPP_