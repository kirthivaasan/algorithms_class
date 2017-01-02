#include <vector>
#include <iostream>
#include <cstdlib>
#include "SortingAlgorithm.cpp"

#ifndef MERGESORT
#define MERGESORT

/*
	Sorts a vector of ints using merge sort.
*/

class MergeSort : public SortingAlgorithm {
private:
	std::vector<int> merge(std::vector<int> v1, std::vector<int> v2) {
		/*
			Merging step is O(3n) => O(n)
			This step is brilliant.
		*/
		//std::cout << v1.size() << " " << v2.size() << std::endl;
		std::vector<int> temp;
		temp.reserve(v2.size() + v1.size());
		int i = 0, j = 0;
		while (i < v1.size() && j < v2.size()) {
			 if (v1[i] < v2[j]) {
				 temp.push_back(v1[i]);
				 i++;
			 } else {
				 temp.push_back(v2[j]);
				 j++;
			 }
		}
		
		for	(; i < v1.size(); i++) temp.push_back(v1[i]);
		for	(; j < v2.size(); j++) temp.push_back(v2[j]);
		
		return temp;
	}
	
	virtual std::vector<int> sort(std::vector<int>& v) {
		if (v.size() <= 1) return v;
		std::vector<int> firstHalf(v.begin(), v.begin() + v.size()/2);
		std::vector<int> secondHalf(v.begin() + v.size()/2, v.end());
		return merge(sort(firstHalf), sort(secondHalf));
	}
	
	
public:
	MergeSort(std::vector<int> &v) : SortingAlgorithm(v) {
		
	}
};

#endif