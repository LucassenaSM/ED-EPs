#include "teamlist.h"
#include <stdlib.h>

// TeamList implemented with a DYNAMIC VECTOR.

struct teamlist {
    Team **teams;
    int size;
    int capacity;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(*tl));

    if (tl == NULL)
        return NULL;

    tl->capacity = 4;
    tl->size = 0;
    tl->teams = malloc((size_t)tl->capacity * sizeof(*tl->teams));
    if (tl->teams == NULL) {
        free(tl);
        return NULL;
    }

    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    Team **new_teams;

    if (tl == NULL)
        return;

    if (tl->size == tl->capacity) {
        tl->capacity *= 2;
        new_teams = realloc(tl->teams,
                            (size_t)tl->capacity * sizeof(*tl->teams));
        if (new_teams == NULL) {
            tl->capacity /= 2;
            team_free(t);
            return;
        }
        tl->teams = new_teams;
    }

    tl->teams[tl->size] = t;
    tl->size++;
}

int tl_size(TeamList *tl) {
    return tl != NULL ? tl->size : 0;
}

Team *tl_get(TeamList *tl, int i) {
    if (tl == NULL || i < 0 || i >= tl->size)
        return NULL;

    return tl->teams[i];
}

void tl_free(TeamList *tl) {
    int i;

    if (tl == NULL)
        return;

    for (i = 0; i < tl->size; i++)
        team_free(tl->teams[i]);
    free(tl->teams);
    free(tl);
}
