#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include <iomanip>

class Customer {
private:
    int id;
    std::string name;
    std::string phone;
    int token;
    std::string orderId;
    std::string orderStatus; // "Waiting", "Preparing", "Ready", "Completed", "Cancelled"
    int priority;            // 3: High/Express, 2: Medium/Regular, 1: Low/Normal

public:
    // Constructors
    Customer();
    Customer(int id, const std::string& name, const std::string& phone,
             int token, const std::string& orderId,
             const std::string& orderStatus = "Waiting", int priority = 2);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getPhone() const;
    int getToken() const;
    std::string getTokenFormatted() const;
    std::string getOrderId() const;
    std::string getOrderStatus() const;
    int getPriority() const;
    std::string getPriorityString() const;

    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setPhone(const std::string& phone);
    void setToken(int token);
    void setOrderId(const std::string& orderId);
    void setOrderStatus(const std::string& status);
    void setPriority(int priority);

    // Display
    void display() const;
    void displayRow() const;
    static void printHeader();
};

#endif // CUSTOMER_H
