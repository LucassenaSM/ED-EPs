#include "teamlist.h"
#include <stdlib.h>

// TeamList implemented with a DOUBLY LINKED LIST.

struct node {
    Team *team;
    struct node *next;
    struct node *prev;
};

struct teamlist {
    struct node *first;
    struct node *last;
    int size;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(*tl));

    if (tl == NULL)
        return NULL;

    tl->first = NULL;
    tl->last = NULL;
    tl->size = 0;
    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    struct node *new_node;

    if (tl == NULL)
        return;

    new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        team_free(t);
        return;
    }

    new_node->team = t;
    new_node->next = NULL;
    new_node->prev = tl->last;

    if (tl->last != NULL)
        tl->last->next = new_node;
    else
        tl->first = new_node;

    tl->last = new_node;
    tl->size++;
}

int tl_size(TeamList *tl) {
    return tl != NULL ? tl->size : 0;
}

Team *tl_get(TeamList *tl, int i) {
    struct node *current;
    int position;

    if (tl == NULL || i < 0 || i >= tl->size)
        return NULL;

    current = tl->first;
    for (position = 0; position < i; position++)
        current = current->next;

    return current->team;
}

void tl_free(TeamList *tl) {
    struct node *current;
    struct node *next;

    if (tl == NULL)
        return;

    current = tl->first;
    while (current != NULL) {
        next = current->next;
        team_free(current->team);
        free(current);
        current = next;
    }
    free(tl);
}
