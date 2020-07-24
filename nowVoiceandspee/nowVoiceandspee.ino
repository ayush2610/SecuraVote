#include <Keypad.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#define ENTERADHAAR 1
#define SCANFINGER 2
#define ENTERVOTE 3
#define BEGINPRINT 0
#define ENDPRINT 1
#define ENDVOTING 4
#define STOP 0

SoftwareSerial mySerial(9, 10);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 8, A0, A1};
byte colPins[COLS] = {A2, A3, A4, A5}; 

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
char  aadharList[5][13] = {"751845414176","263488843244","458557003847","002456909878","910876543231"};
char usedAadharList[5][13];
char eligaadharList[5][13]={"751845414176","263488843244","","002456909878","910876543231"};
int totalID = 4;
int i = 0;
char adhID[13];
char customKey ;
int count[8] = {0,0,0,0,0,0,0,0} ;
int countsize = 8;
char partyName[11][11]  ={"CONGRESS","AAP", "BJP", "SP", "NCP", "CPI", "BSP", "NO PARTY"};

char password[] = "123678";
int z = BEGINPRINT;
int l=0;
char userent[7];
long totaltime = 0;
int usedID[100];
int idn=0;
int retries = 0;
int voted=0;
int ID;

void setup(){
  Serial.begin(9600);
  delay(100);
  finger.begin(57600);
  lcd.begin(16, 2);
  
  
 
  
}

int j =1;
void loop(){
   
//    retAdh();
    scanfinger();
    delay(50);
    entervote();
    endvoting();
}  
 


int p=SCANFINGER;
 void scanfinger(){
  voted=0;
  if(i==0){
        lcd.setCursor(3,0);
        lcd.print("WELCOME TO");
        lcd.setCursor(2,1);
        lcd.print("VOTING SYSTEM");
        delay(500);
        for(int pl =0; pl<1000; pl++)
        Serial.println('a');
        delay(2000);
        lcd.clear();
        i++;
        
  } 
  long t1 = millis()/1000;
  if(p==SCANFINGER){
    if(z==BEGINPRINT)
    {
     lcd.print("Place Finger");
     lcd.setCursor(0,1);
     lcd.print("on Sensor");
     for(int pl =0; pl<100; pl++)
     Serial.println('b');
     z=ENDPRINT;
    } 
 
 uint8_t k = finger.getImage();
 if (k != FINGERPRINT_OK)   {p=SCANFINGER;  return 0;}
  
 k = finger.image2Tz();
   if (k != FINGERPRINT_OK)   {p=SCANFINGER;  return 0;} 

  k = finger.fingerFastSearch();

  if (k != FINGERPRINT_OK)   {
    p=SCANFINGER;
      long t2 = millis()/1000;
      long tim = t2-t1;
      totaltime+=tim; 
      if(totaltime>10){
        lcd.clear();
        lcd.print("Finger Print Not ");
        lcd.setCursor(0,1);
        lcd.print("Matched");
        for(int pl =0; pl<100; pl++)
        Serial.println('c');
        totaltime=0;
        z =BEGINPRINT;
        delay(2000);
        lcd.clear();
         if(retries<3){
          lcd.print("Please try");
          lcd.setCursor(0,1);
          lcd.print("again");
          for(int pl =0; pl<100; pl++)
          Serial.println('d');
          delay(3000);
          lcd.clear();
          
          retries++;
          p = SCANFINGER;
          return;
        }
        else{
          lcd.print("Retries Exceded");
          for(int pl =0; pl<1000; pl++)
          Serial.println('e');
          delay(3000);
          lcd.clear();
          
          p = SCANFINGER;;
          i=0;
          retries = 0;
          return;
        }
        
      
      }
      return 0;}

     ID = finger.fingerID;

      if(k==FINGERPRINT_OK)
        lcd.clear();
      if(ID){  
      lcd.print("Your Adhaar no:");
      lcd.setCursor(0,1);
      lcd.print(aadharList[(ID-1)/2]);
      delay(2000);
      lcd.clear();
      if(strcmp(aadharList[(ID-1)/2],eligaadharList[(ID-1)/2])==0){
       strcpy(usedAadharList[idn], aadharList[(ID-1)/2]);
        for(int q=0; q<idn; q++){
          if(strcmp(usedAadharList[q],aadharList[(ID-1)/2])==0){
            lcd.print("User vote  ");
            lcd.setCursor(0,1);
            lcd.print("already registered");
            for(int pl =0; pl<100; pl++)
            Serial.println('f');
            delay(3000);
            lcd.clear();
            
            p = SCANFINGER;
            i=0;
            z = BEGINPRINT;
            voted=1;
            return ; 
           }
          }
        } 
       else{
        lcd.clear();
        lcd.print("you are not");
        lcd.setCursor(0,1);
        lcd.print("eligible to vote");
        delay(3000);
        lcd.clear();
        for(int pl =0; pl<100; pl++)
        Serial.println('g');
        p=SCANFINGER;
        z=BEGINPRINT;
        voted = 1;
        i=0;
        return;
       }
      if(voted==0){ 
      lcd.print("you can now vote");
      for(int pl =0; pl<100; pl++)
      Serial.println('h');
      delay(3000);
      lcd.clear();
      p = ENTERVOTE; 
      z = BEGINPRINT;
       return ;
      } 
     }
    
    else{
      lcd.clear();
      lcd.print("Finger Print Not ");
      lcd.setCursor(0,1);
      lcd.print("Matched");
      for(int pl =0; pl<100; pl++)
      Serial.println('c');
      delay(3000);
      lcd.clear();
      
      p = SCANFINGER;
      z = BEGINPRINT;
      i=0;
      return ;
      
    }
    
  }
 }

