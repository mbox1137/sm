#include <cstdio>
#include <thread>
#include <cinttypes>
#include <future>
#include <utility>

using namespace std;

int if_prime(uint64_t n)
{
    uint64_t i;
    if (n > 1)
    {
        for(i = 2; i * i <= n; ++i)
        {
            if ((n % i) == 0)
                return 0;
        }
        return 1;
    }

    return 0;
}

void tfun(uint64_t low, uint64_t high, uint32_t count, promise<uint64_t> *prom)
{
    if (count == 0)
        return;

    size_t temp = 0;

    for (uint64_t i = low; i <= high; ++i)
    {
        if (if_prime(i))
        {
            if (temp < count)
                prom[temp].set_value(i);

            if (++temp == count)
                return;
        }
    }
    try
    {
        throw high;
    }
    catch (...)
    {
        prom[temp].set_exception(current_exception());
    }

    return;
}

int main(int argc, char *argv[])
{
    uint64_t low, high;
    uint32_t count;
    thread thr_main;

    if (scanf("%" SCNu64 "%" SCNu64 "%" SCNu32, &low, &high, &count) != 3)
        return 1;

    promise<uint64_t> prom[count], *prom_ptr = prom;
    future<uint64_t> fut[count];

    for(uint32_t i = 0; i < count; ++i)
        fut[i] = prom[i].get_future();

    try
    {
        thr_main = thread(tfun, low, high, count, prom_ptr);
        for (uint32_t i = 0; i != count; ++i)
        {
            fut[i].wait();
            printf("%" PRIu64 "\n", fut[i].get());
        }
    }
    catch (uint64_t err)
    {
        printf("%" PRIu64 "\n", err);
    }

    thr_main.join();

    return 0;
}

// http://www.cplusplus.com/reference/future/promise/
