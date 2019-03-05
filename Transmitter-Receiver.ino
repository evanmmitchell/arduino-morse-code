/*
 * This Arduino sketch allows two boards to communicate with each other using Morse Code.
 * 
 * After uploading this sketch to two Arduino boards, a user may send a string input to one of the boards via the
 * Serial Monitor. This board then transmits in Morse Code each character of the input using an infrared emitter.
 * The other board simultaneously receives this message with an infrared sensor, converting the received Morse Code
 * back into English and printing it to the Serial Monitor. When the transmission is complete, new string inputs
 * may continue to be sent to either board to be transmitted and received as described above.
 * Note: If inputs are sent to both boards at the same time, neither will be received.
 */


//Define pins where the IR sensor, IR emitter, and LED signaling transmission connect to the board
const int RECEIVER_PIN = 2;
const int TRANSMITTER_PIN = 6;
const int TRANSMITTING_LED_PIN = LED_BUILTIN;

//Define the length of one Morse Code dot in milliseconds
const int TIME_UNIT = 10;

//Define Morse Code equivalent for each character
const int DOT = 1;
const int DASH = 3;
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
  {DASH, DASH, DASH, DOT, DOT, DOT},
  {DASH, DOT, DASH, DOT, DASH, DOT},
  {DOT, DASH, DASH, DASH, DASH, DOT},
  {DOT, DASH, DOT, DOT, DASH, DOT},
  {DASH, DOT, DOT, DASH, DOT},
  {DASH, DOT, DOT, DOT, DASH},
  {DOT, DASH, DOT, DASH, DOT},
  {DASH, DOT, DOT, DOT, DOT, DASH},
  {DOT, DOT, DOT, DOT, DOT, DOT}
};
const char CHARACTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I', 'J', 'K', 'L','M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X','Y', 'Z', '1', '2','3', '4', '5', '6', '7', '8', '9', '0', '.', ',', '?', '!','(', ')', ':', ';', '\'', '"', '/', '=', '+', '-', '*'};


int pulseLength(int pin, int value, int timeout){
  int onCounter = 0;
    while (onCounter < timeout && digitalRead(pin) == value){
      delay(1);
      onCounter++;
    }
  return onCounter;
}

void setup() {
  
  //Initialize Serial communication
  Serial.begin(9600);

  //Initialize pins as outputs and inputs
  pinMode(TRANSMITTER_PIN, OUTPUT);
  pinMode(TRANSMITTING_LED_PIN, OUTPUT);
  pinMode(RECEIVER_PIN, INPUT);
}

void loop() {
  String input;
  boolean transmitting = false;
  int currentPulse = 0;

  //Delay until either the IR sensor is activated or a string input is received from the Serial Monitor
  while (digitalRead(RECEIVER_PIN) == LOW && !transmitting) {
    delay(10);
    if (Serial.available() > 0) {
      input = Serial.readString();
      input.toUpperCase();
      transmitting = true;
    }
  }

  //If the IR sensor is activated, receive the Morse Code being transmitted and print the corresponding English characters to the Serial Monitor
  if (!transmitting) {
    Serial.println();
    Serial.print("   RECEIVING: ");

    //Iterate while receiving the same message
    while (currentPulse <= TIME_UNIT * 6) {
      int receivedMorseCode[10] = {0};
      int receivedIndex = 0;
      boolean sameCharacter = true;

      //Iterate while receiving the same character
      while (sameCharacter) {
        if (pulseLength(RECEIVER_PIN, HIGH, (TIME_UNIT * 100)) <= TIME_UNIT) {
         receivedMorseCode[receivedIndex] = DOT;
        } else {
          receivedMorseCode[receivedIndex] = DASH;
        }
        receivedIndex++;
        sameCharacter = pulseLength(RECEIVER_PIN, LOW, (TIME_UNIT + 1)) <= TIME_UNIT;
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
      currentPulse = pulseLength(RECEIVER_PIN, LOW, (TIME_UNIT * 6 + 1));
      if (currentPulse > TIME_UNIT * 2 && currentPulse <= TIME_UNIT * 6) {
        Serial.print(' ');
      }
    } 
  }

  //Otherwise, if a string input has been received, transmit each character of that input in Morse Code while an LED signaling transmission is lit
  if (transmitting) {
    digitalWrite(TRANSMITTING_LED_PIN, HIGH);
    Serial.println();
    Serial.print("TRANSMITTING: ");

    //Iterate until the last character of the input is transmitted
    for (int transmitIndex = 0; transmitIndex < input.length(); transmitIndex++) {

      //If the current character is a space character, delay for an additional four time units (seven total)
      if (input[transmitIndex] == ' ') {
        Serial.print(' ');
        delay(TIME_UNIT * 4);
      }

      //If the current character is a character other than a space or a new line, match the English character with the corresponding Morse Code
      if (input[transmitIndex] != 10 && input[transmitIndex] != 13 && input[transmitIndex] != ' ') {
        int characterIndex = 0;
        while (characterIndex < (sizeof(CHARACTERS) - 1) && input[transmitIndex] != CHARACTERS[characterIndex]) {
          characterIndex++;
        }      
        Serial.print(CHARACTERS[characterIndex]);
        for (int dotDashIndex = 0; MORSE_CODE[characterIndex][dotDashIndex] != 0; dotDashIndex++) {
          digitalWrite(TRANSMITTER_PIN, HIGH);
          delay(TIME_UNIT * MORSE_CODE[characterIndex][dotDashIndex]);
          digitalWrite(TRANSMITTER_PIN, LOW);
          delay(TIME_UNIT);
        }
        delay(TIME_UNIT * 2);
      }
    }
    delay(TIME_UNIT * 5);
    digitalWrite(TRANSMITTING_LED_PIN, LOW);
  }
}
