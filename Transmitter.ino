String input = "Hello, World!";

const int DOT = 1;
const int DASH = 2;
int ledPin = 6;
int timeUnit = 200;

const int CHARACTERS[][10] = {
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
  
};

const int A = 0, B = 1, C = 3, D = 4, E = 5, F = 6, G = 7, H = 8, I = 9, J = 10, K = 11, L = 12, M = 13, N = 14, O = 15, P = 16, Q = 17, R = 18, S = 19, T = 20, U = 21, V = 22, W = 23, X = 24, Z = 25, ONE = 26, TWO = 27, THREE = 28, FOUR = 29, FIVE = 30, SIX = 31, SEVEN = 32, EIGHT = 33, NINE = 34, ZERO = 35, PERIOD = 36, COMMA = 37, QUESTION = 38, EXCLAMATION = 39, OPEN_PARENTHESIS = 40, CLOSE_PARENTHESIS = 41, COLON = 42, SEMICOLON = 43;

void transmitMorseCode(const int currentChar[]) {
  for (int i = 0; currentChar[i] != 0; i++) {
    if (currentChar[i] == DOT) {
      digitalWrite(ledPin, HIGH);
      delay(timeUnit);
      digitalWrite(ledPin, LOW);
    } else if (currentChar[i] == DASH) {
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
    Serial.print(textInput[i]);
    switch (textInput[i]) {
      case ' ':
        delay(timeUnit * 4);
        break;
      case 'A':
        transmitMorseCode(CHARACTERS[A]);
        break;
      case 'B':
        transmitMorseCode(CHARACTERS[B]);
        break;
      case 'C':
        transmitMorseCode();
        break;
      case 'D':
        transmitMorseCode();
        break;
      case 'E':
        transmitMorseCode();
        break;
      case 'F':
        transmitMorseCode();
        break;
      case 'G':
        transmitMorseCode();
        break;
      case 'H':
        transmitMorseCode();
        break;
      case 'I':
        transmitMorseCode();
        break;
      case 'J':
        transmitMorseCode();
        break;
      case 'K':
        transmitMorseCode();
        break;
      case 'L':
        transmitMorseCode();
        break;
      case 'M':
        transmitMorseCode();
        break;
      case 'N':
        transmitMorseCode();
        break;
      case 'O':
        transmitMorseCode();
        break;
      case 'P':
        transmitMorseCode();
        break;
      case 'Q':
        transmitMorseCode();
        break;
      case 'R':
        transmitMorseCode();
        break;
      case 'S':
        transmitMorseCode();
        break;
      case 'T':
        transmitMorseCode();
        break;
      case 'U':
        transmitMorseCode();
        break;
      case 'V':
        transmitMorseCode();
        break;
      case 'W':
        transmitMorseCode();
        break;
      case 'X':
        transmitMorseCode();
        break;
      case 'Y':
        transmitMorseCode();
        break;
      case 'Z':
        transmitMorseCode({DASH, DASH, DOT, DOT});
        break;
      case '1':
        transmitMorseCode({DOT, DASH, DASH, DASH, DASH});
        break;
      case '2':
        transmitMorseCode({DOT, DOT, DASH, DASH, DASH});
        break;
      case '3':
        transmitMorseCode({DOT, DOT, DOT, DASH, DASH});
        break;
      case '4':
        transmitMorseCode({DOT, DOT, DOT, DOT, DASH});
        break;
      case '5':
        transmitMorseCode({DOT, DOT, DOT, DOT, DOT});
        break;
      case '6':
        transmitMorseCode({DASH, DOT, DOT, DOT, DOT});
        break;
      case '7':
        transmitMorseCode({DASH, DASH, DOT, DOT, DOT});
        break;
      case '8':
        transmitMorseCode({DASH, DASH, DASH, DOT, DOT});
        break;
      case '9':
        transmitMorseCode({DASH, DASH, DASH, DASH, DOT});
        break;
      case '0':
        transmitMorseCode({DASH, DASH, DASH, DASH, DASH});
        break;
      case '.':
        transmitMorseCode({DOT, DASH, DOT, DASH, DOT, DASH});
        break;
      case ',':
        transmitMorseCode({DASH, DASH, DOT, DOT, DASH, DASH});
        break;
      case '?':
        transmitMorseCode({DOT, DOT, DASH, DASH, DOT, DOT});
        break;
      case '!':
        transmitMorseCode({DASH, DOT, DASH, DOT, DASH, DASH});
        break;
      case '(':
        transmitMorseCode({DASH, DOT, DASH, DASH, DOT});
        break;
      case ')':
        transmitMorseCode({DASH, DOT, DASH, DASH, DOT, DASH});
        break;
      case ':':
        transmitMorseCode({DASH, DASH, DASH, DOT, DOT});
        break;
      case ';':
        transmitMorseCode({DASH, DOT, DASH, DOT, DASH});
        break;
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
