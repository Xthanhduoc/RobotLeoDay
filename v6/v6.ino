#include <EEPROM.h>

#define encoderPinA 2
#define encoderPinB 3
#define NutStartLayMau 4
#define NutStopLayMau 5

#define NutChuaChay 6
#define DC1EnableA 11 //Động cơ nam châm
#define DC1EnableB 10
#define DC2EnableA 12 //Động cơ leo dây
#define DC2EnableB 13
#define NamCham 7
#define NutStart 8
//#define NutStop 13

//int ViTriGapVat;
int ViTriThaVat;
////////
int thutu1;
int thutu2;
int thutu3;
int thutu4;
int thutu5;

int tam;
int tam1;
int tam2;
int tam3;
/////////


void setup()
{
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(NutStartLayMau, INPUT_PULLUP);
  pinMode(NutStopLayMau,INPUT_PULLUP);
  pinMode(NutChuaChay, INPUT_PULLUP);
  pinMode(NutStart, INPUT_PULLUP);
  pinMode(DC1EnableA,OUTPUT);
  pinMode(DC1EnableB, OUTPUT);
  pinMode(DC2EnableA, OUTPUT);
  pinMode(DC2EnableB,OUTPUT);
  pinMode(NamCham, OUTPUT);

//  pinMode(NutStop, OUTPUT);

 
  //Gán biến vị trí gắp vật bằng giá trị được lưu trong bộ nhớ không mất nội dung
  //ViTriGapVat = EEPROM.read(1);
//  ViTriThaVat = EEPROM.read(2);
  thutu1 = EEPROM.read(1);
  thutu2 = EEPROM.read(2);
  thutu3 = EEPROM.read(3);
  thutu4 = EEPROM.read(4);
  thutu5 = EEPROM.read(5);
  ViTriThaVat = (thutu1*10000) + (thutu2*1000) + (thutu3*100) + (thutu4*10) + thutu5;
  
  attachInterrupt(digitalPinToInterrupt(encoderPinA), isrA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), isrB, CHANGE);


    digitalWrite(DC1EnableA,HIGH);
    digitalWrite(DC1EnableB,HIGH);
    digitalWrite(NamCham,LOW);//nam cham roi nen kich muc cao, nen trang thai ban dau la low
  Serial.begin(9600);

  interrupts();
}

int count = 0;
//int SoLanAnNutStop = 0;
void loop()
{

  Serial.println(count);
  Serial.println(ViTriThaVat);
  delay(500);

  //Hàm cho xe học lên lấy mẫu thả vật;
   if(digitalRead(NutStartLayMau)== 0)
  {
    delay(50); //Chống dội công tắc
    XeChayToi(); //Cho xe chạy tới

    //Đợi xe chạm nút chữa cháy
    while (digitalRead(NutChuaChay)== 1)
        ;
    XeStop();
    delay(5000);

    count = 0;
    interrupts();
    XeChayLui(); //Cho xe chạy lùi
    
    //Đợi Nhấn nút StopLayMau
   while ((digitalRead(NutStopLayMau)== 1)) 
        ;

    XeStop();//Dừng xe
   // EEPROM.write(2, count);//EEPROM.write(addr, val)//Lưu trử vị trí thả vật bằng với giá trị biến count vô bộ nhớ không mất nội dung
    thutu1 = count/10000;
    tam = count % 10000;
    thutu2 = tam / 1000;
    tam1 = tam % 1000;
    thutu3 = tam1 / 100;
    tam2 = tam1% 100;
    thutu4 = tam2 % 10;
    thutu5 = tam2 % 10;
    EEPROM.write( 1 ,thutu1);
    EEPROM.write( 2 ,thutu2);
    EEPROM.write( 3 ,thutu3);
    EEPROM.write( 4 ,thutu4);
    EEPROM.write( 5 ,thutu5);

    //noInterrupts();
    ViTriThaVat = count;
    delay(3000); //Cho xe dừng 10 giây
    XeChayLui();//Tiếp tục cho xe chạy lùi 
    delay(4000);/////////////////////////////////////////
    XeStop();
  }


   if(digitalRead(NutStart)== 0){
    delay(50);
    //Cho xe chạy tới
    XeChayToi();
   
    //Đợi xe chạm nút chữa cháy
    while ((digitalRead(NutChuaChay)== 1))
        ;
    delay(50);
    XeStop();
    delay(1000);
    //Thả dây
    DongCoTha();
    delay(3000);

    //Bật nam châm
    //digitalWrite(NamCham, HIGH);
    //delay(1000);
    //Thu 
    DongCoThu();
    delay(3000);
    DongCoNgung();
    //delay
    delay(1000);
    //Gán giá trị count = 0
    count = 0;
  
    //Cho phép interrupt để xe bắt đầu đo khoảng cách
    interrupts();
    
    //Cho xe chạy lùi

    XeChayLui();
    //delay(10000);
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// delay(10000);    
    //Đợi biến count = vị trí thả vật 
    while (count <= ViTriThaVat){
      delay(10);
      Serial.println(count);

    }
      
    //noInterrupts();
    //Cho xe dùng
    XeStop();
    delay(1000);
    //Chạy động động cơ thả
      DongCoTha();
      delay(3000);
    //Tắt nam châm hút vật
    //digitalWrite(NamCham, LOW);

    
    //Thu dây lên nếu cần
    DongCoThu();
    delay(3000); 
    DongCoNgung();
    //Cho xe chạy lùi tới vị trí xuất phát ban đầu
    
    //Cho xe chạy lùi
    XeChayLui();
    
    //Kết thúc
    delay(4000);
    XeStop();
    
  }
   else
  {
     XeStop();
  }
}

void XeChayToi()
{
  digitalWrite(DC2EnableA, HIGH);
  digitalWrite(DC2EnableB, LOW);
}

void XeChayLui()
{
  digitalWrite(DC2EnableA, LOW);
  digitalWrite(DC2EnableB, HIGH);
  
}

void XeStop()
{
  digitalWrite(12, 1);
  digitalWrite(13, 1);
}

void DongCoTha()
{
    digitalWrite(DC1EnableA,HIGH);
    digitalWrite(DC1EnableB,LOW);
}

void DongCoThu()
{
    digitalWrite(DC1EnableA,LOW);
    digitalWrite(DC1EnableB,HIGH);
  
}
void DongCoNgung(){
    digitalWrite(DC1EnableA,HIGH);
    digitalWrite(DC1EnableB,HIGH);
}



void isrA()
{
  if(digitalRead(encoderPinB) != digitalRead(encoderPinA)) {
    count ++;
  } else {
    count --;
  }
}
void isrB()
{
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    count ++;
  } else {
    count --;
  }
}
