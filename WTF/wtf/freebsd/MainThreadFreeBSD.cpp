// Copyright (c) 2015 Turbulenz Limited

#import "config.h"
#import "MainThread.h"

#include <pthread.h>

namespace WTF
{

static bool       sMainThreadInitialized = false;
static pthread_t  sMainThread;

static bool       sDispatchFunctionsOnMainThread = false;

void initializeMainThreadPlatform()
{
    sMainThreadInitialized = true;
    sMainThread = pthread_self();

    sDispatchFunctionsOnMainThread = false;
}

void scheduleDispatchFunctionsOnMainThread()
{
    sDispatchFunctionsOnMainThread = true;
}

void tickFreeBSD()
{
    if (sDispatchFunctionsOnMainThread)
    {
        sDispatchFunctionsOnMainThread = false;
        dispatchFunctionsFromMainThread();
    }
}

} // namespace WTF
