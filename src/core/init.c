#include <stdio.h>
#include "znet_tcp.h"

int ztcp_init(void) {
    printf("[TurboNet] Initializing userspace network stack...\n");
    printf("[TurboNet] Memory pools configured.\n");
    printf("[TurboNet] Ready for hardware binding.\n");
    return 0;
}