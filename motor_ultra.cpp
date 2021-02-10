//for motor
#define ENA 10
#define ENB 5
#define EN1 9
#define EN2 8
#define EN3 7
#define EN4 6
//for ultra
#define trig 3    // 트리거 핀 선언
#define echo 4    // 에코 핀 선언

int Motor_speed = 100; // 모터 속도 PWM 100으로 설정 0~255
void front(int Motor_speed);
void back(int Motor_speed);
int ultra();

void setup()
{
  Serial.begin(9600);      // 통신속도 9600bps로 시리얼 통신 시작
  Serial.println("초음파 센서 시작");
  pinMode(trig, OUTPUT);    // 트리거 핀 출력으로 선언
  pinMode(echo, INPUT);     // 에코 핀 입력으로 선언

  // PWM 제어핀 출력 설정
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  // 방향 제어핀 출력 설정
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);
}
void loop()
{
  int dis;
  dis = ultra();
  void ultra();
  // 모터 A,B 정방향
  if (155 > dis) // for obstacle avoid(장애물 피하기)
    {
      front(Motor_speed);
    }
  //delay(3000);          // 3초동안 정방향 회전
  // 모터A,B 역방향
  else
    {
      back(Motor_speed);
    }
  delay(3000);       // 3초동안 역방향 회전
}

void front(int Motor_speed)
{
  digitalWrite(EN1, HIGH);   // 모터A 설정
  digitalWrite(EN2, LOW);
  analogWrite(ENA, Motor_speed);

  digitalWrite(EN4, HIGH);  // 모터B설정
  digitalWrite(EN3, LOW);
  analogWrite(ENB, Motor_speed);
}

void back(int Motor_speed)
{
  digitalWrite(EN1, LOW);  // 모터A설정
  digitalWrite(EN2, HIGH);
  analogWrite(ENA, Motor_speed);

  digitalWrite(EN4, LOW); // 모터B설정
  digitalWrite(EN3, HIGH);
  analogWrite(ENB, Motor_speed);
}

int ultra()
{
  long duration, distance;    // 거리 측정을 위한 변수 선언
  // 트리거 핀으로 10us 동안 펄스 출력
  digitalWrite(trig, LOW);        // Trig 핀 Low
  delayMicroseconds(2);            // 2us 딜레이
  digitalWrite(trig, HIGH);    // Trig 핀 High
  delayMicroseconds(10);            // 초음파를 쏘기 위한 10us 딜레이
  digitalWrite(trig, LOW);        // Trig 핀 Low
  /*
      에코핀에서 받은 펄스 값을 pulseIn함수를 호출하여
      펄스가 입력될 때까지의 시간을 us단위로 duration에 저장
      pulseln() 함수는 핀에서 펄스(HIGH or LOW)를 읽어서 마이크로초 단위로 반환
  */
  duration = pulseIn(echo, HIGH); // 특정시간을 측정하기 위해 사용하는 함수
  /*
       음파의 속도는 초당 340m, 왕복하였으니 나누기 2를하면 170m이고,
       mm단위로 바꾸면 170,000mm.
       duration에 저장된 값은 us단위이므로 1,000,000으로 나누어 주고,
       정리해서 distance에 저장
  */
  distance = duration * 170 / 1000;
  Serial.print("거리: ");
  Serial.print(distance); // 거리를 시리얼 모니터에 출력
  Serial.println("mm");
  delay(100);

  return distance;
}

