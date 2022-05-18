const int analogPin = A0;
int value;
/* sensor 값을 저장할 변수를 선언
    5V : 1023
    0V : 0     */
 
void setup(){
    // buadrate 9600 으로 시리얼 포트를 초기화하고
    // 시리얼 포트가 연결 될 때 까지 기다립니다.
    Serial.begin(9600);
    //while(!Serial){
    //    ;
    //}
    delay(1000);
    Serial.println("Initialize Finished...");
    delay(1000);
}
 
void loop(){
    // analogPin 의 값을 value 에 저장 후 시리얼포트로 출력합니다.
    value = analogRead(analogPin);
    Serial.println(value);
    delay(100);
}
