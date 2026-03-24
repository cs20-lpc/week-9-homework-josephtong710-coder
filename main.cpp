#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "QueueFactory.hpp"

using namespace std;

// -------------------------------------------------------
// RunTicketCounterSimulation
// -------------------------------------------------------
void RunTicketCounterSimulation() {
    const int MAX_CUSTOMERS = 10;
    const int ITERATIONS    = 100;

    int customerID  = 1;
    int turnedAway  = 0;
    int totalServed = 0;

    cout << "============================================" << endl;
    cout << " SIMULATION 1: Ticket Counter"               << endl;
    cout << " Queue type  : ArrayQueue (circular buffer)" << endl;
    cout << " Max capacity: " << MAX_CUSTOMERS            << endl;
    cout << " Iterations  : " << ITERATIONS               << endl;
    cout << "============================================" << endl;

    Queue<int>* queue = QueueFactory<int>::GetQueue(MAX_CUSTOMERS);

    for (int i = 1; i <= ITERATIONS; i++) {
        double rnd = -1.0 + (2.0 * rand()) / RAND_MAX;

        if (rnd < 0) {
            if (queue->isEmpty()) {
                cout << "Step " << setw(3) << i
                     << " | Serve attempt - queue is empty, skipping"
                     << " | Length: " << queue->getLength() << endl;
            } else {
                int served = queue->front();
                queue->dequeue();
                totalServed++;
                cout << "Step " << setw(3) << i
                     << " | Customer #" << served << " served (dequeued)"
                     << " | Length: " << queue->getLength() << endl;
            }
        } else {
            if (queue->getLength() == MAX_CUSTOMERS) {
                turnedAway++;
                cout << "Step " << setw(3) << i
                     << " | Customer #" << customerID
                     << " TURNED AWAY - queue full"
                     << " | Length: " << queue->getLength()
                     << " | Turned away: " << turnedAway << endl;
                customerID++;
            } else {
                queue->enqueue(customerID);
                cout << "Step " << setw(3) << i
                     << " | Customer #" << customerID << " joined the line (enqueued)"
                     << " | Length: " << queue->getLength() << endl;
                customerID++;
            }
        }
    }

    cout << endl;
    cout << "--- Simulation 1 Summary ---" << endl;
    cout << "  Total arrivals    : " << (customerID - 1)   << endl;
    cout << "  Customers served  : " << totalServed        << endl;
    cout << "  Turned away       : " << turnedAway         << endl;
    cout << "  Remaining in line : " << queue->getLength() << endl;
    cout << endl;

    delete queue;
}

// -------------------------------------------------------
// RunBankSimulation
// -------------------------------------------------------
void RunBankSimulation() {
    const int ITERATIONS = 100;

    int customerID  = 1;
    int totalServed = 0;
    int peakLength  = 0;

    cout << "============================================"     << endl;
    cout << " SIMULATION 2: Bank Service Line"                 << endl;
    cout << " Queue type  : LinkedQueue (singly linked list)"  << endl;
    cout << " Max capacity: unlimited"                         << endl;
    cout << " Iterations  : " << ITERATIONS                    << endl;
    cout << "============================================"     << endl;

    Queue<int>* queue = QueueFactory<int>::GetQueue();

    for (int i = 1; i <= ITERATIONS; i++) {
        double rnd = -1.0 + (3.0 * rand()) / RAND_MAX;

        if (rnd < 0) {
            if (queue->isEmpty()) {
                cout << "Step " << setw(3) << i
                     << " | Serve attempt - queue is empty, skipping"
                     << " | Length: " << queue->getLength() << endl;
            } else {
                int served = queue->front();
                queue->dequeue();
                totalServed++;
                cout << "Step " << setw(3) << i
                     << " | Customer #" << served << " served (dequeued)"
                     << " | Length: " << queue->getLength() << endl;
            }
        } else {
            queue->enqueue(customerID);
            if (queue->getLength() > peakLength)
                peakLength = queue->getLength();
            cout << "Step " << setw(3) << i
                 << " | Customer #" << customerID << " joined the line (enqueued)"
                 << " | Length: " << queue->getLength() << endl;
            customerID++;
        }
    }

    cout << endl;
    cout << "--- Simulation 2 Summary ---" << endl;
    cout << "  Total arrivals    : " << (customerID - 1)   << endl;
    cout << "  Customers served  : " << totalServed        << endl;
    cout << "  Turned away       : 0 (unbounded queue)"    << endl;
    cout << "  Remaining in line : " << queue->getLength() << endl;
    cout << "  Peak queue length : " << peakLength         << endl;
    cout << endl;

    delete queue;
}

// -------------------------------------------------------
// main
// -------------------------------------------------------
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << endl;
    cout << "==========================================" << endl;
    cout << "   Queue Factory -- Two-Simulation Driver" << endl;
    cout << "==========================================" << endl;
    cout << endl;
    cout << "Design rationale:" << endl;
    cout << "  Sim 1 uses ArrayQueue  -- max size is fixed (10),"  << endl;
    cout << "  so a bounded circular buffer is the right choice."  << endl;
    cout << "  Sim 2 uses LinkedQueue -- no cap; line grows as"    << endl;
    cout << "  needed, so an unbounded linked list fits best."     << endl;
    cout << endl;

    RunTicketCounterSimulation();
    RunBankSimulation();

    return 0;
}