int enA = 11 ;

int in1 = 9;

int in2 = 8;

// второй двигатель

int enB = 5;

int in3 = 7;

int in4 = 6;

void setup()

{

Serial.begin(9600);
pinMode(enA, OUTPUT);

pinMode(enB, OUTPUT);

pinMode(in1, OUTPUT);

pinMode(in2, OUTPUT);

pinMode(in3, OUTPUT);

pinMode(in4, OUTPUT);

}


void loop()

{ 
  
    bool nak = digitalRead(A1);
    if(nak == 1){
    analogWrite(enA, 250);
    analogWrite(enB, 250);
    }
    else{
    analogWrite(enA, 120);
    analogWrite(enB, 120);
    }
    Serial.println(nak);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

}
