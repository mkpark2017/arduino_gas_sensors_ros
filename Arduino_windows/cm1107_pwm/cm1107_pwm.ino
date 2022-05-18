byte PWM_PIN = 3;
int pwm_value;

void setup() {
  pinMode(PWM_PIN, INPUT);
  Serial.begin(115200);
}

void loop() {
  unsigned long highTime = pulseIn(PWM_PIN, HIGH);
  unsigned long lowTime = pulseIn(PWM_PIN, LOW);
  unsigned long cycleTime = highTime + lowTime;
  float dutyCycle = (float)highTime / float(cycleTime);
  Serial.print("High Time : ");
  Serial.print(highTime);
  Serial.print("    ");
  Serial.print("Low Time : ");
  Serial.print(lowTime);
  Serial.print("    ");
  Serial.print("Cycle Time : ");
  Serial.println(cycleTime);

  
}
