#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp> // string message type

// Inheritance => MyClass : public ParentClass
class MyNode : public rclcpp::Node { // MyNode IS A ROS Node
    public:
    MyNode(const std::string& node_name)
    : rclcpp::Node(node_name) 
    {
        m_string_publisher = create_publisher<std_msgs::msg::String>("topic_name",42);
        m_timer = create_wall_timer(std::chrono::seconds(1),std::bind(&MyNode::publish_function,this)); // wall_timer uses system time
    }

    private:
    std::shared_ptr<rclcpp::Publisher<std_msgs::msg::String>> m_string_publisher; // MyNode HAS A publisher object
    std::shared_ptr<rclcpp::TimerBase> m_timer;
    void print_function () {
        std::cout << "Hello ROS! " << std::endl;
    }
    void publish_function () {
        std_msgs::msg::String my_string_message;
        my_string_message.data = "my first message";

        m_string_publisher->publish(my_string_message);
    }
};

int main(int argc, char** argv) {

    rclcpp::init(argc,argv); // Initialize ROS

    // MyNode my_first_node = MyNode("ilo");

    // We always want to use smart pointers in ROS
    std::shared_ptr<MyNode> my_first_node = std::make_shared<MyNode>("ilo"); // shared pointer is a template class where <MyNode> is the template argument
    // Esplicitamente (altrimenti lo fa spin implicitamente)
    //std::shared_ptr<rclcpp::Node> node_name = my_first_node; // Polimorfismo 

    //std::shared_ptr<rclcpp::Node> my_first_node = std::make_shared<MyNode>("ilo");

    rclcpp::spin(my_first_node);

    rclcpp::shutdown(); // Terminate ROS

    return 0;
}