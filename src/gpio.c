#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "gpio.h"

/**
 * @brief Setup GPIO
 * @param pin_num
 */
void gpio_setup(int pin_num)
{
    int fd;
    char pin[3];
    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/export");
        exit(EXIT_FAILURE);
    }

    sprintf(pin, "%d", pin_num);
    if (write(fd, pin, strlen(pin)) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

/**
 * @brief Get GPIO direction (in/out)
 * @param pin_num
 * @return char *
 */
char * gpio_get_direction(int pin_num)
{
    int fd;
    char direction_path[1024], direction[4];
    char error_str[1024];

    sprintf(direction_path, "/sys/class/gpio/gpio%d/direction", pin_num);
    fd = open(direction_path, O_RDONLY);
    if (fd == -1) {
        sprintf(error_str,"Unable to open %s",direction_path);
        perror(error_str);
        exit(EXIT_FAILURE);
    }

    if (read(fd, direction, 2) != 2) {
        sprintf(error_str,"Error writing to %s",direction_path);
        perror(error_str);
        exit(EXIT_FAILURE);
    }

    close(fd);
    return direction;
}

/**
 * @brief Set GPIO direction (in/out)
 * @param pin_num
 * @param direction
 */
void gpio_set_direction(int pin_num, char *direction)
{
    int fd;
    char direction_path[1024];
    char error_str[1024];

    sprintf(direction_path, "/sys/class/gpio/gpio%d/direction",pin_num);
    fd = open(direction_path, O_WRONLY);
    if (fd == -1) {
        sprintf(error_str, "Unable to open %s", direction_path);
        perror(error_str);
        exit(EXIT_FAILURE);
    }

    if (write(fd, direction, strlen(direction)) != strlen(direction)) {
        sprintf(error_str,"Error writing to %s",direction_path);
        perror(error_str);
        exit(EXIT_FAILURE);
    }

    close(fd);
}

/**
 * @brief Get GPIO Pull-Up/Pull-Down
 * @param pin_num
 * @return int
 */
int gpio_get_pullup_down(int pin_num)
{
    int fd;
    char pullup_down_path[1024], pullup_down_str[2];
    char error_str[1024];

    sprintf(pullup_down_path, "/sys/class/gpio/gpio%d/active_low",pin_num);
    fd = open(pullup_down_path, O_RDONLY);
    if (fd == -1) {
        sprintf(error_str, "Unable to open %s", pullup_down_path);
        perror(error_str);
        exit(EXIT_FAILURE);
    }

    if (read(fd, pullup_down_str, 1) != 1) {
        sprintf(error_str, "Error writing to %s", pullup_down_path);
        perror(error_str);
        exit(EXIT_FAILURE);
    }

    close(fd);

    return atoi(pullup_down_str);
}

/**
 * @brief Set GPIO Pull-Up/Pull-Down
 * @param pin_num
 * @param pullup_down
 */
void gpio_set_pullup_down(int pin_num, int pullup_down)
{
    int fd;
    char pullup_down_path[1024], pullup_down_str[2];
    char error_str[1024];

    sprintf(pullup_down_path, "/sys/class/gpio/gpio%d/active_low",pin_num);
    fd = open(pullup_down_path, O_WRONLY);
    if (fd == -1) {
        sprintf(error_str, "Unable to open %s", pullup_down_path);
        perror(error_str);
        exit(EXIT_FAILURE);
    }

    sprintf(pullup_down_str, "%d", pullup_down);
    if (write(fd, pullup_down_str, strlen(pullup_down_str)) != strlen(pullup_down_str)) {
        sprintf(error_str, "Error writing to %s", pullup_down_path);
        perror(error_str);
        exit(EXIT_FAILURE);
    }

    close(fd);
}

/**
 * @brief Get value from GPIO
 * @param pin_num
 * @return int
 */
int gpio_get_value(int pin_num)
{
    int fd;
    char value_path[1024], value[2];
    char error_str[1024];

    sprintf(value_path, "/sys/class/gpio/gpio%d/value",pin_num);
    fd = open(value_path, O_RDONLY);
    if (fd == -1) {
        sprintf(error_str, "Unable to open %s", value_path);
        perror(error_str);
        exit(EXIT_FAILURE);
    }

    if (read(fd, value, 1) != 1) {
        sprintf(error_str, "Error writing to %s", value_path);
        perror(error_str);
        exit(EXIT_FAILURE);
    }

    close(fd);

    return atoi(value);
}

/**
 * @brief Set value from GPIO
 * @param pin_num
 */
void gpio_set_value(int pin_num, int value)
{
    int fd;
    char value_path[1024], value_str[2];
    char error_str[1024];

    sprintf(value_path, "/sys/class/gpio/gpio%d/value",pin_num);
    fd = open(value_path, O_WRONLY);
    if (fd == -1) {
        sprintf(error_str, "Unable to open %s", value_path);
        perror(error_str);
        exit(EXIT_FAILURE);
    }

    sprintf(value_str, "%d", value);
    if (write(fd, value_str, strlen(value_str)) != strlen(value_str)) {
        sprintf(error_str, "Error writing to %s",value_path);
        perror(error_str);
        exit(EXIT_FAILURE);
    }

    close(fd);
}


/**
 * @brief Cleanup GPIO
 * @param pin_num
 */
void gpio_cleanup(int pin_num)
{
    int fd;
    char pin[3];
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/unexport");
        exit(EXIT_FAILURE);
    }

    sprintf(pin,"%d",pin_num);
    if (write(fd, pin, strlen(pin)) != 2) {
        perror("Error writing to /sys/class/gpio/unexport");
        exit(EXIT_FAILURE);
    }

    close(fd);
}