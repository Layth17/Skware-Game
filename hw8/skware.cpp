#include "skware.h"

Skware::Skware(const int size) : m_size(size) {
  _create_puzzle_grid();
  _fill_puzzle_grid();
  _create_sums_grid();
  _calculate_sums();
}

Skware::Skware(const Skware &source) : m_size(source.m_size) {
  _create_puzzle_grid();
  _create_sums_grid();

  // populate copied puzzle grid with source values
  for (int i = 0; i < m_size; i++){
    for (int j = 0; j < m_size; j++){
      m_grid[i][j] = source.m_grid[i][j];
    }
  }
  
  // populate copied sums grid with source values
  for (int i = 0; i < m_TYPES_OF_SUMS; i++){
    for (int j = 0; j < m_size; j++){
      m_sums[i][j] = source.m_sums[i][j];
    }
  }
}

Skware::~Skware(){
  _deallocate_memory();
}

Skware& Skware::operator=(const Skware &source){
  if (!(*this == source)){
    _deallocate_memory();
    m_size = source.m_size;
    _create_puzzle_grid();
    _create_sums_grid();

    // populate copied puzzle grid with source values
    for (int i = 0; i < m_size; i++){
      for (int j = 0; j < m_size; j++){
        m_grid[i][j] = source.m_grid[i][j];
      }
    }
  
    // populate copied sums grid with source values
    for (int i = 0; i < m_TYPES_OF_SUMS; i++){
      for (int j = 0; j < m_size; j++){
        m_sums[i][j] = source.m_sums[i][j];
      }
    }
  }

  return *this;
}

bool Skware::operator==(const Skware &source){
  bool equal = true;

  for (int i = 0; i < m_size; i++){
    for (int j = 0; j < m_size; j++){
      if (m_grid[i][j] != source.m_grid[i][j]){
        equal = false;
      }
    } 
  }
  
  return equal;
}

void Skware::_deallocate_memory(){
  // frees grid heap memory
  for (int i = 0; i < m_size; i++){
    delete[] m_grid[i];
  }
  delete[] m_grid;

  // frees sums heap memory
  for (int i = 0; i < m_TYPES_OF_SUMS; i++){
    delete[] m_sums[i];
  }
  delete[] m_sums;

  // null pointers
  m_grid = nullptr;
  m_sums = nullptr;
  return;
}

void Skware::_create_puzzle_grid(){
  // allocate memory
  m_grid = new short* [m_size];
  for (int i = 0; i < m_size; i++){
    m_grid[i] = new short[m_size];
  }

  // initialize memory
  for (int i = 0; i < m_size; i++){
    for (int j = 0; j < m_size; j++){
      m_grid[i][j] = m_INITIALIZATION_VALUE;
    }
  }

  return;
}

void Skware::_fill_puzzle_grid(){
  const int INCLUSIVE = 1;

  // generate random values
  for (int i = 0; i < m_size; i++){
    for (int j = 0; j < m_size; j++){
      m_grid[i][j] = m_MIN_CELL_VAL + (rand() % m_MAX_CELL_VAL - m_MIN_CELL_VAL + INCLUSIVE);
    }
  }

  return;
}

void Skware::_create_sums_grid(){
  // allocate memory
  m_sums = new short* [m_TYPES_OF_SUMS];
  for (int i = 0; i < m_TYPES_OF_SUMS; i++){
    m_sums[i] = new short [m_size];
  }

  // initialize memory
  for (int i = 0; i < m_TYPES_OF_SUMS; i++){
    for (int j = 0; j < m_size; j++){
      m_sums[i][j] = m_INITIALIZATION_VALUE;
    }
  }

  return;
}

void Skware::_calculate_sums(){
  // calculate sums and fill memory
  for (int i = 0; i < m_TYPES_OF_SUMS; i++){
    for (int j = 0; j < m_size; j++){
      // horizontal sums
      if (i == m_HORIZONTAL_SUM_IDX){
        for (int y = 0; y < m_size; y++){
          m_sums[i][j] += m_grid[j][y];
        }
      }

      // vertical sums
      if (i == m_VERTICAL_SUM_IDX){
        for (int y = 0; y < m_size; y++){
          m_sums[i][j] += m_grid[y][j];
        }
      }
    }
  }

  return;
}

void Skware::_hide_puzzle_values(){
  const int INCLUSIVE = 1;
  const int RESET = 0;
  int hidden = 0; // How many has been hidden so far
  int random_cell = 0; // a value from 1 to m_size * m_size
  int cell_counter = 0; // goes from 1 to random_cell
  
  while (hidden < m_TOTAL_HIDDEN){
    random_cell = (rand() % (m_size * m_size)) + INCLUSIVE;
    for (int i = 0; i < m_size; i++){
      for (int j = 0; j < m_size; j++){
        cell_counter++;
        // check we are at the random cell and we have not been chosen before
        if (cell_counter == random_cell && m_grid[i][j] != m_HIDDEN_FLAG){
          m_grid[i][j] = m_HIDDEN_FLAG;
          hidden++;
        }
      }
    }
    cell_counter = RESET;
  }
  
  return;
}

