
# ProtoRainbow
This library draws animated rainbow drawings based on a predefined 2D array, on dual 64X32pixels HUB75 LED matrices using the [PxMatrix](https://github.com/2dom/PxMatrix) library. A personal project but suitable for protogen suit makers.

## Face array requirements
- Each element of the array represents the state of the pixel, if the element is zero, the pixel will be turned off. A rainbow pixel is drawn if not 0 (I prefer to use a decimal value of 1 because the visual is clearer in the IDE)
- Must be facing to the right or else both sides will be drawn facing the wrong way
![exportface](https://user-images.githubusercontent.com/60218942/125164943-6427bf00-e1c7-11eb-8990-294b11c37ba3.PNG)
- Elements are exported as a 32bit RGBA color value. Comma separated 
![exportsettings](https://user-images.githubusercontent.com/60218942/125164941-61c56500-e1c7-11eb-98ab-ff963e863252.PNG)

## Creating your array and usage
I usually use LEDMatrixStudio to export it from a drawn canvas, then replace or add the arrays in ```./Frames.h```, you might want to change some code in the function ```loop()``` so it doesnt crash from missing variables or to work as however you wish
```ProtoRainbow.ino``` is an example code using the ProtoRainbow library and FastLED's own rainbow scrolling functions for WS2812B

Currently there is 1 static face and an animation 4x2 frames long is played every 2 rainbow cycles, included in the example code. There are settings to adjust the speed and wavelength of the rainbow scroll

## Extras
There is support for sine animations in the library and its properties (period, amp, offset)

##ProtoRainbow Demo
![ProtoRainbowDemo](https://user-images.githubusercontent.com/60218942/125281675-189d1e80-e349-11eb-9692-3ab314db534a.gif)

