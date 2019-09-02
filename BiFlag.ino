#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN 15
#define LED_COUNT 29

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)

//keeps track of which chunk of the LED strip will get which color
uint8_t currentCycle = 0;

void setup() {
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  biCycle(1500);
}

/*
 * sets a single RGB pixel to one of the bi flag RGBs
 * @param int choice choose one of the three biFlag colors
 * @param int i index of the pixel to set
 */
void chooseBiColor(int choice, int i) {
  switch (choice) {
    case 0:
      strip.setPixelColor(i, 214, 2, 112); // pink
      break;
    case 1:
      strip.setPixelColor(i, 155, 20, 150); // purple
      break;
    case 2:
      strip.setPixelColor(i, 0, 56, 168); //blue
      break;
    default:
      break;
  }
}

/*
 * Splits the LED strip into chunks and sets it into cycling biFlag colors
 * @param uint8_t wait length of time to delay in between loops in Milliseconds
 */
void biCycle(uint8_t wait) {
  uint8_t i, j, k;
  for (i = 0; i < LED_COUNT / 3; i++) {
    chooseBiColor(currentCycle % 3, i);
  }
  for (j = LED_COUNT / 3; j < 2 * LED_COUNT / 3; j++) {
    chooseBiColor((currentCycle + 1) % 3, j);
  }
  for (k = 2 * LED_COUNT / 3; k < LED_COUNT; k++) {
    chooseBiColor((currentCycle + 2) % 3, k);
  }
  currentCycle = (currentCycle + 1) % 3;
  
  strip.show();
  delay(wait);
}
