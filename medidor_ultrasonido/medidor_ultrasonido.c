// vi: ts=4 shiftwidth=4
//																			  //
// Author(s):																  //
//	 Miguel Angel Sagreras													  //
//																			  //
// Copyright (C) 2021														  //
//	  Miguel Angel Sagreras													  //
//																			  //
// This source file may be used and distributed without restriction provided  //
// that this copyright statement is not removed from the file and that any	  //
// derivative work contains  the original copyright notice and the associated //
// disclaimer.																  //
//																			  //
// This source file is free software; you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by the   //
// Free Software Foundation, either version 3 of the License, or (at your	  //
// option) any later version.												  //
//																			  //
// This source is distributed in the hope that it will be useful, but WITHOUT //
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or	  //
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for   //
// more details at http://www.gnu.org/licenses/.							  //
//																			  //

#define SRAM_SIZE		((uint32_t) 0x00005000)
#define SRAM_BASE		((uint32_t) 0x20000000)
#define STACKINIT		((interrupt_t)(SRAM_BASE+SRAM_SIZE))

typedef int			   int32_t;
typedef short		   int16_t;
typedef char		   int8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

typedef void(*interrupt_t)(void);

typedef union {
	uint8_t  byte[4];
	uint16_t hword[2];
	uint32_t word;
} word_t;

typedef word_t page[0x400/sizeof(uint32_t)];

// Memory map


#define RCC_BASE            0x40021000 //direccion base del RCC
#define CR_OFFSET           0x00
#define CFGR_OFFSET         0x04
#define CIR_OFFSET          0x08
#define APB2RSTR_OFFSET     0x0C
#define APB1RSTR_OFFSET     0x10
#define AHBENR_OFFSET       0x14
#define APB2BENR            (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define APB12ENR_OFFSET     0x1C  

//GPIO registers
#define GPIOC_CRL           (*(volatile uint32_t *)(GPIO_PORT_C_BASE + 0x00))
#define GPIOA_CRL           (*(volatile uint32_t *)(GPIO_PORT_A_BASE + 0x00))
#define GPIOC_CRH           (*(volatile uint32_t *)(GPIO_PORT_C_BASE + 0x04)) 
#define GPIOA_CRH           (*(volatile uint32_t *)(GPIO_PORT_A_BASE + 0x04)) 
#define GPIOA_IDR           (*(volatile uint32_t *)(GPIO_PORT_A_BASE + 0x08))
#define GPIOC_ODR           (*(volatile uint32_t *)(GPIO_PORT_C_BASE + 0x0C))
#define GPIOA_ODR           (*(volatile uint32_t *)(GPIO_PORT_A_BASE + 0x0C))
#define BSRR_OFFSET         0x10
#define LCKR_OFFSET         0x18

#define GPIO_PORT_A_BASE    0x40010800 //direccion base del GPIO puerto A
#define GPIO_PORT_B_BASE    0x40010C00 //direccion base del GPIO puerto B
#define GPIO_PORT_C_BASE    0x40011000 //direccion base del GPIO puerto C

//SYSTICK REGISTERS
#define SYSTICK_BASE        0XE000E000
#define SYSTICK_CTRL        (*(volatile uint32_t *)(SYSTICK_BASE + 0x00))
#define SYSTICK_LOAD        (*(volatile uint32_t *)(SYSTICK_BASE + 0x04))
#define SYSTICK_VAL         (*(volatile uint32_t *)(SYSTICK_BASE + 0x08))//PAG 154
#define SYSTICK_CSR         (*(volatile uint32_t *)(SYSTICK_BASE + 0x10))
#define SYSTICK_RVR         (*(volatile uint32_t *)(SYSTICK_BASE + 0x14))
#define SYSTICK_CVR         (*(volatile uint32_t *)(SYSTICK_BASE + 0x18))
#define SYSTICK_CALIB       (*(volatile uint32_t *)(SYSTICK_BASE + 0x1C))

//EXTI REGISTERS
#define EXTI_BASE           0x40010400
#define EXTI_IMR            (*(volatile uint32_t *)(EXTI_BASE + 0x00))
#define EXTI_EMR            (*(volatile uint32_t *)(EXTI_BASE + 0x04))
#define EXTI_RTSR           (*(volatile uint32_t *)(EXTI_BASE + 0x08))
#define EXTI_FTSR           (*(volatile uint32_t *)(EXTI_BASE + 0x0C))
#define EXTI_SWIER          (*(volatile uint32_t *)(EXTI_BASE + 0x10))
#define EXTI_PR             (*(volatile uint32_t *)(EXTI_BASE + 0x14))

