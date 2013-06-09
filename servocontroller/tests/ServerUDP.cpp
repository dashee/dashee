
#include "Server/UDP.h"

int main(void)
{
    Server_UDP s(2047);

    s.read(10);

    return 0;
}
