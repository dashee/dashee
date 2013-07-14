
#include "Server/UDP.h"

int main(void)
{
    ServerUDP s(2047);

    s.read(10);

    return 0;
}
