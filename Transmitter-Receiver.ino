String input = "Hello, World!";

boolean transmitOrNot = true;
int transmitIndex = 0;
int offCounter = 0;

const int TRANSMIT_OR_NOT_LED_PIN = LED_BUILTIN;
const int LED_PIN = 6;
const int INPUT_PIN = 2;
const int TIME_UNIT = 200;
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
  {DASH, DOT, DASH, DOT, DASH}
};

const char CHARACTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I', 'J', 'K', 'L','M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X','Y', 'Z', '1', '2','3', '4', '5', '6', '7', '8', '9', '0', '.', ',', '?', '!','(', ')', ':', ';'};

void transmit() {
    if (input[transmitIndex] == ' ') {
      Serial.print(' ');
      delay(TIME_UNIT * 4);
    } else {
      int characterIndex = 0;
      while (characterIndex < sizeof(CHARACTERS) && input[transmitIndex] != CHARACTERS[characterIndex]) {
        characterIndex++;
      }
      if (characterIndex < sizeof(CHARACTERS)) {
        Serial.print(CHARACTERS[characterIndex]);
        for (int dotDashIndex = 0; MORSE_CODE[characterIndex][dotDashIndex] != 0; dotDashIndex++) {
          if (MORSE_CODE[characterIndex][dotDashIndex] == DOT) {
            digitalWrite(LED_PIN, HIGH);
            delay(TIME_UNIT);
            digitalWrite(LED_PIN, LOW);
          } else if (MORSE_CODE[characterIndex][dotDashIndex] == DASH) {
            digitalWrite(LED_PIN, HIGH);
            delay(TIME_UNIT * 3);
            digitalWrite(LED_PIN, LOW);
         }
         delay(TIME_UNIT);
        }
        delay(TIME_UNIT * 2);
      } else {
        Serial.print('*');
      }
    }
}

void receive() {
  boolean sameCharacter = true;
  int receivedMorseCode[10] = {0};
  int receiveIndex = 0;
  int numberOfDots = 0;
  int numberOfDashes = 0;

  while (sameCharacter) {
    if (receiveIndex < sizeof(receivedMorseCode)) {
      int onCounter = 0;
      while (digitalRead(INPUT_PIN) == HIGH){
        delay(TIME_UNIT / TEST_FREQUENCY);
        onCounter++;
      }
      if (onCounter <= TEST_FREQUENCY) {
        receivedMorseCode[receiveIndex] = DOT;
        numberOfDots++;
        receiveIndex++;
      } else if (onCounter <= TEST_FREQUENCY * 3) {
        receivedMorseCode[receiveIndex] = DASH;
        numberOfDashes++;
        receiveIndex++;
      } else {
        receiveIndex = sizeof(receivedMorseCode);
      }
      offCounter = 0;
      while (digitalRead(INPUT_PIN) == LOW && offCounter <= TEST_FREQUENCY) {
        delay(TIME_UNIT / TEST_FREQUENCY);
        offCounter++;
      }
      if (offCounter > TEST_FREQUENCY) {
        sameCharacter = false;
      }
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
  while (digitalRead(INPUT_PIN) == LOW) {
    delay(TIME_UNIT / TEST_FREQUENCY);
    offCounter++;
  }
  if (offCounter > TEST_FREQUENCY * 3 && offCounter <= TEST_FREQUENCY * 8) {
    Serial.print(' ');
  } else if (offCounter > TEST_FREQUENCY * 8) {
    Serial.println();
    Serial.print("RECEIVING: ");
  }
}

void checkForInput() {
  if (Serial.available() > 0) {
    input = Serial.readString();
    input.toUpperCase();
    transmitOrNot = true;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRANSMIT_OR_NOT_LED_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
  input.toUpperCase();
}

void loop() {
  if (transmitOrNot) {
    digitalWrite(TRANSMIT_OR_NOT_LED_PIN, HIGH);
    Serial.println();
    Serial.print("TRANSMITTING: ");
    transmitIndex = 0;
    while (transmitOrNot) {
      transmit();
      transmitIndex++;
      if (transmitIndex == input.length()) {
        transmitIndex = 0;
        transmitOrNot = false;
      }
    }
  }

  if (!transmitOrNot) {
    digitalWrite(TRANSMIT_OR_NOT_LED_PIN, LOW);
    while (digitalRead(INPUT_PIN) == LOW && !transmitOrNot) {
      delay(TIME_UNIT / TEST_FREQUENCY);
      checkForInput();
    }
    if (!transmitOrNot) {
      Serial.println();
      Serial.print("RECEIVING: ");
    }
    while (!transmitOrNot) {
      receive();
    }
  }
}
