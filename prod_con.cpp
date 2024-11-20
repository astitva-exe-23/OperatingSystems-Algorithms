#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <string>

// Global condition variables and mutexes
std::condition_variable empty, full;
std::mutex mu_c, mu_p;
std::mutex mcout;

// Function to print messages to stdout with synchronization
void print2stdout(const std::string& msg) {
    if (!msg.empty()) {
        std::unique_lock<std::mutex> lck(mcout);
        std::cout << msg << std::endl;
    }
}

// OrderBuf class that manages the order buffer
class OrderBuf {
    int order_num;                // Tracks the current number of orders
    int ORDER_BUFFER[10];          // Fixed size buffer for orders

public:
    OrderBuf() : order_num(0) {}   // Constructor to initialize order number

    // Add a new order to the buffer
    void AddOrder(int order_id) {
        if (order_num < 10) {
            ORDER_BUFFER[order_num++] = order_id;
        }
    }

    // Remove an order from the buffer
    void RemoveOrder() {
        if (order_num > 0) {
            order_num--;
        }
    }

    // Get the current number of orders in the buffer
    int CurOrders() const {
        return order_num;
    }

    // Get the maximum capacity of the buffer
    int MaxSize() const {
        return 10;
    }
};

// Function representing the cook thread
void cook(OrderBuf& ordr) {
    while (true) {
        std::unique_lock<std::mutex> lck(mu_c);

        // Wait if the buffer is full
        while (ordr.CurOrders() == ordr.MaxSize()) {
            full.wait(lck);
            print2stdout("Maximum Order produced! Waiting for supplier to serve.");
        }

        // Produce an order and add it to the buffer
        print2stdout("Cook produced an Order.");
        ordr.AddOrder(static_cast<int>(rand() % 1000));

        // Simulate cooking time
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Notify that there is a new order for the supplier
        empty.notify_all();
    }
}

// Function representing the supplier thread
void supplier(OrderBuf& ordr) {
    while (true) {
        std::unique_lock<std::mutex> lck(mu_c);

        // Wait if there are no orders to supply
        while (ordr.CurOrders() == 0) {
            print2stdout("No Order to supply! Waiting for cook to produce.");
            empty.wait(lck);
        }

        // Serve an order
        print2stdout("Supplier has served one order.");
        ordr.RemoveOrder();

        // Simulate serving time
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        // Notify that there is space for new orders
        full.notify_all();
    }
}

int main() {
    // Create the shared order buffer
    OrderBuf Orders;

    // Create and start consumer (supplier) and producer (cook) threads
    std::thread consumer(supplier, std::ref(Orders));
    std::thread producer(cook, std::ref(Orders));

    // Wait for both threads to finish execution
    consumer.join();
    producer.join();

    return 0;
}
