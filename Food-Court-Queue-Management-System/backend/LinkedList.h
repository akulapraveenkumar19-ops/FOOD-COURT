#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Customer.h"
#include "Order.h"
#include <string>
#include <vector>

// --- Food Item Structure & Menu List Node ---
struct FoodItem {
    int id;
    std::string name;
    std::string category;
    double price;
    bool isAvailable;

    FoodItem() : id(0), name(""), category(""), price(0.0), isAvailable(true) {}
    FoodItem(int id, const std::string& name, const std::string& category, double price, bool available = true)
        : id(id), name(name), category(category), price(price), isAvailable(available) {}
};

struct FoodNode {
    FoodItem item;
    FoodNode* next;
    FoodNode(const FoodItem& fi) : item(fi), next(nullptr) {}
};

class FoodMenuList {
private:
    FoodNode* head;
    int count;

public:
    FoodMenuList();
    ~FoodMenuList();

    void addFoodItem(const FoodItem& item);
    bool removeFoodItem(int id);
    FoodItem* findItemById(int id);
    FoodItem* findItemByName(const std::string& name);
    void displayMenu() const;
    void displayByCategory(const std::string& category) const;
    std::vector<FoodItem> getAllItems() const;
    int getSize() const;
    void clear();
};

// --- Customer Linked List ---
struct CustomerNode {
    Customer customer;
    CustomerNode* next;
    CustomerNode(const Customer& c) : customer(c), next(nullptr) {}
};

class CustomerList {
private:
    CustomerNode* head;
    int count;

public:
    CustomerList();
    ~CustomerList();

    void addCustomer(const Customer& c);
    bool removeCustomer(int id);
    Customer* searchById(int id);
    Customer* searchByPhone(const std::string& phone);
    Customer* searchByName(const std::string& name);
    Customer* searchByToken(int token);
    void displayAll() const;
    int getSize() const;
    void clear();
};

// --- Order History Linked List ---
struct OrderHistoryNode {
    Order order;
    OrderHistoryNode* next;
    OrderHistoryNode(const Order& o) : order(o), next(nullptr) {}
};

class OrderHistoryList {
private:
    OrderHistoryNode* head;
    int count;

public:
    OrderHistoryList();
    ~OrderHistoryList();

    void addOrder(const Order& o);
    Order* searchByOrderId(const std::string& orderId);
    Order* searchByToken(int token);
    void displayHistory() const;
    double calculateTotalRevenue() const;
    int getCompletedCount() const;
    int getCancelledCount() const;
    int getSize() const;
    void clear();
};

#endif // LINKED_LIST_H
