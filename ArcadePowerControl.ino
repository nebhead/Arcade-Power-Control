/*
  Adapted from the example button sketch

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe
  modified 23 May 2019
  by Ben Parmeter

  Controls a RetroPie and a power strip (monitor, etc.), via relays

  Designed for a DigiSpark, though could be adapted to other devices

  The circuit:
  - SPST Switch attached from pin 1
  - Relay Output (Pin 0) to control Raspberry Pi attached directly to Relay Input 1
  - Relay Output (Pin 2) to control Power Strip attached directly to Relay Input 2
  - 10K resistor attached to pin 1 from ground

*/

// constants won't change. They're used here to set pin numbers:
const int switchPin = 1;     // the number of the switch pin
const int raspiPin = 0;      // the number of the relay pin for the Raspberry Pi
const int powerPin = 2;      // the number of the relay pin for the power strip

// variables will change:
int switchState = 0;         // variable for reading the switch status
int lastswitchState = 0;	 // variable for keeping track of the last switch state

void setup() {
  // initialize the raspi relay pin as an output:
  pinMode(raspiPin, OUTPUT);
  // initialize the power relay pin as an output:
  pinMode(powerPin, OUTPUT);

  // initialize the switch pin as an input:
  pinMode(switchPin, INPUT);

  switchState = digitalRead(switchPin);
  lastswitchState = switchState;

  if (switchState == 0) {
    // If the switch is not active
	// Keep RaspiPi pin inactive
    digitalWrite(raspiPin, LOW);
    // turn OFF power strip
    digitalWrite(powerPin, HIGH);

  } else {
    // If the switch is active
	// Keep RaspiPi pin inactive
    digitalWrite(raspiPin, LOW);
    // turn ON power strip
    digitalWrite(powerPin, LOW);
  }
}

void loop() {

  delay(500);
  // read the state of the switch:
  switchState = digitalRead(switchPin);

  // check if the state of the switch changed
  if (switchState != lastswitchState)
  {

    if (switchState == 0) {
	  // If the switch is not active, shutdown the Pi, turn off power strip
      // cycle raspi relay:
      digitalWrite(raspiPin, HIGH);
      delay(500); // Wait 500ms before cycling low again
      digitalWrite(raspiPin, LOW);

      delay(25000);  // Wait 25 seconds for raspi to shut down
      // turn off power strip
      digitalWrite(powerPin, HIGH);

    } else {
	  // if the switch is active, then turn on power strip, turn on Pi:
      // turn on power strip
      digitalWrite(powerPin, LOW);

	  // cycle raspi relay to start sequence:
      digitalWrite(raspiPin, HIGH);
      delay(500); // Wait 500ms before cycling low again
      digitalWrite(raspiPin, LOW);

    }

    lastswitchState = switchState;
	}

}
