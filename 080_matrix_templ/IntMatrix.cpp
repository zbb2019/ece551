#include "IntMatrix.h"

// default constructor
IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}

// constructor
IntMatrix::IntMatrix(int r, int c) :
    numRows(r),
    numColumns(c),
    rows(new IntArray *[r]()) {
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}

// copy constructor
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(new IntArray *[rhs.numRows]()) {
  for (int i = 0; i < rhs.numRows; i++) {
    // !!! rows = new Class*[], returns ** and needs 1 initialization for each pointer
    rows[i] = new IntArray(rhs[i]);
  }
}

// destructor
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

// assignment operator
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp = new IntArray *[rhs.numRows]();
    for (int i = 0; i < rhs.numRows; i++) {
      // !!! temp = new Class*[], returns ** and needs 1 initialization for each pointer
      temp[i] = new IntArray(rhs[i]);
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
int IntMatrix::getRows() const {
  return numRows;
}

// getColumns
int IntMatrix::getColumns() const {
  return numColumns;
}

// cosnt [] operator overloading
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

// [] operator overloading
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

// == operator overloading
bool IntMatrix::operator==(const IntMatrix & rhs) const {
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
IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(this->numRows == rhs.numRows);
  assert(this->numColumns == rhs.numColumns);
  IntMatrix ans(rhs.numRows, rhs.numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      (*ans.rows[i])[j] = (*rows[i])[j] + (rhs[i])[j];
    }
  }
  return ans;
}

// operator << overloading
std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
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
