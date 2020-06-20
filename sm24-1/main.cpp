#include <mutex>
#include <thread>

#define NN 3
#define NI 1000000

using namespace std;

double mass[NN];
mutex door;

void tfun(int inx1, int inx2, int val1, int val2)
{
    for (int i = 0; i < NI; ++i)
    {
        lock_guard<mutex> lock(door);
        mass[inx1] += val1;
        mass[inx2] -= val2;
    }
}

int main(int argc, char *argv[])
{
    thread threads[NN];

    for (int i = 0; i < NN; ++i)
        threads[i] = thread(tfun, i, (i + 1) % NN, 80 + 20 * i, 90 + 20 * i);

    for (int i = 0; i < NN; ++i)
        threads[i].join();

    for (int i = 0; i < NN; ++i)
        printf("%.10g\n", mass[i]);

    return 0;
}

// https://en.cppreference.com/w/cpp/thread/lock_guard
// https://github.com/blackav/hse-caos-2019/tree/master/24-stdthread
