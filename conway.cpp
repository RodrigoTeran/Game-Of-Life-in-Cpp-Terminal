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
int WIDTH_WINDOW = 40;
int HEIGHT_WINDOW = 20;

int TIME = 1;

string ICON_ALIVE = "0";
string ICON_DEATH = ".";
string ICON_TRANSITION = "+";

bool WITH_TRANSITIONS = false;

list<list<string> > cells;
list<list<int> > cells_transition;


void showList(list<list<string> > nested_list)
{
  cout << "[\n";

  // nested_list`s iterator(same type as nested_list)
  // to iterate the nested_list
  list<list<string> >::iterator nested_list_itr;

  // Print the nested_list
  for (nested_list_itr = nested_list.begin();
       nested_list_itr != nested_list.end();
       ++nested_list_itr)
  {

    cout << "  [";

    // normal_list`s iterator(same type as temp_list)
    // to iterate the normal_list
    list<string>::iterator single_list_itr;

    // pointer of each list one by one in nested list
    // as loop goes on
    list<string> &single_list_pointer = *nested_list_itr;

    for (single_list_itr = single_list_pointer.begin();
         single_list_itr != single_list_pointer.end();
         single_list_itr++)
    {
      cout << " " << *single_list_itr << " ";
    }
    cout << "]\n";
  }
  cout << "]";
}

int returnYXValueInt (list<list<int> > cells_transition_list, int y, int x){
  list<list<int> >::iterator itrCellsRows = cells_transition_list.begin();
  advance(itrCellsRows, y);

  list<int> &single_list_pointer = *itrCellsRows;

  list<int>::iterator itrCellsColumns = single_list_pointer.begin();

  advance(itrCellsColumns, x);
  return *itrCellsColumns;
};

string returnYXValueString (list<list<string> > cells_transition_list, int y, int x){
  list<list<string> >::iterator itrCellsRows = cells_transition_list.begin();
  advance(itrCellsRows, y);

  list<string> &single_list_pointer = *itrCellsRows;

  list<string>::iterator itrCellsColumns = single_list_pointer.begin();

  advance(itrCellsColumns, x);
  return *itrCellsColumns;
};

void evolve_cells(){
  list<list<string> > aux_cells;
  list<list<int> > aux_cells_transition;
  for (int y = 0; y < HEIGHT_WINDOW; y++)
  {
    list<string> row;
    list<int> row_transition;
    for (int x = 0; x < WIDTH_WINDOW; x++)
    {
      int live_neighbors = 0;
      int number_x_1 = -1;
      int number_x_2 = 2;

      int number_y_1 = -1;
      int number_y_2 = 2;

      if (x == 0){
        // dont - in x
        number_x_1 = 0;
      } else if (x == WIDTH_WINDOW - 1){
        // # dont + in x
        number_x_2 = 1;
      };

       if (y == 0){
        // dont - in y
        number_y_1 = 0;
      } else if (y == HEIGHT_WINDOW - 1){
        // dont + in y
        number_y_2 = 1;
      };

      for (int i = number_y_1; i < number_y_2; i++) // y
      {
        for (int j = number_x_1; j < number_x_2; j++) // x
        {
          // check that is not myself
          if (i == 0 && j == 0) {
            continue;
          };
          // neighbors
          string value = returnYXValueString(cells, y + i, x + j);
          if (value == ICON_ALIVE){
            live_neighbors += 1;
          };
        };
      };

      string value = returnYXValueString(cells, y, x);
      if (value == ICON_ALIVE) {
        // im alive right now
        if(live_neighbors < 2){
          row.push_back(ICON_DEATH);
          row_transition.push_back(1);

        } else if(live_neighbors == 2 || live_neighbors == 3){
          row.push_back(ICON_ALIVE);
          row_transition.push_back(0);

        } else if(live_neighbors > 3){
          row.push_back(ICON_DEATH);
          row_transition.push_back(1);
        }
      } else {
        // im dead right now
        if(live_neighbors == 3){
          row.push_back(ICON_ALIVE);
          row_transition.push_back(1);

        } else {
          row.push_back(ICON_DEATH);
          row_transition.push_back(0);

        };
      };
    };
    // Aux
    aux_cells.push_back(row);
    aux_cells_transition.push_back(row_transition);
  };
  cells = aux_cells;
  cells_transition = aux_cells_transition;
};

void drawCells()
{
  // showList(cells);
  while (true) {
    system("cls");
    for (int y = 0; y < HEIGHT_WINDOW; y++){
      string text_row = "";
      for (int x = 0; x < WIDTH_WINDOW; x++){
        if (WITH_TRANSITIONS){
          int value = returnYXValueInt(cells_transition, y, x);
          if(value == 1){
            text_row = text_row + " " + ICON_TRANSITION;  
          } else {
            string valueString = returnYXValueString(cells, y, x);
            text_row = text_row + " " + valueString;
          };
        } else {
          string value = returnYXValueString(cells, y, x);
          text_row = text_row + " " + value;
        };
      };
      cout << text_row << endl;
    };
    evolve_cells();
    // Sleep(TIME);
  };
};

void populate_window()
{
  for (int y = 0; y < HEIGHT_WINDOW; y++)
  {
    list<string> row;
    list<int> row_transition;
    for (int x = 0; x < WIDTH_WINDOW; x++)
    {
      int choice = rand() % 2;
      if (choice == 1)
      {
        row.push_back(ICON_ALIVE);
      }
      else
      {
        row.push_back(ICON_DEATH);
      };
      row_transition.push_back(0);
    };
    cells.push_back(row);
    cells_transition.push_back(row_transition);
  };
};

int main()
{
  populate_window();
  drawCells();
  getch();
  return 0;
};
