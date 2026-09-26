#ifndef MATRIX_1D
#define MATRIX_1D

#include <iostream>
#include <cassert>
#include <cstddef>

class Matrix1D
{
public:
  Matrix1D(int num_of_row, int num_of_column)
  {
    // num of rows and columns must be above 0, if not terminate the program
    assert(num_of_row > 0);
    assert(num_of_column > 0);

    m_array = new int[static_cast<std::size_t>(num_of_row * num_of_column)];// dynamically allocating an array
                                                                            // static_cast int to unsigned int

    m_num_of_row = num_of_row;
    m_num_of_column = num_of_column;

    assign_values(); // all elements at start will be zeros
  }

  ~Matrix1D()
  {
    delete[] m_array; // memory of array will be freed
  }

  void print_array() const;

  const int* get_array() const { return m_array; }

  int get_length () const { return m_num_of_row * m_num_of_column; }

  void set_value(int row, int column, int value) const {  m_array[get_single_index(row, column)] = value; }

  int get_value(int row, int column) const { return m_array[get_single_index(row, column)]; }

private:
  void assign_values() const;

  int get_single_index(int row, int column) const { return (row *  m_num_of_column) + column; }

private:
  int* m_array {};
  int m_num_of_row{};
  int m_num_of_column {};
};

void Matrix1D::print_array() const
{
  for(int i = 0; i < m_num_of_row; i++)
  {
    for(int j = 0; j < m_num_of_column; j++)
    {
      std::cout << m_array[get_single_index(i, j)] << ' ';
    }
    std::cout << '\n';
  }
}

void Matrix1D::assign_values() const
{
  for(int i = 0; i < m_num_of_row; i++)
  {
    for(int j = 0; j < m_num_of_column; j++)
    {
      m_array[get_single_index(i, j)] = 0;
    }
  }
}

#endif
