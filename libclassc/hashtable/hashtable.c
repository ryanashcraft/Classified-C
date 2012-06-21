
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include "hashtable.h"

typedef struct _htable_entry {
	void *key;
	size_t key_size;
	void *value;
	size_t value_size;
} htable_entry;

static int ht_hash(void *key, size_t key_size, size_t max_size);
static int ht_linear_probe_if_needed(hashtable *table, int hash);
static int ht_correct_index_if_needed(hashtable *table, int index, void *key, size_t key_size);
static hashtable *ht_resize_if_needed(hashtable *table);

hashtable *ht_create(size_t max_size, size_t resize_ratio) {
	hashtable *table = malloc(sizeof(struct _htable));
	assert(table);

	table->entries = calloc(max_size, sizeof(void *));
	assert(table->entries);
	table->max_size = max_size;
	table->entry_count = 0;
	table->resize_ratio = resize_ratio;

	return table;
}

void ht_destroy(hashtable *table) {
	free(table->entries);
	free(table);
}

void ht_insert(hashtable **table, void *key, size_t key_size, void *value, size_t value_size) {
	*table = ht_resize_if_needed(*table);

	int hash = ht_hash(key, key_size, (*table)->max_size);
	hash = ht_linear_probe_if_needed(*table, hash);

	htable_entry *entry = malloc(sizeof(struct _htable_entry));
	
	entry->key = malloc(key_size);
	memcpy(entry->key, key, key_size);
	entry->key_size = key_size;

	entry->value = malloc(value_size);
	memcpy(entry->value, value, value_size);
	entry->value_size = value_size;
	
	(*table)->entries[hash] = entry;

	(*table)->entry_count++;
}

void *ht_remove(hashtable *table, void *key, size_t key_size) {
	int hash = ht_hash(key, key_size, table->max_size);

	int index = ht_correct_index_if_needed(table, hash, key, key_size);
	assert(index >= 0 && index < table->max_size);

	void *value = table->entries[index]->value;

	free(table->entries[index]);
	table->entries[index] = NULL;

	return value;
}

void *ht_get(hashtable *table, void *key, size_t key_size) {
	int hash = ht_hash(key, key_size, table->max_size);

	int index = ht_correct_index_if_needed(table, hash, key, key_size);
	if (index < 0 || index >= table->max_size || table->entries[index]->value == NULL) {
		// fprintf(stderr, "NULL returned from table\n");

		return NULL;
	}

	return table->entries[index]->value;
}

int ht_hash(void *key, size_t key_size, size_t max_size) {
	short *ptr = (short *)key;
    int hash = 0;
    size_t i;

    for (i = 0; i < (key_size / 2); i++) {
        hash ^= (i << 4 ^ *ptr << 8 ^ *ptr);
        ptr++;
    }

    hash = hash % max_size;
    return hash;
}

int ht_linear_probe_if_needed(hashtable *table, int hash) {
	while (table->entries[hash] != NULL) {
		hash += 1;
		if (hash == table->max_size) {
			hash = 0;
		}
	}

	return hash;
}

int ht_correct_index_if_needed(hashtable *table, int index, void *key, size_t key_size) {
	while (1) {
		if (table->entries[index] == NULL) {
			return -1;
		} else if (table->entries[index]->key_size == key_size && memcmp(table->entries[index]->key, key, key_size) == 0) {
			return index;
		} else {
			index += 1;
			if (index == table->max_size) {
				index = 0;
			}
		}
	}

	return -1;
}

hashtable *ht_resize_if_needed(hashtable *table) {
	int ratio = 0;
	hashtable *new_hashtable = NULL;

	if (table->entry_count != 0) {
		ratio = table->max_size / table->entry_count;
		// fprintf(stderr, "max: %d | entries: %d | ratio: %d\n", (int)table->max_size, (int)table->entry_count, ratio);

		if (ratio <= table->resize_ratio) {
			// fprintf(stderr, "WE'RE GOING TO RESIZE\n");
			// not thread safe around here
			// memcpy(table->entries, old_entries, table->max_size);
			
			new_hashtable = ht_create(table->max_size * 2, table->resize_ratio);
			for (int i = 0; i < table->max_size; i++) {
				struct _htable_entry *entry = table->entries[i];
				if (entry != NULL) {
					int hash = ht_hash(entry->key, entry->key_size, new_hashtable->max_size);
					int index = ht_linear_probe_if_needed(new_hashtable, hash);
					assert(index >= 0 && index < new_hashtable->max_size);

					new_hashtable->entries[index] = entry;
					new_hashtable->entry_count++;
				}
			}
		}
	}

	if (new_hashtable == NULL) {
		return table;
	}

	ht_destroy(table);
	return new_hashtable;
}
