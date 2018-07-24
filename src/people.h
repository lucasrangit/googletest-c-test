struct person {
    char *name;
    struct person *next;
    struct person *previous;
};

  
struct person *person_add(const char *name);
void person_destroy(struct person *person);
void person_remove(const char *name);
bool person_exists(const char *name);
int people_count(void);