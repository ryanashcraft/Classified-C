
#define CLASS AutoReleasePool
#define SUPER Stack

#include "Classified-C.h"

proto(new);
proto(dealloc);

void msg_finish_autorelease(void *v);

defclass
	static(new);

	instance(dealloc);
end

defcon(new)
	return msgSuper("init");
end

def(dealloc)
	free_list(self->base.base.value, &msg_finish_autorelease);

	return msgCast(ObjectClass, self, "dealloc");
end

void msg_finish_autorelease(void *v) {
	msg(v, "finishAutoRelease");
}