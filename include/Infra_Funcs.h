#pragma once

#include <Arduino.h>
#include <motor_Funcs_3.h>


#define pinInfraD 35

#define pinInfraE 34
bool leituraD, leituraE;


void setupInfra() {
    pinMode(pinInfraD, INPUT);
    pinMode(pinInfraE, INPUT);
}

void leituraInfras() {
    leituraD = digitalRead(pinInfraD);
    leituraE = digitalRead(pinInfraE);
}

void printInfras(){
    leituraInfras();
    if(leituraD){
        Serial.print("infra D: true  |");
    }else{
        Serial.print("infra D: false |");
    }

    if(leituraE){
        Serial.print("infra E: true  |");
    }else{
        Serial.print("infra E: false |");
    }

    Serial.println();
    
}


bool naLinha() {
    leituraInfras();
    //retorna true para branco
    if(leituraD || leituraE){
        return true;
    }else{
        return false;
    }
}

void retornar() {
    leituraInfras();

    if(leituraD){
        Serial.println("D");
        voltarLinha(1);  
    }else if(leituraE){
        Serial.println("E");
        voltarLinha(2);
    }else{
        Serial.println("D e E juntos");
        voltarLinha(3);
    }
}
