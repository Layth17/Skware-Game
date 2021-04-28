#include "main.h"

void greet(){
  cout << " ~ W E L C O M E  T O  ~" << endl;
  cout << "+---+---+---+---+---+---+" << endl
       << "| S | K | W | A | R | E |" << endl
       << "+---+---+---+---+---+---+" << endl
       << endl;
  return;
}

void sign_off(){
  cout << endl << "Terminating..." << endl << endl
       << "+---+---+   +---+---+   +---+---+   +---+       " << endl
       << "|           |   |   |   |   |   |   |    \\     " << endl
       << "+    ---+   +---+---+   +---+---+   +     \\    " << endl
       << "|       |   |   |   |   |   |   |   |     /     " << endl
       << "+---+---+   +---+---+   +---+---+   +---+       " << endl
       << endl
       << "*********     **      **     *********          " << endl
       << "**    ***      **    **      *********          " << endl
       << "**    ***       **  **       **                 " << endl
       << "**    ***        ****        **                 " << endl
       << "*********         **         *********          " << endl
       << "**    ***         **         **                 " << endl
       << "**    ***         **         **                 " << endl
       << "**    ***         **         *********          " << endl
       << "*********         **         *********          " << endl
       << endl;
  return;
}

bool user_wants_to_play(){
  const char YES = 'y';
  const char NO = 'n';
  static int puzzle_count = 0;
  char usr_choice = 'c';
  bool play = false;

  while (!(usr_choice == YES || usr_choice == NO)){
    if (puzzle_count == 0)
      cout << "Would you like to play a puzzle (y/n) ?_ ";
    else
      cout << endl << "Would you like to play another puzzle (y/n) ?_ ";

    cin >> usr_choice;
  }
  
  if (usr_choice == YES){
    play = true;
    puzzle_count++;
  }
    
  return play;
}

int get_puzzle_size(){
  const int LOWER_BOUND = 6;
  const int UPPER_BOUND = 10;
  int user_desired_grid_size = 0;

  while (!(user_desired_grid_size >= LOWER_BOUND && 
          user_desired_grid_size <= UPPER_BOUND)){

    cout << "Please input a grid value between " << LOWER_BOUND << "-" 
         << UPPER_BOUND << " inclusive:_ ";

    cin >> user_desired_grid_size;
  }
  cout << endl;
  return user_desired_grid_size;
}

void waiting_to_display_solution(){
  bool user_wants_solution = false;
  char user_choice;
  while(!user_wants_solution){
    cout << "Wanna solution (y)?_ ";
    cin >> user_choice;
    if (user_choice == 'y'){
      user_wants_solution = true;
    }
  }
  cout << endl;
  return;
}


// dont include in final submittion
void cool(){
  bool found = false;
  long unsigned int counter = 0;
  long unsigned int supp = 0;
  // 1x 16 1x1
  // 7x 319 for 2x2
  // 10372421 for 3*3

  while (!found)
  {
    Skware blah(2);
    if(blah.dumb()){
      blah.display_puzzle(false);
      found = true;
    }

    counter++;
    cout << counter << " " << endl;
    if (counter == 2147483647)
    {
      counter = 0;
      supp++;
    }
  }
  
  return;
}












