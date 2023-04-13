#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

#include <bits/stdc++.h>
#include <map>


class Order {
private:
    string symbol;
    int quantity;
    double price;
    int id;

public:
    Order(std::string symbol, int quantity, double price, int id):symbol(symbol), quantity(quantity),price(price), id(id) {}

    std::string getSymbol() const {
        return symbol;
    }

    int getQuantity() const {
        return quantity;
    }

    double getPrice() const {
        return price;
    }

    int getId() const {
        return id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Order& order) {
        os << "Order(id: " << order.id << ", Symbol: " << order.symbol << ", Quantity: " << order.quantity << ", Price: " << order.price << " )";
        return os;
    }
};

class BufferFull: public exception{
public:
    const char* what() const noexcept override {
        return "The buffer has reached capacity and is set to not overwrite";
    }
};

class BufferEmpty: public exception{
public:
    const char* what() const noexcept override {
        return "The buffer is empty";
    }
};


template<typename T>
class CircularBuffer{
    
private:
    int capacity;
    bool overwrite;
    int size;
    
    struct Node {
        T data;
        Node* next;
    };
    
    Node* head;
    Node* tail;
    
public:
    CircularBuffer(int capacity, bool overwrite = false): capacity(capacity), overwrite(overwrite), size(0), head(nullptr),tail(nullptr) {}

    ~CircularBuffer() {
        Node* p = head;
        while (p!=tail) {
            Node* temp = p;
            p = p->next;
            delete temp;
        }
        delete tail;
    }

    void push(T data) {
        
        if (size == capacity && !overwrite) {
            throw BufferFull();
        }

        if (size == capacity) {
            T overwritten_data = pop();
        }

        Node* newNode = new Node{data, nullptr};
        
        if (tail!= nullptr) {
            tail->next = newNode;
        }
        tail = newNode;
        tail->next = head;

        if (head == nullptr) {
            head = newNode;
        }

        ++size;
    }

    T pop() {
                
        if (head == nullptr) {
            throw BufferEmpty();
        }

        T pop_data = head->data;

        Node* node = head;
        head = head->next;
        tail->next = head;
        
        if (head == nullptr) {
            tail = nullptr;
        }
        
        delete node;
        --size;

        return pop_data;
    }

    int get_size() const {
        return size;
    }

    int get_capacity() const {
        return capacity;
    }

    bool set_capacity(const int capacity) {
        if (capacity < size) {
            return false;
        }
        else{
            this->capacity = capacity;
            return true;
        }
    }

    void set_overwrite(const bool ow) {
        overwrite = ow;
    }

    bool is_empty() const {
        if (size == 0){
            return true;
        }
        else{
            return false;
        }
    }

    bool is_full() const {
        if (size == capacity){
            return true;
        }
        else {
            return false;
        }
    }

    void display() {
        
        if (head == nullptr){
            return;
        }
        else if (head == tail){
            cout << head->data << endl;
        }
        else{
            Node* current = head;
            do{
                cout << current->data << endl;
                current = current->next;
            } while (current!=head);
        }
    }
};

std::string ltrim(const std::string &str) {
    std::string s(str);

    s.erase(
            s.begin(),
            find_if(s.begin(), s.end(), not1(std::ptr_fun<int, int>(isspace)))
    );

    return s;
}

std::string rtrim(const std::string &str) {
    std::string s(str);

    s.erase(
            find_if(s.rbegin(), s.rend(), not1(std::ptr_fun<int, int>(isspace))).base(),
            s.end()
    );

    return s;
}



int main() {
    CircularBuffer<Order> buffer(3);

    Order order1("AAPL", 100, 150.00, 1);
    Order order2("GOOG", 50, 1200.00, 2);
    Order order3("MSFT", 200, 80.00, 3);

    buffer.push(order1);
    buffer.push(order2);
    buffer.push(order3);

    std::cout << "Current buffer size: " << buffer.get_size() << std::endl;

    Order oldestOrder = buffer.pop();
    std::cout << "Oldest order: " << oldestOrder.getId() << " " << oldestOrder.getSymbol() << " " << oldestOrder.getQuantity() << " " << oldestOrder.getPrice() << std::endl;
    std::cout << "Current buffer size: " << buffer.get_size() << std::endl;
    Order order4("TSLA", 150, 600.00, 4);
    buffer.push(order4);

    buffer.display();

    try {
        Order order5("TSLA", 100, 605.00, 5);
        buffer.push(order5);
    } catch (const BufferFull &e) {
        std::cout << "Good. You threw a BufferFull exception: " << e.what() << std::endl;
    }

    if (!buffer.set_capacity(1)) {
        std::cout << "Capacity can't be set lower than current buffer size" << std::endl;
    }

    std::cout << "Current buffer capacity: " << buffer.get_capacity() << std::endl;

    buffer.set_overwrite(true);
    Order order6("NFLX", 100, 75.00, 6);
    buffer.push(order6);

    buffer.display();

    if (!buffer.set_capacity(50)) {
        std::cout << "You should be able to increase the buffer capacity larger than the current buffer size" << std::endl;
    }

    std::string line;
    std::getline(std::cin, line);
    int in_count = stoi(ltrim(rtrim(line)));

    for (int i = 1; i<=in_count; i++) {
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string symbol, quantity_str, price_str, id_str;

        if (std::getline(ss, symbol, ',') && std::getline(ss, quantity_str, ',') && std::getline(ss, price_str, ',') && std::getline(ss, id_str)) {
            try {
                int quantity = std::stoi(quantity_str);
                double price = std::stod(price_str);
                int id = std::stoi(id_str);

                buffer.push(Order(symbol, quantity, price, id));
            }
            catch (std::exception& e) {
                std::cerr << "Error parsing line: " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "Invalid line format: " << line << std::endl;
        }
    }

    buffer.display();



    return 0;
}