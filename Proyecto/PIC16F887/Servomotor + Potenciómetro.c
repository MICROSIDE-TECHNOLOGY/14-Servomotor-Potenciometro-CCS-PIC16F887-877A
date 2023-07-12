/*
AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.
FECHA: JUNIO 2019
*/

/*
---------------------------------------------------------------------------
Controlar la posici�n de un servomotor por medio de un potenciometro
utilizando los modulos PWM y ADC
---------------------------------------------------------------------------
*/

#include <16F887.h>                            //Incluye el microcontrolador con el que se va a trabajar 
#DEVICE ADC=10                                   //Configura el ADC
#use delay(clock=20Mhz, crystal)                //Tipo de oscilador y frecuencia dependiendo del microcontrolador 

 
int16 Duty;                                     //variable para ajustar el valor del PWM
int1 SUBE;

#int_TIMER0

void TIMER0_isr()

{

output_high(PIN_C2);                          
SUBE=1;
set_timer0(10000);                             

}

void main()

{

  setup_oscillator(OSC_8MHZ);                    //Configura oscilador interno
  set_tris_c (0xFB);                             // C2 salida de pulsos
  setup_timer_0 (T0_INTERNAL|T0_DIV_4);
  enable_interrupts (int_TIMER0) ;
  enable_interrupts (GLOBAL) ;
  setup_adc_ports (sAN0);                        //configuracion deL canal ADC en A0
  setup_adc (ADC_CLOCK_DIV_8);                  //Configura oscilador para la conversi�n
  set_adc_channel (0);                          //conversion analogica por canal 0

    while(1)

         {

                if (SUBE == 1)

               {
                    delay_us (DUTY);
                    output_low (PIN_C2) ;
                    SUBE = 0;
                 }

 

                  if (SUBE == 0)

                      {
                          DUTY = read_adc ();             //lectura del potenciometro
                          DUTY = DUTY * 2;                //ajuste de rango
                          DUTY += 500;
                       }

                           while (SUBE == 0) ;
                }

}
