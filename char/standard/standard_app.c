#include <stdio.h>
#include <fcntl.h>      /* O_RDWR */

int main(int argc, char**argv)
{
        int fd;
        printf("[app] O_RDWR = %d\n", O_RDWR);
        fd = open("/dev/standard_device", O_RDWR);

        if(fd < 0)
        {
                printf("[app] driver open fail\n");
                return -1;
        }

        int write_buf = 100;
        write(fd, &write_buf, 4);

        int read_buf = 0;
        read(fd, &read_buf, 4);

        close(fd);
        printf("[app] read_buf = %d\n", read_buf);

        return 0;
}
