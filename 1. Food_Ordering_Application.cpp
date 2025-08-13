#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

// Use std namespace as requested
using namespace std;

// --- A. FORWARD DECLARATIONS ---
// Core Models
class User;
class Restaurant;
class Order;
class MenuItem;
class DeliveryPartner;

// Manager Classes
class UserManager;
class RestaurantManager;
class OrderManager;
class DeliveryPartnerManager;

// Pattern Interfaces & Classes
class IOrderState;
class IOrderObserver;
class DeliveryPartnerAssignmentStrategy;


// --- B. CORE DOMAIN MODELS & DATA STRUCTURES ---

class Location {
public:
    double latitude;
    double longitude;

    double distanceTo(const Location& other) {
        return sqrt(pow(latitude - other.latitude, 2) + pow(longitude - other.longitude, 2));
    }
};

class Address {
public:
    string street;
    string city;
    string pinCode;
    Location coordinates;
};

class User {
public:
    string userId;
    string name;
    string phone;
    vector<Address*> savedAddresses;
    // string getUserId() const;
    // string getName() const;
};

enum class ItemType { VEG, NON_VEG, VEGAN };

class MenuItem {
public:
    string itemId;
    string name;
    double price;
    ItemType type;
    double rating;
    // string getItemId() const;
    // ... other getters
};

class Menu {
public:
    vector<MenuItem*> items;

    // --- 1. MENU FILTER EXTENSIBILITY (STRATEGY/SPECIFICATION PATTERN) ---
    class IMenuItemFilter {
    public:
        virtual bool matches(MenuItem* item) = 0;
    };

    vector<MenuItem*> filter(const vector<IMenuItemFilter*>& filters) {
        vector<MenuItem*> filteredItems;
        for (MenuItem* item : items) {
            bool allFiltersMatch = true;
            for (IMenuItemFilter* filter : filters) {
                if (!filter->matches(item)) {
                    allFiltersMatch = false;
                    break;
                }
            }
            if (allFiltersMatch) {
                filteredItems.push_back(item);
            }
        }
        return filteredItems;
    }
};

class Restaurant {
public:
    string restaurantId;
    string ownerUserId; // ID of the owner
    string name;
    Address* address;
    Menu* menu;
    double serviceRadius;
    bool isOpen;

    bool isDeliverable(const Location& userLocation) {
        return address->coordinates.distanceTo(userLocation) <= serviceRadius;
    }
};

class DeliveryPartner {
public:
    string partnerId;
    string name;
    Location currentLocation;
    double rating;
    bool isAvailable;
};

// --- 3. CART USES IDs ---
class Cart {
public:
    string userId;       // ID of the user who owns the cart
    string restaurantId; // ID of the restaurant this cart is for
    map<string, int> items; // Map of MenuItem ID to quantity

    void addItem(const string& itemId, int quantity) {
        items[itemId] += quantity;
    }
};

// --- C. OBSERVER PATTERN FOR NOTIFICATIONS ---

// --- 5. OBSERVER PATTERN INTERFACE ---
class IOrderObserver {
public:
    virtual void onStatusUpdated(Order* order) = 0;
};

// --- 5. CONCRETE OBSERVERS ---
class UserNotifier : public IOrderObserver {
private:
    UserManager* userManager; // Needs a manager to fetch user details
public:
    UserNotifier(UserManager* um) : userManager(um) {}
    void onStatusUpdated(Order* order) override; // Implemented after Order & Managers
};

class RestaurantNotifier : public IOrderObserver {
private:
    RestaurantManager* restaurantManager; // Needs a manager to fetch restaurant details
public:
    RestaurantNotifier(RestaurantManager* rm) : restaurantManager(rm) {}
    void onStatusUpdated(Order* order) override; // Implemented after Order & Managers
};


// --- D. STATE PATTERN FOR ORDER STATUS ---

class Order {
public:
    string orderId;
    string userId;
    string restaurantId;
    string deliveryPartnerId; // Initially empty
    double totalAmount;
    IOrderState* currentState; // The current state of the order
    vector<IOrderObserver*> observers;

