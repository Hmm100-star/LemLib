#pragma once

#include "main.h"

#include "lemlib/config.hpp"
#include "lemlib/tracking/TrackingWheelOdom.hpp"
#include "hardware/IMU/V5InertialSensor.hpp"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"

extern pros::Controller master;

// Drive motors (defined in lemlib/config.cpp via config.hpp externs)
// extern lemlib::MotorGroup left_motors;
// extern lemlib::MotorGroup right_motors;

// Sensors
extern lemlib::V5InertialSensor imu;
extern lemlib::TrackingWheel vertical_tracker;
extern lemlib::TrackingWheel horizontal_tracker;
extern lemlib::TrackingWheelOdometry odom;

// Subsystems
extern pros::MotorGroup intake;
extern pros::adi::Pneumatics matchloader;
extern pros::adi::Pneumatics double_state;

// Helpers
void calibrate_sensors();
void start_odometry();
void set_pose(units::Pose pose);
void drive_arcade();
