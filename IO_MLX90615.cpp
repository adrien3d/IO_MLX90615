/***************************************************************************
  This is a library for the MLX90614 InfraRed temperature sensor

  Designed to work with all kinds of MLX90614 Breakout Boards

  These sensors use I2C, 2 pins are required to interface.

  Written by Adrien Chapelet for Iotech
 ***************************************************************************/

#include "IO_MLX90615.h"

IO_MLX90615::IO_MLX90615(uint8_t i2caddr) {
  _addr = i2caddr;
}


boolean IO_MLX90615::begin(void) {
  Wire.begin();

  /*
  for (uint8_t i=0; i<0x20; i++) {
    Serial.print(i); Serial.print(" = ");
    Serial.println(read16(i), HEX);
  }
  */
  return true;
}

//////////////////////////////////////////////////////


double IO_MLX90615::readObjectTempF(void) {
  return (readTemp(MLX90615_TOBJ1) * 9 / 5) + 32;
}


double IO_MLX90615::readAmbientTempF(void) {
  return (readTemp(MLX90615_TA) * 9 / 5) + 32;
}

/*double IO_MLX90615::readObjectTempC(void) {
  return readTemp(MLX90615_TOBJ1);
}


double IO_MLX90615::readAmbientTempC(void) {
  return readTemp(MLX90615_TA);
}*/

double IO_MLX90615::readObjectTempC(void) {
  return readTemp(MLX90615_OBJECT_TEMPERATURE);
}


double IO_MLX90615::readAmbientTempC(void) {
  return readTemp(MLX90615_AMBIENT_TEMPERATURE);
}

//From Grove
float getTemperature(int Temperature_kind) {
  float celcius = 0.0;
 /* byte dev = (i2c_addr << 1);  // remain to be seen!
  byte dataLow = 0;
  byte dataHigh = 0;
  byte pec = 0;

  bus->start(dev | I2C_WRITE);
  bus->write(Temperature_kind);
  // read
  bus->restart(dev | I2C_READ);
  dataLow = bus->read(false);
  dataHigh = bus->read(false);
  pec = bus->read(true);
  bus->stop();

  //This converts high and low bytes together and processes temperature, MSB is a error bit and is ignored for temps
  double tempFactor = 0.02; // 0.02 degrees per LSB (measurement resolution of the MLX90614)
  double tempData = 0x0000; // zero out the data
  int frac; // data past the decimal point

  // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
  tempData = (double)(((dataHigh & 0x007F) << 8) | dataLow);
  tempData = (tempData * tempFactor) - 0.01;

  celcius = (float)(tempData - 273.15);*/

  return celcius;
  //return = (celcius*1.8) + 32;//Fahrenheit
}

float IO_MLX90615::readTemp(uint8_t reg) {
  float temp;
  
  temp = read16(reg);
  temp *= .02;
  temp  -= 273.15;
  return temp;
}

/*********************************************************************/

uint16_t IO_MLX90615::read16(uint8_t a) {
  uint16_t ret;

  Wire.beginTransmission(_addr); // start transmission to device 
  Wire.write(a); // sends register address to read from
  Wire.endTransmission(false); // end transmission
  
  Wire.requestFrom(_addr, (uint8_t)3);// send data n-bytes read
  ret = Wire.read(); // receive DATA
  ret |= Wire.read() << 8; // receive DATA

  uint8_t pec = Wire.read();

  return ret;
}
