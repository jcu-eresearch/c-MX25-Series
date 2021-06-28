/*
 * c-MX25xxxYY is an C Library for the Macronix MX25R6435F flash chip.
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
 * Repository: https://github.com/jcu-eresearch/c-MX25R6435F
 *
 */

#ifndef FLASH_MX25XXXYY_H
#define FLASH_MX25XXXYY_H

#include "stdint.h"
#include "stdbool.h"
#include "string.h"

//DataSheet: https://www.macronix.com/Lists/Datasheet/Attachments/7913/MX25R6435F,%20Wide%20Range,%2064Mb,%20v1.5.pdf

#if defined(__cplusplus)
extern "C"
{
#endif

typedef enum
{
//Register/Setting Commands - Page 17
    MX25xxxYY_Command_READ = 0x03,
    MX25xxxYY_Command_FAST_READ = 0x0B,
    MX25xxxYY_Command_2READ = 0xBB,
    MX25xxxYY_Command_DREAD = 0x3B,
    MX25xxxYY_Command_4READ = 0xEB,
    MX25xxxYY_Command_QREAD = 0x6B,

    MX25xxxYY_Command_PP = 0x02,
    MX25xxxYY_Command_4PP = 0x38,
    MX25xxxYY_Command_SE = 0x20,
    MX25xxxYY_Command_BE32K = 0x52,
    MX25xxxYY_Command_BE64K = 0xD8,
    MX25xxxYY_Command_CE = 0x60, // 0x60 Or 0xC7
    MX25xxxYY_Command_RDSFDP = 0x5A,
//Register/Setting Commands - Page 18

    MX25xxxYY_Command_WREN = 0x06,
    MX25xxxYY_Command_WRDI = 0x04,
    MX25xxxYY_Command_RDSR = 0x05,
    MX25xxxYY_Command_RDCR = 0x15,
    MX25xxxYY_Command_WRSR = 0x01,
    MX25xxxYY_Command_PGM_ERS_Suspend = 0x75, // 0x75 or 0xB0
    MX25xxxYY_Command_PGM_ERS_Resume = 0x7A,  // 0x7A or 0x30
    MX25xxxYY_Command_DP = 0xB9,
    MX25xxxYY_Command_SBL = 0xC0,

//ID/Reset Commands - Page 19

    ///Read Identification
    MX25xxxYY_Command_RDID = 0x9F,
    /*! Read Electronic ID */
    MX25xxxYY_Command_RES = 0xAB,
    //Read Electronic Manufacturer and Device ID
    MX25xxxYY_Command_REMS = 0x90,
    MX25xxxYY_Command_ENSO = 0xB1,
    MX25xxxYY_Command_EXSO = 0xC1,
    MX25xxxYY_Command_RDSCUR = 0x2B,
    MX25xxxYY_Command_WRSCUR = 0x2F,
} MX25xxxYY_COMMAND_enum_t;

typedef enum
{
    MX25xxxYY_status_init = 0,
    MX25xxxYY_status_not_reported = 1,
    MX25xxxYY_status_error = 2,
    MX25xxxYY_status_ok = 4,

    MX25xxxYY_status_error_timeout =          (   0b1000 | MX25xxxYY_status_error),
    MX25xxxYY_status_error_incorrect_ids =    (  0b10000 | MX25xxxYY_status_error),
    MX25xxxYY_status_error_invalid_chip_def = ( 0b100000 | MX25xxxYY_status_error),

} MX25xxxYY_status_enum_t;


#define MX25xxxYY_HAS_ERROR(VALUE) (( (VALUE) & MX25xxxYY_status_error) !=0)

// ----------------------------------------------------------------------------

/**
 * @brief Status Register Write.
 */

typedef enum {
    MX25xxxYY_SR_SRWD_SRWD_Disable = 0, /**< Status Register Write Disable */
    MX25xxxYY_SR_SRWD_SRWD_Enable = 1, /**< Status Register Write Enable */
} MX25xxxYY_SR_SRWD_enum_t;

// ----------------------------------------------------------------------------

typedef enum {
    MX25xxxYY_SR_QE_QE_Disable = 0, /**< Quad Disable */
    MX25xxxYY_SR_QE_QE_Enable = 1, /**< Quad Enable */
} MX25xxxYY_SR_QE_enum_t;

// ----------------------------------------------------------------------------
typedef enum {
    MX25xxxYY_Erase_Undefined = 0,
    MX25xxxYY_Erase_Block_4K = MX25xxxYY_Command_SE,
    MX25xxxYY_Erase_Block_32K = MX25xxxYY_Command_BE32K,
    MX25xxxYY_Erase_Block_64K = MX25xxxYY_Command_BE64K,
    MX25xxxYY_Erase_Chip = MX25xxxYY_Command_CE,
} MX25xxxYY_Erase_enum_t;
// ----------------------------------------------------------------------------

typedef enum {
    MX25xxxYY_SR_BP_PL_0 = 0, /**< Block Protection Level 0 */
    MX25xxxYY_SR_BP_PL_1 = 1, /**< Block Protection Level 1 */
    MX25xxxYY_SR_BP_PL_2 = 2, /**< Block Protection Level 2 */
    MX25xxxYY_SR_BP_PL_3 = 3, /**< Block Protection Level 3 */
    MX25xxxYY_SR_BP_PL_4 = 4, /**< Block Protection Level 4 */
    MX25xxxYY_SR_BP_PL_5 = 5, /**< Block Protection Level 5 */
    MX25xxxYY_SR_BP_PL_6 = 6, /**< Block Protection Level 6 */
    MX25xxxYY_SR_BP_PL_7 = 7, /**< Block Protection Level 7 */
    MX25xxxYY_SR_BP_PL_8 = 8, /**< Block Protection Level 8 */
    MX25xxxYY_SR_BP_PL_9 = 9, /**< Block Protection Level 9 */
    MX25xxxYY_SR_BP_PL_10 = 10, /**< Block Protection Level 10 */
    MX25xxxYY_SR_BP_PL_11 = 11, /**< Block Protection Level 11 */
    MX25xxxYY_SR_BP_PL_12 = 12, /**< Block Protection Level 12 */
    MX25xxxYY_SR_BP_PL_13 = 13, /**< Block Protection Level 13 */
    MX25xxxYY_SR_BP_PL_14 = 14, /**< Block Protection Level 14 */
    MX25xxxYY_SR_BP_PL_15 = 15, /**< Block Protection Level 15 */
} MX25xxxYY_SR_BP_enum_t;

// ----------------------------------------------------------------------------
// Struct 'MX25xxxYY_t' positions & masks.

// Register 'MX25xxxYY.SR'.
#define MX25xxxYY_SR_SRWD_POSITION  (7ul)
#define MX25xxxYY_SR_SRWD_MASK  (0x1ul << 7ul)  /**< [7..7] Status Register Write Protect */
#define MX25xxxYY_SR_SRWD_SRWD_DISABLE  (0ul << 7ul)  /**< Status Register Write Disable */
#define MX25xxxYY_SR_SRWD_SRWD_ENABLE  (1ul << 7ul)  /**< Status Register Write Enable */
#define MX25xxxYY_SR_QE_POSITION  (6ul)
#define MX25xxxYY_SR_QE_MASK  (0x1ul << 6ul)  /**< [6..6] The Quad Enable (QE) bit, non-volatile bit, while it is "0" (factory default), it performs non-Quad and WP#,
RESET#/HOLD# are enable. While QE is "1", it performs Quad I/O mode and WP#, RESET#/HOLD# are disabled.
In the other word, if the system goes into four I/O mode (QE=1), the feature of HPM and RESET/HOLD will be
disabled */
#define MX25xxxYY_SR_QE_QE_DISABLE  (0ul << 6ul)  /**< Quad Disable */
#define MX25xxxYY_SR_QE_QE_ENABLE  (1ul << 6ul)  /**< Quad Enable */
#define MX25xxxYY_SR_BP_POSITION  (2ul)
#define MX25xxxYY_SR_BP_MASK  (0xFul << 2ul)  /**< [5..2] The Block Protect (BP3, BP2, BP1, BP0) bits, non-volatile bits, indicate the protected area (as
defined in "Table 2. Protected Area Sizes" ) of the device to against the program/erase instruction without hardware
protection mode being set. To write the Block Protect (BP3, BP2, BP1, BP0) bits requires the Write Status Register (WRSR)
instruction to be executed. Those bits define the protected area of the memory to against Page Program (PP), Sector
Erase (SE), Block Erase 32KB(BE32K), Block Erase (BE) and Chip Erase (CE) instructions (only if Block Protect bits
(BP3:BP0) set to 0, the CE instruction can be executed). The BP3, BP2, BP1, BP0 bits are "0" as default, which is un-protected. */
#define MX25xxxYY_SR_BP_PL_0  (0ul << 2ul)  /**< Block Protection Level 0 */
#define MX25xxxYY_SR_BP_PL_1  (1ul << 2ul)  /**< Block Protection Level 1 */
#define MX25xxxYY_SR_BP_PL_2  (2ul << 2ul)  /**< Block Protection Level 2 */
#define MX25xxxYY_SR_BP_PL_3  (3ul << 2ul)  /**< Block Protection Level 3 */
#define MX25xxxYY_SR_BP_PL_4  (4ul << 2ul)  /**< Block Protection Level 4 */
#define MX25xxxYY_SR_BP_PL_5  (5ul << 2ul)  /**< Block Protection Level 5 */
#define MX25xxxYY_SR_BP_PL_6  (6ul << 2ul)  /**< Block Protection Level 6 */
#define MX25xxxYY_SR_BP_PL_7  (7ul << 2ul)  /**< Block Protection Level 7 */
#define MX25xxxYY_SR_BP_PL_8  (8ul << 2ul)  /**< Block Protection Level 8 */
#define MX25xxxYY_SR_BP_PL_9  (9ul << 2ul)  /**< Block Protection Level 9 */
#define MX25xxxYY_SR_BP_PL_10  (10ul << 2ul)  /**< Block Protection Level 10 */
#define MX25xxxYY_SR_BP_PL_11  (11ul << 2ul)  /**< Block Protection Level 11 */
#define MX25xxxYY_SR_BP_PL_12  (12ul << 2ul)  /**< Block Protection Level 12 */
#define MX25xxxYY_SR_BP_PL_13  (13ul << 2ul)  /**< Block Protection Level 13 */
#define MX25xxxYY_SR_BP_PL_14  (14ul << 2ul)  /**< Block Protection Level 14 */
#define MX25xxxYY_SR_BP_PL_15  (15ul << 2ul)  /**< Block Protection Level 15 */
#define MX25xxxYY_SR_WEL_POSITION  (1ul)
#define MX25xxxYY_SR_WEL_MASK  (0x1ul << 1ul)  /**< [1..1] The Write Enable Latch (WEL) bit is a volatile bit that is set to “1” by the WREN instruction. WEL needs to be
set to “1” before the device can accept program and erase instructions, otherwise the program and erase instructions
are ignored. WEL automatically clears to “0” when a program or erase operation completes. To ensure that both WIP
and WEL are “0” and the device is ready for the next program or erase operation, it is recommended that WIP be
confirmed to be “0” before checking that WEL is also “0”. If a program or erase instruction is applied to a protected
memory area, the instruction will be ignored and WEL will clear to “0”. */
#define MX25xxxYY_SR_WEL  (1ul << 1ul)
#define MX25xxxYY_SR_WEL_GET_VALUE(REGISTER) (((REGISTER) & MX25xxxYY_SR_WEL_MASK) >> MX25xxxYY_SR_WEL_POSITION)


