/*
 * c-MX25Series is an C Library for the Macronix MX25-Series flash chips.
 * Copyright (C) 2021 eResearch, James Cook University
 * Author: NigelB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Repository: https://github.com/jcu-eresearch/c-MX25-Series
 *
 */

#include "MX25Series.h"
#include "stdio.h"

MX25Series_Chip_Info_t MX25R6435F_Chip_Def_Low_Power = {
        .manufacturer_id=MX25R6435F_MANUFACTURER_ID,
        .memory_type=MX25R6435F_MEMORY_TYPE,
        .memory_density=MX25R6435F_MEMORY_DENSITY,
        .memory_size=MX25R6435F_MEMORY_SIZE,
        .page_size=MX25R6435F_PAGE_SIZE,
        .timing = {
                .tBP=MX25R6435F_tBP_LP,
                .tPP=MX25R6435F_tPP_LP,
                .tSE=MX25R6435F_tSE_LP,
                .tBE32K=MX25R6435F_tBE32K_LP,
                .tBE64K=MX25R6435F_tBE64K_LP,
                .tCE=MX25R6435F_tCE_LP,
                .tWSR=MX25R6435F_tW_LP,
                .tUNKNOWN=MX25Series_tUNKNOWN_TIMING
        },
        .name="MX25R6435F"
};

MX25Series_Chip_Info_t MX25R6435F_Chip_Def_High_Performance = {
        .manufacturer_id=MX25R6435F_MANUFACTURER_ID,
        .memory_type=MX25R6435F_MEMORY_TYPE,
        .memory_density=MX25R6435F_MEMORY_DENSITY,
        .memory_size=MX25R6435F_MEMORY_SIZE,
        .page_size=MX25R6435F_PAGE_SIZE,
        .timing = {
                .tBP=MX25R6435F_tBP_HP,
                .tPP=MX25R6435F_tPP_HP,
                .tSE=MX25R6435F_tSE_HP,
                .tBE32K=MX25R6435F_tBE32K_HP,
                .tBE64K=MX25R6435F_tBE64K_HP,
                .tCE=MX25R6435F_tCE_HP,
                .tWSR=MX25R6435F_tW_HP,
                .tUNKNOWN=MX25Series_tUNKNOWN_TIMING
        },
        .name="MX25R6435F"
};


MX25Series_status_enum_t MX25Series_init(MX25Series_t *dev, MX25Series_Chip_Info_t *chip_def, uint8_t cs_pin, uint8_t reset_pin, uint8_t wp_pin, uint8_t transfer_dummy_byte, void* ctx)
{
    memset(dev, 0, sizeof(MX25Series_t));
    dev->cs_pin = cs_pin;
    dev->reset_pin = reset_pin;
    dev->wp_pin = wp_pin;
    dev->transfer_dummy_byte = transfer_dummy_byte;
    dev->ctx = ctx;
    dev->chip_def = chip_def;

    MX25Series___enable_cs_pin(dev, false);
    MX25Series___enable_reset_pin(dev, false);
    MX25Series___enable_write_protect_pin(dev, false);

    if(dev->chip_def == NULL)
    {
        return MX25Series_status_error_invalid_chip_def;
    }

    return MX25Series_status_ok;
}

MX25Series_status_enum_t MX25Series_read_identification(MX25Series_t *dev, int *manufacturer_id, int *memory_type, int *memory_density)
{
    MX25Series_status_enum_t result = MX25Series_status_init;
    uint8_t value[3] = {0};

    MX25Series___enable_cs_pin(dev, true);
    result = MX25Series___issue_command(dev, MX25Series_Command_RDID);
    result |= MX25Series___read(dev, 3, value);
    MX25Series___enable_cs_pin(dev, false);

    *manufacturer_id = value[0];
    *memory_type = value[1];
    *memory_density = value[2];

    if(dev->chip_def == NULL)
    {
        return MX25Series_status_error_invalid_chip_def;
    }

    if(
            value[0] != dev->chip_def->manufacturer_id &&
            value[1] != dev->chip_def->memory_type &&
            value[2] != dev->chip_def->memory_density
    )
    {
        return MX25Series_status_error_incorrect_ids;
    }

    return result;
}

MX25Series_status_enum_t MX25Series_read_electronic_signature(MX25Series_t *dev, int *electronic_id)
{
    MX25Series_status_enum_t result = MX25Series_status_init;
    uint8_t value;

    MX25Series___enable_cs_pin(dev, true);
    result = MX25Series___issue_command(dev, MX25Series_Command_RES);
    result |= MX25Series___read(dev, sizeof(result), &value);
    *electronic_id = result;
    MX25Series___enable_cs_pin(dev, false);
    return result;
}

