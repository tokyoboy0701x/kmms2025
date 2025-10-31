#include "smooth_generator.h"

int* smooth_sequence_3(int n) {
    int count = 0;
    int h = 1;
    
    while (h < n) {
        count++;
        h = 3 * h + 1;
    }
    
    h = 1;
    int* d = new int[count];
    for (int i = 0; i < count; i++) {
        d[i] = h;
        h = 3 * h + 1;
    }
    
    for (int i = 0; i < count / 2; i++) {
        int temp = d[i];
        d[i] = d[count - 1 - i];
        d[count - 1 - i] = temp;
    }
    
    return d;
}

int get_smooth_sequence_size(int n) {
    int count = 0;
    int h = 1;
    
    while (h < n) {
        count++;
        h = 3 * h + 1;
    }
    
    return count;
}