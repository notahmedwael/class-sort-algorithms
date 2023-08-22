#include <iostream>
#include <chrono> // for time measurement
#include <utility> // for pair
#include <limits> // for dealing with files
#include <fstream> // for dealing with files
#include <vector> // container to store data
#include "Student.h"
using namespace std;
// Quick sort
template<typename T, typename Compare>
int partition(vector<T>& arr, int low, int high, Compare compare, int& comparisons) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (!compare(arr[j], pivot)) { // Negate the comparison here
            i++;
            swap(arr[i], arr[j]);
        }
        comparisons++;
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template<typename T, typename Compare>
void quickSortHelper(vector<T>& arr, int low, int high, Compare compare, int& comparisons) {
    if (low < high) {
        int pi = partition(arr, low, high, compare, comparisons);
        quickSortHelper(arr, low, pi - 1, compare, comparisons);
        quickSortHelper(arr, pi + 1, high, compare, comparisons);
    }
}

template<typename T, typename Compare>
pair<int, double> quickSort(vector<T>& arr, Compare compare) {
    int n = arr.size();
    int comparisons = 0;
    auto start = std::chrono::high_resolution_clock::now();
    quickSortHelper(arr, 0, n - 1, compare, comparisons);
    auto end = std::chrono::high_resolution_clock::now();
    double runningTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count();

    return make_pair(comparisons, runningTime);
}

// Shell sort
template<typename T, typename Compare>
pair<int, double> shellSort(vector<T> &arr, Compare compare) {
    int n = arr.size();
    int comparisons = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && compare(arr[j - gap], temp); j -= gap) {
                arr[j] = arr[j - gap];
                comparisons++;
            }
            arr[j] = temp;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    double runningTime = std::chrono::duration_cast<std::chrono::duration<double, milli>>(end - start).count();
    return make_pair(comparisons, runningTime);
}

// Merge sort
template<typename T, typename Compare>
pair<int, double> mergeSortHelper(vector<T>& arr, int left, int right, Compare compare) {
    int comparisons = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        pair<int, double> leftResult = mergeSortHelper(arr, left, mid, compare);
        pair<int, double> rightResult = mergeSortHelper(arr, mid + 1, right, compare);
        comparisons = leftResult.first + rightResult.first;
        merge(arr, left, mid, right, compare, comparisons);
    }
    return make_pair(comparisons, 0.0); // The running time is not used here
}

template<typename T, typename Compare>
pair<int, double> mergeSort(vector<T>& arr, Compare compare) {
    int n = arr.size();
    auto start = std::chrono::high_resolution_clock::now();
    pair<int, double> result = mergeSortHelper(arr, 0, n - 1, compare);
    auto end = std::chrono::high_resolution_clock::now();
    double runningTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count();
    return make_pair(result.first, runningTime);
}

template<typename T, typename Compare>
void merge(vector<T>& arr, int left, int mid, int right, Compare compare, int& comparisons) {
    vector<T> merged;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (compare(arr[i], arr[j])) {
            merged.push_back(arr[i]);
            i++;
        } else {
            merged.push_back(arr[j]);
            j++;
        }
        comparisons++;
    }

    while (i <= mid) {
        merged.push_back(arr[i]);
        i++;
        comparisons++;
    }

    while (j <= right) {
        merged.push_back(arr[j]);
        j++;
        comparisons++;
    }

    for (int k = 0; k < merged.size(); k++) {
        arr[left + k] = merged[k];
    }
}

// Bubble sort
template<typename T, typename Compare>
pair<int, double> bubbleSort(vector<T> &arr, Compare compare) {
    int n = arr.size();
    int comparisons = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (compare(arr[j + 1], arr[j])) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
            comparisons++;
        }
        if (!swapped) {
            break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    double runningTime = std::chrono::duration_cast<std::chrono::duration<double, milli>>(end - start).count();
    return make_pair(comparisons, runningTime);
}

// Selection sort
template<typename T, typename Compare>
pair<int, double> selectionSort(vector<T> &arr, Compare compare) {
    int n = arr.size();
    int comparisons = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (compare(arr[j], arr[minIndex])) {
                minIndex = j;
            }
            comparisons++;
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    double runningTime = std::chrono::duration_cast<std::chrono::duration<double, milli>>(end - start).count();
    return make_pair(comparisons, runningTime);
}