#define MX25xxxYY_SR_WIP_POSITION  (0ul)
#define MX25xxxYY_SR_WIP_MASK  (0x1ul << 0ul)  /**< [0..0] The Write in Progress (WIP) bit, a volatile bit, indicates whether the device is busy in program/erase/write
status register progress. When WIP bit sets to 1, which means the device is busy in program/erase/write status
register progress. When WIP bit sets to 0, which means the device is not in progress of program/erase/write status
register cycle. */
#define MX25xxxYY_SR_WIP  (1ul << 0ul)
#define MX25xxxYY_SR_WIP_GET_VALUE(REGISTER) (((REGISTER) & MX25xxxYY_SR_WIP_MASK) >> MX25xxxYY_SR_WIP_POSITION)

// Register 'MX25xxxYY.CR'.
#define MX25xxxYY_CR_DC_POSITION  (14ul)
#define MX25xxxYY_CR_DC_MASK  (0x1ul << 14ul)  /**< [14..14] Dummy Cycle */
#define MX25xxxYY_CR_DC  (1ul << 14ul)
#define MX25xxxYY_CR_TB_POSITION  (11ul)
#define MX25xxxYY_CR_TB_MASK  (0x1ul << 11ul)  /**< [11..11] The Top/Bottom (TB) bit is a non-volatile OTP bit. The Top/Bottom (TB) bit is used to configure the Block Protect
area by BP bit (BP3, BP2, BP1, BP0), starting from TOP or Bottom of the memory array. The TB bit is defaulted as “0”,
which means Top area protect. When it is set as “1”, the protect area will change to Bottom area of the memory
device. To write the TB bit requires the Write Status Register (WRSR) instruction to be executed. */
#define MX25xxxYY_CR_TB  (1ul << 11ul)
#define MX25xxxYY_CR_LH_POSITION  (1ul)
#define MX25xxxYY_CR_LH_MASK  (0x1ul << 1ul)  /**< [1..1] The Low Power / High Performance bit is a volatile bit. User can change the value of L/H switch bit to keep Ultra
Low Power mode or High Performance mode. Please check Ordering Information for the L/H Switch default
support. */
#define MX25xxxYY_CR_LH  (1ul << 1ul)

