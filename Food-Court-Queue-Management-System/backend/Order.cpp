#include "Order.h"
#include <sstream>

Order::Order()
    : orderId(""), customerId(0), customerName(""), tokenNumber(0),
      subtotal(0.0), tax(0.0), discount(0.0), totalAmount(0.0),
      orderStatus("Waiting"), paymentMethod("Cash"),
      paymentStatus("Pending"), transactionId(""), timestamp("") {}

Order::Order(const std::string& orderId, int customerId, const std::string& customerName,
             int tokenNumber, const std::string& timestamp)
    : orderId(orderId), customerId(customerId), customerName(customerName),
      tokenNumber(tokenNumber), subtotal(0.0), tax(0.0), discount(0.0),
      totalAmount(0.0), orderStatus("Waiting"), paymentMethod("Cash"),
      paymentStatus("Pending"), transactionId(""), timestamp(timestamp) {}

std::string Order::getOrderId() const { return orderId; }
int Order::getCustomerId() const { return customerId; }
std::string Order::getCustomerName() const { return customerName; }
int Order::getTokenNumber() const { return tokenNumber; }

std::string Order::getTokenFormatted() const {
    std::ostringstream oss;
    oss << "T-" << std::setw(3) << std::setfill('0') << tokenNumber;
    return oss.str();
}

const std::vector<OrderItem>& Order::getItems() const { return items; }
double Order::getSubtotal() const { return subtotal; }
double Order::getTax() const { return tax; }
double Order::getDiscount() const { return discount; }
double Order::getTotalAmount() const { return totalAmount; }
std::string Order::getOrderStatus() const { return orderStatus; }
std::string Order::getPaymentMethod() const { return paymentMethod; }
std::string Order::getPaymentStatus() const { return paymentStatus; }
std::string Order::getTransactionId() const { return transactionId; }
std::string Order::getTimestamp() const { return timestamp; }

void Order::setOrderId(const std::string& id) { this->orderId = id; }
void Order::setCustomerId(int id) { this->customerId = id; }
void Order::setCustomerName(const std::string& name) { this->customerName = name; }
void Order::setTokenNumber(int token) { this->tokenNumber = token; }
void Order::setOrderStatus(const std::string& status) { this->orderStatus = status; }
void Order::setPaymentMethod(const std::string& method) { this->paymentMethod = method; }
void Order::setPaymentStatus(const std::string& status) { this->paymentStatus = status; }
void Order::setTransactionId(const std::string& txnId) { this->transactionId = txnId; }
void Order::setTimestamp(const std::string& timeStr) { this->timestamp = timeStr; }

void Order::addItem(const std::string& name, int qty, double price) {
    OrderItem item;
    item.itemName = name;
    item.quantity = qty;
    item.unitPrice = price;
    items.push_back(item);
    calculateBill(0.0);
}

void Order::calculateBill(double discountPercent) {
    subtotal = 0.0;
    for (const auto& item : items) {
        subtotal += item.getTotal();
    }
    discount = (subtotal * discountPercent) / 100.0;
    double taxable = subtotal - discount;
    if (taxable < 0.0) taxable = 0.0;
    tax = taxable * 0.05; // 5% GST
    totalAmount = taxable + tax;
}

std::string Order::getItemsSummary() const {
    std::string summary = "";
    for (size_t i = 0; i < items.size(); ++i) {
        summary += items[i].itemName + " x" + std::to_string(items[i].quantity);
        if (i + 1 < items.size()) summary += ", ";
    }
    return summary;
}

void Order::printBill() const {
    std::cout << "\n========================================\n";
    std::cout << "         FOOD COURT RECEIPT             \n";
    std::cout << "========================================\n";
    std::cout << " Order ID      : " << orderId << "\n";
    std::cout << " Token Number  : " << getTokenFormatted() << "\n";
    std::cout << " Customer      : " << customerName << " (ID: " << customerId << ")\n";
    if (!timestamp.empty()) {
        std::cout << " Date & Time   : " << timestamp << "\n";
    }
    std::cout << " Order Status  : " << orderStatus << "\n";
    std::cout << " Payment Method: " << paymentMethod;
    if (!transactionId.empty()) {
        std::cout << " [" << transactionId << "]";
    }
    std::cout << "\n----------------------------------------\n";
    std::cout << std::left << std::setw(22) << "Item"
              << std::setw(6)  << "Qty"
              << std::setw(6)  << "Price"
              << std::right << std::setw(6) << "Total" << "\n";
    std::cout << "----------------------------------------\n";

    for (const auto& item : items) {
        std::cout << std::left << std::setw(22) << item.itemName.substr(0, 20)
                  << std::setw(6)  << item.quantity
                  << std::setw(6)  << (int)item.unitPrice
                  << std::right << std::setw(6) << (int)item.getTotal() << "\n";
    }
    std::cout << "----------------------------------------\n";
    std::cout << std::left << std::setw(28) << "Subtotal:" << "Rs. " << std::right << std::setw(8) << std::fixed << std::setprecision(2) << subtotal << "\n";
    if (discount > 0.0) {
        std::cout << std::left << std::setw(28) << "Discount:" << "-Rs. " << std::right << std::setw(7) << discount << "\n";
    }
    std::cout << std::left << std::setw(28) << "GST (5%):" << "Rs. " << std::right << std::setw(8) << tax << "\n";
    std::cout << "========================================\n";
    std::cout << std::left << std::setw(28) << "FINAL TOTAL:" << "Rs. " << std::right << std::setw(8) << totalAmount << "\n";
    std::cout << "========================================\n";
    if (paymentStatus == "Paid") {
        std::cout << "   STATUS: PAYMENT SUCCESSFUL [✓]       \n";
    } else {
        std::cout << "   STATUS: PAYMENT PENDING              \n";
    }
    std::cout << "      Thank You! Visit Again!           \n";
    std::cout << "========================================\n\n";
}

void Order::displaySummary() const {
    std::cout << std::left
              << std::setw(10) << orderId
              << std::setw(10) << getTokenFormatted()
              << std::setw(16) << customerName.substr(0, 14)
              << std::setw(25) << getItemsSummary().substr(0, 23)
              << std::setw(10) << (int)totalAmount
              << std::setw(12) << orderStatus
              << "\n";
}
