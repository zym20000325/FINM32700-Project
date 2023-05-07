#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>


using namespace std;


class Order {
public:
    enum class Status { Open, Closed };

    Order(std::string symbol, int id, int quantity, double price) :
            symbol_(std::move(symbol)),
            id_(id),
            quantity_(quantity),
            price_(price),
            status_(Status::Open),
            filled_quantity_(0)
    {}

    std::string symbol() const {
        return symbol_;
    }
    
    int quantity() const {
        return quantity_;
    }
    
    int id() const {
        return id_;
    }
    
    double price() const {
        return price_;
    }
    
    Status status() const {
        return status_;
    }
    
    int filled_quantity() const {
        return filled_quantity_;
    }
    
    int remaining_quantity() const {
        return (quantity_ - filled_quantity_);
    }

    void fill(int quantity) {
        if(quantity>remaining_quantity()){
            filled_quantity_ = quantity_;
            status_ = Status::Closed;
        }
        else{
            filled_quantity_ += quantity;
            if(remaining_quantity()==0){
                status_ = Status::Closed;
            }
        }
    }

    void delete_remaining() { 
        // filled_quantity_ += quantity_;
        quantity_ = quantity_ - remaining_quantity();
        status_ = Status::Closed;
    }

    friend std::ostream& operator<<(std::ostream& os, const Order& o);

private:
    std::string symbol_;
    int id_;
    int quantity_;
    double price_;
    Status status_;
    int filled_quantity_;
};

std::ostream& operator<<(std::ostream& os, const Order& o) {
    os << "Order(symbol=" << o.symbol()
       << ", quantity=" << o.quantity()
       << ", price=" << o.price()
       << ", status=";
    switch (o.status()) {
        case Order::Status::Open:
            os << "Open";
            break;
        case Order::Status::Closed:
            os << "Closed";
            break;
    }
    os << ", filled_quantity=" << o.filled_quantity()
       << ")";
    return os;
}


std::string to_string(Order::Status status);

class OrderManager {
public:
    void open_order(const std::string &symbol, const int id, const int quantity, const double price){
        Order* new_order = new Order(symbol, id, quantity, price);
        orders_[symbol].push_back(new_order);
    }

    void fill_order(const std::string &symbol, int quantity, const double price) {
        for (const auto& order_ptr : orders_[symbol]) {
            auto& order = *order_ptr;
            if(order.price() == price && order.status()==Order::Status::Open) {
                if(order.remaining_quantity()>=quantity){
                    order.fill(quantity);
                    quantity = 0;
                    break;
                }
                else{
                    int quantity_to_fill = order.remaining_quantity();
                    order.fill(quantity_to_fill);
                    quantity = quantity - quantity_to_fill;
                }
            }
        }
    }

    bool delete_order(const std::string symbol, const int id) {
        auto& orders = orders_[symbol];
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            auto& order = **it;
            if (order.id() == id && order.status() == Order::Status::Open) {
                if (order.filled_quantity() == 0) {
                    delete *it;
                    orders.erase(it);
                    return true;
                } else {
                    order.delete_remaining();
                }
            }
        }
        return false;
    }

    Order* get_order(const std::string symbol, const int id) {
        auto& orders = orders_[symbol];
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            auto& order = **it;
            if (order.id() == id) {
                return &order;
            }
        }
        return nullptr;
    }

    int get_outstanding_volume(const std::string symbol) {
        int outstanding_volume = 0;
        auto& orders = orders_[symbol];
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            auto& order = **it;
            outstanding_volume += order.remaining_quantity();
        }
        return outstanding_volume;
    }

    int get_total_volume(const std::string symbol) {
        int total_volume = 0;
        auto& orders = orders_[symbol];
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            auto& order = **it;
            total_volume += order.quantity();
        }
        return total_volume;
    }

    // Feel free to change this method if you change the storage container
    void print_orders() const {
        for (const auto& [symbol, symbol_orders] : orders_) {
            std::cout << symbol << ":\n";
            for (const auto& order_ptr : symbol_orders) {
                const auto& order = *order_ptr;
                std::cout << "    " << order.id() << " : " << order.quantity() << " shares "
                          << "(" << order.remaining_quantity() << " remaining) at $" << order.price() << " (" << to_string(order.status()) << ")\n";
            }
        }
    }

    // Feel free to change this method if you change the storage container
    void print_orders(const std::string& symbol) const {
        auto it = orders_.find(symbol);
        if (it == orders_.end()) {
            std::cout << "No orders found for symbol: " << symbol << std::endl;
            return;
        }

        std::cout << symbol << ":\n";
        for (const auto& order_ptr : it->second) {
            const auto& order = *order_ptr;
            std::cout << "    " << order.id() << " : " << order.quantity() << " shares "
                      << "(" << order.remaining_quantity() << " remaining) at $" << order.price() << " (" << to_string(order.status()) << ")\n";
        }
    }

    ~OrderManager() {}