//AFIO REGISTERS
#define AFIO_BASE           0x40010000  
#define AFIO_EXTICR1        (*(volatile uint32_t *)(AFIO_BASE + 0x08))   
#define AFIO_EXTICR4        (*(volatile uint32_t *)(AFIO_BASE + 0x14))   // 192 manual

//NVIC REGISTERS
#define NVIC_BASE           0xE000E100
#define NVIC_ISER0        (*(volatile uint32_t *)(NVIC_BASE + 0x00))   

enum {TIM2	= 0, TIM3  = 1, TIM4  = 2 };
enum {GPIOA = 0, GPIOB = 1, GPIOC = 2, GPIOD = 3, GPIOE = 4, GPIOF = 5 };
enum {DMA1	= 0 };
enum {CHN1	= 0, CHN2  = 1, CHN3  = 2, CHN4  = 3, CHN5	= 4, CHN6  = 5, CHN7 = 6, CHN8 = 7 };
enum {ADC1	= 0 };
struct {
	union {
		struct {
			uint32_t CR1;
			uint32_t CR2;
			uint32_t SMCR;
			uint32_t DIER;
			uint32_t SR;
			uint32_t EGR;
			uint32_t CCMR1;
			uint32_t CCMR2;
			uint32_t CCER;
			uint32_t CNT;
			uint32_t PSC;
			uint32_t ARR;
			uint32_t RES1;
			uint32_t CCR1;
			uint32_t CCR2;
			uint32_t CCR3;
			uint32_t CCR4;
			uint32_t BDTR;
			uint32_t DCR;
			uint32_t DMAR;
		} REGs;
		page reserved;
	} TIMs[3];

	word_t reserved1[(0x40002800-0x40000c00)/sizeof(word_t)];
	page RTC;
	page WWDG;
	page IWDG;
	word_t reserved2[(0x40003800-0x40003400)/sizeof(word_t)];
	page SPI2;
	word_t reserved3[(0x40004400-0x40003c00)/sizeof(word_t)];
	page USART[2];
	word_t reserved4[(0x40005400-0x40004c00)/sizeof(word_t)];
	page I2C[2];
	page USB;
	page USBCAN_SRAM;
	page bxCAN;
	word_t reserved5[(0x40006c00-0x40006800)/sizeof(word_t)];
	page BKP;
	page PWR;
	word_t reserved6[(0x40010000-0x40007400)/sizeof(word_t)];

	page AFIO;
	page EXTI;

	union {
		struct {
			uint32_t CRL;
			uint32_t CRH;
			uint32_t IDR;
			uint32_t ODR;
			uint32_t BSRR;
			uint32_t BRR;
			uint32_t LCKR;
		} REGs;
		page reserved;
	} GPIOs[5];
	word_t reserved7[(0x40012400-0x40011C00)/sizeof(word_t)];
	union {
		struct {
			uint32_t SR;
			uint32_t CR1;
			uint32_t CR2;
			uint32_t SMPR1;
			uint32_t SMPR2;
			uint32_t JOFR;
			uint32_t HTR;
			uint32_t LTR;
			uint32_t SQR1;
			uint32_t SQR2;
			uint32_t SQR3;
			uint32_t JSQR;
			uint32_t JDR;
			uint32_t DR;
		} REGs;
		page reserved;
	} ADC[2];
	page TIM1;
	page SPI1;
	word_t reserved8[(0x40013800-0x40013400)/sizeof(word_t)];
	union  {
		struct {
			uint32_t SR;
			uint32_t DR;
			uint32_t BRR;
			uint32_t CR1;
			uint32_t CR2;
			uint32_t CR3;
			uint32_t GTPR;
		} REGs;
		page reserved;
	} USART1;
	word_t reserved9[(0x40020000-0x40013C00)/sizeof(word_t)];
	union {
		struct {
			uint32_t ISR;
			uint32_t IFCR;
			struct {
				uint32_t CCR;
				uint32_t CNDTR;
				uint32_t CPAR;
				uint32_t CMAR;
				uint32_t RESERVED;
			} CHN[8];
		} REGs;
		page reserved;
	} DMAs[1];
	word_t reservedA[(0x40021000-0x40020400)/sizeof(word_t)];

