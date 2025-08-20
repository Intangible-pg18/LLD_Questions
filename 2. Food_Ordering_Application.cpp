#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <stdexcept>

// Use std namespace as requested
using namespace std;

// --- A. FORWARD DECLARATIONS ---
class User;
class Restaurant;
class Order;
class MenuItem;
class DeliveryPartner;
class IOrderState;
class IOrderObserver;
class PaymentStrategy;
class UserManager;
class RestaurantManager;
class OrderManager;

// --- B. ENUMS & CORE DATA STRUCTURES ---
enum class ItemType { VEG, NON_VEG, VEGAN };
enum class PaymentMethodType { CREDIT_CARD, UPI, PAYPAL };

class Location {
public:
    double latitude;
    double longitude;
};

class Address {
public:
    string street;
    string city;
    Location coordinates;
};

// --- C. PATTERN INTERFACES ---
class PaymentStrategy {
public:
    virtual bool pay(double amount) = 0;
};

class IOrderState {
public:
    virtual void process(Order* order) { cout << "No action in this state." << endl; }
    virtual string getStatusName() = 0;
};

class IOrderObserver {
public:
    virtual void onStatusUpdated(Order* order) = 0;
};

class Menu {
public:
    class IMenuItemFilter {
    public:
        virtual bool matches(MenuItem* item) = 0;
    };
    vector<MenuItem*> items;
};

// --- D. CORE DOMAIN MODELS ---
class User {
public:
    string userId;
    string name;
};

class MenuItem {
public:
    string itemId;
    string name;
    double price;
    ItemType type;
};

class Restaurant {
public:
    string restaurantId;
    string ownerUserId;
    string name;
    Address* address;
    Menu* menu;
};

class Cart {
public:
    string userId;
    string restaurantId;
    map<string, int> items; // MenuItem ID -> quantity
    
    double calculateTotal(RestaurantManager* rm); // Needs manager to find item prices
};

class Order {
public:
    string orderId;
    string userId;
    string restaurantId;
    double totalAmount;
    IOrderState* currentState;
    vector<IOrderObserver*> observers;

    void setState(IOrderState* newState);
    void attach(IOrderObserver* observer) { observers.push_back(observer); }
    void notify();
};

// --- E. FACTORY CLASSES ---

// 1. Payment Strategy Factory
class PaymentStrategyFactory {
public:
    static PaymentStrategy* create(PaymentMethodType type, const map<string, string>& details);
};

// 2. Order State Factory
class OrderStateFactory {
public:
    static IOrderState* create(const string& statusName);
};

// 3. Menu Filter Factory
class MenuItemFilterFactory {
public:
    static Menu::IMenuItemFilter* create(const string& filterType, double val1 = 0, double val2 = 0);
};

// 4. Observer (Notifier) Factory
class NotifierFactory {
public:
    static vector<IOrderObserver*> createDefaultNotifiers();
};


// --- F. SINGLETON MANAGER CLASSES ---

class UserManager {
private:
    map<string, User*> users;
    UserManager() {} // Private constructor
public:
    // Delete copy and assignment
    UserManager(const UserManager&) = delete;
    void operator=(const UserManager&) = delete;

    static UserManager& getInstance() {
        static UserManager instance; // Meyers' Singleton
        return instance;
    }

    User* registerUser(const string& id, const string& name) {
        if (users.count(id)) return nullptr;
        User* newUser = new User{id, name};
        users[id] = newUser;
        return newUser;
    }
    User* findUserById(const string& id) {
        return users.count(id) ? users[id] : nullptr;
    }
};

class RestaurantManager {
private:
    map<string, Restaurant*> restaurants;
    map<string, MenuItem*> menuItems; // Global map for quick lookup
    RestaurantManager() {}
public:
    RestaurantManager(const RestaurantManager&) = delete;
    void operator=(const RestaurantManager&) = delete;

    static RestaurantManager& getInstance() {
        static RestaurantManager instance;
        return instance;
    }
    
    Restaurant* registerRestaurant(const string& name, Address* address, const string& ownerId) {
        string newId = "REST" + to_string(restaurants.size() + 1);
        Restaurant* r = new Restaurant{newId, ownerId, name, address, new Menu()};
        restaurants[newId] = r;
        return r;
    }

