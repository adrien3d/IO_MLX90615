/***************************************************************************
  This is a library for the MLX90614 InfraRed temperature sensor

  Designed to work with all kinds of MLX90614 Breakout Boards

  These sensors use I2C, 2 pins are required to interface.

  Written by Adrien Chapelet for Iotech
 ***************************************************************************/

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"


#define MLX90615_I2CADDR 0x5B
  
#define MLX90615_OBJECT_TEMPERATURE     0x27
#define MLX90615_AMBIENT_TEMPERATURE    0x26

// RAM
#define MLX90615_RAWIR1 0x04
#define MLX90615_RAWIR2 0x05
#define MLX90615_TA 0x06
#define MLX90615_TOBJ1 0x07
#define MLX90615_TOBJ2 0x08
// EEPROM
#define MLX90615_TOMAX 0x20
#define MLX90615_TOMIN 0x21
#define MLX90615_PWMCTRL 0x22
#define MLX90615_TARANGE 0x23
#define MLX90615_EMISS 0x24
#define MLX90615_CONFIG 0x25
#define MLX90615_ADDR 0x0E
#define MLX90615_ID1 0x3C
#define MLX90615_ID2 0x3D
#define MLX90615_ID3 0x3E
#define MLX90615_ID4 0x3F


class IO_MLX90615  {
 public:
  IO_MLX90615(uint8_t addr = MLX90615_I2CADDR);
  boolean begin();
  uint32_t readID(void);

  double readObjectTempF(void);
  double readAmbientTempF(void);
  double readObjectTempC(void);
  double readAmbientTempC(void);

  float getTemperature(int Temperature_kind);

 private:
  float readTemp(uint8_t reg);

  uint8_t _addr;
  uint16_t read16(uint8_t addr);
  void write16(uint8_t addr, uint16_t data);
};

