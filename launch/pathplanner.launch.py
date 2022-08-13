import os.path
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    path_planner_server_package_path = get_package_share_directory('path_planner_server')
    config_folder = os.path.join(path_planner_server_package_path, 'config')
    nav2_yaml = os.path.join(config_folder, 'nav2.yaml')
    controller_yaml = os.path.join(config_folder, 'controller.yaml')
    recovery_yaml = os.path.join(config_folder, 'recovery.yaml')
    bt_xml_path = os.path.join(config_folder, 'behavior.xml')
    return LaunchDescription([
        Node(
            package='nav2_planner',
            executable='planner_server',
            name='planner_server',
            output='screen',
            parameters=[nav2_yaml]),
        Node(
            package='nav2_controller',
            executable='controller_server',
            output='screen',
            parameters=[controller_yaml]),
        Node(
            package='nav2_recoveries',
            executable='recoveries_server',
            name='recoveries_server',
            output='screen'),
        Node(
            package='nav2_bt_navigator',
            executable='bt_navigator',
            name='bt_navigator',
            output='screen',
            parameters=[recovery_yaml, {'default_bt_xml_filename': bt_xml_path}]),
        Node(
            package='nav2_lifecycle_manager',
            executable='lifecycle_manager',
            name='lifecycle_manager_pathplanner',
            output='screen',
            parameters=[{'use_sim_time': True},
                        {'autostart': True},
                        {'node_names': ['planner_server','controller_server', 'recoveries_server', 'bt_navigator']}])
    ])