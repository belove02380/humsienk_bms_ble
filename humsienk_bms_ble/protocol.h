#pragma once
#include <vector>
#include <stdint.h>

namespace humsienk_protocol {

struct BmsData {
  float total_voltage;
  float current;
  float soc;
  float temp1;
  float temp2;
  float cell_voltage[4];
  bool charge_mos;
  bool discharge_mos;
};

bool decode_frame(const std::vector<uint8_t> &data, BmsData &out);

}