#ifndef MX25xxxYY_tUNKNOWN_TIMING
    #define MX25xxxYY_tUNKNOWN_TIMING 5000000
#endif

// These are the Max values in micro-seconds. From Page 69 of the Datasheet.
#define MX25R6435F_MANUFACTURER_ID     0xC2
#define MX25R6435F_MEMORY_TYPE         0x28
#define MX25R6435F_MEMORY_DENSITY      0x17
#define MX25R6435F_MEMORY_SIZE     0x800000 /**< 8 MB */
#define MX25R6435F_PAGE_SIZE            256 /**! 256 bytes, Page Size */

#define MX25R6435F_tBP_LP               100 /**! 100 micro-seconds, Low Power Byte-Program Max Time */
#define MX25R6435F_tPP_LP             10000 /**! 10 milli-seconds, Low Power Page Program Max Time */
#define MX25R6435F_tSE_LP            240000 /**! 240 milli-seconds, Low Power Sector Erase Max Time */
#define MX25R6435F_tBE32K_LP        3000000 /**! 3 seconds, Low Power 32KB Block Erase Max Time */
#define MX25R6435F_tBE64K_LP        3500000 /**! 3.5 seconds, Low Power 64KB Block Erase Max Time */
#define MX25R6435F_tCE_LP         240000000 /**! 240 seconds, Low Power Chip Erase Max Time */
#define MX25R6435F_tW_LP              30000 /**! 20 milli-seconds. Low Power Write Status Register Cycle Time */