    void addMenuItem(const string& restaurantId, MenuItem* item) {
        if (restaurants.count(restaurantId)) {
            restaurants[restaurantId]->menu->items.push_back(item);
            menuItems[item->itemId] = item;
        }
    }
    
    Restaurant* findRestaurantById(const string& id) {
        return restaurants.count(id) ? restaurants[id] : nullptr;
    }

    MenuItem* findMenuItemById(const string& id) {
        return menuItems.count(id) ? menuItems[id] : nullptr;
    }
};

class OrderManager {
private:
    map<string, Order*> orders;
    OrderManager() {}
public:
    OrderManager(const OrderManager&) = delete;
    void operator=(const OrderManager&) = delete;

    static OrderManager& getInstance() {
        static OrderManager instance;
        return instance;
    }

    Order* placeOrder(Cart* cart, PaymentMethodType pmt, const map<string, string>& pmtDetails) {
        // Use factories to create dependencies
        PaymentStrategy* payment = PaymentStrategyFactory::create(pmt, pmtDetails);
        if (!payment) {
            cout << "Order placement failed: Invalid payment details." << endl;
            return nullptr;
        }

        double total = cart->calculateTotal(&RestaurantManager::getInstance());
        if (!payment->pay(total)) {
            cout << "Order placement failed: Payment was not successful." << endl;
            return nullptr;
        }
        
        Order* order = new Order();
        order->orderId = "ORD" + to_string(orders.size() + 101);
        order->userId = cart->userId;
        order->restaurantId = cart->restaurantId;
        order->totalAmount = total;
        
        // Attach observers using the factory
        vector<IOrderObserver*> notifiers = NotifierFactory::createDefaultNotifiers();
        for (auto* notifier : notifiers) {
            order->attach(notifier);
        }

        // Set initial state using the factory
        order->setState(OrderStateFactory::create("PLACED"));
        orders[order->orderId] = order;
        return order;
    }
};

// --- G. CONCRETE IMPLEMENTATIONS OF PATTERN INTERFACES ---

// Payment Strategies
class CreditCardPayment : public PaymentStrategy {
    string cardNum;
public:
    CreditCardPayment(string num) : cardNum(num) {}
    bool pay(double amount) override {
        cout << "Paid $" << amount << " using Credit Card " << cardNum << endl;
        return true;
    }
};
class UpiPayment : public PaymentStrategy {
    string upiId;
public:
    UpiPayment(string id) : upiId(id) {}
    bool pay(double amount) override {
        cout << "Paid $" << amount << " using UPI " << upiId << endl;
        return true;
    }
};

// Order States
class PlacedState : public IOrderState {
public:
    void process(Order* order) override {
        cout << "  (Action: Restaurant accepts order)" << endl;
        order->setState(OrderStateFactory::create("ACCEPTED"));
    }
    string getStatusName() override { return "PLACED"; }
};
class AcceptedState : public IOrderState {
public:
    void process(Order* order) override {
        cout << "  (Action: Order is delivered)" << endl;
        order->setState(OrderStateFactory::create("DELIVERED"));
    }
    string getStatusName() override { return "ACCEPTED"; }
};
class DeliveredState : public IOrderState {
public:
    string getStatusName() override { return "DELIVERED"; }
};

// Order Observers (Notifiers)
class UserNotifier : public IOrderObserver {
public:
    void onStatusUpdated(Order* order) override {
        User* user = UserManager::getInstance().findUserById(order->userId);
        if (user) {
            cout << "  -> PUSH to User " << user->name << ": Order " << order->orderId << " is now " << order->currentState->getStatusName() << "." << endl;
        }
    }
};
class RestaurantNotifier : public IOrderObserver {
public:
    void onStatusUpdated(Order* order) override {
        Restaurant* r = RestaurantManager::getInstance().findRestaurantById(order->restaurantId);
        if (r) {
            cout << "  -> DASHBOARD UPDATE for " << r->name << ": Order " << order->orderId << " is now " << order->currentState->getStatusName() << "." << endl;
        }
    }
};

// Menu Filters
class VegFilter : public Menu::IMenuItemFilter {
public:
    bool matches(MenuItem* item) override { return item->type == ItemType::VEG; }
};
class PriceFilter : public Menu::IMenuItemFilter {
    double maxPrice;
public:
    PriceFilter(double max) : maxPrice(max) {}
    bool matches(MenuItem* item) override { return item->price <= maxPrice; }
};


