int a_role = 16;
int b_role = 4;
int c_role = 15;
int d_role = 2;

int a;
int b;
int c;
int d;

bool bir=false;
bool iki=false;
bool uc=false;
bool dort=false;

void setup(){
  pinMode(a_role, OUTPUT);
  pinMode(b_role, OUTPUT);
  pinMode(c_role, OUTPUT;
  pinMode(d_role, OUTPUT);

}

void loop(){
  a=digitalRead(a_role);
  b=digitalRead(b_role);
  c=digitalRead(c_role);
  d=digitalRead(d_role);

  if(a==1 && b==0 && c==0 && d==0 && bir==false){
    bir=true;
    digitalWrite(a_role, 1);
    delay(1000);
  }
  else if (a==1 && b==0 && c==0 && d==0 && bir=true) {
    bir=false;
    digitalWrite(a_role, 0);
    delay(1000);
  }
  if(a==0 && b==1 && c==0 && d==0 && iki==false){
    iki=true;
    digitalWrite(b_role, 1);
    delay(1000);
  }
  else if (a==0 && b==1 && c==0 && d==0 && iki=true) {
    iki=false;
    digitalWrite(b_role, 0);
    delay(1000);
  }
  if(a==0 && b==0 && c==1 && d==0 && uc=false){
    uc=true;
    digitalWrite(c_role, 1);
    delay(1000);
  }
  else if(a==0 && b==0 && c==1 && d==0 && uc=true){
    uc=false;
    digitalWrite(c_role, 0)
    delay(1000);
  }
  if(a==0 && b==0 && c==0 && d==1 && dort=false){
    dort=true;
    digitalWrite(d_role,1);
    delay(1000);
  }
  else if(a==0 && b==0 && c==0 && d==1 && dort=true){
    dort=false;
    digitalWrite(d_role,0);
    delay(1000);
  }








}