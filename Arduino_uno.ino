//  #include <SoftwareSerial.h>
//  SoftwareSerial s(5,6);
//
//
//  void setup() {
//
//  s.begin(115200);
//  Serial.begin(115200);
//  }
//
//
//  void loop() {
//  // read the input on analog pin 0:
////  int ADCdata = analogRead(A0);
//
//// float voltage = (ADCdata * 0.0048828125);
//float voltage=123.00;
//// Serial.println(ADCdata);
// Serial.println(voltage);
// if(s.available()>0)
//  {
//   s.write(voltage);
//  }
// delay(1000);
// }
//
//ThatsEngineering
//Sending Data from Arduino to NodeMCU Via Serial Communication
//Arduino code

//DHT11 Lib
#include <DHT.h>

//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(5, 6);

//Initialisation of DHT11 Sensor
#define DHTPIN 4
DHT dht(DHTPIN, DHT11);
float temp;
float hum;

void setup() {
  Serial.begin(9600);

  dht.begin();
  nodemcu.begin(9600);
  delay(1000);

  Serial.println("Program started");
}

void loop() {

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  //Obtain Temp and Hum data
  dht11_func();


  //Assign collected data to JSON Object
  data["humidity"] = hum;
  data["temperature"] = temp; 

  //Send data to NodeMCU
  data.printTo(nodemcu);
  jsonBuffer.clear();

  delay(2000);
}

void dht11_func() {

  hum = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(hum);
  Serial.print("Temperature: ");
  Serial.println(temp);

}
