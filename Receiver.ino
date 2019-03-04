int inputPin = 2;
int timeUnit = 200;
int testFrequency = 10;
boolean initiated = false;
unsigned long previousMillis;

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

void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
}

void loop() {
  int offCounter = 0;
  while (digitalRead(inputPin) == LOW) {
    delay(timeUnit / testFrequency);
    offCounter++;
  }
  if (offCounter > testFrequency * 3 && offCounter <= testFrequency * 8 && initiated) {
    Serial.print(' ');
  } else if (offCounter > testFrequency * 8 && initiated) {
    Serial.println();
  }

  initiated = true;
  previousMillis = millis();
  int currentMorseCode[10];
  int index = 0;
  int numberOfDots = 0;
  int numberOfDashes = 0;

  while ((millis() - timeUnit - previousMillis) < (timeUnit * numberOfDots * 2 + timeUnit * numberOfDashes * 4)) {
    if (index < sizeof(currentMorseCode)) {
      int onCounter = 0;
      while (digitalRead(inputPin) == HIGH){
        delay(timeUnit / testFrequency);
        onCounter++;
      }
      if (onCounter <= testFrequency) {
        currentMorseCode[index] = DOT;
        numberOfDots++;
        index++;
      } else if (onCounter <= testFrequency * 3) {
        currentMorseCode[index] = DASH;
        numberOfDashes++;
        index++;
      } else {
        index = sizeof(currentMorseCode);
      }
      offCounter = 0;
      while (digitalRead(inputPin) == LOW && offCounter <= testFrequency) {
        delay(timeUnit / testFrequency);
        offCounter++;
      }
    } else {
      Serial.println("ERROR: Check value of timeUnit");
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
