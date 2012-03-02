/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.sunspotworld.demo;

/**
 * Structure de donnees permettant de formaliser les trames sunSpot
 * @author Daniel
 */
public class SunSpotProtocol {
    
  public char[] tabChar = new char[14];
  
  public static final int SYNC_BYTE1 = 0; ///< Synchronisation Byte 1
  public static final int  SYNC_BYTE2 = 1; ///< Synchronisation Byte 2
  public static final int  H_SEQ_LENGTH = 2; ///< Header identification and number of octets following the header octet
  public static final int  ORG = 3; ///< Type of telegram
  public static final int  DATA_BYTE3 = 4; ///< Data Byte 3
  public static final int  DATA_BYTE2 = 5; ///< Data Byte 2
  public static final int  DATA_BYTE1 = 6; ///< Data Byte 1
  public static final int  DATA_BYTE0 = 7; ///< Data Byte 0
  public static final int  ID_BYTE3 = 8; ///< Transmitter ID Byte 3
  public static final int  ID_BYTE2 = 9; ///< Transmitter ID Byte 2
  public static final int  ID_BYTE1 = 10; ///< Transmitter ID Byte 1
  public static final int  ID_BYTE0 = 11; ///< Transmitter ID Byte 0
  public static final int  STATUS = 12; ///< Status field
  public static final int  CHECKSUM = 13; ///< Checksum of the packet
 
  
  
}