	union {
		struct {
			uint32_t CR;
			uint32_t CFGR;
			uint32_t CIR;
			uint32_t APB2RSTR;
			uint32_t APB1RSTR;
			uint32_t AHBENR;
			uint32_t APB2ENR;
			uint32_t APB1ENR;
			uint32_t BDCR;
			uint32_t CSR;
			uint32_t AHBRSTR;
			uint32_t CFGR2;
		} REGs;
		page reserved;
	} RCC;
	word_t reservedB[(0x40022000-0x40021400)/sizeof(word_t)];

	union {
		struct {
			uint32_t ACR;
			uint32_t KEYR;
			uint32_t OPTKEYR;
			uint32_t SR;
			uint32_t CR;
			uint32_t AR;
			uint32_t reserved;
			uint32_t OBR;
			uint32_t WRPR;
		} REGs;
		page reserved;
	} FLASH;
} volatile *const DEVMAP = (void *) 0x40000000;

#define ENA_IRQ(IRQ) {CTX->NVIC.REGs.ISER[((uint32_t)(IRQ) >> 5)] = (1 << ((uint32_t)(IRQ) & 0x1F));}
#define DIS_IRQ(IRQ) {CTX->NVIC.REGs.ICER[((uint32_t)(IRQ) >> 5)] = (1 << ((uint32_t)(IRQ) & 0x1F));}
#define CLR_IRQ(IRQ) {CTX->NVIC.REGs.ICPR[((uint32_t)(IRQ) >> 5)] = (1 << ((uint32_t)(IRQ) & 0x1F));}

struct {
	word_t reversed0[(0xe000e010-0xe0000000)/sizeof(word_t)];
	union {
		struct {
			uint32_t CSR;
			uint32_t RVR;
			uint32_t CVR;
			uint32_t CALIB;
		} REGs;
	} SYSTICK;
	word_t reversed1[(0xe000e100-0xe000e020)/sizeof(word_t)];
	union {
		struct {
			uint32_t ISER[8];
			uint32_t RES0[24];
			uint32_t ICER[8];
			uint32_t RES1[24];
			uint32_t ISPR[8];
			uint32_t RES2[24];
			uint32_t ICPR[8];
			uint32_t RES3[24];
			uint32_t IABR[8];
			uint32_t RES4[56];
			uint8_t  IPR[240];
			uint32_t RES5[644];
			uint32_t STIR;
		} REGs;
	} NVIC;
} volatile *const CTX = ((void *) 0xE0000000);

enum IRQs {
	EXTI_15 = 40,
};

int  main(void);
void EXTI15_10_handler(void);

const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	STACKINIT,												// 0x0000_0000 Stack Pointer
	(interrupt_t) main,										// 0x0000_0004 Reset
	0,														// 0x0000_0008
	0,														// 0x0000_000C
	0,														// 0x0000_0010
	0,														// 0x0000_0014
	0,														// 0x0000_0018
	0,														// 0x0000_001C
	0,														// 0x0000_0020
	0,														// 0x0000_0024
	0,														// 0x0000_0028
	0,														// 0x0000_002C
	0,														// 0x0000_0030
	0,														// 0x0000_0034
	0,														// 0x0000_0038
	0,										                // 0x0000_003C SYSTICK
    0,                                                      //40
    0,                                                      //44
    0,                                                      //48
    0,                                                      //4C
    0,                                                      //50
    0,                                                      //54
	0,          											// 58 (EXTI0)
    0,                      								// 5C (EXTI1)
    0,                      								// 60 (EXTI2)
    0,                      								// 64 (EXTI3)
    0,                      								// 68 (EXTI4)
    0,                      								// 6C (DMA1_CH1)
    0,                      								// 70 (DMA1_CH2)
    0,                      								// 74 (DMA1_CH3)
    0,                      								// 78 (DMA1_CH4)
    0,                      								// 7C (DMA1_CH5)
    0,                      								// 80 (DMA1_CH6)
    0,                      								// 84 (DMA1_CH7)
    0,                      								// 88 (ADC1_2)
    0,                      								// 8C (USB_HP_CAN_TX)
    0,                      								// 90 (USB_LP_CAN_RX0)
    0,                      								// 94 (CAN_RX1)
    0,                      								// 98 (CAN_SCE)
    0,                      								// 9C (EXTI9_5)
    0,                      								// A0 (TIM1_BRK)
    0,                      								// A4 (TIM1_UP)
    0,                      								// A8 (TIM1_TRG_COM)
    0,                      								// AC (TIM1_CC)
    0,                      								// B0 (TIM2)
    0,                      								// B4 (TIM3)
    0,                      								// B8 (TIM4)
    0,                      								// BC (I2C1_EV)
    0,                      								// C0 (I2C1_ER)
    0,                      								// C4 (I2C2_EV)
    0,                      								// C8 (I2C2_ER)
    0,                      								// CC (SPI1)
    0,                      								// D0 (SPI2)
    0,                      								// D4 (USART1)
    0,                      								// D8 (USART2)
    0,                      								// DC (USART3)
    EXTI15_10_handler,       								// E0 (The target for GPIOC15)
};

