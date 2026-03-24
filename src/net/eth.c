#include <stdio.h>
#include <arpa/inet.h> // For ntohs()
#include "net/eth.h"

// TODO 3: Implement a helper function to format and print MAC addresses
// A MAC address is an array of 6 bytes. Print it as XX:XX:XX:XX:XX:XX
static void print_mac(const uint8_t *mac) {
    for (int i = 0; i < ETH_ALEN; i++) {
        printf("%02x%s", mac[i], (i < 5) ? ":" : "");
    }
    printf("\n");
}



// TODO 2: Implement the receive function
// This function will take a raw byte array (the packet) and its length.
// It should cast the byte array to an eth_hdr, print the Source and Destination MACs,
// and print the EtherType (identifying if it's IPv4 or ARP).
void eth_rcv(uint8_t *frame, uint32_t len) {
    if (len < sizeof(struct eth_hdr)) return; // Safety check

    struct eth_hdr *e = (struct eth_hdr *)frame;

    printf("[SOURCE]: ");
    print_mac(e->mac_src); // Pass the pointer, not one byte

    printf("[DESTINATION]: ");
    print_mac(e->mac_dest);

    // TODO 6: EtherType
    uint16_t ethertype = ntohs(e->ether_type);
    if (ethertype == ETH_P_IPV4) {
        printf("Packet: IPv4\n");
    } else if (ethertype == ETH_P_ARP) {
        printf("Packet: ARP\n");
    }
}