    void setState(IOrderState* newState);

    // Delegate behavior to the current state object
    void process() { /* calls currentState->process(this) */ }
    void cancel() { /* calls currentState->cancel(this) */ }

    // Observer management
    void attach(IOrderObserver* observer) { observers.push_back(observer); }
    void detach(IOrderObserver* observer) { /* remove logic here */ }
    void notify() {
        for(auto* obs : observers) {
            obs->onStatusUpdated(this);
        }
    }
};

// --- 2. STATE PATTERN INTERFACE ---
class IOrderState {
public:
    virtual void process(Order* order) { cout << "No action in this state." << endl; }
    virtual void cancel(Order* order) { cout << "Cannot cancel in this state." << endl; }
    virtual string getStatusName() = 0;
};

// --- 2. CONCRETE STATE IMPLEMENTATIONS ---
class PlacedState : public IOrderState {
public:
    void process(Order* order) override; // Will transition to AcceptedState
    void cancel(Order* order) override;  // Will transition to CancelledState
    string getStatusName() override { return "PLACED"; }
};

class AcceptedState : public IOrderState {
public:
    void process(Order* order) override; // Will transition to PreparingState
    string getStatusName() override { return "ACCEPTED"; }
};

class DeliveredState : public IOrderState {
public:
    string getStatusName() override { return "DELIVERED"; }
};

class CancelledState : public IOrderState {
public:
    string getStatusName() override { return "CANCELLED"; }
};

// State transition logic needs to be defined after Order is fully defined
void Order::setState(IOrderState* newState) {
    // In real code with smart pointers, this is automatic
    // delete currentState; 
    currentState = newState;
    cout << "\n>>> Order " << orderId << " status changed to: " << currentState->getStatusName() << " <<<" << endl;
    notify();
}

void PlacedState::process(Order* order) {
    cout << "Restaurant has accepted the order." << endl;
    order->setState(new AcceptedState());
}
void PlacedState::cancel(Order* order) {
    cout << "User has cancelled the order." << endl;
    order->setState(new CancelledState());
}
void AcceptedState::process(Order* order) {
    cout << "Order is prepared and ready for delivery." << endl;
    // In a real system, this might transition to a "ReadyForPickup" state
    // which then triggers the delivery partner assignment.
    // For simplicity, we'll assume it's delivered after this.
    order->setState(new DeliveredState());
}

// --- E. MANAGER CLASSES ---

// --- 4. MANAGER CLASSES ---
class UserManager {
private:
    map<string, User*> users;
public:
    User* registerUser(const string& id, const string& name, const string& phone) {
        if (users.count(id)) return nullptr; // User already exists
        User* newUser = new User{id, name, phone};
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
public:
    // --- 6. RESTAURANT ONBOARDING FUNCTIONALITY ---
    Restaurant* registerRestaurant(const string& name, Address* address, const string& ownerId) {
        string newId = "REST" + to_string(restaurants.size() + 1);
        Restaurant* newRestaurant = new Restaurant{newId, ownerId, name, address, new Menu(), 5.0, true};
        restaurants[newId] = newRestaurant;
        cout << "Restaurant '" << name << "' registered by owner " << ownerId << " with ID " << newId << "." << endl;
        return newRestaurant;
    }

    void addMenuItem(const string& restaurantId, const string& ownerId, MenuItem* item) {
        Restaurant* r = findRestaurantById(restaurantId);
        if (!r) {
            cout << "Error: Restaurant not found." << endl;
            return;
        }
        if (r->ownerUserId != ownerId) {
            cout << "Error: Unauthorized. Only the owner can add menu items." << endl;
            return;
        }
        r->menu->items.push_back(item);
        cout << "Item '" << item->name << "' added to restaurant " << r->name << "." << endl;
    }
    
    Restaurant* findRestaurantById(const string& id) {
        return restaurants.count(id) ? restaurants[id] : nullptr;
    }

    vector<Restaurant*> searchRestaurants(const string& query, const Location& userLocation) {
        vector<Restaurant*> results;
        for (auto const& [id, r] : restaurants) {
            if (r->isOpen && r->name.find(query) != string::npos && r->isDeliverable(userLocation)) {
                results.push_back(r);
            }
        }
        return results;
    }
};

class DeliveryPartnerManager {
private:
    map<string, DeliveryPartner*> partners;
public:
    void addPartner(const string& id, const string& name, const Location& loc) {
        partners[id] = new DeliveryPartner{id, name, loc, 5.0, true};
    }
    vector<DeliveryPartner*> getAvailablePartners() {
        vector<DeliveryPartner*> available;
        for (auto const& [id, p] : partners) {
            if (p->isAvailable) {
                available.push_back(p);
            }
        }
        return available;
    }
};


class OrderManager {
private:
    map<string, Order*> orders;
    UserManager* userManager;
    RestaurantManager* restaurantManager;
    // ... other managers
    vector<IOrderObserver*> defaultObservers;

public:
    OrderManager(UserManager* um, RestaurantManager* rm) : userManager(um), restaurantManager(rm) {}
    
