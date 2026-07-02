#pragma once

#include "esphome/components/ble_client/ble_client.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/core/component.h"
#include "protocol.h"

namespace esphome {
namespace humsienk_bms_ble {

class HumsienkBmsBle : public Component, public ble_client::BLEClientNode {
 public:
  void dump_config() override;
  void loop() override;

  sensor::Sensor *total_voltage_sensor = nullptr;
  sensor::Sensor *current_sensor = nullptr;
  sensor::Sensor *soc_sensor = nullptr;
  sensor::Sensor *temperature_1_sensor = nullptr;
  sensor::Sensor *temperature_2_sensor = nullptr;

  sensor::Sensor *cell_voltage_sensor[4];

  binary_sensor::BinarySensor *charge_mos_sensor = nullptr;
  binary_sensor::BinarySensor *discharge_mos_sensor = nullptr;

 protected:
  void handle_notify(uint16_t handle, const std::vector<uint8_t> &data) override;
  void send_command(uint8_t cmd, uint8_t value);
};

}  // namespace humsienk_bms_ble
}  // namespace esphome
