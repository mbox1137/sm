#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
ssize_t safe_write(int in_fd, void *buf, size_t size){
    size_t need_to_write = size;
    ssize_t num;
    while (need_to_write != 0){
        num = write(in_fd, buf + size - need_to_write, need_to_write);
        if (num == -1) {
            if (errno == EINTR){
                continue;
            }
            if (errno == EAGAIN){
                usleep(10000);
                continue;
            }
            return -1;
        }
        need_to_write -= num;
    }
    return size - need_to_write;
}

ssize_t safe_read(int in_fd, void *buf, size_t size){
    size_t need_to_read = size;
    ssize_t num;
    while (need_to_read != 0){
        num = read(in_fd, buf + size - need_to_read, need_to_read);
        if (num == -1) {
            if (errno == EINTR){
                continue;
            }
            if (errno == EAGAIN){
                usleep(10000);
                continue;
            }
            return -1;
        }
        if (num == 0) {
            break;
        }
        need_to_read -= num;
    }
    return size - need_to_read;
}

void copy_file (int in_fd, int out_fd) {
    char buf[4096];
    while(1) {
        ssize_t num_read; 
        num_read = safe_read(in_fd, buf, 4096);
        if (num_read <= 0){
            return;
        }
        ssize_t num_write;
        num_write = safe_write(out_fd, buf, num_read);
        if (num_write == -1) {
            return;
        }
        if (num_read != 4096) {
            break;
        }
    }

    
}    


int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }
    int in_fd = open(argv[1], O_RDONLY);
    if (in_fd == -1) {
        return 2;
    }
    int out_fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if (out_fd == -1){
        return 3;
    }
    copy_file(in_fd, out_fd);
    close(in_fd);
    close(out_fd);
    return 0;
}
