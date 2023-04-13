/* Test program for 3rd mandatory assignment.
 *
 * A process writes ITS integers to /dev/dm510-0 while
 * another process read ITS integers from /dev/dm510-1.
 * A checksum of the written data is compared with a
 * checksum of the read data.
 *
 * This is done in both directions.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "dm510_ioctl_numbers.h"


int ITS;

void read_all(int fd, void *buf, int count) {
    while (count > 0) {
        int ret;
        ret = read(fd, buf, count);
        if (ret == -1) {
            perror("read");
            exit(1);
        }

        count -= ret;
        buf += ret;
    }
}

void write_all(int fd, void *buf, int count) {
    while (count > 0) {
        int ret;
        ret = write(fd, buf, count);
        if (ret == -1) {
            perror("write");
            exit(1);
        }

        count -= ret;
        buf += ret;
    }
}

void test_ioctl() {
    int fd;
    int buffer_size, nreaders, retval;

    fd = open("/dev/dm510-0", O_RDWR);

    /* Get buffer size */
    retval = ioctl(fd, DM510_IOR_BUFFER_SIZE, &buffer_size);
    if (retval == -1) {
        perror("ioctl");
    }
    printf("Buffer size: %d\n", buffer_size);

    /* Set buffer size */
    buffer_size = 1024;
    retval = ioctl(fd, DM510_IOS_BUFFER_SIZE, &buffer_size);
    if (retval == -1) {
        perror("ioctl");
    }
    printf("New buffer size: %d\n", buffer_size);
    

    /* Get number of readers */
    retval = ioctl(fd, DM510_IOR_READERS, &nreaders);
    if (retval == -1) {
        perror("ioctl");
    }
    printf("Number of readers: %d\n", nreaders);

    /* Set number of readers */
    nreaders = 5;
    retval = ioctl(fd, DM510_IOS_READERS, &nreaders);
    if (retval == -1) {
        perror("ioctl");
    }
    printf("New number of readers: %d\n", nreaders);

    close(fd);
}

void test_read_write(int buffer_size, int its) {
    pid_t pid;
    int fd0, fd1;
    int sum = 0, i;
    int val;
    int cnt;
    int retval;
    ITS = its;

    pid = fork();

    fd0 = open("/dev/dm510-0", O_RDWR);
    perror("w open");

    fd1 = open("/dev/dm510-1", O_RDWR);
    perror("r open");

    /* Set buffer size */
    // doesnt matter if it is fd0 or fd1 as it is the same buffer_size variable in the driver.
    retval = ioctl(fd0, DM510_IOS_BUFFER_SIZE, &buffer_size);
    if (retval == -1) {
        perror("ioctl");
    }
    printf("New buffer size: %d\n", buffer_size);

    if (pid == 0) {	
        for (i=0; i<ITS; i++) {
            val++;
            sum += val;
            cnt = 4;
            write_all(fd0, &val, 4);
        }
        printf("1. expected result: %d\n", sum);

        sum = 0;

        for (i=0; i<ITS; i++) {
            read_all(fd0, &val, 4);
            sum += val;
        }
        printf("2. result: %d\n", sum);
        
        close(fd0);
    } else {
        for (i=0; i<ITS; i++) {
            read_all(fd1, &val, 4);
            sum += val;
        }
        printf("1. result: %d\n", sum);

        sum = 0;

        for (i=0; i<ITS; i++) {
            val++;
            sum += val;
            write_all(fd1, &val, 4);
        }
        printf("2. expected result: %d\n", sum);
        wait(NULL);
        close(fd1);
    }
}

int main(int argc, char *argv[])
{
    test_ioctl();

    test_read_write(9, 20);
    return 0;
}