#define led1 2
#define led2 3
#define led3 4
#define sensor 8

byte alkis =0;
byte sayac = 0;

long ilk_Ses=0;
long son_ses=0;

void setup(){
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(sensor,INPUT);
}

void loop(){
  int sensor_deger=digitalRead(sensor);

  if(sensor_deger==1){

    if(alkis==0){
      ilk_Ses=son_ses=millis();
      alkis++;
    }
    else if(alkis>0 && millis()-son_ses>=50){
      son_ses=millis();
      alkis++;
    }
  }
  if(millis()-ilk_Ses>=400){
    if(alkis==2){
      sayac++;
    }
    alkis=0;
    if(sayac>=4){
      sayac=0;
    }
  }

  switch(sayac){
    case 1:
    digitalWrite(led1,1);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    break;

    case 2:
    digitalWrite(led1,1);
    digitalWrite(led2,1);
    digitalWrite(led3,0);
    break;
    
    case 3:
    digitalWrite(led1,1);
    digitalWrite(led2,1);
    digitalWrite(led3,1);
    break;

    default:
    digitalWrite(led1,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
  }
}














