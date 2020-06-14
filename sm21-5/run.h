int run(const char* cmd, 
        const char* input, 
        char** poutput, 
        char** perror, 
        int timeot);
char* readpipe(int fd);
void writepipe(int fd, const char* s);
