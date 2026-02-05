#include "robot.hpp"

#include "lemlib/config.hpp"
#include "lemlib/util.hpp"

// Set to false if you are not using tracking wheels.
constexpr bool kUseTrackingWheels = false;

pros::Controller master(pros::E_CONTROLLER_MASTER);

// Drivetrain motors (EZ template ports)
lemlib::MotorGroup left_motors({-3, -15, -2}, 600_rpm);
lemlib::MotorGroup right_motors({17, 14, 19}, 600_rpm);

// IMU
lemlib::V5InertialSensor imu(1);

// Tracking wheels (EZ template ports). Offsets are negative for left/back.
lemlib::TrackingWheel vertical_tracker(9, 2.75_in, -4_in); // check
lemlib::TrackingWheel horizontal_tracker(8, 2.75_in, -4_in); // check

const std::vector<lemlib::TrackingWheel*> vertical_wheels =
    kUseTrackingWheels ? std::vector<lemlib::TrackingWheel*>{&vertical_tracker} : std::vector<lemlib::TrackingWheel*>{};
const std::vector<lemlib::TrackingWheel*> horizontal_wheels = kUseTrackingWheels
                                                             ? std::vector<lemlib::TrackingWheel*>{&horizontal_tracker}
                                                             : std::vector<lemlib::TrackingWheel*>{};

lemlib::TrackingWheelOdometry odom({&imu}, vertical_wheels, horizontal_wheels);

// Subsystems
pros::MotorGroup intake({18, -13}, pros::v5::MotorGears::blue);
pros::adi::Pneumatics matchloader('A', false); 
pros::adi::Pneumatics double_state('C', false);

// Lemlib default motion config
const lemlib::PID angular_pid(0.05, 0.0, 0.0);
const lemlib::PID lateral_pid(0.05, 0.0, 0.0);

const lemlib::ExitConditionGroup<AngleRange> angular_exit_conditions({
    lemlib::ExitCondition<AngleRange>(1_stDeg, 250_msec),
});

const lemlib::ExitConditionGroup<Length> lateral_exit_conditions({
    lemlib::ExitCondition<Length>(1_in, 250_msec),
});

const Length track_width = 10_in;  // TODO: measure your track width
const Number drift_compensation = 2;
const Number angular_slew = 0;
const Number lateral_slew = 0;

const std::function<units::Pose()> pose_getter = [] { return odom.getPose(); };

void calibrate_sensors() {
    imu.calibrate();
    while (imu.isCalibrating()) {
        pros::delay(10);
    }

    if (kUseTrackingWheels) {
        vertical_tracker.reset();
        horizontal_tracker.reset();
    }
}

void start_odometry() {
    odom.startTask();
}

void set_pose(units::Pose pose) {
    odom.setPose(pose);
}

void drive_arcade() {
    const int throttle = master.get_analog(ANALOG_LEFT_Y);
    const int turn = master.get_analog(ANALOG_RIGHT_X);

    const Number throttle_pct = static_cast<double>(throttle) / 127.0;
    const Number turn_pct = static_cast<double>(turn) / 127.0;

    const auto outputs = lemlib::desaturate(throttle_pct, turn_pct);
    left_motors.move(outputs.left);
    right_motors.move(outputs.right);
}
