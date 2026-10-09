#define STUDENT_ID  402107271

#define POT_PIN     A0
#define BUTTON_S2   3
#define BUZZER_PIN  8
#define LED_PIN     9

int threshold = 0;
const int MAX_POT = 1023;

void setup() {
  pinMode(BUTTON_S2, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  long lastTwoDigits = STUDENT_ID % 100; 

  threshold = (lastTwoDigits * MAX_POT) / 100; 
  
  digitalWrite(LED_PIN, LOW);
  noTone(BUZZER_PIN);
}

void loop() {
  int potValue = analogRead(POT_PIN);
  bool buttonPressed = (digitalRead(BUTTON_S2) == LOW);

  if (buttonPressed) {
    int frequency = map(potValue, 0, MAX_POT, 200, 2000);

    if (potValue > threshold) {
      digitalWrite(LED_PIN, HIGH);
      tone(BUZZER_PIN, frequency + 500);
      delay(100);
      noTone(BUZZER_PIN);
      delay(50);
    } 
    else {
      digitalWrite(LED_PIN, LOW);
      tone(BUZZER_PIN, frequency);
    }
  } 
  else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  delay(10);
}
