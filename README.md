# Userspace TCP/IP Stack

A custom, high-performance TCP/IP network stack implemented in C. 

This project aims to achieve deterministic microsecond latency by bypassing the Linux kernel's standard networking subsystem. It is designed to serve as the underlying network infrastructure for latency-sensitive applications, operating entirely in userspace through direct hardware polling.

## Architecture & Performance Focus

Standard POSIX sockets rely on hardware interrupts, context switches, and memory copying between kernel and userspace, introducing jitter for high-performance systems. This stack eliminates those bottlenecks through:

1.  **Kernel Bypass:** Takes direct control of the NIC, polling hardware ring buffers on a dedicated CPU core to eliminate interrupt overhead.
2.  **Zero-Copy Memory Model:** Packets are DMA-transferred into pre-allocated memory pools backed by Linux Hugepages. The application logic parses headers and accesses payloads directly at these memory addresses.
3.  **Zero Dynamic Allocation:** The datapath strictly avoids runtime memory allocation. All connection states, ring buffers, and packet pools are initialized at startup to guarantee predictable execution times.

## Protocol Support

* **L2:** Ethernet II, ARP
* **L3:** IPv4, ICMP (Echo)
* **L4:** UDP, TCP (State Machine, Connection Management, Retransmission)

## Development & Build Instructions

*(Instructions to be added once the build system is finalized)*