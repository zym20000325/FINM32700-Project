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

using namespace std;

double my_factorial(double number){
    
    // Calculate factorial
    
    double result = 1;
    for (double i = 1; i<=number; ++i){
        result = result * i;
    }
    
    return result;
}

double my_addition(double number1, double number2){
    
    // Addition
    
    double result = number1 + number2;
    return result;
}

double my_power(double number1, double number2){
    
    // Power
    
    double result = 1;
    for (double i = 1; i<= number2; ++i){
        result = result * number1;
    }
    return result;
}

double my_average(double *array_numbers, int array_size){
    
    // average of an array of numbers
    
    double result = 0;
    
    for (int i = 0; i< array_size; ++i){
        result += array_numbers[i];
    }
    
    result = result / array_size;
    return result;
}

double my_max(double *array_numbers, int array_size){
    
    // max of an array of numbers
    
    double result = array_numbers[0];
    
    for (int i = 1; i< array_size; ++i){
        if(array_numbers[i]>result){
            result = array_numbers[i];
        }
    }
    
    return result;
}

double* my_sort(double *array_numbers, int array_size) {
    
    // sort an array
    
    double temp;
    for (int i = 0; i < array_size; ++i) {
        for (int j = i + 1; j < array_size; ++j) {
            
            if (array_numbers[i] > array_numbers[j]) {
                temp = array_numbers[i];
                array_numbers[i] = array_numbers[j];
                array_numbers[j] = temp;
            }
        }
    }
    
    return array_numbers;
}

void slice(double *arr, int start, int end, double *result) {
    for (int i = start; i < end; i++) {
        result[i - start] = arr[i];
    }
}

int main() {
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
        
    double* arr = nullptr; 
    double n; 
    int size = 0; 
    
    while (cin >> n) { 
        
        size++; 
        double* new_arr = new double[size]; 
        
        if (arr != nullptr) { 
            
            for (int i = 0; i < size-1; i++) {
                new_arr[i] = arr[i];
            }
            delete[] arr; 
        }
        new_arr[size-1] = n; 
        arr = new_arr; 
    }
    
    double index = arr[0];
    double number, number1, number2;
    int array_size;    
    bool correct = false;
    
    if (index == 0){
        
        number = arr[1];
        double expected_output0 = arr[2];
        if (my_factorial(number)==expected_output0){
            correct = true;
        }
    }
    else if (index == 1){
        
        number1 = arr[1];
        number2 = arr[2];
        double expected_output1 = arr[3];
        
        if (my_addition(number1, number2)==expected_output1){
            correct = true;
        }
    }
    else if (index == 2){
        
        number1 = arr[1];
        number2 = arr[2];
        double expected_output2 = arr[3];
                
        if (my_power(number1, number2) == expected_output2){
            correct = true;
        }
    }
    else if (index == 3){
        
        array_size = arr[1];
        double array_numbers3[array_size];
        slice(arr, 2, 2+array_size, array_numbers3);
        double expected_output3 = arr[2+array_size]; 
             
        if (my_average(array_numbers3, array_size) == expected_output3){
            correct = true;
        } 
    }
    else if (index == 4){
        
        array_size = arr[1];
        double array_numbers4[array_size];
        
        slice(arr, 2, 2+array_size, array_numbers4);
        double expected_output4 = arr[2+array_size]; 
         
        if (my_max(array_numbers4, array_size) == expected_output4){
            correct = true;
        } 
    }
    else if (index == 5){
        
        array_size = arr[1];
        double array_numbers5[array_size];
        slice(arr, 2, 2+array_size, array_numbers5);
        my_sort(array_numbers5, array_size);

        double expected_output5[array_size];
        slice(arr, 2+array_size, 2+2*array_size, expected_output5);
        
        correct = true;
        
        for(int i = 0; i<array_size; ++i){
            if(array_numbers5[i]!=expected_output5[i]){
                correct = false;
            }
        }
    }
    
    if (correct == true){
        cout << "PASS";
    }
    else{
        cout << "FAIL";
    }

    delete[] arr;     

    return 0;
}