    void subscribe(IOrderObserver* observer) {
        defaultObservers.push_back(observer);
    }
    
    Order* placeOrder(Cart* cart) {
        // Validation logic
        if (!userManager->findUserById(cart->userId) || !restaurantManager->findRestaurantById(cart->restaurantId)) {
            cout << "Error: Invalid user or restaurant." << endl;
            return nullptr;
        }

        Order* order = new Order();
        order->orderId = "ORD" + to_string(orders.size() + 101);
        order->userId = cart->userId;
        order->restaurantId = cart->restaurantId;
        order->totalAmount = 500.0; // Simplified calculation
        
        // Attach all default observers
        for(auto* obs : defaultObservers) {
            order->attach(obs);
        }
        
        // Set initial state
        order->setState(new PlacedState());

        orders[order->orderId] = order;
        cout << "Order " << order->orderId << " has been successfully placed by user " << cart->userId << "." << endl;

        return order;
    }

    // In a real system, you would have an assignDeliveryPartner method here
    // that uses a DeliveryPartnerAssignmentStrategy.
};


// --- F. CONCRETE OBSERVER IMPLEMENTATION (needs managers) ---
void UserNotifier::onStatusUpdated(Order* order) {
    User* user = userManager->findUserById(order->userId);
    if (user) {
        cout << "  -> PUSH_NOTIFICATION to User " << user->name << ": Your order "
             << order->orderId << " is now " << order->currentState->getStatusName() << "." << endl;
    }
}
void RestaurantNotifier::onStatusUpdated(Order* order) {
    Restaurant* restaurant = restaurantManager->findRestaurantById(order->restaurantId);
    if (restaurant) {
        cout << "  -> DASHBOARD_UPDATE for Restaurant " << restaurant->name << ": Order "
             << order->orderId << " is now " << order->currentState->getStatusName() << "." << endl;
    }
}


// --- G. CONCRETE MENU FILTER IMPLEMENTATIONS ---
class VegFilter : public Menu::IMenuItemFilter {
public:
    bool matches(MenuItem* item) override {
        return item->type == ItemType::VEG;
    }
};

class PriceRangeFilter : public Menu::IMenuItemFilter {
private:
    double minPrice, maxPrice;
public:
    PriceRangeFilter(double min, double max) : minPrice(min), maxPrice(max) {}
    bool matches(MenuItem* item) override {
        return item->price >= minPrice && item->price <= maxPrice;
    }
};


// --- H. SYSTEM FACADE ---
class FoodOrderingApp {
private:
    UserManager* userManager;
    RestaurantManager* restaurantManager;
    OrderManager* orderManager;
    DeliveryPartnerManager* deliveryPartnerManager;

public:
    FoodOrderingApp() {
        userManager = new UserManager();
        restaurantManager = new RestaurantManager();
        // Inject dependencies into managers that need them
        orderManager = new OrderManager(userManager, restaurantManager);
        deliveryPartnerManager = new DeliveryPartnerManager();

        // Register observers with the OrderManager
        orderManager->subscribe(new UserNotifier(userManager));
        orderManager->subscribe(new RestaurantNotifier(restaurantManager));
    }

