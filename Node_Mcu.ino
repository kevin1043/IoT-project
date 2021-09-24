//#include <SoftwareSerial.h>
////    SoftwareSerial s1(2,3);
////
////
////    void setup() {
////    s1.begin(9600);
////    Serial.begin(9600);
////    }
////    void loop() {
////
//////    s.write("s");
////    if (s1.available()>0)
////    {
////   float data=s1.read();
////    Serial.println(data);
////    }
////     delay(1000);
////   }
//SoftwareSerial mySerial(3,2); // RX, TX
//
//void setup() {
//  // Open serial communications and wait for port to open:
//  Serial.begin(115200);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }
//
//
//  Serial.println("2");
//
//  // set the data rate for the SoftwareSerial port
//  mySerial.begin(115200);
//  mySerial.println("2 UNO");
//}
//
//void loop() { // run over and over
//  if (mySerial.available()) {
//    Serial.write(mySerial.read());
//  }
//  if (Serial.available()) {
//    mySerial.write(Serial.read());
//  }
//}
//ThatsEngineering
//Sending Data from Arduino to NodeMCU Via Serial Communication
//NodeMCU code

//Include Lib for Arduino to Nodemcu
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <string>
#include <ESP8266WiFi.h>
//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);
#define FIREBASE_HOST "thermal-setup-304113-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Xegn2X9SVrS3WGCvOk3uEt1FTrlT8pE4mO3TIrnI"
#define WIFI_SSID "Kvin"
#define WIFI_PASSWORD "87654321"


void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  nodemcu.begin(9600);
  while (!Serial) continue;
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());                               //prints local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }

  Serial.println("JSON Object Recieved");
  Serial.print("Recieved Humidity:  ");
  float hum = data["humidity"];
  Serial.println(hum);
  Serial.print("Recieved Temperature:  ");
  float temp = data["temperature"];
  Serial.println(temp);
  Serial.println("-----------------------------------------");


  
  Firebase.setFloat("temp:", temp);
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(1000);
  Firebase.setFloat("hum:", hum);
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(1000);





}
