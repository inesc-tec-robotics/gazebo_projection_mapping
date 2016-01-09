gazebo_projection_mapping
=========================

ROS package that uses a Gazebo virtual camera to retrieve an image from a simulated environment that will be displayed in the ambient using a projector.

Note: welding projection requires:
* [Gazebo 7.0.1](https://bitbucket.org/carlosmccosta/gazebo/src/b7557435def9f168eb4c56e665c30af163606b6a/?at=camera_intrinsics) with PR [2058](https://bitbucket.org/osrf/gazebo/pull-requests/2058/added-camera-intrinsics-fx-fy-cx-cy-s/diff)
* [SDFormat](https://bitbucket.org/carlosmccosta/sdformat/src/ae321f916e67edf65997df8aecb4ff6a83504356/?at=camera_intrinsics) with PR [248](https://bitbucket.org/osrf/sdformat/pull-requests/248/added-camera-intrinsics-fx-fy-cx-cy-s/diff)
* [gazebo_ros_pkgs](https://github.com/carlosmccosta/gazebo_ros_pkgs/tree/gazebo-7.0.1-with-camera-intrinsics) with PR [374](https://github.com/ros-simulation/gazebo_ros_pkgs/pull/374) and [375](https://github.com/ros-simulation/gazebo_ros_pkgs/pull/375)


[![Welding projection](http://img.youtube.com/vi/pR6mW5sGbWg/maxresdefault.jpg)](http://www.youtube.com/watch?v=pR6mW5sGbWg)

Video 1: Welding shape projection


[![Welding projection](http://img.youtube.com/vi/DusawLIn3AY/maxresdefault.jpg)](http://www.youtube.com/watch?v=DusawLIn3AY)

Video 2: Welding shape projection with object placement


![Wall projection](docs/wall_projection.jpg "Wall projection")

Figure 1: Wall projection
