# Product Requirements Document: Userspace TCP/IP Stack

## 1. Objective
To design and implement a custom, high-performance userspace TCP/IP network stack in C. The system must bypass the standard Linux kernel network stack to achieve deterministic, microsecond-level latency and high-throughput packet processing, suitable for latency-critical applications such as financial order matching engines.

## 2. System Architecture
The stack will operate entirely in userspace. It will take direct control of the Network Interface Card (NIC) memory rings via Direct Memory Access (DMA).



### Core Design Principles:
* **Kernel Bypass:** Utilization of a polling mechanism on dedicated CPU cores, completely avoiding hardware interrupts and kernel context switches.
* **Zero-Copy Processing:** Packets are read from and written to pre-allocated hugepage memory. The application processes the payload directly from the DMA buffer without intermediate memory copying (`memcpy`).
* **Zero Dynamic Allocation:** All memory required for packet buffers, connection states, and routing tables must be pre-allocated during the initialization phase. Functions like `malloc` or `calloc` are strictly forbidden in the datapath.
* **Lock-Free Structures:** Concurrency (if implemented) will rely on single-writer/single-reader ring buffers and atomic operations to avoid mutex contention.

## 3. Scope of Implementation

### Phase 1: Data Link Layer (Layer 2)
* Raw Ethernet frame reception and transmission.
* MAC address filtering.
* Address Resolution Protocol (ARP) implementation (request and reply).

### Phase 2: Network Layer (Layer 3)
* IPv4 header parsing and validation (checksum verification).
* Internet Control Message Protocol (ICMP) for Echo Request/Reply (Ping).
* Basic static routing table implementation.

### Phase 3: Transport Layer (Layer 4)
* **UDP:** Connectionless datagram transmission and reception.
* **TCP:** * Connection management (Three-way handshake, connection termination).
    * State machine implementation (RFC 793).
    * Sequence number tracking and acknowledgment.
    * Basic retransmission mechanism.

## 4. Non-Goals (Out of Scope for V1)
* IPv6 support.
* Complex TCP Congestion Control algorithms (e.g., CUBIC, BBR).
* IP fragmentation and reassembly.
* Dynamic routing protocols (BGP, OSPF).
* Multithreaded TCP connection handling (the initial architecture will pin one stack instance to one core).