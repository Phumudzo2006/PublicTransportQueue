# 🚕 Taxi Queue Simulation System (C++)

A **discrete-time simulation** of a taxi boarding system that models passenger arrivals, waiting queues, dynamic taxi capacities, and boarding delays using **queues and structured data** in C++.

---

## 🧠 Project Overview

This project simulates how passengers are served by taxis on **three different routes** under **time-varying capacity constraints**.

Each passenger:
- Arrives at a specific time
- Belongs to a route (S, L, or C)
- Requires a fixed boarding time

Each taxi:
- Boards passengers one at a time
- Has a **dynamic capacity** that changes over time
- Departs when full

The simulation prints a **time-step table** showing system state at each moment.

---

## 🛣 Routes Modeled

| Route Code | Description |
|-----------|-------------|
| S | Short Route |
| L | Long Route |
| C | City Route |

Each route has:
- Its own waiting queue
- Its own taxi
- Its own time-based capacity profile

---

## 📂 Input Data

Passenger data is read from a file:

taxiData.txt


### File Format
arrival_time,route_type,boarding_time


Example:
2,S,3
4,L,2
6,C,4


---

## ⏱ Simulation Logic

At **each time unit** the system performs:

1. Read new passenger arrivals
2. Add passengers to route queues
3. Board passengers if taxi is available
4. Decrease boarding time (tick)
5. Load passengers into taxi
6. Dispatch taxi if capacity is reached
7. Print system state

---

## 📊 Dynamic Taxi Capacity

Taxi capacity changes over time to simulate:
- Rush hours
- Low-demand periods
- Operational constraints

Example:
```cpp
vector<int> capS = {5,5,5,4,4,3,3,3,2,2,1,1,0,5,...};
This introduces realistic system behavior instead of fixed assumptions.

🧩 Key Data Structures Used
Structure	Purpose
queue<Passenger>	Waiting passengers per route
struct Passenger	Arrival time, route type, boarding time
struct Taxi	Onboard passengers and boarding state
vector<Passenger>	Stores all input passengers
ifstream	File input handling
🧮 Algorithms & Concepts Demonstrated
Queue-based simulation

Event-driven systems

Time-step iteration

Resource capacity constraints

File parsing and validation

Memory management (new / delete)

Formatted tabular output

🖥 Sample Output (Simplified)
T    next                     S         L         C         WQS         WQL            WQC         CS  CL CC
0    S0(2)                    S0(2)                                     4   5  5
1                              S0(1)
2    L2(1)                              L2(1)
3    C3(2)                                        C3(2)
Each row shows:

Current time

New arrivals

Currently boarding passengers

Waiting queues

Available seats per taxi

▶ How to Compile & Run
Compile
g++ main.cpp -o taxi_sim
Run
./taxi_sim
⚠️ Ensure the input file path is correct:

"C:\\data\\taxiData.txt"
(Change this if running on Linux or macOS.)

🎯 Learning Outcomes
This project demonstrates:

Practical use of queues

Simulation of real-world systems

Structured program design

Time-based system modeling

File-based input processing

🚀 Possible Extensions
Remove hardcoded file path

Add statistics (average wait time)

Replace static capacities with AI prediction

Visualize simulation output

Support more routes dynamically

👨‍💻 Author
Phumudzo Matshaya

🤖 AI Assistance Disclosure
AI tools were used to assist with:

Queue-based simulation logic

File parsing techniques

Output formatting

📜 License
This project is open for educational and learning purposes.


---

🔥 This one is **excellent for showing data structures + simulation skills** on GitHub.

If you want, next we can:
- clean memory usage (`unique_ptr`)
- refactor into classes
- or write a **combined portfolio README** listing *all* your projects

Just say 👌
