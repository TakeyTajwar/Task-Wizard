#ifndef WIZARD_H
#define WIZARD_H

#define print_help(y, help, ...) mvwprintw(wiz_win, y, 2, help, __VA_ARGS__)

void clear_help();
void tasks_navigation_help();
void task_editor_help();

void clear_warn();
void warn_nokb(int format);

#endif
