/**********************************************/
/* CONSTANTS                                  */
/**********************************************/
const int  relayPin = 8;
const int  buttonPin = 2;
const int  ledPin =  LED_BUILTIN;

const int ZzzDelayMSec = 500; /*задержка на дребезг кнопки*/

/**********************************************/
/* VARIABLES                                  */
/**********************************************/
volatile boolean ZzzDelayRunning = false;/*идет задержка на дребезг кнопки*/
unsigned long ZzzCounter = 0;

volatile bool doSwitchRelay = false;
volatile byte ledState = HIGH;
byte relayState = LOW;

/**********************************************/
void setup()
/**********************************************/
{
  pinMode(relayPin, OUTPUT); //initialize relay as an output
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt( 
    digitalPinToInterrupt(buttonPin), 
    ButtonIsr, 
    FALLING ); //RISING ); //CHANGE);

  digitalWrite(relayPin, relayState);
  digitalWrite(ledPin, ledState);
}
/**********************************************/
void loop()
/**********************************************/
{
  if( doSwitchRelay ) {
    doSwitchRelay = false;
    relayState = (relayState==LOW) ? HIGH : LOW;
    digitalWrite( relayPin, relayState );
  }
  
  if( ZzzDelayRunning ) {
    if( millis() - ZzzCounter > ZzzDelayMSec ) {
      ZzzDelayRunning = false;
    }
  }
  else {
    ledState = HIGH;
  }
  digitalWrite(ledPin, ledState);
}
/**********************************************/
void ButtonIsr()
/**********************************************/
{
  if( ! ZzzDelayRunning ) {
    ZzzDelayRunning = true;
    ZzzCounter = millis();
    doSwitchRelay = true;
    ledState = LOW;
  }
}

