#define out_sig 3
void setup() {
  // put your setup code here, to run once:
  pinMode(out_sig, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(out_sig, HIGH);
  delay(1000);
  digitalWrite(out_sig, LOW);
  delay(1000);
}
