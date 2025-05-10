/////////////////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v4)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement posted on edX:
// (Course > Assignments > Assignment Information & Policies > Academic Integrity Policy)
/////////////////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with:

// No one
//
// Name: Adrina Esfandiari
// login ID: a2esfand
//////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>


/////////////////////////////////////////////////////////
/////////////// DO NOT MODIFY THIS CODE /////////////////
/////////////////////////////////////////////////////////

const int MAX_SHIPS = 5;
const int MAX_SHOTS = 100;
const int MAX_STR_LEN = 50;
const int BOARD_ROWS = 10;
const int BOARD_COLS = 10;

struct ship {
	char name[51];     // ship's name (e.g. "Battleship")
	char sym;          // symbol for use on the board (e.g. 'B')
	bool is_vert;      // true if positioned vertically, false if horizontal
	int length;        // number of spaces occupied
	int top_left_row;  // row index of top-leftmost occupied square
	int top_left_col;  // column index of top-leftmost occupied square
	int hits;          // number of times this ship has been hit
};


// print_ship(shp) prints the fields of the ship pointed to by shp to stdout
// requires: shp is a valid ship
// effects: produces output
void print_ship(const struct ship *shp) {
	assert(shp);
	printf("Name: %s, Symbol: %c, Vertical?: %d, ",
	    	shp->name, shp->sym, shp->is_vert);
	printf("Length: %d, Top Left Row: %d, Top Left Col: %d\n",
			shp->length, shp->top_left_row, shp->top_left_col);
}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////// YOU MAY MAKE EDITS IN THE FOLLOWING SECTION /////////
///// DO NOT CHANGE FUNCTION SIGNATURES OF REQUIRED FUNCTIONS //////
//// INCLUDE DOCUMENTED HELPER FUNCTIONS IF ANY IN THIS SECTION ////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


// read_ship(shp) reads the values of a ship from stdin and assigns them to the
//   ship pointed to by shp if and only if successful. Returns true if successful
//   and false if not.
// requires: shp is a valid struct ship
// effects: reads input,
//          may mutate the ship pointed to by shp
bool read_ship(struct ship *shp) {
  assert(shp); 
	// Notice that *shp is given to us, meaning that we can 
	// use it to mutates the information.

	int i = 0; 
	char name[51];  // Temporary name storage
    char sym;
    char vert_or_horiz;
    int length;
    int row;
    int col;

	while (i < 6){
		if (i == 0){
			// inputing the name
			if (scanf(" %50s", name) == 1){
				strcpy(shp->name, name);
			} else {
				return false; 
			}
			
		} else if (i == 1) {
			// inputing the symbol for ship
			if (scanf(" %c", &sym) == 1){
				shp->sym = sym; 
			} else {
				return false; 
			}

		} else if (i == 2) {
			// horizontal vertical placement
			if (scanf(" %c", &vert_or_horiz) == 1){
				if (vert_or_horiz == 'v'){
					shp->is_vert = true; 
				} else {
					shp->is_vert = false; 
				}

			} else {
				return false; 
			}

		} else if (i == 3) {
			// The length of ship
			if (scanf(" %d", &length) == 1){
				shp->length = length; 
			} else {
				return false; 
			}
			
		} else if (i == 4) {
			// row of the top left square occupied by the ship
			if (scanf(" %d", &row) == 1){
				shp->top_left_row = row; 
			} else {
				return false; 
			}

		} else {
			// col of the top left square occupied by the ship
			if (scanf(" %d", &col) == 1){
				shp->top_left_col = col; 
			} else {
				return false; 
			}
		}
		i++; 
	}

	// And we have to initiliz hit to zero, so we have: 
	shp->hits = 0; 
	return true; 
}


