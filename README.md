# TFT-Scan-Test
Arduino code for performing bounds tests on TFT displays

This performs full screen RGB test then scans each line of the display while displaying the line position on screen.

This was created because I noticed the cheap TFT displays from China don't always provide use of the entire screen, or sometimes self-report their size as different than the actual pixels available. For instance, I got a batch of 128x128 displays that identify as 128x160, with the Y origin shifted -2 pixels so the actual usable space is 4 pixels less than advertised.

This code will show the colors, origin, and bounds of a display. 

Attach the TFT as directed for your board. If your board doesn't use the standard Uno pins you will have to redefine the cs, dc, and rst pins appropriately. (Lines 5-7)

Attach a potentiometer to analog pin 6. This will be used to adjust the scan speed.

When first run, the sketch will do an RGB test of the board, displaying each color full screen for a period of time. To adjust the time each color is on screen, change the value of refTime on line 18. This test allows you to quickly see if all pixels are addressable and also that your colors appear in the right order. Some screens I've encountered have the red and blue reversed.

After the RGB test, lines will scan down and across the screen, allowing you to see which if any lines are not within the reported spec of the display. The speed of the scan is adjustable with the pot. The initial maximum time for each line is 10 seconds, but the mapping can easily be adjusted on line 17. 
