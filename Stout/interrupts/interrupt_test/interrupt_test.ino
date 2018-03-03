#define INTRPT1 A0
#define INTRPT2 A1

void setup() {
  pinMode(INTRPT1, INPUT);
  pinMode(INTRPT2, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  digitalWrite(INTRPT2, HIGH);
  Serial.println("High");
  Serial.println(digitalRead(INTRPT1));

  delay(1000);

  digitalWrite(INTRPT2, LOW);
  Serial.println("Low");
  Serial.println(digitalRead(INTRPT1));

  delay(1000);
}
