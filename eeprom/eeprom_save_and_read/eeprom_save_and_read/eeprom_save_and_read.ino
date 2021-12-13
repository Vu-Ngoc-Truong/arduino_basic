

#include <EEPROM.h>

// EEPROM Map
#define ADDR_EEPROM_ADDR_SAVE 10        // Vị trí lưu địa chỉ cho giao dịch hiện tại
#define ADDR_EEPROM_START_SAVE 100     // Vị trí bắt đầu lưu giao dịch
#define ADDR_EEPROM_END_SAVE   200     // Vị trí kết thúc lưu giao dịch

int eeAddrSave ;

// Lưu dữ liệu giao dịch vào EEPROM nếu giao dịch thành công
// Lưu dữ liệu giao dịch vào EEPROM nếu giao dịch thành công
void luuDuLieuGD(byte a1,byte a2,byte a3,byte a4)
{
  // lấy các dữ liệu
  byte dataSave[10];
  dataSave[0] = a1;
  dataSave[1] = a2;
  dataSave[2] = a3;
  dataSave[3] = a4;
  dataSave[4] = 0;
  dataSave[5] = 0;
  dataSave[6] = 0;
  dataSave[7] = 0;
  dataSave[8] = 0;
  dataSave[9] = 0 ;

  // ghi vào eeprom 10 byte
  EEPROM.get(ADDR_EEPROM_ADDR_SAVE,eeAddrSave)   ; // Lấy vị trí lưu trong EEPROM
  Serial.println(eeAddrSave);
  EEPROM.put(eeAddrSave, dataSave); // luu mang gia tri vao eeprom
  eeAddrSave +=10;  // tăng giá trị đến địa chỉ lưu tiếp theo
  // Khi bộ nhớ đầy thì lưu lại ở vị trí đầu
  if ( eeAddrSave >= ADDR_EEPROM_END_SAVE )
  {
    eeAddrSave = ADDR_EEPROM_START_SAVE ; // Quay lại vị trí lưu đầu tiên
  }

  EEPROM.put(ADDR_EEPROM_ADDR_SAVE,eeAddrSave)   ; // Lưu lại vị trí con trỏ trong EEPROM

}

// Đọc dữ liệu giao dịch từ EEPROM
void docDulieuGD(int soGD)
{
  // Tìm trong EEPROM theo số lượng giao dịch
  int eeAddrSaveTemp;
  byte dataArr[10];
  bool addrOver = false;
  EEPROM.get(ADDR_EEPROM_ADDR_SAVE,eeAddrSave)   ; // Lấy vị trí lưu hiện tại trong EEPROM
  eeAddrSaveTemp = eeAddrSave;
  if ( eeAddrSave == ADDR_EEPROM_START_SAVE)
    {
      eeAddrSave = ADDR_EEPROM_END_SAVE - 10;
    }
    else
    {
      eeAddrSave -= 10;
    }
  // In header
  Serial.print("Stt\t");
  Serial.print("ID\t");
  Serial.print("Ma Sach\t");
  Serial.print("Loai_GD\t");
  Serial.print("Nam\t");
  Serial.print("Thang\t");
  Serial.print("Ngay\t");
  Serial.print("Gio\t");
  Serial.print("Phut\t");
  Serial.println("Giay\t");
  // In data giao dịch
  for (int i = 0; i < soGD; i++)
  {
    // Lưu dữ liệu vòng tròn : start -->  end -- > start
    // đọc data từ giao dịch gần nhất nên bộ nhớ sẽ đọc từ địa chỉ cao xuống thấp
    if ( eeAddrSave < ADDR_EEPROM_START_SAVE)
    {
      eeAddrSave = ADDR_EEPROM_END_SAVE - 10;
      addrOver = true;
    }
    // Đọc hết 1 vòng bộ nhớ thì thoát
    if ( ( eeAddrSave < eeAddrSaveTemp ) && addrOver )
    {
      Serial.println("Đã đọc hết bộ nhớ !!!");
      break;

    }
    // Đọc giao dịch
    EEPROM.get(eeAddrSave,dataArr);
    // In các giao dịch ra màn hình
    Serial.print(i+1); // in số thứ tự
    Serial.print("\t");
    for (int j = 0; j < 9; j++)
    {
      Serial.print(dataArr[j]);
      Serial.print("\t");
    }
    Serial.println(); // Hết 1 dòng giao dịch
    //Serial.println(eeAddrSave);
    eeAddrSave -= 10; // Chuyển đến địa chỉ lưu giao dịch trước đó
  }
}


void setup() {

 
  Serial.begin(115200);
  

  // Lấy các tham số lưu ở EEPROM
  EEPROM.get(ADDR_EEPROM_ADDR_SAVE,eeAddrSave)   ;
  // Ghi giá trị vào EEPROM cho lần đầu tiên
  if ( eeAddrSave == 0 )
  {
    EEPROM.put(ADDR_EEPROM_ADDR_SAVE,ADDR_EEPROM_START_SAVE);
    eeAddrSave = ADDR_EEPROM_START_SAVE;
    Serial.println("Ghi gia tri ban dau vao EEPROM !");
  }
  // Ghi giá trị vào để đọc thử
  //eeAddrSave = ADDR_EEPROM_START_SAVE;
  /* for ( int ct = 1 ; ct <= 10; ct++)
  {
    luuDuLieuGD(ct,ct+1,ct+2,ct+3);
  } */
}



void loop() 
{
   if (Serial.available() > 0)
  {      // Check for incomding data
    String dataIn = Serial.readString();
    // Lệnh với EEPROM
    // Lệnh đọc giá trị int
    if (dataIn.startsWith("EEGET"))
    {
      int _eeAddr,_eeData;
      String dataInS = dataIn.substring(5, dataIn.length());
      _eeAddr = dataInS.toInt(); // Lấy địa chỉ EEPROM
      EEPROM.get(_eeAddr,_eeData)   ; // Lấy dữ liệu
      Serial.print("EEPROM Read Data: ");
      Serial.println(_eeData);
    }
    
    // Lệnh ghi giá trị int
    if (dataIn.startsWith("EEPUT"))
    {
      int _eeAddr,_eeData;
      String dataInS = dataIn.substring(5, 9);
      String dataInD = dataIn.substring(10, dataIn.length());
      _eeAddr = dataInS.toInt(); // Lấy địa chỉ EEPROM
      _eeData = dataInD.toInt(); // Lấy giá trị ghi vào
      EEPROM.put(_eeAddr,_eeData)   ; // Lấy dữ liệu
      Serial.println(_eeAddr);
      Serial.print("EEPROM Write Data: ");
      Serial.println(_eeData);
    }

    // Lệnh đọc dữ liệu giao dịch
    if (dataIn.startsWith("GD"))
    {
      int slGD;
      String dataInS = dataIn.substring(2, dataIn.length());
      slGD = dataInS.toInt(); // Lấy địa chỉ EEPROM
      Serial.println("Doc du lieu GD: ");
      docDulieuGD(slGD) ; // Lấy dữ liệu
    }
  }
}
