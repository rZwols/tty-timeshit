
#ifndef TIMESHIT_H_INCLUDED
#define TIMESHIT_H_INCLUDED

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <ncurses.h>
#include <unistd.h>

/* macros */
#define MINUTE_TO_SECOND_RATIO  (60)
#define HOUR_TO_SECOND_RATIO    (60*60)
#define DAY_TO_SECOND_RATIO     (60*60*24)
#define YEAR_TO_SECOND_RATIO    (60*60*24*356)

/* prototypes */
void init();
void cleanup();
void refresh_current_time();
void renderscr();

/* global variables */
FILE *database;
const struct tm emptyDate = {
    .tm_year = 1900,
    .tm_mon = 0,
    .tm_mday = 1,
    .tm_hour = 0,
    .tm_min = 0,
    .tm_sec = 0,
};
struct tm *birthdate;
struct tm *currentTime;
struct tm *endYear;
int running;

#endif /* TIMESHIT_H_INCLUDED */
