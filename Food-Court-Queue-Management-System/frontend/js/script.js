/**
 * FOOD COURT QUEUE MANAGEMENT SYSTEM - FRONTEND ENGINE
 * Implements Queue, Circular Queue, Priority Queue, Deque, Stack & Linked List logic
 * Synchronizes real-time state with localStorage across all pages.
 */

// ================= INITIAL DATA SEED =================
const DEFAULT_MENU = [
  { id: 101, name: "Classic Burger", category: "Burgers", price: 120, img: "assets/food-images/classic_burger.jpg", desc: "Crispy patty, lettuce, tomato & secret mayo", available: true },
  { id: 102, name: "Cheese Burger", category: "Burgers", price: 150, img: "assets/food-images/cheese_burger.jpg", desc: "Double cheddar cheese layer with toasted sesame bun", available: true },
  { id: 103, name: "Veg Burger", category: "Burgers", price: 110, img: "assets/food-images/veg_burger.jpg", desc: "Spiced potato & pea patty with mint relish", available: true },
  { id: 104, name: "Chicken Burger", category: "Burgers", price: 160, img: "assets/food-images/chicken_burger.jpg", desc: "Juicy grilled chicken fillet with caramelized onions", available: true },
  { id: 105, name: "Double Chicken Burger", category: "Burgers", price: 220, img: "assets/food-images/double_burger.jpg", desc: "Two jumbo chicken patties loaded with spicy bbq sauce", available: true },
  { id: 106, name: "Paneer Burger", category: "Burgers", price: 140, img: "assets/food-images/paneer_burger.jpg", desc: "Crispy breaded paneer block with creamy chipotle", available: true },

  { id: 201, name: "Margherita Pizza", category: "Pizza", price: 199, img: "assets/food-images/margherita_pizza.jpg", desc: "Classic mozzarella, san marzano tomato sauce, fresh basil", available: true },
  { id: 202, name: "Farmhouse Pizza", category: "Pizza", price: 259, img: "assets/food-images/farmhouse_pizza.jpg", desc: "Capsicum, onion, grilled mushrooms and golden corn", available: true },
  { id: 203, name: "Paneer Pizza", category: "Pizza", price: 239, img: "assets/food-images/paneer_pizza.jpg", desc: "Tandoori marinated paneer cubes, red paprika & capsicum", available: true },
  { id: 204, name: "Chicken Pizza", category: "Pizza", price: 289, img: "assets/food-images/chicken_pizza.jpg", desc: "Loaded barbecued chicken chunks with extra cheese", available: true },
  { id: 205, name: "Veggie Pizza", category: "Pizza", price: 219, img: "assets/food-images/veggie_pizza.jpg", desc: "Garden fresh bell peppers, black olives & fresh onions", available: true },
  { id: 206, name: "Cheese Burst Pizza", category: "Pizza", price: 319, img: "assets/food-images/cheese_burst_pizza.jpg", desc: "Crust filled with molten liquid cheese blend", available: true },

  { id: 301, name: "Masala Dosa", category: "Indian Food", price: 80, img: "assets/food-images/masala_dosa.jpg", desc: "Crispy golden crepe with potato masala, sambar & chutneys", available: true },
  { id: 302, name: "Idli (2 pcs)", category: "Indian Food", price: 50, img: "assets/food-images/idli.jpg", desc: "Steamed rice cakes served piping hot with coconut chutney", available: true },
  { id: 303, name: "Vada (2 pcs)", category: "Indian Food", price: 60, img: "assets/food-images/vada.jpg", desc: "Crispy lentil donuts with sambar and spicy dip", available: true },
  { id: 304, name: "Paneer Biryani", category: "Indian Food", price: 190, img: "assets/food-images/paneer_biryani.jpg", desc: "Fragrant basmati rice layered with paneer tikka & saffron", available: true },
  { id: 305, name: "Chicken Biryani", category: "Indian Food", price: 220, img: "assets/food-images/chicken_biryani.jpg", desc: "Slow cooked dum biryani with succulent chicken piece", available: true },
  { id: 306, name: "Veg Fried Rice", category: "Indian Food", price: 130, img: "assets/food-images/fried_rice.jpg", desc: "Wok-tossed long grain rice with garden vegetables", available: true },
  { id: 307, name: "Veg Hakka Noodles", category: "Indian Food", price: 140, img: "assets/food-images/noodles.jpg", desc: "Indo-Chinese street style tossed noodles with peppers", available: true },

  { id: 401, name: "French Fries", category: "Snacks", price: 80, img: "assets/food-images/french_fries.jpg", desc: "Golden salted crispy potato fries with tomato ketchup", available: true },
  { id: 402, name: "Chicken Nuggets", category: "Snacks", price: 130, img: "assets/food-images/chicken_nuggets.jpg", desc: "Tender breaded chicken bites with spicy mayo dip", available: true },
  { id: 403, name: "Samosa (2 pcs)", category: "Snacks", price: 40, img: "assets/food-images/samosa.jpg", desc: "Traditional flaky pastry filled with spiced potato & peas", available: true },
  { id: 404, name: "Grilled Sandwich", category: "Snacks", price: 90, img: "assets/food-images/sandwich.jpg", desc: "Toasted sandwich loaded with vegetables and mint chutney", available: true },
  { id: 405, name: "Veg Spring Rolls", category: "Snacks", price: 110, img: "assets/food-images/spring_rolls.jpg", desc: "Crispy rolls stuffed with julienned vegetables and sweet chilli", available: true },
  { id: 406, name: "Steamed Momos (6 pcs)", category: "Snacks", price: 100, img: "assets/food-images/momos.jpg", desc: "Himalayan dumplings served with authentic fiery red dip", available: true },

  { id: 501, name: "Coke (Can)", category: "Beverages", price: 40, img: "assets/food-images/coke.jpg", desc: "330ml chilled carbonated beverage", available: true },
  { id: 502, name: "Pepsi (Can)", category: "Beverages", price: 40, img: "assets/food-images/pepsi.jpg", desc: "330ml chilled refreshing cola", available: true },
  { id: 503, name: "Sprite (Can)", category: "Beverages", price: 40, img: "assets/food-images/sprite.jpg", desc: "330ml crisp lemon-lime soda", available: true },
  { id: 504, name: "Fresh Lemon Soda", category: "Beverages", price: 50, img: "assets/food-images/lemon_soda.jpg", desc: "Fizzy lime cooler with sweet & salted blend", available: true },
  { id: 505, name: "Filter Coffee", category: "Beverages", price: 45, img: "assets/food-images/coffee.jpg", desc: "Authentic South Indian aromatic decoction with frothy milk", available: true },
  { id: 506, name: "Masala Chai", category: "Beverages", price: 35, img: "assets/food-images/tea.jpg", desc: "Traditional brew infused with cardamom, ginger & spices", available: true },
  { id: 507, name: "Chocolate Milkshake", category: "Beverages", price: 90, img: "assets/food-images/milkshake.jpg", desc: "Thick creamy shake topped with chocolate drizzle", available: true },
  { id: 508, name: "Fresh Orange Juice", category: "Beverages", price: 80, img: "assets/food-images/orange_juice.jpg", desc: "100% pure squeezed citrus juice, no added sugar", available: true }
];

