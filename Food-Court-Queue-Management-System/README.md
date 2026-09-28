# Food Court Queue Management System 🍔🍟🍕
**A Complete C++ & Web Data Structures Mini Project**

Designed for **B.Tech CSE / IT / Data Structures and Algorithms** coursework, practical lab assessments, and viva examinations.

---

## 📌 Project Overview

The **Food Court Queue Management System** is a real-world simulation and software application designed to handle customer orders, billing, token generation, and kitchen queue processing in high-density food courts. 

The core algorithmic logic, queue scheduling, and memory structures are implemented in **C++** using manual pointer-based data structures without relying on heavy abstractions. The frontend provides a responsive dashboard built with **HTML5, CSS3, and JavaScript**, featuring real-time visualizers that demonstrate queue mechanics in action.

---

## 📂 File & Directory Structure

```text
Food-Court-Queue-Management-System/
│
├── frontend/
│   ├── index.html              # Main portal, hero showcase, role switcher, overview
│   ├── menu.html               # Categorized food catalog (Burgers, Pizza, Indian, Snacks, Drinks)
│   ├── order.html              # Cart management, priority selection, checkout & token generator
│   ├── queue.html              # Live token dashboard, serve/skip controls, and DS Visualizer
│   ├── admin.html              # Kitchen & revenue metrics, customer search, menu manager
│   ├── billing.html            # Thermal invoice receipt, 5% GST calculation, simulated payment
│   │
│   ├── css/
│   │   └── style.css           # Modern food court aesthetic, responsive grid, dark/light themes
│   │
│   ├── js/
│   │   └── script.js           # Shared state engine, audio synthesis, visualizer animations
│   │
│   └── assets/
│       └── food-images/        # High-res SVG food illustrations (Burger, Pizza, Dosa, etc.)
│
├── backend/
│   ├── main.cpp                # Interactive console CLI, system orchestrator & simulation
│   ├── Customer.h / .cpp       # Customer entity class
│   ├── Order.h / .cpp          # Order entity, item breakdown, invoice printing
│   ├── Queue.h / .cpp          # 1. Normal Queue (FIFO) implementation
│   ├── CircularQueue.h / .cpp  # 2. Circular Queue (Modulo buffer) implementation
│   ├── PriorityQueue.h / .cpp  # 3. Priority Queue (Multi-tier express dispatcher)
│   ├── Deque.h / .cpp          # 4. Double Ended Queue (Deque with doubly linked list)
│   ├── Stack.h / .cpp          # 5. Order Stack (LIFO for undo & recent transactions)
│   └── LinkedList.h / .cpp     # 6. Master records (Menu, Customers, Order History)
│
├── database/
│   └── sample-data.txt         # Seed database file for food menu, customers & sample orders
│
└── README.md                   # Project documentation, DSA guide, test cases & Viva Q&A
```

---

## 🛠️ Data Structures Implemented & Academic Explanation

| # | Data Structure | Used For | Time Complexity (Insert / Remove) | Space Complexity |
|---|---|---|---|---|
| **1** | **Normal Queue** (Linked List) | Standard FIFO waiting line for normal customer orders | $O(1)$ Enqueue / $O(1)$ Dequeue | $O(N)$ |
| **2** | **Circular Queue** (Array modulo) | Fixed counter token buffer; wraps rear to front using `(rear + 1) % size` | $O(1)$ Add / $O(1)$ Serve | $O(K)$ |
| **3** | **Priority Queue** (Sorted List) | Express orders served ahead of Regular and Normal orders | $O(N)$ Enqueue / $O(1)$ Dequeue | $O(N)$ |
| **4** | **Deque** (Doubly Linked List) | VIP front entry, regular rear entry, cancellation from either end | $O(1)$ Both Ends | $O(N)$ |
| **5** | **Stack** (Linked List) | Recent transactions tracking & instantaneous **Undo Last Order** | $O(1)$ Push / $O(1)$ Pop | $O(N)$ |
| **6** | **Linked List** (Singly Linked) | Master catalog of food menu, customer records, and order history | $O(1)$ Insert / $O(N)$ Search | $O(N)$ |

### Detailed DS Mechanics:

1. **Normal Queue (`Queue.h`, `Queue.cpp`)**:
   - Implemented using dynamic linked nodes `QueueNode` having pointers `front` and `rear`.
   - Ensures First-Come First-Served fairness.
   - Diagram:
     ```text
     FRONT
       ↓
     [T-001 : Praveen] ---> [T-002 : Sneha] ---> [T-003 : Rahul]
                                                    ↑
                                                   REAR
     ```

2. **Circular Queue (`CircularQueue.h`, `CircularQueue.cpp`)**:
   - Implemented via array of fixed capacity $C = 15$.
   - Avoids memory wastage seen in basic linear arrays.
   - Pointers update via:
     $$\text{rear} = (\text{rear} + 1) \pmod{\text{capacity}}$$
     $$\text{front} = (\text{front} + 1) \pmod{\text{capacity}}$$

