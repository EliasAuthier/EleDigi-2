#include <stdint.h>

#define SRAM_SIZE		((uint32_t) 0x00005000)
#define SRAM_BASE		((uint32_t) 0x20000000)
#define STACKINIT		((interrupt_t)(SRAM_BASE+SRAM_SIZE))

typedef void(*interrupt_t)(void);

int  main(void);

const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	STACKINIT,										// 0x0000_0000 Stack Pointer
	(interrupt_t) main,								// 0x0000_0004 Reset
};

int main(void){

	*(int *)(0x40021018) |= (1 << 4) | (1 << 2);	// Habilitacion del reloj del GPIOC.

	*(int *)(0x40011004) = (3 << 20);				// Configuracion del GPIOC desde el pin 8 al 15
													//    Mode = 11 (Salida de hasta 50 MHz) para el pin 13 del GPIOC
													//    CNF  = 00 (Salida Push-Pull)

	*(int *)(0x4001100C) = (0 << 13);				// Pone un '1' en el registro ODR
	
	while(1) {
	}

	return 0;
}