const DEFAULT_ORDERS = [
  {
    orderId: "ORD1001", customerId: 1001, customerName: "Praveen Kumar", phone: "9876543210",
    token: 1, priority: 2, status: "Waiting", paymentMethod: "UPI", paymentStatus: "Paid",
    timestamp: "28-Sep-2026 12:15:20",
    items: [{ itemName: "Chicken Burger", quantity: 1, unitPrice: 160 }, { itemName: "Coke (Can)", quantity: 1, unitPrice: 40 }],
    subtotal: 200, discount: 0, tax: 10, total: 210, txnId: "TXN10037"
  },
  {
    orderId: "ORD1002", customerId: 1002, customerName: "Sneha Sharma", phone: "9845123456",
    token: 2, priority: 3, status: "Waiting", paymentMethod: "Credit Card", paymentStatus: "Paid",
    timestamp: "28-Sep-2026 12:18:45",
    items: [{ itemName: "Cheese Burst Pizza", quantity: 1, unitPrice: 319 }, { itemName: "Fresh Lemon Soda", quantity: 1, unitPrice: 50 }],
    subtotal: 369, discount: 0, tax: 18.45, total: 387.45, txnId: "TXN10074"
  },
  {
    orderId: "ORD1003", customerId: 1003, customerName: "Rahul Verma", phone: "9712345678",
    token: 3, priority: 2, status: "Preparing", paymentMethod: "Cash", paymentStatus: "Paid",
    timestamp: "28-Sep-2026 12:20:10",
    items: [{ itemName: "Chicken Biryani", quantity: 1, unitPrice: 220 }],
    subtotal: 220, discount: 0, tax: 11, total: 231, txnId: "TXN10111"
  },
  {
    orderId: "ORD1004", customerId: 1004, customerName: "Priya Patel", phone: "9988776655",
    token: 4, priority: 1, status: "Ready", paymentMethod: "UPI", paymentStatus: "Paid",
    timestamp: "28-Sep-2026 12:22:30",
    items: [{ itemName: "Masala Dosa", quantity: 1, unitPrice: 80 }, { itemName: "French Fries", quantity: 1, unitPrice: 80 }],
    subtotal: 160, discount: 0, tax: 8, total: 168, txnId: "TXN10148"
  },
  {
    orderId: "ORD1005", customerId: 1005, customerName: "Vikram Rao", phone: "9123456780",
    token: 5, priority: 2, status: "Completed", paymentMethod: "Debit Card", paymentStatus: "Paid",
    timestamp: "28-Sep-2026 12:25:00",
    items: [{ itemName: "Veg Burger", quantity: 1, unitPrice: 110 }, { itemName: "French Fries", quantity: 1, unitPrice: 80 }],
    subtotal: 190, discount: 0, tax: 9.5, total: 199.5, txnId: "TXN10185"
  }
];

