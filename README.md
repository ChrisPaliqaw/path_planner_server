# path_planner_server

## Dependencies
- [cartographer_slam](https://github.com/christophomos/cartographer_slam)
- [localization_server](https://github.com/christophomos/localization_server)

## Step 3 Path planning
Run everything from step 1 & 2 (see dependencies), but use `rviz2` with the config file `path_planner_server/rviz/pathplanner.rviz`
in the `plan` shell
```
cd ros2_ws/
colcon build
source ~/ros2_ws/install/setup.bash
ros2 launch path_planner_server pathplanner.launch.py
```
When run on real robot, crashes rviz
```
61159914.957 for reason 'Unknown'
terminate called after throwing an instance of 'tf2::ConnectivityException'
  what():  Could not find a connection between 'map' and 'robot_front_laser_link' because they are not part of the same tree.Tf has two or more unconnected trees.
Aborted (core dumped)
```
## Step 4   Navigate programmatically
Run step 3 then in `nav prog` shell run
```
cd ros2_ws/
colcon build
source ~/ros2_ws/install/setup.bash
ros2 launch path_planner_server nav_to_pose_action_client.launch.py
```

In the `send goal` shell, send commands of the form
```
ros2 action send_goal /navigate_to_pose nav2_msgs/action/NavigateToPose "pose: {header: {frame_id: map}, pose: {position: {x: 1.52, y: 1.92, z: 0.0}, orientation:{x: 0.0, y: 0.0, z: 0, w: 1.0000000}}}"
```
