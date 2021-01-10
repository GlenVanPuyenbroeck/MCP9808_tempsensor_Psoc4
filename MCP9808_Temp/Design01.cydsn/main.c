/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <stdlib.h>
#include <project.h>
#include <I2C.h>


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    I2C_1_Start();
    UART_1_Start();
    uint8 temp = 0;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    char string[30];

        for(;;)
        {
           temp = Readtemp(TEMP_REG);  
           itoa(temp,string,10);
           UART_1_UartPutString("Temperatuur MCP9808 : ");
           UART_1_UartPutString(string);
           UART_1_UartPutString(" graden");
           UART_1_UartPutChar('\n'); 
           UART_1_UartPutChar('\r');
           CyDelay(1000);
        }
}

/* [] END OF FILE */