// ================= STATE MANAGER =================
class AppState {
  static get(key, fallback) {
    const raw = localStorage.getItem(`foodcourt_${key}`);
    return raw ? JSON.parse(raw) : fallback;
  }

  static set(key, val) {
    localStorage.setItem(`foodcourt_${key}`, JSON.stringify(val));
    window.dispatchEvent(new Event("stateChanged"));
  }

  static init() {
    const storedMenu = localStorage.getItem("foodcourt_menu");
    // If not set or still has old svg paths, refresh with high quality real-world photos
    if (!storedMenu || storedMenu.includes(".svg")) {
      this.set("menu", DEFAULT_MENU);
    }
    if (!localStorage.getItem("foodcourt_orders")) {
      this.set("orders", DEFAULT_ORDERS);
    }
    if (!localStorage.getItem("foodcourt_orders")) {
      this.set("orders", DEFAULT_ORDERS);
    }
    if (!localStorage.getItem("foodcourt_cart")) {
      this.set("cart", []);
    }
    if (!localStorage.getItem("foodcourt_nextToken")) {
      this.set("nextToken", 6);
    }
    if (!localStorage.getItem("foodcourt_nextCustId")) {
      this.set("nextCustId", 1006);
    }
    if (!localStorage.getItem("foodcourt_nextOrderSeq")) {
      this.set("nextOrderSeq", 1006);
    }
    if (!localStorage.getItem("foodcourt_theme")) {
      this.set("theme", "light");
    }
    if (!localStorage.getItem("foodcourt_role")) {
      this.set("role", "customer");
    }
  }
}

// Initialize state
AppState.init();

// Apply Theme
function applyTheme() {
  const theme = AppState.get("theme", "light");
  document.documentElement.setAttribute("data-theme", theme);
  const btn = document.getElementById("theme-toggle");
  if (btn) {
    btn.innerHTML = theme === "dark" ? "☀️" : "🌙";
  }
}

function toggleTheme() {
  const current = AppState.get("theme", "light");
  const next = current === "dark" ? "light" : "dark";
  AppState.set("theme", next);
  applyTheme();
}

// Sound synthesiser using Web Audio API
function playSound(type) {
  try {
    const ctx = new (window.AudioContext || window.webkitAudioContext)();
    const osc = ctx.createOscillator();
    const gain = ctx.createGain();
    osc.connect(gain);
    gain.connect(ctx.destination);

    if (type === "order") {
      osc.type = "sine";
      osc.frequency.setValueAtTime(523.25, ctx.currentTime); // C5
      osc.frequency.exponentialRampToValueAtTime(659.25, ctx.currentTime + 0.15); // E5
      gain.gain.setValueAtTime(0.3, ctx.currentTime);
      gain.gain.exponentialRampToValueAtTime(0.01, ctx.currentTime + 0.3);
      osc.start();
      osc.stop(ctx.currentTime + 0.3);
    } else if (type === "serve") {
      osc.type = "triangle";
      osc.frequency.setValueAtTime(440, ctx.currentTime);
      osc.frequency.exponentialRampToValueAtTime(880, ctx.currentTime + 0.2);
      gain.gain.setValueAtTime(0.3, ctx.currentTime);
      gain.gain.exponentialRampToValueAtTime(0.01, ctx.currentTime + 0.35);
      osc.start();
      osc.stop(ctx.currentTime + 0.35);
    } else if (type === "alert") {
      osc.type = "square";
      osc.frequency.setValueAtTime(300, ctx.currentTime);
      gain.gain.setValueAtTime(0.2, ctx.currentTime);
      gain.gain.exponentialRampToValueAtTime(0.01, ctx.currentTime + 0.2);
      osc.start();
      osc.stop(ctx.currentTime + 0.2);
    }
  } catch (e) {
    // Ignore audio errors on unsupported browsers
  }
}

