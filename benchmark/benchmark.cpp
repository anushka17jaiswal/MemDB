#include "../include/Database.h"

#include <chrono>
#include <iostream>

int main()
{
    Database db;

    const int OPERATIONS = 1000000;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < OPERATIONS; i++)
    {
        db.set("key" + std::to_string(i),
               "value" + std::to_string(i));
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    double opsPerSecond = OPERATIONS / elapsed.count();

    std::cout << "========== MemDB Benchmark ==========\n\n";

    std::cout << "SET Benchmark\n";
    std::cout << "Operations : " << OPERATIONS << "\n";
    std::cout << "Time       : " << elapsed.count() << " seconds\n";
    std::cout << "Throughput : " << opsPerSecond << " ops/sec\n";

    auto getStart = std::chrono::high_resolution_clock::now();

for (int i = 0; i < OPERATIONS; i++)
{
    db.get("key" + std::to_string(i));
}

auto getEnd = std::chrono::high_resolution_clock::now();

std::chrono::duration<double> getElapsed = getEnd - getStart;

double getOps = OPERATIONS / getElapsed.count();

std::cout << "\nGET Benchmark\n";
std::cout << "Operations : " << OPERATIONS << "\n";
std::cout << "Time       : " << getElapsed.count() << " seconds\n";
std::cout << "Throughput : " << getOps << " ops/sec\n";

auto delStart = std::chrono::high_resolution_clock::now();

for (int i = 0; i < OPERATIONS; i++)
{
    db.del("key" + std::to_string(i));
}

auto delEnd = std::chrono::high_resolution_clock::now();

std::chrono::duration<double> delElapsed = delEnd - delStart;

double delOps = OPERATIONS / delElapsed.count();

std::cout << "\nDEL Benchmark\n";
std::cout << "Operations : " << OPERATIONS << "\n";
std::cout << "Time       : " << delElapsed.count() << " seconds\n";
std::cout << "Throughput : " << delOps << " ops/sec\n";
    return 0;
}