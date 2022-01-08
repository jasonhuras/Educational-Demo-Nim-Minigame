# Educational-Exercise-Nim-Minigame
The Nim is a mathematical game of strategy in which two players take turns removing matches from an arbitrary number of rows. On each turn, a player must remove one or more match from a single row. The goal of the game is make the opponent take the final match left in all of the rows, at that point the play who didnt pick the last match is the winner.

In this version of the game, the computer wins most of the time. Try your luck to see if you can play perfectly to beat the computer!

Usage: 
1) Download source files and compile using the make command
2) Run the executable with command line parameters as follows. The first arguement is either '0' or '1', 0 indicating that the computer goes first and 1 indicating the player goes first. The following arguments indicate the amount of matches in each row, with each seperated by a space
3) Example run command "./a 0 5 3 2 1" would create a board with 4 rows, matches 5,3,2,1 respectivly with the computer making the first move.
4) To make a move enter the row number making sure the press ENTER, then entering the number of matches you wish to remove
