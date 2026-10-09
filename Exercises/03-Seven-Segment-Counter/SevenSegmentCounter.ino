#pragma GCC push_options
#pragma GCC optimize ("O1")
#define STUDENT_ID 402107271
#define SEG_A 4
#define SEG_B 5
#define SEG_C 6
#define SEG_D 7
#define SEG_E 8
#define SEG_F 9
#define SEG_G 10
#define DIGIT1 11
#define DIGIT2 12
#define BUTTON_S3 3

int initialValue;
int currentValue;
bool lastReading = HIGH;
bool lastStableState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

byte digitPatterns[10] = {
  0b00111111,
  0b00000110,
  0b01011011,
  0b01001111,
  0b01100110,
  0b01101101,
  0b01111101,
  0b00000111,
  0b01111111,
  0b01101111
};

void setup() {
  pinMode(SEG_A, OUTPUT); pinMode(SEG_B, OUTPUT); pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT); pinMode(SEG_E, OUTPUT); pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(DIGIT1, OUTPUT);
  pinMode(DIGIT2, OUTPUT);
  pinMode(BUTTON_S3, INPUT_PULLUP);
  initialValue = STUDENT_ID % 100;
  currentValue = initialValue;
  lastReading = digitalRead(BUTTON_S3); 
  lastStableState = digitalRead(BUTTON_S3);
}

void loop() {
  displayNumber(currentValue);

  bool reading = digitalRead(BUTTON_S3);

  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != lastStableState) {
      lastStableState = reading;
      if (lastStableState == LOW) {
        currentValue++;
        if (currentValue > 99) {
          currentValue = initialValue - 1;
        }
      }
    }
  }

  lastReading = reading;
}

void displayNumber(int num) {
  int tens = num / 10;
  int units = num % 10;

  digitalWrite(DIGIT2, HIGH);
  digitalWrite(DIGIT1, LOW);
  setSegments(tens);
  delay(2);

  digitalWrite(DIGIT1, HIGH);
  digitalWrite(DIGIT2, LOW);
  setSegments(units);
  delay(2);
}

void setSegments(int digit) {
  digitalWrite(SEG_A, bitRead(digitPatterns[digit], 0));
  digitalWrite(SEG_B, bitRead(digitPatterns[digit], 1));
  digitalWrite(SEG_C, bitRead(digitPatterns[digit], 2));
  digitalWrite(SEG_D, bitRead(digitPatterns[digit], 3));
  digitalWrite(SEG_E, bitRead(digitPatterns[digit], 4));
  digitalWrite(SEG_F, bitRead(digitPatterns[digit], 5));
  digitalWrite(SEG_G, bitRead(digitPatterns[digit], 6));
}

#pragma GCC pop_options