// print_board(char *board) which takes as a parameter a char *. 
// This pointer points to a char array of size 100, to be interpreted 
// as a 2D grid of 10 rows and 10 columns, as described in the 
// introduction to this question.
// requires:  board is not NULL,
void print_board(char *board) {
	// *board is a pointer to a char array of size 100. 
	// If you run this: 
	// for (int j = 0 ; j < 100; j++){
	//    printf("%d \n", board[j]); 
	// }
	// you get 46, 46, ..., 46
	// which represents the ASCII number for .
	// meaning that the given array is already filled with.
	assert(board); 
	// we just need to organise it. 
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            printf("%c", board[i * BOARD_COLS + j]);  // Access correct index
        }
        printf("\n");
    }
}


// place_ship(const struct ship *shp, char *board) places the 
// ship onto the board if the  location indicated by 
// the ship's fields is valid.
// requires:  board is not NULL,
//            shp is not NULL
bool place_ship(const struct ship *shp, char *board) {
	// it is a valid position if the length of the 
	// ship fits in the board, 
	// and 
	// it is not in the squares of other ships
	
	// Length condition: 
	// This means: length <= 10
	
	// Square condition: 
	// well a square is full if it is copntained
	// by a capital element. 
	
	// if it is '.', then it is not occupied 
	// and we can replace it. 
	
	// Already defined constatnts: 
	// const int BOARD_ROWS = 10;
  	// const int BOARD_COLS = 10;  
    assert(shp);
    assert(board);

    int row = shp->top_left_row;
    int col = shp->top_left_col;

    // Check if the ship fits within board boundaries
    if (shp->is_vert) {
        if (row + shp->length > BOARD_ROWS){ 
          // Out of bounds when it is vertical. 
          return false;
        }  

        // Check if any cell in the path is already occupied
        for (int i = 0; i < shp->length; i++) {
            // this if checks if the cell is occupied or not. 
            // Notice that if we are in the point let's say (4,5), 
            // then 4 = row, 5 = col
            // then in our array, this is like: 
            // (4 * 10) --> since we go through the first 40 places in 
            // row 1-4
            // then to reach the col 5 we add 
            // (4 * 10) + 5
            
            
            // So the way I structured array as a board is that
            // the first 10 number represents the first row
            // the second 10 number represents the second row
            // and so on, then each col, is basically
            // in between these for example row 1 col 7 is 7
            // row 30 col 6 is 36 and so on. 
            
            // Hence we have: 
            // index = row * 10 + col
            
            // now let's say length = 4, we want to be vertical
            // so like
            // * --> starting point according to ship->row 
            // * 
            // * 
            // * 
            // Example: 
            // Battelship --> length = 4, vertical, start row = 1, col = 3
            // then the occupid places by this ship would be
            // 13, 23, 33, 43
            // and the following if statement do the following for us. 
            if (board[(row + i) * BOARD_COLS + col] != '.'){
              // it checks if that position is not '.', then it is fill 
              // with something else so it is full
              // and then we return false. 
              return false;
              
            }  
        }
        
        // Place the ship
        for (int i = 0; i < shp->length; i++) {
          // now same idea we just now place the ship with its symbol
            board[(row + i) * BOARD_COLS + col] = shp->sym;
        }
        
        
    } else { 
      // Horizontal placement
        if (col + shp->length > BOARD_COLS){
          // The ship is out of bounds whne is horizontal and
          // ship + col is more then BOUNDS_COL
           return false; 
        }
        
        // Check if any cell in the path is already occupied
        for (int i = 0; i < shp->length; i++) {
          // now this is easier to understand 
          // Example
          // Battelship: horizontal, length = 3, row = 1, col = 4
          // now isnce it is horizontal, and it is valid position, 
          // meaning that it does not exeed the board, 
          // then the ship is placed in the row-10th, statring with shp->col
          // meaing that in here: 
          // the row is 1, so the ship is in the FIRST 10th place. 
          // now statring from the sh->col, we get: 
          // occupied cells: 14, 15, 16
            if (board[row * BOARD_COLS + (col + i)] != '.'){
              // overlaping situation
              return false;
            } 
        }
        // placing the ship: 
        for (int i = 0; i < shp->length; i++) {
            board[row * BOARD_COLS + (col + i)] = shp->sym;
        }
    }
    return true;
}	

