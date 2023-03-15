

#include <16f877a.h>



#fuses HS,NOWDT,NOPROTECT,NOPUT,NOLVP,BROWNOUT
#use delay(clock=4M)
#use standard_io(D)
#use standard_io(C)
#use fast_io(A)




   #define TC_CLK     PIN_C3            //edit these pins as necessary 
   #define TC_CS      PIN_C0 
   #define TC_DATA    PIN_C4 


#define LCD_DB4  PIN_D4                     // Pines de la pantalla LCD 2004
#define LCD_DB5  PIN_D5
#define LCD_DB6  PIN_D6
#define LCD_DB7  PIN_D7
#define LCD_RS   PIN_D2
#define LCD_E    PIN_D3


#include <LCD_20X4.c>                       // Libreria para el manejo de la LCD 20x4
#include <math.h>                            // libreria mate
#include <kbd4x4.c>           // libreria teclado
#include <string.h>        //libreria comparaciones
#include <max6675.c>             //libreria termocupla


char cara[8] = {0x00,0x0A,0x0A,0x0A,0x00,0x11,0x0E,0x00};
char grado[8] = {0x07,0x05,0x07,0x00,0x00,0x00,0x00,0x00};
char bota [8] =  {0b00000001, 0b00000011, 0b00000111, 0b00000111, 0b00000111,0b0000111,0b00001101,0b00011101};
char k;
int num=0;

                  //variable

int cont=0;
int pos=0;
int sensor1=0;
int sensor2=0;
int sensor3=0;
int sensor4=0;
char clave [4];
char clavem [1];
char clave_a[] = "A";   // para ingresar a opcion a
char clave_b[] = "B";   // para ingresar b
char clave_c[] = "C";   // para ingresar c
char temperatura_entrada[] ="#";  //entrada a temperatura

int menu=0;

int dato_temperatura=0;


void termocupla();
void botones();


