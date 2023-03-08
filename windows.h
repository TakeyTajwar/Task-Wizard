#ifndef WINDOWS_H
#define WINDOWS_H

// Create a new Window
WINDOW *create_newwin(int h, int w, int starty, int startx, char title[]);

// Destroy Window
void destroy_win(WINDOW *local_win);

// Select a Window
void select_window(WINDOW *win);

// Refresh Cursor Position on selected Window
void refresh_cursor();

// Create all the task windows
void create_task_windows();

// Destroy all the task windows
void destroy_task_windows();

// Cursor Navigation
void cursor_next();
void cursor_prev();
void cursor_start();
void cursor_end();
void cursor_center();

extern int col, row;
extern WINDOW *list_win, *tasks_win, *task_win, *wiz_win;
extern WINDOW *sel_win;
extern int sel_cursor_y;

#endif
