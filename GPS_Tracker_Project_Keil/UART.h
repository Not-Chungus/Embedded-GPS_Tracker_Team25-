#ifndef UART_H    // Change to a unique name like UART_H to avoid redefinition
#define UART_H



// Function prototypes for UART initialization and character handling
void UART_init(void);                    // Function to initialize UART1
int UART_IsCharAvail(void);              // Check if a character is available in UART
char UART_GetChar(void);                 // Get a character from UART

#endif // UART_H
