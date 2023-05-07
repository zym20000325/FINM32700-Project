#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <regex>
#include <bits/stdc++.h>


using namespace std;

string ltrim(const string &);
string rtrim(const string &);

std::string sPattern = "^(([A-Z]{6}|[A-Z]{5}\\s{1}|[A-Z]{4}\\s{2}|[A-Z]{3}\\s{3}|[A-Z]{2}\\s{4}|[A-Z]{1}\\s{5})([0-9]{2})(0[1-9]|1[0-2])([0-9]{2})([CP])([0-9]{8}))$";  

int main() {
    string count;
    getline(cin, count);
    int n = stoi(ltrim(rtrim(count)));
    
    string osiSym;
    std::regex pattern(sPattern); 
    
    std::smatch matches;
    for (int i=0; i<n; i++) {
        
        getline(cin, osiSym);
        
        std::smatch matches;
        if (std::regex_search(osiSym, matches, pattern)) {
            std::cout << "MATCH: " << osiSym << std::endl;
        } else {
            std::cout << "NO MATCH: " << osiSym << std::endl;
        }    
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