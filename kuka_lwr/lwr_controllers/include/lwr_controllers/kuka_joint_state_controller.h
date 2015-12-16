#ifndef LWR_CONTROLLERS__KUKA_JOINT_STATE_CONTROLLER_H_
#define LWR_CONTROLLERS__KUKA_JOINT_STATE_CONTROLLER_H_

#include <controller_interface/controller.h>
#include <hardware_interface/joint_state_interface.h>
#include <pluginlib/class_list_macros.h>
#include <sensor_msgs/JointState.h>
#include <geometry_msgs/Pose.h>
#include <realtime_tools/realtime_publisher.h>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include "KinematicChainControllerBase.h"


namespace lwr_controllers{

class KUKAJointStateController : public controller_interface::KinematicChainControllerBase<hardware_interface::JointStateInterface> {

public:

    KUKAJointStateController() : publish_rate_(0.0) {}

    virtual bool init(hardware_interface::JointStateInterface* hw,
                      ros::NodeHandle&                         root_nh,
                      ros::NodeHandle&                         controller_nh);
    virtual void starting(const ros::Time& time);
    virtual void update(const ros::Time& time, const ros::Duration& period);
    virtual void stopping(const ros::Time&);

private:

    std::vector<hardware_interface::JointStateHandle> joint_state_;
    boost::shared_ptr<realtime_tools::RealtimePublisher<sensor_msgs::JointState> > realtime_pub_;
    boost::shared_ptr<realtime_tools::RealtimePublisher<geometry_msgs::Pose> > realtime_pose_pub_;
    ros::Time last_publish_time_;
    double publish_rate_;
    unsigned int num_hw_joints_;
    void addExtraJoints(const ros::NodeHandle& nh, sensor_msgs::JointState& msg);

    boost::scoped_ptr<KDL::ChainFkSolverPos_recursive> fk_pos_solver_;
    KDL::Frame x_;		//current pose
    KDL::JntArray K_, D_;


    std::vector<hardware_interface::JointStateInterface::ResourceHandleType> joint_handles_stiffness;


};

}

#endif