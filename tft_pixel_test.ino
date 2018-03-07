#include <TFT.h>
#include <SPI.h>

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

TFT TFTscreen = TFT(cs, dc, rst);

int potPin = 6;    // select the input pin for the potentiometer
int y = 0;       // variable to store y position
int x = 0;      // variable to store x position
int myWidth = 0;      // variable to store reported screen width
int myHeight = 0;     // variable to store reported screen height
int delTime = 0;      // variable to store delay time
int maxTime = 10000;  // variable to store maximum delay time (milliseconds)
int refTime = 500;    // variable for RGB screen refresh delay (milliseconds)

// char array to print to the screen
char linePos[6];
char del[8];



void setup() {
  Serial.begin(9600);  // initialize serial communication at 9600 bits per second:
  TFTscreen.begin();

myWidth = TFTscreen.width();
myHeight = TFTscreen.height();

//RGB full screen color test
  TFTscreen.background(255, 255, 255);
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.text("Red:", 10, 10);
  delay(refTime+50);
  TFTscreen.background(255, 0, 0);
  delay(refTime);
  TFTscreen.background(255, 255, 255);
  TFTscreen.text("Green:", 10, 10);
  delay(refTime+50);
  TFTscreen.background(0, 255, 0);
  delay(refTime);
  TFTscreen.background(255, 255, 255);
  TFTscreen.text("Blue:", 10, 10);
  delay(refTime+50);
  TFTscreen.background(0, 0, 255);
  delay(refTime);
  TFTscreen.background(255, 255, 255);

 //set text options for sketch
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.setTextSize(1);

}

void loop() {
 
  Serial.println("Width"); //prints Width in the serial monitor
  Serial.println(myWidth); //prints self-reported screen width in the serial monitor
  Serial.println("Height"); //prints Height in the serial monitor
  Serial.println(myHeight);  //prints self-reported screen height in the serial monitor

do {
  int delTime = analogRead(potPin); // reads value of potentiometer

  // clear previous loop's delay value
  TFTscreen.stroke(255, 255, 255);  
  TFTscreen.text(del, 45, 33);      

  // map delay time to pot value
  delTime = map(delTime, 0, 1023, 0, maxTime);

  // parse delay value to be printed on screen
  String delVal = String(delTime);
  delVal.toCharArray(del, 5);
  
  TFTscreen.stroke(255, 0, 255);  // sets text color
  
  // prints text to screen
  TFTscreen.text("Line:", 10, 23);
  TFTscreen.text("Delay:", 10, 33);
  TFTscreen.text(del, 45, 33);

  // parse line position to value for printout
  String lineVal = String(y);
  lineVal.toCharArray(linePos, 6);
  
  //draw red line across screen
  TFTscreen.stroke(255, 0, 0);
  TFTscreen.line(0, y, myWidth, y);
  
  //erase previous loop's red line
  TFTscreen.stroke(255, 255, 255);    
  TFTscreen.line(0, y-1, myWidth, y-1);
  
  //print line position
  TFTscreen.stroke(255, 0, 255);
  TFTscreen.text(linePos, 45, 23);
  
  delay(delTime);     //delay before moving onto next line
  
  // clears line position from screen
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.text(linePos, 45, 23);

  //checks to see if line is at the bottom of the screen, if so reset Y to 0 and move on to X scan
  if (y >= myHeight) {
      y = 0;
      x = 1;
      TFTscreen.background(255, 255, 255);
    } else {
      // increment the vertical position:
      y++;
    }
}  while (y != 0);




// begin X line scan
do {
  int delTime = analogRead(potPin); // reads value of potentiometer

  // clear previous loop's delay value
  TFTscreen.stroke(255, 255, 255);  
  TFTscreen.text(del, 45, 33);      

  // map delay time to pot value
  delTime = map(delTime, 0, 1023, 0, maxTime);

  // parse delay value to be printed on screen
  String delVal = String(delTime);
  delVal.toCharArray(del, 5);
  
  TFTscreen.stroke(255, 0, 255);  // sets text color
  
  // prints text to screen
  TFTscreen.text("Line:", 10, 23);
  TFTscreen.text("Delay:", 10, 33);
  TFTscreen.text(del, 45, 33);


  // parse line position to value for printout
  String lineVal = String(x);
  lineVal.toCharArray(linePos, 6);
  
  //draw red line across screen
  TFTscreen.stroke(255, 0, 0);
  TFTscreen.line(x, 0, x, myHeight);
  
  //erase previous loop's red line
  TFTscreen.stroke(255, 255, 255);    
  TFTscreen.line(x-1, 0, x-1, myHeight);
  
  //print line position
  TFTscreen.stroke(255, 0, 255);
  TFTscreen.text(linePos, 45, 23);
  
  delay(delTime);     //delay before moving onto next line
  
  // clears line position from screen  
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.text(linePos, 45, 23);

    //checks to see if line is at the right of the screen, if so reset X to 0 and move back to Y scan
  if (x >= myWidth) {
      y = 1;
      x = 0;
      TFTscreen.background(255, 255, 255);
    } else {
      // increment the horizontal position:
      x++;
    }
}  while (x != 0);

}