MX25Series_status_enum_t MX25Series_read_manufacture_and_device_id(MX25Series_t *dev, int *manufacturer_id, int *memory_type)
{
    MX25Series_status_enum_t result = MX25Series_status_init;
    uint8_t value[2];

    MX25Series___enable_cs_pin(dev, true);
    result = MX25Series___issue_command(dev, MX25Series_Command_REMS);
    result |= MX25Series___read(dev, sizeof(value), (uint8_t *) &value);
    *manufacturer_id = value[0];
    *memory_type = value[1];
    MX25Series___enable_cs_pin(dev, false);
    return result;
}

MX25Series_status_enum_t MX25Series_read_status_register(MX25Series_t *dev, uint8_t *status_register)
{
    MX25Series_status_enum_t result = MX25Series_status_init;

    MX25Series___enable_cs_pin(dev, true);
    result = MX25Series___issue_command(dev, MX25Series_Command_RDSR);
    result |= MX25Series___read(dev, 1, status_register);
    MX25Series___enable_cs_pin(dev, false);
    return result;
}

MX25Series_status_enum_t MX25Series_read_configuration_register(MX25Series_t *dev, uint16_t *configuration_register)
{
    MX25Series_status_enum_t result = MX25Series_status_init;

    MX25Series___enable_cs_pin(dev, true);
    result = MX25Series___issue_command(dev, MX25Series_Command_RDCR);
    result |= MX25Series___read(dev, sizeof(*configuration_register), (uint8_t *) configuration_register);
    MX25Series___enable_cs_pin(dev, false);
    return result;
}

MX25Series_status_enum_t MX25Series_configure_chip(
        MX25Series_t *dev,
        uint8_t status_register,
        uint16_t configuration_register)
{
    MX25Series_status_enum_t result = MX25Series_status_init;

    MX25Series___enable_cs_pin(dev, true);
    result = MX25Series___issue_command(dev, MX25Series_Command_WRSR);
    result |= MX25Series___write(dev, 1, &status_register);
    result |= MX25Series___write(dev, 2, (uint8_t *) &configuration_register);
    MX25Series___enable_cs_pin(dev, false);
    return result;
}

MX25Series_status_enum_t MX25Series_set_write_enable(MX25Series_t *dev, bool enable)
{
    MX25Series_status_enum_t result = MX25Series_status_init;

    MX25Series___enable_cs_pin(dev, true);
    result = MX25Series___issue_command(dev, enable ? MX25Series_Command_WREN : MX25Series_Command_WRDI);
    MX25Series___enable_cs_pin(dev, false);
    return result;
}

MX25Series_status_enum_t MX25Series_read_stored_data(
        MX25Series_t *dev,
        bool use_fast_mode,
        uint32_t memory_address,
        size_t length,
        uint8_t* buffer)
{
    MX25Series_status_enum_t result = MX25Series_status_init;
    uint8_t address[3] = {0};

    address[0] = (memory_address & 0xFF0000) >> 16;
    address[1] = (memory_address & 0xFF00) >> 8;
    address[2] = (memory_address & 0xFF);

    MX25Series___enable_cs_pin(dev, true);
    
    //Send the READ Command
    result = MX25Series___issue_command(dev, use_fast_mode ? MX25Series_Command_FAST_READ : MX25Series_Command_READ);

    //Send the memory address we wish to retrieve
    result |= MX25Series___write(dev, sizeof(address), address);

    //In fast mode a dummy byte needs to be transferred after the address.
    if(use_fast_mode)
    {
        uint8_t dummy = dev->transfer_dummy_byte;
        MX25Series___write(dev, 1, &dummy);
    }

    //read the data
    result |= MX25Series___read(dev, length, buffer);

    MX25Series___enable_cs_pin(dev, false);

    return result;
}

MX25Series_status_enum_t MX25Series_write_stored_data(
        MX25Series_t *dev,
        uint32_t memory_address,
        size_t length,
        uint8_t* buffer)
{
    MX25Series_status_enum_t result = MX25Series_status_init;
    uint8_t address[3] = {0};

    address[0] = (memory_address & 0xFF0000) >> 16;
    address[1] = (memory_address & 0xFF00) >> 8;
    address[2] = (memory_address & 0xFF);

    MX25Series___enable_cs_pin(dev, true);

    //Send the PP Command
    result = MX25Series___issue_command(dev, MX25Series_Command_PP);
//    result = MX25Series___issue_command(dev, MX25Series_Command_4PP);

    //Send the memory address we wish to retrieve
    result |= MX25Series___write(dev, sizeof(address), address);

    //write the data
    result |= MX25Series___write(dev, length, buffer);

    MX25Series___enable_cs_pin(dev, false);

    return result;

}