static const uint16_t seven_seg_decimal_digits[10] = {
    0x00EE, // 0
    0x0088, // 1
    0x00D6, // 2
    0x00DC, // 3
    0x00B8, // 4
    0x007C, // 5
    0x007E, // 6
    0x00C8, // 7
    0x00FE, // 8
    0x00FC  // 9
};

static const uint16_t seven_seg_units_digits[10] = {
    0x02E3, // 0
    0x0021, // 1
    0x0362, // 2
    0x0163, // 3
    0x01A1, // 4
    0x01C3, // 5
    0x03C3, // 6
    0x0061, // 7
    0x03E3, // 8
    0x01E3  // 9
};

// Los vectores de arriba tienen los bits necesarios para generar cada número de 0 a 9 usando sus respectivos GPIO
// Por conveniencia, cada número está en su posición, para poder mostrar el número N como seven_seg_units_digits[N]
// o  seven_seg_decimal_digits[N]

uint32_t read_gpioc15_input_data(void)
{
    return (DEVMAP->GPIOs[GPIOC].REGs.IDR >> 15) & 0x1;  // Devuelve 0 o 1
}

void set_gpioc15_as_input_rest_as_output(void)
// El GPIOC15 se usa para el Echo que recibe el dato de regreso de la onda, por lo tanto lo necesitamos en INPUT
// EL GIPOC14 se usa para el trigger 
{	    

	DEVMAP->RCC.REGs.APB2ENR |= (1 << 4);                   // Enable GPIOC clock.

	DEVMAP->GPIOs[GPIOC].REGs.CRL  = 0x33333333;            // Make low GPIOC output
	DEVMAP->GPIOs[GPIOC].REGs.CRH  = 0x83333333;            // Make high GPIOC output, // by chatgpt
	//DEVMAP->GPIOs[GPIOC].REGs.CRH  = 0x43333333;            // Make high GPIOC output
	DEVMAP->GPIOs[GPIOC].REGs.ODR &= ~(1 << 14); 			// Initialize GPIOC 14 low 
}


void set_gpiob_ports_as_output(void)
// Los GPIOB 0-1 y 4-8 se usan para el 7 segmentos de las unidades
{	    

	DEVMAP->RCC.REGs.APB2ENR |= (1 << 3);                   // Enable GPIOB clock.

	DEVMAP->GPIOs[GPIOB].REGs.CRL  = 0x33333333;            // Make low GPIOB output
	DEVMAP->GPIOs[GPIOB].REGs.CRH  = 0x33333333;            // Make high GPIOB output
}

void set_gpioa_ports_as_output(void)
// Los GPIOA 1-7 se usan para el 7 segmentos de las decenas
{	    
    DEVMAP->RCC.REGs.APB2ENR |= (1 << 2);                   // Enable GPIOA clock.

	DEVMAP->GPIOs[GPIOA].REGs.CRL  = 0x33333333;            // Make low GPIOC output
	DEVMAP->GPIOs[GPIOA].REGs.CRH  = 0x33333333;            // Make high GPIOC output
}

void turn_on_all_display_leds(void)
{	    
	DEVMAP->GPIOs[GPIOA].REGs.ODR = 0x000000FF;
	DEVMAP->GPIOs[GPIOB].REGs.ODR = 0x0000FFFF;
}

void set_decimal_display_digit(int digit)
// Función que setea un digito en el 7 segmentos de las decenas
{
	if (digit < 0) {
		digit = 0;
	}
	else if (digit > 9){
		digit = 9;
	}
	
    DEVMAP->GPIOs[GPIOA].REGs.ODR = seven_seg_decimal_digits[digit];
}

void set_unit_display_digit(int digit)
// Función que setea un digito en el 7 segmentos de las unidades
{
    if (digit < 0) {
		digit = 0;
	}
	else if (digit > 9){
		digit = 9;
	}

    DEVMAP->GPIOs[GPIOB].REGs.ODR = seven_seg_units_digits[digit];
}

