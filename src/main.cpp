#include "main.h"

#include "autons.hpp"
#include "robot.hpp"
#include "pros/llemu.hpp"

void initialize() {
    pros::lcd::initialize();

    calibrate_sensors();
    start_odometry();

    static pros::Task screen_task([] {
        while (true) {
            const auto pose = odom.getPose();
            pros::lcd::print(0, "X: %f", to_in(pose.x));
            pros::lcd::print(1, "Y: %f", to_in(pose.y));
            pros::lcd::print(2, "Theta: %f", to_cDeg(pose.orientation));
            pros::delay(50);
        }
    });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    left_motors.setBrakeMode(lemlib::BrakeMode::HOLD);
    right_motors.setBrakeMode(lemlib::BrakeMode::HOLD);

    auton::default_auton();
}

void opcontrol() {
    left_motors.setBrakeMode(lemlib::BrakeMode::BRAKE);
    right_motors.setBrakeMode(lemlib::BrakeMode::BRAKE);

    while (true) {
        drive_arcade();

        const bool intake_in = master.get_digital(DIGITAL_L1) || master.get_digital(DIGITAL_R1);
        const bool intake_out = master.get_digital(DIGITAL_L2) || master.get_digital(DIGITAL_R2);

        if (intake_in) {
            intake.move_velocity(600);
        } else if (intake_out) {
            intake.move_velocity(-600);
        } else {
            intake.move_velocity(0);
        }

        if (master.get_digital(DIGITAL_R1) || master.get_digital(DIGITAL_R2)) {
            double_state.set_value(false);
        } else if (master.get_digital(DIGITAL_L1) || master.get_digital(DIGITAL_L2)) {
            double_state.set_value(true);
        } 

        pros::delay(10);
    }
}
