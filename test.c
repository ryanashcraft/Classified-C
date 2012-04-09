
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "objc.h"

char *strendtrim(char *s);

int main(int argc, char **argv) {
	string prompt = "? "; 
	int rc = 0;
	int i;
	string command;
	string temp;

	_objc_init();

	var a_null = objc_constructor("Null");
	
	objc_message_send(a_null, "description", &temp);
}

char *strendtrim(char *s) {
	if (strlen(s) > 0) {
	    int i = (int)strlen(s) - 1;
	    while(i >= 0
	    		&& (s[i] == '\n' || s[i] == '\r' || s[i] == ' ' || s[i] == '\t')) {
	        s[i] = 0;
	        --i;
	    }
	}

    return s;
}
