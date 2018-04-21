# Programming

Sample code is written in the Arduino IDE.  To program the badge, you will need a suitable 
programmer, like the USB-ASP, or another Arduino.  Headers on the board are in the standard 
AVR ISP pinout.  **WARNING: Check programmer voltage.  Needs 3.3V, not 5V.**

To set up the Arduino IDE to program the badge using either programmer, you will first need 
to load the board support files.  In the IDE, open Preferences, then find the _Additional 
Boards Manager URLs_ text box.  Put in 
https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json 
and click _OK_.  Now, go to _Tools_ -> _Board_ -> _Boards Manager..._  In this list, there will be 
a new entry, probably at the bottom, named _attiny_.  Select it, and click _Install_.  It should 
list _INSTALLED_ once complete.

Now that the attiny BSP is installed, you can now set up the target with the following items 
in the _Tools_ menu.  For _Board_, under _ATtiny Microcontrollers_, select _ATtiny25/45/85_.  For 
_Processor_, select _ATtiny85_.  And for _Clock_, select _Internal 8 MHz_.

If this is a new microcontroller that hasn't been programmed yet, it will need the 
bootloader burned so that it can be programmed by the Arduino IDE.  Select your programmer 
first under _Tools_ -> _Programmer_.  The Badge Pirates team is using the USBasp programmer.  
Then, click _Tools_ -> _Burn Bootloader_.  If working correctly, four LEDs on the front of the 
badge will glow and blink as the device is programmed.  If it returns without an error 
message, then congrats, your badge is ready to accept custom code!

At this point, the programming target settings are correct, and you should be able to 
program anything you want onto the device.  If your code is super buggy, it won't even 
compile.  However, it may still compile and upload, but be buggy enough to not run.  Don't 
worry - with the bootloader installed, you can always upload a new program onto the device, 
without fear of bricking it.  If things get really bad, you may need to burn the bootloader 
again.  But at least the device isn't completely bricked.

Get a hold of us if you run into any problems and we'll be glad to help.  twitter: @BadgePirates
