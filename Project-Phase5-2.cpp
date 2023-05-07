#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iomanip>
#include <ctime>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

// std::time_t parseDate(std::string osidate) {
// }

enum OptionType {CALL, PUT};
const std::string OptionTypeNames[] = { "CALL", "PUT"};

struct Option {
    // std::string root_sym;
    // std::time_t exp_date;
    // OptionType opType;
    // signed int strike;
    // Option(std::string root_sym_, std::time_t exp_date_, OptionType opType_, signed int strike_)
    //         : root_sym{root_sym_}, exp_date{exp_date_}, opType{opType_}, strike{strike_} {}
    
    std::string root_sym;
    std::string exp_date;
    OptionType opType;
    double strike;

    Option(std::string root_sym_, std::string exp_date_, OptionType opType_, double strike_)
            : root_sym{root_sym_}, exp_date{exp_date_}, opType{opType_}, strike{strike_} {}
            
    friend std::ostream& operator<<(std::ostream& os, const Option& o) {
        // Your code here.
        os << "Option(root_sym=\"" << o.root_sym << "\", exp_date=" << o.exp_date;
        os << ", opType=" << OptionTypeNames[o.opType] << ", strike=" << o.strike << ")" << endl;
        return os;
    }
};

std::string format_date(const std::string& date_str) {
    std::string day_str = date_str.substr(4, 2);
    std::string month_str = date_str.substr(2, 2);
    std::string year_str = "20" + date_str.substr(0, 2);
    return year_str + "-" + month_str + "-" + day_str;
}

Option makeOption(std::string osiSym) {
    
    std::string sPattern = "^(([A-Z]{6}|[A-Z]{5}\\s{1}|[A-Z]{4}\\s{2}|[A-Z]{3}\\s{3}|[A-Z]{2}\\s{4}|[A-Z]{1}\\s{5})([0-9]{2})(0[1-9]|1[0-2])([0-9]{2})([CP])([0-9]{8}))$";
    std::regex re(sPattern);
    if (!std::regex_match(osiSym, re)) {
        throw std::invalid_argument("Invalid OSI symbol");
    }
    
    std::string root_sym = osiSym.substr(0, 6);
    root_sym.erase(root_sym.find_last_not_of(" \n\r\t")+1);

    std::string exp_date_ = osiSym.substr(6, 6);
    std::string exp_date = format_date(exp_date_);

    std::string opType_ = osiSym.substr(12, 1);
    OptionType opType;
    if(opType_ == "C"){
        opType = CALL;
    }
    else if(opType_ == "P"){
        opType = PUT;
    }

    std::string strike_str = osiSym.substr(13, 8);
    signed int strike_int = std::stoi(strike_str);
    double strike = static_cast<double>(strike_int);
    strike = strike/1000;

    Option new_option(root_sym, exp_date, opType, strike);
    return new_option;
}

int main() {
    std::string line;
    getline(cin, line);
    
    int n = stoi(ltrim(rtrim(line)));
    
    for (int i=0; i<n; i++) {
        getline(cin, line);
        try {
            Option o1 = makeOption(line);
            std::cout << o1;
        } catch (std::invalid_argument& e) {
            std::cout << "Invalid argument: " << e.what() << " - " << line << " - " << line.length() << std::endl;
        };
        
    }
    
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