private:
    std::unordered_map<std::string, std::vector<Order*>> orders_;
};

std::string to_string(Order::Status status) {
    switch (status) {
        case Order::Status::Open:
            return "open";
        case Order::Status::Closed:
            return "closed";
        default:
            return "unknown";
    }
}
#define TEST_FUNCTION(X,Y) { \
    if (X==Y) { \
        std::cout << "PASSED" << std::endl; \
    } else { \
        std::cout << "Line " << __LINE__ << ": FAILED - Expected '"; \
        std::cout << Y << "' Recieved '" << X << "'" << std::endl; \
    } \
}


int main() {
    OrderManager order_manager;

    int oid = 1;

    order_manager.open_order("AAPL", oid++, 100, 150.0);
    order_manager.open_order("AAPL", oid++, 200, 155.0);
    order_manager.open_order("AAPL", oid++, 300, 160.0);
    order_manager.open_order("AAPL", oid++, 120, 155.0);
    order_manager.open_order("AAPL", oid++, 1, 100.0);
    order_manager.open_order("AAPL", oid++, 65, 160.0);

    order_manager.print_orders();

    // Full and partial fill at $155.0
    order_manager.fill_order("AAPL", 150, 155.0);
    order_manager.fill_order("AAPL", 70, 155.0);
    order_manager.fill_order("AAPL", 50, 150.0);

    order_manager.print_orders();

    // Decrement remaining quantity of order 1 and close it.
    order_manager.delete_order("AAPL", 1);

    Order* order = order_manager.get_order("AAPL", 1);

    // Show AAPL order 1 closed and with less quantity.
    cout << *order << endl;

    // Try to get an order that doesn't exist.
    {
        int d_id = 100;
        order = order_manager.get_order("AAPL", d_id);

        if (order == nullptr) {
            cout << "Good. No AAPL order with id=" << d_id << endl;
        } else {
            cout << "This order shouldn't exist." << endl;
        }
    }

    order_manager.delete_order("AAPL", 5);

    {
        int d_id = 5;
        order = order_manager.get_order("AAPL", d_id);

        if (order == nullptr) {
            cout << "Good. No AAPL order with id=" << d_id << endl;
        } else {
            cout << "This order shouldn't exist." << endl;
        }
    }

    TEST_FUNCTION(order_manager.get_outstanding_volume("AAPL"), 465);
    TEST_FUNCTION(order_manager.get_total_volume("AAPL"), 735);

    std::string option_sym = "AAPL  230616C00170000";
    order_manager.open_order(option_sym, oid++, 5, 1.25);
    order_manager.open_order(option_sym, oid++, 3, 1.20);

    order_manager.print_orders(option_sym);

    TEST_FUNCTION(order_manager.get_outstanding_volume(option_sym), 8);
    TEST_FUNCTION(order_manager.get_total_volume(option_sym), 8);


}