
#define CLASS Stack
#define SUPER LinkedList

#include "Classified-C.h"

proto(new);
proto(push);
proto(pop);
proto(peek);

defclass
	static(new);

	instance(push);
	instance(pop);
	instance(peek);
end

defcon(new)
	return msgSuper("init");
end

def(push)
	return msgSuper("pushFront", NEXT_ARG(Object));
end

def(pop)
	return msgSuper("removeFront");
end

def(peek)
	return msgSuper("getFront");
end
