#include <Arduino.h>

// Constante de aire limpio
#define CLEAN_AIR 3.6

// Valor de resistencia recomendado por datasheet
// Entre GND y Aout
#define RL 47

// Cantidad de muestras para promediar
#define CICLE_AVERAGE 500

// Valor de voltaje de alimentacion de placa
#define VCC_BOARD 5.0

// Maxima resolucion de entrada analogica
// En NodemCu:  10-bit (2^10) = obtiene valores entre 0 y 1023
#define ADC_MAX_SAMPLES 1023


/**
 * @brief Get the Resistance Air Fresh object (R0) for use in calc PPM
 * @param MQ137_PIN entrada analogica destinada a MQ137
 * 
 * @return float 
 */
float getResistanceAirFresh(const byte MQ137_PIN){
  float analog_value;
  float VRL;
  float Rs;
  float Ro;
  for (uint8_t i = 0; i < CICLE_AVERAGE; i++)
  {
    analog_value= analog_value + analogRead(MQ137_PIN);
  }
  // Obtener promedio de lecturas
  analog_value= analog_value/CICLE_AVERAGE;

  // Convertir entrada analogica a voltaje
  VRL= analog_value*(VCC_BOARD/ADC_MAX_SAMPLES);

  // Formula para obtener la resistencia del sensor en varias concentraciones de gases
  Rs= ((VCC_BOARD/VRL) -1) * RL;
  
  // Formula para obtener la resistencia del sensor en en el aire limpio
  Ro= Rs/CLEAN_AIR;

  return Ro;
}