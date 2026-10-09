#define BUTTON_PIN  2    

#define LED4_PIN    7
#define LED3_PIN    6
#define LED2_PIN    5
#define LED1_PIN    4

int currentState = 0;       
bool lastButtonState = HIGH;
bool buttonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 2;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(LED4_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);

  allLEDsOff();      
}

void loop() {
  bool reading = digitalRead(BUTTON_PIN);


  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
      if (buttonState == LOW) {           
        currentState++;           
        
        if (currentState > 4) {
          currentState = 0;          
        }
        
        updateLEDs();
      }
    }
  }

  lastButtonState = reading;
}

void updateLEDs() {
  allLEDsOff();
  

  switch (currentState) {
    case 1:
      digitalWrite(LED4_PIN, HIGH);
      break;
    case 2:
      digitalWrite(LED3_PIN, HIGH);
      break;
    case 3:
      digitalWrite(LED2_PIN, HIGH);
      break;
    case 4:
      digitalWrite(LED1_PIN, HIGH);
      break;
    case 0:

      break;
  }
}

void allLEDsOff() {
  digitalWrite(LED4_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED1_PIN, LOW);
}
