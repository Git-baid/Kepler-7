#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <faces.h>

// ------------------ MATRIX CONFIG ------------------
#define R1_PIN 25
#define G1_PIN 26
#define B1_PIN 27
#define R2_PIN 14
#define G2_PIN 12
#define B2_PIN 13
#define A_PIN 18
#define B_PIN 19
#define C_PIN 5
#define D_PIN 17
#define E_PIN -1 // required for 1/32 scan panels, like 64x64px. Any available pin would do, i.e. IO32
#define LAT_PIN 4
#define OE_PIN 33
#define CLK_PIN 16

#define PANEL_WIDTH 64
#define PANEL_HEIGHT 32
#define PANEL_CHAIN 2

HUB75_I2S_CFG::i2s_pins _pins={R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};

HUB75_I2S_CFG mxconfig(
  PANEL_WIDTH,
  PANEL_HEIGHT,
  PANEL_CHAIN,
  _pins
);

MatrixPanel_I2S_DMA matrix(mxconfig);

int blinkInterval = 1;
int blinkTime = 0;
// ------------------ FUNCTION PROTOTYPES ------------------
void drawFace(const uint16_t face[2][32][64]);

// ------------------ SETUP ------------------
void setup() {
  Serial.begin(115200);

  // Initialize matrix
  matrix.begin();
  matrix.setBrightness8(128);  // 0–255
  matrix.clearScreen();

  drawFace(neutral);
}

// ------------------ LOOP ------------------
void loop() {
  int now = millis();
  if (now - blinkTime >= blinkInterval) {
    blinkTime = now;
    blinkInterval = random(3000, 8000);
    drawFace(neutral_blink);
    delay(100);
    drawFace(neutral);
  }
}

// ------------------ FUNCTIONS ------------------
void drawFace(const uint16_t face[2][32][64]) {
  matrix.drawRGBBitmap(0, 0, (uint16_t *)face[0], PANEL_WIDTH, PANEL_HEIGHT);
  matrix.drawRGBBitmap(64, 0, (uint16_t *)face[1], PANEL_WIDTH, PANEL_HEIGHT);
}