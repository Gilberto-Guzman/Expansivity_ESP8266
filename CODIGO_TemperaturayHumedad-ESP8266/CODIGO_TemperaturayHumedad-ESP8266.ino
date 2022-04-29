#include <ESP8266WiFi.h>

const char* ssid     = "Profe. Gil";      // SSID
const char* password = "tapioca1";      // Contraseña
const char* host = "192.168.68.113";  // IP
const int   port = 80;            // Puerto
const int   watchdog = 5000;        // Frecuencia del watchdog
unsigned long previousMillis = millis(); 

//Incluimos la libreria del sensor de temperatura y humedad dht11
#include "DHT.h"        
#define DHTTYPE DHT11 

//Definimos el puerto de informacion del sensor dht11
//Puertos esp8266 --> https://forum.arduino.cc/t/esp8266-uploading-compiling-error-d1-was-not-declared-in-this-scope/594940/3
#define dht_dpin 4


DHT dht(dht_dpin, DHTTYPE); 


//Algoritmo para verificar la conexion de red wifi
void setup(void)
{ 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado al WiFi");  
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
  
  dht.begin();
  Serial.begin(9600);
  Serial.println("Humedad y Temperatura\n\n");
  delay(700);
}






void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();         
    
    Serial.print("Humedad = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("Temperatura = ");
    Serial.print(t); 
    Serial.println("°C  ");

    delay(10000);  
    
    float t2 = dht.readTemperature();  
    Serial.print("Temperatura = ");
    Serial.print(t); 
    Serial.println("°C  ");

    
    unsigned long currentMillis = millis();
    
  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;
  
    if (!client.connect(host, port)) {
      Serial.println("Fallo al conectar");
      return;
    }

    String url = "/PHP_TO_MYSQL/index.php?temp=";
    url += t;
    url += "&temp2=";
    url += t2;
    url += "&hum=";
    url += h;
    
    // Enviamos petición al servidor
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
 
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Cliente --> Tiempo de espera terminado !");
        client.stop();
        return;
      }
    }
  
    // Leemos la respuesta del servidor
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  delay(800);
}
