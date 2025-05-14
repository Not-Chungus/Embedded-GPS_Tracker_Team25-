#ifndef UART_H    // Change to a unique name like UART_H to avoid redefinition
#define UART_H



// Function prototypes for UART initialization and character handling
void UART2_init(void);                    // Function to initialize UART1
int UART2_IsCharAvail(void);              // Check if a character is available in UART
char UART2_GetChar(void);                 // Get a character from UART
void UART0_init(void);

void U0_print_char_to_PC(char c);
char U0_read_char_fromPC(void);
void U0_print_string_toPC(char* string);



#endif // UART_H
