/*
This Arduino sketch allows two boards to communicate with each other using Morse Code.

After uploading this sketch to two Arduino boards, a user may send a string input to one of the boards via the Serial Monitor. This board then transmits in Morse Code each character of the input using an infrared emitter. The other board simultaneously receives this message with an infrared sensor, converting the received Morse Code back into English and printing it to the Serial Monitor. When the transmission is complete, new string inputs may continue to be sent to either board to be transmitted and received as described above.
NB: If inputs are sent to both boards at the same time, neither will be received.

String input from Serial Monitor (input) --> Morse Code transmitted by IR emitter (output)
Morse Code received by IR sensor (input) --> English characters printed to the Serial Monitor (output)
*/

//Define pins where the IR sensor, IR emitter, and LED signaling transmission connect to the board
const int RECEIVER_PIN = 2;
const int TRANSMITTER_PIN = 6;
const int TRANSMITTING_LED_PIN = LED_BUILTIN;

const int TIME_UNIT = 100;       //the length of one Morse Code dot in milliseconds
const int TEST_FREQUENCY = 10;   //the number of times per time unit a change should be tested for


//Define Morse Code equivalent for each character
const char CHARACTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I', 'J', 'K', 'L','M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X','Y', 'Z', '1', '2','3', '4', '5', '6', '7', '8', '9', '0', '.', ',', '?', '!','(', ')', ':', ';', '\'', '"', '/', '=', '+', '-', '*'};

const int DOT = 1;
const int DASH = 2;

const int MORSE_CODE[][10] = {
  {DOT, DASH},
  {DASH, DOT, DOT, DOT},
  {DASH, DOT, DASH, DOT},
  {DASH, DOT, DOT},
  {DOT},
  {DOT, DOT, DASH, DOT},
  {DASH, DASH, DOT},
  {DOT, DOT, DOT, DOT},
  {DOT, DOT},
  {DOT, DASH, DASH, DASH},
  {DASH, DOT, DASH},
  {DOT, DASH, DOT, DOT},
  {DASH, DASH},
  {DASH, DOT},
  {DASH, DASH, DASH},
  {DOT,DASH, DASH, DOT},
  {DASH, DASH, DOT, DASH},
  {DOT, DASH, DOT},
  {DOT, DOT, DOT},
  {DASH},
  {DOT, DOT, DASH},
  {DOT, DOT, DOT, DASH},
  {DOT, DASH, DASH},
  {DASH, DOT, DOT, DASH},
  {DASH, DOT, DASH, DASH},
  {DASH, DASH, DOT, DOT},
  {DOT, DASH, DASH, DASH, DASH},
  {DOT, DOT, DASH, DASH, DASH},
  {DOT, DOT, DOT, DASH, DASH},
  {DOT, DOT, DOT, DOT, DASH},
  {DOT, DOT, DOT, DOT, DOT},
  {DASH, DOT, DOT, DOT, DOT},
  {DASH, DASH, DOT, DOT, DOT},
  {DASH, DASH, DASH, DOT, DOT},
  {DASH, DASH, DASH, DASH, DOT},
  {DASH, DASH, DASH, DASH, DASH},
  {DOT, DASH, DOT, DASH, DOT, DASH},
  {DASH, DASH, DOT, DOT, DASH, DASH},
  {DOT, DOT, DASH, DASH, DOT, DOT},
  {DASH, DOT, DASH, DOT, DASH, DASH},
  {DASH, DOT, DASH, DASH, DOT},
  {DASH, DOT, DASH, DASH, DOT, DASH},
  {DASH, DASH, DASH, DOT, DOT},
  {DASH, DOT, DASH, DOT, DASH},
  {DOT, DASH, DASH, DASH, DASH, DOT},
  {DOT, DASH, DOT, DOT, DASH, DOT},
  {DASH, DOT, DOT, DASH, DOT},
  {DASH, DOT, DOT, DOT, DASH},
  {DOT, DASH, DOT, DASH, DOT},
  {DASH, DOT, DOT, DOT, DOT, DASH},
  {DOT, DOT, DOT, DOT, DOT, DOT}
};


void setup() {
  //Initialize Serial communication
  Serial.begin(9600);
  //Initialize pins as outputs and inputs
  pinMode(TRANSMITTER_PIN, OUTPUT);
  pinMode(TRANSMITTING_LED_PIN, OUTPUT);
  pinMode(RECEIVER_PIN, INPUT_PULLUP);
}

