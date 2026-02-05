#include "main.h"

#include "autons.hpp"
#include "robot.hpp"
#include "pros/llemu.hpp"

void initialize() {
    pros::lcd::initialize();

    chassis.calibrate();

    static pros::Task screen_task([] {
        while (true) {
            const auto pose = chassis.getPose();
            pros::lcd::print(0, "X: %f", pose.x);
            pros::lcd::print(1, "Y: %f", pose.y);
            pros::lcd::print(2, "Theta: %f", pose.theta);
            pros::delay(50);
        }
    });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    auton::default_auton();
}

void opcontrol() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

    while (true) {
        const int throttle = master.get_analog(ANALOG_LEFT_Y);
        const int turn = master.get_analog(ANALOG_RIGHT_X);
        chassis.arcade(throttle, turn);

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
