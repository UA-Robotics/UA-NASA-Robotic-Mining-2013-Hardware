//One side note: I used the Arduino's pullup resistors to "steer" the inputs high when they were not engaged by the encoder. Hence the encoder common pin is connected to ground. 
//The sketch above fails to mention that some pulldown resistors (10k is fine) are going to be needed on the inputs since the encoder common is attached to +5V.

/* read a rotary encoder with interrupts
   Encoder hooked up with common to GROUND,
   encoder0PinA to pin 2, encoder0PinB to pin 4 (or pin 3 see below)
   it doesn't matter which encoder pin you use for A or B  

   uses Arduino pullups on A & B channel outputs
   turning on the pullups saves having to hook up resistors 
   to the A & B channel outputs 

*/ 

#define encoder0PinA  2
#define encoder0PinB  3

//#define encoder0PinA  5                                                                                ***** Use when hooking up another encoder
//#define encoder0PinB  6


volatile unsigned int encoder0Pos = 0;

void setup() { 
  static long encoder0Pos =0;

  pinMode(encoder0PinA, INPUT_PULLUP); 
 // digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor
  pinMode(encoder0PinB, INPUT_PULLUP); 
  //digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor

  attachInterrupt(0, doEncoder1, CHANGE);  // encoder pin on interrupt 0 - pin 2
 // attachInterrupt(1, doEncoder2, CHANGE);                                                                ***** I cannot use 2 encoders at the same time with the UNO. Only 2 interrupt pins.
  Serial.begin (9600);
  Serial.println("start");                // a personal quirk

} 

void loop(){
// do some stuff here - the joy of interrupts is that they take care of themselves
}

void doEncoder1() {
  /* If pinA and pinB are both high or both low, it is spinning
   * forward. If they're different, it's going backward.
   *
   * For more information on speeding up this process, see
   * [Reference/PortManipulation], specifically the PIND register.
   */
  if ((digitalRead(encoder0PinA) == digitalRead(encoder0PinB))) {
    encoder0Pos--;
  } else {
    encoder0Pos++;
  }
 
  
  
  
//    if (digitalRead(encoder0PinA) != digitalRead(encoder0PinB)) {
//    encoder0Pos++;
//  } else {
//    encoder0Pos--;
//  }
  
  
  
  
  
  
  
  
  
  

  Serial.println (encoder0Pos, DEC);
 
}


/* See this expanded function to get a better understanding of the
 * meanings of the four possible (pinA, pinB) value pairs:
 */
void doEncoder_Expanded(){
  if (digitalRead(encoder0PinA) == HIGH) {   // found a low-to-high on channel A
    if (digitalRead(encoder0PinB) == LOW) {  // check channel B to see which way
                                             // encoder is turning
      encoder0Pos = encoder0Pos - 1;         // CCW
    } 
    else {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
  }
  else                                        // found a high-to-low on channel A
  { 
    if (digitalRead(encoder0PinB) == LOW) {   // check channel B to see which way
                                              // encoder is turning  
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }

  }
  Serial.println (encoder0Pos, DEC);          // debug - remember to comment out
                                              // before final program run                                ******* What is this for? Why would the serial write to output slow down the program?
  // you don't want serial slowing down your program if not needed
}

/*  to read the other two transitions - just use another attachInterrupt()
in the setup and duplicate the doEncoder function into say, 
doEncoderA and doEncoderB. 
You also need to move the other encoder wire over to pin 3 (interrupt 1). 
*/ 
