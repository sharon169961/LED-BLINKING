#include <stdint.h>

#define IOPORT_BASE   (0x00000000UL)
#define GPIOA_BASE    (IOPORT_BASE + 0x00000000UL)

void initGPIO() {
    uint32_t mask = 0x00000c0;
    volatile uint32_t* ledport = (uint32_t*)(GPIOA_BASE);

    uint32_t x = *(ledport + 0x00);
    x = (x & ~mask) | (0x01 << 10);
    *(ledport + 0x00) = x; 
}

void toggle_pin(uint32_t gpiobase, uint16_t pin) {
    // Get the current state of the output data register
    uint32_t x = *(volatile uint32_t*)(gpiobase + 0x14);
    
    // Use BSRR register to toggle the pin
    if (x & (1 << pin)) {
        *(volatile uint32_t*)(gpiobase + 0x18) = (1 << (pin + 16)); // Reset the pin
    } else {
        *(volatile uint32_t*)(gpiobase + 0x18) = (1 << pin);        // Set the pin
    }
}

int main(void) {
    initGPIO();
    toggle_pin(GPIOA_BASE, 5);

    while (1) {
        for (int i = 0; i < 1000000; i++); // Delay loop
        toggle_pin(GPIOA_BASE, 5);
    }

    return 0;
}
