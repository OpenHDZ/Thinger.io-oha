#define _DEBUG_

//#define THINGER_SERVER "192.168.1.2"

#include <YunClient.h>
#include <ThingerYun.h>

#include "DHT.h"

// dht config
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define USERNAME "OHA"
#define DEVICE_ID "OHA_YUN"
#define DEVICE_CREDENTIAL "lxXcCG4vGF4N"

ThingerYun thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
const int ledPin =  13;

void setup() {
  pinMode(ledPin, OUTPUT);

  // initialize bridge
  Bridge.begin();

  // pin control example (i.e. turning on/off a light, a relay, etc)
  thing["led"] << digitalPin(ledPin);

  dht.begin();
  
  thing["dht11"] >> [](pson& out){
    out["humidity"] = dht.readHumidity();
    out["celsius"] = dht.readTemperature();
    out["fahrenheit"] = dht.readTemperature(true);

  
  // more details at http://docs.thinger.io/arduino/
};
}

void loop() {
  thing.handle();
   thing.stream(thing["dht11"]);
}
