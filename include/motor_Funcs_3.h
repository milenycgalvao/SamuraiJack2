#pragma once

#include <Arduino.h>
#include <TB6612FNG.h>


// 27 - Standby pin
// 14 - AIN1 pin
// 12 - AIN2 pin
// 13 - PWMA pin
// 26 - BIN1 pin
// 25 - BIN2 pin
// 33 - PWMB pin
// These pins are in a straight line on the left side of WEMOS LOLIN32 board (skip 34 and 35 as they are input-only).
// To reverse forward motor direction, switch the AIN1 and AIN2 or BIN1 and BIN2 pin numbers.
Tb6612fng motors(26, 27, 14, 12, 25, 33, 32);
// Tb6612fng motors(27, 12, 14, 13, 25, 26, 33); // Reversed forward motor direction.

void setupMotor3() {
  Serial.begin(115200);
  motors.begin();
}

void teste_motores3() {
  Serial.printf("Loop: ");
  Serial.println(millis());
  //dir para tras e esq para frente
  //motors.drive(0.5, 500);
  //dir para frente e esq para dir
  //motors.drive(-0.5, 500);
  //os dois para frente
  //motors.drive(-1.0, 1.0, 500);
  //os dois para tras
  //motors.drive(1.0, -1.0, 500);
  
}


double v1, v2;
int ms;
void andar3(double v1, double v2, int ms){
  motors.drive(v1, v2, ms, false);
}

void girar3(double v1, int ms){
  motors.drive(v1, ms, false);
}




void voltarLinha(int caso){
    //REVER VALORES
    if(caso==1){
        //sair da linha da dir
        //atras(255, 255);
        //delay(50);
        //radarEsquerda(255, 255);
        delay(50);
    }else if(caso==2){
        //sair da linha da esq
        //atras(255, 255);
        delay(50);
        //radarEsquerda(255, 255);
        delay(50);
    }else if(caso==3){
        //sair das duas linhas
        //frente(255, 255);
        //volta um pouquinho pra tras e liga estrategia de radar pra qualquer lado por enquanto
    }
}