#include <iostream>
#include <cstdlib>  // для abs()

using namespace std;


int gcd(int a, int b) {

    if (b == 0) {
        return abs(a);  
    }

    return gcd(b, a % b);
}


int gcd_short(int a, int b) {
    return b == 0 ? abs(a) : gcd_short(b, a % b);
}

int main() {
    setlocale(LC_ALL, "ru");
    int a, b;

    cout << "=== Вычисление НОД двух чисел (рекурсивно) ===" << endl;
    cout << "Введите первое число: ";
    cin >> a;
    cout << "Введите второе число: ";
    cin >> b;

    int result = gcd(a, b);

    cout << "НОД(" << a << ", " << b << ") = " << result << endl;


    return 0;
}