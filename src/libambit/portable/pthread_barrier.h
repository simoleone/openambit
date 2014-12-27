/*
 * mostly taken from: http://blog.albertarmea.com/post/47089939939/using-pthread-barrier-on-mac-os-x
 *
 * OS X doesn't implement barriers. So this is an equivalent implementation.
 */

#ifndef PTHREAD_BARRIER_H_
#define PTHREAD_BARRIER_H_

#include <pthread.h>

typedef int libambit_pthread_barrierattr_t;
typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int tripCount;
} libambit_pthread_barrier_t;


int libambit_pthread_barrier_init(libambit_pthread_barrier_t *barrier, const libambit_pthread_barrierattr_t *attr, unsigned int count);
int libambit_pthread_barrier_destroy(libambit_pthread_barrier_t *barrier);
int libambit_pthread_barrier_wait(libambit_pthread_barrier_t *barrier);

#if (defined(_POSIX_BARRIERS) && _POSIX_BARRIERS <= 0)
typedef libambit_pthread_barrierattr_t pthread_barrierattr_t;
typedef  libambit_pthread_barrier_t pthread_barrier_t;
#define pthread_barrier_init(B, A, C) libambit_pthread_barrier_init(B, A, C)
#define pthread_barrier_destroy(B) libambit_pthread_barrier_destroy(B)
#define pthread_barrier_wait(B) libambit_pthread_barrier_wait(B)
#endif // !_POSIX_BARRIERS

#endif // PTHREAD_BARRIER_H_