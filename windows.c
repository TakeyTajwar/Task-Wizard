#include <ncurses.h>
#include <string.h>

#include "windows.h"

WINDOW *list_win, *tasks_win, *task_win, *wiz_win;
WINDOW *sel_win = NULL;

int sel_cursor_y = 2;

WINDOW *create_newwin(int h, int w, int starty, int startx, char title[])
{
	// Create a window and put border & title on it

	// create a window
	WINDOW *local_win;
	local_win = newwin(h, w, starty, startx);

	wbkgd(local_win, COLOR_PAIR(1));

	// put a border around the window
	box(local_win, 0, 0);

	// put window title
	mvwprintw(local_win, 1, (w-strlen(title)-8)/2, "o-- %s --o", title);

	refresh();
	wrefresh(local_win);
	return(local_win);
}

void destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}

void select_window(WINDOW *win)
{
	if(sel_win != NULL)
	{
		wbkgd(sel_win, COLOR_PAIR(1));
		wrefresh(sel_win);
	}
	sel_win = win;
	wbkgd(sel_win, COLOR_PAIR(2));
	wrefresh(sel_win);
}

void refresh_cursor()
{
	// Put cursor at the centre left of the currently selected window
	wmove(sel_win, sel_cursor_y, 2);//, getmaxy(sel_win)/2, 2);
	wrefresh(sel_win);
}

void create_task_windows()
{
	int col, row;
	getmaxyx(stdscr, col, row);

	// 1st Column
	tasks_win = create_newwin(col, row*0.45, 0, 0, "TASKS");

	// 2nd Column
	list_win = create_newwin(col/3, row*0.55, 0,       row*0.45, "LIST");
	task_win = create_newwin(col/3, row*0.55, col/3,   row*0.45, "TASK");
	wiz_win  = create_newwin(col/3, row*0.55, col/3*2, row*0.45, "WIZARD");

	select_window(tasks_win);
}

void destroy_task_windows()
{
	destroy_win(list_win);
	destroy_win(tasks_win);
	destroy_win(task_win);
	destroy_win(wiz_win);
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

void cursor_start()
{
	sel_cursor_y = 2;
}

void cursor_end()
{
	sel_cursor_y = getmaxy(sel_win)-2;
}

void cursor_center()
{
	sel_cursor_y = getmaxy(sel_win)/2;
}
