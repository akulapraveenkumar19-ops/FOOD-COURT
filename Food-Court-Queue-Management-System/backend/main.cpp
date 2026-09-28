#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "Customer.h"
#include "Order.h"
#include "Queue.h"
#include "CircularQueue.h"
#include "PriorityQueue.h"
#include "Deque.h"
#include "Stack.h"
#include "LinkedList.h"

class FoodCourtSystem {
private:
    FoodMenuList menuList;
    CustomerList customerList;
    OrderHistoryList orderHistory;
    Queue normalQueue;
    CircularQueue circularQueue;
    PriorityQueue priorityQueue;
    Deque dequeQueue;
    OrderStack recentOrdersStack;

    int nextCustomerId;
    int nextTokenNumber;
    int nextOrderSeq;

    std::string getTimestamp() const {
        std::time_t now = std::time(nullptr);
        char buf[64];
        std::strftime(buf, sizeof(buf), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
        return std::string(buf);
    }

public:
    FoodCourtSystem()
        : normalQueue(100), circularQueue(15), nextCustomerId(1006), nextTokenNumber(6), nextOrderSeq(1006) {}

    void loadSampleData(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cout << "[INFO] Could not open database file. Initializing default menu...\n";
            initDefaultMenu();
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;

            std::stringstream ss(line);
            std::string type;
            std::getline(ss, type, '|');

            if (type == "FOOD") {
                std::string sId, name, category, sPrice, sAvail;
                std::getline(ss, sId, '|');
                std::getline(ss, name, '|');
                std::getline(ss, category, '|');
                std::getline(ss, sPrice, '|');
                std::getline(ss, sAvail, '|');

                int id = std::stoi(sId);
                double price = std::stod(sPrice);
                bool avail = (sAvail == "1");
                menuList.addFoodItem(FoodItem(id, name, category, price, avail));
            } else if (type == "CUSTOMER") {
                std::string sId, name, phone, sTok, orderId, status, sPri;
                std::getline(ss, sId, '|');
                std::getline(ss, name, '|');
                std::getline(ss, phone, '|');
                std::getline(ss, sTok, '|');
                std::getline(ss, orderId, '|');
                std::getline(ss, status, '|');
                std::getline(ss, sPri, '|');

                int id = std::stoi(sId);
                int tok = std::stoi(sTok);
                int pri = std::stoi(sPri);

                Customer c(id, name, phone, tok, orderId, status, pri);
                customerList.addCustomer(c);

                if (status == "Waiting" || status == "Preparing") {
                    normalQueue.enqueue(c);
                    priorityQueue.enqueue(c);
                    circularQueue.addToken(tok);
                    dequeQueue.insertRear(c);
                }
            } else if (type == "ORDER") {
                std::string ordId, sCid, cName, sTok, status, method, sTotal, itemsStr;
                std::getline(ss, ordId, '|');
                std::getline(ss, sCid, '|');
                std::getline(ss, cName, '|');
                std::getline(ss, sTok, '|');
                std::getline(ss, status, '|');
                std::getline(ss, method, '|');
                std::getline(ss, sTotal, '|');
                std::getline(ss, itemsStr, '|');

                int cid = std::stoi(sCid);
                int tok = std::stoi(sTok);

                Order o(ordId, cid, cName, tok, getTimestamp());
                o.setOrderStatus(status);
                o.setPaymentMethod(method);
                o.setPaymentStatus("Paid");

                // Parse items: Name:Qty:Price;...
                std::stringstream itemss(itemsStr);
                std::string itemChunk;
                while (std::getline(itemss, itemChunk, ';')) {
                    if (itemChunk.empty()) continue;
                    std::stringstream chunkss(itemChunk);
                    std::string iname, sqty, sprice;
                    std::getline(chunkss, iname, ':');
                    std::getline(chunkss, sqty, ':');
                    std::getline(chunkss, sprice, ':');
                    if (!iname.empty() && !sqty.empty() && !sprice.empty()) {
                        o.addItem(iname, std::stoi(sqty), std::stod(sprice));
                    }
                }
                orderHistory.addOrder(o);
                recentOrdersStack.push(o);
            }
        }
        file.close();
        std::cout << "[SUCCESS] Loaded sample data from database file successfully!\n";
    }

