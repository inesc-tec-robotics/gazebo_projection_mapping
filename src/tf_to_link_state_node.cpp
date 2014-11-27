/**\file tf_to_link_state_node.cpp
 * \brief Description...
 *
 * @version 1.0
 * @author Carlos Miguel Correia da Costa
 */

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <includes>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include <ros/ros.h>
#include <gazebo_projection_mapping/tf_to_link_state.h>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </includes>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



// ###################################################################################   <main>   ##############################################################################
int main(int argc, char** argv) {
	ros::init(argc, argv, "gpm_tf_to_link_state");

	ros::NodeHandlePtr node_handle(new ros::NodeHandle());
	ros::NodeHandlePtr private_node_handle(new ros::NodeHandle("~"));

	gazebo_projection_mapping::TFToLinkState tf_to_link_state;
	tf_to_link_state.setupConfigurationFromParameterServer(node_handle, private_node_handle);
	tf_to_link_state.publishLinkStateFromTF();

	return 0;
}
// ###################################################################################   </main>   #############################################################################
