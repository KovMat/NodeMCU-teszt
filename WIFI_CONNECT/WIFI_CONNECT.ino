#include <ESP8266WiFi.h>

const char* ssid = "Máté iPhone";
const char* pass = "ABBADEAF01";
const uint8_t reset_pin = 5;

int ledState = LOW;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Setup is in progress!");

  pinMode(BUILTIN_LED, OUTPUT);
  
  digitalWrite(BUILTIN_LED, ledState);
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "-Encrypted");
      delay(10);
    }
  }

  WiFi.begin(ssid, pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED);
  IPAddress local_ip = WiFi.localIP();
  Serial.print("Connected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(local_ip);

  Serial.println("Setup done");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW)
      ledState = HIGH;  // Note that this switches the LED *off*
    else
      ledState = LOW;   // Note that this switches the LED *on*
    digitalWrite(BUILTIN_LED, ledState);
  }
}
