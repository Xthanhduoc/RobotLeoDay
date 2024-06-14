#include <EEPROM.h>

#define encoderPinA 2
#define encoderPinB 3
#define NutStartLayMau 4
#define NutStopLayMau 5

#define NutChuaChay 6
#define DC1EnableA 7 //Động cơ nam châm
#define DC1EnableB 8
#define DC2EnableA 9 //Động cơ leo dây
#define DC2EnableB 10
#define NamCham 11
#define NutStart 12
#define NutStop 13

int ViTriGapVat;
int ViTriThaVat;
void setup()
{
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(NutStartLayMau, INPUT_PULLUP);
  pinMode(NutStopLayMau,INPUT_PULLUP);
  pinMode(NutChuaChay, INPUT_PULLUP);
  pinMode(DC1EnableA,OUTPUT);
  pinMode(DC1EnableB, OUTPUT);
  pinMode(DC2EnableA, OUTPUT);
  pinMode(DC2EnableB,OUTPUT);
  pinMode(NamCham, OUTPUT);
  pinMode(NutStart, OUTPUT);
  pinMode(NutStop, OUTPUT);

 
  //Gán biến vị trí gắp vật bằng giá trị được lưu trong bộ nhớ không mất nội dung
  ViTriGapVat = EEPROM.read(1);
  ViTriThaVat = EEPROM.read(2);
  
  attachInterrupt(digitalPinToInterrupt(encoderPinA), isrA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), isrB, CHANGE);
}

int count = 0;
int SoLanAnNutStop = 0;
void loop()
{
  if(digitalRead(NutStartLayMau)== 0)
  {
    delay(500); //Chống dội công tắc
    XeChayToi(); //Cho xe chạy tới

    //Đợi xe chạm nút chữa cháy
    while ((digitalRead(NutChuaChay)== 0))
        ;
    delay(2000);

    count = 0;
    interrupts();
    XeChayLui(); //Cho xe chạy lùi
    
    //Đợi Nhấn nút StopLayMau
   while ((digitalRead(NutStopLayMau)!= 0))
        ;

    XeStop();//Dừng xe
    EEPROM.write(1, count);//EEPROM.write(addr, val)//Lưu trử vị trí thả vật bằng với giá trị biến count vô bộ nhớ không mất nội dung
    delay(3000); //Cho xe dừng 10 giây
    XeChayLui();//Tiếp tục cho xe chạy lùi 
  }

  

  if (digitalRead(NutStart)== 0)
  {
    //Cho xe chạy tới
    XeChayToi();
    //Đợi xe chạm nút chữa cháy
    while ((digitalRead(NutChuaChay)== 0))
        ;
    delay(2000);

    //Thả dây

    //delay
    
    //Bật nam châm

    //Thu 

    //delay
  
    //Gán giá trị count = 0
    count = 0;
  
    //Cho phép interrupt để xe bắt đầu đo khoảng cách
    interrupts();
    
    //Cho xe chạy lùi
    XeChayLui();
       
    //Đợi biến count == với vị trí gắp vật
    while (count!= ViTriThaVat)
        ;
    
    //Cho xe dùng
    XeStop();
       
    //Chạy động động cơ thả
      
    
    //Tắt nam châm hút vật

    
    //Thu dây lên nếu cần
    
    
    //Cho xe chạy lùi tới vị trí thả vật
    
    //Cho xe chạy lùi
    XeChayLui();
    
    //Kết thúc
    delay(5000);
    XeStop();
  }
}

void XeChayToi()
{
  
}

void XeChayLui()
{
  
}

void XeStop()
{
  
}

void DongCoTha()
{
  
}

void DongCoThu()
{
  
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
