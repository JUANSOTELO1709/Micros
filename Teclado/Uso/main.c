#include <main.h>
#use standard_io(D)

#include <LCD.c>

#include <kbd4x4.c>

char k;


void main()
{
   lcd_init();
   kbd_init();
port_b_pullups(true);

   while(TRUE)
   {
      lcd_gotoxy(1,1);
      lcd_putc("Tecla:");

k=kbd_getc();

if(k != 0){
   lcd_gotoxy(8,1);
               lcd_gotoxy(8,1);
               lcd_putc(k);
               
         }
   }
}
