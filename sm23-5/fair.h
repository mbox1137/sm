struct FairRwLock
{
	int i;
};

typedef struct FairRwLock fair_rwlock_t;

#define FAIR_RWLOCK_INITIALIZER {0}

void fair_rwlock_init(fair_rwlock_t *prw);
void fair_rwlock_destroy(fair_rwlock_t *prw);
void fair_rwlock_wrlock(fair_rwlock_t *prw);
void fair_rwlock_rdlock(fair_rwlock_t *prw);
void fair_rwlock_unlock(fair_rwlock_t *prw);

