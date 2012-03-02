/*
 * Copyright (c) 2006-2010 Sun Microsystems, Inc.
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package org.sunspotworld.demo;

import com.sun.spot.io.j2me.radiogram.RadiogramConnection;
import com.sun.spot.peripheral.radio.RadioFactory;
import com.sun.spot.util.IEEEAddress;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Timestamp;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.microedition.io.Connector;
import javax.microedition.io.Datagram;


/**
 * Sample Sun SPOT host application
 */
public class HostAppli {

    private static final int HOST_PORT = 50;
    
    private static final int SOCKET_PORT = 7080;
    
    private static final int FRAME_SIZE = 14;
    
    char fromHexToChar (int hex) {
        if (hex <= 9) {
            return (char)('0'+ hex); }
        else { return (char)('A'+(hex-10)); }
    }
    
    /**
     * toString
     */
    public void toString(SunSpotProtocol frame, char[] buffer) {
        int temp;
        char c;
        for (int i = 0; i < FRAME_SIZE; i++) {
            temp = frame.tabChar[i];
            if (temp < 0) { temp = 255 - temp; }
            temp = frame.tabChar[i] & 15;
            c = fromHexToChar(temp);
            buffer[2*i+1] = c;
            temp = frame.tabChar[i] >> 4;
            c = fromHexToChar(temp);
            buffer[2*i] = c;
        }
    }
    
    /**
     * setId
     */
    public void setId(SunSpotProtocol frame, int id){
       frame.tabChar[SunSpotProtocol.ID_BYTE0] = (char)(id & 255);
       id = id >> 8;
       System.out.println(id);
       frame.tabChar[SunSpotProtocol.ID_BYTE1] = (char)(id & 255);
       id = id >> 8;
       System.out.println(id);
       frame.tabChar[SunSpotProtocol.ID_BYTE2] = (char)(id & 255);
       id = id >> 8;
       System.out.println(id);
       frame.tabChar[SunSpotProtocol.ID_BYTE3] = (char)(id & 255);
    }
    
    /**
     * setTemperature
     */
    public void setTemperature(SunSpotProtocol frame, double temp, double minTemp, double maxTemp) {
        double multiplyer = (double)(maxTemp-minTemp) / 255.0;
        frame.tabChar[SunSpotProtocol.DATA_BYTE1] = (char)((temp - (double)( (multiplyer>=0)? minTemp : maxTemp )) / multiplyer);
    } //----- End of setTemperature

    /**
     * setIlluminance
     */
    public void setIlluminance(SunSpotProtocol frame, double val, double minL, double maxL) {
        double multiplyer = (double)(maxL-minL) / 255.0;
        frame.tabChar[SunSpotProtocol.DATA_BYTE2] = (char)((val - (double)( (multiplyer>=0)? minL : maxL )) / multiplyer);
    } //----- End of setIlluminance
    
    /**
     * setIlluminance
     */
    public void setAccelerometre(SunSpotProtocol frame, double val, double minL, double maxL) {
        double multiplyer = (double)(maxL-minL) / 255.0;
        frame.tabChar[SunSpotProtocol.DATA_BYTE3] = (char)((val - (double)( (multiplyer>=0)? minL : maxL )) / multiplyer);
    } //----- End of setAccelerometre
    
    
    /*
     * fillByte
     */
    public void fillByte(SunSpotProtocol frame){
        frame.tabChar[SunSpotProtocol.SYNC_BYTE1] = 0xA5;
        frame.tabChar[SunSpotProtocol.SYNC_BYTE2] = 0x5A;
        frame.tabChar[SunSpotProtocol.H_SEQ_LENGTH] = 0x0B;
        frame.tabChar[SunSpotProtocol.ORG] = 0xA5;
    }
    
    /*
     * setCheckSum
     */
    public void setCheckSum(SunSpotProtocol frame){
        int sum = 0;
        for(int i = 0; i<13; i++){
            sum += frame.tabChar[i];
        }
        sum = sum & 255;
        frame.tabChar[SunSpotProtocol.CHECKSUM] = (char)sum;
        return;
    }
    
    
    /**
     * Print out our radio address.
     */
    public void run() {
        
        ServerSocket serverSocket = null;
        
        SunSpotProtocol frame = new SunSpotProtocol();
        char[] buffer = new char[2*FRAME_SIZE];
        
        // On ouvre la connection en reception :
        RadiogramConnection recConn = null;
        // Trame reçue :
        Datagram dg = null;
        
        try {
            recConn = (RadiogramConnection) Connector.open("radiogram://:" + HOST_PORT);
            dg = recConn.newDatagram(recConn.getMaximumLength());
            
            // Creation d'un serveur socket pour l'envoie des données
            serverSocket = new ServerSocket(SOCKET_PORT);
            System.out.println("Server On");
        } catch (Exception e) {
            System.err.println("Erreur " + e + " lors de l'initialisation");
        }
        
        //On attend une connexion
        Socket socket = null ;
        try {
            socket = serverSocket.accept();
        } catch (IOException ex) {
            Logger.getLogger(HostAppli.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        while (true) {
            try {
                // On recupere le message 
                recConn.receive(dg);
                
                // On recupere les donnees souhaitees :
                String address = dg.getAddress();
                
                Long nowTime = dg.readLong(); // Time en millisecondes
                Double light = dg.readDouble();
                Double temperature = dg.readDouble();
                Double accel = dg.readDouble();
                
                
                System.out.println("["+ address +"] time: " + nowTime
                        +" temp: "+ temperature + " ;accel: "+ accel
                        + " ;light: "+ light);
                
                // On formatte l'adress en Id conforme
                String[] addressSplited = address.split("\\.");
                String stringId = addressSplited[3];
                System.out.println("Id parseInt : "+ stringId);
                setId(frame, (int)Integer.parseInt(stringId,16));
                
                // On admet empiriquement que l'acceleration est comprise entre 0 et 10:
                setTemperature(frame, temperature, -40, 60);
                System.out.println("Data Temperature : "+ (int) frame.tabChar[SunSpotProtocol.DATA_BYTE1]);
                
                // On admet empiriquement que l'acceleration est comprise entre 0 et 10:
                setIlluminance(frame, light, 0, 750);
                System.out.println("Data Illuminance : "+ (int) frame.tabChar[SunSpotProtocol.DATA_BYTE2]);
                
                // On admet empiriquement que l'acceleration est comprise entre 0 et 10:
                setAccelerometre(frame, accel, 0, 10);
                System.out.println("Data accelerometre : "+ (int) frame.tabChar[SunSpotProtocol.DATA_BYTE3]);
                
                fillByte(frame);
                
                //Verification de trame:
                setCheckSum(frame);
                
                toString(frame, buffer);
                System.out.println("Msg ToSend "+ String.valueOf(buffer));
                
                
                // On envoie les donnees à l'adresse :
                PrintWriter pred = new PrintWriter(
                         new BufferedWriter(
                            new OutputStreamWriter(socket.getOutputStream())),
                         true);
                
                pred.println(buffer);
                // On vide le message (au cas ou)
                dg.reset();
                
            } catch (Exception e) {
                System.err.println("Erreur " + e + " pendant la reception de donnees");
            }
        }
    }

    /**
     * Start up the host application.
     *
     * @param args any command line arguments
     */
    public static void main(String[] args) throws Exception {
        HostAppli app = new HostAppli();
        app.run();
        System.exit(0);
    }

}
