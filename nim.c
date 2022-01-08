/* This project contains files from multiple sources, not all files are created by Jason Huras, some files were provided by the professor since the project was for educational
 * purposes. These files were produced by Professor Stefan Kremer at the University of Guelph CIS department
 * "alphanim.c"		Produced by Stefan Kremer
 * "makefile"		Produced by Jason Huras
 * "nim.c" 		Produced by Jason Huras
 * "nim.h"		Produced by Jason Huras
 * "nimhelp.c"		Produced by Stefan Kremer
*/
#include <stdio.h>
#include <stdlib.h>
#include "nim.h"

// creates board
int*new_board( int board_size ){
    int * board = malloc(sizeof(int) * board_size);
    if (board == NULL){ // if malloc fails
        fprintf(stderr, "Failed to allocate for board\b");
        exit(1);
    }
    return board;
}
// creates nodes
struct node *mk_nim_hash( int max_hash, int board_size, int * start_board ){
    struct node * returnnode = malloc(sizeof(struct node) * max_hash);
    if (returnnode == NULL){    // if malloc fails
        fprintf(stderr, "Failed to allocate for nodes\b");
        exit(1);
    }
    for (int i = 0; i < max_hash; ++i){// loopes through the new nodes and initializez them to default values
        returnnode[i].moves = -1;
        returnnode[i].move = NULL;
        returnnode[i].nimsum = -1;
        returnnode[i].board = hash2board(board_size, start_board, i);
    }
    return returnnode;
}
// frees board
void free_board(int * board){
    free(board);
}
// frees nodes
void free_nim_hash( int max_hash, struct node *nim_hash ){
    free(nim_hash->board);
    free(nim_hash->move);
    free(nim_hash);
}
// creates board from arguements
int * board_from_argv( int board_size, char ** argv ){
    int * board = malloc(sizeof(int) * board_size);
    for (int i = 0; i < board_size; ++i){   // takes the characters from the arguements and converts them into numbers and stores them to the board rows
        board[i] = atoi(argv[i]);
    }
    return board;
}
// copies board
int *copy_board(int board_size, int *board){
    int * copyboard = malloc(sizeof(int) * board_size);
    for (int i = 0; i < board_size; ++i){// copies all the board values
        copyboard[i] = board[i];
    }
    return copyboard;
}
// determines if the game is over given a board
int game_over(int board_size, int * board){
    int numberMatches = 0;
    for (int i = 0; i < board_size; ++i){// counts matches
        numberMatches += board[i];
    }
    if (numberMatches == 1){// if there is only one match,
        return 1;
    }
    else{
        return 0;
    }
}
// creates all the graphs and edges for every possible board using recursion
void join_graph (struct node * nim_hash, int hash, int board_size, int *start_board){
    nim_hash[hash].nimsum = compute_nimsum(board_size,nim_hash[hash].board);
    if (nim_hash[hash].moves != -1){
        return;
    }
    int numbermoves = 0;
    nim_hash[hash].moves = 0;
    for (int i = 0; i < board_size; ++i){
        numbermoves += nim_hash[hash].board[i];
    }
    nim_hash[hash].moves = numbermoves;
    nim_hash[hash].move = malloc(sizeof(struct move) * numbermoves);
    int j = 0;
    for (int i = 0; i < board_size; ++i){
        for (int k = 1; k <= nim_hash[hash].board[i]; ++k){
            nim_hash[hash].move[j].row = i;
            nim_hash[hash].move[j].matches = k;
            int * newboard = copy_board(board_size, nim_hash[hash].board);
            newboard[i] -= k;

            nim_hash[hash].move[j].hash = board2hash(board_size, start_board, newboard);
            join_graph(nim_hash, nim_hash[hash].move[j].hash, board_size, start_board);
            ++j;
        }
    }
}
// computes the nim sum for the given board
int compute_nimsum( int board_size, int * board){
    int nimsum = board[0];
    int specialcase = 1;
    if (board[0] > 1){
        specialcase = 0;
    }
    for (int i = 1; i < board_size; ++i){
        nimsum ^= board[i];
        if (board[i] > 1){
            specialcase = 0;
        }
    }
    if (specialcase){
        return !nimsum;
    }
    return nimsum;
}
