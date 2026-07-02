# Humsienk BMS BLE (BMC-04001) for ESPHome

This ESPHome external component adds full BLE support for Humsienk Smart BMS using protocol BMC-04001.

## BLE Handles
- Service: 0xFFF0
- Notify: 0xFFF1
- Write: 0xFFF2

## ESPHome YAML Example

```yaml
external_components:
  - source: github://christophe/humsienk-bms-ble

esp32_ble_tracker:

ble_client:
  - mac_address: XX:XX:XX:XX:XX:XX
    id: humsienk_client

humsienk_bms_ble:
  ble_client_id: humsienk_client
  update_interval: 5s
