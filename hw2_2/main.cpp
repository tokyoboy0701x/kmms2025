#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "shell_sort.h"

using namespace std;

int main() {
    const int s[] = {1000, 10000, 100000, 1000000};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);
    
    for (int n : s) {
        int* arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = dist(gen);
        }
        
        int* shell_sort_arr = new int[n];
        int* quick_sort_arr = new int[n];
        
        copy(arr, arr + n, shell_sort_arr);
        copy(arr, arr + n, quick_sort_arr);
        
        auto start_shell_sort = chrono::high_resolution_clock::now();
        shell_sort(shell_sort_arr, n);
        auto end_shell_sort = chrono::high_resolution_clock::now();
        chrono::duration<double> time_shell_sort = end_shell_sort - start_shell_sort;
        
        auto start_quick_sort = chrono::high_resolution_clock::now();
        sort(quick_sort_arr, quick_sort_arr + n);
        auto end_quick_sort = chrono::high_resolution_clock::now();
        chrono::duration<double> time_quick_sort = end_quick_sort - start_quick_sort;
        
        bool shell_sorted_correctly = is_sorted(shell_sort_arr, shell_sort_arr + n);
        bool quick_sorted_correctly = is_sorted(quick_sort_arr, quick_sort_arr + n);
        
        cout << "n = " << n << ":" << endl;
        cout << "Shell sort: " << time_shell_sort.count() << "s, sorted: " << shell_sorted_correctly << endl;
        cout << "Quick sort: " << time_quick_sort.count() << "s, sorted: " << quick_sorted_correctly << endl;
        cout << endl;

        delete[] arr;
        delete[] shell_sort_arr;
        delete[] quick_sort_arr;
    }
    
    return 0;
}