#define MX25R6435F_tBP_HP               100 /**! 100 micro-seconds, High Performance Byte-Program Max Time */
#define MX25R6435F_tPP_HP             10000 /**! 10 milli-seconds, High Performance Page Program Max Time */
#define MX25R6435F_tSE_HP            240000 /**! 240 milli-seconds, High Performance Sector Erase Max Time */
#define MX25R6435F_tBE32K_HP        1500000 /**! 1.5 seconds, High Performance 32KB Block Erase Max Time */
#define MX25R6435F_tBE64K_HP        3000000 /**! 3 seconds, High Performance 64KB Block Erase Max Time */
#define MX25R6435F_tCE_HP         150000000 /**! 150 seconds, High Performance Chip Erase Max Time */
#define MX25R6435F_tW_HP              20000 /**! 20 milli-seconds. High Performance Write Status Register Cycle Time */


typedef struct
{
    uint8_t manufacturer_id;
    uint8_t memory_type;
    uint8_t memory_density;
    uint32_t memory_size;
    uint32_t page_size;
    struct{
        uint32_t tBP;      /**! Byte-Program Max Time */
        uint32_t tPP;      /**! Page Program Max Time */
        uint32_t tSE;      /**! Sector Erase Max Time */
        uint32_t tBE32K;   /**! 32KB Block Erase Max Time */
        uint32_t tBE64K;   /**! 64KB Block Erase Max Time */
        uint32_t tCE;      /**! Chip Erase Max Time */
        uint32_t tWSR;     /**! Status Register Write Max Time */
        uint32_t tUNKNOWN; /**! Unknown Operation Max Time */
    }timing;
    char name[20];
}MX25xxxYY_Chip_Info_t;

extern MX25xxxYY_Chip_Info_t MX25R6435F_Chip_Def_Low_Power;
extern MX25xxxYY_Chip_Info_t MX25R6435F_Chip_Def_High_Performance;

