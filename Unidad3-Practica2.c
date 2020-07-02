#include <16f877a.h>
#fuses hs,nowdt
#use delay(clock=20M)

void main()
{
   set_tris_b(0b0000000);    //Configurando el pin B son de salida
   
   /*
     set_tris_b(0b11111111);
     set_tris_b(0b11110000);
   */
   
   output_b(0b00000000);
   
   while(true)
   {
      output_b(0b00000001);
      delay_ms(10);
      output_b(0b00000011);
      delay_ms(10);
      output_b(0b00000111);
      delay_ms(10);
      output_b(0b00001111);
      delay_ms(10);
      output_b(0b00011111);
      delay_ms(10);
      output_b(0b00111111);
      delay_ms(10);
      output_b(0b01111111);
      delay_ms(10);
      output_b(0b11111111);
      delay_ms(10);
      output_b(0b00000000);
      delay_ms(10);
   }
}
