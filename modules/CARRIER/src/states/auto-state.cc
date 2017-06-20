#include "auto-state.hh"
using namespace Carrier;

AutoState::AutoState(CarrierController &controller): ICarrierState(controller) {
    controller.getMotorController().forward(controller.getSpeed());
}

void AutoState::update() {
    srand(time(NULL));
    CarrierState next_state;
    for(int i = 0; i < 20; i++) {
        x = rand() % 5;
        next_state = states[x];
        if (next_state == CarrierState::CounterClockwise) {
            controller.getMotorController().left(controller.getSpeed());
            delay(250);
        } else if (next_state == CarrierState::Clockwise) {
            controller.getMotorController().right(controller.getSpeed());
            delay(250);
        } else if (next_state == CarrierState::Forward) {
            if(controller.getSonar() <= )
            controller.getMotorController().forward(controller.getSpeed());
            delay(500);
        } else if (next_state == CarrierState::Backward) {
            controller.getMotorController().backward(controller.getSpeed());
            delay(500);
        } else if (next_state == CarrierState::Idle) {
            controller.getMotorController().stop();
            delay(100);
        }
    }
    controller.getMotorController().stop();
}

CarrierState AutoState::getState() {
    return CarrierState::Auto;
}
