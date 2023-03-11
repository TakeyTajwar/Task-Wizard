#include <ncurses.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "task_editor.h"
#include "windows.h"
#include "tasks.h"
#include "config.h"

void clear_task()
{
	for(int y=2;y<getmaxy(task_win)-1;++y)
	{
		wmove(task_win, y, 2);
		wclrtoeol(task_win);
	}
	wattron(task_win, COLOR_PAIR(1));
	box(task_win, 0, 0);
	wattroff(task_win, COLOR_PAIR(1));
}

void create_task()
{
	char title[65];
	char date[11];
	char daytime[6];

	bool recur = false;
	int recur_amount = 0; // Number
	char recur_factor = 0; // Day, Week, Month, year

	bool filter = false;
	char filter_weekdays[8];
	char filter_date[11];

	int ch;
	char num[33];

	// Get Previously Selected Window and Select Task Editor Window

	WINDOW *prev_win = sel_win;
	clear_task();
	select_window(task_win);

	// Create UI

	wattron(task_win,  COLOR_PAIR(3));

	// General task information
	print_ui(2, "Title");
	print_ui(3, "Date");
	print_ui(4, "Time");
	
	// Whether the task is recurring
	print_cb(6, "Recur");

	// Get Input

	echo();

	// Title
	get_ui(2, 64, title);

	// Date
	do
	{
		get_ui(3, 10,  date);

		// Use current date if it's blank
		if(strlen(date)==0)
		{
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			snprintf(date, 11, "%04d-%02d-%2d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
		}
	}
	while	(!eval_date(date));

	// Time
	do	get_ui(4,  5,  daytime);
	while	(!eval_time(daytime));

	// Recurring
	get_cb(6, ch, recur);

	if(recur)
	{
		// UI

		// Recurring Task Information
		print_ui(7, "Amount");

		// Filtering
		print_cb(9, "Filter");

		// Get Input

		// Recurring Amount
		do
		{
			get_ui(7, 33, num);
			sscanf(num, "%i%c", &recur_amount, &recur_factor);
		}
		while (!(recur_factor == DAILY || recur_factor == WEEKLY || recur_factor == MONTHLY || recur_factor == YEARLY));

		// Filter
		get_cb(9, ch, filter);

		if(filter)
		{
			// UI

			// Filter Task Information
			print_ui(10, "Weekdays");
			print_ui(11, "Date");

			// Get Input

			// Filter Weekdays
			do	get_ui(10, 7, filter_weekdays);
			while	(!eval_filter_weekdays(filter_weekdays));

			// Filter Date
			do	get_ui(11, 10, filter_date);
			while	(!eval_date_filter(filter_date));
		}
	}

	// Add the Task and Select Previously Selected Window

	noecho();
	add_task(title, date, daytime);
	select_window(prev_win);
}

int eval_date(char date[11])
{
	// YYYY-MM-DD

	if(!isdigit(date[0])) return 0;
	if(!isdigit(date[1])) return 0;
	if(!isdigit(date[2])) return 0;
	if(!isdigit(date[3])) return 0;

	if((date[4] != DATE_SEP)) return 0;

	if(!isdigit(date[5])) return 0;
	if(!isdigit(date[6])) return 0;

	if((date[7] != DATE_SEP)) return 0;

	if(!isdigit(date[8])) return 0;
	if(!isdigit(date[9])) return 0;

	return 1;
}

int eval_time(char time[6])
{
	// HH:MM

	if(!isdigit(time[0])) return 0;
	if(!isdigit(time[1])) return 0;

	if((time[2] != TIME_SEP)) return 0;

	if(!isdigit(time[3])) return 0;
	if(!isdigit(time[4])) return 0;

	return 1;
}

int eval_filter_weekdays(char filter_weekdays[8])
{
	// 0123456 each number should be larger than the one before

	char last = -1;

	for(int i=0; i<strlen(filter_weekdays); ++i)
	{
		if(!isdigit(filter_weekdays[i])) return 0;
		if(!(filter_weekdays[i] > last)) return 0;
		last = filter_weekdays[i];
	}

	return 1;
}

int eval_date_filter(char date_filter[11])
{
	// YYYY-MM-DD with one or more Y/M/D being replaced with *

	// A blank will do
	if(strlen(date_filter)==0) return 1;

	// Needs at least one digit and one '*'
	{
		int asterisk_count;
		int num_count;
		for(int i=0; i<strlen(date_filter); ++i)
		{
			if	(date_filter[i] == '*') ++asterisk_count;
			else if	(isdigit(date_filter[i])) ++num_count;
		}
		if(!asterisk_count || !num_count) return 0;
	}

	if(!isdigit(date_filter[0]) && date_filter[0] != '*') return 0;
	if(!isdigit(date_filter[1]) && date_filter[1] != '*') return 0;
	if(!isdigit(date_filter[2]) && date_filter[2] != '*') return 0;
	if(!isdigit(date_filter[3]) && date_filter[3] != '*') return 0;

	if((date_filter[4] != DATE_SEP)) return 0;

	if(!isdigit(date_filter[5]) && date_filter[5] != '*') return 0;
	if(!isdigit(date_filter[6]) && date_filter[6] != '*') return 0;

	if((date_filter[7] != DATE_SEP)) return 0;

	if(!isdigit(date_filter[8]) && date_filter[8] != '*') return 0;
	if(!isdigit(date_filter[9]) && date_filter[9] != '*') return 0;

}