typedef struct
{
    uint8_t cs_pin;
    uint8_t reset_pin;
    uint8_t wp_pin;
    uint8_t transfer_dummy_byte;
    int state;
    MX25xxxYY_Chip_Info_t *chip_def;
    void* ctx;
} MX25xxxYY_t;

/**
 * MX25xxxYY_init initialized the MX25xxxYY_t structure dev.
 * @param dev the device structure for the MX25xxxYY chip.
 * @param cs_pin The pin number to use for the Slave Select pin
 * @param reset_pin The pin to use for the Reset pin
 * @param transfer_dummy_byte a byte to use as a dummy byte for SPI transfers.
 * @param ctx a void* pointer that can be used by the implementation functions for context specific operations.
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY_init(MX25xxxYY_t *dev, MX25xxxYY_Chip_Info_t *chip_def, uint8_t cs_pin, uint8_t reset_pin, uint8_t wp_pin, uint8_t transfer_dummy_byte, void* ctx);

/**
 * MX25xxxYY_read_identification issues the RDID command to the chip
 * See page 22 and page 25 of the Datasheet
 *
 * @param dev the device structure for the MX25xxxYY chip.
 * @param manufacturer_id
 * @param memory_type
 * @param memory_density
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY_read_identification(MX25xxxYY_t *dev, int *manufacturer_id, int *memory_type, int *memory_density);

/**
 * MX25xxxYY_read_electronic_signature issues the RES command to the chip
 * See page 23 and page 25  of the Datasheet
 *
 * @param dev the device structure for the MX25xxxYY chip.
 * @param electronic_id
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY_read_electronic_signature(MX25xxxYY_t *dev, int *electronic_id);

/**
 * MX25xxxYY_read_manufacture_and_device_id issues the REMS command to the chip.
 * See page 24 and page 25  of the Datasheet
 *
 * @param dev the device structure for the MX25xxxYY chip.
 * @param manufacturer_id
 * @param memory_type
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY_read_manufacture_and_device_id(MX25xxxYY_t *dev, int *manufacturer_id, int *memory_type);

 /**
  * MX25xxxYY_read_status_register
  * @param dev the device structure for the MX25xxxYY chip.
  * @param status_register see datasheet page 30 for data fields
  * @return a MX25xxxYY_status_enum_t indication success or error codes.
  */
 MX25xxxYY_status_enum_t MX25xxxYY_read_status_register(MX25xxxYY_t *dev, uint8_t *status_register);

/**
 * MX25xxxYY_read_configuration_register
 * @param dev the device structure for the MX25xxxYY chip.
 * @param configuration_register see datasheet page 31 for register fields.
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY_read_configuration_register(MX25xxxYY_t *dev, uint16_t *configuration_register);

/**
 *
 * @param dev the device structure for the MX25xxxYY chip.
 * @param status_register the value to write to the status register
 * @param configuration_register the value to write to the configuration register
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY_configure_chip(
        MX25xxxYY_t *dev,
        uint8_t status_register,
        uint16_t configuration_register);


/**
 * MX25xxxYY_set_write_enable
 * @param dev the device structure for the MX25xxxYY chip.
 * @param enable - true to issue WREN false to issue WRDI
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY_set_write_enable(MX25xxxYY_t *dev, bool enable);

/**
 * MX25xxxYY_read_data_bytes reads data from the flash storage.
 * @param dev the device structure for the MX25xxxYY chip.
 * @param use_fast_mode If true the (FAST_READ) command is issued else (READ) command is issued.
 * @param memory_address the 24-bit memory address to read from.
 * @param length the number of bytes to read.
 * @param buffer the buffer in which to store the read data.
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY_read_stored_data(
        MX25xxxYY_t *dev,
        bool use_fast_mode,
        uint32_t memory_address,
        size_t length,
        uint8_t* buffer);

/**
 * MX25xxxYY_write_stored_data stores the specified data at the specified address.
 * @param dev the device structure for the MX25xxxYY chip.
 * @param memory_address
 * @param length
 * @param buffer
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY_write_stored_data(
        MX25xxxYY_t *dev,
        uint32_t memory_address,
        size_t length,
        uint8_t* buffer);

/**
 * MX25xxxYY_erase erases the specified flash area, specified by erase_type ond memory_address
 * @param dev the device structure for the MX25xxxYY chip.
 * @param erase_type the scope of the erasure, a 4KB block, 32KB area, 64KB area or the entire chip.
 * @param memory_address Any address that falls within the specified block will select that block for erasure. Except for Chip Erasure which erases the entire chip.
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY_erase(
        MX25xxxYY_t *dev,
        MX25xxxYY_Erase_enum_t erase_type,
        uint32_t memory_address);

/**
 * MX25xxxYY_get_erasure_size_string converts a MX25xxxYY_Erase_enum_t to a Human Readable String
 * @param size the MX25xxxYY_Erase_enum_t to get the string representation of.
 * @return the string representation of size
 */
