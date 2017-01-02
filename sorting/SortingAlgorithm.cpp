#ifndef SORTING_ALGORITHM
#define SORTING_ALGORITHM

#include <vector>
#include <iostream>

class SortingAlgorithm {
private:
	std::vector<int> original;
	std::vector<int> sorted;
	
	void printArray(std::vector<int>& v) {
		for (auto elem : v) std::cout << elem << " ";
		std::cout << std::endl;
	}
	
public:
	SortingAlgorithm(std::vector<int> &v) {
		original = v;
	}
	
	virtual std::vector<int> sort(std::vector<int> &v) = 0;
	
	void resort() {
		sorted = sort(original);
	}
	
	std::vector<int>& getSorted() {
		//sorted = sort(original);
		return sorted;
	}
};

#endif