
# ProtoRainbow
This program draws animated rainbow drawings based on a predefined 2D array, on dual 64X32pixels HUB75 LED matrices using the [PxMatrix](https://github.com/2dom/PxMatrix) library . Suitable for protogen suit makers.

# Face array requirements
- Each element of the array represents the state of the pixel, if the element is zero, the pixel will be turned off. A rainbow pixel is drawn if not 0 (I prefer to use a decimal value of 1 to save space)
- Must be facing to the right (or else both sides will be drawn facing away from the center)
![exportface](https://user-images.githubusercontent.com/60218942/125164943-6427bf00-e1c7-11eb-8990-294b11c37ba3.PNG)
- Elements are exported as a 32bit RGBA color value. Comma separated 
![exportsettings](https://user-images.githubusercontent.com/60218942/125164941-61c56500-e1c7-11eb-98ab-ff963e863252.PNG)

# Creating your array
I usually use LEDMatrixStudio to export it from a drawn canvas, then replace the arrays in the example code, you might want to change some code in the function ```loop()``` so it doesnt crash from missing variables or it works as however you wish

Currently there is 1 static face and a 4 frame animation and back is played every 2 rainbow loops included in your example code
![ProtoRainbowDemo](https://user-images.githubusercontent.com/60218942/125281675-189d1e80-e349-11eb-9692-3ab314db534a.gif)

