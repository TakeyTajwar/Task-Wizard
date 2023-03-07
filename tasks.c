#include <time.h>
#include <sqlite3.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "tasks.h"
#include "windows.h"
#include "config.h"

// database
sqlite3* db;

// current column number
int list_col = 0;

void clear_list()
{
	for(int y=4;y<getmaxy(list_win)-2;++y)
	{
		wmove(wiz_win, y, 2);
		wclrtoeol(list_win);
	}
	wattron(list_win, COLOR_PAIR(1));
	box(list_win, 0, 0);
	wattroff(list_win, COLOR_PAIR(1));
	list_col = 0;
}

static int list_tasks_callback(void *data, int argc, char **argv, char **azColName)
{
	mvwprintw(list_win, list_col+2, 2, "%s\t%s\n",\
	argv[0] ? argv[0] : "NULL",\
	argv[1] ? "DONE" : "TODO"\
	);
	++list_col;

	return 0;
}

void list_tasks()
{
	int rc;
	char *sql;
	char *zErrMsg = 0;
	char *data;

	clear_list();

	sql = "SELECT * from TASKS";

	wattron(list_win, COLOR_PAIR(3));
	rc = sqlite3_exec(db, sql, list_tasks_callback, (void*)data, &zErrMsg);

	if (rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
	}
	wattron(list_win, COLOR_PAIR(1));
	box(list_win, 0, 0);
	wattroff(list_win, COLOR_PAIR(1));
	wrefresh(list_win);

	sqlite3_free(zErrMsg);
}

void add_task(char title[32])
{
	int rc;
	char *sql;
	char *zErrMsg = 0;

	sql = \
	"INSERT INTO TASKS (TITLE,DONE)" \
	"VALUES ( 'Shower', NULL);";

	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
	}
	sqlite3_free(zErrMsg);
}

void fetch_db()
{
	// Create Data Directory

	char path[32];
	strcpy(path, HOME);
	strcat(path, DATA_DIR);
	mkdir(path, 0700);

	// Fetch DB to memory

	strcat(path, DB_FILE);
	int rc;
	rc = sqlite3_open(path, &db);
	if (rc)
	{
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
	}

	// Create Table (if it doesn't exist) and list tasks);
	create_table();
	list_tasks();
}

void close_db()
{
	sqlite3_close(db);
}

void create_table()
{
	int rc;
	char *sql;
	char *zErrMsg = 0;

	sql = \
	"CREATE TABLE IF NOT EXISTS TASKS(" \
	"TITLE TEXT NOT NULL," \
	"DONE  INT);";

	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
	}
	sqlite3_free(zErrMsg);
}
