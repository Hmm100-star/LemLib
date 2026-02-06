#include "robot.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

// Drivetrain motors
pros::MotorGroup left_motors({-3, -15, -2}, pros::v5::MotorGears::blue);
pros::MotorGroup right_motors({17, 14, 19}, pros::v5::MotorGears::blue);

// IMU
pros::Imu imu(1);

// Drivetrain settings
constexpr float kTrackWidth = 13.0f; // inches (measure this)
constexpr float kWheelDiameter = lemlib::Omniwheel::NEW_4; // inches
constexpr float kDrivetrainRpm = 600.0f;
constexpr float kHorizontalDrift = 2.0f;

lemlib::Drivetrain drivetrain(&left_motors, &right_motors, kTrackWidth, kWheelDiameter, kDrivetrainRpm,
                              kHorizontalDrift);

// Odometry sensors (IMU + tracking wheels)
pros::Rotation vertical_rotation(11, false);
pros::Rotation horizontal_rotation(10, false);
lemlib::TrackingWheel vertical_tracking(&vertical_rotation, 2.0f, 0.0f);
lemlib::TrackingWheel horizontal_tracking(&horizontal_rotation, 2.0f, 1.5f);
lemlib::OdomSensors sensors(&vertical_tracking, nullptr, &horizontal_tracking, nullptr, &imu);

// Controller settings
lemlib::ControllerSettings lateral_controller(10, // kP
                                             0, // kI
                                             3, // kD
                                             3, // anti-windup
                                             1, // small error range (in)
                                             100, // small error timeout (ms)
                                             3, // large error range (in)
                                             500, // large error timeout (ms)
                                             20 // max accel (slew)
);

lemlib::ControllerSettings angular_controller(2, // kP
                                             0, // kI
                                             10, // kD
                                             3, // anti-windup
                                             1, // small error range (deg)
                                             100, // small error timeout (ms)
                                             3, // large error range (deg)
                                             500, // large error timeout (ms)
                                             0 // max accel (slew)
);

// Chassis
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);

// Subsystems
pros::MotorGroup intake({18, -13}, pros::v5::MotorGears::blue);
pros::adi::Pneumatics matchloader('A', false);
pros::adi::Pneumatics double_state('C', false);