MX25Series_status_enum_t MX25Series_erase(
        MX25Series_t *dev,
        MX25Series_Erase_enum_t erase_type,
        uint32_t memory_address)
{
    MX25Series_status_enum_t result = MX25Series_status_init;
    MX25Series_COMMAND_enum_t command;
    switch(erase_type)
    {
        case MX25Series_Command_SE:
        case MX25Series_Command_BE32K:
        case MX25Series_Command_BE64K:
        case MX25Series_Command_CE:
            command = (MX25Series_COMMAND_enum_t)erase_type;
            break;
        default:
            return result;
    }

    uint8_t address[3] = {0};

    address[0] = (memory_address & 0xFF0000) >> 16;
    address[1] = (memory_address & 0xFF00) >> 8;
    address[2] = (memory_address & 0xFF);

    MX25Series___enable_cs_pin(dev, true);

    //Send the Erase Command
    result = MX25Series___issue_command(dev, command);

    //Send the memory address we wish to erase, except for chip erase.
    if(command != MX25Series_Command_CE) {
        result |= MX25Series___write(dev, sizeof(address), address);
    }

    MX25Series___enable_cs_pin(dev, false);
    return result;
}

const char* MX25Series_get_erasure_size_string(MX25Series_Erase_enum_t size)
{
    switch(size)
    {
        case MX25Series_Erase_Block_4K: {return "4 KB";} break;
        case MX25Series_Erase_Block_32K: {return "32 KB";} break;
        case MX25Series_Erase_Block_64K: {return "64 KB";} break;
        case MX25Series_Erase_Chip: {return "Entire Chip";} break;
        case MX25Series_Erase_Undefined:
        default: {return "Undefined";}
    }
    return "Undefined";
}

uint32_t MX25Series_get_erasure_max_time(MX25Series_t *dev, MX25Series_Erase_enum_t erase_type)
{
    switch(erase_type)
    {
        case MX25Series_Erase_Block_4K:
            return dev->chip_def->timing.tSE;
            break;
        case MX25Series_Erase_Block_32K:
            return dev->chip_def->timing.tBE32K;
            break;
        case MX25Series_Erase_Block_64K:
            return dev->chip_def->timing.tBE64K;
            break;
        case MX25Series_Erase_Chip:
            return dev->chip_def->timing.tCE;
            break;
        case MX25Series_Erase_Undefined:
        default:
            return dev->chip_def->timing.tUNKNOWN;
    }
    return dev->chip_def->timing.tUNKNOWN;
}

MX25Series_status_enum_t MX25Series_read_security_register(
        MX25Series_t *dev,
        uint8_t *security_register)
{
    MX25Series_status_enum_t result = MX25Series_status_init;

    MX25Series___enable_cs_pin(dev, true);
    result = MX25Series___issue_command(dev, MX25Series_Command_RDSCUR);
    result |= MX25Series___read(dev, 1, security_register);
    MX25Series___enable_cs_pin(dev, false);
    return result;
}

MX25Series_status_enum_t MX25Series_write_security_register(
        MX25Series_t *dev,
        uint8_t *security_register)
{
    MX25Series_status_enum_t result = MX25Series_status_init;

    return result;
}

__attribute__((weak)) MX25Series_status_enum_t MX25Series___issue_command(MX25Series_t *dev, MX25Series_COMMAND_enum_t command)
{
    return MX25Series_status_error;
}

__attribute__((weak)) MX25Series_status_enum_t MX25Series___read(MX25Series_t *dev, size_t length, uint8_t* buffer)
{
    dev->state = 0xFFFFFFF1;
    return MX25Series_status_error;
}

__attribute__((weak)) MX25Series_status_enum_t MX25Series___write(MX25Series_t *dev, size_t length, uint8_t* buffer)
{
    dev->state = 0xFFFFFFF2;
    return MX25Series_status_error;
}

__attribute__((weak)) void MX25Series___enable_cs_pin(MX25Series_t *dev, bool value)
{
    dev->state = 0xFFFFFFF3;
}

__attribute__((weak)) void MX25Series___enable_reset_pin(MX25Series_t *dev, bool value)
{
    dev->state = 0xFFFFFFF4;
}

__attribute__((weak)) void MX25Series___enable_write_protect_pin(MX25Series_t *dev, bool value)
{
    dev->state = 0xFFFFFFF5;
}

__attribute__((weak)) bool MX25Series___test_linker(MX25Series_t *dev)
{
    dev->state = 0xFFFFFFF6;
    return false;
}

__attribute__((weak)) void MX25Series___delay_micro_second(MX25Series_t *dev, unsigned int us)
{
    dev->state = 0xFFFFFFF8;
}




