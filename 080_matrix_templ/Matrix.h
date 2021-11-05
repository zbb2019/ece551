#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;

 public:
  // default constructor
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}

  // constructor
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T> *[r]) {
    for (int i = 0; i < r; i++) {
      rows[i] = new std::vector<T>(c);
    }
  }

  // copy constructor
  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(new std::vector<T> *[rhs.numRows]()) {
    for (int i = 0; i < rhs.numRows; i++) {
      // !!! rows = new Class*[], returns ** and needs 1 initialization for each pointer
      rows[i] = new std::vector<T>(rhs[i]);
    }
  }

  // destructor
  ~Matrix() {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }

  // assignment operator
  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      std::vector<T> ** temp = new std::vector<T> *[rhs.numRows]();
      for (int i = 0; i < rhs.numRows; i++) {
        // !!! temp = new Class*[], returns ** and needs 1 initialization for each pointer
        temp[i] = new std::vector<T>(rhs[i]);
      }
      for (int i = 0; i < numRows; i++) {
        delete rows[i];
      }
      delete[] rows;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = temp;
    }
    return *this;
  }

  // getRow
  int getRows() const { return numRows; }

  // getColumns
  int getColumns() const { return numColumns; }

  // cosnt [] operator overloading
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }

  // [] operator overloading
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }

  // == operator overloading
  bool operator==(const Matrix & rhs) const {
    if (this->numRows != rhs.numRows || this->numColumns != rhs.numColumns) {
      return false;
    }
    for (int i = 0; i < numRows; i++) {
      if (*rows[i] != rhs[i]) {
        return false;
      }
    }
    return true;
  }

  // operator + overloading
  Matrix operator+(const Matrix & rhs) const {
    assert(this->numRows == rhs.numRows);
    assert(this->numColumns == rhs.numColumns);
    Matrix ans(rhs.numRows, rhs.numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        (*ans.rows[i])[j] = (*rows[i])[j] + (rhs[i])[j];
      }
    }
    return ans;
  }

  template<typename X>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<X> & rhs);
};

// operator << overloading
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  int szRow = rhs.getRows();
  if (szRow == 0) {
    s << "[]";
    return s;
  }
  s << "[";
  for (int i = 0; i < szRow - 1; i++) {
    s << rhs[i] << ",\n";
  }
  s << rhs[szRow - 1] << "]";
  return s;
}
template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  int sz = rhs.size();
  if (sz == 0) {
    s << "{}";
    return s;
  }
  s << "{";
  for (int i = 0; i < sz - 1; i++) {
    s << rhs[i] << ", ";
  }
  s << rhs[sz - 1] << "}";
  return s;
}

#endif
