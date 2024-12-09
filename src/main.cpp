
#include <Adafruit_GFX.h>
#include <GxEPD2.h>
#include <GxEPD2_3C.h>
#include <logo.h>

// or select the display constructor line in one of the following files (old style):
#include "GxEPD2_display_selection.h"

GxEPD2_3C<GxEPD2_420c, GxEPD2_420c::HEIGHT / 2> display(GxEPD2_420c(D5, D6, D4, D7));

// for handling alternative SPI pins (ESP32, RP2040) see example GxEPD2_Example.ino
const int WIDTH = 400;
const int HEIGHT = 300;

void debug1() {
  display.setRotation(0);
  display.setFullWindow();
  display.firstPage();

  const auto padding = random(0, 20);
  Serial.print("pages = "); Serial.print(display.pages()); Serial.print(" page height = "); Serial.println(display.pageHeight());

  display.fillScreen(GxEPD_WHITE);

  do {
    for (auto x = padding; x < WIDTH - padding; x += 4) {
      for (auto y = padding; y < HEIGHT - padding; y += 4) {
        for (auto i = 0; i < 2; i++) {
          int c_rand = random(0, 3);
          for (auto j = 0; j < 2; j++) {
            auto color = c_rand == 0 ? GxEPD_WHITE : c_rand == 1 ? GxEPD_BLACK : GxEPD_RED;
            display.drawPixel(x + i, y + j, color);
          }
        }
      }
    }
  } while (display.nextPage());
}

void blank() {
  display.setRotation(0);
  display.setFullWindow();
  display.firstPage();

  display.fillScreen(GxEPD_WHITE);
  while (display.nextPage()) {};
}

void debug2() {
  display.setRotation(0);
  display.setFullWindow();
  display.firstPage();

  uint32_t pixels = sizeof(epd_bitmap_dither_it_sanity_monogram__white_on_red);
  Serial.print("pages = "); Serial.print(display.pages()); Serial.print(" page height = "); Serial.println(display.pageHeight());
  Serial.print("pixels = "); Serial.print(pixels);
  do {
    display.drawRGBBitmap(0, 0, epd_bitmap_dither_it_sanity_monogram__white_on_red,  WIDTH, HEIGHT);
  } while (display.nextPage());
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.print("Initializing...");

  display.init(115200);
  //blank();
  debug1();
  sleep(2);
  debug2();

}

void loop() {};