    void initDefaultMenu() {
        // Fallback default menu items
        menuList.addFoodItem(FoodItem(101, "Classic Burger", "Burgers", 120.0));
        menuList.addFoodItem(FoodItem(102, "Cheese Burger", "Burgers", 150.0));
        menuList.addFoodItem(FoodItem(104, "Chicken Burger", "Burgers", 160.0));
        menuList.addFoodItem(FoodItem(201, "Margherita Pizza", "Pizza", 199.0));
        menuList.addFoodItem(FoodItem(202, "Farmhouse Pizza", "Pizza", 259.0));
        menuList.addFoodItem(FoodItem(301, "Masala Dosa", "Indian Food", 80.0));
        menuList.addFoodItem(FoodItem(305, "Chicken Biryani", "Indian Food", 220.0));
        menuList.addFoodItem(FoodItem(401, "French Fries", "Snacks", 80.0));
        menuList.addFoodItem(FoodItem(501, "Coke (Can)", "Beverages", 40.0));
        menuList.addFoodItem(FoodItem(505, "Filter Coffee", "Beverages", 45.0));
    }

    void placeNewOrder() {
        std::cout << "\n========================================\n";
        std::cout << "           PLACE NEW FOOD ORDER         \n";
        std::cout << "========================================\n";

        std::string name, phone;
        std::cout << "Enter Customer Name: ";
        std::getline(std::cin, name);
        if (name.empty()) {
            std::cout << "Name cannot be empty.\n";
            return;
        }

        std::cout << "Enter Customer Phone: ";
        std::getline(std::cin, phone);

        std::cout << "\nPriority Options:\n";
        std::cout << " 1. Low Priority (Normal Order)\n";
        std::cout << " 2. Medium Priority (Regular Order)\n";
        std::cout << " 3. High Priority (Emergency / Express Order)\n";
        std::cout << "Select Priority (1-3) [Default 2]: ";
        std::string priInput;
        std::getline(std::cin, priInput);
        int priority = 2;
        if (priInput == "1") priority = 1;
        else if (priInput == "3") priority = 3;

        int customerId = nextCustomerId++;
        int tokenNum = nextTokenNumber++;
        std::string orderId = "ORD" + std::to_string(nextOrderSeq++);

        Order newOrder(orderId, customerId, name, tokenNum, getTimestamp());

        menuList.displayMenu();

        bool adding = true;
        while (adding) {
            std::cout << "Enter Food Item ID to add (or 0 to finish): ";
            int itemId;
            if (!(std::cin >> itemId) || itemId == 0) {
                std::cin.clear();
                std::string dummy;
                std::getline(std::cin, dummy);
                break;
            }

            FoodItem* item = menuList.findItemById(itemId);
            if (!item) {
                std::cout << "[ERROR] Invalid Food Item ID!\n";
                continue;
            }
            if (!item->isAvailable) {
                std::cout << "[INFO] Sorry, this item is currently Sold Out!\n";
                continue;
            }

            std::cout << "Enter Quantity for " << item->name << ": ";
            int qty;
            std::cin >> qty;
            if (qty <= 0) qty = 1;

            newOrder.addItem(item->name, qty, item->price);
            std::cout << "[+] Added " << qty << "x " << item->name << " to order.\n";
        }

        std::string dummy;
        std::getline(std::cin, dummy); // flush newline

        if (newOrder.getItems().empty()) {
            std::cout << "[INFO] No items selected. Order cancelled.\n";
            return;
        }

        std::cout << "\nSelect Payment Method (1. UPI, 2. Cash, 3. Credit Card, 4. Debit Card): ";
        std::string payStr;
        std::getline(std::cin, payStr);
        if (payStr == "2") newOrder.setPaymentMethod("Cash");
        else if (payStr == "3") newOrder.setPaymentMethod("Credit Card");
        else if (payStr == "4") newOrder.setPaymentMethod("Debit Card");
        else newOrder.setPaymentMethod("UPI");

        std::string txnId = "TXN" + std::to_string(10000 + tokenNum * 37);
        newOrder.setTransactionId(txnId);
        newOrder.setPaymentStatus("Paid");
        newOrder.setOrderStatus("Waiting");

        Customer newCustomer(customerId, name, phone, tokenNum, orderId, "Waiting", priority);

        // Update all Data Structures!
        customerList.addCustomer(newCustomer);
        orderHistory.addOrder(newOrder);
        normalQueue.enqueue(newCustomer);
        priorityQueue.enqueue(newCustomer);
        circularQueue.addToken(tokenNum);
        dequeQueue.insertRear(newCustomer);
        recentOrdersStack.push(newOrder);

        std::cout << "\n=======================================================\n";
        std::cout << " [✓] ORDER CONFIRMED SUCCESSFULLY!\n";
        std::cout << "-------------------------------------------------------\n";
        std::cout << " Customer   : " << name << "\n";
        std::cout << " Order ID   : " << orderId << "\n";
        std::cout << " Token No.  : " << newCustomer.getTokenFormatted() << "\n";
        std::cout << " Items      : " << newOrder.getItemsSummary() << "\n";
        std::cout << " Priority   : " << newCustomer.getPriorityString() << "\n";
        std::cout << " Total Paid : Rs. " << newOrder.getTotalAmount() << "\n";
        std::cout << " Status     : WAITING IN QUEUE\n";
        std::cout << " Txn ID     : " << txnId << "\n";
        std::cout << "=======================================================\n";
    }

