#include "team.h"
#include <stdlib.h>
#include <string.h>

struct team {
    int id;
    char *name;
    int wins;
    int draws;
    int losses;
    int goals_scored;
    int goals_conceded;
};

Team *team_create(int id, const char *name) {
    Team *t;
    size_t name_length;

    if (name == NULL)
        return NULL;

    t = malloc(sizeof(*t));
    if (t == NULL)
        return NULL;

    name_length = strlen(name);
    t->name = malloc(name_length + 1);
    if (t->name == NULL) {
        free(t);
        return NULL;
    }

    memcpy(t->name, name, name_length + 1);
    t->id = id;
    t->wins = 0;
    t->draws = 0;
    t->losses = 0;
    t->goals_scored = 0;
    t->goals_conceded = 0;

    return t;
}

int team_id(Team *t) {
    return t != NULL ? t->id : 0;
}

const char *team_name(Team *t) {
    return t != NULL ? t->name : NULL;
}

int team_wins(Team *t) {
    return t != NULL ? t->wins : 0;
}

int team_draws(Team *t) {
    return t != NULL ? t->draws : 0;
}

int team_losses(Team *t) {
    return t != NULL ? t->losses : 0;
}

int team_goals_scored(Team *t) {
    return t != NULL ? t->goals_scored : 0;
}

int team_goals_conceded(Team *t) {
    return t != NULL ? t->goals_conceded : 0;
}

void team_free(Team *t) {
    if (t == NULL)
        return;

    free(t->name);
    free(t);
}