void set_systick_to_1us(void)
{
	CTX->SYSTICK.REGs.RVR = 8;							// Set tick time to systick freq/100000 = 8e6/100000 = 8e1, therefore happening once every 10us 
	CTX->SYSTICK.REGs.CSR  = 0x00000;						// Clear register 
	CTX->SYSTICK.REGs.CSR |= (1 << 2);						// Clear /8 clock speed divide, if needed set to 0
	CTX->SYSTICK.REGs.CSR |= (0 << 1);						// Disable interrupt
	CTX->SYSTICK.REGs.CSR |= (1 << 0);						// Enable SysTick	
	CTX->SYSTICK.REGs.CVR = 0;	
}

void set_systick_to_10us(void)
{
	CTX->SYSTICK.REGs.RVR = 80;							// 8MHz × 10µs = 80 ticks per period
	CTX->SYSTICK.REGs.CSR  = 0x00000;						// Clear register 
	CTX->SYSTICK.REGs.CSR |= (1 << 2);						// Clear /8 clock speed divide, if needed set to 0
	CTX->SYSTICK.REGs.CSR |= (0 << 1);						// Disable interrupt
	CTX->SYSTICK.REGs.CSR |= (1 << 0);						// Enable SysTick
	CTX->SYSTICK.REGs.CVR = 0;	
}

uint32_t read_systick_bit16(void)
{
    return (CTX->SYSTICK.REGs.CSR >> 16) & 0x1;  // Devuelve 0 o 1
	
}

void wait_for_at_least_2_seconds(void){
	int reads = 0; 
	while(1){
		if(read_systick_bit16() == 1){
			if(reads >= 200000){
				return;
			}
			reads++;
		}
	}
}

void raise_trigger_for_at_least_10_us(void){
	//Systick works at 10_us;
	DEVMAP->GPIOs[GPIOC].REGs.ODR |= (1 << 14);// Raise trigger
	int read_already = 0;
	while(1){
		if(read_systick_bit16() == 1){
			if(read_already == 0){
				read_already = 1;
				continue;
			}
			DEVMAP->GPIOs[GPIOC].REGs.ODR &= ~(1 << 14); // Lower trigger
			return;
		}
	}
}

void raise_trigger_for_10_us(void){
	//Systick works at 10_us;
	DEVMAP->GPIOs[GPIOC].REGs.ODR |= (1 << 14);// Raise trigger
	while(1){
		if(read_systick_bit16() == 1){
			DEVMAP->GPIOs[GPIOC].REGs.ODR &= ~(1 << 14); // Lower trigger
			return;
		}
	}
}

void display_distance_on_displays(float distance_in_cm){
	// Dado un número, se lo muestra en los displays
	// Notar que recibe float porque es lo que esperamos de la distancia, dado que SOUND_SPEED va con coma
	int int_distance = (int) distance_in_cm;

	if (int_distance > 99){
		int_distance = 99;
	}
	// Se deja en 99 la distancia máxima

	int units = int_distance % 10; 
	int tens = (int_distance / 10) % 10;
	set_decimal_display_digit(tens);
	set_unit_display_digit(units);
}

void cycle_digits(void)
{
	// Función para debugear
	float number = 0;
	int reads = 0;
	uint32_t bit_16;

	while(1){
		bit_16 = read_systick_bit16();
		if (bit_16 == 1){
			if (reads == 99999) {
				// Está puesto con reads = 99999 porque se usó para generar cambios cada 1 segundo,
				// Y para usar esta función se seteaba el systick en 10us
				display_distance_on_displays(number);
				if (number==99){
					number = 0;
				}
				else {
					number++;
				}
				reads = 0;
			}
			else{
				reads++;
			}
			
		}
	};
}

void wait_for_gpioc15_to_be_low(void){
	while(read_gpioc15_input_data() == 1){}
	return;
}

void wait_for_gpioc15_to_be_high(void){
	while(read_gpioc15_input_data() == 0){}
	return;
}

void config_exti_for_gpioc15(void){
	APB2BENR |= (1<<4);//habilito gpioc
    APB2BENR |= (1<<0); //Enable AFIO clock
	AFIO_EXTICR4 = 0x0000; //Reset
	AFIO_EXTICR4 = 0x2000; //Map GPIOC15 to EXTI15
	
	EXTI_RTSR = (1 << 15); //flanco acendente 
    EXTI_FTSR = (1 << 15); //flanco decendente
	EXTI_IMR = (1 << 15); // MR0 = 1 (not masked)
    ENA_IRQ(EXTI_15);
}

