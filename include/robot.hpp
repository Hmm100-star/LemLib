#pragma once

#include "main.h"

#include "lemlib/api.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"

extern pros::Controller master;

// Drivetrain
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;
extern pros::Imu imu;
extern lemlib::Chassis chassis;

// Subsystems
extern pros::MotorGroup intake;
extern pros::adi::Pneumatics matchloader;
extern pros::adi::Pneumatics double_state;
