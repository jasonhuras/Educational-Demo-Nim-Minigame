/* This project contains files from multiple sources, not all files are created by Jason Huras, some files were provided by the professor since the project was for educational
 * purposes. These files were produced by Professor Stefan Kremer at the University of Guelph CIS department
 * "alphanim.c"		Produced by Stefan Kremer
 * "makefile"		Produced by Jason Huras
 * "nim.c" 		Produced by Jason Huras
 * "nim.h"		Produced by Jason Huras
 * "nimhelp.c"		Produced by Stefan Kremer
*/
#include "nim.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* this program implements a human computer game of misere
 * nim
 *
 * The first argument decides who goes first:
 *   0 - computer
 *   1 - human
 *
 * The remaining arguments are the number of matches in each
 * row.
 */

int main( int argc, char **argv )
{
  char input[16];	// general input string
  int player;		// whose turn it is

  if (argc<3)
  {
    fprintf( stderr, "usage:  %s first_turn matches\n", argv[0] );
    exit(-1);
  }

  player = atoi( argv[1] );


  int board_size = argc-2;

  // store initial board for re-use
  int *start_board = board_from_argv( board_size, argv+2 );

  // determine how big the hash table needs to be
  int max_hash = compute_max_hash(board_size,start_board);

  // populate the hash table with boards
  struct node *nim_hash = mk_nim_hash( max_hash, board_size, start_board );

  // add moves (edges) to the graph
  join_graph( nim_hash, max_hash-1, board_size, start_board );

  // set current_board to a copy of the start_board
  int *current_board = copy_board( board_size, start_board );

  // begin multi-game loop
  do
  {  
    // begin single game loop
    while ( !game_over(board_size, current_board) )
    {
      int row, matches;
      if (player)	// human
      {
        printf( "Ready Player 1:\n" );
        print_board( board_size, current_board );
 
        // prompt human for move	
        printf( "Row: " );
        fgets( input, 16, stdin );
        row = atoi( input );

        printf( "Matches: " );
        fgets( input, 16, stdin );
        matches = atoi( input );

	// if input is invalid, just ask the user again
        if ( row>board_size ||
	     matches<=0 ||
	     current_board[row] < matches )
	{
	  printf( "Invalid move!\n" );
	  continue;
	}
      }
      else // computer
      {
	// find node corresponding to current board
	struct node *node = nim_hash + 
	  board2hash(board_size, start_board, current_board);


	// pick first available move
	row = node->move[0].row;
	matches = node->move[0].matches;

        // loop over possible moves
	for (int i=0;i<node->moves;i++)
	{
	  struct node *next = nim_hash + node->move[i].hash;

	  // if move is really good, do that instead
	  if (next->nimsum==0)
	  {
	    row = node->move[i].row;
	    matches = node->move[i].matches;
	    break;  // quit looking for other moves
	  }
	}

        printf( "Computer removes %d matches from row %d\n", 
	                          matches, row );

      }

      // change current board to reflect the move
      current_board[row] -= matches;

      // switch players
      player = !player;
    }

    // game is done
    free_board( current_board ); // because it was malloc'd

    // get a new board copy
    current_board = copy_board( board_size, start_board );

    // print result message
    if (player)
    {
      printf( "Sorry, you lost!  Game over.\n" );
    }
    else
    {
      printf( "Congratulations, you won!\n" );
    }

    // prompt to play again
    printf( "Play again (y/n): " );
    fgets( input, 16, stdin );

    // keep looping while human wants to play
  } while ( strcmp( input, "y" )==0 || 
            strcmp( input, "Y" )==0 );

  // free the memory
  free_nim_hash( max_hash, nim_hash );
  free_board( current_board );
  free_board( start_board );

  return 0;
}