3. **Priority Queue (`PriorityQueue.h`, `PriorityQueue.cpp`)**:
   - Organizes customers based on urgency:
     - 🔴 **High (3)**: Express / Emergency / Takeaway Priority
     - 🟡 **Medium (2)**: Regular Dine-in Order
     - 🟢 **Low (1)**: Standard / Discounted Order
   - Dequeuing always pulls the highest priority customer first.
   - Diagram:
     ```text
     HIGH (Express - Served First)
      ↓
     [T-002 : Sneha]

     MEDIUM (Regular)
      ↓
     [T-001 : Praveen] ---> [T-003 : Rahul]

     LOW (Normal)
      ↓
     (None)
     ```

4. **Deque (`Deque.h`, `Deque.cpp`)**:
   - Uses `DequeNode` with `prev` and `next` pointers.
   - Supports: `insertFront()`, `insertRear()`, `deleteFront()`, `deleteRear()`.
   - Diagram:
     ```text
     FRONT                                          REAR
       ↓                                              ↓
     [T-001] <=====================> [T-002] <=====================> [T-003]
     ```

5. **Stack (`Stack.h`, `Stack.cpp`)**:
   - LIFO (Last-In-First-Out) stack of orders.
   - Enables **Undo Last Order**: Pops the latest active order, updates its status to `Cancelled`, and triggers a refund.
   - Diagram:
     ```text
      TOP  ↓
     +----------------------------------------+
     | ORD1005  T-005  Vikram Rao   Rs.220    |
     | ORD1004  T-004  Priya Patel  Rs.160    |
     | ORD1003  T-003  Rahul Verma  Rs.230    |
     +----------------------------------------+
                     BOTTOM
     ```

---

## 💻 System Architecture

```text
+--------------------------------------------------------------------+
|                          USER INTERFACE                            |
|  [Food Menu]   [Cart & Order]   [Live Queue]   [Thermal Billing]   |
+--------------------------------------------------------------------+
                                   │
                                   ▼
+--------------------------------------------------------------------+
|               FRONTEND ENGINE & STATE (script.js)                  |
|  - LocalStorage Real-time Synchronization across Pages             |
|  - Web Audio API Sound Synthesizer (Chime & Alerts)                |
|  - CSS Animated DS Visualizers (Queue, Circular, Priority, Stack)  |
+--------------------------------------------------------------------+
                                   │
                                   ▼
+--------------------------------------------------------------------+
|                  C++ CORE DATA STRUCTURE BACKEND                   |
|  ├── Normal Queue       (FIFO waiting lines)                       |
|  ├── Priority Queue     (Express kitchen dispatcher)               |
|  ├── Circular Queue     (Token cycling buffer)                     |
|  ├── Deque              (Double-ended order modifications)         |
|  ├── Stack              (Undo order & transaction history)         |
|  └── Linked Lists       (Master Customer & Menu Catalog)           |
+--------------------------------------------------------------------+
                                   │
                                   ▼
+--------------------------------------------------------------------+
|                    PERSISTENCE LAYER (sample-data.txt)             |
|  FOOD | ID | Name | Category | Price | Status                      |
|  CUSTOMER | ID | Name | Phone | Token | OrderID | Priority         |
|  ORDER | OrderID | CustID | Token | Items | Total | Status         |
+--------------------------------------------------------------------+
```

---

## ⚙️ Compilation & Setup Instructions

### Prerequisites
- Any modern C++ compiler (`g++`, `clang++`, or MSVC `cl.exe`) supporting C++11 or higher (C++17 recommended).
- Any standard web browser (Chrome, Edge, Firefox, Safari).

### 1. Compiling the C++ Application

Open terminal / PowerShell in `Food-Court-Queue-Management-System/backend`:

```bash
cd backend
g++ -std=c++17 -Wall -Wextra main.cpp Customer.cpp Order.cpp Queue.cpp CircularQueue.cpp PriorityQueue.cpp Deque.cpp Stack.cpp LinkedList.cpp -o foodcourt_system.exe
```

### 2. Running the C++ Console Program

```bash
.\foodcourt_system.exe
```

### 3. Launching the Web Frontend

Simply open `frontend/index.html` in your web browser, or launch a lightweight local server:

```bash
# Optional: Using Python
cd frontend
python -m http.server 8080
```
Then navigate to: `http://localhost:8080/index.html`

---

## 🧪 Demonstration Flow & Test Cases

