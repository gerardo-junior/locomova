//arduino UNO
//Motores
const int ENA=13;
const int IN1=12;
const int IN2=11;
const int IN3=10;
const int IN4=9;
const int ENB=8;
//saidas e entradas
const int ledERRO=7;
const int ledLDB=6;
const int botao=5;
const int potenciometro = A1;
//comunicação entre os arduinos
const int d4=4;
const int d3=3;
const int d2=2;
//var's de controle
float dis;
int disE;
int disD;
int velo;

void setup(){
  //inciar comunicação serial pelo bluetooth
  Serial.begin(9600);
  //pinos de saidas para motores
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB,OUTPUT);
  // S/E
  pinMode(ledERRO,OUTPUT);
  pinMode(ledLDB,OUTPUT);
  pinMode(botao,INPUT);
  //ARDUINO
  pinMode(d4,INPUT);
  pinMode(d3,INPUT);
  pinMode(d2,INPUT);
}
void passo(){
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENA,velo);
  analogWrite(ENB,velo);
  delay(1000);
}

void desviar(){
  if((digitalRead(d3) == HIGH) && (digitalRead(d2) == LOW)){
    giroD();
    frente();
    giroE();
    frente();
  }
  else{
    if((digitalRead(d3) == LOW) && (digitalRead(d2) == HIGH)){
      giroE();
      frente();
      giroD();
      frente();  
    }
    else{
      if((digitalRead(d3) == HIGH) && (digitalRead(d2) == HIGH)){
        Serial.println("trais");
        trais();
      }
      else
      {
        if((digitalRead(d3) == LOW) && (digitalRead(d2) == LOW)){
          digitalWrite(ledLDB,LOW);
          digitalWrite(ledERRO,HIGH);
          delay(2000);
          digitalWrite(ledERRO,LOW);
        }
      }
    }
  }
}


void frente(){
  if(digitalRead(d4)== LOW){
    passo();
  }
  else{
    if(digitalRead(d4)== HIGH){
      delay(5000);
      desviar();
    }
  }
}

void trais(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,HIGH); 
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENA,velo);
  analogWrite(ENB,velo);
  delay(100);
}
void giroE(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,LOW);
  digitalWrite(IN1,HIGH); 
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENA,velo);
  analogWrite(ENB,velo);
  delay(100);
}
void giroD(){
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENA,velo);
  analogWrite(ENB,velo);
  delay(100);
}
void parar(){
  analogWrite(ENA,0);
  analogWrite(ENB,0);

}
void S(){
  digitalWrite(ledLDB,HIGH);
}
void loop(){
  char ctrl = Serial.read();
  int pot=analogRead(potenciometro);
  velo=map(pot, 0, 1023, 0, 255);
  //Serial.println(velo);

  switch (ctrl){ 
  case 'e':
    frente();
    S(); 
    break;
  case 'f':
    giroE();
    S();
    break;
  case 't':
    giroD();
    S();
    break; 
  case 'd':
    trais();
    S();
    break;
  case 'p':
    parar();
    S();
    break;
  default:
    digitalWrite(ledLDB,LOW);
    digitalWrite(ledERRO,HIGH);
    delay(20);
    digitalWrite(ledERRO,LOW);
    break;
  }

}












