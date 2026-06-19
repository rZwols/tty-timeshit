#include "timeshit.h"

void init() {
    /* initialize birthdate */
    database = fopen("database.txt", "r");
    if (database == NULL) {
        perror( "add your birthday with:        \n"
                "   timeshit -s [yyyy/mm/dd]    \n");
        exit(EXIT_FAILURE);
    }
    birthdate = malloc(sizeof(struct tm));
    int year;
    int month;
    int day;
    fscanf(database, "%d/%d/%d", &year, &month, &day);
    birthdate->tm_year = year-1900;
    birthdate->tm_mon = month-1;
    birthdate->tm_mday = day;
    /* */
    initscr();
    return;
}

void cleanup() {
    free(birthdate);
    return;
}

void refresh_current_time() {
    time_t rawCurrentTime = time(NULL);
    currentTime = gmtime(&rawCurrentTime);
}

int main (int argc, char **argv) {

    atexit(cleanup);

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
                perror("database.txt");
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
        printw("you were born in %d/%d/%d\n", 
            birthdate->tm_year+1900, birthdate->tm_mon+1, birthdate->tm_mday);
        printw("now: %d/%d/%d %d:%d:%d\n", 
            currentTime->tm_year+1900, currentTime->tm_mon+1, currentTime->tm_mday,
            currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
        refresh();
        sleep(1);
    }

    endwin();
}
