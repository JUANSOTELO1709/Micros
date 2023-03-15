#include <16f877a.h>       // incluir libreria de el pic utilizado


#fuses HS,NOWDT,NOPROTECT,NOPUT,NOLVP,BROWNOUT        // fusibles estandares

#use fast_io(A)
#use fast_io(b)

#define  ld0     PIN_A0 
#define  ld1      PIN_A1  
#define  ld2      PIN_A2 
#define  ld3       PIN_A3  
#define  ld4      PIN_A4  


int boton1;
int boton2;

void grupo1();                                  //prototipos
void grupo2();


void main(){                        //funcion que lee todo codigo para generar en el pic

set_tris_a(0b11111111);
set_tris_b(0b00000000);


while(true){

output_low(ld0);
output_low(ld1);
output_low(ld2);
output_low(ld3);
output_low(ld4);



//if(input(PIN_A5)==1){   
 //while(input(PIN_A1)==1){
 //}
//}


//else
//boton1=0;

//if(boton1==1) {
//output_high(PIN_A2);
//output_high(PIN_a1);
//}
//else
//output_low(PIN_A2);
//output_low(Pin_a1);


}



}



void grupo1(){
output_high(ld0);
output_low(ld1);
output_high(ld2);
output_low(ld3);
output_high(ld4);
}


void grupo2(){
output_high(ld0);
output_high(ld1);
output_high(ld2);
output_high(ld3);
output_high(ld4);
}
