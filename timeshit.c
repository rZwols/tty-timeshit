#include "timeshit.h"

void init() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    refresh_current_time();
    /* initialize birthdate */
    database = fopen("database.txt", "r");
    if (database == NULL) {
        perror( "add your birthday with:        \n"
                "   timeshit -s [yyyy/mm/dd]    \n");
        exit(EXIT_FAILURE);
    }
    int year;
    int month;
    int day;
    fscanf(database, "%d/%d/%d", &year, &month, &day);
    birthdate = malloc(sizeof(struct tm));
    *birthdate = emptyDate;
    birthdate->tm_year = year-1900;
    birthdate->tm_mon = month-1;
    birthdate->tm_mday = day;
    /* initialize endYear */
    endYear = malloc(sizeof(struct tm));
    *endYear = emptyDate;
    endYear->tm_year = currentTime->tm_year+1;
    return;
}

void cleanup() {
    free(birthdate);
    free(endYear);
    return;
}

void refresh_current_time() {
    time_t rawCurrentTime = time(NULL);
    currentTime = gmtime(&rawCurrentTime);
}

void renderscr() {    
    time_t rawCurrentTime = mktime(currentTime);
    time_t rawBirthdate = mktime(birthdate);
    time_t rawEndYear = mktime(endYear);

    double lifetime = difftime(rawCurrentTime, rawBirthdate);

    int totWeeks = lifetime / (7 * DAY_TO_SECOND_RATIO);

    int years = lifetime / YEAR_TO_SECOND_RATIO;
    lifetime -= years * YEAR_TO_SECOND_RATIO;
    int days = lifetime / DAY_TO_SECOND_RATIO;
    lifetime -= days * DAY_TO_SECOND_RATIO;
    int hours = lifetime / HOUR_TO_SECOND_RATIO;
    lifetime -= hours * HOUR_TO_SECOND_RATIO;
    int minutes = lifetime / MINUTE_TO_SECOND_RATIO;
    lifetime -= minutes * MINUTE_TO_SECOND_RATIO;
    int seconds = lifetime;

    int daysUntilEndYear = 1 + difftime(rawEndYear, rawCurrentTime) / DAY_TO_SECOND_RATIO;

    printw("now: %04d/%02d/%02d %02d:%02d:%02d\n", 
        currentTime->tm_year+1900, currentTime->tm_mon+1, currentTime->tm_mday,
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
    printw("you were born in %04d/%02d/%02d\n", 
        birthdate->tm_year+1900, birthdate->tm_mon+1, birthdate->tm_mday);
    printw("humans live on average 4000 weeks, you've already lived %d of yours\n",
        totWeeks);
    printw("days until the end of this year: %d\n", 
        daysUntilEndYear);
    printw("you're currently %dy, %dd, %02dh, %02dm, %02ds old\n", 
        years, days, hours, minutes, seconds);
}

int main (int argc, char **argv) {

    atexit(cleanup);

    struct timespec ts = {
        .tv_sec = 0,
        .tv_nsec = 500000000
    };
    
    int c;
    while ((c = getopt(argc, argv, "hs:")) != -1) {
        switch (c) {
        case 'h':
            printf(
                "usage:                                     \n"
                "   -h                  shows this message  \n"
                "   -s [yyyy/mm/dd]     set your birthday   \n"
            );
            exit(EXIT_SUCCESS);
            break;
        case 's':
            int year;
            int month;
            int day;
            if (3 != sscanf(optarg, "%d/%d/%d", &year, &month, &day)) {
                exit(EXIT_FAILURE);
            }
            database = fopen("database.txt", "w");
            if (database == NULL) {
                perror( "add your birthday with:        \n"
                        "   timeshit -s [yyyy/mm/dd]    \n");
                exit(EXIT_FAILURE);
            }
            fprintf(database, "%d/%d/%d", year, month, day);
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }

    init();

    running = 1;
    while (running) {
        refresh_current_time();
        clear();
        renderscr();
        refresh();
        nanosleep(&ts, NULL);
        if (getch() == 'q') running = 0;
    }

    endwin();
}
