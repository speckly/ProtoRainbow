/*********
   By speck and jtingf MUhahaha
  *********/
#include "ProtoRainbow.h"
#include "RainbowSettings.h"
#include "Frames.h"
#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "Framebuffer_GFX.h"
#include "PxMatrix.h"
#include "FastLED.h"
#include "btserver.h"

#define P_LAT 22
#define P_A 19
#define P_B 23
#define P_C 18
#define P_D 5
#define P_E 15
#define P_OE 2
CRGB matrixleds[ledcount];

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
TaskHandle_t Task1;
TaskHandle_t Task2;

// Pins for LED MATRIX
#define matrix_width 128
#define matrix_height 32

// This defines the 'on' time of the display is us. The larger this number, the brighter the display
uint8_t display_draw_time = 30; // 10-50 is usually fine
uint8_t *current_face = def;
bool animate = true;

// rainbow scroll for WS2812B
void rainbow_wave(uint8_t thisSpeed, uint8_t deltaHue, int framedelay, int counts)
{
	for (int i = 0; i < (counts + 1); i++)
	{
		uint8_t thisHue = beat8(thisSpeed, 255); // uint8_t thisHue = beatsin8(thisSpeed,0,255);
		fill_rainbow(matrixleds, ledcount, thisHue, deltaHue);
		delay(framedelay);
		FastLED.show();
	}
}
void Task2code(void *pvParameters)
{
	for (;;)
	{
		delay(1);
		display.display(50); // was60
	}
}

void setup()
{
	Serial.begin(9600);
	setCpuFrequencyMhz(160);
	xTaskCreatePinnedToCore(
		Task2code,
		"Task2",
		11000,
		NULL,
		24,
		&Task2,
		0);
	SerialBT.begin(BT_NAME); // Bluetooth device name
	display.begin(16);
	display.setMuxDelay(1, 1, 1, 1, 1);
	display.setPanelsWidth(2);
	display.setFastUpdate(true);
	FastLED.addLeds<WS2812, 4>(matrixleds, ledcount); // "4" is the pin you connect your WS2812 matrix to !
	display.setBrightness(matrix_brightness);		  // this is where you set your brightness for HUB75
	FastLED.setBrightness(led_brightness);			  // and for WS2812
}

void loop()
{	
	std::pair<String, int> result = bt_loop(); // Call the Bluetooth loop function
    if (result.first != "") {
        // Process the result if a valid message was received
		if (result.first == "matrix_brightness"){
			display.setBrightness(matrix_brightness);

		} else if (result.first == "led_brightness") {
			FastLED.setBrightness(led_brightness);
		} else if (result.first == "sad") {
			current_face = sad;
			animate = false;
		} else if (result.first == "happy") {
			current_face = cheer;
			animate = true;
		} else if (result.first == "crispity") {
			current_face = crisp;
			animate = false;
		} else if (result.first == "default") {
			current_face = def;
			animate = true;
		}
        Serial.print("Received: ");
        Serial.print(result.first);
        Serial.print(" = ");
        Serial.println(result.second);
    }
	hueOffset += 1; // insert event but itson the (loop_event)th RGB cycle TODO: what is 72???
	if (animate && hueOffset == (72 * loop_event + 1)) { 
		// your event goes here, here it blinks on every second cycle
		for (int h = 0; h < 7; h++)
		{
			display.clearDisplay();
			switch (h)
			{
			case 0:
			case 6:
				draw_face(blink1, h);
				rainbow_wave(50, 10, animation_delay, 4); // this function serves as a delay but to include the scrolling of WS2812B's, since there aint async or maybe im stupid
				break;
			case 1:
			case 5:
				draw_face(blink2, h);
				rainbow_wave(50, 10, animation_delay, 4);
				break;
			case 2:
			case 4:
				draw_face(blink3, h);
				rainbow_wave(50, 10, animation_delay, 4);
				break;
			case 3:
				draw_face(blink4, h);
				rainbow_wave(50, 10, animation_delay, 8);
				break;
			}
		}
		hueOffset = 4; // 4 Represents how may frames have passed? shouldnt it be 7?
		display.clearDisplay();
	}
	else
	{
		draw_face(current_face, hueOffset);
		rainbow_wave(50, 10, frame_delay, 1);
		if (!animate && hueOffset == 72) {
			hueOffset = 0;
		}
	}
}
