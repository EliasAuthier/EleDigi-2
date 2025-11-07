typedef int            int32_t;
typedef short          int16_t;
typedef char           int8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

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
volatile int flag = 0;

void EXTI0_handler(void){
    flag = 1;
    EXTI_PR |= (1 << 0); // Sirve para limpiar el pedido de interrupción y así salga de la interrupción
}

int main(void)
{
    APB2BENR |= (1<<2); //pongo un 1 en en la posicion 2, que activa el periferico A
    APB2BENR |= (1<<4);//habilito gpioc
    APB2BENR |= (1<<0); //AFIO

    GPIOC_CRH = 0x33333333; // activo todos los high de C

    GPIOA_CRL = (1<<3); // Queremos poner el pin PA0 en modo input y pull down
   // GPIOA_ODR = (0<<0); // le ponemos un cero para q sea pull down en la posicion del pin q quiero (0)

    AFIO_EXTICR1 = 0x00; // activo interrupcion para pin A
    EXTI_RTSR = (1 << 0); //flanco acendente 
    EXTI_FTSR = (1 << 0); //flanco decendente
    EXTI_IMR = (1 << 0); // MR0 = 1 (not masked)
    NVIC_ISER0 = (1 << 6); // Sería el IRQN = 6 (EXTI0)
        // EL NVIC debe ir depues de todo lo anterior

  while(1){
    if(flag)
        GPIOC_ODR ^= (1<<13);// direccion del led interno pc13 
        flag=0;
    }
return 0;}

#define SRAM_SIZE ((uint32_t) 0x00005000)
#define SRAM_BASE ((uint32_t) 0x20000000)
#define STACKINIT ((interrupt_t)(SRAM_BASE+SRAM_SIZE))

typedef void(*interrupt_t)(void);
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