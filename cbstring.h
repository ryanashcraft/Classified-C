
#ifndef CB_STRING_H
#define CB_STRING_H

typedef struct _cbstring_data *cbstring_data;

struct _cbstring_data {
	string value;
};

string cbstring_to_string();

class cbstring_init();

#endif