/*overview:
- The encoder needs to track velocity, # of clicks, #count, direction
- The encoder can only miss 1-5% of the counts
- Needs to be designed in junction with the encoder board.


Pins on Arduino boards for interrupt:
Arduino Due	All Digital Pins	
Arduino Uno	2, 3	13
Arduino Leonardo	0, 1, 2, 3	
Arduino Mega	2, 3, 18, 19, 20, 21	
Sanguino	2, 10, 11	0

/* Encoder Library - TwoKnobs Example
 */// http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * //This example code is in the public domain.

/*
#include <Encoder.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knobLeft(5, 6);
Encoder knobRight(7, 8);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("TwoKnobs Encoder Test:");
}

long positionLeft  = -999;
long positionRight = -999;

void loop() {
  long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }
}

*/


//-------------------------------------------------------
//This is code found on a basic interrupt
//http://www.dave-auld.net/index.php?option=com_content&view=article&id=107:arduino-interrupts&catid=53:arduino-input-output-basics&Itemid=107

/*

int pbIn = 0;                  // Interrupt 0 is on DIGITAL PIN 2!
int ledOut = 4;                // The output LED pin
volatile int state = LOW;      // The input state toggle
//&nbsp;
void setup()
{                
  // Set up the digital pin 2 to an Interrupt and Pin 4 to an Output
  pinMode(ledOut, OUTPUT);
//&nbsp;
  //Attach the interrupt to the input pin and monitor for ANY Change 
  attachInterrupt(pbIn, stateChange, CHANGE);
}
//&nbsp;
void loop()                     
{
  //Simulate a long running process or complex task
  for (int i = 0; i < 100; i++)
  {
    // do nothing but waste some time
    delay(10); 
  }
}
//&nbsp;
void stateChange()
{
  state = !state;
  digitalWrite(ledOut, state);  
}

*/

//---------------------------------------------------------------------------------------
//This is for a rotary encoder
//https://www.sparkfun.com/datasheets/Components/RotaryEncoder.pde

/*

// This is just a code snippet, provided in case it helps you.
// My setup: This encoder has pin C (middle pin of the three on one side) and 
// one of the pair on the other side connected to ground.  The other pins are 
// connected as follows to my Arduino Mega:
//      'A': digital pin 22
//      'B': digital pin 24
//      'press': digital pin 26
// In "real" code, you'd want a state machine to keep track of the rotation,
// and only take note of the "forward" or "back" when the encoder is reporting
// 0 again.

// Digital pin definitions
//enum enDigitalPins

  // Rotary encoder input lines
  dpInEncoderA=22,
  dpInEncoderB=24,
  dpInEncoderPress=26,
};


static void _ResetPins()
{
  // Rotary encoder input lines
  // Configure as input, turn on pullup resistors
  pinMode(dpInEncoderA, INPUT);
  digitalWrite(dpInEncoderA, HIGH);
  pinMode(dpInEncoderB, INPUT);
  digitalWrite(dpInEncoderB, HIGH);
  pinMode(dpInEncoderPress, INPUT);
  digitalWrite(dpInEncoderPress, HIGH);
}


void _lowlevel_ReadEncoder(int &rotate, int& press)
{
  rotate = (digitalRead(dpInEncoderB) * 2) + digitalRead(dpInEncoderA);
  press = digitalRead(dpInEncoderPress);
}


void ReadEncoder()
{
  int Position, Press;
  int isForward = 0;
  
  _ResetPins();
  Serial.println("Reading the encoder... press a key to abort.");
  _lowlevel_ReadEncoder(Position, Press);
  while (!Serial.available())
  {
    int Position2, Press2;
    do
    {
      _lowlevel_ReadEncoder(Position2, Press2);
    } while ((Position2 == Position) && (Press2 == Press));
    if (Position2 != Position)
    {
      // "Forward" is shown by the position going from (0 to 1) or (1 to 3)
      // or (3 to 2) or (2 to 0).  Anything else indicates that the user is
      // turning the device the other way.  Remember: this is Gray code, not
      // binary.
      int isFwd = ((Position == 0) && (Position2 == 1)) ||
                  ((Position == 1) && (Position2 == 3)) ||
                  ((Position == 3) && (Position2 == 2)) ||
                  ((Position == 2) && (Position2 == 0));
      Serial.println(isFwd ? "FWD" : "BWD");
    }
    if (Press2 != Press)
    {
      Serial.println(Press ? "Press" : "Release");
    }
    Position = Position2;
    Press = Press2;
  }
}


/*void setup()
{
  // configure the pins
  _ResetPins();

  // init serial communication
  Serial.begin(115200); 
  Serial.println("Ready to begin");
}


void loop()
{
  ReadEncoder();
}
*/