    void serveNextCustomer() {
        std::cout << "\n========================================\n";
        std::cout << "          SERVE NEXT CUSTOMER           \n";
        std::cout << "========================================\n";

        if (priorityQueue.isEmpty() && normalQueue.isEmpty()) {
            std::cout << "[INFO] Queue is currently empty. No waiting customers!\n";
            return;
        }

        Customer servedCustomer;
        bool dequeued = false;

        // Serve by Priority Queue first!
        if (!priorityQueue.isEmpty()) {
            priorityQueue.dequeue(servedCustomer);
            dequeued = true;
        } else {
            normalQueue.dequeue(servedCustomer);
            dequeued = true;
        }

        if (dequeued) {
            int tokenServed = 0;
            circularQueue.serveToken(tokenServed);

            Customer dummy;
            dequeQueue.deleteFront(dummy);

            // Update status in Master records
            Customer* cPtr = customerList.searchById(servedCustomer.getId());
            if (cPtr) cPtr->setOrderStatus("Completed");

            Order* oPtr = orderHistory.searchByOrderId(servedCustomer.getOrderId());
            if (oPtr) oPtr->setOrderStatus("Completed");

            std::cout << "[✓] SERVED CUSTOMER DETAILS:\n";
            std::cout << "----------------------------------------\n";
            std::cout << " Token Number : " << servedCustomer.getTokenFormatted() << "\n";
            std::cout << " Customer     : " << servedCustomer.getName() << "\n";
            std::cout << " Order ID     : " << servedCustomer.getOrderId() << "\n";
            std::cout << " Priority     : " << servedCustomer.getPriorityString() << "\n";
            std::cout << " Order Status : COMPLETED & SERVED [✓]\n";
            std::cout << "----------------------------------------\n";
            std::cout << "Remaining in Normal Queue: " << normalQueue.getSize() << " customers\n";
            std::cout << "Remaining in Priority Queue: " << priorityQueue.getSize() << " customers\n";
        }
    }

    void skipCustomer() {
        if (normalQueue.isEmpty()) {
            std::cout << "[INFO] Queue is empty. No customer to skip.\n";
            return;
        }
        Customer c;
        normalQueue.dequeue(c);
        normalQueue.enqueue(c);
        std::cout << "[✓] Customer " << c.getName() << " (" << c.getTokenFormatted()
                  << ") moved to the rear of the queue.\n";
    }

