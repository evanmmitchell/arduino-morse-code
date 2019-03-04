String input = "Hello, World!";

const int DOT = 1;
const int DASH = 2;
int ledPin = 6;
int timeUnit = 200;

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

const char CHARACTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I', 'J', 'K', 'L','M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X','Y', 'Z', '1', '2','3', '4', '5', '6', '7', '8', '9', '0', '.', ',', '?', '!','(', ')', ':', ';'}; //could add duplicate at end in case character doesn't match any of these

void transmitMorseCode(const int currentChar[]) {
  for (int k = 0; currentChar[k] != 0; k++) {
    if (currentChar[k] == DOT) {
      digitalWrite(ledPin, HIGH);
      delay(timeUnit);
      digitalWrite(ledPin, LOW);
    } else if (currentChar[k] == DASH) {
      digitalWrite(ledPin, HIGH);
      delay(timeUnit * 3);
      digitalWrite(ledPin, LOW);
    }
    delay(timeUnit);
  }
  delay(timeUnit * 2);
}

void transmitStringInMorseCode(String textInput) {
  for (int i = 0; i < textInput.length(); i++) {
    if (textInput[i] == ' ') {
      delay(timeUnit * 4);
    } else {
      int j = 0;
      while (j < sizeof(CHARACTERS) && textInput[i] != CHARACTERS[j]) {
        j++;
      }
      if (j < sizeof(CHARACTERS)) {
        Serial.print(CHARACTERS[j]);
        transmitMorseCode(MORSE_CODE[j]);
      } else {
        Serial.print('*');
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  input.toUpperCase();
}

void loop() {
  transmitStringInMorseCode(input);
  delay(timeUnit * 28);
  Serial.println();
}
