#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL30Es1Pbrz"
#define BLYNK_TEMPLATE_NAME "Power Monitoring System"
#define BLYNK_AUTH_TOKEN "3ywvmY_5QmOLBM5Iz6bfdKga7VjKdsaw"

#include "EmonLib.h"   // https://github.com/openenergymonitor/EmonLib
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

EnergyMonitor emon;
#define vCalibration 115     // Voltage calibration factor
#define currCalibration 2.5  // Current calibration factor

BlynkTimer timer;

char ssid[] = "H";
char pass[] = "12345679";

float kWh = 0;
unsigned long lastmillis = millis();

// --- Function to get Load Status ---
String getLoadStatus(float power) {
  if (power < 200) return "Low Load";
  else if (power < 400) return "Medium Load";
  else return "High Load";
}

// --- Reset kWh function ---
BLYNK_WRITE(V4)  // Reset Button on V4
{
  int pinValue = param.asInt();
  if (pinValue == 1) {
    kWh = 0;
    Serial.println("kWh reset to 0");
    Blynk.virtualWrite(V3, kWh);
  }
}

void myTimerEvent() {
  emon.calcVI(40, 2000);  // Higher samples for better accuracy

  float Vrms = emon.Vrms;
  float Irms = emon.Irms;
  float realPower = emon.realPower;

  // --- Eliminate noise readings ---
  if (Irms < 0.1) Irms = 0;
  if (realPower < 5) realPower = 0;

  // Update energy (kWh)
  unsigned long currentMillis = millis();
  kWh += realPower * (currentMillis - lastmillis) / 3600000000.0;
  lastmillis = currentMillis;

  // --- Print and send to Blynk ---
  Serial.print("Vrms: "); Serial.print(Vrms, 2); Serial.print("V\t");
  Serial.print("Irms: "); Serial.print(Irms, 4); Serial.print("A\t");
  Serial.print("Real Power: "); Serial.print(realPower, 4); Serial.print("W\t");
  Serial.print("kWh: "); Serial.print(kWh, 4); Serial.println("kWh");

  Blynk.virtualWrite(V0, Vrms);
  Blynk.virtualWrite(V1, Irms);
  Blynk.virtualWrite(V2, realPower);
  Blynk.virtualWrite(V3, kWh);

  // --- Load Status + Color ---
  String loadStatus = getLoadStatus(realPower);
  Blynk.virtualWrite(V5, loadStatus);

  if (realPower < 200) {
    Blynk.setProperty(V5, "color", "#23C48E"); // Green
  } else if (realPower < 400) {
    Blynk.setProperty(V5, "color", "#ED9D00"); // Yellow
  } else {
    Blynk.setProperty(V5, "color", "#D3435C"); // Red
  }
}

void setup() {
  Serial.begin(115200);
  emon.voltage(35, vCalibration, 1.7);  // Voltage: pin 35
  emon.current(34, currCalibration);   // Current: pin 34

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(5000L, myTimerEvent);  // Every 5 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}
