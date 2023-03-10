#include <ncurses.h>

#include "wizard.h"
#include "windows.h"
#include "keybinding.h"
#include "config.h"

void clear_help()
{
	for(int y=4;y<getmaxy(wiz_win)-5;++y)
	{
		wmove(wiz_win, y, 2);
		wclrtoeol(wiz_win);
	}
	wattron(wiz_win, COLOR_PAIR(1));
	box(wiz_win, 0, 0);
	wattroff(wiz_win, COLOR_PAIR(1));
}

void tasks_navigation_help()
{
	clear_help();

	wattron(wiz_win,   COLOR_PAIR(3));
	print_help(3, "%c or %c to go to the next line", KB_NEXT, AKB_NEXT);
	print_help(4, "%c or %c to go to the previous line", KB_PREV, AKB_PREV);
	print_help(5, "%c or %c to quit", KB_QUIT, AKB_QUIT);
	print_help(6, "%c to go to the start of the window", KB_START);
	print_help(7, "%c to go to the end of the window", KB_END);
	print_help(8, "%c to go to the center of the window", KB_CENTER);
	print_help(9, "%c to switch between windows", KB_WSWITCH);
	print_help(10, "%c to add a new task", KB_ADD_NEW_TASK);
	print_help(11, "%c to mark the task done", KB_DONE);
	print_help(12, "%c to skip the task", KB_SKIP);
	print_help(13, "%c to delete the task", KB_DELETE);

	wrefresh(wiz_win);
}

void create_task_help()
{
	clear_help();
	wattron(wiz_win,   COLOR_PAIR(3));
	print_help(3, "Enter Title, Date, Time, etc to create a new Task", 0);
	print_help(4, "Date should be in YYYY%cMM%cDD format. Leave it blank to use current date.", DATE_SEP, DATE_SEP);
	print_help(5, "Time should be in HH%cMM format and in 24h.", TIME_SEP);

	print_help(7, "Use number followed by %c/%c/%c/%c for task recursion rate.", DAILY, WEEKLY, MONTHLY, YEARLY);
	print_help(8, "'1%c' will recur a task every week", WEEKLY);


	print_help(10, "Use weekday filter to recur tasks only certain days of the week.", 0);
	print_help(11, "Filtered date should be in YYYY/MM/DD format with one or more number being replaced by *.", 0);

	wrefresh(wiz_win);
}

void clear_warn()
{
	wmove(wiz_win, getmaxy(wiz_win)-4, 2);
	wclrtoeol(wiz_win);
	wmove(wiz_win, getmaxy(wiz_win)-3, 2);
	wclrtoeol(wiz_win);
	wattron(wiz_win, COLOR_PAIR(1));
	box(wiz_win, 0, 0);
	wattroff(wiz_win, COLOR_PAIR(1));
	wrefresh(wiz_win);
}

void warn_nokb(int format)
{
	clear_warn();
	wattron(wiz_win,   COLOR_PAIR(5));
	print_help(getmaxy(wiz_win)-4, "No keybinding for %c", format);
	wattroff(wiz_win,   COLOR_PAIR(5));
	wrefresh(wiz_win);
}