int exti15_toggle = 0;

void EXTI15_10_handler(void){
	exti15_toggle = !exti15_toggle;
	CLR_IRQ(EXTI_15);
}

const float SOUND_SPEED = 0.343f; // In cm/10us

int main(void)
{
	int high_reads;
	float distance_in_cm;
	
	set_gpioa_ports_as_output();
	set_gpiob_ports_as_output();
	set_gpioc15_as_input_rest_as_output();
	// - El GPIOA (1 a 7) corresponde a los pines del 7 segmentos de las decenas
	// - El GPIOB (0,1 y 4 a 8) corresponde a los pines de los 7 segmentos de las unidades
	// - El GPIOC 14 fue usado de output para el TRIGGER (Que se usa para marcar la creación de una onda)
	// - El GPIOC 15 fue el único input, usado para recibir la señal ECHO que está en alto mientras la onda 
	// va y vuelve.
	
	set_systick_to_10us();
	// El systick en 10us permite generar un trigger de 10us fácilmente, que es lo que necesita el sensor
	// Intenté bajarlo a 1us pero era inconsistente el timing usando polling.

	//turn_on_all_display_leds(); 
	// Función que prende todos los leds de ambos 7 segmentos. Útil para testear las conexiones
	
	//cycle_digits(); 
	// Función que hace un conteo cada 1 segundo, me fue util para verificar el timing del systick
	
	
	/* EXTI BLOCK - FALLANDO

	Como punto de mejora traté de usar interrupciones por flanco ascendente y descendente en vez de
	polling puro para capturar la duración de la onda, pero no funcionó.

	config_exti_for_gpioc15();
	exti15_toggle = 0;
	raise_trigger_for_at_least_10_us();
	wait_for_gpioc15_to_be_high();
	
	float cycles = 0;
	while(exti15_toggle==1){
		cycles ++;
	}
	display_distance_on_displays(cycles);
	*/


	/* TEST BLOCK - MOSTRAR 1 LECTURA

	Bloque de testeo, útil al inicio del proyecto

	raise_trigger_for_at_least_10_us();
	wait_for_gpioc15_to_be_high();
	CTX->SYSTICK.REGs.CVR = 0; // reset counter and clear stale COUNTFLAG
	int reads = 0;
	float cycles = 0;
	while(read_gpioc15_input_data() == 1){
		cycles ++;
		if (read_systick_bit16() == 1){
			reads++;
		}
	}
	display_distance_on_displays(cycles);
	*/

	while(1){
		//wait_for_at_least_2_seconds(); 
		// Inicialmente pensé que iba a necesitar esperar entre mediciones y por eso tenía
		// la función wait_for_at_least_2_seconds, pero no fue necesario.
		
		if (read_gpioc15_input_data() != 0) {
			continue;
		}
		// Este while me aseguraba que un nuevo cíclo de medición no se superpusiera con el anterior,
		// Dado que el GPIOC15 estaba conectado el ECHO (receptor)
		
		high_reads = 0;
		
		raise_trigger_for_10_us(); 
		// Levantar el PIN de Trigger (GPIOC14) por 10 segundos hace que comience el proceso de emisión de una
		// onda de ultra sonido función 
		
		wait_for_gpioc15_to_be_low(); 
		// Técnicamente GPIOC15 está garantizado de ser 0 en este punto, pero igualmente agregué esta función
		// para cubrirme ante algun caso de borde. 

		wait_for_gpioc15_to_be_high();
		// Cuando se recibe una señal en 1, es momento de empezar a medir el tiempo en el cual permanece en 1 
		
		while(read_gpioc15_input_data() == 1){
			if (read_systick_bit16() == 1){
				high_reads++;
			}
		}
		// Este bloque mide usnado polling cuánto tiempo está en alta el pin de ECHO, osea cuánto tiempo tarda la onda
		// en ir y volver. Cada lectura se toma cada 10us, gracias al ResetValue del systick. Por ende 
		// la variable "high_reads" tendrá la cantidad de 10us de duración de la onda 
		// Ejemplo: si high_reads = 15, entonces la onda tardó 150us.

		distance_in_cm = SOUND_SPEED * high_reads / 2; 
		// Sabiendo la velocidad del sonido y el tiempo de recorrido podemos calcular la distancia usando MRU
		// Notar que hay que dividir por 2 el resultado, porque la onda viaja de ida y de vuelta.

		display_distance_on_displays(distance_in_cm);
	}
	
	return 0;
}
