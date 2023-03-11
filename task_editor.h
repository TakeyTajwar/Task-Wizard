#ifndef TASK_EDITOR_H
#define TASK_EDITOR_H

// Clear Task Editor Window
void clear_task();

// Show Information about the task
void info_task(char title[64]);

// Open Task in Task Editor
void edit_task(char title[64]);

// Open Task Editor to create a new task
void create_task();

// Evaluate Date string
int eval_date(char date[11]);

// Evaluate Time string
int eval_time(char time[6]);

// Evaluate Filter_Weekday string
int eval_filter_weekdays(char filter_weekdays[8]);

// Evaluate Date Filter string
int eval_date_filter(char date_filter[11]);

// Print UI element
#define print_ui(y, name) mvwprintw(task_win, y, 2, "%-7s : ", name)
#define print_cb(y, name) mvwprintw(task_win, y, 2, "%-7s : [ ] (Y/n)", name)

// Get Input
#define get_ui(y, n, str) mvwgetnstr(task_win, y, 12, str, n)
#define get_cb(y, ch, var)\
{\
	do	ch = mvwgetch(task_win, y, 13);\
	while	(!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));\
	switch (ch)\
	{\
		case 'Y':\
		case 'y':\
			var = true;\
			break;\
	}\
}

#endif
