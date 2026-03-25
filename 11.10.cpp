#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace chrono;

// Функция для генерации случайного массива
vector<int> generateArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);

    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Функция для копирования массива
vector<int> copyArray(const vector<int>& original) {
    return vector<int>(original.begin(), original.end());
}

// 1. Пузырьковая сортировка (Bubble sort)
void bubbleSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 2. Шейкерная сортировка (Shaker sort)
void shakerSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;

        // Проход слева направо
        for (int i = start; i < end; i++) {
            comparisons++;
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        end--;

        // Проход справа налево
        for (int i = end - 1; i >= start; i--) {
            comparisons++;
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        start++;
    }
}

// 3. Сортировка выбором (Selection sort)
void selectionSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
        }
    }
}

// 4. Сортировка вставками (Insertion sort)
void insertionSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

// 5. Быстрая сортировка (Quick sort)
int partition(vector<int>& arr, int low, int high, long long& comparisons) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortRecursive(vector<int>& arr, int low, int high, long long& comparisons) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons);
        quickSortRecursive(arr, low, pi - 1, comparisons);
        quickSortRecursive(arr, pi + 1, high, comparisons);
    }
}

void quickSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    quickSortRecursive(arr, 0, arr.size() - 1, comparisons);
}

// 6. Сортировка слиянием (Merge sort)
void merge(vector<int>& arr, int left, int mid, int right, long long& comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortRecursive(vector<int>& arr, int left, int right, long long& comparisons) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRecursive(arr, left, mid, comparisons);
        mergeSortRecursive(arr, mid + 1, right, comparisons);
        merge(arr, left, mid, right, comparisons);
    }
}

void mergeSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    mergeSortRecursive(arr, 0, arr.size() - 1, comparisons);
}

// Структура для хранения результатов
struct SortResult {
    string name;
    long long comparisons;
    double timeMs;
};

// Функция для тестирования одного алгоритма
SortResult testSort(void (*sortFunc)(vector<int>&, long long&),
    const vector<int>& original,
    const string& name) {
    vector<int> arr = copyArray(original);
    long long comparisons = 0;

    auto start = high_resolution_clock::now();
    sortFunc(arr, comparisons);
    auto end = high_resolution_clock::now();

    double timeMs = duration<double, milli>(end - start).count();

    return { name, comparisons, timeMs };
}

// Функция для вывода таблицы результатов
void printResults(const vector<SortResult>& results, int arraySize) {
    cout << "\n" << string(80, '=') << endl;
    cout << "Результаты для массива размером " << arraySize << " элементов:" << endl;
    cout << string(80, '=') << endl;

    cout << left << setw(25) << "Алгоритм сортировки"
        << right << setw(15) << "Время (мс)"
        << right << setw(20) << "Сравнений" << endl;
    cout << string(80, '-') << endl;

    for (const auto& res : results) {
        cout << left << setw(25) << res.name
            << right << setw(15) << fixed << setprecision(3) << res.timeMs
            << right << setw(20) << res.comparisons << endl;
    }
    cout << string(80, '=') << endl;
}

// Функция для проверки, отсортирован ли массив
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "ru");
    // Размеры массивов для тестирования
    vector<int> sizes = { 1000, 10000, 100000 };

    // Количество запусков для каждого размера
    const int RUNS = 5;

    cout << "Программа для сравнения алгоритмов сортировки" << endl;
    cout << "Количество запусков для каждого размера: " << RUNS << endl;

    for (int size : sizes) {
        cout << "\nГенерация массива размером " << size << "..." << endl;
        vector<int> original = generateArray(size);

        // Массив для хранения лучших результатов для каждого алгоритма
        vector<SortResult> bestResults;

        // Список алгоритмов для тестирования
        vector<pair<void(*)(vector<int>&, long long&), string>> algorithms = {
            {bubbleSort, "Пузырьковая"},
            {shakerSort, "Шейкерная"},
            {selectionSort, "Выбором"},
            {insertionSort, "Вставками"},
            {quickSort, "Быстрая"},
            {mergeSort, "Слиянием"}
        };

        // Тестируем каждый алгоритм
        for (const auto& algo : algorithms) {
            cout << "Тестирование: " << algo.second << "... ";

            SortResult bestResult = { "", 0, 999999999.0 };

            // Выполняем несколько запусков и выбираем лучшее время
            for (int run = 0; run < RUNS; run++) {
                SortResult result = testSort(algo.first, original, algo.second);

                if (result.timeMs < bestResult.timeMs) {
                    bestResult = result;
                }
            }

            bestResults.push_back(bestResult);
            cout << "лучшее время: " << fixed << setprecision(3)
                << bestResult.timeMs << " мс" << endl;
        }

        // Выводим таблицу результатов
        printResults(bestResults, size);

        // Вывод рекомендаций
        cout << "\nРекомендации для размера " << size << ":" << endl;

        // Находим самый быстрый алгоритм
        auto fastest = min_element(bestResults.begin(), bestResults.end(),
            [](const SortResult& a, const SortResult& b) {
                return a.timeMs < b.timeMs;
            });

        cout << "✓ Самый быстрый: " << fastest->name
            << " (" << fastest->timeMs << " мс)" << endl;

        // Находим алгоритм с наименьшим количеством сравнений
        auto leastComparisons = min_element(bestResults.begin(), bestResults.end(),
            [](const SortResult& a, const SortResult& b) {
                return a.comparisons < b.comparisons;
            });

        cout << "✓ Наименьшее количество сравнений: " << leastComparisons->name
            << " (" << leastComparisons->comparisons << ")" << endl;

        // Анализ сложности
        if (size <= 10000) {
            cout << "ℹ Для малых массивов квадратичные алгоритмы (пузырьковая, "
                << "вставками, выбором) могут показывать приемлемые результаты." << endl;
        }
        else {
            cout << "ℹ Для больших массивов (≥100000) рекомендуется использовать "
                << "быструю сортировку или сортировку слиянием." << endl;
        }
    }

    // Дополнительный тест: проверка корректности сортировки
    cout << "\n\n" << string(80, '=') << endl;
    cout << "Проверка корректности работы алгоритмов:" << endl;
    cout << string(80, '=') << endl;

    vector<int> testArray = generateArray(100);

    vector<pair<void(*)(vector<int>&, long long&), string>> algorithms = {
        {bubbleSort, "Пузырьковая"},
        {shakerSort, "Шейкерная"},
        {selectionSort, "Выбором"},
        {insertionSort, "Вставками"},
        {quickSort, "Быстрая"},
        {mergeSort, "Слиянием"}
    };

    for (const auto& algo : algorithms) {
        vector<int> arr = copyArray(testArray);
        long long comparisons = 0;
        algo.first(arr, comparisons);

        if (isSorted(arr)) {
            cout << "✓ " << algo.second << ": массив отсортирован корректно" << endl;
        }
        else {
            cout << "✗ " << algo.second << ": ОШИБКА! Массив не отсортирован!" << endl;
        }
    }

    cout << "\nПрограмма завершена." << endl;

    return 0;
}