    // Expose manager functionalities through the facade
    UserManager* getUsers() { return userManager; }
    RestaurantManager* getRestaurants() { return restaurantManager; }
    OrderManager* getOrders() { return orderManager; }
    DeliveryPartnerManager* getDeliveryPartners() { return deliveryPartnerManager; }
};


// --- Note on Memory Management ---
// As requested, this design uses raw pointers and omits destructors.
// In a modern, production C++ application, you MUST use smart pointers
// (std::unique_ptr, std::shared_ptr) to manage memory automatically and
// prevent memory leaks. The current code will leak memory.

// --- I. MAIN FUNCTION (DEMONSTRATION) ---
int main() {
    cout << "--- System Setup ---" << endl;
    FoodOrderingApp* app = new FoodOrderingApp();

    cout << "\n--- 1. Onboarding ---" << endl;
    app->getUsers()->registerUser("owner01", "Bob", "111");
    Address* r_addr = new Address{"MG Road", "Bengaluru", "560001", {12.97, 77.59}};
    Restaurant* myRestaurant = app->getRestaurants()->registerRestaurant("Bob's Burgers", r_addr, "owner01");
    
    app->getRestaurants()->addMenuItem(myRestaurant->restaurantId, "owner01", new MenuItem{"B01", "Veggie Burger", 250.0, ItemType::VEG, 4.5});
    app->getRestaurants()->addMenuItem(myRestaurant->restaurantId, "owner01", new MenuItem{"B02", "Chicken Burger", 350.0, ItemType::NON_VEG, 4.8});
    app->getRestaurants()->addMenuItem(myRestaurant->restaurantId, "owner01", new MenuItem{"B03", "Fries", 120.0, ItemType::VEG, 4.2});
    // Unauthorized attempt
    app->getRestaurants()->addMenuItem(myRestaurant->restaurantId, "other_user", new MenuItem{"B04", "Invalid", 100.0, ItemType::VEG, 1.0});


    cout << "\n--- 2. User Interaction ---" << endl;
    app->getUsers()->registerUser("cust01", "Alice", "999");
    Location userLoc = {12.98, 77.60};
    
    cout << "\n--- 3. Menu Filtering ---" << endl;
    cout << "Searching for 'Burger' restaurants near user..." << endl;
    vector<Restaurant*> found = app->getRestaurants()->searchRestaurants("Burger", userLoc);
    if (found.empty()) {
        cout << "No restaurants found." << return 1;
    }
    Restaurant* selectedRestaurant = found[0];
    cout << "User selected: " << selectedRestaurant->name << endl;
    
    cout << "\nApplying VEG filter:" << endl;
    vector<Menu::IMenuItemFilter*> filters = { new VegFilter() };
    vector<MenuItem*> vegItems = selectedRestaurant->menu->filter(filters);
    for (auto* item : vegItems) {
        cout << " - " << item->name << " (Rs. " << item->price << ")" << endl;
    }

    cout << "\n--- 4. Placing an Order ---" << endl;
    Cart* aliceCart = new Cart();
    aliceCart->userId = "cust01";
    aliceCart->restaurantId = selectedRestaurant->restaurantId;
    aliceCart->addItem("B01", 2); // 2 Veggie Burgers

    Order* alicesOrder = app->getOrders()->placeOrder(aliceCart);
    
    if (alicesOrder) {
        cout << "\n--- 5. Order State Progression ---" << endl;
        // The first notification happened when the state was set to PLACED inside placeOrder.
        
        // Simulate restaurant accepting the order
        alicesOrder->currentState->process(alicesOrder);

        // Simulate order being prepared and delivered
        alicesOrder->currentState->process(alicesOrder);

        // Try to perform an action on a final state
        cout << "\nAttempting to process a delivered order:" << endl;
        alicesOrder->currentState->process(alicesOrder);
    }
    
    // Cleanup (in a real app, this would be handled by smart pointers)
    delete app;

    return 0;
}
