#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

WebSocketsClient wsc;

const char *ssid = "ahmedWaleed";
const char *pass = "123456789";

#define SERVER "192.168.1.2"
#define PORT 9000
#define URL "/"

#define LED_PIN D2

void websocketEvent(WStype_t type, uint8_t *data, size_t length)
{

  switch (type)
  {

  case WStype_CONNECTED:

    Serial.println("Connected To WebSocket Server");

    break;

  case WStype_DISCONNECTED:

    Serial.println("Disconnected From WebSocket Server");

    break;

  case WStype_TEXT:
  {

    int intensity = atoi((char *)data);

    intensity = constrain(intensity, 0, 255);

    analogWrite(LED_PIN, intensity);

    Serial.print("Intensity: ");
    Serial.println(intensity);

    break;
  }
  }
}

void setup()
{

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  analogWriteRange(255);

  analogWrite(LED_PIN, 0);

  Serial.println();
  Serial.println("Connecting To WiFi...");

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {

    delay(500);

    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");

  Serial.print("NodeMCU IP: ");
  Serial.println(WiFi.localIP());

  wsc.begin(SERVER, PORT, URL);

  wsc.onEvent(websocketEvent);

  wsc.setReconnectInterval(1000);
}

void loop()
{

  wsc.loop();
}