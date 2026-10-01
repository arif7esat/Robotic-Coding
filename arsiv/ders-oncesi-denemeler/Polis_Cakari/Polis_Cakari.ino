const int led1 = 3;
const int led2 = 4;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {

  // Sol hızlı çakar
  for(int i = 0; i < 3; i++) {
    digitalWrite(led1, HIGH);
    delay(80);
    digitalWrite(led1, LOW);
    delay(80);
  }

  delay(150);

  // Sağ hızlı çakar
  for(int i = 0; i < 3; i++) {
    digitalWrite(led2, HIGH);
    delay(80);
    digitalWrite(led2, LOW);
    delay(80);
  }

  delay(150);
}