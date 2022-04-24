#include "controller/Controller.h"

int main()
{
    controller::Controller controller;
    controller.init();  // print start logo and keys info
    controller.start();
    controller.finalize();  // print score
    return 0;
}