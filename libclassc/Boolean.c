
#define CLASS Boolean
#define SUPER Integer

#include "Classified-C.h"

proto(newWithInt);
proto(yes);
proto(no);
proto(isYes);

static Boolean yesInstance = NULL;
static Boolean noInstance = NULL;

defclass
	constructor(newWithInt);

	static(yes);
	static(no);
	static(isYes);

	yesInstance = msg(BooleanClass, "newWithInt", YES);
	noInstance = msg(BooleanClass, "newWithInt", NO);
end

defcon(newWithInt)
	msg(self, "initWithInt", args);

	return self;
end

defstat(yes)
	return yesInstance;
end

defstat(no)
	return noInstance;
end

defstat(isYes)
	if (NEXT_ARG(size_t) == (size_t)NO) {
		return NO;
	}

	return YES;
end
