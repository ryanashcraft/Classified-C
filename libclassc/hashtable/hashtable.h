
#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef void (*hash_func)(void *, size_t size);

struct _htable_entry;

typedef struct _htable {
	struct _htable_entry **entries;
	size_t max_size;
	size_t entry_count;
	size_t resize_ratio;
} hashtable;

hashtable *ht_create(size_t max_size, size_t resize_ratio);

void ht_destroy(hashtable *table);

void ht_insert(hashtable **table, void *key, size_t key_size, void *value, size_t value_size);

void *ht_remove(hashtable *table, void *key, size_t key_size);

void *ht_get(hashtable *table, void *key, size_t key_size);

#endif
