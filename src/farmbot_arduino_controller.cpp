// Do not remove the include below
#include "farmbot_arduino_controller.h"
#include "pins.h"
//#include "Config.h"
//#include "StepperControl.h"
//#include "ServoControl.h"
//#include "PinGuard.h"
//#include "TimerOne.h"

//static char commandEndChar = 0x0A;
//static GCodeProcessor* gCodeProcessor = new GCodeProcessor();

unsigned long lastAction;
unsigned long currentTime;

bool encA1;
bool encA2;
bool encB1;
bool encB2;

// Blink led routine used for testing
bool blink = false;
void blinkLed() {
	blink = !blink;
	digitalWrite(LED_PIN,blink);
}

//The setup function is called once at startup of the sketch
void setup() {

	// Setup pin input/output settings
	pinMode(X_STEP_PIN  , OUTPUT);
	pinMode(X_DIR_PIN   , OUTPUT);
	pinMode(X_ENABLE_PIN, OUTPUT);
	pinMode(E_STEP_PIN  , OUTPUT);
	pinMode(E_DIR_PIN   , OUTPUT);
	pinMode(E_ENABLE_PIN, OUTPUT);
	pinMode(X_MIN_PIN   , INPUT_PULLUP );
	pinMode(X_MAX_PIN   , INPUT_PULLUP );

	pinMode(Y_STEP_PIN  , OUTPUT);
	pinMode(Y_DIR_PIN   , OUTPUT);
	pinMode(Y_ENABLE_PIN, OUTPUT);
	pinMode(Y_MIN_PIN   , INPUT_PULLUP );
	pinMode(Y_MAX_PIN   , INPUT_PULLUP );

	pinMode(Z_STEP_PIN  , OUTPUT);
	pinMode(Z_DIR_PIN   , OUTPUT);
	pinMode(Z_ENABLE_PIN, OUTPUT);
	pinMode(Z_MIN_PIN   , INPUT_PULLUP );
	pinMode(Z_MAX_PIN   , INPUT_PULLUP );

	pinMode(HEATER_0_PIN, OUTPUT);
	pinMode(HEATER_1_PIN, OUTPUT);
	pinMode(FAN_PIN     , OUTPUT);
	pinMode(LED_PIN     , OUTPUT);


	pinMode(X_ENCDR_A   , INPUT_PULLUP );
	pinMode(X_ENCDR_A_Q , INPUT_PULLUP );
	pinMode(X_ENCDR_B   , INPUT_PULLUP );
	pinMode(X_ENCDR_B_Q , INPUT_PULLUP );

	pinMode(Y_ENCDR_A   , INPUT_PULLUP );
	pinMode(Y_ENCDR_A_Q , INPUT_PULLUP );
	pinMode(Y_ENCDR_B   , INPUT_PULLUP );
	pinMode(Y_ENCDR_B_Q , INPUT_PULLUP );

	pinMode(Z_ENCDR_A   , INPUT_PULLUP );
	pinMode(Z_ENCDR_A_Q , INPUT_PULLUP );
	pinMode(Z_ENCDR_B   , INPUT_PULLUP );
	pinMode(Z_ENCDR_B_Q , INPUT_PULLUP );


	digitalWrite(X_ENABLE_PIN, HIGH);
	digitalWrite(E_ENABLE_PIN, HIGH);
	digitalWrite(Y_ENABLE_PIN, HIGH);
	digitalWrite(Z_ENABLE_PIN, HIGH);

	Serial.begin(115200);

	delay(100);

	encA1 = false;
	encA2 = false;
	encB1 = false;
	encB2 = false;

	// Initialize the inactivity check
	lastAction = millis();
}



// The loop function is called in an endless loop
void loop() {

	currentTime = millis();
	if (currentTime < lastAction) {

		// If the device timer overruns, reset the idle counter
		lastAction = millis();
	}
	else {

		if ((currentTime - lastAction) > 500) {


			encA1 = digitalRead(X_ENCDR_A);
			encA2 = digitalRead(X_ENCDR_A_Q);
			encB1 = digitalRead(X_ENCDR_B);
			encB2 = digitalRead(X_ENCDR_B_Q);

			// After an idle time, send the idle message
			Serial.print(": ");
			Serial.print(encA1);
			Serial.print(" ");
			Serial.print(encA2);
			Serial.print(" ");
			Serial.print(encB1);
			Serial.print(" ");
			Serial.print(encB2);
			Serial.print("\r\n");

			lastAction = millis();
		}
	}
}

