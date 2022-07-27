#include "AdamModBus/modbusTCP.h"

struct Valve_2_2{
    Valve_2_2(modbus::ModbusTCP* adam, uint8_t address) : 
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

struct Valve_3_2{
    Valve_3_2(modbus::ModbusTCP* adam, uint8_t address1, uint8_t address2) : 
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
        return adam_->read_DO(address1_).value_or(false) && adam_->read_DO(address2_).value_or(false);
    }

    private:
        uint8_t address1_;
        uint8_t address2_;
        modbus::ModbusTCP* adam_;
};