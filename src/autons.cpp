#include "autons.hpp"

namespace auton {

void default_auton() {
    // Set your starting position here if needed
    chassis.setPose(0, 0, 0);

    // Example: turn to 90 degrees
    chassis.turnToHeading(90, 2000, {}, false);
}

} // namespace auton
