#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "shell_sort.h"

using namespace std;

int main() {

    vector<int> s = {1000, 10000, 100000, 1000000};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);
    
    for (int n : s) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = dist(gen);
        }
        
        vector<int> a1 = a;
        vector<int> a2 = a;
        
        auto start_shell_sort = chrono::high_resolution_clock::now();
        shell_sort(a1);
        auto end_shell_sort = chrono::high_resolution_clock::now();
        chrono::duration<double> time_shell_sort = end_shell_sort - start_shell_sort;
        
        auto start_quick_sort = chrono::high_resolution_clock::now();
        sort(a2.begin(), a2.end());
        auto end_quick_sort = chrono::high_resolution_clock::now();
        chrono::duration<double> time_quick_sort = end_quick_sort - start_quick_sort;
        
        bool sorted_correctly = is_sorted(a1.begin(), a1.end());
        
        cout << time_shell_sort.count() << endl;
        cout << time_quick_sort.count() << endl;
        cout << " " << endl;
    }
    
    return 0;
}