// Toast notification helper
function showToast(message, type = "info") {
  let container = document.getElementById("toast-container");
  if (!container) {
    container = document.createElement("div");
    container.id = "toast-container";
    document.body.appendChild(container);
  }

  const toast = document.createElement("div");
  toast.className = `toast ${type}`;
  let icon = "ℹ️";
  if (type === "success") icon = "✓";
  if (type === "danger") icon = "✕";
  if (type === "warning") icon = "⚠";

  toast.innerHTML = `<span>${icon}</span> <div>${message}</div>`;
  container.appendChild(toast);

  setTimeout(() => {
    toast.style.opacity = "0";
    toast.style.transform = "translateX(100%)";
    toast.style.transition = "all 0.3s ease";
    setTimeout(() => toast.remove(), 300);
  }, 3500);
}

// Format token helper (e.g. 5 -> "T-005")
function formatToken(tok) {
  return "T-" + String(tok).padStart(3, "0");
}

// Priority helper
function getPriorityLabel(pri) {
  if (pri === 3) return { text: "High (Express)", class: "high", badge: "🔴 High" };
  if (pri === 2) return { text: "Medium (Regular)", class: "medium", badge: "🟡 Medium" };
  return { text: "Low (Normal)", class: "low", badge: "🟢 Low" };
}

// Update nav badges
function updateNavBadges() {
  const cart = AppState.get("cart", []);
  const cartCount = cart.reduce((sum, item) => sum + item.qty, 0);
  const badge = document.getElementById("nav-cart-badge");
  if (badge) {
    badge.textContent = cartCount;
    badge.style.display = cartCount > 0 ? "inline-block" : "none";
  }

  const orders = AppState.get("orders", []);
  const waitingOrders = orders.filter(o => o.status === "Waiting" || o.status === "Preparing");
  const queueBadge = document.getElementById("nav-queue-badge");
  if (queueBadge) {
    queueBadge.textContent = waitingOrders.length;
  }
}

// ================= CART OPERATIONS =================
function addToCart(itemId, qty = 1) {
  const menu = AppState.get("menu", []);
  const item = menu.find(i => i.id === itemId);
  if (!item || !item.available) {
    showToast("This item is currently unavailable!", "danger");
    return;
  }

  const cart = AppState.get("cart", []);
  const existing = cart.find(c => c.id === itemId);
  if (existing) {
    existing.qty += qty;
  } else {
    cart.push({
      id: item.id,
      name: item.name,
      price: item.price,
      category: item.category,
      qty: qty
    });
  }

  AppState.set("cart", cart);
  playSound("order");
  showToast(`Added ${qty}x ${item.name} to cart!`, "success");
  updateNavBadges();
}

function removeFromCart(itemId) {
  let cart = AppState.get("cart", []);
  cart = cart.filter(i => i.id !== itemId);
  AppState.set("cart", cart);
  showToast("Item removed from cart.", "warning");
  updateNavBadges();
  renderCartPage();
}

function updateCartQty(itemId, delta) {
  let cart = AppState.get("cart", []);
  const item = cart.find(i => i.id === itemId);
  if (item) {
    item.qty += delta;
    if (item.qty <= 0) {
      cart = cart.filter(i => i.id !== itemId);
    }
    AppState.set("cart", cart);
    updateNavBadges();
    renderCartPage();
  }
}

function calculateCartTotals() {
  const cart = AppState.get("cart", []);
  const subtotal = cart.reduce((acc, it) => acc + (it.price * it.qty), 0);
  const discount = 0; // Discount calculation if coupon applied
  const taxable = Math.max(0, subtotal - discount);
  const tax = Math.round((taxable * 0.05) * 100) / 100; // 5% GST
  const total = taxable + tax;
  return { subtotal, discount, tax, total };
}

