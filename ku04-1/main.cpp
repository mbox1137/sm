#include <iostream>
using namespace std;

class Op {
  int width, height;
  public:
    int f(int) __attribute__((thiscall));
};

//int Op::f(int x) __attribute__((thiscall));

/*
typedef bool (*fp_CGPlayer_C__ClickToMove) (
  uint32_t ctmtype, uint64_t* clickGUID,
  float* clickPos, float precision)
  __attribute__((stdcall));
*/

int Op::f(int x) {
  return(x+1);
}

int main() 
{ 
  Op op;
  op.f(123);
  cout << "Hello, world!" << endl;
  return 0; 
}
