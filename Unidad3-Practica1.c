#include <16f877a.h>
#fuses hs,nowdt      //xt para oscilador 4MHZ, hs para osc>4MHZ 
#use delay (clock=20M)

void main()
{
   output_low(pin_b0); //iniciar el pin_b0 en logico (led apagado)
   while(true)
   {
      output_high(pin_b0);    //enciende el led.
      delay_ms(10);         //Espera 1 segundo.
      output_low(pin_b0);     //apaga el led.
      delay_ms(20);        //espera 2 segundos.
   }
}
