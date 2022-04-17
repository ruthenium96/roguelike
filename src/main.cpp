#include "world/Engine.h"
#include <iostream>
#include <algorithm>
#include "common/Command.h"
#include "controller/Controller.h"


int main() {
    controller::Controller controller;
    controller.start();

    return 0;
}