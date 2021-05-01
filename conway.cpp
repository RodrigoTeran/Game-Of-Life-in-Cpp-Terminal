#include <iostream>
#include <conio.h> // getch()
#include <list>
#include <Windows.h>
#include <iterator>
#include <algorithm>
#include <stdlib.h> // system("cls");
#include <ctime>    // srand(time(0));

using namespace std;

// CONSTANTS
const int WIDTH_WINDOW = 40;
const int HEIGHT_WINDOW = 40;

int TIME = 10;

string ICON_ALIVE = "0";
string ICON_DEATH = ".";
string ICON_TRANSITION = "+";

bool WITH_TRANSITIONS = false;

string cells[HEIGHT_WINDOW][WIDTH_WINDOW];
int cells_transition[HEIGHT_WINDOW][WIDTH_WINDOW];

void evolve_cells()
{
  string aux_cells[HEIGHT_WINDOW][WIDTH_WINDOW];
  int aux_cells_transition[HEIGHT_WINDOW][WIDTH_WINDOW];

  for (int y = 0; y < HEIGHT_WINDOW; y++)
  {
    string row[WIDTH_WINDOW];
    int row_transition[WIDTH_WINDOW];

    for (int x = 0; x < WIDTH_WINDOW; x++)
    {
      int live_neighbors = 0;
      int number_x_1 = -1;
      int number_x_2 = 2;

      int number_y_1 = -1;
      int number_y_2 = 2;

      if (x == 0)
      {
        // dont - in x
        number_x_1 = 0;
      }
      else if (x == WIDTH_WINDOW - 1)
      {
        // # dont + in x
        number_x_2 = 1;
      };

      if (y == 0)
      {
        // dont - in y
        number_y_1 = 0;
      }
      else if (y == HEIGHT_WINDOW - 1)
      {
        // dont + in y
        number_y_2 = 1;
      };

      for (int i = number_y_1; i < number_y_2; i++) // y
      {
        for (int j = number_x_1; j < number_x_2; j++) // x
        {
          // check that is not myself
          if (i == 0 && j == 0)
          {
            continue;
          };
          // neighbors
          string value = cells[y + i][x + j];
          if (value == ICON_ALIVE)
          {
            live_neighbors += 1;
          };
        };
      };

      string value = cells[y][x];
      if (value == ICON_ALIVE)
      {
        // im alive right now
        if (live_neighbors < 2)
        {
          row[x] = ICON_DEATH;
          row_transition[x] = 1;
        }
        else if (live_neighbors == 2 || live_neighbors == 3)
        {
          row[x] = ICON_ALIVE;
          row_transition[x] = 0;
        }
        else if (live_neighbors > 3)
        {
          row[x] = ICON_DEATH;
          row_transition[x] = 1;
        }
      }
      else
      {
        // im dead right now
        if (live_neighbors == 3)
        {
          row[x] = ICON_ALIVE;
          row_transition[x] = 1;
        }
        else
        {
          row[x] = ICON_DEATH;
          row_transition[x] = 0;
        };
      };
    };
    // Aux
    for (int iRow = 0; iRow < WIDTH_WINDOW; iRow++)
    {
      aux_cells[y][iRow] = row[iRow];
      aux_cells_transition[y][iRow] = row_transition[iRow];
    };
  };
  for (int iColumn = 0; iColumn < HEIGHT_WINDOW; iColumn++)
  {
    for (int iRow = 0; iRow < WIDTH_WINDOW; iRow++)
    {
      cells[iColumn][iRow] = aux_cells[iColumn][iRow];
      cells_transition[iColumn][iRow] = aux_cells_transition[iColumn][iRow];
    };
  };
};

void drawCells()
{
  while (true)
  {
    system("cls");
    for (int y = 0; y < HEIGHT_WINDOW; y++)
    {
      string text_row = "";
      for (int x = 0; x < WIDTH_WINDOW; x++)
      {
        if (WITH_TRANSITIONS)
        {
          int value = cells_transition[y][x];
          if (value == 1)
          {
            text_row = text_row + " " + ICON_TRANSITION;
          }
          else
          {
            string valueString = cells[y][x];
            text_row = text_row + " " + valueString;
          };
        }
        else
        {
          string value = cells[y][x];
          text_row = text_row + " " + value;
        };
      };
      cout << text_row << endl;
    };
    evolve_cells();
    Sleep(TIME);
  };
};

void populate_window()
{
  for (int y = 0; y < HEIGHT_WINDOW; y++)
  {
    string row[WIDTH_WINDOW];
    int row_transition[WIDTH_WINDOW];
    for (int x = 0; x < WIDTH_WINDOW; x++)
    {
      int choice = rand() % 2;
      if (choice == 1)
      {
        row[x] = ICON_ALIVE;
      }
      else
      {
        row[x] = ICON_DEATH;
      };
      row_transition[x] = 0;
    };
    for (int iRow = 0; iRow < WIDTH_WINDOW; iRow++)
    {
      cells[y][iRow] = row[iRow];
      cells_transition[y][iRow] = row_transition[iRow];
    };
  };
};

int main()
{
  srand(time(0));
  populate_window();
  drawCells();
  getch();
  return 0;
};
