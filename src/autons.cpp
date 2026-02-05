#include "autons.hpp"

#include "lemlib/lemlib.hpp"

namespace auton {

void default_auton() {
    // Set your starting position here if needed
    odom.setPose({0_in, 0_in, 0_stDeg});

    // Example: turn to 90 degrees
    lemlib::turnTo(90_stDeg, 2_sec, {}, {});
}

} // namespace auton
