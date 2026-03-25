#include <iostream>
#include <vector>

using namespace std;



// Проверка, упорядочен ли массив по убыванию
bool isDescendingSorted(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        if (arr[i] < arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Сортировка по убыванию
void bubbleSortDescending(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    setlocale(LC_ALL "ru");
    vector<int> arr = { 4, 9, 7, 6, 2, 3 };

    cout << "Исходный массив: ";
    for (int val : arr) cout << val << " ";
    cout << endl;

    if (isDescendingSorted(arr)) {
        cout << "Массив уже упорядочен по убыванию." << endl;
    }
    else {
        cout << "Массив не упорядочен по убыванию. Выполняем сортировку..." << endl;
        bubbleSortDescending(arr);
        cout << "Результат: ";
        for (int val : arr) cout << val << " ";
        cout << endl;
    }

    return 0;
}




