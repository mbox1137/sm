// Задача была решена на семинаре

#define DEBUG 0

#include <future>
#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <utility>

using namespace std;

class Counter_pi
{
public:
    pair<uint64_t,uint64_t> operator() (uint32_t number,uint64_t number_of_iteration);
    //Counter_pi(uint64_t num_it): number_of_iteration(num_it) {};
};

pair<uint64_t,uint64_t> Counter_pi::operator() (uint32_t number, uint64_t number_of_iteration)
{
    unsigned int seed = static_cast<int>(number);
    pair<uint64_t,uint64_t> result(0,0);

    for(uint64_t i = 0; i < number_of_iteration; i++)
    {
        double x,y;
        x = rand_r(&seed)/static_cast<double>(RAND_MAX);
        y = rand_r(&seed)/static_cast<double>(RAND_MAX);

        if ((x * x + y * y) <= 1.0)
            result.first++;

        result.second++;
    }

#if DEBUG
    fprintf(stderr, "thread %" PRIu32 "%" PRIu64 "%" PRIu64 "\n", number, result.first, result.second);
#endif

    return result;
}

int main(int argc,char *argv[])
{
    uint32_t num_threads;
    uint64_t number_of_iteration;

    if (argc < 3)
    {
        fprintf(stderr,"We need: number_of_threads and number_of_iterations\n");
        return 1;
    }

    char *end_ptr;
    num_threads=strtoul(argv[1], &end_ptr, 10);
    number_of_iteration=strtoull(argv[2], &end_ptr, 10);

    Counter_pi *counters = new Counter_pi [num_threads];
    auto *futures = new future<pair<uint64_t,uint64_t>> [num_threads];
    for(uint32_t i = 0; i<num_threads; i++)
        futures[i] = async(counters[i],i + 1 , number_of_iteration);

    double result = 0;
    for(uint32_t i = 0; i < num_threads; i++)
    {
        pair<uint64_t,uint64_t> p;
        futures[i].wait();
        p = futures[i].get();
        result += static_cast<double>(p.first) / p.second;
    }

    printf("%.10f\n",result * 4.0 / num_threads);

    return 0;
}

