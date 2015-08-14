//One side note: I used the Arduino's pullup resistors to "steer" the inputs high when they were not engaged by the encoder. Hence the encoder common pin is connected to ground. The sketch above fails to mention that some pulldown resistors (10k is fine) are going to be needed on the inputs since the encoder common is attached to +5V.

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
#define numberOfMagnets 6
#define RADIUSPERMAGNET 9.42//cm

//#define encoder0PinA  5                                                                                ***** Use when hooking up another encoder
//#define encoder0PinB  6


void setup() { 


  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor
 
  pinMode(13, OUTPUT); 
 
  attachInterrupt(0, doEncoder1, RISING);  // encoder pin on interrupt 0 - pin 2
 // attachInterrupt(0, doEncoder2, CHANGE);                                                                ***** I cannot use 2 encoders at the same time with the UNO. Only 2 interrupt pins.
  Serial.begin (9600);
  Serial.println("start");                // a personal quirk

} 

volatile boolean STATE = true;
volatile long previousTime = millis();
volatile long currentTime;

void loop() {
 digitalWrite(13, STATE); 
 if(currentTime-previousTime > 1000){
  previousTime = currentTime; 
 }
 
}

void doEncoder1() {
 previousTime = currentTime;
 currentTime = millis();
 Serial.println(RADIUSPERMAGNET*1000/(currentTime-previousTime));
 STATE = !STATE;
 }
