cmake_minimum_required(VERSION 2.8.3)
project(gazebo_projection_mapping)



#######################################################################################################################
## packages
#######################################################################################################################

set(${PROJECT_NAME}_CATKIN_COMPONENTS
    roscpp
    tf
    gazebo_msgs
    rosconsole
)

find_package(catkin REQUIRED COMPONENTS ${${PROJECT_NAME}_CATKIN_COMPONENTS})



#######################################################################################################################
## catkin specific configuration
#######################################################################################################################


catkin_package(
    INCLUDE_DIRS include
    LIBRARIES
        gpm_tf_to_link_state
    CATKIN_DEPENDS
        ${${PROJECT_NAME}_CATKIN_COMPONENTS}
)



#######################################################################################################################
## build
#######################################################################################################################

#==================
# includes
#==================

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)



#==================
# libraries
#==================

add_library(gpm_tf_to_link_state
    src/tf_to_link_state.cpp
)



#==================
# executables
#==================

add_executable(gpm_tf_to_link_state_node
    src/tf_to_link_state_node.cpp
)



#==================
# library link
#==================

target_link_libraries(gpm_tf_to_link_state
    ${catkin_LIBRARIES}
)

target_link_libraries(gpm_tf_to_link_state_node
    gpm_tf_to_link_state
    ${catkin_LIBRARIES}
)
