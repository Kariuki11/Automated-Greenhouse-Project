// Pin Definitions
const int ldrPin = A0;       // LDR connected to analog pin A0
const int relayLightPin = 7; // Relay for artificial lights connected to digital pin 7
const int lightThresholdLow = 500;  // Low light threshold (adjust based on testing)
const int lightThresholdHigh = 800; // High light threshold (adjust based on testing)

int previousLightIntensity = 0; // To track changes in light intensity

void setup() {
  Serial.begin(9600);              // Start serial communication for debugging
  pinMode(relayLightPin, OUTPUT);  // Set light relay pin as output
  digitalWrite(relayLightPin, LOW); // Turn off artificial lights initially
}

void loop() {
  int lightIntensity = analogRead(ldrPin); // Read LDR value (0-1023)
  Serial.print("Current Light Intensity: ");
  Serial.println(lightIntensity);

  // Detect changes in light intensity
  if (lightIntensity > previousLightIntensity) {
    Serial.println("The light intensity is increasing.");
  } else if (lightIntensity < previousLightIntensity) {
    Serial.println("The light intensity is decreasing.");
  } else {
    Serial.println("The light intensity remains stable.");
  }

  // Automation logic for light control
  if (lightIntensity < lightThresholdLow) {
    // Low light detected, turn on artificial lights
    digitalWrite(relayLightPin, HIGH);
    Serial.println("Low light detected - Turning ON artificial lights.");
  } else if (lightIntensity > lightThresholdHigh) {
    // High light detected, turn off artificial lights
    digitalWrite(relayLightPin, LOW);
    Serial.println("High light detected - Turning OFF artificial lights.");
  } else {
    // Moderate light detected, ensure artificial lights are off
    digitalWrite(relayLightPin, LOW);
    Serial.println("Moderate light detected - Artificial lights remain OFF.");
  }

  // Update previous light intensity for the next loop
  previousLightIntensity = lightIntensity;

  delay(10000); // Wait for a second before the next reading
}
