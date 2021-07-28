#include <gtest/gtest.h>
#include "pose2d.hpp"
#include "control/model_f_euler_dis.hpp"
#include "control/position_controller.hpp"
#include "vel_commands.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <mutex> // proteggere accesso ad un'area di dati condivisa

void dummy_fct(){
    std::cout<<"1"<<std::endl;
    std::cout<<"2"<<std::endl;
    std::cout<<"3"<<std::endl;
}

void controller_thread_fct(double goal_x, double goal_y, std::shared_ptr<Pose2D> robot_pose, PosCtrl pos_controller, std::shared_ptr<VelCommands> input_signal, std::shared_ptr<std::mutex> ctrl_mtx, std::shared_ptr<bool> end_task){
    while (true){

        { // This defines the scope of the variables inside this area. e.g. locker, which is what we want
            std::unique_lock<std::mutex> locker (*ctrl_mtx);

            double e_x = robot_pose->x - goal_x;
            double e_y = robot_pose->y - goal_y;

            if (std::abs(e_x) <= 1e-3 && std::abs(e_y) <= 1e-3){
                *end_task = true;
                break;
            }

            *input_signal = pos_controller.input_function(e_x, e_y, *robot_pose);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(15)); // sleep for 10 ms starting from here
    }
}

void integration_thread_fct(std::shared_ptr<Pose2D> robot_pose, KinModel unicycle, double delta_time, std::shared_ptr<VelCommands> input_signal, std::shared_ptr<std::mutex> ctrl_mtx, std::shared_ptr<bool> end_task){
    while (true){

        {
            std::unique_lock<std::mutex> locker (*ctrl_mtx);

            if (*end_task) {
                break;
            }

            *robot_pose = unicycle.integration(input_signal->v, input_signal->omega, delta_time);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // sleep for delta_t*1000 ms starting from here
    }
}

TEST(test_posctrl_mt, simple_threads)
{
    
    std::thread a = std::thread(dummy_fct); // The constructor takes a function as input (which needs to return void)
    // The thread dies when the function ends

    std::thread b = std::thread(dummy_fct);

    a.join(); // stops the execution of the current thread until the "a" thread is not over
    b.join();

    EXPECT_TRUE(false);
}

TEST(test_posctrl_mt, pos_control_mt)
{
    double delta_time = 0.01;  // [s]
    double len = 0.5;       // [m]
    double gain_x = 1;
    double gain_y = 1;
    Pose2D initial_pose = {0, 0, 0};
    double goal_x = 10;
    double goal_y = 10;

    KinModel unicycle = KinModel(initial_pose);
    PosCtrl pos_controller = PosCtrl(len, gain_x, gain_y);
    std::shared_ptr<Pose2D> robot_pose = std::make_shared<Pose2D>(initial_pose);
    std::shared_ptr<VelCommands> input_signal = std::make_shared<VelCommands>();
    std::shared_ptr<std::mutex> ctrl_mtx = std::make_shared<std::mutex>(); // mutex takes no arguments in the constructor
    std::shared_ptr<bool> end_task = std::make_shared<bool>(false);

    std::thread a = std::thread(controller_thread_fct, goal_x, goal_y, robot_pose, pos_controller, input_signal, ctrl_mtx, end_task);

    std::thread b = std::thread(integration_thread_fct, robot_pose, unicycle, delta_time, input_signal, ctrl_mtx, end_task);

    a.join();
    b.join();

    std::cout << *robot_pose << std::endl;
    std::cout << *input_signal << std::endl;

    EXPECT_TRUE(false);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}