// ================= ORDER & TOKEN CREATION =================
function placeOrder(customerName, phone, priority, paymentMethod) {
  const cart = AppState.get("cart", []);
  if (cart.length === 0) {
    showToast("Your cart is empty! Please add some delicious food first.", "danger");
    return null;
  }

  if (!customerName || customerName.trim() === "") {
    showToast("Please enter customer name!", "danger");
    return null;
  }

  const { subtotal, discount, tax, total } = calculateCartTotals();
  const nextTok = AppState.get("nextToken", 6);
  const nextCid = AppState.get("nextCustId", 1006);
  const nextSeq = AppState.get("nextOrderSeq", 1006);

  const now = new Date();
  const dateStr = now.toLocaleDateString('en-GB', { day: '2-digit', month: 'short', year: 'numeric' }) + " " +
                  now.toLocaleTimeString('en-GB', { hour: '2-digit', minute: '2-digit', second: '2-digit' });

  const newOrder = {
    orderId: "ORD" + nextSeq,
    customerId: nextCid,
    customerName: customerName.trim(),
    phone: phone ? phone.trim() : "9900000000",
    token: nextTok,
    priority: parseInt(priority) || 2,
    status: "Waiting",
    paymentMethod: paymentMethod || "UPI",
    paymentStatus: "Paid",
    timestamp: dateStr,
    items: cart.map(i => ({ itemName: i.name, quantity: i.qty, unitPrice: i.price })),
    subtotal: subtotal,
    discount: discount,
    tax: tax,
    total: total,
    txnId: "TXN" + (10000 + nextTok * 43)
  };

  const orders = AppState.get("orders", []);
  orders.push(newOrder);

  // Update counters
  AppState.set("orders", orders);
  AppState.set("nextToken", nextTok + 1);
  AppState.set("nextCustId", nextCid + 1);
  AppState.set("nextOrderSeq", nextSeq + 1);
  AppState.set("cart", []); // Clear cart

  playSound("order");
  showToast(`Order Confirmed! Token ${formatToken(newOrder.token)} generated.`, "success");
  updateNavBadges();

  return newOrder;
}

// ================= QUEUE OPERATIONS =================
function getWaitingQueue() {
  const orders = AppState.get("orders", []);
  return orders.filter(o => o.status === "Waiting" || o.status === "Preparing");
}

function getPriorityQueueSorted() {
  const waiting = getWaitingQueue();
  // Sort descending by priority (3 High, 2 Med, 1 Low), within equal priority preserve FIFO (by token)
  return [...waiting].sort((a, b) => {
    if (b.priority !== a.priority) {
      return b.priority - a.priority;
    }
    return a.token - b.token;
  });
}

function serveNextCustomer() {
  const pq = getPriorityQueueSorted();
  if (pq.length === 0) {
    showToast("No customers in queue to serve!", "warning");
    return null;
  }

  const topCustomer = pq[0];
  const orders = AppState.get("orders", []);
  const target = orders.find(o => o.orderId === topCustomer.orderId);

  if (target) {
    if (target.status === "Waiting") {
      target.status = "Preparing";
      showToast(`Token ${formatToken(target.token)} (${target.customerName}) is now PREPARING!`, "info");
    } else if (target.status === "Preparing") {
      target.status = "Ready";
      showToast(`Token ${formatToken(target.token)} (${target.customerName}) is READY for pickup!`, "warning");
    } else {
      target.status = "Completed";
      showToast(`Token ${formatToken(target.token)} (${target.customerName}) has been SERVED & COMPLETED!`, "success");
    }
    AppState.set("orders", orders);
    playSound("serve");
    refreshAllViews();
    return target;
  }
  return null;
}

function skipCustomer() {
  const orders = AppState.get("orders", []);
  const waiting = orders.filter(o => o.status === "Waiting");
  if (waiting.length === 0) {
    showToast("No waiting customer to skip.", "warning");
    return;
  }

  const frontOrder = waiting[0];
  // Increase token virtual sequence or move to rear
  const maxTok = Math.max(...orders.map(o => o.token)) + 1;
  frontOrder.token = maxTok;
  AppState.set("orders", orders);
  showToast(`Customer ${frontOrder.customerName} moved to the rear of queue.`, "info");
  refreshAllViews();
}

function undoLastOrder() {
  const orders = AppState.get("orders", []);
  // Find latest active or completed order
  if (orders.length === 0) {
    showToast("No orders available to undo.", "warning");
    return;
  }

  const lastOrder = orders[orders.length - 1];
  if (lastOrder.status === "Cancelled") {
    showToast("Last order is already cancelled.", "warning");
    return;
  }

  lastOrder.status = "Cancelled";
  AppState.set("orders", orders);
  playSound("alert");
  showToast(`[UNDO] Order ${lastOrder.orderId} (Token ${formatToken(lastOrder.token)}) cancelled. Refund issued!`, "danger");
  refreshAllViews();
}

function clearWaitingQueue() {
  const orders = AppState.get("orders", []);
  orders.forEach(o => {
    if (o.status === "Waiting" || o.status === "Preparing") {
      o.status = "Cancelled";
    }
  });
  AppState.set("orders", orders);
  showToast("Waiting queue has been cleared.", "warning");
  refreshAllViews();
}

