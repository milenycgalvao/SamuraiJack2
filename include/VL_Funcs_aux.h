#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"


#define VL_ADDRES03 0X32
#define VL_ADDRES04 0X33


#define VL_PIN03 17
#define VL_PIN04 16


Adafruit_VL53L0X VL03 = Adafruit_VL53L0X();
Adafruit_VL53L0X VL04 = Adafruit_VL53L0X();




VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;




void setID() {
  Wire.begin (21, 22);//sda, scl  

  pinMode(VL_PIN03, OUTPUT);
  pinMode(VL_PIN04, OUTPUT);
  

  // all reset
  digitalWrite(VL_PIN03, LOW); 
  digitalWrite(VL_PIN04, LOW); 
   
  vTaskDelay(10);

  // all unreset
  digitalWrite(VL_PIN03, HIGH); 
  digitalWrite(VL_PIN04, HIGH); 
   
  vTaskDelay(10);

  // activating LOX1 and resetting LOX2 
  digitalWrite(VL_PIN03, LOW ); 
  digitalWrite(VL_PIN04, LOW ); 
   

  digitalWrite(VL_PIN03, HIGH);
  digitalWrite(VL_PIN04, LOW );

  vTaskDelay(10); 
  
  if(!VL03.begin(VL_ADDRES03)) {
    Serial.println(F("Failed to boot terceiro VL53L0X"));
    while(1);
  }

  
  digitalWrite(VL_PIN04, HIGH);
  vTaskDelay(10); 
  
  if(!VL04.begin(VL_ADDRES04)) {
    Serial.println(F("Failed to boot quarto VL53L0X"));
    while(1);
  }
  
}

void printLasersTeste(){
  
  VL03.rangingTest (& measure3, false);
  VL04.rangingTest (& measure4, false);

  
  
  if(measure3.RangeStatus != 4){
    Serial.print(" | Distancia VL3 (mm): ");
    Serial.print(measure3.RangeMilliMeter);
  }else{
    Serial.println(" out of range ");
  }

  
  if(measure4.RangeStatus != 4){
    Serial.print(" | Distancia VL4 (mm): ");
    Serial.println(measure4.RangeMilliMeter);
  }else{
    Serial.println(" out of range ");
  }

}

bool enxergaLaser() {
  
  VL03.rangingTest (& measure3, false);
  VL04.rangingTest (& measure4, false);


  //if algum deles for menor que 750mm retorna true (para chamar funcao de atacar)
  //se nao falso (para chamar funcao de busca)
  if(measure3.RangeMilliMeter<750 || measure4.RangeMilliMeter<750){
    return true;
  }else{
    return false;
  }
}



int qualAtaque() {
  VL03.rangingTest (& measure3, false);
  VL04.rangingTest (& measure4, false);
  

  //se estiver vendo pelos dos cantos vai girar no proprio eixo para virar mais rapido, se ver pelos da frente vai so alinhar enquanto anda
  
  
    if(measure3.RangeMilliMeter<750 && measure4.RangeMilliMeter>=750){
      //else if ve no canto esquerdo da frente
      Serial.println("caso 3");
      Serial.print(" Distancia VL3 (mm): ");
      Serial.print(measure3.RangeMilliMeter);
      Serial.print(" | Distancia VL4 (mm): ");
      Serial.println(measure4.RangeMilliMeter);
      return 3;
    }else if(measure3.RangeMilliMeter>=750 && measure4.RangeMilliMeter<750){
      //else if ve no canto direito da frente
      Serial.println("caso 4");
      Serial.print(" Distancia VL3 (mm): ");
      Serial.print(measure3.RangeMilliMeter);
      Serial.print(" | Distancia VL4 (mm): ");
      Serial.println(measure4.RangeMilliMeter);
      return 4;
    }else if(measure3.RangeMilliMeter<100 && measure4.RangeMilliMeter<750){
      //else ve nos dois do meio ao mesmo tempo
      Serial.println("caso 5");
      Serial.print(" Distancia VL3 (mm): ");
      Serial.print(measure3.RangeMilliMeter);
      Serial.print(" | Distancia VL4 (mm): ");
      Serial.println(measure4.RangeMilliMeter);
      return 5;
    }else{
      //nao ve com nenhum
      Serial.println("caso 6");
      return 6;
    }
   
}


int teste_VLs_motores(){
  VL03.rangingTest (& measure3, false);
  VL04.rangingTest (& measure4, false);

  if(measure3.RangeMilliMeter>=750 && measure4.RangeMilliMeter<750){
    //enxerga com o 4
    return 1;
  }else if(measure3.RangeMilliMeter<750 && measure4.RangeMilliMeter>=750){
    //enxerga com o 3
    return 2;
  }else{
    return 3;
  }
}