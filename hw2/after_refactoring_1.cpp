#include <iostream>
#include <cmath>

using namespace std;
int main()
{
    const int size = 10;
    int a[size];
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < size; j++) {
            a[j] = rand() % size;
        }

        cout << "Последовательность " << i + 1 << endl;
        for (int j = 0; j < size; j++) {
            cout << a[j] << ' ';
        }

        float avg_a = 0;
        for (int j = 0; j < size; j++) {
            avg_a += a[j];
        }
        cout << "Среднее последовательности " << i + 1 << " = " << avg_a / size <<  endl;
    }


    return 0;
}
