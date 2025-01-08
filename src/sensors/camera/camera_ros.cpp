#include "godot_ros/sensors/camera/camera_ros.hpp"

CameraRos::CameraRos()
{
    try{
        rclcpp::init(0, nullptr);
    } catch (...) {}
}

CameraRos::~CameraRos()
{
    rclcpp::shutdown();
}

void CameraRos::init(const String &node_name, const String &topic_name, const String &frame_id)
{
    node_name_ = node_name;
    topic_name_ = topic_name;
    frame_id_ = frame_id;

    m_node = std::make_shared<rclcpp::Node>(node_name_.utf8().get_data());
    rclcpp::QoS qos(rclcpp::KeepLast(7));
    m_pub = m_node->create_publisher<sensor_msgs::msg::Image>(topic_name_.utf8().get_data(), qos);
}

void CameraRos::publish(const Ref<Image> &img)
{
    if (!m_pub)
    {
        std::cerr << "Publisher is not initialized." << std::endl;
        return;
    }

    m_msg = std::make_unique<sensor_msgs::msg::Image>();
    m_msg->header.frame_id = frame_id_.utf8().get_data();
    m_msg->height = img->get_height();
    m_msg->width = img->get_width();

    m_msg->encoding = "rgb8";
    m_msg->is_bigendian = false;
    m_msg->step = img->get_data().size() / m_msg->height;
    m_msg->data.resize(img->get_data().size());

    std::memcpy(&m_msg->data[0], img->get_data().ptrw(), img->get_data().size());

    m_pub->publish(std::move(m_msg));
}

void CameraRos::spin_some()
{
    rclcpp::spin_some(m_node);
}

void CameraRos::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("init", "node_name", "topic_name", "frame_id"), &CameraRos::init);
    ClassDB::bind_method(D_METHOD("publish", "img"), &CameraRos::publish);
    ClassDB::bind_method(D_METHOD("spin_some"), &CameraRos::spin_some);
}