### Flow of Demonstration:
1. **Open Frontend**: Navigate to `index.html`. Notice live statistics and current serving token.
2. **Browse Menu**: Click **Food Menu**, filter by category (e.g. *Burgers* or *Pizza*), adjust quantity, and click **Add to Cart**.
3. **Cart & Priority**: Go to **Order & Cart**, enter Customer Name (`"Praveen Kumar"`), Phone (`"9876543210"`), and select **Priority (🔴 High)**.
4. **Token Generation**: Click **Confirm Order**. The system generates token `T-006` and confirms order `ORD1006`.
5. **Live Queue & Visualizer**: Go to **Live Queue**. Observe `T-006` in the Normal Queue, Priority Queue (at the front of its category lane), Circular Queue, and Order Stack.
6. **Serve Customer**: Click **Serve Next Customer**. The system serves the highest priority waiting order and updates the state.
7. **Undo Last Order**: Click **Undo Last Order (Stack Pop)**. Watch the top order get popped and marked as `Cancelled`.
8. **Billing**: Go to **Billing & Receipt**, inspect the thermal receipt with 5% GST breakdown, and test the payment gateway simulator (UPI / Card).
9. **Admin Panel**: Visit **Admin Dashboard** to search customers, inspect revenue analytics, and add or toggle dishes.

---

## 📋 Sample Output from C++ Console

```text
********************************************************
      DATA STRUCTURE VISUALIZATION DEMONSTRATION        
********************************************************

========================================
         NORMAL QUEUE VISUALIZER        
========================================

 FRONT
   |
   v
[T-001 : Praveen ] ---> [T-002 : Sneha Sh] ---> [T-003 : Rahul Ve]
                                                  ^
                                                  |
                                                 REAR
========================================


========================================
       PRIORITY QUEUE VISUALIZER        
========================================

 HIGH (Express - Served First)
  |
  v
 [T-002 : Sneha Sh]

 MEDIUM (Regular)
  |
  v
 [T-001 : Praveen ] ---> [T-003 : Rahul Ve]

 LOW (Normal)
  |
  v
  (None)

========================================


===================================================
           CIRCULAR QUEUE BUFFER SLOTS             
===================================================
Slot Index: [ 0] [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8] [ 9] [10] [11] [12] [13] [14] 
Token Val :   T 1   T 2   T 3   --    --    --    --    --    --    --    --    --    --    --    --  
Pointers  :  FRNT        REAR                                                             
Status: ACTIVE | Total: 3 / 15
===================================================


========================================
          ORDER STACK VISUALIZER        
========================================

 TOP
  |
  v
+--------------------------------------+
| ORD1005    T-005   Vikram Rao   Rs.220 |
| ORD1004    T-004   Priya Patel  Rs.160 |
| ORD1003    T-003   Rahul Verma  Rs.230 |
| ORD1002    T-002   Sneha Sharma Rs.350 |
| ORD1001    T-001   Praveen Kuma Rs.200 |
+--------------------------------------+
               BOTTOM                  
========================================
```

---

## 🎓 Viva Questions & Answers (DSA Lab & Mini Project Exam)

### Q1: Why use a Circular Queue instead of a linear array queue?
> **Answer**: In a linear array queue, dequeuing elements leaves empty spaces at the front that cannot be reused without shifting elements (which takes $O(N)$ time). A Circular Queue wraps around using modulo arithmetic `(rear + 1) % capacity`, achieving $O(1)$ enqueue and dequeue operations without memory wastage.

### Q2: What is the time complexity of enqueue and dequeue in your Queue implementation?
> **Answer**: Both are $O(1)$ constant time. Because we maintain both `front` and `rear` pointers in our linked list implementation, we can append to the rear and delete from the front without traversing the list.

### Q3: How is the Priority Queue implemented and how does it prevent starvation?
> **Answer**: It is implemented as a sorted linked list ordered descending by priority level (High = 3, Medium = 2, Low = 1). Within the same priority tier, elements are arranged in FIFO order (ensuring fairness). In high-volume setups, aging (gradually incrementing priority based on wait time) can be introduced to prevent starvation.

### Q4: Why is a Stack suitable for the "Undo Last Order" operation?
> **Answer**: The Stack adheres to LIFO (Last-In-First-Out). The most recent order placed is always at the top of the stack. Popping takes $O(1)$ time to access and reverse the most recently placed order.

### Q5: What is the difference between a Deque and a normal Queue?
> **Answer**: A normal Queue is restricted to insertion at the rear and deletion from the front. A Deque (Double-Ended Queue) allows insertion and deletion at both the front and the rear in $O(1)$ time using a doubly linked list.

### Q6: How does the system calculate billing and tax?
> **Answer**: The system sums the line items ($\text{Qty} \times \text{UnitPrice}$), subtracts any promotional discount, and adds 5% GST on the taxable amount:
> $$\text{Total} = (\text{Subtotal} - \text{Discount}) \times 1.05$$

### Q7: Why did you implement data structures manually rather than using C++ STL?
> **Answer**: Manual implementation demonstrates fundamental understanding of pointers, memory allocation (`new` and `delete`), linked node traversal, and algorithmic invariants required in computer science coursework.

---

## 👨‍💻 Project Contributor & Academic Attribution
- **Course**: B.Tech CSE (2nd Year) — Data Structures and Algorithms / DSC ++
- **Project**: Food Court Queue Management System Mini Project
