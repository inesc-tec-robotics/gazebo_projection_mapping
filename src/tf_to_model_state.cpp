/**\file tf_to_model_state.cpp
 * \brief Description...
 *
 * @version 1.0
 * @author Carlos Miguel Correia da Costa
 */

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <includes>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include <gazebo_projection_mapping/tf_to_model_state.h>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </includes>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace gazebo_projection_mapping {

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <imports>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </imports>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// =============================================================================  <public-section>  ============================================================================
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructor>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructor>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <TFToModelState-functions>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void TFToModelState::setupConfigurationFromParameterServer(ros::NodeHandlePtr& node_handle, ros::NodeHandlePtr& private_node_handle) {
	node_handle_ = node_handle;

	private_node_handle->param("tf_source_frame", tf_source_frame_, std::string("camera_link"));
	private_node_handle->param("tf_target_frame", tf_target_frame_, std::string("map"));

	std::string gazebo_reference_frame;
	private_node_handle->param("gazebo_reference_frame", gazebo_reference_frame, std::string("world"));

	std::string gazebo_model_name;
	private_node_handle->param("gazebo_model_name", gazebo_model_name, std::string("camera_link"));

	std::string set_model_state_topic;
	private_node_handle->param("gazebo_set_model_state_topic", set_model_state_topic, std::string("/gazebo/set_model_state"));
	model_state_publisher_ = node_handle->advertise<gazebo_msgs::ModelState>(set_model_state_topic, 10, true);

	double publish_rate;
	private_node_handle->param("publish_rate", publish_rate, 30.0);
	publish_rate_ = ros::Rate(publish_rate);

	model_state_.model_name = gazebo_model_name;
	model_state_.reference_frame = gazebo_reference_frame;
	model_state_.pose.position.x = 0.0;
	model_state_.pose.position.y = 0.0;
	model_state_.pose.position.z = 0.0;
	model_state_.pose.orientation.x = 0.0;
	model_state_.pose.orientation.y = 0.0;
	model_state_.pose.orientation.z = 0.0;
	model_state_.pose.orientation.w = 1.0;
	model_state_.twist.linear.x = 0.0;
	model_state_.twist.linear.y = 0.0;
	model_state_.twist.linear.z = 0.0;
	model_state_.twist.angular.x = 0.0;
	model_state_.twist.angular.y = 0.0;
	model_state_.twist.angular.z = 0.0;
}

void TFToModelState::publishModelStateFromTF() {
	while (node_handle_->ok()) {
		tf::StampedTransform transform;
		try {
			tf_listener_.lookupTransform(tf_target_frame_, tf_source_frame_, ros::Time(0), transform);

			if (!state_published_ || model_state_.pose.position.x != transform.getOrigin().getX() ||
					model_state_.pose.position.y != transform.getOrigin().getY() ||
					model_state_.pose.position.z != transform.getOrigin().getZ() ||
					model_state_.pose.orientation.x != transform.getRotation().getX() ||
					model_state_.pose.orientation.y != transform.getRotation().getY() ||
					model_state_.pose.orientation.z != transform.getRotation().getZ() ||
					model_state_.pose.orientation.w != transform.getRotation().getW())
			{
				model_state_.pose.position.x = transform.getOrigin().getX();
				model_state_.pose.position.y = transform.getOrigin().getY();
				model_state_.pose.position.z = transform.getOrigin().getZ();
				model_state_.pose.orientation.x = transform.getRotation().getX();
				model_state_.pose.orientation.y = transform.getRotation().getY();
				model_state_.pose.orientation.z = transform.getRotation().getZ();
				model_state_.pose.orientation.w = transform.getRotation().getW();

				model_state_publisher_.publish(model_state_);
				state_published_ = true;
			}
		} catch (tf::TransformException &ex) {
			ROS_WARN_STREAM_THROTTLE(1, "Couldn't find tf [ " << tf_source_frame_ << " -> " << tf_target_frame_ << " ]");
		}

		publish_rate_.sleep();
	}
}

} /* namespace tf_to_model_state */

