#include <main.h>
#use standard_io(D)
#use standard_io(B)
#use fast_io(E)

#include <string.h>
#include <kbd4x4.c>

#define LCD_DB4  PIN_D4                     // Pines de la pantalla LCD 2004
#define LCD_DB5  PIN_D5
#define LCD_DB6  PIN_D6
#define LCD_DB7  PIN_D7
#define LCD_RS   PIN_D2
#define LCD_E    PIN_D3


#include <LCD_20X4.c>     
char k;


int num=0;
char clave_entrada[] = "#000000000";
char clave [8];

int menu=0;

void main()
{
   lcd_init();
   kbd_init();
   port_b_pullups(true);

      

   while(TRUE)
   {

switch (menu){
case 0:
      lcd_putc('\f');
      lcd_gotoxy(1,1);
      lcd_putc("INGRESAR CLAVE");
num = 0;
      
while(num<1){
         k=kbd_getc();
         if(k != 0){
           
          clave[num]=k;
           num++;
          lcd_gotoxy(num+1,2);
          lcd_putc(k);
               
            }
         }
      delay_ms(1500);


if(strstr(clave , clave_entrada)){
      output_high(PIN_E0);
      output_low(PIN_E1);
      lcd_putc('\f');
      lcd_gotoxy(1,1);
      lcd_putc(" clave correcta");
      menu++;

  delay_ms(100);
      lcd_gotoxy(1,2);
      lcd_putc(" Adelante!");
delay_ms(150);
}
else {
      output_high(PIN_E1);
      output_low(PIN_E0);
      lcd_putc('\f');
      lcd_gotoxy(1,1);
      lcd_putc("  clave erronea");
  delay_ms(150);

}
break;
case 1:
      lcd_putc('\f');
lcd_gotoxy(1,1);
      lcd_putc("  hola");

      
}
   }}