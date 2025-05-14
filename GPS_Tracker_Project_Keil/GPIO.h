#ifndef GPIO
#define GPIO

void delayMs(int n);




#define LCD_Data_ddr GPIO_PORTB_DIR_R                            
#define LCD_Data_port GPIO_PORTB_DATA_R
#define LCD_Control_ddr GPIO_PORTC_DIR_R                             
#define LCD_Control_port GPIO_PORTC_DATA_R
#define RS_pin 4  //PC4
#define E_pin 5		//PC5
#define RW_pin 6	//PC6

//void Init_PortF(void);
void PORTB_init(void); //initializes portB      as digital i/o
void PORTC_init(void); //initializes PC4 -> PC6 as digital i/o  (didnt use 0-2 bec JTAG)
void PORTE_init(void);

//void red_led(char state);
//void green_led(char state);
//void blue_led(char state);







#endif

