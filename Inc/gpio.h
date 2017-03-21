#ifndef GPIO_H
#define GPIO_H

#define PORT_TR0 GPIOG
#define PORT_TR1 GPIOB
#define PORT_TR2 GPIOG
#define PORT_TR3 GPIOI

#define PORT_ACC0 GPIOH
#define PORT_ACC1 GPIOI
#define PORT_ACC2 GPIOI
#define PORT_ACC3 GPIOA

#define PIN_TR0 GPIO_PIN_6
#define PIN_TR1 GPIO_PIN_4
#define PIN_TR2 GPIO_PIN_7
#define PIN_TR3 GPIO_PIN_0

#define PIN_ACC0 GPIO_PIN_6
#define PIN_ACC1 GPIO_PIN_3
#define PIN_ACC2 GPIO_PIN_2
#define PIN_ACC3 GPIO_PIN_15

#define PORT_IN0 GPIOA
#define PORT_IN1 GPIOF
#define PORT_IN2 GPIOF
#define PORT_IN3 GPIOF

#define PIN_IN0 GPIO_PIN_0
#define PIN_IN1 GPIO_PIN_10
#define PIN_IN2 GPIO_PIN_9
#define PIN_IN3 GPIO_PIN_8


void gpio_init(void);
void gpio_all_on(void);
void gpio_all_off(void);

#endif
