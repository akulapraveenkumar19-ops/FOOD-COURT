#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

struct OrderItem {
    std::string itemName;
    int quantity;
    double unitPrice;

    double getTotal() const {
        return quantity * unitPrice;
    }
};

class Order {
private:
    std::string orderId;
    int customerId;
    std::string customerName;
    int tokenNumber;
    std::vector<OrderItem> items;
    double subtotal;
    double tax;        // 5% GST
    double discount;
    double totalAmount;
    std::string orderStatus;     // "Waiting", "Preparing", "Ready", "Completed", "Cancelled"
    std::string paymentMethod;   // "Cash", "UPI", "Credit Card", "Debit Card"
    std::string paymentStatus;   // "Pending", "Paid"
    std::string transactionId;
    std::string timestamp;

public:
    Order();
    Order(const std::string& orderId, int customerId, const std::string& customerName,
          int tokenNumber, const std::string& timestamp = "");

    // Getters
    std::string getOrderId() const;
    int getCustomerId() const;
    std::string getCustomerName() const;
    int getTokenNumber() const;
    std::string getTokenFormatted() const;
    const std::vector<OrderItem>& getItems() const;
    double getSubtotal() const;
    double getTax() const;
    double getDiscount() const;
    double getTotalAmount() const;
    std::string getOrderStatus() const;
    std::string getPaymentMethod() const;
    std::string getPaymentStatus() const;
    std::string getTransactionId() const;
    std::string getTimestamp() const;

    // Setters
    void setOrderId(const std::string& id);
    void setCustomerId(int id);
    void setCustomerName(const std::string& name);
    void setTokenNumber(int token);
    void setOrderStatus(const std::string& status);
    void setPaymentMethod(const std::string& method);
    void setPaymentStatus(const std::string& status);
    void setTransactionId(const std::string& txnId);
    void setTimestamp(const std::string& timeStr);

    // Operations
    void addItem(const std::string& name, int qty, double price);
    void calculateBill(double discountPercent = 0.0);
    void printBill() const;
    void displaySummary() const;
    std::string getItemsSummary() const;
};

#endif // ORDER_H
