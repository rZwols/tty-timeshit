#include "timeshit.h"

void init() {
    initscr();
    return;
}

void cleanup() {
    return;
}

int main (int argc, char **argv) {

    atexit(cleanup);

    FILE *data;
    int c;
    while ((c = getopt(argc, argv, "hs:")) != -1) {
        switch (c) {
        case 'h':
            printf(
                "usage:                         \n"
                "   -h      shows this message  \n"
                "   -s      set your birthday   \n"
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
            data = fopen("database.txt", "w");
            if (data == NULL) {
                perror("database.txt");
                exit(EXIT_FAILURE);
            }
            fprintf(data, "%d/%d/%d", year, month, day);
            exit(EXIT_SUCCESS);
            break;
        default:

            break;
        }
    }

    init();

    getch();

    endwin();
}