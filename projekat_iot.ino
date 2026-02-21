#include <WiFi.h>
#include <PubSubClient.h>
#include <NewPing.h>

// WiFi Credentials
const char* ssid     = "";
const char* password = "";

// ThingsBoard Cloud 
const char* mqtt_server = "thingsboard.cloud";  
const int   mqtt_port   = 1883U;
const char* TB_TOKEN    = "";  

// ESP32 Pins
const int pirPin  = 13;   // PIR sensor
const int trigPin = 12;   // Ultrasonic trigger
const int echoPin = 14;   // Ultrasonic echo
const int ledPin  = 2;    // Built-in LED

// Ultrasonic
#define MAX_DISTANCE 400 // cm
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

// WiFi & MQTT
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected! IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to ThingsBoard...");
    if (client.connect("ESP32Client", TB_TOKEN, nullptr)) {
      Serial.println("connected!");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" -> retry in 2 sec");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read sensors
  int pirState = digitalRead(pirPin);
  int distance = sonar.ping_cm();
  if (distance == 0) distance = MAX_DISTANCE; // no echo

  // Build JSON
  String payload = "{\"pir\":" + String(pirState) +
                   ",\"distance\":" + String(distance) + "}";

  // Publish telemetry
  if (client.publish("v1/devices/me/telemetry", payload.c_str())) {
    Serial.println("Sent: " + payload);
  } else {
    Serial.println("Failed to send telemetry!");
  }

  delay(1000); // every second
}