// ================= VISUALIZERS RENDERING =================
function renderNormalQueueVisual(containerId) {
  const container = document.getElementById(containerId);
  if (!container) return;

  const orders = AppState.get("orders", []);
  const waiting = orders.filter(o => o.status === "Waiting" || o.status === "Preparing");

  if (waiting.length === 0) {
    container.innerHTML = `<div style="text-align:center; padding:1.5rem; color:var(--text-muted); font-family:monospace;">Queue is EMPTY [ FRONT = NULL | REAR = NULL ]</div>`;
    return;
  }

  let html = `<div class="queue-visual-track">`;
  waiting.forEach((cust, idx) => {
    const isFront = idx === 0;
    const isRear = idx === waiting.length - 1;
    const pri = getPriorityLabel(cust.priority);

    html += `
      <div class="queue-visual-node">
        ${isFront ? '<span class="node-pointer-tag">FRONT</span>' : ''}
        <div class="node-token">${formatToken(cust.token)}</div>
        <div class="node-name" title="${cust.customerName}">${cust.customerName}</div>
        <span class="node-tag" style="background:${pri.class === 'high' ? '#fee2e2' : pri.class === 'medium' ? '#fef3c7' : '#e0f2fe'}; color:${pri.class === 'high' ? '#dc2626' : pri.class === 'medium' ? '#d97706' : '#0284c7'};">${cust.status}</span>
        ${isRear ? '<span class="node-pointer-tag node-pointer-rear">REAR</span>' : ''}
      </div>
    `;

    if (idx < waiting.length - 1) {
      html += `<div class="queue-arrow">➔</div>`;
    }
  });
  html += `</div>`;
  container.innerHTML = html;
}

function renderPriorityQueueVisual(containerId) {
  const container = document.getElementById(containerId);
  if (!container) return;

  const pq = getPriorityQueueSorted();
  const high = pq.filter(o => o.priority === 3);
  const med = pq.filter(o => o.priority === 2);
  const low = pq.filter(o => o.priority === 1);

  const renderLane = (label, list, laneClass) => {
    let itemsHtml = "";
    if (list.length === 0) {
      itemsHtml = `<span style="color:var(--text-muted); font-size:0.85rem; font-style:italic;">(No orders)</span>`;
    } else {
      list.forEach((o, i) => {
        itemsHtml += `
          <div style="background:var(--bg-alt); border:1px solid var(--border); border-radius:6px; padding:0.4rem 0.75rem; font-size:0.8rem; font-weight:700; display:inline-flex; align-items:center; gap:0.4rem;">
            <span style="color:var(--primary); font-family:monospace;">${formatToken(o.token)}</span>
            <span>${o.customerName}</span>
          </div>
        `;
        if (i < list.length - 1) itemsHtml += `<span style="color:var(--text-muted); font-weight:bold;">➔</span>`;
      });
    }

    return `
      <div class="pq-lane ${laneClass}">
        <div class="pq-lane-label">${label}</div>
        <div style="display:flex; align-items:center; gap:0.5rem; flex-wrap:wrap; flex:1;">${itemsHtml}</div>
      </div>
    `;
  };

  container.innerHTML = `
    ${renderLane("🔴 HIGH (Express)", high, "high")}
    ${renderLane("🟡 MEDIUM (Regular)", med, "medium")}
    ${renderLane("🟢 LOW (Normal)", low, "low")}
  `;
}

function renderCircularQueueVisual(containerId) {
  const container = document.getElementById(containerId);
  if (!container) return;

  const orders = AppState.get("orders", []);
  const waiting = orders.filter(o => o.status === "Waiting" || o.status === "Preparing");
  const capacity = 10;

  let slotsHtml = "";
  for (let i = 0; i < capacity; i++) {
    const cust = waiting[i];
    const isOccupied = !!cust;
    const isFront = i === 0 && waiting.length > 0;
    const isRear = i === waiting.length - 1 && waiting.length > 0;

    slotsHtml += `
      <div class="circular-slot ${isOccupied ? 'occupied' : ''} ${isFront ? 'is-front' : ''}">
        <div class="circular-slot-idx">Slot #${i}</div>
        <div class="circular-slot-val">${isOccupied ? formatToken(cust.token) : '--'}</div>
        <div style="font-size:0.65rem; font-weight:700; color:${isFront ? 'var(--primary)' : isRear ? 'var(--secondary)' : 'transparent'};">
          ${isFront && isRear ? 'F & R' : isFront ? 'FRONT' : isRear ? 'REAR' : '.'}
        </div>
      </div>
    `;
  }

  container.innerHTML = `
    <div class="circular-slots-grid">${slotsHtml}</div>
    <div style="font-size:0.8rem; color:var(--text-muted); display:flex; justify-content:space-between; margin-top:0.5rem;">
      <span>Capacity: ${capacity} Slots</span>
      <span>Active Tokens: ${waiting.length} / ${capacity}</span>
      <span>Modulo: (rear + 1) % ${capacity}</span>
    </div>
  `;
}

