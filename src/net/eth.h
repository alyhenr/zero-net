#ifndef ZNET_ETH_H
#define ZNET_ETH_H

#include <stdint.h>

#define ETH_ALEN 6 // Length of a MAC address in bytes

// EtherTypes in Network Byte Order
// Note: We define them in Host Byte Order here, you must convert them when comparing!
#define ETH_P_IPV4 0x0800 
#define ETH_P_ARP  0x0806 
#define ETH_P_IPV6 0x86DD

// TODO 1: Define the Ethernet Header Struct
// It must contain: Destination MAC, Source MAC, and EtherType.
// It MUST be exactly 14 bytes in memory. Apply the packed attribute.
struct  __attribute__((packed)) eth_hdr {
    uint8_t* mac_dest[ETH_ALEN];
    uint8_t* mac_src[ETH_ALEN];
    short ether_type;
};

void eth_rcv(uint8_t *frame, uint32_t len);

#endif // ZNET_ETH_H