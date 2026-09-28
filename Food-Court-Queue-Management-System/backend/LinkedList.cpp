#include "LinkedList.h"
#include <iostream>
#include <iomanip>

// ================= FoodMenuList Implementation =================
FoodMenuList::FoodMenuList() : head(nullptr), count(0) {}

FoodMenuList::~FoodMenuList() {
    clear();
}

void FoodMenuList::clear() {
    while (head != nullptr) {
        FoodNode* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
}

int FoodMenuList::getSize() const { return count; }

void FoodMenuList::addFoodItem(const FoodItem& item) {
    FoodNode* newNode = new FoodNode(item);
    if (head == nullptr) {
        head = newNode;
    } else {
        FoodNode* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    count++;
}

bool FoodMenuList::removeFoodItem(int id) {
    if (head == nullptr) return false;
    if (head->item.id == id) {
        FoodNode* temp = head;
        head = head->next;
        delete temp;
        count--;
        return true;
    }
    FoodNode* curr = head;
    while (curr->next != nullptr && curr->next->item.id != id) {
        curr = curr->next;
    }
    if (curr->next != nullptr) {
        FoodNode* temp = curr->next;
        curr->next = temp->next;
        delete temp;
        count--;
        return true;
    }
    return false;
}

FoodItem* FoodMenuList::findItemById(int id) {
    FoodNode* curr = head;
    while (curr != nullptr) {
        if (curr->item.id == id) return &(curr->item);
        curr = curr->next;
    }
    return nullptr;
}

FoodItem* FoodMenuList::findItemByName(const std::string& name) {
    FoodNode* curr = head;
    while (curr != nullptr) {
        if (curr->item.name == name) return &(curr->item);
        curr = curr->next;
    }
    return nullptr;
}

void FoodMenuList::displayMenu() const {
    std::cout << "\n============================== FOOD MENU ==============================\n";
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(26) << "Item Name"
              << std::setw(16) << "Category"
              << std::setw(12) << "Price (Rs)"
              << std::setw(12) << "Status"
              << "\n";
    std::cout << std::string(72, '-') << "\n";

    FoodNode* curr = head;
    while (curr != nullptr) {
        std::cout << std::left
                  << std::setw(6)  << curr->item.id
                  << std::setw(26) << curr->item.name.substr(0, 24)
                  << std::setw(16) << curr->item.category
                  << std::setw(12) << (int)curr->item.price
                  << std::setw(12) << (curr->item.isAvailable ? "Available" : "Sold Out")
                  << "\n";
        curr = curr->next;
    }
    std::cout << "=======================================================================\n\n";
}

void FoodMenuList::displayByCategory(const std::string& category) const {
    std::cout << "\n================= " << category << " MENU =================\n";
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(26) << "Item Name"
              << std::setw(12) << "Price (Rs)"
              << std::setw(12) << "Status"
              << "\n";
    std::cout << std::string(56, '-') << "\n";

    FoodNode* curr = head;
    while (curr != nullptr) {
        if (curr->item.category == category) {
            std::cout << std::left
                      << std::setw(6)  << curr->item.id
                      << std::setw(26) << curr->item.name.substr(0, 24)
                      << std::setw(12) << (int)curr->item.price
                      << std::setw(12) << (curr->item.isAvailable ? "Available" : "Sold Out")
                      << "\n";
        }
        curr = curr->next;
    }
    std::cout << "--------------------------------------------------------\n\n";
}

std::vector<FoodItem> FoodMenuList::getAllItems() const {
    std::vector<FoodItem> items;
    FoodNode* curr = head;
    while (curr != nullptr) {
        items.push_back(curr->item);
        curr = curr->next;
    }
    return items;
}

// ================= CustomerList Implementation =================
CustomerList::CustomerList() : head(nullptr), count(0) {}

CustomerList::~CustomerList() {
    clear();
}

void CustomerList::clear() {
    while (head != nullptr) {
        CustomerNode* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
}

int CustomerList::getSize() const { return count; }

void CustomerList::addCustomer(const Customer& c) {
    CustomerNode* newNode = new CustomerNode(c);
    if (head == nullptr) {
        head = newNode;
    } else {
        CustomerNode* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    count++;
}

bool CustomerList::removeCustomer(int id) {
    if (head == nullptr) return false;
    if (head->customer.getId() == id) {
        CustomerNode* temp = head;
        head = head->next;
        delete temp;
        count--;
        return true;
    }
    CustomerNode* curr = head;
    while (curr->next != nullptr && curr->next->customer.getId() != id) {
        curr = curr->next;
    }
    if (curr->next != nullptr) {
        CustomerNode* temp = curr->next;
        curr->next = temp->next;
        delete temp;
        count--;
        return true;
    }
    return false;
}

Customer* CustomerList::searchById(int id) {
    CustomerNode* curr = head;
    while (curr != nullptr) {
        if (curr->customer.getId() == id) return &(curr->customer);
        curr = curr->next;
    }
    return nullptr;
}

Customer* CustomerList::searchByPhone(const std::string& phone) {
    CustomerNode* curr = head;
    while (curr != nullptr) {
        if (curr->customer.getPhone() == phone) return &(curr->customer);
        curr = curr->next;
    }
    return nullptr;
}

Customer* CustomerList::searchByName(const std::string& name) {
    CustomerNode* curr = head;
    while (curr != nullptr) {
        if (curr->customer.getName() == name) return &(curr->customer);
        curr = curr->next;
    }
    return nullptr;
}

Customer* CustomerList::searchByToken(int token) {
    CustomerNode* curr = head;
    while (curr != nullptr) {
        if (curr->customer.getToken() == token) return &(curr->customer);
        curr = curr->next;
    }
    return nullptr;
}

void CustomerList::displayAll() const {
    if (head == nullptr) {
        std::cout << "[INFO] Customer list is empty.\n";
        return;
    }
    std::cout << "\n======================= REGISTERED CUSTOMERS (" << count << ") =======================\n";
    Customer::printHeader();
    CustomerNode* curr = head;
    while (curr != nullptr) {
        curr->customer.displayRow();
        curr = curr->next;
    }
    std::cout << "============================================================================\n\n";
}

// ================= OrderHistoryList Implementation =================
OrderHistoryList::OrderHistoryList() : head(nullptr), count(0) {}

OrderHistoryList::~OrderHistoryList() {
    clear();
}

void OrderHistoryList::clear() {
    while (head != nullptr) {
        OrderHistoryNode* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
}

int OrderHistoryList::getSize() const { return count; }

void OrderHistoryList::addOrder(const Order& o) {
    OrderHistoryNode* newNode = new OrderHistoryNode(o);
    if (head == nullptr) {
        head = newNode;
    } else {
        OrderHistoryNode* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    count++;
}

Order* OrderHistoryList::searchByOrderId(const std::string& orderId) {
    OrderHistoryNode* curr = head;
    while (curr != nullptr) {
        if (curr->order.getOrderId() == orderId) return &(curr->order);
        curr = curr->next;
    }
    return nullptr;
}

Order* OrderHistoryList::searchByToken(int token) {
    OrderHistoryNode* curr = head;
    while (curr != nullptr) {
        if (curr->order.getTokenNumber() == token) return &(curr->order);
        curr = curr->next;
    }
    return nullptr;
}

void OrderHistoryList::displayHistory() const {
    if (head == nullptr) {
        std::cout << "[INFO] Order history is empty.\n";
        return;
    }
    std::cout << "\n============================== ORDER HISTORY (" << count << ") ==============================\n";
    std::cout << std::left
              << std::setw(10) << "Order ID"
              << std::setw(10) << "Token"
              << std::setw(16) << "Customer"
              << std::setw(25) << "Items"
              << std::setw(10) << "Total"
              << std::setw(12) << "Status"
              << "\n";
    std::cout << std::string(83, '-') << "\n";

    OrderHistoryNode* curr = head;
    while (curr != nullptr) {
        curr->order.displaySummary();
        curr = curr->next;
    }
    std::cout << "=================================================================================\n\n";
}

double OrderHistoryList::calculateTotalRevenue() const {
    double total = 0.0;
    OrderHistoryNode* curr = head;
    while (curr != nullptr) {
        if (curr->order.getOrderStatus() == "Completed") {
            total += curr->order.getTotalAmount();
        }
        curr = curr->next;
    }
    return total;
}

int OrderHistoryList::getCompletedCount() const {
    int c = 0;
    OrderHistoryNode* curr = head;
    while (curr != nullptr) {
        if (curr->order.getOrderStatus() == "Completed") c++;
        curr = curr->next;
    }
    return c;
}

int OrderHistoryList::getCancelledCount() const {
    int c = 0;
    OrderHistoryNode* curr = head;
    while (curr != nullptr) {
        if (curr->order.getOrderStatus() == "Cancelled") c++;
        curr = curr->next;
    }
    return c;
}
