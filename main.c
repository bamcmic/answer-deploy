#include "gd32e23x.h"

void delay(volatile uint32_t t)
{
    while(t--);
}

/* UART打印 */
void uart_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_USART0);

    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_9);
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_10);

    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);

    usart_baudrate_set(USART0, 115200);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_enable(USART0);
}

void uart_send(char c)
{
    usart_data_transmit(USART0, c);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
}

void uart_print(char *s)
{
    while(*s)
        uart_send(*s++);
}

/* I2C初始化（OLED用） */
void i2c_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_I2C0);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6 | GPIO_PIN_7);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);

    i2c_clock_config(I2C0, 100000, I2C_DTCY_2);
    i2c_enable(I2C0);
}

/* 这里先用占位函数（你后面再升级SSD1306驱动） */
void oled_show(void)
{
    // 先不复杂化，后面我可以给你完整SSD1306驱动
}

int main(void)
{
    uart_init();
    i2c_init();

    uart_print("GD32E230 BOOT OK\r\n");

    while(1)
    {
        uart_print("alive\r\n");
        delay(800000);
    }
}