#define DEBUG 0

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <semaphore.h>
#include "fair.h"

fair_rwlock_t myrw=FAIR_RWLOCK_INITIALIZER;

void fair_rwlock_init(fair_rwlock_t *prw) {
}

void fair_rwlock_destroy(fair_rwlock_t *prw) {
}

void fair_rwlock_wrlock(fair_rwlock_t *prw) {
}

void fair_rwlock_rdlock(fair_rwlock_t *prw) {
}

void fair_rwlock_unlock(fair_rwlock_t *prw) {
}