void entervote()
{
  if(p==ENTERVOTE)
  {
    if(z==BEGINPRINT)
    {
      lcd.print("enter choice");
//      lcd.setCursor(0,1);
//      lcd.print("1.A 2.B 3.C 4.D");
      z=ENDPRINT; 
      for(int pl =0; pl<100; pl++)
      Serial.println('j');
    }
      input:
      char vote = Serial.read();
      if(vote!='0'){
//             if(vote =='0')
//              count[0]++; 
              if(vote =='1')
              count[1]++; 
             else if(vote == '2')
              count[2]++;
             else if(vote == '3')
              count[3]++;
             else if(vote == '4')
              count[4]++;
             else if(vote == '5')
              count[5]++; 
             else if(vote == '6')
              count[6]++;
             else if(vote == '7')
              count[7]++;     
              else{
               
                goto input;         
              }
      }  
             else{
              Serial.print('j');
              goto input;
             }
              p = SCANFINGER;;
              z = BEGINPRINT;
              idn++;
              
              lcd.clear();
              lcd.print("Vote Succesful");
              for(int pl =0; pl<100; pl++)
              Serial.println('l');
              delay(3000);
              i=0;
              lcd.clear();
              return;
           }
  }
         
    
  
 



void endvoting()
{

  if(p==ENDVOTING)
  {
    if(z == BEGINPRINT){
      lcd.clear();
      lcd.print("Enter Admin Password");
      lcd.setCursor(0,1);
      lcd.print("(6 digit) to end voting");
      delay(3000);
      lcd.clear(); 
      z = ENDPRINT;
      }
    customKey = customKeypad.getKey();
    if(customKey)
    {
      if(isDigit(customKey))
          {
            
             userent[l] = customKey;
             lcd.print('*');
              l++;
           }
           else if(customKey=='*')
           {
              l--;
              lcd.clear();
              for( int j=0;j<l;j++)
              lcd.print(userent[l]);
           }
           else
           {
            lcd.clear();
            lcd.print("Invalid Key");
            lcd.setCursor(0,1);
            lcd.print("Entered");
            delay(2000);
             for( int j=0;j<=l;j++)
             lcd.print(userent[l]);
           }
    }
    if(strcmp(password,userent)==0){
        p = STOP;
        z = BEGINPRINT;
        l = 0;
        lcd.clear();
        lcd.print("Voting Ended");
        delay(2000);
        lcd.clear();
        lcd.print("Votes to each");
        lcd.setCursor(0,1);
        lcd.print("are as");
        delay(2000);
        lcd.clear();
        lcd.print("1:");
        lcd.setCursor(2,0);
        lcd.print(count[0]);
        lcd.setCursor(3,0);
        lcd.print(" ");
        lcd.setCursor(4,0);
        lcd.print("2:");
        lcd.setCursor(5,0);
        lcd.print(" ");
        lcd.setCursor(6,0);
        lcd.print(count[1]);
        lcd.setCursor(7,0);
        lcd.print(" ");
        lcd.setCursor(8,0);
        lcd.print("3:");
        lcd.setCursor(10,0);
        lcd.print(count[2]);
        lcd.setCursor(11,0);
        lcd.print(" ");
        lcd.setCursor(12,0);
        lcd.print("4:");
        lcd.setCursor(14,0);
        lcd.print(count[3]);
        lcd.setCursor(15,0);
        lcd.print(" ");    
        lcd.setCursor(0,1);
        lcd.print("5:");
        lcd.setCursor(2,1);
        lcd.print(count[4]);
        lcd.setCursor(3,1);
        lcd.print(" ");  
        lcd.setCursor(4,1);
        lcd.print("6:");
        lcd.setCursor(6,1);
        lcd.print(count[5]);
        lcd.setCursor(7,1);
        lcd.print(" ");
        lcd.setCursor(8,1);
        lcd.print("7:");
        lcd.setCursor(10,1);
        lcd.print(count[6]);
        lcd.setCursor(11,1);
        lcd.print(" ");  
        lcd.setCursor(12,1);
        lcd.print("8:");
        lcd.setCursor(14,1);
        lcd.print(count[7]);
        lcd.setCursor(15,1);
        lcd.print(" ");  
        delay(3000);   
        lcd.clear();
        maximum();
      }

      else{
        lcd.clear();
        lcd.print("Invalid password ");
        lcd.setCursor(0,1);
        lcd.print("Redirecting...");
        delay(2000);
        lcd.clear();
        p = ENTERADHAAR;
        z = BEGINPRINT;
        l = 0;
        i = 0;
        return;
      }
    }
  }
}

void maximum()
{
  
  lcd.setCursor(0,1);
  int  maximu = count[0];
  int maxindex = 0;
  int draw = 0;
  for(int nu=0; nu<countsize; nu++){
    if(maximu<count[nu]){
        maximu = count[nu];
        maxindex = nu;
        draw=0;
    }
    else if(maximu == count[nu]){
      draw =1;
    }
  }
  Serial.println();
  if(maximu){
    if(draw==0){
  Serial.print(partyName[maxindex]);
  Serial.println(" wins");
    }
    else{
      Serial.println("no clear majority");
    }
  }
  else{
    Serial.print("no votes entered");
  }
 
  
//  else
//    lcd.print("no clear win");  
//  delay(2000);
//  lcd.clear();
  
}

