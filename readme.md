# Overview #
Since Playstation 2 to USB adapters for the Cobalt Flux stopped working around 32-bit Windows XP, and I've been deprived of ITG, I decided to completely replace my control box with an Arduino and a circuit.
Since the Cobalt Flux is just a bunch of switches, this is really easy.

### What You'll Need ###
* An Arduino 
* A breadboard, or any circuit board
* wires
* A solderable male HD15 (VGA) connector (optional but recommended)

# Let's Get Started #
First, you're going to want to flash your Arduino firmware to the most recent version if it currently isn't using [this guide](https://www.arduino.cc/en/Hacking/DFUProgramming8U2).
After that, you can upload the code to the Arduino.

Since we can't send out keyboard input with the current firmware, we'll need to flash it (just like we flashed the firmware before) with USB HID keyboard firmware found [here](http://dl.dropbox.com/u/1816557/Arduino-keyboard-0.3.hex).

Once that's done, we can make our circuit.

### Pinout ###
![pinout](http://i.imgur.com/vYh9sUK.png)

The mapping I have is as follows:

Ground is connected to ground.  
Up is connected to D2  
Down is connected to D4  
Left is connected to D6  
Right is connected to D8  
Up Left is connected to D10  
Up Right is connected to D12  
Down Left is connected to D13  


If you don't have a male HD15 connector that you can solder wires to, you can stick the jumper cables in the female HD15 connector attached to the Cobalt Flux, however I wouldn't recommend it.

Here's what my circuit looked like.
![my loadout](http://i.imgur.com/crnClZX.jpg)
# Usage #
The current mapping I have from pin to keypresses are:

Up is w  
Down is s  
Left is a  
Right is d  
Up Left is esc (default song exit)  
Up Right is enter (default song select)  
Down Left is shift + enter (default sort)  

You can change these in your Stepmania settings to match the code, or change them in the code to match your Stepmania settings.

# Notes #
If you wanted to change the code uploaded to the Arduino, you would have to flash it back to the previous firmware so that it can be recognized as an Arduino.
So for writing new code, the steps would be

1. Flash the Arduino with the firmware used in [this guide](https://www.arduino.cc/en/Hacking/DFUProgramming8U2).
2. Unplug it and plug it back in
3. Upload your code
4. Flash the Arduino with the USB keyboard firmware found [here](http://dl.dropbox.com/u/1816557/Arduino-keyboard-0.3.hex).
5. Unplug it and plug it back in

If you wanted to change the code keypresses to follow your Stepmania settings, you would have to follow the USB HID keyboard usage table, found [here](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0CB0QFjAAahUKEwip6aTBz4zIAhUGcj4KHRHWCwg&url=http%3A%2F%2Fwww.usb.org%2Fdevelopers%2Fhidpage%2FHut1_12v2.pdf&usg=AFQjCNEun33wLDX52uUN7p6F2mf0s_3D9g&sig2=RnA2Bnpq8FVhPE8Qz8fBTA&bvm=bv.103388427,d.cWw).

I have firmware debouncing in the form of a 5ms delay between presses, so you may have to adjust your offset in Stepmania to compensate.

# References #
[keyboard firmware from here](http://mitchtech.net/arduino-usb-hid-keyboard/)  
[USB HID reference](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0CB0QFjAAahUKEwip6aTBz4zIAhUGcj4KHRHWCwg&url=http%3A%2F%2Fwww.usb.org%2Fdevelopers%2Fhidpage%2FHut1_12v2.pdf&usg=AFQjCNEun33wLDX52uUN7p6F2mf0s_3D9g&sig2=RnA2Bnpq8FVhPE8Qz8fBTA&bvm=bv.103388427,d.cWw)  
[Cobalt flux pinout](http://pinouts.ru/Game/cobalt_flux_pinout.shtml)
