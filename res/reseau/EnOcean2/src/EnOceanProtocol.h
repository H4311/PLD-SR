/*
 Copyright 2008 Daniel Lechner, Andreas Dielacher
 see COPYING and COPYING.LESSER file for details.
*/
#ifndef ENOCEANPROTOCOL_H_
#define ENOCEANPROTOCOL_H_

#include <stdint.h>

/// the main "type" for datatransfer
#define BYTE uint8_t

/**
 * @defgroup structs Data structures
 * The definitions of the EnOcean data-structures
 * @{
 */
/**
 * \brief The default structure for EnOcean packets
 *
 * Data structure for RPS, 1BS, 4BS and HRC packages
 * Since most of the packages are in this format, this
 * is taken as default. Packages of other structure have
 * to be converted with the appropirate functions.
 **/
typedef struct enocean_data_structure {
  BYTE SYNC_BYTE1; ///< Synchronisation Byte 1
  BYTE SYNC_BYTE2; ///< Synchronisation Byte 2
  BYTE H_SEQ_LENGTH; ///< Header identification and number of octets following the header octet
  BYTE ORG; ///< Type of telegram
  BYTE DATA_BYTE3; ///< Data Byte 3
  BYTE DATA_BYTE2; ///< Data Byte 2
  BYTE DATA_BYTE1; ///< Data Byte 1
  BYTE DATA_BYTE0; ///< Data Byte 0
  BYTE ID_BYTE3; ///< Transmitter ID Byte 3
  BYTE ID_BYTE2; ///< Transmitter ID Byte 2
  BYTE ID_BYTE1; ///< Transmitter ID Byte 1
  BYTE ID_BYTE0; ///< Transmitter ID Byte 0
  BYTE STATUS; ///< Status field
  BYTE CHECKSUM; ///< Checksum of the packet
} enocean_data_structure;

/// 6DT Package structure
/** Data structure for 6DT packages
 **/
typedef struct enocean_data_structure_6DT {
  BYTE SYNC_BYTE1; ///< Synchronisation Byte 1
  BYTE SYNC_BYTE2; ///< Synchronisation Byte 2
  BYTE H_SEQ_LENGTH; ///< Header identification and number of octets following the header octet
  BYTE ORG; ///< Type of telegram
  BYTE DATA_BYTE5; ///< Data Byte 5
  BYTE DATA_BYTE4; ///< Data Byte 4
  BYTE DATA_BYTE3; ///< Data Byte 3
  BYTE DATA_BYTE2; ///< Data Byte 2
  BYTE DATA_BYTE1; ///< Data Byte 1
  BYTE DATA_BYTE0; ///< Data Byte 0
  BYTE ADDRESS1; ///< Adress Byte 1
  BYTE ADDRESS0; ///< Adress Byte 0
  BYTE STATUS; ///< Status field
  BYTE CHECKSUM; ///< Checksum of the packet
} enocean_data_structure_6DT;

/// MDA Package structure
/** Data structure for MDA packages
 **/
typedef struct enocean_data_structure_MDA {
  BYTE SYNC_BYTE1; ///< Synchronisation Byte 1
  BYTE SYNC_BYTE2; ///< Synchronisation Byte 2
  BYTE H_SEQ_LENGTH; ///< Header identification and number of octets following the header octet
  BYTE ORG; ///< Type of telegram
  BYTE DATA_UNUSED5; ///< Data Byte 5 (unused)
  BYTE DATA_UNUSED4; ///< Data Byte 4 (unused)
  BYTE DATA_UNUSED3; ///< Data Byte 3 (unused)
  BYTE DATA_UNUSED2; ///< Data Byte 2 (unused)
  BYTE ADDRESS1; ///< Adress Byte 1
  BYTE ADDRESS0; ///< Adress Byte 0
  BYTE DATA_UNUSED1; ///< Data Byte 1 (unused)
  BYTE DATA_UNUSED0; ///< Data Byte 0 (unused)
  BYTE STATUS; ///< Status field
  BYTE CHECKSUM; ///< Checksum of the packet
} enocean_data_structure_MDA;
/*@}*/

/**
 * @defgroup sync Sync fields
 * The definitions for the sync-bytes
 * @{
 */
/**
 * \brief 1st synchronization byte
 *
 * The first synchronization byte. It is always 0xA5
 */
#define C_S_BYTE1 0xA5
/**
 * \brief 2nd synchronization byte
 *
 * The second synchronization byte. It is always 0x5A
 */
#define C_S_BYTE2 0x5A
/*@}*/
/**
 * @defgroup h_seq Header identification
 * The definitions for the header identification. This field is contained
 * contains the highest 3 bits of the H_SEQ_LENGTH byte.
 * @{
 */
/**
 * \brief RRT
 *
 * Header identification says receive radio telegram (RRT)
 */
#define C_H_SEQ_RRT 0x00
/**
 * \brief TRT
 *
 * Header identification says transmit radio telegram (TRT)
 */
#define C_H_SEQ_TRT 0x60
/**
 * \brief RMT
 *
 * Header identification says receive message telegram (RMT)
 */
#define C_H_SEQ_RMT 0x80
/**
 * \brief TCT
 *
 * Header identification says transmit command telegram (TCT)
 */
#define C_H_SEQ_TCT 0xA0
/**
 * \brief OK
 *
 * Standard message to confirm that an action was performed correctly by the TCM
 */
