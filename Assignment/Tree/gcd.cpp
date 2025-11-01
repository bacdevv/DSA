#include <iostream>
using namespace std;

// int gcd(int a, int b) {
//     if (b > a) {
//         int temp = a;
//         a = b;
//         b = temp;
//     }

//     int count = 0;
//     while (b != 0) {
//         ++count;
//         cout << count << endl;
//         int temp = b;
//         b = a % b;
//         a = temp;
//     }
//     return a;
// }

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main () {
    int result = gcd(48, 60);
    cout << result;
} 