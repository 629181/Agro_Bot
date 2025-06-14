#include <DHT.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
int gas=A0,gasR ;
int sMos=A1, sMosR;

// Define pin and sensor type
#define DHTPIN 4         // Pin where the DHT11 is connected
  // Use DHT11
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  pinMode(gas, INPUT);
  pinMode(sMos, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
    dht.begin();
  Serial.println("DHT11 sensor reading...");
}

void loop() {
  gasR=analogRead(gas);
  sMosR=analogRead(sMos);
// Wait a few seconds between readings
  delay(2000);

  // Read temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Default is Celsius

  int sMosA=map(sMosR,1023,0,99,0);
  int gasA=map(gasR,1023,0,99,0);

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print results
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Gas: ");
  Serial.println(gasR);
  Serial.println(gasA);
  Serial.print("Soil Moisture: ");
  Serial.println(sMosR);
  Serial.println(sMosA);
  long hum=humidity+100;
  mySerial.println(hum);
  long temp=temperature+200;
  mySerial.println(temp);
  long gasT=gasA+300;
  mySerial.println(gasT);
  long sMosT=sMosA+400;
  mySerial.println(sMosT);

  delay(15000);
}
