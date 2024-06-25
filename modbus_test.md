// coil ------------------
01 01 00 00 00 32 BD DF   // traditional modbus request

00 00 00 00 00 06 01 01 00 00 00 0A  // IP modbus request
00 00 00 00 00 05 01 01 02 01 02  // IP modbus response
// coil ------------------

//decrete input -------------------
01 02 00 00 00 32 F9 DF // traditional modbus request

00 00 00 00 00 06 01 02 00 00 00 0A  // IP modbus request
//decrete input -------------------

// holding register ----------------------------------------------------------------------------------------
01 03 00 00 00 0A C5 CD	// traditional modbus request
01 03 14 00 30 00 31 00 32 00 33 00 34 00 35 00 36 00 37 00 38 00 39 3C A3 // traditional modbus response

00 0C 00 00 00 06 01 03 00 00 00 0A // IP modbus request
00 0C 00 00 00 17 01 03 14 00 0B 00 0C 00 01 00 02 00 03 00 04 00 05 00 06 00 07 00 08 // IP modbus response
// holding register ----------------------------------------------------------------------------------------

// input register ------------------------------------
01 04 00 00 00 32 71 DF // traditional modbus request

00 00 00 00 00 06 01 04 00 00 00 0A // IP modbus request
// input register ------------------------------------


// write single coil -----------------------------------
01 05 00 07 00 01 BD CB // traditional modbus request


// write single coil -----------------------------------

00 A9 00 00 00 06 01 05 00 00 FF 00 // IP modbus request
00 A9 00 00 00 06 01 05 00 00 FF 00 // IP modbus response
// write single coil -----------------------------------

// write single register --------------------------------

// write single register --------------------------------

// write multi coil -------------------------------------
01 0F 00 05 00 14 03 89 24 09 0F 99 // traditional modbus request

00 00 00 00 00 0A 01 0F 00 00 00 14 03 00 00 00 // IP modbus request
// write multi coil -------------------------------------

// write multi register -------------------------------------
01 10 00 00 00 05 0A 00 00 00 00 00 00 00 00 00 00 01 F8  // traditional modbus request
// write multi register -------------------------------------

int ModRTU_CRC(char* buf, int len)
{
  int crc = 0xFFFF;
  
  for (int pos = 0; pos < len; pos++) {
    crc ^= (int)buf[pos];          // XOR byte into least sig. byte of crc
  
    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;  
}