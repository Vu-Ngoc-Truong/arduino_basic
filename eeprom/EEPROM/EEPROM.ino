

#include <EEPROM.h>

int ADDR_EEPROM_ADDR_SAVE = 10;
int eeAddrSave = 100;

// Lưu dữ liệu giao dịch vào EEPROM nếu giao dịch thành công
void luuDuLieuGD()
{
  // lấy các dữ liệu
  byte dataSave[];
  dataSave[0] = 0;
  dataSave[1] = 1;
  dataSave[2] = 2;
  dataSave[3] = 3;
  dataSave[4] = 4;
  dataSave[5] = 5;
  dataSave[6] = 6;
  dataSave[7] = 7;
  dataSave[8] = 8;
  dataSave[9] = 0 ;

  // ghi vào eeprom 10 byte
  EEPROM.get(ADDR_EEPROM_ADDR_SAVE,eeAddrSave)   ; // Lấy vị trí lưu trong EEPROM
  for (int i = 0;  i < 10; i++)
  {
    EEPROM.write(eeAddrSave, dataSave[i]);  
    eeAddrSave++;
  }
  // Khi bộ nhớ đầy thì lưu lại ở vị trí đầu
  if ( eeAddrSave >= ADDR_EEPROM_END_SAVE ) 
  {
    eeAddrSave = ADDR_EEPROM_START_SAVE ; // Quay lại vị trí lưu đầu tiên
  }
  
  EEPROM.put(ADDR_EEPROM_ADDR_SAVE,eeAddrSave)   ; // Lưu lại vị trí con trỏ trong EEPROM
  
}

void setup() {

 
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Read float from EEPROM: ");

  //Get the float data from the EEPROM at position 'eeAddress'
  EEPROM.get(eeAddress, f);
  Serial.println(f, 3);    //This may print 'ovf, nan' if the data inside the EEPROM is not a valid float.


}



void loop() {
  /* Empty loop */
}
