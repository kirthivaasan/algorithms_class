#include "MergeSort.cpp"
#include "QuickSort.cpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;

void printVector(vector<int> &numbers) {
	for (auto elem : numbers) cout << elem << " ";
	cout << endl;
}

void sortTest(SortingAlgorithm& sortingObject) {
	sortingObject.resort(); // does the actual sorting
	printVector(sortingObject.getSorted()); // prints sorted array
}

int main() {
	srand(time(0));
	vector<int> numbers;
	for (int i = 0; i < 10; i++) numbers.push_back(rand() % 100 + 1); // creates random vector of ints
	
	//MergeSort mergeSort(numbers);
	//sortTest(mergeSort);
	cout << "Original: " << endl;
	printVector(numbers);
	QuickSort quickSort(numbers);
	cout << "Sorted: " << endl;
	sortTest(quickSort);
	
}