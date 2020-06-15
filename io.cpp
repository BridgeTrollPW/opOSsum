#include "io.hpp"

/**
 * @brief  write one byte to port memory address
 * @note   
 * @param  port: 
 * @param  value: 
 * @retval None
 */
void IO::outb(uint16_t port, uint8_t value)
{
    asm volatile("outb %1, %0"
                 :
                 : "dN"(port), "a"(value));
}

/**
 * @brief  receive byte from port line
 * @note   
 * @param  port: 
 * @retval 
 */
uint8_t IO::inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0"
                 : "=a"(ret)
                 : "dN"(port));
    return ret;
}

/**
 * @brief  receive short from port line
 * @note   
 * @param  port: 
 * @retval 
 */
uint16_t IO::inw(uint16_t port)
{
    uint16_t ret;
    asm volatile("inw %1, %0"
                 : "=a"(ret)
                 : "dN"(port));
    return ret;
}