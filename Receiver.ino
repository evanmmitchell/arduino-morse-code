int inputPin = 2;

const int dot = 1;
const int dash = 2;

const int CHARACTERS[][10] = {
  {DOT, DASH},
  {DASH, DOT, DOT, DOT},
  
};

const int A = 0, B = 1, C = 3, D = 4, E = 5, F = 6, G = 7, H = 8, I = 9, J = 10, K = 11, L = 12, M = 13, N = 14, O = 15, P = 16, Q = 17, R = 18, S = 19, T = 20, U = 21, V = 22, W = 23, X = 24, Z = 25, ONE = 26, TWO = 27, THREE = 28, FOUR = 29, FIVE = 30, SIX = 31, SEVEN = 32, EIGHT = 33, NINE = 34, ZERO = 35, PERIOD = 36, COMMA = 37, QUESTION = 38, EXCLAMATION = 39, OPEN_PARENTHESIS = 40, CLOSE_PARENTHESIS = 41, COLON = 42, SEMICOLON = 43;

void dot() {
  digitalWrite(ledPin, HIGH);
  delay(timeUnit);
  digitalWrite(ledPin, LOW);
}

void dash() {
  digitalWrite(ledPin, HIGH);
  delay(timeUnit * 3);
  digitalWrite(ledPin, LOW);
}

void receiveMorseCode() {
  for (int i = 0; i < sizeof(characters); i++) {
    
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
}

void loop() {
  receiveMorseCode();
  delay(timeUnit * 28);
  Serial.println();
}