// --- H. LINKING IMPLEMENTATIONS (Factories, Order methods, etc.) ---

// Now we can implement the factory methods that depend on the concrete classes above
PaymentStrategy* PaymentStrategyFactory::create(PaymentMethodType type, const map<string, string>& details) {
    if (type == PaymentMethodType::CREDIT_CARD) return new CreditCardPayment(details.at("cardNumber"));
    if (type == PaymentMethodType::UPI) return new UpiPayment(details.at("upiId"));
    // Add other payment methods here
    return nullptr;
}

IOrderState* OrderStateFactory::create(const string& statusName) {
    if (statusName == "PLACED") return new PlacedState();
    if (statusName == "ACCEPTED") return new AcceptedState();
    if (statusName == "DELIVERED") return new DeliveredState();
    return new PlacedState(); // Default
}

Menu::IMenuItemFilter* MenuItemFilterFactory::create(const string& filterType, double val1, double val2) {
    if (filterType == "VEG_ONLY") return new VegFilter();
    if (filterType == "PRICE_LESS_THAN") return new PriceFilter(val1);
    // Add other filter types here
    return nullptr;
}

vector<IOrderObserver*> NotifierFactory::createDefaultNotifiers() {
    return {new UserNotifier(), new RestaurantNotifier()};
}

// And methods of core models that depend on factories/managers
void Order::setState(IOrderState* newState) {
    currentState = newState;
    cout << "\n>>> Order " << orderId << " status changed to: " << currentState->getStatusName() << " <<<" << endl;
    notify();
}

void Order::notify() {
    for (auto* obs : observers) {
        obs->onStatusUpdated(this);
    }
}

double Cart::calculateTotal(RestaurantManager* rm) {
    double total = 0.0;
    for (auto const& [itemId, quantity] : items) {
        MenuItem* item = rm->findMenuItemById(itemId);
        if (item) {
            total += item->price * quantity;
        }
    }
    return total;
}


// --- I. MAIN FUNCTION (DEMONSTRATION) ---
int main() {
    cout << "--- System Setup & Onboarding ---" << endl;
    UserManager::getInstance().registerUser("owner01", "Bob");
    Restaurant* r = RestaurantManager::getInstance().registerRestaurant("Bob's Bistro", new Address{"Main St", "Anytown"}, "owner01");
    
    MenuItem* i1 = new MenuItem{"B01", "Veggie Burger", 250.0, ItemType::VEG};
    MenuItem* i2 = new MenuItem{"B02", "Chicken Burger", 350.0, ItemType::NON_VEG};
    RestaurantManager::getInstance().addMenuItem(r->restaurantId, i1);
    RestaurantManager::getInstance().addMenuItem(r->restaurantId, i2);

    cout << "\n--- User Interaction ---" << endl;
    UserManager::getInstance().registerUser("cust01", "Alice");
    
    cout << "\n--- Menu Filtering (using Factory) ---" << endl;
    Menu::IMenuItemFilter* vegFilter = MenuItemFilterFactory::create("VEG_ONLY");
    cout << "Veg items at " << r->name << ":" << endl;
    for(auto* item : r->menu->items) {
        if(vegFilter->matches(item)) {
            cout << " - " << item->name << endl;
        }
    }

    cout << "\n--- Cart & Order Placement (using Factories) ---" << endl;
    Cart* aliceCart = new Cart();
    aliceCart->userId = "cust01";
    aliceCart->restaurantId = r->restaurantId;
    aliceCart->items["B01"] = 2; // 2 Veggie Burgers

    map<string, string> paymentDetails = {{"upiId", "alice@okbank"}};
    
    // The OrderManager uses all factories internally to place the order
    Order* alicesOrder = OrderManager::getInstance().placeOrder(aliceCart, PaymentMethodType::UPI, paymentDetails);

    if (alicesOrder) {
        cout << "\n--- Order State Progression (State Pattern in action) ---" << endl;
        // The first notification happened when the state was set to PLACED.
        
        // Simulate further processing
        alicesOrder->currentState->process(alicesOrder);
        alicesOrder->currentState->process(alicesOrder);
    }

    // NOTE: This program leaks memory due to the "no destructors" and "raw pointers"
    // constraints. In a real application, smart pointers (std::unique_ptr,
    // std::shared_ptr) are essential for proper memory management.

    return 0;
}
