#include "smooth_generator.h"

#include <set>
#include <algorithm>



std::vector<int> smooth_sequence_3(int n) {
    std::set<int> d_set;

    for (int i = 1; i <= n; i *= 2) {
        for (int j = i; j <= n; j *= 3) {
            if (j <= n) {
                d_set.insert(j);
            }
        }
    }

    std::vector<int> d(d_set.begin(), d_set.end());
    std::sort(d.rbegin(), d.rend());
    
    return d;
}