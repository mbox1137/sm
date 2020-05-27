#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char** argv) {
/*
# create an INET, STREAMing socket
#    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# now connect to the web server on port 80 - the normal http port
#    s.connect(("www.python.org", 80))
#    print(s)
*/
    int s;
    s=socket(AF_INET, SOCK_STREAM, 0);
    printf("%d\n", s);
    return(0);
}
