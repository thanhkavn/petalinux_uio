#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#define GPIO_MAP_SIZE           0x10000
#define GPIO_DATA               0x00
#define GPIO_TRI                0x04
#define LED_NUM             256

#define LED_DELAY             10000000


int main(int argc, char *argv[])
{
    int fd;
    char *uiod = "/dev/uio4";
    void *gpio_ptr;
    volatile int Delay;

    printf("AXI GPIO UIO test.\n");

    // open the UIO device file to allow access to the device in user space

    fd = open(uiod, O_RDWR);
    if (fd < 1) {
        printf("Invalid UIO device file:%s.\n", uiod);
        return -1;
    }

    // mmap the GPIO device into user space

    gpio_ptr = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (gpio_ptr == MAP_FAILED) {
        printf("Mmap call failure.\n");
        return -1;
    }

    // set bit0 on the GPIO to be output
    // see pg144 for ref

  //  *((volatile unsigned *)(gpio_ptr + GPIO_TRI)) = 0x0;


    // Toggle the LED
    while (1) {
        int i;
        unsigned char led_pin = 0x0;
        for (i = 0; i < LED_NUM; i++) {
            *((volatile unsigned *)(gpio_ptr + GPIO_DATA)) = led_pin;
            for (Delay = 0; Delay < LED_DELAY; Delay++);
            *((volatile unsigned *)(gpio_ptr + GPIO_DATA)) = 0x0;
            led_pin++;
        }
    }


    // unmap the GPIO device from user space

    munmap(gpio_ptr, 4096);
    return 0;
}