    void undoLastOrder() {
        if (recentOrdersStack.isEmpty()) {
            std::cout << "[INFO] No recent orders to undo in Stack.\n";
            return;
        }
        Order lastOrder;
        recentOrdersStack.pop(lastOrder);

        Order* oPtr = orderHistory.searchByOrderId(lastOrder.getOrderId());
        if (oPtr) oPtr->setOrderStatus("Cancelled");

        Customer* cPtr = customerList.searchById(lastOrder.getCustomerId());
        if (cPtr) cPtr->setOrderStatus("Cancelled");

        std::cout << "\n[!] UNDO ACTION PERFORMED (Stack Pop):\n";
        std::cout << " Cancelled Order : " << lastOrder.getOrderId() << "\n";
        std::cout << " Customer        : " << lastOrder.getCustomerName() << "\n";
        std::cout << " Token           : " << lastOrder.getTokenFormatted() << "\n";
        std::cout << " Refund Amount   : Rs. " << lastOrder.getTotalAmount() << "\n";
    }

    void showBillForOrder() {
        std::cout << "Enter Order ID or Token Number: ";
        std::string query;
        std::getline(std::cin, query);

        Order* o = nullptr;
        if (query.rfind("ORD", 0) == 0) {
            o = orderHistory.searchByOrderId(query);
        } else {
            try {
                int tok = std::stoi(query);
                o = orderHistory.searchByToken(tok);
            } catch (...) {
                o = orderHistory.searchByOrderId(query);
            }
        }

        if (o != nullptr) {
            o->printBill();
        } else {
            std::cout << "[ERROR] Order not found for query: " << query << "\n";
        }
    }

    void searchCustomerOrOrder() {
        std::cout << "\n================ SEARCH =================\n";
        std::cout << "1. Search by Customer ID\n";
        std::cout << "2. Search by Customer Name\n";
        std::cout << "3. Search by Phone Number\n";
        std::cout << "4. Search by Token Number\n";
        std::cout << "5. Search by Order ID\n";
        std::cout << "Select search type (1-5): ";
        std::string opt;
        std::getline(std::cin, opt);

        if (opt == "1") {
            std::cout << "Enter Customer ID: ";
            int id;
            std::cin >> id;
            std::string dummy; std::getline(std::cin, dummy);
            Customer* c = customerList.searchById(id);
            if (c) c->display();
            else std::cout << "Customer not found.\n";
        } else if (opt == "2") {
            std::cout << "Enter Customer Name: ";
            std::string name;
            std::getline(std::cin, name);
            Customer* c = customerList.searchByName(name);
            if (c) c->display();
            else std::cout << "Customer not found.\n";
        } else if (opt == "3") {
            std::cout << "Enter Phone Number: ";
            std::string phone;
            std::getline(std::cin, phone);
            Customer* c = customerList.searchByPhone(phone);
            if (c) c->display();
            else std::cout << "Customer not found.\n";
        } else if (opt == "4") {
            std::cout << "Enter Token Number (numeric): ";
            int tok;
            std::cin >> tok;
            std::string dummy; std::getline(std::cin, dummy);
            Customer* c = customerList.searchByToken(tok);
            if (c) c->display();
            else std::cout << "Token not found.\n";
        } else if (opt == "5") {
            std::cout << "Enter Order ID: ";
            std::string ord;
            std::getline(std::cin, ord);
            Order* o = orderHistory.searchByOrderId(ord);
            if (o) o->printBill();
            else std::cout << "Order not found.\n";
        }
    }