void main()
{


      lcd_init();       //inicia lcd
      kbd_init();       //inicia tecaldo
      port_b_pullups(true);      //oficializa pullups

//setup_timer_2(t2_div_by_16,155,1);        //estabiliza timer 2
//setup_ccp1(ccp_pwm);                      // configura pwm


//setup_adc(adc_clock_internal);            //inicia salidas de A en adc
//setup_adc_ports(all_analog);              // establecer todo puerto A en enalogo
SET_TRIS_D(0xFF);          //D como salidas  
SET_TRIS_B(0xFF);           //B como salidas          
SET_TRIS_C(0xFF);          //C como salidas 
SET_TRIS_A(0x00);          //C como Entradas 




 CGRAM_position(0);
 CGRAM_create_char(cara);

 CGRAM_position(1);
 CGRAM_create_char(grado);

 CGRAM_position(2);
 CGRAM_create_char(bota);



   while(true)
   {
      num=0;
      pos=0;

      switch (menu) {            //generar menu con #
    case 0:  
              //menu caso 1 (Temperatura)
      lcd_putc('\f');
      lcd_gotoxy(6,2);
      CGRAM_putc(2);
      lcd_putc("buen dia ");
      CGRAM_putc(0);
      delay_ms(200);  
      menu++;
           break;

    case 1:          //menu caso 2 (Medicion)
 while(input(menu)==1);
      while(input(menu)!=1){
         lcd_putc('\f');
         lcd_gotoxy(1,1);
         lcd_putc("cont");
         lcd_gotoxy(5,1);


         lcd_gotoxy(1,2);
         lcd_putc("Temp:");
      lcd_gotoxy(8,3);
      printf(lcd_putc,"%01.2f%cC\r\n", do_everything(),0xB0);

        lcd_gotoxy(17,2);
    CGRAM_putc(1);
         lcd_gotoxy(1,3);
         lcd_putc("Posicion:");


if(sensor1==1){
    lcd_gotoxy(11,3);
         lcd_putc("34-35");


}
if(sensor2==1){
    lcd_gotoxy(11,3);
         lcd_putc("36-37");
}
if(sensor3==1){
    lcd_gotoxy(11,3);
         lcd_putc("38-39");
}


         lcd_gotoxy(1,4);
         lcd_putc("Presione # para temp");


while(num<1){
   k=kbd_getc();
   if(k != 0){
           
          clavem[num]=k;
          num++;
         lcd_gotoxy(10,1);
         lcd_putc(k);

}
}

if(strstr(clavem, clave_a)){             //posicion 34/35 , A
menu =3;
}
if(strstr(clavem, clave_b)){               //posicion 36/37     B
menu=4;

}
if(strstr(clavem, clave_c)){                  //posicion 38/39  C
menu=5;
}
if(strstr(clavem, temperatura_entrada)){
      menu=6;
      }
 break;


      }
 case 3:                // posicion 1
       lcd_putc('\f');
      lcd_gotoxy(7,1);
      lcd_putc("BUSCANDO");
      sensor1=0;
      sensor2=0;
      sensor3=0;
      sensor4=0;                                                                                                                                   //posicion 1
if(pos<2){
      output_low(pin_c1);     
      output_high(pin_c2);          //empieza a bajar el motor si la posicion es distinta a 0, siempre baja
 }   
if(pos>2){
      output_low(pin_c1);     
      output_high(pin_c2);          //empieza a bajar el motor si la posicion es distinta a 0, siempre baja
}




if(input(PIN_A0)==1){         //si llega a accionarse el sensor A0 el motor se detiene
   while(input(PIN_A0)==1){
      sensor1=1;           //se suma sensor 1, aclarando que esta en la posicion 1
      pos=1;
  }
}
if(sensor1==1){
      output_low(pin_c1);
      output_low(pin_c2);           //se detiene el motor
      }
if(sensor1==1){
            output_low(pin_c1);
      output_low(pin_c2);   
      menu=1;
      delay_ms(200);
}
      delay_ms(200);

 break;


 case 4:                            // posicion 2


      lcd_putc('\f');
      lcd_gotoxy(7,1);
      lcd_putc("BUSCANDO");
      lcd_gotoxy(7,2);
      lcd_putc("36-37");;
      sensor1=0;
      sensor2=0;
      sensor3=0;
      sensor4=0;                                                                                                                                   //posicion 1
if(pos<2){
      output_low(pin_c1);     
      output_high(pin_c2);          //empieza a bajar el motor si la posicion es distinta a 0, siempre baja
 }   
if(pos>2){
      output_low(pin_c1);     
      output_high(pin_c2);          //empieza a bajar el motor si la posicion es distinta a 0, siempre baja
}




if(input(PIN_A1)==1){         //si llega a accionarse el sensor A0 el motor se detiene
   while(input(PIN_A1)==1){
      sensor2=1;           //se suma sensor 1, aclarando que esta en la posicion 1
      pos=2;
  }
}
if(sensor2==1){
      output_low(pin_c1);
      output_low(pin_c2);           //se detiene el motor
      }
if(sensor2==1){
            output_low(pin_c1);
      output_low(pin_c2);   
      menu=1;
      delay_ms(200);
}
      delay_ms(200);
 break;


 case 5:                            //posicion 3
      sensor1=0;
      sensor2=0;
      sensor3=0;
      sensor4=0;

if (pos<4){
      output_low(pin_c1);     
      output_high(pin_c2);          //empieza a bajar el motor si la posicion es distinta a 0, siempre baja
}
      lcd_putc('\f');
      lcd_gotoxy(7,1);
      lcd_putc("posicion 4");
      
                                                                                                                                                //posicion 3
if(input(PIN_A2==1)){         //si llega a accionarse el sensor A3 el motor se detiene
   while(input(PIN_A2)==1){
sensor3=1;
pos=3;

 }}


if(sensor3==1){
      output_low(pin_c1);
      output_low(pin_c2);
 }

 if (sensor3==1){
      menu=1;
      delay_ms(200);
 }


 break;


 case 6:

      lcd_putc('\f');
         lcd_gotoxy(1,1);
         lcd_putc("INGRESE GRADOS");
          CGRAM_putc(1);
         lcd_gotoxy(1,2);
         lcd_putc("3 digitos");



while(num<3){
   k=kbd_getc();
   if(k != 0){
           
          clave[num]=k;
          num++;
         lcd_gotoxy(num+1,4);
         lcd_putc(k);
dato_temperatura=k;
}

if(dato_temperatura!=0){
menu=1;
}

}

   delay_ms(100);



}}

   }
















