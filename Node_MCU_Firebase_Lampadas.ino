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
#include "FirebaseESP8266.h"
#include <DNSServer.h>          //autoconect
#include <ESP8266WebServer.h>   //autoconect
#include <WiFiManager.h>        //autoconect


//************* Constantes ******************** 
// 1. Alterar as seguintes informações
#define FIREBASE_HOST "automahouse-ad208.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "tFRwpBblQhJ5QPyE0BGfMWBqFo8NEVAZAQfhH0OU"

//**************  VARIAVEIS GLOBAIS  *****************
//N/A

//*******************FUNÇÕES*********************************
// 2. Definir o objeto de dados FirebaseESP8266 para envio e recebimento de dados
FirebaseData firebaseData;

//********************  SETUP  ***********************
void setup()
{

  Serial.begin(115200);
  
  // Wifi AutoConnect
  WiFiManager wifiManager;                      // inicializa o wifi manager
  wifiManager.resetSettings();                //reset saved settings
  //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));    //set custom ip for portal
  wifiManager.autoConnect("AutoConnectAP");     // busca o ssid e passa do eeprom e tenta se conectar, se não conseguir se conectar inicializa uma rede wifi "AutoConnectAP" 
  Serial.println("Wifi Conectado com sucesso!");       // se você chegar aqui, você se conectou ao WiFi
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  
  // 3 Defina suas informações do Firebase

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // 4. Ative a reconexão automática do Wi-Fi quando a conexão for perdida
  Firebase.reconnectWiFi(true);

  // 5. Tente definir dados int para Firebase
  // A função set retorna bool para o status da operação
  // firebaseData requer para enviar os dados
  if(Firebase.setInt(firebaseData, "/LED_Status", 1))
  {
    //Sucesso
     Serial.println("Set int data success");

  }else{
    // Falhou?, Obtenha o motivo do erro do firebaseData
    Serial.print("Error in setInt, ");
    Serial.println(firebaseData.errorReason());
  }


  // 6. Tente obter dados int do Firebase
  // A função get retorna bool para o status da operação
  // firebaseData requer para receber os dados
  if(Firebase.getInt(firebaseData, "/LED_Status"))
  {
    //Successo
    Serial.print("Get int data success, int = ");
    Serial.println(firebaseData.intData());

  }else{
    // Falhou?, Obtenha o motivo do erro do firebaseData

    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  }

 /*

  Caso deseje definir outros tipos de dados, como bool, float, double e String, você pode usar setBool, setFloat, setDouble e setString.
  Se você deseja obter dados que você conhece seu tipo em um nó específico, use getInt, getBool, getFloat, getDouble, getString.
  Se você não souber o tipo de dados no nó específico, use get e verifique seu tipo.

  A seguir, mostra como obter os dados variantes

  */

 if(Firebase.get(firebaseData, "/LED_Status"))
  {
    //Successo
    Serial.print("Get variant data success, type = ");
    Serial.println(firebaseData.dataType());

    if(firebaseData.dataType() == "int"){
      Serial.print("data = ");
      Serial.println(firebaseData.intData());
    }else if(firebaseData.dataType() == "bool"){
      if(firebaseData.boolData())
        Serial.println("data = true");
      else
        Serial.println("data = false");
    }

  }else{
    // Falhou?, Obtenha o motivo do erro do firebaseData

    Serial.print("Error in get, ");
    Serial.println(firebaseData.errorReason());
  }

  /*

  Se você deseja obter os dados em tempo real, em vez de usar get, consulte os exemplos de fluxo.
  Se você deseja trabalhar com JSON, consulte os exemplos FirebaseJson, jsonObject e jsonArray.

  Se você tiver dúvidas ou tiver encontrado os erros, sinta-se à vontade para abrir o problema aqui https://github.com/mobizt/Firebase-ESP8266

  */

}

//****************** LOOP *************************
void loop()
{
}
