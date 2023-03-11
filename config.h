#ifndef CONFIG_H
#define CONFIG_H

// Paths

#define HOME		getenv("HOME")
#define DATA_DIR	"/.local/share/Twiz/"
#define DB_FILE		"Task_Wizard.db"

// Date Time

#define DATE_SEP	'-'
#define TIME_SEP	':'

// Recurring Factors
#define DAILY		'd'
#define WEEKLY		'w'
#define MONTHLY		'm'
#define YEARLY		'y'

#endif
