# ProtoRainbow
This program draws animated rainbow drawings based on a predefined 2D array, on dual 64X32pixels HUB75 LED matrices using the [PxMatrix](https://github.com/2dom/PxMatrix) library .
Suitable for protogen suit makers.

# Face array requirements
- Must be facing to the right (or else both sides will be drawn facing away from the center)

- Each element of the array represents the state of the pixel, 0 is off and a rainbow pixel is drawn if not 0 (I prefer to use a value of 1 to save space)

# Creating your array
I usually use LEDMatrixStudio to export it from a drawn canvas, then replace the arrays in the example code, you might want to alter ```loop()``` so it doesnt crash from missing variables or it works as however you wish
