/*
Equivalencia das saidas Digitais entre NodeMCU e ESP8266 (na IDE do Arduino)
NodeMCU - ESP8266
D0 = 16;
D1 = 5;
D2 = 4;
D3 = 0;
D4 = 2;
D5 = 14;
D6 = 12;
D7 = 13;
D8 = 15;
D9 = 3;
D10 = 1;
*/

//************* Bibliotecas *******************
//#include <ESP8266WiFi.h>        // conexão direta ao wifi sem autoconect
#include <FirebaseArduino.h>    //comunicação com firebase
#include <IRremoteESP8266.h>    //send e receive IR
#include <DNSServer.h>          //autoconect
#include <ESP8266WebServer.h>   //autoconect
#include <WiFiManager.h>        //autoconect




//************* Constantes ******************** 
#define FIREBASE_HOST "automacao-a9861.firebaseio.com" //aqui vai o host do server firebase sem o HTTPS
#define FIREBASE_AUTH "iQwdB3Uj8obv1WNbmoC1nMOxGtk2XvFANKCBvBNW" //aqui vai a autenticação da API   
#define pin_led 4                                                   //pino de status, led sinalizador que acende durante o envio do comando IR
#define pin_led1 5


//**************  VARIAVEIS GLOBAIS  *****************

int lampada;                //variavel que será utilizada para ligar a lampada
int n = 0; 

//*******************FUNÇÕES*********************************



//********************  SETUP  ***********************
void setup() {
  Serial.begin(9600);                           // inicializa função para imprimir na porta serial
  pinMode(pin_led, OUTPUT);                     // inicializa o pino definido como pino de saída
  pinMode(pin_led1,OUTPUT);
  digitalWrite(pin_led,HIGH);  
 
  WiFiManager wifiManager;                      // inicializa o wifi manager
  wifiManager.resetSettings();                //reset saved settings
  //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));    //set custom ip for portal
  wifiManager.autoConnect("AutoConnectAP");     // busca o ssid e passa do eeprom e tenta se conectar, se não conseguir se conectar inicializa uma rede wifi "AutoConnectAP" 
  digitalWrite(pin_led,LOW);
  digitalWrite(pin_led1,HIGH);
  Serial.println("Wifi Conectado com sucesso!");       // se você chegar aqui, você se conectou ao WiFi

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //inicializa função para integração com firebase
  //Firebase.setBool("lampada",0);                
}

//****************** LOOP *************************
void loop() {

 //Receber a variavel lampada do firebase
 /*lampada = Firebase.getBool("lampada");
  Serial.print("lampada: ");
  Serial.println(lampada);
  if(lampada == 1){
     digitalWrite(pin_led,HIGH); 
  }
else if(lampada == 0){
    digitalWrite(pin_led,LOW); 
  }*/

    // set value 
  Firebase.setFloat("number", 42.0); 
  // handle error 
  if (Firebase.failed()) { 
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(1000); 
   
  // update value 
  Firebase.setFloat("number", 43.0); 
  // handle error 
  if (Firebase.failed()) { 
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(1000); 
 
  // get value  
  Serial.print("number: "); 
  Serial.println(Firebase.getFloat("number")); 
  delay(1000); 
 
  // remove value 
  Firebase.remove("number"); 
  delay(1000); 
 
  // set string value 
  Firebase.setString("message", "hello world"); 
  // handle error 
  if (Firebase.failed()) { 
      Serial.print("setting /message failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(1000); 
   
  // set bool value 
  Firebase.setBool("truth", false); 
  // handle error 
  if (Firebase.failed()) { 
      Serial.print("setting /truth failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(1000); 
 
  // append a new value to /logs 
  String name = Firebase.pushInt("logs", n++); 
  // handle error 
  if (Firebase.failed()) { 
      Serial.print("pushing /logs failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  Serial.print("pushed: /logs/"); 
  Serial.println(name); 
  delay(1000); 
    
}


