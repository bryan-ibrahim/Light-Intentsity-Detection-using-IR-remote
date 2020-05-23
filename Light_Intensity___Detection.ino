#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

int redLEDPin = 13;
int greenLEDPin = 12;
int yellowLEDPin = 11;

int lightIntensity = 0;

int RECV_PIN = 7;

IRrecv irrecv(RECV_PIN);

decode_results results;

boolean lightDetection = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);


  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  //  Serial.println("Should turn on");

  //  digitalWrite(redLEDPin, HIGH);
  //  digitalWrite(greenLEDPin, HIGH);
  //  digitalWrite(yellowLEDPin, HIGH);
  //  delay(1000);
  //  digitalWrite(redLEDPin, LOW);
  //  digitalWrite(greenLEDPin, LOW);
  //  digitalWrite(yellowLEDPin, LOW);
  //  delay(1000);

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value

    //RED LIGHT ON/OFF
    if (results.value == 0xFFC23D || results.value == 0x20FE4DBB) {
      if (lightDetection) {
        Serial.println("OFF");
        lightDetection = false;
      } else {
        Serial.println("ON");
        lightDetection = true;
      }
    }
  }

  if (lightDetection) {
    lightIntensity = analogRead(A5);
    Serial.println(lightIntensity);

    //Darkest
    if (lightIntensity <= 10) {
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(yellowLEDPin, LOW);
    }

    //Darker
    else if (lightIntensity > 10 && lightIntensity <= 20) {
      digitalWrite(redLEDPin, LOW);
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(yellowLEDPin, LOW);
    }

    //A bit dark
    else if (lightIntensity > 20 && lightIntensity <= 30) {
      digitalWrite(redLEDPin, LOW);
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(yellowLEDPin, HIGH);
    }

    //There's enough light, hence turn off all the LEDs
    else {
      digitalWrite(redLEDPin, LOW);
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(yellowLEDPin, LOW);
    }

    delay(100);
  } else {
    //USER DOES NOT WANT TO DETECT LIGHT, HENCE TURN OFF ALL THE LIGHTS IF THEY'RE ON
    digitalWrite(redLEDPin, LOW);
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(yellowLEDPin, LOW);
  }
  delay(100);
}
