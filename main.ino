#include <DHT.h>
#include <SHA256.h>

#define DHTPIN 2          // Pin which is connected to the DHT11 sensor
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

void setup() {
  Serial.begin(9600);    // Initialize serial communication
  dht.begin();           // Initialize DHT sensor
}

void loop() {
  float temperature = dht.readTemperature();    // Read temperature value from DHT11 sensor
  float humidity = dht.readHumidity();          // Read humidity value from DHT11 sensor

  if (isnan(temperature) || isnan(humidity)) {  // Check if DHT11 sensor reading is valid
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  String data = String(temperature) + "," + String(humidity);  // Create data string with temperature and humidity values

  SHA256 sha256;  // Initialize SHA256 hashing algorithm
  uint8_t hash[32];  // Initialize hash buffer

  sha256.update(data.c_str(), data.length());  // Update hash with data string
  sha256.finalize(hash, sizeof(hash));         // Finalize hash

  Serial.print("Data: ");
  Serial.print(data);
  Serial.print(", Hash: ");
  for (int i = 0; i < sizeof(hash); i++) {
    Serial.print(hash[i], HEX);
  }
  Serial.println();

  delay(1000);    // Wait for 1 second before next measurement
}
