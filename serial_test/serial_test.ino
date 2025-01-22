const int buttonPin = 2;
const int ledPin = 13;

int buttonState = 0;
int ledState = LOW;
int lastButtonState = LOW;
bool pressed = false;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

char rx_byte;

void setup() {
  Serial.begin(19200);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        if (pressed == false){
          Serial.println("on");
          pressed = true;
        }
        ledState = HIGH;
      } else {
        if (pressed == true){
          Serial.println("off");
          pressed = false;
          ledState = LOW;
        }
      }
    }
  }

  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}
