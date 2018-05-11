
/*
 *  Este codigo permite você enviar comandos via strings para um servidor
 *  e usar diversas redes pré determinadas no codigo, o ESP8266 sempre se conectara 
 *  naquela que estiver mais proxima e com melhor sinal, sendo possivel assim você
 *  levar aplicações desde sua a casa para seu escritorio, etc, e o ESP se conectara 
 *  na rede que você estiver.
 *  
 *  Neste caso estou usando um ESP8266 que envia comandos para o 
 *  node-red em um Raspberry PI como servidor, 
 *  os comandos enviados permitem ligar e desligar um LED em um GPIO do Raspberry PI
 *  mas é claro que este é apenas um exemplo e voce pode fazer muito mais que isso,
 *  o limite é sua imaginação e necessidade.
 *  
 *  Eng.Carlos kwiek
 *  
 *  contato@carloskwiek.com.br 
 *
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;

int button = D5;
int var = 0;

void setup() {
    Serial.begin(115200);
    delay(10);
    pinMode(button,INPUT);
    

    // We start by connecting to a WiFi network
    WiFiMulti.addAP("sua rede", "password"); // aqui coloque suas redes e senhas
    WiFiMulti.addAP("sua rede", "passwod");

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}


void loop() {
    const uint16_t port = 15200;
    const char * host = "192.168.0.26"; // ip or dns

    
    
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
    }

    var = digitalRead (button);

    if(var == HIGH){
    client.print("1");
    }

    if (var == LOW){
      client.println("0");
    }
    
    //read back one line from server
    String line = client.readStringUntil('\r');
    client.println(line);

    
    Serial.println("Fecha conexao");
    client.stop();

  
    Serial.println("aguarda 100 ms...");
    delay(100);
}

