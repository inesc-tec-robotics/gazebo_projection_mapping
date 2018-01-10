/**\file tf_to_link_state.cpp
 * \brief Description...
 *
 * @version 1.0
 * @author Carlos Miguel Correia da Costa
 */

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <includes>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include <gazebo_projection_mapping/tf_to_link_state.h>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </includes>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace gazebo_projection_mapping {

// =============================================================================  <public-section>  ============================================================================

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <TFToLinkState-functions>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void TFToLinkState::setupConfigurationFromParameterServer(ros::NodeHandlePtr& node_handle, ros::NodeHandlePtr& private_node_handle) {
	node_handle_ = node_handle;

	private_node_handle->param("tf_source_frame", tf_source_frame_, std::string("camera_link"));
	private_node_handle->param("tf_target_frame", tf_target_frame_, std::string("map"));

	std::string gazebo_reference_frame;
	private_node_handle->param("gazebo_reference_frame", gazebo_reference_frame, std::string("world"));

	std::string gazebo_link_name;
	private_node_handle->param("gazebo_link_name", gazebo_link_name, std::string("camera_link"));

	std::string set_link_state_topic;
	private_node_handle->param("gazebo_set_link_state_topic", set_link_state_topic, std::string("/gazebo/set_link_state"));
	link_state_publisher_ = node_handle->advertise<gazebo_msgs::LinkState>(set_link_state_topic, 10, true);

	double publish_rate;
	private_node_handle->param("publish_rate", publish_rate, 30.0);
	publish_rate_ = ros::Rate(publish_rate);

	link_state_.link_name = gazebo_link_name;
	link_state_.reference_frame = gazebo_reference_frame;
	link_state_.pose.position.x = 0.0;
	link_state_.pose.position.y = 0.0;
	link_state_.pose.position.z = 0.0;
	link_state_.pose.orientation.x = 0.0;
	link_state_.pose.orientation.y = 0.0;
	link_state_.pose.orientation.z = 0.0;
	link_state_.pose.orientation.w = 1.0;
	link_state_.twist.linear.x = 0.0;
	link_state_.twist.linear.y = 0.0;
	link_state_.twist.linear.z = 0.0;
	link_state_.twist.angular.x = 0.0;
	link_state_.twist.angular.y = 0.0;
	link_state_.twist.angular.z = 0.0;
}

void TFToLinkState::publishLinkStateFromTF() {
	while (node_handle_->ok()) {
		tf::StampedTransform transform;
		try {
			tf_listener_.lookupTransform(tf_target_frame_, tf_source_frame_, ros::Time(0), transform);

			if (!state_published_ || link_state_.pose.position.x != transform.getOrigin().getX() ||
					link_state_.pose.position.y != transform.getOrigin().getY() ||
					link_state_.pose.position.z != transform.getOrigin().getZ() ||
					link_state_.pose.orientation.x != transform.getRotation().getX() ||
					link_state_.pose.orientation.y != transform.getRotation().getY() ||
					link_state_.pose.orientation.z != transform.getRotation().getZ() ||
					link_state_.pose.orientation.w != transform.getRotation().getW())
			{
				link_state_.pose.position.x = transform.getOrigin().getX();
				link_state_.pose.position.y = transform.getOrigin().getY();
				link_state_.pose.position.z = transform.getOrigin().getZ();
				link_state_.pose.orientation.x = transform.getRotation().getX();
				link_state_.pose.orientation.y = transform.getRotation().getY();
				link_state_.pose.orientation.z = transform.getRotation().getZ();
				link_state_.pose.orientation.w = transform.getRotation().getW();

				link_state_publisher_.publish(link_state_);
				state_published_ = true;
			}
		} catch (tf::TransformException &ex) {
			ROS_WARN_STREAM_THROTTLE(1, "Couldn't find tf [ " << tf_source_frame_ << " -> " << tf_target_frame_ << " ]");
		}

		publish_rate_.sleep();
	}
}
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </TFToLinkState-functions>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// =============================================================================  </public-section>  ===========================================================================

} /* namespace tf_to_link_state */

