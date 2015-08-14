int encoderPinA = 2;
int x;

volatile unsigned int encoderPos = 0;  // a counter for the dial
unsigned int lastReportedPos = 1;   // change management

void setup() {
  pinMode(encoderPinA, INPUT); 
  Serial.begin(9600);  // output
}

// main loop, work is done by interrupt service routines, this one only prints stuff
void loop() { 
  if( (x = digitalRead(encoderPinA)) < 1) {
      encoderPos += 1;
  }
    Serial.println(x, DEC);
//    Serial.println(encoderPos, DEC);
}


