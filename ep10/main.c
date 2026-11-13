#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "team.h"
#include "teamlist.h"

static int utf8_continuation_bytes(const char *text) {
    int count = 0;
    const unsigned char *p = (const unsigned char *)text;

    while (*p != '\0') {
        if ((*p & 0xC0) == 0x80)
            count++;
        p++;
    }
    return count;
}

static void print_header(void) {
    printf("%-3s %-15s %3s %3s %3s %3s %3s %3s %3s\n",
           "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
}

int main(void) {
    FILE *file;
    TeamList *tl = tl_create();
    char line[1024];
    int i;

    if (tl == NULL)
        return EXIT_FAILURE;

    file = fopen("teams.csv", "r");
    if (file == NULL) {
        tl_free(tl);
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char *comma;
        char *end;
        int id;
        Team *team;

        comma = strchr(line, ',');
        if (comma == NULL)
            continue;

        *comma = '\0';
        end = comma + 1;
        end[strcspn(end, "\r\n")] = '\0';
        id = atoi(line);
        team = team_create(id, end);
        if (team != NULL)
            tl_append(tl, team);
    }
    fclose(file);

    print_header();
    for (i = 0; i < tl_size(tl); i++) {
        Team *team = tl_get(tl, i);
        const char *name = team_name(team);
        int goals_scored = team_goals_scored(team);
        int goals_conceded = team_goals_conceded(team);
        int wins = team_wins(team);
        int draws = team_draws(team);
        int balance = goals_scored - goals_conceded;
        int points = 3 * wins + draws;

        printf("%-3d %-15s", team_id(team), name);
        for (int extra = 0; extra < utf8_continuation_bytes(name); extra++)
            putchar(' ');
        printf(" %3d %3d %3d %3d %3d %3d %3d\n",
               wins, draws, team_losses(team), goals_scored,
               goals_conceded, balance, points);
    }

    tl_free(tl);
    return 0;
}
