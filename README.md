# 🚀 MemDB

A Redis-inspired multithreaded in-memory key-value database built in Modern C++.

## ✨ Features

- TCP Socket Server
- Multi-threaded Client Handling
- Thread-safe Operations using std::mutex
- In-memory Key-Value Storage
- TTL (Time-To-Live) Support
- LRU (Least Recently Used) Cache Eviction
- File Persistence
- CMake Build Support

## 🛠 Tech Stack

- C++17
- POSIX Sockets
- STL
- std::thread
- std::mutex
- CMake

## 🏗️ Architecture

```text
                  Client (nc)
                        │
                 TCP Socket Server
                        │
                Multi-threaded Server
                        │
               Thread-safe Database
          ┌─────────────┼─────────────┐
          │             │             │
    unordered_map       TTL      LRU Cache
          │
      File Persistence
```
## 📂 Project Structure

```text
MemDB/
├── include/
│   ├── Database.h
│   ├── Server.h
│   └── LRUCache.h
│
├── src/
│   ├── main.cpp
│   ├── Database.cpp
│   ├── Server.cpp
│   ├── LRUCache.cpp
│   └── test_lru.cpp
│
├── build/
├── CMakeLists.txt
├── README.md
└── LICENSE
```
## ⚙️ Build Instructions

### Prerequisites

- C++17 Compiler
- CMake 3.10+
- POSIX-compatible Operating System (Linux/macOS)

### Build

```bash
git clone <your-github-repository-url>

cd MemDB

mkdir build
cd build

cmake ..
make

./memdb
```
## 📡 Supported Commands

| Command | Example | Description |
|---------|---------|-------------|
| `PING` | `PING` | Check if the server is running |
| `SET` | `SET name Anushka` | Store a key-value pair |
| `GET` | `GET name` | Retrieve the value of a key |
| `DEL` | `DEL name` | Delete a key |
| `EXISTS` | `EXISTS name` | Check if a key exists |
| `SIZE` | `SIZE` | Get the total number of keys |
| `CLEAR` | `CLEAR` | Remove all keys from the database |
## 💻 Example Usage

### Start the server

```bash
./memdb
```

### Connect using Netcat

```bash
nc localhost 8080
```

### Example Session

```text
PING
PONG

SET name Anushka
OK

GET name
Anushka

EXISTS name
TRUE

SIZE
1

DEL name
OK

GET name
NULL

CLEAR
OK
```
## 📈 Performance

### Time Complexity

| Operation | Complexity |
|-----------|------------|
| SET | O(1) Average |
| GET | O(1) Average |
| DEL | O(1) Average |
| EXISTS | O(1) Average |
| LRU Update | O(1) |

### Features

- Constant-time average lookup using `std::unordered_map`
- O(1) LRU updates using a doubly linked list + hash map
- Thread-safe request handling using `std::mutex`
- Multi-client support using `std::thread`

## 📈 Performance Benchmark

Benchmarked on Apple Silicon (macOS) using a release build.

| Operation | Throughput |
|-----------|-----------:|
| SET | ~722K ops/sec |
| GET | ~7.69M ops/sec |
| DEL | ~9.05M ops/sec |