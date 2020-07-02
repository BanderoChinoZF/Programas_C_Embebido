#include <16f877a.h>
#fuses hs,nowdt
#use delay(clock=20M)

#define lcd_rs_pin pin_b0
#define lcd_rw_pin pin_b1
#define lcd_enable_pin pin_b2
#define lcd_data4 pin_b4
#define lcd_data5 pin_b5
#define lcd_data6 pin_b6
#define lcd_data7 pin_b7

#include <lcd.c> //Libreria para el control del lcd.

void main()
{
   lcd_init();
   
   while(true)
   {
      lcd_gotoxy(1,1);
      printf (lcd_putc, "HOLA MUNDO");
      delay_ms(50);
   }
}