const char* MX25xxxYY_get_erasure_size_string(MX25xxxYY_Erase_enum_t size);

/**
 * MX25xxxYY_get_erasure_max_time returns the appropriate value from the MX25xxxYY_t.chip_def timing section for the provided erase_type.
 * @param dev the device structure for the MX25xxxYY chip.
 * @param erase_type the MX25xxxYY_Erase_enum_t type for which to retrieve the timing value of.
 * @return the maximum number of micro-seconds required for the specified erasure operation.
 */
uint32_t MX25xxxYY_get_erasure_max_time(MX25xxxYY_t *dev, MX25xxxYY_Erase_enum_t erase_type);

MX25xxxYY_status_enum_t MX25xxxYY_read_security_register(
        MX25xxxYY_t *dev,
        uint8_t *security_register);

MX25xxxYY_status_enum_t MX25xxxYY_write_security_register(
        MX25xxxYY_t *dev,
        uint8_t *security_register);

// These function implement the platform specific functionality required by this library.
// __attribute__((weak)) implementations of these functions are provided so that this
// library can compile. Any program making use of this library must provide implementations
// of these function that perform the required actions on the specific platform.

/**
 * MX25xxxYY___issue_command write the provided command out on the relevant SPI bus
 * @param dev the device structure for the MX25xxxYY chip.
 * @param command the MX25xxxYY_COMMAND_enum_t to issue.
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY___issue_command(MX25xxxYY_t *dev, MX25xxxYY_COMMAND_enum_t command);

/**
 * MX25xxxYY___read reads length bytes from the relevant SPI bus into buffer
 * @param dev the device structure for the MX25xxxYY chip.
 * @param length the size of the provided buffer
 * @param buffer the buffer to read bytes into
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY___read(MX25xxxYY_t *dev, size_t length, uint8_t* buffer);

/**
 * MX25xxxYY___write writes length bytes from buffer to the relevant SPI bus
 * @param dev the device structure for the MX25xxxYY chip.
 * @param length the size of the provided buffer
 * @param buffer the data to write to the relevant SPI bus
 * @return a MX25xxxYY_status_enum_t indication success or error codes.
 */
MX25xxxYY_status_enum_t MX25xxxYY___write(MX25xxxYY_t *dev, size_t length, uint8_t* buffer);

/**
 * MX25xxxYY___enable_cs_pin asserts the active low CS pin
 * @param dev the device structure for the MX25xxxYY chip.
 * @param value true->RESET-> LOW, false->RESET->HIGH
 */
void                    MX25xxxYY___enable_cs_pin(MX25xxxYY_t *dev, bool value);

/**
 * MX25xxxYY___enable_reset_pin asserts the active low RESET pin
 * @param dev the device structure for the MX25xxxYY chip.
 * @param value true->RESET-> LOW, false->RESET->HIGH
 */
void                    MX25xxxYY___enable_reset_pin(MX25xxxYY_t *dev, bool value);

/**
 * MX25xxxYY___enable_write_protect_pin asserts the active low WP pin
 * @param dev the device structure for the MX25xxxYY chip.
 * @param value true->RESET-> LOW, false->RESET->HIGH
 */
void                    MX25xxxYY___enable_write_protect_pin(MX25xxxYY_t *dev, bool value);

/**
 *  MX25xxxYY___test_linker returns FALSE. A library providing the platform specific implementation functions needs
 *  to provide one for MX25xxxYY___test_linker that returns TRUE. This enables the library to detect if there has
 *  been an issue linking the two libraries together.
 * @param dev the device structure for the MX25xxxYY chip.
 * @return
 */
bool                    MX25xxxYY___test_linker(MX25xxxYY_t *dev);

#if defined(__cplusplus)
}
#endif


#endif //FLASH_MX25XXXYY_H
