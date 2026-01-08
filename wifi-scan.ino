#include <WiFi.h>
#include <HTTPClient.h>
#include "occupancy_model.h"

// WiFi (Wokwi)
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASS = "";

// ThingSpeak
String THINGSPEAK_KEY = "WJ5ZQNITE6UU3K76";
const char* THINGSPEAK_URL = "http://api.thingspeak.com/update";
const unsigned long PUBLISH_INTERVAL_MS = 16000; // keep >= 15s to avoid rate limits

// Pots (ADC)
const int PIN_HUM_ADC   = 32;
const int PIN_LIGHT_ADC = 34;
const int PIN_CO2_ADC   = 35;

// Actuators
const int PIN_FAN    = 2;
const int PIN_HEATER = 4;

// StandardScaler params (from your fitted pipeline)
// Feature order: Temperature, Humidity, Light, CO2, HumidityRatio
static const float MEAN[5] = {
  2.10936164e+01f,
  2.36210357e+01f,
  2.49495596e+02f,
  6.66738895e+02f,
  3.65122328e-03f
};
static const float STDV[5] = {
  1.07776449e+00f,
  3.74383789e+00f,
  2.29705980e+02f,
  2.39564550e+02f,
  5.94066665e-04f
};

static inline float zscore(float x, int i) {
  return (x - MEAN[i]) / STDV[i];
}

float mapAdcToRange(int adc, float outMin, float outMax) {
  float x = (float)adc / 4095.0f;
  return outMin + x * (outMax - outMin);
}

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting WiFi");
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    delay(300);
    Serial.print(".");
  }
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi OK: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi not connected (still running simulation).");
  }
}

void publishThingSpeak(int occ, float t, float h, float l, float c, float hr) {
  if (WiFi.status() != WL_CONNECTED) return;
  if (THINGSPEAK_KEY.startsWith("REPLACE_")) return;

  HTTPClient http;
  String url = String(THINGSPEAK_URL) +
               "?api_key=" + THINGSPEAK_KEY +
               "&field1=" + String(occ) +
               "&field2=" + String(t, 3) +
               "&field3=" + String(h, 3) +
               "&field4=" + String(l, 3) +
               "&field5=" + String(c, 3) +
               "&field6=" + String(hr, 6);

  http.begin(url);
  int code = http.GET();
  String payload = http.getString();
  http.end();

  Serial.print("ThingSpeak HTTP ");
  Serial.print(code);
  Serial.print(" resp: ");
  Serial.println(payload);
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  pinMode(PIN_FAN, OUTPUT);
  pinMode(PIN_HEATER, OUTPUT);

  connectWiFi();

  Serial.println("\nOccupancy + Energy Optimizer (Decision Tree on ESP32)");
  Serial.println("Order: Temperature, Humidity, Light, CO2, HumidityRatio");
}

void loop() {
  // Simulated sensors
  int rawHum   = analogRead(PIN_HUM_ADC);
  int rawLight = analogRead(PIN_LIGHT_ADC);
  int rawCO2   = analogRead(PIN_CO2_ADC);

  // Map to realistic-ish ranges near your training distribution
  float Temperature = 20.0f + 3.0f * sin(millis() / 25000.0f); // ~17..23
  float Humidity    = mapAdcToRange(rawHum, 18.0f, 35.0f);
  float Light       = mapAdcToRange(rawLight, 0.0f, 800.0f);
  float CO2         = mapAdcToRange(rawCO2, 350.0f, 1200.0f);

  // Option A: fixed HumidityRatio at training mean to avoid formula mismatch
  float HumidityRatio = MEAN[4];

  // Scale for the exported tree (tree splits are in z-space)
  float zT  = zscore(Temperature, 0);
  float zH  = zscore(Humidity, 1);
  float zL  = zscore(Light, 2);
  float zC  = zscore(CO2, 3);
  float zHR = zscore(HumidityRatio, 4); // will be ~0

  int occ = predict_occupancy(zT, zH, zL, zC, zHR);

  // Energy optimization
  if (occ == 1) {
    digitalWrite(PIN_FAN, HIGH);
    digitalWrite(PIN_HEATER, (Temperature < 20.5f) ? HIGH : LOW);
  } else {
    digitalWrite(PIN_FAN, LOW);
    digitalWrite(PIN_HEATER, LOW);
  }

  // Insight
  Serial.println("--------------------------------------------------");
  Serial.printf("RAW  T=%.2f H=%.2f L=%.1f CO2=%.1f HR=%.6f => occ=%d\n",
                Temperature, Humidity, Light, CO2, HumidityRatio, occ);
  Serial.printf("Z    zT=%.3f zH=%.3f zL=%.3f zC=%.3f zHR=%.3f\n",
                zT, zH, zL, zC, zHR);
  Serial.printf("ACT  FAN=%d HEATER=%d\n", digitalRead(PIN_FAN), digitalRead(PIN_HEATER));

  // Publish
  static unsigned long lastPub = 0;
  if (millis() - lastPub >= PUBLISH_INTERVAL_MS) {
    publishThingSpeak(occ, Temperature, Humidity, Light, CO2, HumidityRatio);
    lastPub = millis();
  }

  delay(400); // fast local loop; publish still throttled
}
