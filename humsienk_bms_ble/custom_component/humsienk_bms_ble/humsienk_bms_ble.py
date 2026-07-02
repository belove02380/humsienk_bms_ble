import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import ble_client, sensor, binary_sensor
from esphome.const import (
    CONF_ID,
    UNIT_VOLT,
    UNIT_AMPERE,
    UNIT_PERCENT,
    UNIT_CELSIUS,
)

AUTO_LOAD = ["ble_client"]

humsienk_bms_ble_ns = cg.esphome_ns.namespace("humsienk_bms_ble")
HumsienkBmsBle = humsienk_bms_ble_ns.class_("HumsienkBmsBle", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(HumsienkBmsBle),
    cv.Required("ble_client_id"): cv.use_id(ble_client.BLEClient),
    cv.Optional("update_interval", default="5s"): cv.update_interval,
})

SENSORS = {
    "total_voltage": UNIT_VOLT,
    "current": UNIT_AMPERE,
    "soc": UNIT_PERCENT,
    "temperature_1": UNIT_CELSIUS,
    "temperature_2": UNIT_CELSIUS,
    "cell_voltage_1": UNIT_VOLT,
    "cell_voltage_2": UNIT_VOLT,
    "cell_voltage_3": UNIT_VOLT,
    "cell_voltage_4": UNIT_VOLT,
}

BINARY_SENSORS = {
    "charge_mos": None,
    "discharge_mos": None,
}

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.set_update_interval(config["update_interval"]))

    client = yield cg.get_variable(config["ble_client_id"])
    cg.add(var.set_ble_client(client))

    # Sensors
    for key, unit in SENSORS.items():
        if key in config:
            sens = yield sensor.new_sensor(config[key])
            cg.add(getattr(var, f"set_{key}_sensor")(sens))

    # Binary sensors
    for key in BINARY_SENSORS:
        if key in config:
            bs = yield binary_sensor.new_binary_sensor(config[key])
            cg.add(getattr(var, f"set_{key}_binary_sensor")(bs))
