#include "bbattery.h"
#include "gdef.h"
#include "swrite.h"

int main(void) {
    swrite_Basic = FALSE;
    bbattery_RabbitFile("vax.bin", 1048576);
    return 0;
}
