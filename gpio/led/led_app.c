#include <stdio.h>
#include <fcntl.h>      /* O_RDWR */

#define LED_ON  1
#define LED_OFF 2

int main(int argc, char**argv)
{
        int fd = -1;
        int i = 0;
        fd = open("/dev/standard_device", O_RDWR);

        if(fd < 0)
        {
                printf("[app] driver open fail\n");
                return -1;
        }

        int write_buf = -1;
        for(i = 0; i < 10; i++)
        {
                write_buf = LED_ON;
                write(fd, &write_buf, 4);

                write_buf = LED_OFF;
                write(fd, &write_buf, 4);

                sleep(1);
        }

        close(fd);

        return 0;
}
