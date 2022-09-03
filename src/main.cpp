

#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <AsyncTCP.h>
#include "Adafruit_VL53L0X.h"
//#include "VL_Funcs.h"
#include "VL_Funcs_aux.h"
//#include "VL_Funcs_unitario.h"
#include "Infra_Funcs.h"
//#include "motor_Funcs.h"
//#include "motor_Funcs_2.h"
#include "motor_Funcs_3.h"


int estrategia = 3;

//#define OTA 
#ifdef OTA
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
AsyncWebServer server(80);
const char* ssid = "mi123";
const char* password = "mileny123";
#endif




void setup(void) {
  

  Serial.begin(115200);
  
  #ifdef OTA
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP32. BBB");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
  #endif

  
  setID();
  
  //setupInfra();
  //setupMotor1();
  //setupMotor2();
  setupMotor3();
}

bool inicio = true, ajeitar = false;
int  ataque, aux = 0.6, um=1;//aux==1==100%
unsigned long millisInicial = millis();
unsigned long contMillis = millis();

void loop(void) {

  if(estrategia==0){
    //estrategia para testes dos componentes
    //printLasersTeste();
    //atras(255, 255);
    //testeMD();//motorDireita
    //printInfras();
    //teste_motores2();
    //teste_motores3();
    //andar3();

    /*

    if(teste_VLs_motores()==1){
      //enxerga com 4
      //motor A liga
      andar3(-0.5, 0.5, 500);
    }else if(teste_VLs_motores()==2){
      //enxerga com 3
      //motor B liga
      andar3(0.5, -0.5, 500);
    }else{
      girar3(0.5, 500); 
    }*/

    Serial.println("\nestrategia 0");
  }else if(estrategia==1){
    Serial.println("\nestrategia 1");

    //ROBO DE FRENTE OU OLHANDO PARA A ESQUERDA
    //estrategia mais simples

    //esperar 5 segundos
    /*if(inicio==true){
      contMillis = millis();
      while(millis() - contMillis <= 5000){
        Serial.println(millis()-contMillis + " milisegundos");
      }
      inicio = false;
    }else{
      //começa
      if(naLinha()){
      retornar();
    }else{
      if(enxergaLaser() || ajeitar == true){
        //atacar ou ajeitar
        if(enxergaLaser()){
          ataque = 0; 
        }
        if(qualAtaque()==1 || ataque == 1){
          ajeitar = true;
          //girar para a direita
          //motor esquerdo "baixo", motor direito alto
          ataque = 1;
          andar(-255, 255);
        }else if(qualAtaque()==2 || ataque == 2){
          ajeitar = true;
          //girar para a esquerda
          //motor esquerdo alto, motor direito baixo
          ataque = 2;
          andar(255, -255);
        }else if (qualAtaque()==3 || ataque == 3){
          ajeitar = true;
          //motor esquerdo baixo, motor direito alto
          ataque = 3;
          andar(150, 255);
        }else if (qualAtaque()==4 || ataque == 4){
          ajeitar = true;
          //motor esquerdo alto, motor direito baixo
          ataque = 4;
          andar(255, 150);
        }else{
          ajeitar = false;
          //velocidade alta nos 2 motores
          andar(255, 255);
        }
      }else{
        //estratégia de busca RADAR PARA A DIREITA
        andar(255, -255);
      }
    
    }
    
    }
    */
  }else if(estrategia == 2){
    Serial.println("estrategia 2");
    //ROBO DE FRENTE OU OLHANDO PARA A ESQUERDA
    //estrategia considerando distancia, quanto mais longe esta mais forte faz a curva
    /*
    //esperar 5 segundos
    if(inicio==true){
      contMillis = millis();
      while(millis() - contMillis <= 5000){
        Serial.println(millis()-contMillis + " milisegundos");
      }
      inicio = false;
    }else{
      //começa
      if(naLinha()){
      retornar();
      }else{
        if(enxergaLaser() || ajeitar == true){
          //atacar ou ajeitar
          if(enxergaLaser()){
            ataque = 0; 
          }
          if(qualAtaque()==1 || ataque == 1){
            ajeitar = true;
            //girar para a direita
            //motor esquerdo "baixo", motor direito alto
            ataque = 1;
            andar(-aux*255, 255);
          }else if(qualAtaque()==2 || ataque == 2){
            ajeitar = true;
            //girar para a esquerda
            //motor esquerdo alto, motor direito baixo
            ataque = 2;
            andar(255, -aux*255);
          }else if (qualAtaque()==3 || ataque == 3){
            ajeitar = true;
            //motor esquerdo baixo, motor direito alto
            ataque = 3;
            andar(aux*255, 255);
          }else if (qualAtaque()==4 || ataque == 4){
            ajeitar = true;
            //motor esquerdo alto, motor direito baixo
            ataque = 4;
            andar(255, aux*150);
          }else{
            ajeitar = false;
            //velocidade alta nos 2 motores
            andar(255, 255);
          }
        }else{
          //estratégia de busca RADAR PARA A DIREITA
          andar(255, -255);
        }
      
      }
    }
    */
  }else if(estrategia == 3){
    //Serial.println("\n estrategia 3");
    //ESTRATEGIA PARA USAR COM 2 SENSORES NA FRENTE APENAS
    //ROBO DE FRENTE OU OLHANDO PARA A ESQUERDA
    //desconsiderando distancia
    
    //esperar 5 segundos
    if(inicio==true){
      
      
      //Serial.println("\ncontando");
      //Serial.print("Millis = ");
      //Serial.println(millis());

      if(um==1){
        millisInicial = millis();
        um=2;
      }
      //Serial.print("millisInicial = ");
      //Serial.println(millisInicial);



      contMillis = millis()-millisInicial;
      //Serial.print("contMillis = ");
      //Serial.println(contMillis);
      
      while(contMillis <= 5000){
        //Serial.println(millis()-contMillis + " milisegundos");
        contMillis = millis()-millisInicial;
        //Serial.print("contMillis = ");
        //Serial.println(contMillis);
      }
      inicio = false;
    }else{
      //começa
      
      
      if(naLinha()){
      retornar();
      }else{
        if(enxergaLaser()){
          //atacar ou ajeitar
          if(qualAtaque()==3){
            //else if ve no canto esquerdo da frente
            //andar(150, 255);
            Serial.println("ataque 3: fraco no esq, alto no dir");
            andar3(-1.0, 0.5, 10);
          }else if(qualAtaque()==4){
            //else if ve no canto direito da frente
            //andar(255, 150);
            Serial.println("ataque 4: alto no esq, fraco no dir");
            andar3(-0.5, 1.0, 100);
          }else if(qualAtaque()==5){
            ajeitar = false;
            //velocidade alta nos 2 motores
            //andar(255, 255);
            Serial.println("ataque 5: forte os dois");
            andar3(-0.5, 0.5, 10);
          }
        }else{
          //estratégia de busca RADAR PARA A DIREITA
          //andar(255, -255);
          Serial.println("busca");
          girar3(0, 10);
          
        }
        
      }
    }
    
  }

  
  
}