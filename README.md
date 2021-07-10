
# ProtoRainbow
This program draws animated rainbow drawings based on a predefined 2D array, on dual 64X32pixels HUB75 LED matrices using the [PxMatrix](https://github.com/2dom/PxMatrix) library . Suitable for protogen suit makers.

# Face array requirements
- Each element of the array represents the state of the pixel, 0 is off and a rainbow pixel is drawn if not 0 (I prefer to use a decimal value of 1 to save space)
- Must be facing to the right (or else both sides will be drawn facing away from the center)
![exportface](https://user-images.githubusercontent.com/60218942/125164943-6427bf00-e1c7-11eb-8990-294b11c37ba3.PNG)
- Elements are exported as a 32bit (be careful with the values since the array is ```uint8_t```) , unless you change the variable type. Comma separated 

![exportsettings](https://user-images.githubusercontent.com/60218942/125164941-61c56500-e1c7-11eb-98ab-ff963e863252.PNG)

# Creating your array
I usually use LEDMatrixStudio to export it from a drawn canvas, then replace the arrays in the example code, you might want to alter ```loop()``` so it doesnt crash from missing variables or it works as however you wish

