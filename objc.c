
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "list.h"

#include "objc.h"
#include "objc_null.h"

list *class_list;

obj *objc_constructor(string class_name);

int class_name_equals(const void *class, va_list args);

void _objc_init() {
	class_list = create_list();

	push_back(class_list, _objc_null_init());
}

int main(int argc, char **argv) {
	_objc_init();

	var a_null = objc_constructor("NULL");

	((method *)back(a_null->class->v_table))->f_pointer(a_null);

	printf("\n");
}

obj *objc_constructor(string class_name) {
	class *new_class = get_first_occurrence(class_list, class_name_equals, class_name);

	return new_class->constructor();
}

int class_name_equals(const void *classp, va_list args) {
	string name;
	class *the_class = (class *)classp;

	vsprintf(name, "%s", args);

	if (strcmp(the_class->name, name) == 0) {
		return 1;
	}

	return 0;
}