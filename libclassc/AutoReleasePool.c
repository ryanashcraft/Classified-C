
#define CLASS AutoReleasePool
#define SUPER Stack

#include "Classified-C.h"

proto(new);
proto(dealloc);

void msg_finish_auto_release(void *v);

defclass {
	constructor(new);

	instance(dealloc);
} end

defcon(new) {
	return msgSuper("init");
} end

def(dealloc) {
	free_list(self->base.base.value, &msg_finish_auto_release);

	return msgCast(ObjectClass, self, "dealloc");
} end

void msg_finish_auto_release(void *v) {
	msg(v, "finishAutoRelease");
}