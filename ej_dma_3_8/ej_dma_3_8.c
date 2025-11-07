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
	EXTI_0 = 6,
};

int  main(void);
void  EXTI0_handler(void);

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
    EXTI0_handler,                                          //58
};

//  0x00002000 setea un 1 en el bit 13 y los demás en 0 (prende y apaga el led esto)
uint32_t const on_data[1] = {0x00000000}; 
uint32_t const off_data[1] = {0x00002000}; 

void load_to_dma_for_switching_board_led_status(void) {
    static uint8_t toggle = 0;  // Keeps its value between calls

    if (toggle) {
        DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CMAR = (uint32_t)on_data;
    } else {
        DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CMAR = (uint32_t)off_data;
    }

    toggle = !toggle;  // Flip between 0 and 1 each call
}

void EXTI0_handler(void){
	load_to_dma_for_switching_board_led_status();
	EXTI_PR |= (1 << 0); // Sirve para limpiar el pedido de interrupción y así salga de la interrupción
	CLR_IRQ(EXTI_0);
}

void set_gpioc_ports_as_output(void)
{	    

	DEVMAP->RCC.REGs.APB2ENR |= (1 << 4);                   // Enable GPIOC clock.

	DEVMAP->GPIOs[GPIOC].REGs.CRL  = 0x33333333;            // Make low GPIOC output
	DEVMAP->GPIOs[GPIOC].REGs.CRH  = 0x33333333;            // Make high GPIOC output
}

void set_gpioa0_as_input_rest_as_output(void)
{	    
    DEVMAP->RCC.REGs.APB2ENR |= (1 << 2);                   // Enable GPIOA clock.

	DEVMAP->GPIOs[GPIOA].REGs.CRL  = 0x33333337;            // Make low GPIOC output
    //Notar que se configura el GPIOA0 como pullup/pulldown, NO FLOTANTE
	DEVMAP->GPIOs[GPIOA].REGs.CRH  = 0x33333333;            // Make high GPIOC output
}

void config_exti_0_for_gpioa0(void){
    AFIO_EXTICR1 = 0x00; // activo interrupcion para pin A
    EXTI_RTSR = (1 << 0); //flanco acendente 
    EXTI_FTSR = (1 << 0); //flanco decendente
    EXTI_IMR = (1 << 0); // MR0 = 1 (not masked)
}

void config_dma_to_write_on_gpioc(void)
{
	DEVMAP->RCC.REGs.APB1ENR |= (1 << 0);					// Enable TIM2 clock.
	DEVMAP->RCC.REGs.AHBENR  |= (1 << 0);					// Enable DMA1 clock.

	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CNDTR = sizeof(on_data)/sizeof(uint32_t); // Transfer size
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CMAR	= (uint32_t) on_data;				 // Memory source address, inicializamos en ON
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CPAR	= (uint32_t) &DEVMAP->GPIOs[GPIOC].REGs.ODR; // Peripheral destination address

	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR  = 0;				// Reset CCR
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR &= ~(1 << 14);	// Disable memory to memory transfer on DMA1 channel 2
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (0b11 << 12); // Set DMA priority to very high
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (0b10 << 10); // Set memory transfer size to 32-bits
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (0b10 << 8);	// Set peripheral transfer size to 32-bits
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 7);		// Enable memory increment mode
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR &= ~(1 << 6);		// Disable peripheral increment mode
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 5);		// Enable circular mode
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 4);		// Read from memory

	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |= (1 << 0);		// Enable DMA

	DEVMAP->TIMs[TIM2].REGs.CR1  = 0x0000;					// Reset CR1 just in case
    //	DEVMAP->TIMs[TIM2].REGs.CR1  |= (1 << 4);				// Down counter mode
    DEVMAP->TIMs[TIM2].REGs.PSC   = (72e6/8)/(sizeof(on_data)/sizeof(on_data[0]))-1;	// fCK_PSC / (PSC[15:0] + 1)
    DEVMAP->TIMs[TIM2].REGs.ARR   = 8-1;
    DEVMAP->TIMs[TIM2].REGs.DIER |= (1 << 14);				// Trigger DMA request enable
    DEVMAP->TIMs[TIM2].REGs.DIER |= (1 <<  8);				// Update DMA request enable

    DEVMAP->TIMs[TIM2].REGs.CR1  |= (1 << 0);				// Finally enable TIM1 module
}


int main(void)
{
	// DMA code
	set_gpioc_ports_as_output();
    set_gpioa0_as_input_rest_as_output();
    config_dma_to_write_on_gpioc();
    config_exti_0_for_gpioa0();
    ENA_IRQ(EXTI_0);

	while(1){
	};

	return 0;
}