// fire_shot(board, shot_row, shot_col) simulates firing a shot on the given
//   board at row, shot_row, and column, shot_col. Changes the symbol at that
//   position to '-' if a miss, and '*' if a hit.
// requires: 0 <= shot_row < BOARD_ROWS,
//           0 <= shot_col < BOARD_COLS,
//           board is not NULL,
//           board has length BOARD_ROWS * BOARD_COLS (not asserted)
// effects: mutates the board pointed to by board
char fire_shot(char *board, const int shot_row, const int shot_col) {
  assert(board);
  assert(shot_row >= 0 && shot_row < BOARD_ROWS);
  assert(shot_col >= 0 && shot_col < BOARD_COLS);
	// finding the index of the shot in our array: 
	// index = row * 10 + col
	int shot_place_in_array = shot_row * BOARD_COLS + shot_col; 
	char shot_place = board[shot_place_in_array]; 
	
	// Now we have few cases: 
	// if the cell is not occupied with any ship: 
	// it is a miss --> return '.', and replace the sym with '-'
	
	// if the cell is occupied with a ship:
	// it is a miss --> return 'shp->sym', and replace the sym with '*'
	if (shot_place == '.'){
	  // meaning that it is missed:
	  shot_place = '-'; 
	  
	} else {
	  // meaning that it is fired to a ship:
	  shot_place = '*'; 
	}
	
	// And then at the end we just return the original 
	// char before it was shot, which is basically
	// shot_place = [shot_place_in_array], so: 
	return shot_place; 
}


// play_battleship(ship_arr, num_ships, board, num_shots, shot_rows, shot_cols)
//   simulates a (single-player) game of Battleship on the given board. ship_arr
//   contains a number of ships equal to num_ships. shot_rows and 
//   shot_cols each contain num_shots items. The row of shot i is given by
//   shot_rows[i], and the column by shot_cols[i].
//   Prints a message to stdout for each shot that misses, hits,
//   and each ship sunk.
// requires: ship_arr is not NULL,
//           ships in ship_arr are already added to board (not asserted)
//           board is not NULL,
//           shot_rows is not NULL,
//           shot_cols is not NULL,
//           shot_rows and shot_cols have length num_shots (not asserted)
// effects: mutates the board pointed to by board
//          may mutate the ships in ship_arr
//          may produce output
void play_battleship(struct ship *ship_arr, const int num_ships, char *board,
		const int num_shots, const int *shot_rows,
		const int *shot_cols) {
	// This function has 5 main things that it has to do: 
  // 1. Goes through the list of shots.
  // 2. Call fire_shot for each shot and keep track of results:
  // 3. Print "Hit at R%d C%d\n" or "Miss at R%d C%d\n" 
  // based on whether a ship was hit.
  // 4. If a ship was hit, update its hits field.
  // 5. If the ship's hits equals its length, print "%s was sunk!\n".
  
  // First assertions: 
    assert(ship_arr);
    assert(board);
    assert(shot_rows);
    assert(shot_cols);
    
  // Second step: Defining the variables we need: 
  int shot_row = 0; 
  int shot_col = 0; 
  char shot_result = '\0'; 
  
  // Third step go through the list of shots: 
    for (int i = 0; i < num_shots; i++) {
      // Ok first we see where our shot is for the first shot: 
        shot_row = shot_rows[i]; 
        shot_col = shot_cols[i];
        
        // now shot result is the return value of firs_shot function. 
        shot_result = fire_shot(board, shot_row, shot_col);
        
        // Now if the shot_result = '.', then the shot is missed
        // so we print "Miss at R%d C%d\n". 
        if (shot_result == '.') {
          // if the shot is missed: 
            printf("Miss at R%d C%d\n", shot_row, shot_col);
            
        } else {
          // Else if the shot_result is any other element, then: 
          // 1. print that it is hitten
          // 2. update the results 
            printf("Hit at R%d C%d\n", shot_row, shot_col);
            
            for (int j = 0; j < num_ships; j++) {
              // Now we go through the ship array that we have: 
              // and notice that this array is an array of structures
              // so in order to access the number of hits
              // or other information, we need to define a pointer
              // to that specific ship and mutate it using the pointer. 
                struct ship *shp = &ship_arr[j];
                if (shp->sym == shot_result) {
                  // if the sho->sym is smae as result, 
                  // then it means that shp is fired
                  // so we add 1 to its number of hits
                    shp->hits++;
                  
                  // In addition we have to check if the number of the hits
                  // is equivelant to the length of the ship
                  // then it means we have hit the whole ship
                  // and it is sunk so we check: 
                    if (shp->hits == shp->length) {
                        printf("%s was sunk!\n", shp->name);
                        // If the ship is sunk, then we're done. 
                        break; 
                    }
                }
            }
        }
    }
}


