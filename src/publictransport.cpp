#include <iostream>
#include <fstream>
#include <queue>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Passenger structure
struct Passenger {
    int arrivalTime;
    char routeType; // S, L, or C
    int boardingTime;

    Passenger(int t, char r, int b) : arrivalTime(t), routeType(r), boardingTime(b) {}
};

// Taxi structure
struct Taxi {
    queue<Passenger> onboard;
    Passenger* currentPassenger = nullptr;
    int remainingTime = 0;

    void boardPassenger(Passenger p) {
        currentPassenger = new Passenger(p);
        remainingTime = p.boardingTime;
    }

    void tick() {
        if (currentPassenger != nullptr) {
            remainingTime--;
            if (remainingTime == 0) {
                onboard.push(*currentPassenger);
                delete currentPassenger;
                currentPassenger = nullptr;
            }
        }
    }

    bool isFull(int dynamicCapacity) const {
        return onboard.size() + (currentPassenger != nullptr ? 1 : 0) >= dynamicCapacity;
    }

    void clearTaxi() {
        while (!onboard.empty()) onboard.pop();
    }

    int availableSeats(int dynamicCapacity) const {
        return dynamicCapacity - onboard.size() - (currentPassenger != nullptr ? 1 : 0);
    }
};

// Helper function to print passenger info
string formatPassenger(Passenger* p) {
    if (p == nullptr) return "";
    return string(1, p->routeType) + to_string(p->arrivalTime) + "(" + to_string(p->boardingTime) + ")";
}

string formatQueue(queue<Passenger> q) {
    stringstream ss;
    while (!q.empty()) {
        Passenger p = q.front(); q.pop();
        ss << p.routeType << p.arrivalTime << "(" << p.boardingTime << ") ";
    }
    return ss.str();
}

int main() {
    ifstream file("C:\\data\\taxiData.txt");
    if (!file.is_open()) {
        cout << "Error opening file: Cannot open file." << endl;
        return 1;
    }

    // Queues for each route
    queue<Passenger> qS, qL, qC;

    // Taxis for each route
    Taxi taxiS, taxiL, taxiC;

    // Read all data from file into a vector
    vector<Passenger> passengers;
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string timeStr, routeStr, boardStr;

        if (!getline(ss, timeStr, ',')) continue;
        if (!getline(ss, routeStr, ',')) continue;
        if (!getline(ss, boardStr, ',')) continue;

        try {
            int time = stoi(timeStr);
            char route = toupper(routeStr[0]);
            int boarding = stoi(boardStr);
            if (route == 'S' || route == 'L' || route == 'C')
                passengers.emplace_back(time, route, boarding);
        } catch (...) {
            cerr << "Skipping invalid line: " << line << endl;
        }
    }

    file.close();

    // Time-based capacities per route
    vector<int> capS = {5,5,5,4,4,3,3,3,2,2,1,1,0,5,5,5,5,4,4,4,3,3};
    vector<int> capL = {5,5,5,5,5,4,4,4,4,4,3,3,3,3,2,2,2,2,2,2,2,2};
    vector<int> capC = {5,5,5,4,4,3,3,3,2,2,1,1,1,1,1,1,0,5,4,4,3,3};

    int currentTime = 0;
    int maxTime = 30; // Adjust if needed

    cout << left << setw(5) << "T" << setw(25) << "next"
         << setw(10) << "S" << setw(10) << "L" << setw(10) << "C"
         << setw(12) << "WQS" << setw(20) << "WQL" << setw(12) << "WQC"
         << setw(6) << "CS" << setw(6) << "CL" << "CC" << endl;

    while (currentTime <= maxTime) {
        // Get capacities for current time
        int cap_s = (currentTime < capS.size()) ? capS[currentTime] : 5;
        int cap_l = (currentTime < capL.size()) ? capL[currentTime] : 5;
        int cap_c = (currentTime < capC.size()) ? capC[currentTime] : 5;

        // Process new arrivals
        string next = "";
        for (auto& p : passengers) {
            if (p.arrivalTime == currentTime) {
                next += p.routeType + to_string(p.arrivalTime) + "(" + to_string(p.boardingTime) + ") ";
                if (p.routeType == 'S') qS.push(p);
                else if (p.routeType == 'L') qL.push(p);
                else if (p.routeType == 'C') qC.push(p);
            }
        }

        // Boarding logic for each route
        if (taxiS.currentPassenger == nullptr && !qS.empty() && !taxiS.isFull(cap_s)) {
            taxiS.boardPassenger(qS.front());
            qS.pop();
        }
        if (taxiL.currentPassenger == nullptr && !qL.empty() && !taxiL.isFull(cap_l)) {
            taxiL.boardPassenger(qL.front());
            qL.pop();
        }
        if (taxiC.currentPassenger == nullptr && !qC.empty() && !taxiC.isFull(cap_c)) {
            taxiC.boardPassenger(qC.front());
            qC.pop();
        }

        // Tick: process current boarding
        taxiS.tick();
        taxiL.tick();
        taxiC.tick();

        // Check for full taxis and depart
        if (taxiS.isFull(cap_s)) taxiS.clearTaxi();
        if (taxiL.isFull(cap_l)) taxiL.clearTaxi();
        if (taxiC.isFull(cap_c)) taxiC.clearTaxi();

        // Output simulation row
        cout << left << setw(5) << currentTime
             << setw(25) << next
             << setw(10) << formatPassenger(taxiS.currentPassenger)
             << setw(10) << formatPassenger(taxiL.currentPassenger)
             << setw(10) << formatPassenger(taxiC.currentPassenger)
             << setw(12) << formatQueue(qS)
             << setw(20) << formatQueue(qL)
             << setw(12) << formatQueue(qC)
             << setw(6) << taxiS.availableSeats(cap_s)
             << setw(6) << taxiL.availableSeats(cap_l)
             << taxiC.availableSeats(cap_c)
             << endl;

        currentTime++;
        if (passengers.back().arrivalTime + 20 < currentTime) break; // safety stop
    }

    return 0;
}
