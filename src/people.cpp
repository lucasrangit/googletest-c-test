#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "people.h"

struct people {
    struct person *head;
    int count;
};

static struct people people = { NULL, 0 };

struct person *person_add(const char *name)
{
    struct person *person;
 
    /* Allocate memory for the person structure. */
    person = (struct person*)malloc(sizeof *person);
    assert(person != NULL);
 
    /* Allocate a copy of the name. */
    person->name = strdup(name);
    assert(person->name != NULL);
 
    /* Make person the new head */
    person->previous = NULL;
    person->next = people.head;
    if (person->next != NULL)
        person->next->previous = person;
    people.head = person;
 
    people.count++;

    return person;
}

void person_destroy(struct person *person)
{
    if (person != people.head && 
        person->next == NULL && person->previous == NULL)
        return;

    /* Update head */
    if (person == people.head)
        people.head = person->next;

    /* Unlink person from list */
    if (person->previous != NULL)
        person->previous->next = person->next;

    if (person->next != NULL)
        person->next->previous = person->previous;

    person->next = 0;
    person->previous = 0;

    /* Release memory. */
    free(person);

    people.count--;

    return;
}

void person_remove(const char *name)
{
    struct person *cursor;
 
    for (cursor = people.head; cursor != NULL; cursor = cursor->next) {
        if (strcmp(cursor->name, name) == 0) {
            person_destroy(cursor);
            break;
        }
    }
} 

bool person_exists(const char *name)
{
    struct person *cursor;
 
    for (cursor = people.head; cursor != NULL; cursor = cursor->next) {
        if (strcmp(cursor->name, name) == 0)
            return true;
    }
 
    return false;                      
}

int people_count(void)
{
    return people.count;
}
