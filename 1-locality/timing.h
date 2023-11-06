////////////////////////////// some functionality for timing our code
#include <sys/time.h>
#include <time.h>

typedef struct timeval wallclock_t;

void wallclock_mark(wallclock_t *const tptr)
{
    gettimeofday(tptr, NULL);
}

double wallclock_since(wallclock_t *const tptr)
{
    struct timeval  now;
    gettimeofday(&now, NULL);

    return difftime(now.tv_sec, tptr->tv_sec)
            + ((double)now.tv_usec - (double)tptr->tv_usec) / 1000000.0;
}
////////////////////////////////////////////////////////////////////////