
#ifndef AUTO_RELEASE_POOL_H
#define AUTO_RELEASE_POOL_H

extern Class AutoReleasePoolClass;

typedef struct _AutoReleasePool {
	struct _Stack base;
} *AutoReleasePool;

void AutoReleasePoolInit();

#endif
