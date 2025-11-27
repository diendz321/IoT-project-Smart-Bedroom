

#define TRIG_PIN 5   // D1
#define ECHO_PIN 4   // D2

int distance = 0;
int threshold = 150; // <150 cm => co nguoi

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("Bat dau do sonar...");
}

// Ham do khoang cach
int getDistance() {
  long duration;
  int d;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 25000); // timeout 25ms

  d = duration * 0.034 / 2; // doi ra cm

  if (d <= 0 || d > 400) d = 400; // gioi han

  return d;
}

void loop() {
  distance = getDistance();

  Serial.print("Khoang cach: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < threshold) {
    Serial.println(" ==> CO NGUOI TRONG PHONG");
  } else {
    Serial.println(" ==> KHONG CO AI");
  }

  delay(500);
}
