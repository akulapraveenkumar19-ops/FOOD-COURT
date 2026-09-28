#include "Customer.h"
#include <sstream>

Customer::Customer()
    : id(0), name("Unknown"), phone(""), token(0), orderId(""),
      orderStatus("Waiting"), priority(2) {}

Customer::Customer(int id, const std::string& name, const std::string& phone,
                   int token, const std::string& orderId,
                   const std::string& orderStatus, int priority)
    : id(id), name(name), phone(phone), token(token), orderId(orderId),
      orderStatus(orderStatus), priority(priority) {}

int Customer::getId() const { return id; }
std::string Customer::getName() const { return name; }
std::string Customer::getPhone() const { return phone; }
int Customer::getToken() const { return token; }

std::string Customer::getTokenFormatted() const {
    std::ostringstream oss;
    oss << "T-" << std::setw(3) << std::setfill('0') << token;
    return oss.str();
}

std::string Customer::getOrderId() const { return orderId; }
std::string Customer::getOrderStatus() const { return orderStatus; }
int Customer::getPriority() const { return priority; }

std::string Customer::getPriorityString() const {
    switch (priority) {
        case 3: return "High (Express)";
        case 2: return "Medium (Regular)";
        case 1: return "Low (Normal)";
        default: return "Medium";
    }
}

void Customer::setId(int id) { this->id = id; }
void Customer::setName(const std::string& name) { this->name = name; }
void Customer::setPhone(const std::string& phone) { this->phone = phone; }
void Customer::setToken(int token) { this->token = token; }
void Customer::setOrderId(const std::string& orderId) { this->orderId = orderId; }
void Customer::setOrderStatus(const std::string& status) { this->orderStatus = status; }
void Customer::setPriority(int priority) { this->priority = priority; }

void Customer::display() const {
    std::cout << "-------------------------------------------\n";
    std::cout << " Customer ID   : " << id << "\n";
    std::cout << " Name          : " << name << "\n";
    std::cout << " Phone         : " << phone << "\n";
    std::cout << " Token Number  : " << getTokenFormatted() << "\n";
    std::cout << " Order ID      : " << orderId << "\n";
    std::cout << " Order Status  : " << orderStatus << "\n";
    std::cout << " Priority      : " << getPriorityString() << "\n";
    std::cout << "-------------------------------------------\n";
}

void Customer::printHeader() {
    std::cout << std::left
              << std::setw(8)  << "ID"
              << std::setw(18) << "Name"
              << std::setw(14) << "Phone"
              << std::setw(10) << "Token"
              << std::setw(12) << "Order ID"
              << std::setw(14) << "Status"
              << std::setw(16) << "Priority"
              << "\n";
    std::cout << std::string(92, '-') << "\n";
}

void Customer::displayRow() const {
    std::cout << std::left
              << std::setw(8)  << id
              << std::setw(18) << name.substr(0, 16)
              << std::setw(14) << phone
              << std::setw(10) << getTokenFormatted()
              << std::setw(12) << orderId
              << std::setw(14) << orderStatus
              << std::setw(16) << getPriorityString()
              << "\n";
}
