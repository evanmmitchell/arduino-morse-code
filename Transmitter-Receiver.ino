String input = "Hello, World!";
boolean transmit = true;

int offCounter = 0;
boolean initiated = false;

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
  for (int i = 0; i < input.length(); i++) {
    if (input[i] == ' ') {
      Serial.print(' ');
      delay(TIME_UNIT * 4);
    } else {
      int j = 0;
      while (j < sizeof(CHARACTERS) && input[i] != CHARACTERS[j]) {
        j++;
      }
      if (j < sizeof(CHARACTERS)) {
        Serial.print(CHARACTERS[j]);
        for (int k = 0; MORSE_CODE[j][k] != 0; k++) {
          if (MORSE_CODE[j][k] == DOT) {
            digitalWrite(LED_PIN, HIGH);
            delay(TIME_UNIT);
            digitalWrite(LED_PIN, LOW);
          } else if (MORSE_CODE[j][k] == DASH) {
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
}

void receive() {
  while (digitalRead(INPUT_PIN) == LOW) {
    delay(TIME_UNIT / TEST_FREQUENCY);
    offCounter++;
  }
  if (offCounter > TEST_FREQUENCY * 3 && offCounter <= TEST_FREQUENCY * 8 && initiated) {
    Serial.print(' ');
  } else if (offCounter > TEST_FREQUENCY * 8 && initiated) {
    Serial.println();
  }

  initiated = true;
  boolean sameCharacter = true;
  int currentMorseCode[10] = {0};
  int index = 0;
  int numberOfDots = 0;
  int numberOfDashes = 0;

  while (sameCharacter) {
    if (index < sizeof(currentMorseCode)) {
      int onCounter = 0;
      while (digitalRead(INPUT_PIN) == HIGH){
        delay(TIME_UNIT / TEST_FREQUENCY);
        onCounter++;
      }
      if (onCounter <= TEST_FREQUENCY) {
        currentMorseCode[index] = DOT;
        numberOfDots++;
        index++;
      } else if (onCounter <= TEST_FREQUENCY * 3) {
        currentMorseCode[index] = DASH;
        numberOfDashes++;
        index++;
      } else {
        index = sizeof(currentMorseCode);
      }
      offCounter = 0;
      while (digitalRead(INPUT_PIN) == LOW && offCounter <= TEST_FREQUENCY * 1) {
        delay(TIME_UNIT / TEST_FREQUENCY);
        offCounter++;
      }
      if (offCounter > TEST_FREQUENCY * 1) {
        sameCharacter = false;
      }
    }
  }

  for (int i = 0; i < sizeof(MORSE_CODE); i++) {
    for (int j = 0; j < sizeof(currentMorseCode) && MORSE_CODE[i][j] == currentMorseCode[j]; j++) {
      if (currentMorseCode[j] == 0) {
        Serial.print(CHARACTERS[i]);
        i = sizeof(MORSE_CODE);
        break;
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
  input.toUpperCase();
}

void loop() {
  while (transmit) {
    delay(TIME_UNIT * 28);
    Serial.print("TRANSMITTING: ")
    transmit();
    Serial.println();
  }
  while (!transmit) {
    Serial.print("RECEIVING: ")
    receive();
  }
}
