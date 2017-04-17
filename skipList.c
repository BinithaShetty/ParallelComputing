#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
 
#define SL_MAX_DEPTH 6
 
typedef struct snode {
    int key;
    int value;
    struct snode **forward;
} snode;
 
typedef struct skiplist {
    int level;
    int size;
    struct snode *header;
} skiplist;
 
skiplist *skiplist_init(skiplist *list) {
    int i;
    snode *header = (snode *) malloc(sizeof(struct snode));
    list->header = header;
    header->key = INT_MAX;
    header->forward = (snode **) malloc(
            sizeof(snode*) * (SL_MAX_DEPTH + 1));
    for (i = 0; i <= SL_MAX_DEPTH; i++) {
        header->forward[i] = list->header;
    }
 
    list->level = 1;
    list->size = 0;
 
    return list;
}
 
static int rand_level() {
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < SL_MAX_DEPTH)
        level++;
    return level;
}
 
int skiplist_insert(skiplist *list, int key, int value) {
    snode *update[SL_MAX_DEPTH + 1];
    snode *x = list->header;
    int i, level;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }
    x = x->forward[1];
 
    if (key == x->key) {
        x->value = value;
        return 0;
    } else {
        level = rand_level();
        if (level > list->level) {
            for (i = list->level + 1; i <= level; i++) {
                update[i] = list->header;
            }
            list->level = level;
        }
 
        x = (snode *) malloc(sizeof(snode));
        x->key = key;
        x->value = value;
        x->forward = (snode **) malloc(sizeof(snode*) * (level + 1));
        for (i = 1; i <= level; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
    return 0;
}
 
snode *skiplist_search(skiplist *list, int key) {
    snode *x = list->header;
    int i;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
    }
    if (x->forward[1]->key == key) {
        return x->forward[1];
    } else {
        return NULL;
    }
    return NULL;
}
 
static void skiplist_node_free(snode *x) {
    if (x) {
        free(x->forward);
        free(x);
    }
}

static void skiplist_print(skiplist *list) {
    snode *x = list->header;
    while (x && x->forward[1] != list->header) {
        printf("%d[%d]->", x->forward[1]->key, x->forward[1]->value);
        x = x->forward[1];
    }
    printf("NIL\n");
}

 
int main() {
    int arr[] = { 3, 6, 9, 2, 11, 1, 4 };
    skiplist list;
    skiplist_init(&list);
 
    printf("Insert values 3, 6, 9, 2, 11, 1, 4 into the list\n");
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        skiplist_insert(&list, arr[i], arr[i]);
    }
    skiplist_print(&list);
 
    printf("Searching for the values\n");
    int keys[] = { 3, 9, 11, 8 };
 
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        snode *x = skiplist_search(&list, keys[i]);
        if (x) {
            printf("key = %d, value = %d\n", keys[i], x->value);
        } else {
            printf("key = %d, not found\n", keys[i]);
        }
    }
 
    return 0;
}
