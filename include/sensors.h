#include "AdamModBus/modbusTCP.h"

/**
 * @brief struct for reading pressure sensors
 * 
 */
struct PressureSensor{
    PressureSensor(modbus::ModbusTCP* adam, uint8_t address) : 
        adam_(adam), address_(address) {}

    float get_pressure(){
        if(auto pressure = get_value())
        {
            return calc_pressure(pressure.value);
        }
        else
        {
            return 9999.f;
        }

    }

    private:
        float calc_pressure(uint16_t value){
            auto max = std::numeric_limits<uint16_t>::max();
            float a = 10.0f / max; // 10 bar == 10 volts;
            float c = 0.0f; //shift
            return a*value + c;
        }

        std::optional<uint16_t> get_value(){
            return adam_->read_AI;
        }

        uint8_t address_;
        modbus::ModbusTCP* adam_;
}