    void displayAdminDashboard() {
        std::cout << "\n========================================================\n";
        std::cout << "              ADMIN DASHBOARD ANALYTICS                 \n";
        std::cout << "========================================================\n";
        std::cout << "+-----------------------+------------------------------+\n";
        std::cout << "| Metric                | Value                        |\n";
        std::cout << "+-----------------------+------------------------------+\n";
        std::cout << "| Total Customers       | " << std::left << std::setw(28) << customerList.getSize() << " |\n";
        std::cout << "| Total Orders          | " << std::left << std::setw(28) << orderHistory.getSize() << " |\n";
        std::cout << "| Active Queue Length   | " << std::left << std::setw(28) << normalQueue.getSize() << " |\n";
        std::cout << "| Priority Queue Length | " << std::left << std::setw(28) << priorityQueue.getSize() << " |\n";
        std::cout << "| Completed Orders      | " << std::left << std::setw(28) << orderHistory.getCompletedCount() << " |\n";
        std::cout << "| Cancelled Orders      | " << std::left << std::setw(28) << orderHistory.getCancelledCount() << " |\n";
        std::cout << "| Total Revenue         | Rs. " << std::left << std::setw(24) << (int)orderHistory.calculateTotalRevenue() << " |\n";
        std::cout << "+-----------------------+------------------------------+\n\n";
    }

    void visualizeAllDataStructures() {
        std::cout << "\n********************************************************\n";
        std::cout << "      DATA STRUCTURE VISUALIZATION DEMONSTRATION        \n";
        std::cout << "********************************************************\n";

        // 1. Normal Queue
        normalQueue.displayVisual();

        // 2. Priority Queue
        priorityQueue.displayVisual();

        // 3. Circular Queue
        circularQueue.displayVisual();

        // 4. Deque
        dequeQueue.displayVisual();

        // 5. Order Stack
        recentOrdersStack.displayVisual();
    }

    void runRealtimeSimulation() {
        std::cout << "\n=======================================================\n";
        std::cout << "         REAL-TIME QUEUE SIMULATION DEMO               \n";
        std::cout << "=======================================================\n";
        std::cout << "Simulating rapid food court traffic...\n\n";

        std::string simNames[] = {"Aarav Sharma", "Diya Patel", "Kabir Singh", "Ananya Roy", "Rohan Mehta"};
        int simPriorities[] = {2, 3, 1, 3, 2}; // Express, Normal, Regular mix
        std::string simFoods[] = {"Classic Burger", "Margherita Pizza", "Chicken Biryani", "Masala Dosa", "French Fries"};
        double simPrices[] = {120.0, 199.0, 220.0, 80.0, 80.0};

        for (int i = 0; i < 5; ++i) {
            int cid = nextCustomerId++;
            int tok = nextTokenNumber++;
            std::string oid = "ORD" + std::to_string(nextOrderSeq++);
            std::string name = simNames[i];
            int pri = simPriorities[i];

            Order o(oid, cid, name, tok, getTimestamp());
            o.addItem(simFoods[i], 1, simPrices[i]);
            o.setPaymentMethod("UPI");
            o.setPaymentStatus("Paid");
            o.setOrderStatus("Waiting");

            Customer c(cid, name, "98" + std::to_string(10000000 + tok), tok, oid, "Waiting", pri);

            customerList.addCustomer(c);
            orderHistory.addOrder(o);
            normalQueue.enqueue(c);
            priorityQueue.enqueue(c);
            circularQueue.addToken(tok);
            dequeQueue.insertRear(c);
            recentOrdersStack.push(o);

            std::cout << "[STEP " << (i + 1) << "] Customer Arrived: " << name
                      << " | Token: " << c.getTokenFormatted()
                      << " | Priority: " << c.getPriorityString()
                      << " | Ordered: " << simFoods[i] << "\n";
        }

        std::cout << "\n--> State After 5 Arrivals:\n";
        visualizeAllDataStructures();

        std::cout << "\n--> Now serving 2 Customers using Priority Queue Dispatcher:\n";
        serveNextCustomer();
        serveNextCustomer();

        std::cout << "\n--> State After 2 Serves:\n";
        visualizeAllDataStructures();

        std::cout << "[✓] Real-Time Simulation Completed Successfully!\n";
    }

