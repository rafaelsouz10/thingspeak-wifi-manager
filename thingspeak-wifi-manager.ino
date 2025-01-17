#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

String apiKey ="AOA4R0PCU0H0MRUI";
const char* server = "api.thingspeak.com";

int cont = 0;

WiFiClient client;

void setup() {
  
 Serial.begin(115200);
 conexaoWiFi(); 

}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    if (client.connect(server,80)) { // "184.106.153.149" or api.thingspeak.com
      String postStr = apiKey;

      postStr +="&field1=";
      postStr += String(cont);

      postStr +="&field2=";
      postStr += String(cont*2);

      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);

      Serial.println("% send to Thingspeak");
    }
    
    Serial.println("Waiting…");
    // thingspeak needs minimum 15 sec delay between updates

    cont++;
    delay(15000);
  }else{
    Serial.println("");
    Serial.println("Rede DESconectada");
    Serial.println("");
    conexaoWiFi();
  }
}
// ----------------------------------------------------------------------------------------------
void conexaoWiFi(){
  Serial.println("Reconectando WiFi...");

  WiFiManager wm; // Objeto WiFiManager
  wm.setConfigPortalTimeout(60);
  bool res;

  // Se conecta automaticamente com WiFiManager
  res = wm.autoConnect("AgriTec", "laboratorio"); // AP protegido por senha
  if (!res) {
    Serial.println("Falha ao conectar...");
    delay(500);
  }
}