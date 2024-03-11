#include "config.h"
#include "ELECHOUSE_CC1101_SRC_DRV.h"

#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

SPIClass *nspi = NULL;
RF24 radio(NRF24_CE, NRF24_SS);


void testSDCard() {
  Serial.println("1) Testing microSD card");
   // default pins used by library are the same as the config.h declaration
  if (!SD.begin(SD_SS)) {
    Serial.println("[FAIL] Can't enable microSD card module.");
    return;
  } else {
    Serial.println("\t[OK] MicroSD module detected.");
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE){
    Serial.println("\t[FAIL] No SD card attached");
    return;
  }
  Serial.print("\t[OK] MicroSD attached. Detected type: ");
  switch (cardType) {
    case CARD_MMC:
      Serial.println("MMC");
      break;
    case CARD_SD:
      Serial.println("SDSC");
      break;
    case CARD_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("UNKNOWN");
  }
  uint64_t sdSize = SD.cardSize() / (1024 * 1024);
  uint64_t sdTotalSpace = SD.totalBytes() / (1024 * 1024);
  uint64_t sdUsedSpace = SD.usedBytes() / (1024 * 1024);
  
  Serial.printf("\t[INFO] MicroSD Card Size: %lluMB\n", sdSize);
  Serial.printf("\t\tTotal space: %lluMB\n", sdTotalSpace);
  Serial.printf("\t\tUsed space: %lluMB\n", sdUsedSpace);
}

void testCC1101Connected() {
  Serial.println("2) Testing cc1101 modules");
  // check cc1101 module 1
  ELECHOUSE_cc1101.setModul(0);
  Serial.println(ELECHOUSE_cc1101.getCC1101() ? "\t[OK] Module 1 detected." : "\t[FAIL] Module 1 not detected.");
  delay(100);
  // check cc1101 module 2
  ELECHOUSE_cc1101.setModul(1);
  Serial.println(ELECHOUSE_cc1101.getCC1101() ? "\t[OK] Module 2 detected." : "\t[FAIL] Module 2 not detected.");
}

void testNrf24Connected() {
  Serial.println("3) Testing nrf24 module");
  nspi = new SPIClass(HSPI);
  nspi->begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI);
  radio.begin(nspi);
  Serial.println(radio.isChipConnected() ? "\t[OK] Module detected." : "\t[FAIL] Module not detected.");
  radio.printDetails(); // Comment out if it annoys you
  
}

void testButton(int button, int pin) {
  pinMode(pin, INPUT);
  int s = 10;
  Serial.printf("\t[INFO] Testing button %d, waiting %d seconds for the user to press the button", button, s);
  for (int i = 0; i<(s*1000); i+=100) { // 10 secs, check every 100ms
    if (i%1000==0) Serial.print(".");
    if (digitalRead(pin) == LOW) {
     Serial.printf("\n\t[OK] button %d pressed.\n", button);
     return;
    }
    delay(100);
  }
  Serial.printf("\n\t[FAIL] button %d not pressed.\n", button);
}

/****** RX/TX tests *********/
void setRx(int module, float frequency) {
  // config module (rx)
  ELECHOUSE_cc1101.setModul(module);
  ELECHOUSE_cc1101.setSyncMode(0);
  ELECHOUSE_cc1101.setPktFormat(3);   
  ELECHOUSE_cc1101.setMHZ(frequency);
  ELECHOUSE_cc1101.SetRx();
}

void setTx(int module, float frequency) {
  ELECHOUSE_cc1101.setModul(module);
  ELECHOUSE_cc1101.Init();
  ELECHOUSE_cc1101.setMHZ(frequency);
  ELECHOUSE_cc1101.SetTx();
}

void testReception(int m1, int m2, int gdo0, int gdo2) {
  pinMode(gdo0, OUTPUT);
  pinMode(gdo2, INPUT);

  int rfFrequency = 433.92;
  
  // Test M1 Tx, M2 Rx
  Serial.printf("5) Testing module %d on Tx, module %d on Rx...", m1+1, m2+1);
  setRx(m2, rfFrequency);
  int t1 = ELECHOUSE_cc1101.getRssi();
  int t2 = ELECHOUSE_cc1101.getRssi();
  setTx(m1, rfFrequency);
  digitalWrite(gdo0, HIGH);
  delay(500);
  setRx(m2, rfFrequency);
  int t3 = ELECHOUSE_cc1101.getRssi();
  Serial.println("DONE");
  Serial.printf("\t[INFO] RSSI on module %d-> Internal noise: %d. With module %d emitting: %d\n", m2+1, (t1+t2)/2, m1+1, t3);
  Serial.println(t3 > (t1+t2+20)/2 ? "\t[OK] Detected signal." : "\t[FAIL] No detected signal.");
  digitalWrite(gdo0, LOW);
  ELECHOUSE_cc1101.setSidle();
  ELECHOUSE_cc1101.setModul(m1);
  ELECHOUSE_cc1101.setSidle();
}

void testTxRx() { 
  testReception(0,1, MOD0_GDO0, MOD1_GDO2);
  testReception(1,0, MOD1_GDO0, MOD0_GDO2);
}
/****************************************/

void setup() {
  // Initializations
  pinMode(LED, OUTPUT);
  Serial.begin(SERIAL_BAUDRATE);
  ELECHOUSE_cc1101.addSpiPin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, CC1101_SS0, 0); // (0) first module
  ELECHOUSE_cc1101.addSpiPin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, CC1101_SS1, 1); // (1) second module
  
  // Tests
  Serial.print("Initializating tests in 3 seconds");
  for (int i = 0; i < 3; i++){
    Serial.print('.');
    delay(1000);
  }
  Serial.println("NOW");
  Serial.println("BASIC TESTS");
  testSDCard();
  testCC1101Connected();
  testNrf24Connected();
  testTxRx();
  // Tests
  Serial.println("6) Testing blinking led for 5 seconds");
  for (int i = 0; i < 5; i++){
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  Serial.println("7) Test buttons manually");
  testButton(1, BUTTON1);
  testButton(2, BUTTON2);
  Serial.println("Tests - ENDED - Reset ecrf if you want to run tests again. Thx.");
}

void loop() {}
