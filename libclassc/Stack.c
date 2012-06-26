
#define CLASS Stack
#define SUPER LinkedList

#include "Classified-C.h"

proto(new);
proto(push);
proto(pop);
proto(peek);

defclass
	constructor(new);

	instance(push);
	instance(pop);
	instance(peek);
end

defcon(new)
	return msgSuper("init");
end

def(push)
	return msgSuper("pushFront", nextArg(Object));
end

def(pop)
	return msgSuper("removeFront");
end

def(peek)
	return msgSuper("getFront");
end
