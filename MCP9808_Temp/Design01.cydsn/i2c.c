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
#include <I2C.h>

uint8 Readtemp(uint8 temp)
{
  uint8 write_buf[1] = {0};
  uint16 result = 0;
  uint32 time = 0x10;
  int i = 0;
  uint8 upper,lower = 0;
  uint8 Read_Buf[2]= {0};
  write_buf[0] = temp;  

  I2C_1_I2CMasterWriteBuf(TEMP_ADDR, (uint8 *)write_buf , 1 , I2C_1_I2C_MODE_NO_STOP);
  while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT)==0){}
         
  I2C_1_I2CMasterReadBuf(TEMP_ADDR, (uint8 *) Read_Buf , 2 ,I2C_1_I2C_MODE_REPEAT_START);     
  while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_RD_CMPLT) == 0){}
        
  I2C_1_I2CMasterClearReadBuf();
         
          while( i != 2)
          {
            switch (i)
            {                
             case 0: upper = Read_Buf[i]; i++;break; 
             case 1: lower = Read_Buf[i]; i++;break;
             default: ;            
            }
          }       
          i = 0;
        
        //if ((upper & 0x8) == 0x80){ //TA ³ TCRIT
        //}
        //if ((upper & 0x4) == 0x40){ //TA > TUPPER
        //}
        //if ((upper & 0x2) == 0x20){ //TA < TLOWER
        //}
        
        upper = upper & 0x1F; //Clear flag bits
        
            if ((upper & 0x10) == 0x10)
            { //TA < 0°C
            upper = upper & 0x0F; //Clear SIGN
            temp = 256 - ((upper * 16) + (lower / 16));
            }
                else //TA ³ 0°C
                {
                temp = ((upper * 16) + (lower / 16));
                }
  return temp;
}

/* [] END OF FILE */
