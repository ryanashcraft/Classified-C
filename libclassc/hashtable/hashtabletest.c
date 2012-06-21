
#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"

int main(int argc, char **argv) {
	hashtable *ht = ht_create(8, 2);
	ht_insert(ht, "foo", 3, "fighter", 7);
	char *what = ht_get(ht, "foo", 3);
	printf("%s\n", what);
}
