#include <iostream>
#include <bits/stdc++.h>
#include <map>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

template<typename T>
class CircularLinkedList {
private:
    
    // Finish the Node
    struct Node {
        T data;
        Node* next;
    };
    
    Node* head;
    Node* tail;
    
public:
    CircularLinkedList():head(nullptr),tail(nullptr){}

    // Insert a new node at the beginning of the list
    void insert_begin(T data) {
        
        Node *newNode = new Node{data, nullptr};
        
        if (head == nullptr){
            head = newNode;
            tail = newNode;
            head->next = tail;
        }
        else{
            newNode->next = head;
            head = newNode;
            tail->next = head;
        }
    }

    // Insert a new node at the end of the list
    void insert_end(T data) {
        
        Node *newNode = new Node{data, nullptr};
        
        if (head == nullptr){
            head = newNode;
            tail = newNode;
            head->next = tail;
        }
        else{
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
    }

    // Delete a node from the list
    void delete_node(T data) {
        
        Node* current = head;
        Node* prev = nullptr;
        
        while (current != nullptr && current->data != data) {
            prev = current;
            current = current->next;
            if (current == head) {
                break;
            }
        }
        
        if (current == nullptr) {
            return;
        }
        
        if (current == head && current == tail) {
            head = nullptr;
            tail = nullptr;
        }
        else if (current == head) {
            head = current->next;
            tail->next = head;
        }
        else if (current == tail) {
            prev->next = head;
            tail = prev;
        }
        else {
            prev->next = current->next;
        }
        
        delete current;
    }

    // Display the contents of a linked list of real number
    void display() {
        
        if(head == nullptr){
            return;
        }
                
        Node* current = head;
        
        string type_name = typeid(current->data).name();
    
        do {
            if(type_name == "i"){
                cout << current->data << endl;
            }
            else if(type_name == "f"){
                cout << fixed << setprecision(6) << current->data << endl;
            }
            else if(type_name == "d"){
                cout << fixed << setprecision(6) << current->data << endl;
            }
            
            current = current->next;
            
        } while (current != head);
    }
    
    //Display the contents of linked list of char
    void display_char() {
                
        if(head == nullptr){
            return;
        }
                
        Node* current = head;

        do {
            cout << static_cast<char>(current->data);
            current = current->next;
            
        } while (current != head);
        
        cout << endl;
    }
    
};

void test_cll_int() {
    CircularLinkedList<int> cll;

    std::string line;
    std::getline(std::cin, line);
    int in_count = stoi(ltrim(rtrim(line)));

    for (int i=1; i<=in_count; i++) {
        std::getline(std::cin, line);
        int k = stoi(ltrim(rtrim(line)));
        cll.insert_end(k);
    }

    std::getline(std::cin, line);
    int del_count = stoi(ltrim(rtrim(line)));
    for (int i=1; i<=del_count; i++) {
        std::getline(std::cin, line);
        int k = stoi(ltrim(rtrim(line)));
        cll.delete_node(k);
    }
    cll.display();
}

void test_cll_char() {
    CircularLinkedList<char> cll;

    std::string line;
    std::getline(std::cin, line);
    int in_count = stoi(ltrim(rtrim(line)));

    if (in_count > 0) {
        std::getline(std::cin, line);
        for (char c: line) {
            cll.insert_end(c);
        }
        cll.display_char();
    }

    std::getline(std::cin, line);
    int del_count = stoi(ltrim(rtrim(line)));

    if (del_count > 0) {
        std::getline(std::cin, line);
        for (char c: line) {
            cll.delete_node(c);
        }
        cll.display_char();
    }

    std::getline(std::cin, line);
    in_count = stoi(ltrim(rtrim(line)));

    if (in_count > 0) {
        std::getline(std::cin, line);
        for (char c: line) {
            cll.insert_begin(c);
        }
        cll.display_char();
    }
}

void test_cll_float() {
    CircularLinkedList<float> cll;
    cll.insert_begin(3.14f);
    cll.insert_end(2.718f);
    cll.insert_end(1.618f);
    cll.display();
    cll.delete_node(1.618f);
    cll.display();
}

void test_cll_double() {
    CircularLinkedList<double> cll;
    cll.insert_begin(3.141592);
    cll.insert_end(2.718281);
    cll.insert_end(1.414213);
    cll.display();
}


typedef void (*Fptr)(void);
Fptr test_functions[] = {
        &test_cll_int,
        &test_cll_float,
        &test_cll_double,
        &test_cll_char,

};



int main() {
    string arg;
    getline(cin, arg);
    int i = stoi(ltrim(rtrim(arg)));
        
    test_functions[i]();
    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
            s.begin(),
            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
            find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
            s.end()
    );

    return s;
}