function renderDequeVisual(containerId) {
  const container = document.getElementById(containerId);
  if (!container) return;

  const orders = AppState.get("orders", []);
  const waiting = orders.filter(o => o.status === "Waiting" || o.status === "Preparing");

  if (waiting.length === 0) {
    container.innerHTML = `<div style="text-align:center; padding:1.5rem; color:var(--text-muted); font-family:monospace;">Deque is EMPTY</div>`;
    return;
  }

  let html = `<div class="queue-visual-track">`;
  waiting.forEach((cust, idx) => {
    const isFront = idx === 0;
    const isRear = idx === waiting.length - 1;

    html += `
      <div class="queue-visual-node" style="border-color:var(--secondary);">
        ${isFront ? '<span class="node-pointer-tag" style="background:var(--secondary);">FRONT [In/Del]</span>' : ''}
        <div class="node-token" style="color:var(--secondary);">${formatToken(cust.token)}</div>
        <div class="node-name">${cust.customerName}</div>
        ${isRear ? '<span class="node-pointer-tag node-pointer-rear" style="background:var(--secondary);">REAR [In/Del]</span>' : ''}
      </div>
    `;

    if (idx < waiting.length - 1) {
      html += `<div class="queue-arrow" style="color:var(--secondary);">⮂➔</div>`;
    }
  });
  html += `</div>`;
  container.innerHTML = html;
}

function renderStackVisual(containerId) {
  const container = document.getElementById(containerId);
  if (!container) return;

  const orders = AppState.get("orders", []);
  const recent = [...orders].slice(-5).reverse(); // Last 5 orders, top is latest

  if (recent.length === 0) {
    container.innerHTML = `<div style="text-align:center; padding:1.5rem; color:var(--text-muted); font-family:monospace;">Stack is EMPTY [ TOP = NULL ]</div>`;
    return;
  }

  let html = `<div class="stack-visual-box">`;
  recent.reverse().forEach((ord, idx) => {
    const isTop = idx === recent.length - 1;
    html += `
      <div class="stack-item ${isTop ? 'top-item' : ''}">
        <div>
          ${isTop ? '<span style="font-size:0.65rem; background:var(--primary); color:#fff; padding:0.1rem 0.35rem; border-radius:3px; margin-right:4px;">TOP</span>' : ''}
          <span style="font-family:monospace; font-weight:700;">${ord.orderId}</span>
          <span style="color:var(--text-muted); margin-left:4px;">(${formatToken(ord.token)})</span>
        </div>
        <div>
          <span>${ord.customerName}</span>
          <span style="font-weight:700; margin-left:8px; font-family:monospace;">₹${ord.total}</span>
        </div>
      </div>
    `;
  });
  html += `</div><div style="text-align:center; font-size:0.75rem; color:var(--text-muted); margin-top:0.4rem;">LIFO (Last In First Out) - Undo operates on TOP</div>`;
  container.innerHTML = html;
}

// ================= REAL-TIME SIMULATION =================
let simulationInterval = null;

function runSimulation() {
  const simBtn = document.getElementById("btn-sim-run");
  if (simBtn) simBtn.disabled = true;

  showToast("🚀 Real-Time Queue Simulation Started!", "info");

  const simNames = ["Aarav Sharma", "Diya Patel", "Kabir Singh", "Ananya Roy", "Rohan Mehta"];
  const simPriorities = [2, 3, 1, 3, 2];
  const simFoods = [101, 201, 305, 401, 501]; // Burger, Pizza, Biryani, Fries, Coke
  let step = 0;

  const simTimer = setInterval(() => {
    if (step < simNames.length) {
      const name = simNames[step];
      const pri = simPriorities[step];
      const foodId = simFoods[step];

      const menu = AppState.get("menu", []);
      const food = menu.find(f => f.id === foodId) || menu[0];

      // Add to cart & place order automatically
      AppState.set("cart", [{ id: food.id, name: food.name, price: food.price, category: food.category, qty: 1 }]);
      const ord = placeOrder(name, "98" + Math.floor(10000000 + Math.random() * 90000000), pri, "UPI");

      showToast(`[Sim] Customer ${name} placed order (${formatToken(ord.token)}) with priority ${getPriorityLabel(pri).badge}`, "info");
      refreshAllViews();
      step++;
    } else if (step === simNames.length) {
      showToast("[Sim] Counter is now serving next high priority customer...", "warning");
      serveNextCustomer();
      step++;
    } else if (step === simNames.length + 1) {
      showToast("[Sim] Serving subsequent customer...", "warning");
      serveNextCustomer();
      step++;
    } else {
      clearInterval(simTimer);
      showToast("✓ Real-Time Simulation Finished!", "success");
      if (simBtn) simBtn.disabled = false;
      refreshAllViews();
    }
  }, 1800);
}