void loop() {
  String input;
  boolean transmitting = false;

  //Delay until either the IR sensor is activated or a string input is received from the Serial Monitor
  while (digitalRead(RECEIVER_PIN) == HIGH && !transmitting) {
    delay(TIME_UNIT / TEST_FREQUENCY);
    if (Serial.available() > 0) {
      input = Serial.readString();
      input.toUpperCase();
      transmitting = true;
    }
  }


  //If the IR sensor is activated, receive the Morse Code being transmitted and print the 
  //corresponding English characters to the Serial Monitor
  if (!transmitting) {
    Serial.println();
    Serial.print("   RECEIVING: ");

    int counter = 0;
    while (counter <= TEST_FREQUENCY * 6) {         //Iterate while receiving the same message
      int receivedMorseCode[10] = {0};              //array to store received dots and dashes
      int receivedIndex = 0;

      while (counter <= TEST_FREQUENCY) {           //Iterate while receiving the same character
        //Delay and count while the IR sensor is activated to determine whether a dot or dash is being received
        counter = 0;
        while (digitalRead(RECEIVER_PIN) == LOW){
          delay(TIME_UNIT / TEST_FREQUENCY);
          counter++;
        }
        if (counter <= TEST_FREQUENCY) {            //if IR sensor is activated for up to one time unit
          receivedMorseCode[receivedIndex] = DOT;
        } else {                                    //if IR sensor is activated for more than one time unit
          receivedMorseCode[receivedIndex] = DASH;
        }
        receivedIndex++;

        //Delay and count while the IR sensor is not activated to see if the same character is still being received
        counter = 0;
        while (digitalRead(RECEIVER_PIN) == HIGH && counter <= TEST_FREQUENCY) {
          delay(TIME_UNIT / TEST_FREQUENCY);
          counter++;
        }
      }

      //Match the received Morse Code array to its corresponding English character and print the character to the Serial Monitor
      for (int characterIndex = 0; characterIndex < sizeof(CHARACTERS); characterIndex++) {
        for (int dotDashIndex = 0; dotDashIndex < sizeof(receivedMorseCode) && MORSE_CODE[characterIndex][dotDashIndex] == receivedMorseCode[dotDashIndex]; dotDashIndex++) {
          if (receivedMorseCode[dotDashIndex] == 0) {
            Serial.print(CHARACTERS[characterIndex]);
            characterIndex = sizeof(CHARACTERS);
            break;
          }
        }
      }

      //Delay and count while IR sensor is not activated to see if the same word or else the same message is still being received
      counter = 0;
      while (digitalRead(RECEIVER_PIN) == HIGH && counter <= TEST_FREQUENCY * 6) {
        delay(TIME_UNIT / TEST_FREQUENCY);
        counter++;
      }
      if (counter > TEST_FREQUENCY * 2 && counter <= TEST_FREQUENCY * 6) {
        Serial.print(' ');
      }
    } 
  }


  //Otherwise, if a string input has been received, transmit each character of that input in 
  //Morse Code while an LED signaling transmission is lit
  if (transmitting) {
    digitalWrite(TRANSMITTING_LED_PIN, HIGH);   //Light LED signaling transmission
    Serial.println();
    Serial.print("TRANSMITTING: ");

    //Iterate until the last character of the input is transmitted
    for (int transmitIndex = 0; transmitIndex < input.length(); transmitIndex++) {
      //If the current character is a space character, delay for an additional four time units (seven total)
      if (input[transmitIndex] == ' ') {
        Serial.print(' ');
        delay(TIME_UNIT * 4);
      } else if (input[transmitIndex] != 10 && input[transmitIndex] != 13) {   //if it is a character other than a space or a new line
        int characterIndex = 0;
        //Match the English character with the corresponding Morse Code
        while (characterIndex < (sizeof(CHARACTERS) - 1) && input[transmitIndex] != CHARACTERS[characterIndex]) {
          characterIndex++;
        }      
        Serial.print(CHARACTERS[characterIndex]);   //Print character being transmitted to the Serial Monitor
        for (int dotDashIndex = 0; MORSE_CODE[characterIndex][dotDashIndex] != 0; dotDashIndex++) {
          //If the current Morse Code is a dot, transmit a dot.
          if (MORSE_CODE[characterIndex][dotDashIndex] == DOT) {
            digitalWrite(TRANSMITTER_PIN, HIGH);
            delay(TIME_UNIT);
            digitalWrite(TRANSMITTER_PIN, LOW);
          } else {   //If the current Morse Code is a dash, transmit a dash.
            digitalWrite(TRANSMITTER_PIN, HIGH);
            delay(TIME_UNIT * 3);
            digitalWrite(TRANSMITTER_PIN, LOW);
          }
          delay(TIME_UNIT);
        }
        delay(TIME_UNIT * 2);
      }
    }
    delay(TIME_UNIT * 5);
    digitalWrite(TRANSMITTING_LED_PIN, LOW);
  }
}
