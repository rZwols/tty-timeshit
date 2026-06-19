
#ifndef TIMESHIT_H_INCLUDED
#define TIMESHIT_H_INCLUDED

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <ncurses.h>
#include <unistd.h>

/* prototypes */
void init();
void cleanup();
void refresh_current_time();

/* global variables */
FILE *database;
struct tm *birthdate;
struct tm *currentTime;
int running;

#endif /* TIMESHIT_H_INCLUDED */