// ================= REFRESH ALL VIEWS =================
function refreshAllViews() {
  updateNavBadges();
  renderNormalQueueVisual("ds-normal-queue");
  renderPriorityQueueVisual("ds-priority-queue");
  renderCircularQueueVisual("ds-circular-queue");
  renderDequeVisual("ds-deque");
  renderStackVisual("ds-stack");
  updateQueueDashboardHeader();
  renderAdminMetrics();
  renderOrdersTable();
}

function updateQueueDashboardHeader() {
  const currentTokenEl = document.getElementById("dash-current-token");
  const currentMetaEl = document.getElementById("dash-current-meta");
  const queueLengthEl = document.getElementById("dash-queue-length");

  const waiting = getWaitingQueue();
  const pq = getPriorityQueueSorted();

  if (currentTokenEl) {
    if (pq.length > 0) {
      currentTokenEl.textContent = formatToken(pq[0].token);
      if (currentMetaEl) {
        currentMetaEl.textContent = `${pq[0].customerName} • ${pq[0].status} (${getPriorityLabel(pq[0].priority).text})`;
      }
    } else {
      currentTokenEl.textContent = "READY";
      if (currentMetaEl) currentMetaEl.textContent = "No active orders in queue";
    }
  }

  if (queueLengthEl) {
    queueLengthEl.textContent = waiting.length;
  }
}

function renderAdminMetrics() {
  const orders = AppState.get("orders", []);
  const waiting = orders.filter(o => o.status === "Waiting");
  const preparing = orders.filter(o => o.status === "Preparing");
  const completed = orders.filter(o => o.status === "Completed");
  const totalRev = orders.filter(o => o.status === "Completed").reduce((sum, o) => sum + o.total, 0);

  const setVal = (id, val) => {
    const el = document.getElementById(id);
    if (el) el.textContent = val;
  };

  setVal("metric-total-orders", orders.length);
  setVal("metric-waiting", waiting.length);
  setVal("metric-preparing", preparing.length);
  setVal("metric-completed", completed.length);
  setVal("metric-revenue", `₹${Math.round(totalRev)}`);
  setVal("metric-queue-len", waiting.length + preparing.length);
}

function renderOrdersTable() {
  const tableBody = document.getElementById("admin-orders-tbody");
  if (!tableBody) return;

  const orders = AppState.get("orders", []);
  const query = (document.getElementById("search-input")?.value || "").toLowerCase().trim();

  const filtered = orders.filter(o => {
    if (!query) return true;
    return o.orderId.toLowerCase().includes(query) ||
           o.customerName.toLowerCase().includes(query) ||
           formatToken(o.token).toLowerCase().includes(query) ||
           (o.phone && o.phone.includes(query)) ||
           String(o.customerId).includes(query);
  });

  if (filtered.length === 0) {
    tableBody.innerHTML = `<tr><td colspan="8" style="text-align:center; padding:1.5rem; color:var(--text-muted);">No matching orders found.</td></tr>`;
    return;
  }

  tableBody.innerHTML = filtered.map(o => `
    <tr>
      <td style="font-family:monospace; font-weight:700;">${o.orderId}</td>
      <td style="font-family:monospace; font-weight:800; color:var(--primary);">${formatToken(o.token)}</td>
      <td><strong>${o.customerName}</strong><br><small style="color:var(--text-muted);">${o.phone}</small></td>
      <td style="max-width:200px; font-size:0.85rem;">${o.items.map(it => `${it.itemName} x${it.quantity}`).join(", ")}</td>
      <td><span class="role-pill ${getPriorityLabel(o.priority).class}">${getPriorityLabel(o.priority).text}</span></td>
      <td style="font-family:monospace; font-weight:700;">₹${o.total}</td>
      <td><span class="status-pill status-${o.status.toLowerCase()}">${o.status}</span></td>
      <td>
        <button class="btn btn-outline btn-sm" onclick="viewOrderBill('${o.orderId}')">Bill 🧾</button>
      </td>
    </tr>
  `).join("");
}

function viewOrderBill(orderId) {
  sessionStorage.setItem("view_bill_order_id", orderId);
  window.location.href = "billing.html";
}

// Global initialization on DOM ready
document.addEventListener("DOMContentLoaded", () => {
  applyTheme();
  updateNavBadges();
  refreshAllViews();

  // Listen for storage changes from other browser tabs
  window.addEventListener("storage", () => {
    refreshAllViews();
  });

  window.addEventListener("stateChanged", () => {
    refreshAllViews();
  });
});
