#include <CayenneMQTTESP8266.h>
#include <DHT.h>

#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial



// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "wifi name";
char pass[] = "wifi password*";
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char username[] = "c68e5940-20d6-11eb-883c-638d8ce4c23d";
char Mqtt_password[] = "d41ea2db2e09c7aab609f66e9ba896ae4846a190";   //this is my identity one should use its own MQTT 
char Client_id[] = "9aa55d10-219e-11eb-b767-3f1a8f1211ba";

 DHT dht(2,DHT11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Cayenne.begin(username,Mqtt_password,Client_id,ssid, pass);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
    Cayenne.loop();
  float temp = dht.readTemperature(true);
  float hum = dht.readHumidity();
  Cayenne.virtualWrite(1, temp , TYPE_TEMPERATURE , UNIT_CELSIUS);
  
  Cayenne.virtualWrite(2, hum , TYPE_RELATIVE_HUMIDITY , UNIT_PERCENT);
  //for printing on serial monitor
    Serial.print("Current humidity = ");
    Serial.print(hum);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(temp); 
    Serial.println("C  ");
     delay(60000);//Wait 5 seconds before accessing sensor again.
}

CAYENNE_IN(0)
{
  digitalWrite(2,!getValue.asInt());
}
