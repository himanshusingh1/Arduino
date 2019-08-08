
#define T_C 262
#define T_D 294
#define T_E 330
#define T_F 349
#define T_G 392
#define T_A 440
#define T_B 493

const int Buzz = 11;

void setup()
{
  pinMode(A0,INPUT);
    Serial.begin(9600);

}
int last = 0;
void loop()
{
  Serial.println(analogRead(A0));
  double input = analogRead(A0);
  if (input > 0 && input < 20){
    if (last == 0){
      last++;
        tone(Buzz,T_D);
    }else if (last == 1){
            last++;
      tone(Buzz,T_C);
      }
      else{
        tone(Buzz,T_E);
       last = 0 ;
        }
       
   }else if (input >= 20){
     if (last == 0){
      last++;
        tone(Buzz,T_A);
    }else if (last == 1){
            last++;
      tone(Buzz,T_B);
      }
      else{
        tone(Buzz,T_G);
       last = 0 ;
        }
    }else{
          noTone(Buzz);
    }
    delay(500);
}
