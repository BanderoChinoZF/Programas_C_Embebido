#include <16f877a.h>
#fuses hs, nowdt
#use delay (clock=20M)

#define lcd_rs_pin pin_b0
#define lcd_rw_pin pin_b1
#define lcd_enable_pin pin_b2
#define lcd_data4 pin_b4
#define lcd_data5 pin_b5
#define lcd_data6 pin_b6
#define lcd_data7 pin_b7

#include <lcd.c>

void main()
{
   set_tris_a(0b00011);
   lcd_init();
   int x = 1;
   
      while(true)
      {
         if(input (pin_a0)==1)
         {
             do{}
             while(input (pin_a0)==1);
             x=1;
                  for(int i = 15;i>=0;i--)
                  {
                     x++;
                     lcd_gotoxy(1,1);
                     printf(LCD_PUTC, "\f");
                     lcd_gotoxy(i,2);
                     printf(lcd_putc,"MARICELA MORALES HERNENDEZ");
                     delay_ms(10);
                     printf(LCD_PUTC, "\f");
                     if (x==40)
                     {
                        break;
                     };
                  }
                  
         }
         
         if(input (pin_a1)==1)
         {
            x=1;
            do{}
            while(input (pin_a1)==1);
               for(int i = 15;i>=0;i--)
               {
                     x++;
                     lcd_gotoxy(i,1);
                     printf(lcd_putc,"LUIS ANGEL ZARAGOZA FARRERA");
                     delay_ms(10);
                     printf(LCD_PUTC, "\f");
                     if (x==47)
                     {  //Tiempo que tarda en pasar todo el nombre
                        break;
                     };
               }
        }
      }
}
