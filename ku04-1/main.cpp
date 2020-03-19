//https://www.ownedcore.com/forums/world-of-warcraft/world-of-warcraft-bots-programs/wow-memory-editing/281008-gcc-thiscall-calling-convention-linux-win32-mingw.html

#include <iostream>
#include "ku04-1.h"

using namespace std;

int main() 
{ 
    cout << "Hello, world!" << endl;
    return 0; 
}

/*
int main() {
    int v2 = 2;
    long long v3 = 4;
    float v4 = 1.0;
    printf("%d\n", forward$args(v2, v3, v4));

    return 0;
}
*/
/*
typedef bool (*fp_CGPlayer_C__ClickToMove) (
  uint32_t ctmtype, uint64_t* clickGUID,
  float* clickPos, float precision)
  __attribute__((thiscall));
*/