/////////////////////////////////////////////////////////
/////////// DO NOT MODIFY ANY CODE BELOW THIS ///////////
/////////////////////////////////////////////////////////


int main(void) {
	// Hard coded test harness will dictate what .in and .expect files 
	// are like for .in file:
	// first line is 1 integer, N, giving the number of ships
	// the next N lines give 1 ship each with 6 values:
	//   a string, the ship's name
	//   a char, a capital letter for representing the ship on the board
	//   a char, either h (horizontal placement) or v (vertical placement)
	//   an int, the length of the ship
	//   an int, the row of the top left square occupied by the ship
	//   an int, the column of the top left square occupied by the ship
	// until the end of the file, read lines beginning with a char:
	//   b: print the board
	//   s: print a ship
	//      followed by an int, the index of the ship to be printed
	//   p: play Battleship
	//      followed by int M, giving the number of shots
	//      followed by 2*M ints giving the row and column of shots
	//        (in the order row_0 col_0 row_1 col_1 row_2 col_2 ...)
	//   any other char: exit program
	// See sample .in and .expect files for examples.

	int num_ships = 0;
	char board[10 * 10];
	struct ship ship_arr[5];

	for (int i = 0; i < BOARD_ROWS; ++i) {
		for (int j = 0; j < BOARD_COLS; ++j) {
			board[i * BOARD_COLS + j] = '.';
		}
	}

	// read in ships
	if (!(scanf("%d", &num_ships) == 1)) {
		printf("Failed to read number of ships.\n");
		return 0;
	}
	if (num_ships > MAX_SHIPS) {
		printf("Number of ships exceeds maximum.\n");
		return 0;
	}
	for (int i=0; i<num_ships; ++i) {
		if (!read_ship(&(ship_arr[i]))) {
			printf("Invalid ship.\n");
			return 0;
		} else if (!place_ship(&(ship_arr[i]), board)) {
			printf("Invalid ship placement.\n");
			return 0;
		}
	}

	char command = '\0';
	int print_index = 0;
	int num_shots = 0;
	int shot_rows[100];
	int shot_cols[100];
	
	// read in commands
	while (scanf(" %c", &command) == 1) {
		if (command == 'b') {
			print_board(board);
		} else if (command == 's') {
			if (scanf("%d", &print_index) == 1 && print_index >= 0 &&
			   print_index < MAX_SHIPS) {
				print_ship(&(ship_arr[print_index]));
			} else {
				printf("Given invalid ship index to print.\n");
				return 0;
			}
		} else if (command == 'p') {
			if (scanf("%d", &num_shots) == 1 && num_shots >= 0 &&
			   num_shots < MAX_SHOTS) {
				for (int i = 0; i < num_shots; ++i) {
					bool read_success = scanf("%d", &(shot_rows[i])) == 1;
					read_success = read_success &&
					               scanf("%d", &(shot_cols[i])) == 1;
					if (!read_success) {
						printf("Failed to read shot coordinates.\n");
						return 0;
					}
				}
				play_battleship(ship_arr, num_ships, board,
				                num_shots, shot_rows, shot_cols);
			} else {
				printf("Given invalid number of shots.\n");
				return 0;
			}
		} else {
			printf("Exiting.\n");
			return 0;
		}
	}
} 