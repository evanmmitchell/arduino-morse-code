String input = "Hello, World!";
int ledPin = 6;
int timeUnit = 200;

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

void transmitStringInMorseCode(String textInput) {
  for (int i = 0; i < textInput.length(); i++) {
    switch (textInput[i]) {
      case ' ':
        Serial.print(' ');
        delay(timeUnit * 4);
        break;
      case 'A':
        Serial.print('A');
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case 'B':
        Serial.print('B');
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case 'C':
        Serial.print('C');
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case 'D':
        Serial.print('D');
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case 'E':
        Serial.print('E');
        dot();
        delay(timeUnit * 3);
        break;
      case 'F':
        Serial.print('F');
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case 'G':
        Serial.print('G');
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case 'H':
        Serial.print('H');
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case 'I':
        Serial.print('I');
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case 'J':
        Serial.print('J');
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case 'K':
        Serial.print('K');
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;      
      case 'L':
        Serial.print('L');
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case 'M':
        Serial.print('M');
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case 'N':
        Serial.print('N');
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case 'O':
        Serial.print('O');
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case 'P':
        Serial.print('P');
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case 'Q':
        Serial.print('Q');
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case 'R':
        Serial.print('R');
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case 'S':
        Serial.print('S');
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case 'T':
        Serial.print('T');
        dash();
        delay(timeUnit * 3);
        break;
      case 'U':
        Serial.print('U');
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case 'V':
        Serial.print('V');
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case 'W':
        Serial.print('W');
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case 'X':
        Serial.print('X');
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case 'Y':
        Serial.print('Y');
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case 'Z':
        Serial.print('Z');
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case '1':
        Serial.print('1');
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case '2':
        Serial.print('2');
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case '3':
        Serial.print('3');
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case '4':
        Serial.print('4');
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case '5':
        Serial.print('5');
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case '6':
        Serial.print('6');
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case '7':
        Serial.print('7');
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case '8':
        Serial.print('8');
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case '9':
        Serial.print('9');
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case '0':
        Serial.print('0');
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case '.':
        Serial.print('.');
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case ',':
        Serial.print(',');
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case '?':
        Serial.print('?');
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case '!':
        Serial.print('!');
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case '(':
        Serial.print('(');
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case ')':
        Serial.print(')');
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit * 3);
        break;
      case ':':
        Serial.print(':');
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      case ';':
        Serial.print(';');
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit);
        dash();
        delay(timeUnit);
        dot();
        delay(timeUnit * 3);
        break;
      default:
        Serial.print(textInput[i]);
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
