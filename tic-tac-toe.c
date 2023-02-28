#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void showBoard(char cells[][3]);
void selectCell(char cells[][3], char player);
void initGame(char cells[][3]);
char checkWinner(char cells[][3]);

int main()
{
  char play;
  char cells[3][3];

  do
  {
    initGame(cells);

    printf("\nNew game ? S/N: \n");
    fflush(stdin);
    scanf("%c", &play);
  } while (play == 'S' || play == 's');

  return 0;
}

void showBoard(char cells[][3])
{
  system("cls");
  printf("\n");
  printf("\t %c | %c | %c\n", cells[0][0], cells[0][1], cells[0][2]);
  printf("\t-----------\n");
  printf("\t %c | %c | %c\n", cells[1][0], cells[1][1], cells[1][2]);
  printf("\t-----------\n");
  printf("\t %c | %c | %c\n", cells[2][0], cells[2][1], cells[2][2]);
  printf("\n");
}

void initGame(char cells[][3])
{
  srand(time(NULL));
  int random = rand() % 2;
  char winner = '\0';
  char player = random ? 'X' : 'O';

  for (int row = 0; row < 3; row++)
    for (int column = 0; column < 3; column++)
      // THIS FILLS ALL THE MULTIDIMENSIONAL-ARRAY WITH THE NUMBERS.
      // WE NEED TO INITIALIZE IN '1' AND ADD INT VALUE OF ROW AND COLUMN TO INCREMENT THE ASCII VALUE, SO '1' WILL BE '2', '3',...
      cells[row][column] = '1' + row * 3 + column;

  do
  {
    selectCell(cells, player);

    // AFTER SELECTING CELL, WE NEED TO CHANGE THE PLAYERS WHO SELECTS THE NEW CELL.
    player = player == 'X' ? 'O' : 'X';

    winner = checkWinner(cells); // IF CHECK WINNER RETURNS A CHAR EQUALS TO '\0' THE GAME CONTINUE.
  } while (winner == '\0');

  showBoard(cells);

  if (winner != 'D')
    printf("\n'%c' WON!\n\n", winner);
  else
    printf("\nDraw!\n\n");
}

void selectCell(char cells[][3], char player)
{
  int row, column, selectedNumber = 0;

  while (1)
  {
    showBoard(cells);

    printf("Select a cell '%c:' ", player);

    if (scanf("%i", &selectedNumber) != 1)
      fflush(stdin);

    if (selectedNumber < 1 || selectedNumber > 9)
      continue;

    // THIS IS THE OPERATION TO DO TO HAVE THE EXACT ROW AND COLUMN THROUGH A NUMBER WHICH IS SELECTED BY USER.
    row = (selectedNumber - 1) / 3;
    column = (selectedNumber - 1) % 3;
    // EXAMPLE, USER NUMBER = 1 REFERS TO CELLS[0][0] OR USER NUMBER = 7 REFERS TO CELLS[2][0];
    // ROW = (1 - 1) / 3 => 0, COLUMN = (1 - 1) % 3 = 0
    // ROW = (7 - 1) / 3 => 6 / 3 => 2, COLUMN = (7 - 1) % 3 => 6 % 3 => 0
    // THE CONVERSION WORKS!

    if (cells[row][column] == 'X' || cells[row][column] == 'O')
      continue;

    cells[row][column] = player;
    break;
  }
}

/*POSIBLE VALUES TO RETURN:
'\0': CONTINUE THE GAME, NOBODY WONS AND THERE IS STILL ONE FREE CELL.
'X': THERE IS A WINNER, IS 'X'.
'O': THERE IS A WINNER, IS 'O'.
'D': IT'S A DRAW. BECAUSE THE BOARD IS FULL AND THERE IS NO WINNER.
*/
char checkWinner(char cells[][3])
{
  // CHECK ALL COMBINATIONS TO WIN
  if (cells[0][0] == cells[0][1] && cells[0][0] == cells[0][2])
    return cells[0][0];

  if (cells[0][0] == cells[1][0] && cells[0][0] == cells[2][0])
    return cells[0][0];

  if (cells[2][2] == cells[1][2] && cells[2][2] == cells[0][2])
    return cells[2][2];

  if (cells[2][2] == cells[2][0] && cells[2][2] == cells[2][1])
    return cells[2][2];

  if (cells[1][1] == cells[0][0] && cells[1][1] == cells[2][2])
    return cells[1][1];

  if (cells[1][1] == cells[2][0] && cells[1][1] == cells[0][2])
    return cells[1][1];

  if (cells[1][1] == cells[0][1] && cells[1][1] == cells[2][1])
    return cells[1][1];

  if (cells[1][1] == cells[1][0] && cells[1][1] == cells[1][2])
    return cells[1][1];

  // CHECK IF THERE IS AT LEAST ONE FREE CELL. IF NOT, RETURN '2' (DRAW)
  int isCell = 0;
  for (int row = 0; row < 3 && isCell == 0; row++)
    for (int column = 0; column < 3 && isCell == 0; column++)
      // IF THE CURRENT CELL IS NOT X AND O THAT MEANS THAT IS NOT OCCUPIED
      if (cells[row][column] != 'X' && cells[row][column] != 'O')
        isCell = 1;

  if (!isCell)
    return 'D';

  return '\0';
}