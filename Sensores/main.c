#include <main.h>

#fuses nowdt,noprotect,nolvp,nodebug,xt
#include <lcd.c>
#include <math.h>
#use standard_io(B)
#use fast_io(E)
#include <string.h>
#include <kbd4x4.c>

char k;

int num=0;
char clave_entrada[] = "1111";
char clave [4];
void main()

{
setup_adc(adc_clock_internal);
setup_adc_ports(all_analog);
SET_TRIS_D(0xFF);
SET_TRIS_B(0xFF);
SET_TRIS_C(0xFF);



setup_timer_2(t2_div_by_16,155,1);
setup_ccp1(ccp_pwm);


int8 a;
int8 temp;
float valor_a;
float pot;
lcd420_init();




kbd_init();
port_b_pullups(true);




int8 pwm= (temp*625)/1024;

//625/1024
   while(TRUE)
   {
 
   

      if(input(PIN_C5)==1){         //Sensor Temperatura
   while(input(PIN_C5)==1);
   delay_ms(20);

      while(input(pin_C6)!=1){
         set_adc_channel(0);
         delay_us(20);
          a=read_adc();
         temp=a*0.4882;
      
    
         lcd_gotoxy(2,1);
         printf(lcd_putc,"La temp \nes: %u C",temp);
         delay_us(20);

         switch(temp){
              case 25:        set_pwm1_duty(0); 

              case 29:       delay_us(20);
                             set_pwm1_duty(pwm); // alarma
            
      } 
      
      output_low(pin_b0);
      


if (temp>30){
      lcd_putc('\f');
     lcd_gotoxy(1,1);
      lcd_putc("INGRESAR CLAVE");
num = 0;
            while(num<4){
                  k=kbd_getc();
                  if(k != 0){
                  clave[num]=k;
                  num++;
                  lcd_gotoxy(num+1,2);
                  lcd_putc(k);
            }
         }
      delay_ms(150);

if(strstr(clave , clave_entrada)){
      lcd_putc('\f');
      lcd_gotoxy(1,1);
      lcd_putc(" clave correcta");

  delay_ms(100);
      lcd_gotoxy(1,2);
      lcd_putc(" Adelante!");
delay_ms(150);



lcd_putc('\f');
lcd_gotoxy(1,2);
printf(lcd_putc,"La temp \nes: %u C",temp);
delay_ms(2000);

}
else {
      output_high(PIN_E1);
      output_low(PIN_E0);
      lcd_putc('\f');
      lcd_gotoxy(1,1);
      lcd_putc("  clave erronea");
  delay_ms(150);



  } 
}
 } 


 }





      if(input(PIN_C6)==1){         //Sensor Potenciometro
   while(input(PIN_C6)==1);
delay_ms(20);
      while(input(pin_C5)!=1){
         set_adc_channel(1);
         delay_us(20);

          valor_a=read_adc();

         pot=(valor_a*32.2);
      
    
         lcd_gotoxy(2,1);
         printf(lcd_putc,"el grado \nes: %F3.2",pot);
         delay_us(20);

         switch(temp){
              case 25:        set_pwm1_duty(0); 

              case 29:       delay_us(20);
                             set_pwm1_duty(pwm); // alarma
            
      } 
      
      output_low(pin_b0);
      


if (pot>30){
      lcd_putc('\f');
     lcd_gotoxy(1,1);
      lcd_putc("INGRESAR CLAVE");
num = 0;
            while(num<4){
                  k=kbd_getc();
                  if(k != 0){
                  clave[num]=k;
                  num++;
                  lcd_gotoxy(num+1,2);
                  lcd_putc(k);
            }
         }
      delay_ms(150);

if(strstr(clave , clave_entrada)){
      output_high(PIN_E0);
      output_low(PIN_E1);
      lcd_putc('\f');
      lcd_gotoxy(1,1);
      lcd_putc(" clave correcta");

  delay_ms(100);
      lcd_gotoxy(1,2);
      lcd_putc(" Adelante!");
delay_ms(150);


lcd_gotoxy(1,1);
lcd_putc('f');
lcd_gotoxy(1,2);
lcd_putc('f');
printf(lcd_putc," es: %f3.2",pot);
delay_ms(2000);

}
else {
      output_high(PIN_E1);
      output_low(PIN_E0);
      lcd_putc('\f');
      lcd_gotoxy(1,1);
      lcd_putc("  clave erronea");
  delay_ms(150);



  } 
}
 } 


 }



} }



