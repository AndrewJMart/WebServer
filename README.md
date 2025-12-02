# Simple TCP Client-Server in C

Basic TCP client-server implementation demonstrating Unix socket programming fundamentals.

## Files

- **server.c** - Listens on port 3490 and sends a message to clients
- **client.c** - Connects to server and receives message
- **showip.c** - Resolves and displays IP addresses for a hostname

## Quick Start
```bash
# Compile
gcc server.c -o server
gcc client.c -o client
gcc showip.c -o showip

# Run server
./server

# Run client (in another terminal)
./client localhost 3490

# Lookup IPs
./showip google.com
```

## Features

- IPv4/IPv6 compatible
- TCP stream sockets
- Basic error handling
- Sequential connection handling

## Requirements

- C compiler (gcc/clang)
- Unix-like OS (Linux, macOS, BSD)