// Insertion sort
template<typename T, typename Compare>
pair<int, double> insertionSort(vector<T> &arr, Compare compare){
    int n = arr.size();
    int comparisons = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && compare(arr[j], key)) {
            arr[j + 1] = arr[j];
            --j;
            comparisons++;
        }
        arr[j + 1] = key;
    }
    auto end = std::chrono::high_resolution_clock::now();
    double runningTime = std::chrono::duration_cast<std::chrono::duration<double, milli>>(end-start).count();
    return make_pair(comparisons, runningTime);
 }

int main() {
    // Defining a vector to hold the students objects from implemented Student class.
    vector<Student> studentsList;
    // Opening a file and reading the objects and appending them to the vector.
    try{
    ifstream inFile;
    inFile.open(R"(D:\Studying\2nd Year\Second Semester\Data Structures\Assignments\Assignment #1\Solution\students.txt)");
    if (!inFile.is_open()){
        throw runtime_error("File could not be opened");
    }
    int studentsNum;
    inFile >> studentsNum;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');
        string name, id;
        double gpa;
        while (getline(inFile, name) && inFile >> id >> gpa) {
            inFile.ignore(numeric_limits<streamsize>::max(), '\n');
            studentsList.emplace_back(name, id, gpa);
        }
    inFile.close();
    }
    catch (const runtime_error &e){
        cout << "Exception : " << e.what() << endl;
    }
    catch(...){
        cout << "Unknown exception occurred." << endl;
    }
    // Defining copies of the studentList to pass them as parameters to be sorted using different sorting algorithms.
    vector<Student> insertionByGpa = studentsList;
    vector<Student> insertionByName = studentsList;
    vector<Student> selectionByGpa = studentsList;
    vector<Student> selectionByName = studentsList;
    vector<Student> bubbleByGpa = studentsList;
    vector<Student> bubbleByName = studentsList;
    vector<Student> shellByGpa = studentsList;
    vector<Student> shellByName = studentsList;
    vector<Student> mergeByGpa = studentsList;
    vector<Student> mergeByName = studentsList;
    vector<Student> quickByGpa = studentsList;
    vector<Student> quickByName = studentsList;

    // Sorting using different algorithms, methods return a pair that has the number of comparisons and running time of each method.
    pair<int, double> insertionGpa = insertionSort(insertionByGpa, [](const Student &s1, const Student &s2){return s1.getGpa() < s2.getGpa();});
    pair<int, double> insertionName = insertionSort(insertionByName, [](const Student &s1, const Student &s2){return s1.getName() > s2.getName();});
    pair<int, double> selectionGpa = selectionSort(selectionByGpa, [](const Student &s1, const Student &s2){return s1.getGpa() > s2.getGpa();});
    pair<int, double> selectionName = selectionSort(selectionByName, [](const Student &s1, const Student &s2){return s1.getName() < s2.getName();});
    pair<int, double> bubbleGpa = bubbleSort(bubbleByGpa, [](const Student &s1, const Student &s2){return s1.getGpa() > s2.getGpa();});
    pair<int, double> bubbleName = bubbleSort(bubbleByName, [](const Student &s1, const Student &s2){return s1.getName() < s2.getName();});
    pair<int, double> shellGpa = shellSort(shellByGpa, [](const Student &s1, const Student &s2){return s1.getGpa() < s2.getGpa();});
    pair<int, double> shellName = shellSort(shellByName, [](const Student &s1, const Student &s2){return s1.getName() > s2.getName();});
    pair<int, double> mergeGpa = mergeSort(mergeByGpa, [](const Student &s1, const Student &s2){return s1.getGpa() > s2.getGpa();});
    pair<int, double> mergeName = mergeSort(mergeByName, [](const Student &s1, const Student &s2){return s1.getName() < s2.getName();});
    pair<int, double> quickGpa = quickSort(quickByGpa, [](const Student &s1, const Student &s2){return s1.getGpa() < s2.getGpa();});
    pair<int, double> quickName = quickSort(quickByName, [](const Student &s1, const Student &s2){return s1.getName() > s2.getName();});

    // Writing to the file the results.
    try{
        // Writing to the gpa file.
        ofstream outFileGpa;
        outFileGpa.open("SortedByGpa.txt");
        if(!outFileGpa.is_open()){
            throw runtime_error("Sorry, file could not be opened or created.");
        }
        outFileGpa << "Algorithm: Insertion Sort" << endl << "No. of comparisons: " << insertionGpa.first << endl << "Running time: " << insertionGpa.second << endl;
        for(auto const& it: insertionByGpa){
            outFileGpa << it.getName() << endl << it.getId() << endl << it.getGpa() << endl;
        }
        outFileGpa << endl;
        outFileGpa << "Algorithm: Selection Sort" << endl << "No. of comparisons: " << selectionGpa.first << endl << "Running time: " << selectionGpa.second << endl;
        for(auto const& it: selectionByGpa){
            outFileGpa << it.getName() << endl << it.getId() << endl << it.getGpa() << endl;
        }
        outFileGpa << endl;
        outFileGpa << "Algorithm: Bubble Sort" << endl << "No. of comparisons: " << bubbleGpa.first << endl << "Running time: " << bubbleGpa.second << endl;
        for(auto const& it: bubbleByGpa){
            outFileGpa << it.getName() << endl << it.getId() << endl << it.getGpa() << endl;
        }
        outFileGpa << endl;
        outFileGpa << "Algorithm: Shell Sort" << endl << "No. of comparisons: " << shellGpa.first << endl << "Running time: " << shellGpa.second << endl;
        for(auto const& it: shellByGpa){
            outFileGpa << it.getName() << endl << it.getId() << endl << it.getGpa() << endl;
        }
        outFileGpa << endl;
        outFileGpa << "Algorithm: Merge Sort" << endl << "No. of comparisons: " << mergeGpa.first << endl << "Running time: " << mergeGpa.second << endl;
        for(auto const& it: mergeByGpa){
            outFileGpa << it.getName() << endl << it.getId() << endl << it.getGpa() << endl;
        }
        outFileGpa << endl;
        outFileGpa << "Algorithm: Quick Sort" << endl << "No. of comparisons: " << quickGpa.first << endl << "Running time: " << quickGpa.second << endl;
        for(auto const& it: quickByGpa){
            outFileGpa << it.getName() << endl << it.getId() << endl << it.getGpa() << endl;
        }
        outFileGpa << endl;
        outFileGpa.close();

        // Writing to the name file.
        ofstream outFileName;
        outFileName.open("SortedByName.txt");
        if(!outFileName.is_open()){
            throw runtime_error("Sorry, file could not be opened or created.");
        }
        outFileName << "Algorithm: Insertion Sort" << endl << "No. of comparisons: " << insertionName.first << endl << "Running time: " << insertionName.second << endl;
        for(auto const& it: insertionByName){
            outFileName << it.getName() << endl << it.getId() << endl << it.getGpa() << endl;
        }
        outFileName << endl;
        outFileName << "Algorithm: Selection Sort" << endl << "No. of comparisons: " << selectionName.first << endl << "Running time: " << selectionName.second << endl;
        for(auto const& it: selectionByName){
            outFileName << it.getName() << endl << it.getId() << endl << it.getGpa() << endl;
        }
        outFileName << endl;
        outFileName << "Algorithm: Bubble Sort" << endl << "No. of comparisons: " << bubbleName.first << endl << "Running time: " << bubbleName.second << endl;
        for(auto const& it: bubbleByName){
            outFileName << it.getName() << endl << it.getId() << endl << it.getGpa() << endl;
        }
        outFileName << endl;
        outFileName << "Algorithm: Shell Sort" << endl << "No. of comparisons: " << shellName.first << endl << "Running time: " << shellName.second << endl;
        for(auto const& it: shellByName){
            outFileName << it.getName() << endl << it.getId() << endl << it.getGpa() << endl;
        }
        outFileName << endl;
        outFileName << "Algorithm: Merge Sort" << endl << "No. of comparisons: " << mergeName.first << endl << "Running time: " << mergeName.second << endl;
        for(auto const& it: mergeByName){
            outFileName << it.getName() << endl << it.getId() << endl << it.getGpa() << endl;
        }
        outFileName << endl;
        outFileName << "Algorithm: Quick Sort" << endl << "No. of comparisons: " << quickName.first << endl << "Running time: " << quickName.second << endl;
        for(auto const& it: quickByName){
            outFileName << it.getName() << endl << it.getId() << endl << it.getGpa() << endl;
        }
        outFileName << endl;
        outFileName.close();
    }
    catch (const runtime_error &e){
        cout << "Exception : " << e.what() << endl;
    }
    catch(...){
        cout << "Unknown exception occurred." << endl;
    }
    return 0;
}