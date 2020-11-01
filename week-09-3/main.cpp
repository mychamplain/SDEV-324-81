/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Champlain College SDEV-345-81
 *
 * C++ Week 9: Quicksort (first semester) - (2020/10/30)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Write a program that will randomly populate an array of 250 integers and print them
 * out in a formatted way to the console. Once printed, call a quicksort algorithm to
 * sort the array and print it out again, this time in order.
 *
 * Include the worst case running time in your output.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Written by Llewellyn van der Merwe <llewellyn.vandermerw@mymail.champlain.edu>, October 2020
 * Copyright (C) 2020. All Rights Reserved
 * License GNU/GPL Version 2 or later - http://www.gnu.org/licenses/gpl-2.0.html
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <memory>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Quick Sort Class
class QuickSort {
private:
    // the comparison counter
    int comparison_counter;
    // local sort needed for quick sort
    void sort(int *arr, int low, int high) {
        // some default stuff
        int i = low;
        int j = high;
        int pivot = *(arr + ((i + j) / 2));
        int temp;
        // compare the array positions
        while (position_compare(&i, &j)) {
            // compare the array values
            while (compare(&pivot, (arr + i)))
                i++;
            // compare the array values
            while (compare((arr + j), &pivot))
                j--;
            // compare the array positions
            if (position_compare(&i, &j)) {
                temp = *(arr + i);
                *(arr + i) = *(arr + j);
                *(arr + j) = temp;
                i++;
                j--;
            }
        }
        // compare the array values
        if (compare(&j, &low))
            sort(arr, low, j);
        // compare the array values
        if (compare(&high, &i))
            sort(arr, i, high);
    }
    // local compare for the positions
    bool position_compare(int *a, int *b) {
        comparison_counter++; // not sure if this should also be count (just comment out this line if not)
        return *a <= *b;
    }
    // function to compare values
    bool compare(int *a, int *b) {
        comparison_counter++;
        return *a > *b;
    }
public:
    // get comparison counter
    int getComparisonCounter() { return comparison_counter; }
    // sort function
    void sort(int *arr, int size ) {
        comparison_counter = 0;
        sort(arr, 0, size - 1);
    }
};

// function declarations
void printArray(int arr[], int size, string action);
void reverseArray(int arr[], int start, int end);
void printNotice(int microseconds, int comparisons, string status);
void printWorseCase(int random, int revers, int sorted);

// main function
int main() {
    // the size of our array
    const int SIZE = 250;
    // for random seeding
    time_t aTime;
    // array we would like to sort
    int arr[SIZE];
    // Instantiate Quick Sort
    shared_ptr<QuickSort> quick = make_shared<QuickSort>();
    // Seed randoms
    srand( static_cast<unsigned>(time(&aTime)) );
    // load 250 random values (between 0 - 3000)
    for(int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 3000;
    }
    // start the display
    cout << endl << " | THE QUICKSORT DEMONSTRATION" << endl;
    // display array before sorting
    printArray(arr, SIZE, "Random");
    // now we sort the the array
    cout << " | Sorting the RANDOM array with Quicksort" << endl;
    // get the starting point of the sort
    auto start = high_resolution_clock::now();
    // sort the array
    quick->sort(arr, SIZE);
    // After sort
    auto stop = high_resolution_clock::now();
    // display proof that the array was sorted
    printArray(arr, SIZE, "Sorted");
    // we get the duration of the sort in microseconds
    auto duration = duration_cast<microseconds>(stop - start);
    // give notice
    printNotice(duration.count(), quick->getComparisonCounter(), "RANDOM");
    // reverse the array to sort the array in worse case
    reverseArray(arr, 0, SIZE-1);
    // display proof that the array was reversed
    printArray(arr, SIZE, "Reversed");
    // now we sort the the array
    cout << " | Sorting the REVERSED array with Quicksort" << endl;
    // get the starting point of the sort
    auto again_start = high_resolution_clock::now();
    // sort the array
    quick->sort(arr, SIZE);
    // After sort
    auto again_stop = high_resolution_clock::now();
    // display proof that the was sorted
    printArray(arr, SIZE, "Sorted");
    // we get the duration of the sort in microseconds
    auto again_duration = duration_cast<microseconds>(again_stop - again_start);
    // give notice
    printNotice(again_duration.count(), quick->getComparisonCounter(), "REVERSED");
    // now we sort the the array
    cout << "_|___________________________________________________" << endl;
    cout << " | Sorting the SORTED array with Quicksort" << endl;
    // get the starting point of the sort
    auto and_again_start = high_resolution_clock::now();
    // sort the array
    quick->sort(arr, SIZE);
    // After sort
    auto and_again_stop = high_resolution_clock::now();
    // proof that it was sorted
    printArray(arr, SIZE, "Still Sorted");
    // we get the duration of the sort in microseconds
    auto and_again_duration = duration_cast<microseconds>(again_stop - again_start);
    // give notice
    printNotice(and_again_duration.count(), quick->getComparisonCounter(), "SORTED");
    // print the worse case
    printWorseCase(duration.count(), again_duration.count(), and_again_duration.count());
    return 0;
}

// Function to reverse arr[] from start to end
// https://www.geeksforgeeks.org/write-a-program-to-reverse-an-array-or-string/
void reverseArray(int arr[], int start, int end)
{
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

// Utility function to print an array
// https://www.geeksforgeeks.org/write-a-program-to-reverse-an-array-or-string/
void printArray(int arr[], int size, string action)
{
    cout << "_|___________________________________________________" << endl;
    cout << " | Display " << action;
    for (int i = 0; i < size; i++) {
        if (i % 20 == 0) {
            cout << endl;
            cout << " | ";
        }
        cout << arr[i] << " ";
    }
    cout << endl << "_|___________________________________________________" << endl;
}

// little function to print out notices
void printNotice(int microseconds, int comparisons, string status) {
    // show the duration
    cout << " | SORT Duration with (" << status << " ARRAY): " << microseconds << "μs" << endl;
    // show the comparisons
    cout << " | SORT Comparisons: " << comparisons << endl;
}

// little function to print the worse case
void printWorseCase(int random, int revers, int sorted) {
    // show the worse case
    cout << "_|___________________________________________________" << endl;
    cout << " | QUICKSORT WORSE CASE WAS ";
    if(random > revers && random > sorted) {
        cout << "RANDOM ARRAY: " << random << "μs" << endl;
    } else if(revers > random && revers > sorted) {
        cout << "REVERSED ARRAY: " << revers << "μs" << endl;
    } else {
        cout << "SORTED ARRAY: " << sorted << "μs" << endl;
    }
    cout << "_|___________________________________________________" << endl;
}
