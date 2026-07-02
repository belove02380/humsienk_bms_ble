#include "humsienk_bms_ble.h"
#include "esphome/core/log.h"

namespace esphome {
namespace humsienk_bms_ble {

static const char *TAG = "humsienk_bms_ble";

static const uint16_t NOTIFY_HANDLE = 0xFFF1;
static const uint16_t WRITE_HANDLE  = 0xFFF2;

void HumsienkBmsBle::dump_config() {
  ESP_LOGCONFIG(TAG, "Humsienk BMS BLE (BMC-04001)");
}

void HumsienkBmsBle::loop() {}

void HumsienkBmsBle::handle_notify(uint16_t handle, const std::vector<uint8_t> &data) {
  if (handle != NOTIFY_HANDLE) return;

  humsienk_protocol::BmsData bms;
  if (!humsienk_protocol::decode_frame(data, bms)) return;

  if (this->total_voltage_sensor)
    this->total_voltage_sensor->publish_state(bms.total_voltage);

  if (this->current_sensor)
    this->current_sensor->publish_state(bms.current);

  if (this->soc_sensor)
    this->soc_sensor->publish_state(bms.soc);

  if (this->temperature_1_sensor)
    this->temperature_1_sensor->publish_state(bms.temp1);

  if (this->temperature_2_sensor)
    this->temperature_2_sensor->publish_state(bms.temp2);

  for (int i = 0; i < 4; i++) {
    if (this->cell_voltage_sensor[i])
      this->cell_voltage_sensor[i]->publish_state(bms.cell_voltage[i]);
  }

  if (this->charge_mos_sensor)
    this->charge_mos_sensor->publish_state(bms.charge_mos);

  if (this->discharge_mos_sensor)
    this->discharge_mos_sensor->publish_state(bms.discharge_mos);
}

void HumsienkBmsBle::send_command(uint8_t cmd, uint8_t value) {
  std::vector<uint8_t> frame = {0xAA, 0x55, 0x05, cmd, value, 0x00, 0x00};
  this->parent_->write_value(WRITE_HANDLE, frame);
}

}  // namespace humsienk_bms_ble
}  // namespace esphome
