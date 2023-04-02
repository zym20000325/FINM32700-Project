#include <iostream>
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

void allocate_matrix(double **a, int rows, int columns)
{
    // You need to do the dynamic allocation on the heap
        
    *a = new double[rows*columns];    
}

void initialize_a(double *a, int rows, int columns)
{
    //You need to initialize a
    /* We want a to look like the following
    *      1  2  3
    * a =  1  1  1
    *      1  1  1
    */

    double (*twod_array)[3] = (double (*)[3]) a;
    
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < columns; ++j){
            
            if (i==0){
                twod_array[i][j] = j+1;
            }
            else{
                twod_array[i][j] = 1;
            }
        }
    } 
}

void initialize_b(double *a, int rows, int columns)
{
    //You need to initialize b
    /* We want b to look like the following
    * b =  1  1  1
    */
        
    for (int i = 0; i < columns; ++i){
        a[i] = 1;
    }
}

void initialize_c(double *a, int rows, int columns)
{
    //You need to initialize c
    /* We want c to look like the following
    * c =  0 0 0
    */
    
    for (int i = 0; i < columns; ++i){
        a[i] = 0;
    }
}


void product_sum(double (*a)[3], double *b,  double *c)
{
    /* We want a vector s.t.
    * c = b * a + b
    */
    
    for (int i = 0; i < 3; i++) {
        c[i] = b[i];
        
        for (int j = 0; j < 3; j++) {
            c[i] += b[j] * a[j][i];
        }
    }
}

#define TEST_IS_EQUAL(X,Y) {if (X==Y) {cout << "PASS" << endl;} else {cout << "FAIL" << endl;}}
#define TEST_IS_NOT_EQUAL(X,Y) {if (X!=Y) {cout << "PASS" << endl;} else { cout << "FAIL" << endl;}}

void display_matrix_3(double (*c)[3])
{
    for (int i=0; i<3;i++) {
        for (int k = 0; k < 3; k++)
            cout << c[i][k] << " ";
        cout << endl;
    }

}

void display_vector(double *c, int size)
{
    for (int i=0; i<size;i++) {
        cout << c[i] << " ";
    }
}

void test_allocate_matrix() {
    string arg;
    getline(cin, arg);
    int rowSize = stoi(ltrim(rtrim(arg)));
    
    getline(cin, arg);
    int colSize = stoi(ltrim(rtrim(arg)));
    
    double * mat = NULL;
    allocate_matrix(&mat,rowSize,colSize);
    TEST_IS_NOT_EQUAL(mat, (double *)NULL);
}

void test_initialize_a() {
    double * mat;
    allocate_matrix(&mat,3,3);
    initialize_a(mat,3,3);
    display_matrix_3((double (*)[3])mat);  
}

void test_initialize_b() {
    double * vec;
    allocate_matrix(&vec,3,3);
    initialize_b(vec,1,3);
    display_vector(vec, 3);   
}

void test_initialize_c() {
    double * vec;
    allocate_matrix(&vec,3,3);
    initialize_c(vec,1,3);
    display_vector(vec, 3);    
}

void test_product_sum() {
    double * matA = NULL;
    allocate_matrix(&matA,3,3);
    initialize_a(matA, 3, 3);
    double * vecB = NULL;
    allocate_matrix(&vecB,3,3);
    initialize_b(vecB, 1, 3);
    double * vecC = NULL;
    allocate_matrix(&vecC,3,3);
    initialize_b(vecC, 1, 3);
    product_sum((double(*)[3])matA, vecB, vecC);
    display_vector(vecC, 3);
}



typedef void (*Fptr)(void);
Fptr test_functions[] = {
        &test_allocate_matrix,
        &test_initialize_a,
        &test_initialize_b,
        &test_initialize_c,
        &test_product_sum,
    };

int main() 
{  
    string test_idx;
    getline(cin, test_idx);
    
    int i = stoi(ltrim(rtrim(test_idx)));
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