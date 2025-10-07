#include <stdint.h>

// 1. Define Base Address and Register Offsets (from Reference Manual)
#define PERIPH_BASE     (0x40000000UL)
#define AHB1_PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define RCC_BASE        (AHB1_PERIPH_BASE + 0x3800UL) // Example address
#define GPIOA_BASE      (AHB1_PERIPH_BASE + 0x0000UL) // Example address

// 2. Define Register Pointers (Typecasting the address)
#define RCC_AHB1ENR     *((volatile uint32_t *) (RCC_BASE + 0x30U)) // Clock Enable Register
#define GPIOA_MODER     *((volatile uint32_t *) (GPIOA_BASE + 0x00U)) // Mode Register
#define GPIOA_ODR       *((volatile uint32_t *) (GPIOA_BASE + 0x14U)) // Output Data Register

// 3. Define the Bit Masks (from Reference Manual)
#define GPIOAEN_POS     (0U) // Bit 0 in RCC_AHB1ENR enables GPIOA
#define LED_PIN         (5U) // User LED often on Pin 5 (PA5)

int main(void)
{
    // --- STEP 1: Enable the clock for GPIOA ---
    // Use bitwise OR to set the GPIOAEN bit high (no other bits are changed).
    RCC_AHB1ENR |= (1U << GPIOAEN_POS);

    // --- STEP 2: Set the LED pin mode to General Purpose Output ---
    // Clear bits [11:10] and set to '01' for output mode (Mode 01)
    // Pin 5 uses bits 10 and 11 (5 * 2 = 10)
    GPIOA_MODER &= ~(0b11U << (LED_PIN * 2)); // Clear bits 10 and 11
    GPIOA_MODER |= (0b01U << (LED_PIN * 2));  // Set to 01 (Output Mode)

    while (1)
    {
        // --- STEP 3: Toggle the LED (Set HIGH) ---
        // Use bitwise OR to set the specific pin high.
        GPIOA_ODR |= (1U << LED_PIN);

        for (int i = 0; i < 500000; i++); // Simple software delay

        // --- STEP 4: Toggle the LED (Set LOW) ---
        // Use bitwise AND with NOT (~) to clear the specific pin low.
        GPIOA_ODR &= ~(1U << LED_PIN);

        for (int i = 0; i < 500000; i++); // Simple software delay
    }
}