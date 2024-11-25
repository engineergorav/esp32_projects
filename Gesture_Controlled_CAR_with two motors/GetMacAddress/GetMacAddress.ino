#include <esp_system.h>

void setup() {
  Serial.begin(115200);
  uint8_t mac[6];
  esp_efuse_mac_get_default(mac);
  Serial.print("ESP32 Factory MAC Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", mac[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
}

void loop() {
  // Nothing needed here
}
