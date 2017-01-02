#include <iostream>
#include <cstdlib>
#include <vector>
#include <functional>
using namespace std;

/*
 Things to implement:
    1. rref()
    2. apply mathematical function to each element. E.g M.apply(sin)
    3. rref can be then used to find dim(), shape()
    4. transpose() / transpose(const Matrix& M) (don't bother providing static functions yet)
    5. Matrix slicing
    6. inverse() / inverse(const Matrix& M)
    7. 
*/

class Matrix {
private:
	float* array; // int changed to float
	int rows = 0;
	int columns = 0;
	
	bool validIndex(int row, int col) const {
		bool invalid = row < 1 || col < 1 || row > rows || col > columns;
		return !invalid;
	}
	
	bool canMultiply(const Matrix &b) const {
		return getColumns() == b.getRows();
	}
	
	int calcIndex(int row, int col) const {
		row--;
		col--;
		return (row * columns) + col;
	}
	
	void multiplyColumn(int col, int scalar) {
		if(!validIndex(1, col)) throw 1; // should throw invalid column error
		for (int r = 1; r <= rows; r++) {
			setElement(scalar * getElement(r, col), r, col);
		}
	}
	
public:
	Matrix(int numRows, int numCols) {
		array = new float[numRows * numCols](); // int changed to float
		rows = numRows;
		columns = numCols;
	}
	
	Matrix(float* m, int numRows, int numCols) { // int changed to float
		rows = numRows;
		columns = numCols;
		array = m;
		print();
	}
    
    void clear() {
        delete[] array;
		array = NULL;
    }
		
	~Matrix() {
		clear();
	}
	
	int getRows() const {
		return rows;
	}
	
	int getColumns() const {
		return columns;
	}
	
	void setElement(float num, int row, int col) {
		if (!validIndex(row, col)) throw row; // should throw invalid index error
		//cout << num << " calcIndex = " << row << ", " << col << " : " << calcIndex(row, col) << endl;
		array[calcIndex(row, col)] = num;
	}
	
	float getElement(int row, int col) const {
		if (!validIndex(row, col)) throw row; // should throw invalid index error
		return array[calcIndex(row, col)];
	}
	
	void apply() {
		
	}
	
	void print() const {
		//cout << "print() called " << endl << "\t\t" << rows << " " << columns << endl;
		for (int i = 1; i <= rows; i++) {
			for (int j = 1; j <= columns; j++) cout << getElement(i, j) << "\t";
			cout << endl;
		}
		cout << endl << endl;
	}
	
	void random(int lowest, int highest) {
		for (int i = 1; i <= rows; i++) {
			for (int j = 1; j <= columns; j++) {
				setElement((rand() % highest + 1) + lowest, i, j);
			} 
		}
	}
	
	void random() {
		random(0, 100);
	}
	
	Matrix& multiply(int scalar) {
		for (int i = 0; i < rows * columns; i++) {
			array[i] = array[i] * scalar;
		}
		return *this;
	}
	
	Matrix multiply(const Matrix &M) {
		if (!canMultiply(M)) throw 1; // should throw bad dimensions error
		//cout << "Can multiply" << endl;
		Matrix N(rows, M.getColumns());
		
		for (int r = 1; r <= rows; r++) {
			for (int m_col = 1; m_col <= M.getColumns(); m_col++) {
				float result = 0; // int changed to float
				for (int c = 1; c <= columns; c++) {
					result += getElement(r, c) * M.getElement(c, m_col);
				}
				N.setElement(result, r, m_col);
			}
		}
		return N;
	}
	
	
	Matrix operator*(const Matrix &M) {
		return multiply(M);
	}
	
	static bool canMultiply(const Matrix &a, const Matrix &b) {
		return a.getColumns() == b.getRows();
	}
};

int main() {
	float a[6] = {1.34, 2, 3, 4.6, 5, 6};
	float b[6] = {7, 8.2, 9, 10.124, 11, 12};
	Matrix A(a, 2, 3);
	Matrix B(b, 3, 2);
	//int entries =  500;
	//Matrix A(entries, entries);
	//Matrix B(entries, entries);
	//A.random();
	//B.random();
	
	(A * B).print();
}