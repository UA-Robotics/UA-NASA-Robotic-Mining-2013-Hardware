//Look at for example of RN 41 at work:
//http://www.fixkick.com/ELM327/taurus-sim/Arduino/compiler/arduino-1.0.5/my-code/MPG/MPG-H5/RN41/RN41.ino




void setup() {

char val;         // variable to receive data from the serial port
int PIO3 = 3;
int Redledpin = 8;
int Greenledpin = 5;
int YellowledpinTX = 13;
int YellowledpinRX = 14;

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
// ********* comms are 115200 buud , but is way too fast for UNO softwareserial pins, so reduced  BAUD to 38k (bits per second)

}

{
  pinMode(PIO3, INPUT);
}

{
pinMode(Redledpin, OUTPUT);      // sets the digital pin as output
pinMode(Greenledpin, OUTPUT);
pinMode(YellowledpinTX, OUTPUT);
pinMode(YellowledpinRX, INPUT;
pinMode(connectbit, INPUT); //  this is the RN41 status bit for IM connected.

}


//---------------------------------------------start Bluetooth Connection



/*

   setupBlueToothConnection();   // activate the RN41 bluethooth. 

  Serial.println("BT conn finished");//     
  delay(1000);
  Serial.flush(); // RN-41 rec.
  blueToothSerial.flush(); // same
//  displaybump();  // go from FEEd to 0001 on the display.
  

  
  //-----Start OBDII initialitation
  obd_init();  // sets up the funky old , OBD2 ELM327 (works on clones and counterfeits too....)
  // we now have this huge serial path working, arduino to OBD2, no small task....
  Serial.println("OBD init done , next?, we scan the ECU , forever");// xxx    
  t.every(1000,mpg_calc); //Every 1000ms read MPG value from OBD (200 fails as does 500) im clueless !
// wdt_enable(WDTO_8S);  //  I now turn ON  WATCH DOG  (8 is max ,sadly) but you can edit the class.
  
} // end setup()
*/

{
  
  delay (200);
    val =LOW;
    Serial.println("Setting up BT RN41 Link");  
    blueToothSerial.print("$$$");  // enter command mode ,you only have 60 seconds (and power up) for this to work.  /r and /n (cr or lf) are NOT ALLOWED.  see datasheet.    
    getRX(); // expect to see echoed  "CMD"  , most commands echo, AOK or if bad ERR, malformed commands expect ? for a response.
    delay(1000);  // the RN book says 500 minimum
    Serial.println("Sending C ");
    blueToothSerial.print("C\r");  // connect now.
    delay(3000);
    getRX();  // you will see TRYING only , echoed. then the solid green led and then flashing red as my MPG loops and sends data flashing said LED    
    blueToothSerial.flush();
    Serial.println("Exit BT setup!");
}
else Serial.println("Autoconnected sw3");
    
}  // end new RN41 blue tooth setup


void loop() {}

//Look for the other paired device
duration = pulseIn(PIO3, HIGH);

{
    if( Serial.available() )       // if data is available to read
  {
    val = Serial.read();       // read it and store it in 'val'
  }
 
  if( val == '0' )               // if '0' was received led 13 is switched off

  {
    digitalWrite(ledpin, LOW);    // turn Off pin 13 off
    delay(500);                  // waits for half a second   
    Serial.println("13 off");
  }

  if( val == '1' )               // if '1' was received led 13 on
  {
    digitalWrite(ledpin = 13, HIGH);  // turn ON pin 13 on
    delay(500);                  // waits for half a second
    Serial.println("13 on");
  }
}




//What the LEDs do on the RN41:
digitalWrite(Redledpin, HIGH);   // sets the LED on
  delay(1000);                  // waits for a second
  digitalWrite(Redledpin, LOW);    // sets the LED off
  delay(1000);                  // waits for a second
  
digitalWrite(Greenledpin, HIGH);   // sets the LED on
  delay(1000);                  // waits for a second
  digitalWrite(Greenledpin, LOW);    // sets the LED off
  delay(1000);                  // waits for a second
  
digitalWrite(YellowledpinTX, HIGH);   // sets the LED on
  delay(1000);                  // waits for a second
  digitalWrite(YellowledpinTX, LOW);    // sets the LED off
  delay(1000);                  // waits for a second

digitalWrite(YellowledpinRX, HIGH);   // sets the LED on
  delay(1000);                  // waits for a second
  digitalWrite(YellowledpinRX, LOW);    // sets the LED off
  delay(1000);                  // waits for a second



/*PIO3 = switch2 = Auto discovery
PIO5 = Green LED = good connection
PINS 13 & 14 on both devices = Yellow LED = trans/receive
PIO8 = Red LED = no connection
PIO6 = Auto Master Mode (High signal)

Rx (ATMega328 on HHC)= pin 30
Tx (ATMega328 on HHC)= pin 31

Rx (RN41 on HHC)= pin 13
Tx (RN41 on HHC)= pin 14

--------------------------------------------
Signal wires and respective inputs/outputs

Rx (ATMega1280 on Control Board)= pin 12
Tx (ATMega1280 on Control Board)= pin 13

Rx (RN41 on Control Board)= pin 13
Tx (RN41 on Control Board)= pin 14


------------------------------------------------------------------------------






/*
Already Salvaged this code to above
------------------


simple LED test


char val;         // variable to receive data from the serial port
int ledpin = 13;  // LED connected to pin 2 (on-board LED)

void setup()
{
  pinMode(ledpin, OUTPUT);  // pin 13 (on-board LED) as OUTPUT
  Serial.begin(9600);       // start serial communication at 115200bps
 
}
 
void loop() {
  if( Serial.available() )       // if data is available to read
  {
    val = Serial.read();       // read it and store it in 'val'
  }
 
  if( val == '0' )               // if '0' was received led 13 is switched off

  {
    digitalWrite(ledpin, LOW);    // turn Off pin 13 off
    delay(500);                  // waits for half a second   
    Serial.println("13 off");
  }

  if( val == '1' )               // if '1' was received led 13 on
  {
    digitalWrite(ledpin = 13, HIGH);  // turn ON pin 13 on
    delay(500);                  // waits for half a second
    Serial.println("13 on");
  }
}
