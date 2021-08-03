#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO_INPUT      "in"
#define GPIO_OUTPUT     "out"
#define GPIO_PULL_UP    1
#define GPIO_PULL_DOWN  0

void gpio_setup(int pin_num);
char * gpio_get_direction(int pin_num);
void gpio_set_direction(int pin_num, char *direction);
int gpio_get_pullup_down(int pin_num);
void gpio_set_pullup_down(int pin_num, int pullup_down);
int gpio_get_value(int pin_num);
void gpio_set_value(int pin_num, int value);
void gpio_cleanup(int pin_num);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H */