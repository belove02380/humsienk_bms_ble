#include "protocol.h"

namespace humsienk_protocol {

bool decode_frame(const std::vector<uint8_t> &data, BmsData &out) {
  if (data.size() < 20) return false;
  if (data[0] != 0xAA || data[1] != 0x55) return false;

  uint8_t cmd = data[3];
  if (cmd != 0x03) return false;

  out.total_voltage = (data[4] * 256 + data[5]) / 100.0f;
  out.current = ((data[6] * 256 + data[7]) - 30000) / 100.0f;
  out.soc = data[8];

  out.temp1 = data[9] - 40;
  out.temp2 = data[10] - 40;

  for (int i = 0; i < 4; i++) {
    out.cell_voltage[i] =
        (data[11 + i * 2] * 256 + data[12 + i * 2]) / 1000.0f;
  }

  out.charge_mos = data[20] & 0x01;
  out.discharge_mos = data[20] & 0x02;

  return true;
}

}
