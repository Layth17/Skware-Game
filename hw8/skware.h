#ifndef SKWARE_H
#define SKWARE_H

#include <cstdlib>
#include <iostream>
#include <cstdlib>
using std::cout;
using std::endl;

class Skware{

private:
  static const int m_INITIALIZATION_VALUE = 0; // all heap initialized to
  static const int m_TYPES_OF_SUMS = 2; // horizontal and vertical
  static const int m_HORIZONTAL_SUM_IDX = 0; //m_sums index for horizontal sums
  static const int m_VERTICAL_SUM_IDX = 1; //m_Sums index for vertical sums
  static const int m_TOTAL_HIDDEN = 5; // total un-revealed values
  static const int m_HIDDEN_FLAG = -1; // marks hidden values
  static const int m_MAX_CELL_VAL = 7; // max value in a cell
  static const int m_MIN_CELL_VAL = 1; // min value in a cell

  short ** m_grid = nullptr;
  short ** m_sums = nullptr;
  int m_size = 0;
  
private:
  void _create_puzzle_grid();
  void _fill_puzzle_grid();
  void _create_sums_grid();
  void _calculate_sums();
  void _hide_puzzle_values();
  void _deallocate_memory();
  bool _check_solution();

public:
  Skware(const int rows = 0);
  Skware(const Skware &source);
  ~Skware();

  Skware& operator=(const Skware &source);
  void solve();
  bool operator==(const Skware &source);
  void display_puzzle(const bool hide = true);

  bool dumb();
};

#endif