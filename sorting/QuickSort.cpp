#include <vector>
#include <iostream>

#ifndef QUICKSORT
#define QUICKSORT

class QuickSort : public SortingAlgorithm {
private:
	void print(std::vector<int>& v) {
		for (auto elem : v) std::cout << elem << " ";
		std::cout << std::endl;
	}
	
	void swap(std::vector<int>& v, int i, int j) {
		//std::cout << "swapping " << v[i] << " and " << v[j] << std::endl;
		int temp = v[i];
		v[i] = v[j];
		v[j] = temp;
	}
	
	int partition(std::vector<int>& v, int pivot_index, int begin, int end) {
		// this step is brilliant.
		int divider = 1; // index of divider between smaller & larger elements of pivot
		swap(v, pivot_index, begin); // swap pivot with first element
		pivot_index = begin;
		int pivot = v[pivot_index];
		//std::cout << "pivot: " << pivot << std::endl;
		for (int i = begin + 1; i <= end; i++) {
			// smaller num right of pivot
			if (v[i] <= pivot) {
				swap(v, divider, i);
				divider++;
			}
		}
		int new_pivot_index = divider - 1;
		swap(v, new_pivot_index, begin);
		//std::cout << "If valid partition: " << validPartition(v, new_pivot_index) << std::endl;
		return new_pivot_index;
	}
	
	bool validPartition(std::vector<int>& v, int pivot_index) {
		//TODO
	}
	
	bool isSorted(std::vector<int>& v) {
		for (int i = 0; i < v.size() - 1; i++) if (v[i] > v[i+1]) return false;
		return true;
	}
	
	void sortHelper(std::vector<int>& v, int begin, int end) {
		// make a partition around pivot (in this case the middle element)
		// call recursively on elements left of pivot, and right of pivot
		if (begin >= end || end <= begin) return;
		int middle = (begin + end)/2;
		int index = partition(v, middle, begin, end); // partitions around the middle
		//std::cout << "pivot new index: " << index << std::endl;
		print(v);
		sortHelper(v, begin, index);
		sortHelper(v, index + 1, end);
	}
	
	virtual std::vector<int> sort(std::vector<int>& v) {
		sortHelper(v, 0, v.size() - 1);
		std::cout << "is it sorted? " << isSorted(v) << std::endl;
		return v;
	}
	
public:
	QuickSort(std::vector<int> &v) : SortingAlgorithm(v) {
		
	}
};

#endif