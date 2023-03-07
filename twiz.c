#include <ncurses.h>
#include <string.h>

#include "twiz.h"
#include "keybinding.h"
#include "windows.h"
#include "wizard.h"
#include "tasks.h"

// Move Cursor Down
void cursor_next();

// Move Cursor Up
void cursor_prev();

int main()
{

	// initialise screen
	initscr();
	curs_set(1);
	start_color();
	raw();
	noecho();
	keypad(stdscr, true);

	// Init Pairs
	init_pair(1, COLOR_CYAN,   COLOR_BLACK); // Default Window
	init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Selected Window

	init_pair(3, COLOR_WHITE, COLOR_BLACK); // Default Text
	init_pair(4, COLOR_GREEN, COLOR_BLACK); // GOOD Text
	init_pair(5, COLOR_RED,   COLOR_BLACK); // BAD Text

	init_pair(6, COLOR_WHITE, COLOR_BLACK); // OK Indicator
	init_pair(7, COLOR_WHITE, COLOR_GREEN); // GOOD Indicator
	init_pair(8, COLOR_WHITE, COLOR_RED);   // BAD Indicator


	// windows
	create_task_windows();
	wattron(tasks_win, COLOR_PAIR(3));
	wattron(list_win,  COLOR_PAIR(3));
	wattron(task_win,  COLOR_PAIR(3));
	wattron(wiz_win,   COLOR_PAIR(3));
	tasks_navigation_help();

	// DB
	fetch_db();
	refresh_cursor();

	// input loop
	int ch;
	do
	{
		ch = getch();
		clear_warn();

		switch(ch)
		{

			// quitting
			case KB_QUIT:
			case AKB_QUIT:
				// save and quit
				break;

			// navigating
			case KB_NEXT:
			case AKB_NEXT:
				cursor_next();
				break;
			case KB_PREV:
			case AKB_PREV:
				cursor_prev();
				break;
			case KB_TOGGLE:
				// Toggle between Tasks & List windows
				if(sel_win == tasks_win)
				{
					select_window(list_win);
				}
				else
				{
					select_window(tasks_win);
				}
				sel_cursor_y = 2;
				break;

			// Selected Task
			case KB_DONE:
				break;
			case KB_SKIP:
				break;
			case KB_DELETE:
				break;

			// Task Editor
			case KB_ADD_NEW_TASK:
				// add task
				add_task("Title");
				list_tasks();
				break;
			case KB_EXIT_EDITOR:
				break;

			default:
				// print out the character pressed
				warn_nokb(ch);
				break;
		}
		refresh_cursor();
	}
	while (ch != KB_QUIT && ch!= AKB_QUIT);

	close_db();
	destroy_task_windows();
	refresh();
	endwin();
	return 0;
}

void cursor_next()
{
	if (sel_cursor_y < getmaxy(sel_win)-2)
	{
		++sel_cursor_y;
	}
}

void cursor_prev()
{
	if (sel_cursor_y > 2)
	{
		--sel_cursor_y;
	}
}
