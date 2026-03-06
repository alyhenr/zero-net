#include <stdio.h>
#include "znet_tcp.h"

int main(void) {
    printf("Starting application...\n");
    
    if (ztcp_init() != 0) {
        fprintf(stderr, "Failed to initialize ZeroNet.\n");
        return 1;
    }
    test_mempool();
    printf("Application running with custom network stack.\n");
    return 0;
}