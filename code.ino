// esp8266 node mcu + oled display ssd1306 128x64 + DHT11 Sensor + Own API
#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>
#include<ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dht11.h>
#include <WiFiClient.h>

WiFiClient wifiClient;

#define DHT11PIN 12
dht11 DHT11;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int ledPin =  2;

// Wifi Credintials
const char* SSID = "SSID";
const char* Password = "Password";




void connectWifiNetwork(){
  WiFi.begin(SSID, Password);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to Your Wifi ...");
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(18, 5);
    display.writePixel(10, 10, 1);
    display.writePixel(10, 8, 1);
    display.writePixel(9, 8, 1);
    display.writePixel(11, 8, 1);
    display.writePixel(8, 9, 1);
    display.writePixel(12, 9, 1);
    display.writePixel(6, 7, 1);
    display.writePixel(7, 6, 1);
    display.writePixel(8, 5, 1);
    display.writePixel(9, 5, 1);
    display.writePixel(10, 5, 1);
    display.writePixel(11, 5, 1);
    display.writePixel(12, 5, 1);
    display.writePixel(13, 6, 1);
    display.writePixel(14, 7, 1);
    display.println("Connecting WiFi...");
    display.setCursor(0, 18);
    display.setTextSize(2);
    display.println("Wait a fewMoment!");
    display.display();
  }
}

void requestAPI(){
  // Declare http client reference
  HTTPClient http;

  // Create HTTP Request
  http.begin(wifiClient,"your_own_api");

  // get status code
  int httpCode = http.GET();

  // check if httpCode == 200
  if(httpCode == HTTP_CODE_OK){
    Serial.print("HTTP Status Code: ");
    Serial.print(httpCode);
    Serial.println();

    //print response
    Serial.println(http.getString());
    parseJSON(http.getString());

    
  }

  //close connection
  http.end();
}

void parseJSON(String json){
  
  //declare the buffer
  DynamicJsonDocument buffer(1024);

  //Deserialize the string => object
  deserializeJson(buffer, json);

  //get Message field
  const char* message = buffer["message"];
  int ledStatus = buffer["data"]["status"];

  //Print Response
  Serial.println();
  Serial.print("Response is : ");
  Serial.print(message);
  Serial.println();
  Serial.print("Led 1 Status is: ");
  Serial.print(ledStatus);
  
  int chk = DHT11.read(DHT11PIN);

  if(ledStatus == 0){
    digitalWrite(ledPin, LOW);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(18, 5);
    display.writePixel(10, 10, 1);
    display.writePixel(10, 8, 1);
    display.writePixel(9, 8, 1);
    display.writePixel(11, 8, 1);
    display.writePixel(8, 9, 1);
    display.writePixel(12, 9, 1);
    display.writePixel(6, 7, 1);
    display.writePixel(7, 6, 1);
    display.writePixel(8, 5, 1);
    display.writePixel(9, 5, 1);
    display.writePixel(10, 5, 1);
    display.writePixel(11, 5, 1);
    display.writePixel(12, 5, 1);
    display.writePixel(13, 6, 1);
    display.writePixel(14, 7, 1);
    display.println("WiFi Connected!");
    display.setCursor(0, 18);
    display.setTextSize(2);
    display.println("Led1: OFF");
    display.setCursor(0, 40);
    display.setTextSize(1);
    display.print("Temperature:");
    display.print((float)DHT11.temperature, 2);
    display.println(" C");
    display.print("Humidity:   ");
    display.print((float)DHT11.humidity, 2);
    display.println(" %");
    display.display();
  }else{
    digitalWrite(ledPin, HIGH);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(18, 5);
    display.writePixel(10, 10, 1);
    display.writePixel(10, 8, 1);
    display.writePixel(9, 8, 1);
    display.writePixel(11, 8, 1);
    display.writePixel(8, 9, 1);
    display.writePixel(12, 9, 1);
    display.writePixel(6, 7, 1);
    display.writePixel(7, 6, 1);
    display.writePixel(8, 5, 1);
    display.writePixel(9, 5, 1);
    display.writePixel(10, 5, 1);
    display.writePixel(11, 5, 1);
    display.writePixel(12, 5, 1);
    display.writePixel(13, 6, 1);
    display.writePixel(14, 7, 1);
    display.println("WiFi Connected!");
    display.setCursor(0, 18);
    display.setTextSize(2);
    display.println("Led1: ON");
    display.setCursor(0, 40);
    display.setTextSize(1);
    display.print("Temperature:");
    display.print((float)DHT11.temperature, 2);
    display.println(" C");
    display.print("Humidity:   ");
    display.print((float)DHT11.humidity, 2);
    display.println(" %");
    display.display();
  }

}


void setup() {

  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);

  //welcome screen delay 3s
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setFont(NULL);
  display.setCursor(0, 9);
  display.println("WELCOME TOHOME IOT  AUTOMATION");
  display.display();
  delay(3000);

  //setup wifi
  connectWifiNetwork();

}

void loop() {
  
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Successfully Connected to Your Wifi Network.");
    
    requestAPI();
    delay(2000);
  }

}
