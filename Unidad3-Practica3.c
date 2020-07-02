#include <16f877a.h> //Libreria para el PIC16G877A
#fuses hs,nowdt
#use delay(clock=20M)

int8 segmento[16] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 103, 119, 127, 57, 63, 121, 113}; //Arreglo
int8 i;

void main()
{
   set_tris_b(0b00000000);
   output_b (segmento[0]);
   
   while(true)
   {
      for(i=0; i<16; i++)
      {
         output_b (segmento[i]); //Configurando la salida del PIC
         delay_ms(350);  //Le asignamos un retardo.
      }
   }
}
