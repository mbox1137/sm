#ifdef __cplusplus
extern "C" 
#endif
int process(int *that, long long v2, float v4, unsigned v3);

//int forward$args (int v2, long long v3, float v4) __attribute__((thiscall));
//    extern "C++" int forward$args (int v2, long long v3, float v4) __attribute__((thiscall));

#ifdef __cplusplus
class FUNC { 
    public: 
    string funcname; 
    int v2;
    long long v3;
    float v4;

    void printname() {
       cout << "Geekname is: " << funcname; 
    }
    int prc(int v2, long long v3, float v4);
};
#endif

#ifdef __cplusplus
extern "C" 
#endif
int forward$args(
#ifdef __cplusplus
FUNC *p, 
#else
void *p, 
#endif
int v2, long long v3, float v4) __attribute__((thiscall));
