#include "main.h"

int main(){
  const bool hide = true;
  srand(time(NULL));

  greet();
  while(user_wants_to_play()){
    Skware puzzle(get_puzzle_size());
    Skware soln(puzzle);
    puzzle.display_puzzle();
    cout << endl << "Here's your puzzle....solve it if you can!" << endl;
    waiting_to_display_solution();
    puzzle.solve();
    puzzle.display_puzzle(!hide);
    if (soln == puzzle){
      cout << endl << "Generated solution matches the original solution!" << endl;
    }
    else{
      cout << endl << "Generated solution doesn't match the original solution!" << endl;  
    }
  }
  sign_off();

  return 0;
}