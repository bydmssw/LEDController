#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define LED1 5
#define LED2 4

const char* ssid = " ";      // Nama SSID AP/Hotspot
const char* password = " ";  // Password Wifi

ESP8266WebServer server(80);  //Menyatakan Webserver pada port 80
String webpage;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  Serial.begin(115200);
  delay(500); 
  WiFi.begin(ssid, password); // Proses koneksi jaringan
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("terkoneksi dengan ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


// Isi dari halaman Web
  webpage+= "<h1>LED Panel</h1>";
  webpage+= "<p>LED 1 : ";
  webpage+= "<a href=\"LED1ON\"\"><button>ON</button></a><a href=\"LED1OFF\"\"><button>OFF</button></a></p><br>";
  webpage+= "<p>LED 2 : ";
  webpage+= "<a href=\"LED2ON\"\"><button>ON</button></a><a href=\"LED2OFF\"\"><button>OFF</button></a></p><br>";
          
// Membuat tampilan halaman web
  server.on("/", []() {
    server.send(200, "text/html", webpage);
   });

// Bagian input output
  server.on("/LED1ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1,HIGH);
    delay(500);
  });
  server.on("/LED2ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED2,HIGH);
    delay(500);
  });
  server.on("/LED1OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1,LOW);
    delay(500);
  });
  server.on("/LED2OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED2,LOW);
    delay(500);
  });
  server.begin();
  Serial.println("Webserver dijalankan");
}

void loop() {
   server.handleClient();
}
