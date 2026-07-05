#include "../include/Database.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

// -------------------- SET / GET --------------------
void testSetGet()
{
    Database db;

    db.set("name", "Anushka");

    assert(db.get("name") == "Anushka");

    cout << "✅ SET/GET Test Passed\n";
}

// -------------------- DELETE --------------------
void testDelete()
{
    Database db;

    db.set("name", "Anushka");

    assert(db.del("name") == true);
    assert(db.get("name") == "NULL");
    assert(db.exists("name") == false);

    cout << "✅ DEL Test Passed\n";
}

// -------------------- EXISTS --------------------
void testExists()
{
    Database db;

    db.set("city", "Raipur");

    assert(db.exists("city") == true);
    assert(db.exists("college") == false);

    cout << "✅ EXISTS Test Passed\n";
}

// -------------------- SIZE --------------------
void testSize()
{
    Database db;

    db.set("A", "1");
    db.set("B", "2");
    db.set("C", "3");

    assert(db.size() == 3);

    cout << "✅ SIZE Test Passed\n";
}

// -------------------- CLEAR --------------------
void testClear()
{
    Database db;

    db.set("A", "1");
    db.set("B", "2");

    db.clear();

    assert(db.size() == 0);
    assert(db.get("A") == "NULL");
    assert(db.get("B") == "NULL");

    cout << "✅ CLEAR Test Passed\n";
}

// -------------------- TTL --------------------
void testTTL()
{
    Database db;

    db.set("temp", "123", 2);

    assert(db.get("temp") == "123");

    this_thread::sleep_for(chrono::seconds(3));

    assert(db.get("temp") == "NULL");

    cout << "✅ TTL Test Passed\n";
}

// -------------------- MAIN --------------------
int main()
{
    cout << "\n========== MemDB Test Suite ==========\n\n";

    testSetGet();
    testDelete();
    testExists();
    testSize();
    testClear();
    testTTL();

    cout << "\n======================================\n";
    cout << "🎉 ALL MEMDB TESTS PASSED!\n";
    cout << "======================================\n";

    return 0;
}