void Skware::display_puzzle(const bool hide){
  // prototype with fake numbers
  // +---+---+---+
  // | 7 | 2 | 7 | 34
  // +---+---+---+
  // | 2 | 5 | 3 | 12
  // +---+---+---+
  // | 1 | 5 | 5 | 56
  // +---+---+---+
  //  42   12  10

  if (hide == true)  
    _hide_puzzle_values();

  for (int i = 0; i < m_size; i++){
    cout << "+";

    for (int _ = 0; _ < m_size; _++)
      cout << "---+";

    cout << endl << "|";
    for (int j = 0; j < m_size; j++){
      if (m_grid[i][j] == m_HIDDEN_FLAG)
        cout << "   |";
      else
        cout << " " << m_grid[i][j] << " |";

      if (j == m_size -1){
        cout << " " << m_sums[m_HORIZONTAL_SUM_IDX][i];
      }
    }
    cout << endl;
  }

  cout << "+";
  for (int _ = 0; _ < m_size; _++)
    cout << "---+";

  cout << endl;
  for (int i = 0; i < m_size; i++)
    cout << " " << m_sums[m_VERTICAL_SUM_IDX][i] << " ";

  cout << endl;
  return;
}

void Skware::solve(){
  // m_sums[0][row] is horizontal
  // m_sums[1][col] is vertical
  int index;
  bool lock_solution = false;
  // int org_cell_val = 0;
  short ** possible_combo = new short * [m_TOTAL_HIDDEN];

  // point at the values with the hidden flag
  index = 0;
  for (int i = 0; i < m_size; i++){
    for (int j = 0; j < m_size; j++){
      if (m_grid[i][j] == m_HIDDEN_FLAG){
        possible_combo[index] = &m_grid[i][j];
        index++;
      }
    }
  }

  // // initialize to min
  // for (int p = 0; p < m_TOTAL_HIDDEN; p++){ // 1 1 1 1 1
  //   *possible_combo[p] = m_MIN_CELL_VAL;
  // }
  
  for (int a = m_MIN_CELL_VAL; a <= m_MAX_CELL_VAL; a++){
    for (int b = m_MIN_CELL_VAL; b <= m_MAX_CELL_VAL; b++){
      for (int c = m_MIN_CELL_VAL; c <= m_MAX_CELL_VAL; c++){
        for (int d = m_MIN_CELL_VAL; d <= m_MAX_CELL_VAL; d++){
          for (int e = m_MIN_CELL_VAL; e <= m_MAX_CELL_VAL; e++){
            if (!lock_solution){
              *possible_combo[0] = e;
              *possible_combo[1] = d;
              *possible_combo[2] = c;
              *possible_combo[3] = b;
              *possible_combo[4] = a;
              lock_solution = _check_solution();
            }
          }
        }
      }
    }
  }
  
  
  // for (int k = 0; k < m_MAX_CELL_VAL; k++){ // +0:6 +0:6 +0:6 +0:6 +0:6
  //   for (int i = 0; i < m_TOTAL_HIDDEN; i++){ // 0 1 2 3 4
  //     if (!lock_solution){   
  //       *possible_combo[i] = m_MIN_CELL_VAL + k;
  //       lock_solution = _check_solution();
  //     }
  //   }
  // }

  return;
}

bool Skware::_check_solution(){
  const int RESET = 0;
  int temp_horizontal_sum = 0;
  int temp_vertical_sum = 0;
  bool found = true;

  // temp horizontal sums
  for (int row = 0; row < m_size; row++){
    for (int col = 0; col < m_size; col++){
      temp_horizontal_sum += m_grid[row][col];
    }
    if (m_sums[m_HORIZONTAL_SUM_IDX][row] != temp_horizontal_sum){
      found = false;
    }
    temp_horizontal_sum = RESET;
  }

  // temp vertical sums
  for (int col = 0; col < m_size; col++){
    for (int row = 0; row < m_size; row++){
      temp_vertical_sum += m_grid[row][col];
    }

    if (m_sums[m_VERTICAL_SUM_IDX][col] != temp_vertical_sum){
      found = false;
    }
    temp_vertical_sum = RESET;
  }
  
  return found;
}


// dont include in final submittion
bool Skware::dumb(){
  bool found = true;

  for (int i = 0; i < m_size; i++)
  {
    for (int j = 0; j < m_size; j++)
    {
      if (m_grid[i][j] != 1)
      {
        found = false;
      }
    }
  }

  return found;
}
