#include "shell_sort.h"
#include "smooth_generator.h"

void shell_sort(int* arr, int n) {
    int* d = smooth_sequence_3(n);
    int d_size = get_smooth_sequence_size(n);
    
    for (int k = 0; k < d_size; k++) {
        int h = d[k];
        for (int i = h; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= h && arr[j - h] > temp) {
                arr[j] = arr[j - h];
                j -= h;
            }
            arr[j] = temp;
        }
    }
    
    delete[] d;
}