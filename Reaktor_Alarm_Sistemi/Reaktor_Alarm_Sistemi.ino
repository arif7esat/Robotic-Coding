const int led1 = 3;
const int led2 = 4;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {

  // Yavaş
  for(int i = 0; i < 5; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(500);

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    delay(500);
  }

  // Orta hız
  for(int i = 0; i < 10; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(200);

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    delay(200);
  }

  // Kritik alarm
  for(int i = 0; i < 30; i++) {

    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    delay(50);

    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(50);
  }
}