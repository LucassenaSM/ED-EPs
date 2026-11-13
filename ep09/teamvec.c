#include "teamvec.h"
#include <stdlib.h>

struct teamvec {
    Team **teams;
    int capacity;
    int size;
};

TeamVec *tv_create(void) {
    TeamVec *tv = malloc(sizeof(*tv));

    if (tv == NULL)
        return NULL;

    tv->capacity = 4;
    tv->size = 0;
    tv->teams = malloc((size_t)tv->capacity * sizeof(*tv->teams));
    if (tv->teams == NULL) {
        free(tv);
        return NULL;
    }

    return tv;
}

void tv_insert(TeamVec *tv, Team *t) {
    Team **new_teams;

    if (tv == NULL)
        return;

    if (tv->size == tv->capacity) {
        new_teams = realloc(tv->teams,
                            (size_t)(tv->capacity * 2) * sizeof(*tv->teams));
        if (new_teams == NULL)
            return;

        tv->teams = new_teams;
        tv->capacity *= 2;
    }

    tv->teams[tv->size] = t;
    tv->size++;
}

int tv_size(TeamVec *tv) {
    return tv != NULL ? tv->size : 0;
}

Team *tv_get(TeamVec *tv, int i) {
    if (tv == NULL || i < 0 || i >= tv->size)
        return NULL;

    return tv->teams[i];
}

void tv_free(TeamVec *tv) {
    int i;

    if (tv == NULL)
        return;

    for (i = 0; i < tv->size; i++)
        team_free(tv->teams[i]);

    free(tv->teams);
    free(tv);
}
