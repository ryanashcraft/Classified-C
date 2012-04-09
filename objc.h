
#ifndef OBJC_H
#define OBJC_H

typedef struct _class class;
typedef struct _obj obj;
typedef struct _method method;

typedef obj * var;

typedef unsigned int uint;
typedef char * string;
typedef obj * (*cpointer) (void);
typedef void * (*fpointer) (obj *obj);

struct _class {
	string name;
	cpointer constructor;
	list *v_table;
};

struct _obj {
	class *class;
};

struct _method {
	string name;
	fpointer f_pointer;
	class *return_type;
};

#endif