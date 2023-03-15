#include <16f877a.h>
#device ADC=10

#fuses HS,NOWDT,NOPROTECT,NOPUT,NOLVP,BROWNOUT
#use delay(clock=4M)
#use standard_io(D)
#use standard_io(C)
#use fast_io(E)

#include <lcd.c>                       // Libreria para el manejo de la LCD 20x4
#include <math.h>                            // libreria mate
#include <kbd4x4.c>           // libreria teclado
#include <string.h>        //libreria comparaciones


char k;
int num=0;


char clave_subida[] = "1";   // para aumentar al menu
char subida [1];

char clave_bajada[] = "2";    // para disminuir al menu
char bajada [1];

char  clave_ok[] = "#";    // para acceder
char ok [1];

char clave_siete[]= "A";      // acceder a menu 7oz
char siete[1];

char clave_doce[]= "B";       //acceder a menu 12oz
char doce[2];

int late=0;
int capuchino=0;
int expreso=0;

int menu=0;



long a;
long temp;
int temp_encendido=35;



void electro();
void lat();
void capuchi();
void exp();

void main()
{

setup_adc(adc_clock_internal);            //inicia salidas de A en adc
setup_adc_ports(all_analog);              // establecer todo puerto A en enalogo
         set_adc_channel(0);
      



      lcd_init();       //inicia lcd
      kbd_init();       //inicia tecaldo
      port_b_pullups(true);      //oficializa pullups



setup_timer_2(t2_div_by_16,155,1);        //estabiliza timer 2
setup_ccp1(ccp_pwm);                      // configura pwm



SET_TRIS_D(0xFF);          //D como entradas  
SET_TRIS_B(0xFF);           //B como entradas          
SET_TRIS_C(0xFF);          //C como entradas 




   while(true)
   {
     num=0;       //numero de keyboard






      
      switch (menu) {            //generar menu

    case 0:  
    num=0;
    menu=0;
    late=0;
    capuchino=0;
    expreso=0;
lcd_putc('\f');
         lcd_gotoxy(1,1);
         lcd_putc("late");
            lcd_gotoxy(10,1);
         lcd_putc("<<");


         lcd_gotoxy(1,2);
         lcd_putc("capuchino");

while(num<1){
   k=kbd_getc();
   if(k != 0){
           
          subida[num]=k;
          bajada[num]=k;
          ok[num]=k;
          num++;


}
}

delay_ms(100);

if(strstr(subida , clave_subida)){
      menu++;
delay_ms(100);
   }
   
else {
menu=1;
}

if(strstr(bajada , clave_bajada)){
      menu=2;
delay_ms(100);
   }
   
else {
menu=1;
}
    

if(strstr(ok , clave_ok)){
    lcd_putc('\f');
         lcd_gotoxy(8,1);
         lcd_putc("late");
                  late++;
delay_ms(200);
      menu=3;
delay_ms(100);

   }  
           break;

   




   
    case 1:          //menu caso 1 (seleccion)
           lcd_putc('\f');
         lcd_gotoxy(1,1);
         lcd_putc("late");

         lcd_gotoxy(1,2);
         lcd_putc("capuchino");
            lcd_gotoxy(10,2);
         lcd_putc("<<");
while(num<1){
   k=kbd_getc();
   if(k != 0){    
          subida[num]=k;
          bajada[num]=k;
          ok[num]=k;
          num++;

}
}

      if(strstr(subida , clave_subida)){
            menu=2;
            delay_ms(100);
   }

      if(strstr(bajada , clave_bajada)){
            menu--;
      delay_ms(100);
   }
if(strstr(ok , clave_ok)){
    lcd_putc('\f');
         lcd_gotoxy(8,1);
         lcd_putc("capuchino");
delay_ms(200);
      menu=3;
      capuchino++;
delay_ms(100);
   }  
delay_ms(200);
      
 break;





case 2:                    //menu 2 parte de seleccion de temperatura o posicion
          
           lcd_putc('\f');
         lcd_gotoxy(1,1);
         lcd_putc("expreso");
           
            lcd_gotoxy(10,1);
         lcd_putc("<<");


while(num<1){
   k=kbd_getc();
   if(k != 0){    
          subida[num]=k;
          bajada[num]=k;
          ok[num]=k;
          num++;
         

   }
}

if(strstr(subida , clave_subida)){
      menu=0;
delay_ms(100);
   }
   
if(strstr(bajada , clave_bajada)){
      menu=1;
delay_ms(100);
   }
 if(strstr(ok , clave_ok)){
    lcd_putc('\f');
         lcd_gotoxy(8,1);
         lcd_putc("expreso");
         expreso++;
delay_ms(200);
      menu=3;
delay_ms(100);
   }    
 delay_ms(200);




break;

case 3:
    lcd_putc('\f');
         lcd_gotoxy(1,1);
         lcd_putc("7oz = A");
         lcd_gotoxy(1,2);
         lcd_putc("12oz = B");
delay_ms(200);





while(num<1){
   k=kbd_getc();
   if(k != 0){    
          siete[num]=k;
          doce[num]=k;
          ok[num]=k;
          num++;
         lcd_gotoxy(10,1);
         lcd_putc(k);
   }
}
if(strstr(siete , clave_siete)){
menu=4;
delay_ms(100);
   }

if(strstr(doce , clave_doce)){
menu=5;
delay_ms(100);
   }
break;

case 4:
          lcd_putc('\f');
             lcd_gotoxy(1,1);
         lcd_putc("7oz");


if(late==1){



         lcd_gotoxy(10,1);
        lcd_putc("late");
         lcd_gotoxy(1,2);
         a=read_adc();
         temp=(a*0.4882);
         printf(lcd_putc,"%Lu C",temp);

         electro();
         lat();
         delay_ms(200); 
      
}


if(capuchino==1){
   late=0;



        lcd_gotoxy(10,1);
         lcd_putc("capuchino");
         delay_ms(200);
         a=read_adc();
         temp=(a*0.4882);
         printf(lcd_putc,"%Lu C",temp);
   
         electro();
         capuchi();      delay_ms(200); 
}

if (expreso==1){

late=0;
            lcd_gotoxy(10,1);
         lcd_putc("expreso");
         delay_ms(200);
         a=read_adc();
         temp=(a*0.4882);
         printf(lcd_putc,"%Lu C",temp);
   
         electro();
         exp();
      delay_ms(200); 
}



break;

case 5:
          lcd_putc('\f');
             lcd_gotoxy(1,1);
         lcd_putc("12oz");
delay_ms(100);

if(late==1){



         lcd_gotoxy(10,1);
        lcd_putc("late");
         lcd_gotoxy(1,2);
         a=read_adc();
         temp=(a*0.4882);
         printf(lcd_putc,"%Lu C",temp);
        
         electro();
         lat();
 delay_ms(200); 
      
}


if(capuchino==1){
   late=0;



        lcd_gotoxy(10,1);
         lcd_putc("capuchino");
         delay_ms(200);
         a=read_adc();
         temp=(a*0.4882);
         printf(lcd_putc,"%Lu C",temp);
      
         electro();
         capuchi();   delay_ms(200); 
}

if (expreso==1){

late=0;
            lcd_gotoxy(10,1);
         lcd_putc("expreso");
         delay_ms(200);
         a=read_adc();
         temp=(a*0.4882);
         printf(lcd_putc,"%Lu C",temp);
        
         electro();
         exp();
 delay_ms(200); 
}


break;


}
}
}






void electro()
{     
if (temp>=temp_encendido){
   SET_TRIS_e(0x00); // como salidas
   output_high(PIN_E0);
}
else 
 output_low(PIN_E0);         
}








void lat(){
   
setup_timer_2(t2_div_by_16,155,1);        //estabiliza timer 2
setup_ccp1(ccp_pwm);                      // configura pwm


      set_pwm1_duty(1500);
      delay_ms(2000);
   
      menu=0;
if(menu==0){

   set_pwm1_duty(0);
}

}







void capuchi(){
setup_timer_2(t2_div_by_16,155,1);        //estabiliza timer 2
setup_ccp1(ccp_pwm);                      // configura pwm


      set_pwm1_duty(1000);
      delay_ms(2000);
   
      menu=0;
if(menu==0){

   set_pwm1_duty(0);
}

}






void exp(){
setup_timer_2(t2_div_by_16,155,1);        //estabiliza timer 2
setup_ccp1(ccp_pwm);                      // configura pwm


      set_pwm1_duty(1300);
      delay_ms(2000);
   
      menu=0;
if(menu==0){

   set_pwm1_duty(0);
}

}