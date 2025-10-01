#include "shell_sort.h"
#include "smooth_generator.h"


void shell_sort(std::vector<int>& a) {
    int n = a.size();
    std::vector<int> d = smooth_sequence_3(n);
    
    for (int h : d) {
        for (int i = h; i < n; i++) {
            int temp = a[i];
            int j = i;
            while (j >= h && a[j - h] > temp) {
                a[j] = a[j - h];
                j -= h;
            }
            a[j] = temp;
        }
    }
}