#define H_SEQ_OK 0x80
/**
 * \brief ERR
 *
 * Standard error message response if an action was not performed correctly by the TCM
 */
#define H_SEQ_ERR 0x80
/*@}*/

/**
 * @defgroup length Length byte
 * Number of octets following the header octed.
 * Is contained in the last 5 bits of the H_SEQ_LENGTH byte.
 * @{
 */
/**
 * \brief Fixed length
 *
 * Every packet has the same length: 0x0B
 */
#define C_LENGTH 0x0B
/*@}*/

/**
 * @defgroup org Type of telegram
 * Type definition of the telegram.
 * @{
 */
/**
 * \brief PTM telegram
 *
 * Telegram from a PTM switch module received (original or repeated message)
 */
#define C_ORG_RPS 0x05
/**
 * \brief 1 byte data telegram
 *
 * Detailled 1 byte data telegram from a STM sensor module received (original or repeated message)
 */
#define C_ORG_1BS 0x06
/**
 * \brief 4 byte data telegram
 *
 * Detailled 4 byte data telegram from a STM sensor module received (original or repeated message)
 */
#define C_ORG_4BS 0x07
/**
 * \brief CTM telegram
 *
 * Telegram from a CTM module received (original or repeated message)
 */
#define C_ORG_HRC 0x08
/**
 * \brief Modem telegram
 *
 * 6byte Modem Telegram (original or repeated)
 */
#define C_ORG_6DT 0x0A
/**
 * \brief Modem ack
 *
 * Modem Acknowledge Telegram
 */
#define C_ORG_MDA 0x0B
/*@}*/


/**
 * \brief ID-range telegram
 *
 * When this command is sent to the TCM, the base ID range number is retrieved though an INF_IDBASE telegram.
 */
#define C_ORG_RD_IDBASE 0x58



/**
 * @defgroup bitmasks Bitmasks for various fields.
 * There are two definitions for every bit mask. First, the bit mask itself
 * and also the number of necessary shifts.
 * @{
 */
/**
 * @defgroup status_rps Status of telegram (for RPS telegrams)
 * Bitmasks for the status-field, if ORG = RPS.
 * @{
 */
#define S_RPS_T21 0x20
#define S_RPS_T21_SHIFT 5
#define S_RPS_NU  0x10
#define S_RPS_NU_SHIFT 4
#define S_RPS_RPC 0x0F
#define S_RPS_RPC_SHIFT 0
/*@}*/
/**
 * @defgroup status_rpc Status of telegram (for 1BS, 4BS, HRC or 6DT telegrams)
 * Bitmasks for the status-field, if ORG = 1BS, 4BS, HRC or 6DT.
 * @{
 */
#define S_RPC 0x0F
#define S_RPC_SHIFT 0
/*@}*/

/**
 * @defgroup data3 Meaning of data_byte 3 (for RPS telegrams, NU = 1)
 * Bitmasks for the data_byte3-field, if ORG = RPS and NU = 1.
 * @{
 */
#define DB3_RPS_NU_RID 0xC0
#define DB3_RPS_NU_RID_SHIFT 6
#define DB3_RPS_NU_UD  0x20
#define DB3_RPS_NU_UD_SHIFT 5
#define DB3_RPS_NU_PR  0x10
#define DB3_RPS_NU_PR_SHIFT 4
#define DB3_RPS_NU_SRID 0x0C
#define DB3_RPS_NU_SRID_SHIFT 2
#define DB3_RPS_NU_SUD 0x02
#define DB3_RPS_NU_SUD_SHIFT 1
#define DB3_RPS_NU_SA 0x01
#define DB3_RPS_NU_SA_SHIFT 0
/*@}*/

/**
 * @defgroup data3_1 Meaning of data_byte 3 (for RPS telegrams, NU = 0)
 * Bitmasks for the data_byte3-field, if ORG = RPS and NU = 0.
 * @{
 */
#define DB3_RPS_BUTTONS 0xE0
#define DB3_RPS_BUTTONS_SHIFT 4
#define DB3_RPS_PR 0x10
#define DB3_RPS_PR_SHIFT 3
/*@}*/

/**
 * @defgroup data0 Meaning of data_byte 0 (for 4BS telegrams)
 * Bitmasks for the data_byte0-field, if ORG = 4BS.
 * @{
 */
#define DB0_4BS_DI_3 0x08
#define DB0_4BS_DI_3_SHIFT 3
#define DB0_4BS_DI_2 0x04
#define DB0_4BS_DI_2_SHIFT 2
#define DB0_4BS_DI_1 0x02
#define DB0_4BS_DI_1_SHIFT 1
#define DB0_4BS_DI_0 0x01
#define DB0_4BS_DI_0_SHIFT 0
/*@}*/

/**
 * @defgroup data3_hrc Meaning of data_byte 3 (for HRC telegrams)
 * Bitmasks for the data_byte3-field, if ORG = HRC.
 * @{
 */
#define DB3_HRC_RID 0xC0
#define DB3_HRC_RID_SHIFT 6
#define DB3_HRC_UD  0x20
#define DB3_HRC_UD_SHIFT 5
#define DB3_HRC_PR  0x10
#define DB3_HRC_PR_SHIFT 4
#define DB3_HRC_SR  0x08
#define DB3_HRC_SR_SHIFT 3
/*@}*/
/*@}*/

#endif /*ENOCEANPROTOCOL_H_*/
