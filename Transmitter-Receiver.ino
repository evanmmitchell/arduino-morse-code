const int RECEIVER_PIN = 2;
const int TRANSMITTER_PIN = 6;
const int TRANSMITTING_LED_PIN = LED_BUILTIN;

const int TIME_UNIT = 100;
const int TEST_FREQUENCY = 10;

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

const char CHARACTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I', 'J', 'K', 'L','M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X','Y', 'Z', '1', '2','3', '4', '5', '6', '7', '8', '9', '0', '.', ',', '?', '!','(', ')', ':', ';', '\'', '"', '/', '=', '+', '-', '*'};


void setup() {
  Serial.begin(9600);
  pinMode(TRANSMITTER_PIN, OUTPUT);
  pinMode(TRANSMITTING_LED_PIN, OUTPUT);
  pinMode(RECEIVER_PIN, INPUT_PULLUP);
}

void loop() {
  String input;
  boolean transmitting = false;

  while (digitalRead(RECEIVER_PIN) == LOW && !transmitting) {
    delay(TIME_UNIT / TEST_FREQUENCY);
    if (Serial.available() > 0) {
      input = Serial.readString();
      input.toUpperCase();
      transmitting = true;
    }
  }

  if (!transmitting) {
    Serial.println();
    Serial.print("   RECEIVING: ");
    int counter = 0;
    while (counter <= TEST_FREQUENCY * 6) {
      int receivedMorseCode[10] = {0};
      int receivedIndex = 0;
      while (counter <= TEST_FREQUENCY) {
        counter = 0;
        while (digitalRead(RECEIVER_PIN) == HIGH){
          delay(TIME_UNIT / TEST_FREQUENCY);
          counter++;
        }
        if (counter <= TEST_FREQUENCY) {
          receivedMorseCode[receivedIndex] = DOT;
        } else {
          receivedMorseCode[receivedIndex] = DASH;
        }
        receivedIndex++;
        counter = 0;
        while (digitalRead(RECEIVER_PIN) == LOW && counter <= TEST_FREQUENCY) {
          delay(TIME_UNIT / TEST_FREQUENCY);
          counter++;
        }
      }
      for (int characterIndex = 0; characterIndex < sizeof(CHARACTERS); characterIndex++) {
        for (int dotDashIndex = 0; dotDashIndex < sizeof(receivedMorseCode) && MORSE_CODE[characterIndex][dotDashIndex] == receivedMorseCode[dotDashIndex]; dotDashIndex++) {
          if (receivedMorseCode[dotDashIndex] == 0) {
            Serial.print(CHARACTERS[characterIndex]);
            characterIndex = sizeof(CHARACTERS);
            break;
          }
        }
      }
      counter = 0;
      while (digitalRead(RECEIVER_PIN) == LOW && counter <= TEST_FREQUENCY * 6) {
        delay(TIME_UNIT / TEST_FREQUENCY);
        counter++;
      }
      if (counter > TEST_FREQUENCY * 2 && counter <= TEST_FREQUENCY * 6) {
        Serial.print(' ');
      }
    } 
  }

  if (transmitting) {
    digitalWrite(TRANSMITTING_LED_PIN, HIGH);
    Serial.println();
    Serial.print("TRANSMITTING: ");
    for (int transmitIndex = 0; transmitIndex < input.length(); transmitIndex++) {
      if (input[transmitIndex] == ' ') {
        Serial.print(' ');
        delay(TIME_UNIT * 4);
      } else if (input[transmitIndex] != 10 && input[transmitIndex] != 13) {
        int characterIndex = 0;
        while (characterIndex < (sizeof(CHARACTERS) - 1) && input[transmitIndex] != CHARACTERS[characterIndex]) {
          characterIndex++;
        }      
        Serial.print(CHARACTERS[characterIndex]);
        for (int dotDashIndex = 0; MORSE_CODE[characterIndex][dotDashIndex] != 0; dotDashIndex++) {
          if (MORSE_CODE[characterIndex][dotDashIndex] == DOT) {
            digitalWrite(TRANSMITTER_PIN, HIGH);
            delay(TIME_UNIT);
            digitalWrite(TRANSMITTER_PIN, LOW);
          } else {
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
