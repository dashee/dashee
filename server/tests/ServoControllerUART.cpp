
#include "ServoController/UART.h"

int main(void)
{
    ServoController_UART s("/dev/ttyAMA0");

    Log::info(1, "Error: %d", s.getError());

    s.setTarget(1, 25);
    Log::info(1, "Target 25: %d", s.getTarget(1));

    s.setTarget(1, 50);
    Log::info(1, "Target 50: %d", s.getTarget(1));
    
    s.setTarget(1, 75);
    Log::info(1, "Target 75: %d", s.getTarget(1));

    for (int x = 0; x < 100; x++)
    {
        s.setTarget(1, x+1);
        Log::info(1, "Target %d: %d", x+1, s.getTarget(1));
    }

    return 0;
}
