#include <iostream>
#include <vector>
using namespace std;

vector<int> findMinRefuels(const vector<int>& distances, int S) {
    int n = distances.size() + 1;  // количество заправок (первая в Петербурге, последняя в Москве)
    vector<int> refuels;  // номера заправок, на которых нужно заправляться
    refuels.push_back(1);  // начинаем с первой заправки (Петербург)

    int current = 0;  // текущая заправка (индекс 0-based)

    while (current < n - 1) {
        int max_reachable = current;
        int total_dist = 0;

        // Находим самую дальнюю заправку, до которой можно доехать
        while (max_reachable < n - 1 &&
            total_dist + distances[max_reachable] <= S) {
            total_dist += distances[max_reachable];
            max_reachable++;
        }

        // Если не можем доехать даже до следующей заправки
        if (max_reachable == current) {
            cout << "Невозможно доехать до Москвы!" << endl;
            return {};  // возвращаем пустой вектор в случае ошибки
        }

        // Если можно доехать до Москвы
        if (max_reachable == n - 1) {
            break;  // доехали до Москвы
        }

        // Заправляемся на самой дальней достижимой заправке
        refuels.push_back(max_reachable + 1);  // +1 для перевода в 1-based нумерацию
        current = max_reachable;
    }

    return refuels;
}

int main() {
    setlocale(LC_ALL, "ru");
    // Пример входных данных
    int L;      // расстояние от Петербурга до Москвы
    int S;      // расстояние, которое машина может проехать с полным баком
    int n;      // количество заправок

    cout << "Введите расстояние от Петербурга до Москвы (L): ";
    cin >> L;

    cout << "Введите расстояние, которое может проехать машина с полным баком (S): ";
    cin >> S;

    cout << "Введите количество заправок (включая Петербург и Москву): ";
    cin >> n;

    vector<int> distances(n - 1);  // расстояния между заправками

    cout << "Введите расстояния между заправками (D1, D2, ..., D" << n - 1 << "):" << endl;
    for (int i = 0; i < n - 1; i++) {
        cin >> distances[i];
    }

    // Проверка, что сумма расстояний равна L
    int sum = 0;
    for (int d : distances) {
        sum += d;
    }

    if (sum != L) {
        cout << "Ошибка: сумма расстояний между заправками не равна L!" << endl;
        return 1;
    }

    vector<int> result = findMinRefuels(distances, S);

    if (!result.empty()) {
        cout << "\nМинимальное количество заправок: " << result.size() << endl;
        cout << "Номера заправок для посещения: ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) cout << " → ";
        }
        cout << endl;
    }

    return 0;
}