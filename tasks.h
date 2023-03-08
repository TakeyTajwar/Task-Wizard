#ifndef TASKS_H
#define TASKS_H

// Clear the characters on Task List window
void clear_list();

// List tasks on Task List window
void list_tasks();

// Add a new task to DB
void add_task(char title[64], char date[10], char time[5]);

// Create* Data Directory & Fetch DB to memory
void fetch_db();

// Clsoe DB from memory
void close_db();

// Create Data Table
void create_tables();

#endif