    void manageFoodMenu() {
        std::cout << "\n================ MANAGE FOOD MENU ================\n";
        std::cout << "1. View All Menu Items\n";
        std::cout << "2. Add New Food Item\n";
        std::cout << "3. Remove Food Item\n";
        std::cout << "Select option (1-3): ";
        std::string opt;
        std::getline(std::cin, opt);

        if (opt == "1") {
            menuList.displayMenu();
        } else if (opt == "2") {
            std::cout << "Enter Item ID: ";
            int id;
            std::cin >> id;
            std::string dummy; std::getline(std::cin, dummy);
            std::cout << "Enter Item Name: ";
            std::string name; std::getline(std::cin, name);
            std::cout << "Enter Category (Burgers, Pizza, Indian Food, Snacks, Beverages): ";
            std::string cat; std::getline(std::cin, cat);
            std::cout << "Enter Price: ";
            double price; std::cin >> price;
            std::getline(std::cin, dummy);
            menuList.addFoodItem(FoodItem(id, name, cat, price, true));
            std::cout << "[✓] Added " << name << " to menu successfully!\n";
        } else if (opt == "3") {
            std::cout << "Enter Item ID to remove: ";
            int id;
            std::cin >> id;
            std::string dummy; std::getline(std::cin, dummy);
            if (menuList.removeFoodItem(id)) {
                std::cout << "[✓] Item " << id << " removed from menu.\n";
            } else {
                std::cout << "[ERROR] Item ID not found.\n";
            }
        }
    }

    void runConsole() {
        bool running = true;
        while (running) {
            std::cout << "\n=======================================================\n";
            std::cout << "       FOOD COURT QUEUE MANAGEMENT SYSTEM (C++)        \n";
            std::cout << "=======================================================\n";
            std::cout << " 1. Customer: View Menu\n";
            std::cout << " 2. Customer: Place Food Order (Generate Token)\n";
            std::cout << " 3. Customer: Search & Track Order / Token Status\n";
            std::cout << " 4. Customer: View Detailed Bill Receipt\n";
            std::cout << " 5. Counter/Queue: Serve Next Customer (Priority Queue)\n";
            std::cout << " 6. Counter/Queue: Skip Customer (Move to Rear)\n";
            std::cout << " 7. Counter/Queue: Undo Last Order (Stack Pop)\n";
            std::cout << " 8. Counter/Queue: View Waiting Queue\n";
            std::cout << " 9. Data Structures Visualizer (Normal, Priority, Circular, Deque, Stack)\n";
            std::cout << "10. Real-Time Queue Simulation Demo\n";
            std::cout << "11. Admin: Dashboard & Revenue Analytics\n";
            std::cout << "12. Admin: Manage Food Menu (Add / Remove Dishes)\n";
            std::cout << "13. Admin: View All Customers & Order History\n";
            std::cout << "14. Exit System\n";
            std::cout << "=======================================================\n";
            std::cout << "Enter Choice (1-14): ";

            std::string choice;
            std::getline(std::cin, choice);

            if (choice == "1") {
                menuList.displayMenu();
            } else if (choice == "2") {
                placeNewOrder();
            } else if (choice == "3") {
                searchCustomerOrOrder();
            } else if (choice == "4") {
                showBillForOrder();
            } else if (choice == "5") {
                serveNextCustomer();
            } else if (choice == "6") {
                skipCustomer();
            } else if (choice == "7") {
                undoLastOrder();
            } else if (choice == "8") {
                normalQueue.display();
                circularQueue.display();
            } else if (choice == "9") {
                visualizeAllDataStructures();
            } else if (choice == "10") {
                runRealtimeSimulation();
            } else if (choice == "11") {
                displayAdminDashboard();
            } else if (choice == "12") {
                manageFoodMenu();
            } else if (choice == "13") {
                customerList.displayAll();
                orderHistory.displayHistory();
            } else if (choice == "14") {
                std::cout << "Thank you for using Food Court Queue Management System!\n";
                running = false;
            } else {
                std::cout << "[ERROR] Invalid choice. Please select 1 to 14.\n";
            }
        }
    }
};

int main() {
    FoodCourtSystem app;
    app.loadSampleData("../database/sample-data.txt");
    app.runConsole();
    return 0;
}
