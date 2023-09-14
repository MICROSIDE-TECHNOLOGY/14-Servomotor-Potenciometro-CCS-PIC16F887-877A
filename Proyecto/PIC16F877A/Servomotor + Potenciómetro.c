/************************************************************************************************
Company:
Microside Technology Inc.
File Name:
Servomotor + Potenciometro.c
Product Revision  :  1
Device            :  X-TRAINER
Driver Version    :  1.0
************************************************************************************************/

/*
---------------------------------------------------------------------------
Controlar la posición de un servomotor por medio de un potenciometro
utilizando los modulos PWM y ADC
---------------------------------------------------------------------------
*/

#include <16F877A.h> //Incluye el microcontrolador con el que se va a trabajar
#DEVICE ADC = 10     // Configura el ADC para usar resolución de 10 bits (1024)
#include "Servo.h"   // Librería para controlar 1 servo (Utiliza Timer1)

int16 valor_ADC;     // Variable para guardar la entrada analógica
int posicion;        // Variable para ajustar la posición dle servo

// Escala el valor de una entrada de un rango a uno diferente
double map( float value, float fromLow, float fromHigh, float toLow, float toHigh );

void main( void )
{
    set_tris_c( 0xFB );                                    // C2 salida de pulsos
    setup_servo( PIN_C2 );                                 // Configura el PIN C2 como el servo
    setup_adc_ports( AN0 );                                // Configuracion deL canal ADC en A0
    setup_adc( ADC_CLOCK_DIV_8 );                          // Configura oscilador para la conversión
    set_adc_channel( 0 );                                  // Conversion analogica por canal 0

    while ( 1 ) {
        valor_ADC = read_adc();                            // Lectura del potenciometro
        posicion = (int)map( valor_ADC, 0, 1024, 0, 180 ); // Obtiene la posición en grados
        set_servo_angle( posicion );                       // Actualiza la posición del servo
    }
}

double map( float value, float fromLow, float fromHigh, float toLow, float toHigh )
{
    return ( ( ( ( value - fromLow ) * ( toHigh - toLow ) ) / ( fromHigh - fromLow ) ) + toLow );
}