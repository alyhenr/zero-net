#include <stdio.h>
#include <arpa/inet.h> // For ntohs()
#include "net/eth.h"

// TODO 3: Implement a helper function to format and print MAC addresses
// A MAC address is an array of 6 bytes. Print it as XX:XX:XX:XX:XX:XX
static void print_mac(const uint8_t *mac) {
    // ... your implementation here
    printf("%x\n", *mac);
}


// TODO 2: Implement the receive function
// This function will take a raw byte array (the packet) and its length.
// It should cast the byte array to an eth_hdr, print the Source and Destination MACs,
// and print the EtherType (identifying if it's IPv4 or ARP).
void eth_rcv(uint8_t *frame, uint32_t len) {
    printf("[Lenght of frame]: %d\n", len);
    struct eth_hdr e;
    // TODO 4: Cast the 'frame' pointer to your 'struct eth_hdr'
    for (int i = 0; i < ETH_ALEN; ++i) {
        e.mac_dest[(ETH_ALEN-1) - i] = &frame[i];
    }
    
    for (int i = ETH_ALEN; i < 2*ETH_ALEN; ++i) {
        e.mac_src[(2*ETH_ALEN - 1) - i] = &frame[i];
    }

    // TODO 5: Print the Source MAC, Destination MAC
    printf("[SOURCE]: \n");
    print_mac(e.mac_src[0]);
    printf("[DESTINATION]: \n");
    print_mac(e.mac_dest[0]);
    // TODO 6: Extract the ethertype. Convert it from Network Byte Order 
    // to Host Byte Order using ntohs(). Print whether it is an IPv4 or ARP packet.
}