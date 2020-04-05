// пины подключения x,y,z

const int pinX = A1;


// переменные для хранения значений

unsigned int x;


void setup() {

  // запуск последовательного порта

  Serial.begin(9600);

}



void loop() {

  // получение данных

  x = analogRead(pinX);


  // вывод в последовательный порт

  Serial.println(x);


  // пауза

  delay(3000);

}
