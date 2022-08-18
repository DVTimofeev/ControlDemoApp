#include "AdamModBus/modbusTCP.h"

/**
 * @brief valve with one coil and 2 states opened/closed
 * 
 * EXAMPLE: valve 2/2 or 3/2, both has one coil and two states
 * 
 * This struct is to bind object(valve) to adam I/O controller pin address  
 */
struct ValveSingleCoil{
    ValveSingleCoil(modbus::ModbusTCP* adam, uint8_t address) : 
        adam_(adam), address_(address) {}
    
    void open()
    {
        adam_->write_DO(address_, true);
    }

    void close()
    {
        adam_->write_DO(address_, false);
    }

    bool is_opened()
    {
        return adam_->read_DO(address_).value_or(false);
    }

    private:
        uint8_t address_;
        modbus::ModbusTCP* adam_;
};

/**
 * @brief valve with two active coils each can be triggered separetly, 
 * but to switch position of valve oposite states of coils is required
 * 
 * EXAMPLE: valve 5/3 which redirects flow in two directions
 * 
 * This struct is to bind object(valve) to adam I/O controller pin address  
 */
struct ValveDoubleCoil{
    ValveDoubleCoil(modbus::ModbusTCP* adam, uint8_t address1, uint8_t address2) : 
        adam_(adam), address1_(address1), address2_(address2) {}

    void switch1_2()
    {
        adam_->write_DO(address1_, true);
        adam_->write_DO(address2_, false);
    }

    void switch2_1()
    {
        adam_->write_DO(address2_, true);
        adam_->write_DO(address1_, false);
    }

    void close()
    {
        adam_->write_DO(address1_, false);
        adam_->write_DO(address2_, false);
    }

    bool is_opened()
    {
        return adam_->read_DO(address1_).value_or(false) || adam_->read_DO(address2_).value_or(false);
    }

    private:
        uint8_t address1_;
        uint8_t address2_;
        modbus::ModbusTCP* adam_;
};

/**
 * @brief turn on/off heater at address
 * 
 * 
 * This struct is to bind object(heater) to adam I/O controller pin address  
 */
struct Heater{
    Heater(modbus::ModbusTCP* adam, uint8_t address) : 
        adam_(adam), address_(address) {}

    void turn_on(){
        adam_->write_DO(address_, true);
    }

    void turn_off(){
        adam_->write_DO(address_, false);
    }

    bool is_on()
    {
        return adam_->read_DO(address_).value_or(false);
    }

    private:
        uint8_t address_;
        modbus::ModbusTCP* adam_;
}