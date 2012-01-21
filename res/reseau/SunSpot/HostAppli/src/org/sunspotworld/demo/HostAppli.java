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
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.sql.Timestamp;
import javax.microedition.io.Connector;
import javax.microedition.io.Datagram;


/**
 * Sample Sun SPOT host application
 */
public class HostAppli {

    private static final int HOST_PORT = 50;
    
    private static final int SOCKET_PORT = 8080;

    
    /**
     * Print out our radio address.
     */
    public void run() {
        
        Socket socket = null;
        /*
        long ourAddr =  RadioFactory.getRadioPolicyManager().getIEEEAddress();
        System.out.println("Our radio address = " + IEEEAddress.toDottedHex(ourAddr));
        */
        
        // On ouvre la connection en reception :
        RadiogramConnection recConn = null;
        // Trame reçue :
        Datagram dg = null;
        
        try {
            recConn = (RadiogramConnection) Connector.open("radiogram://:" + HOST_PORT);
            dg = recConn.newDatagram(recConn.getMaximumLength());
            
            // Connexion au serveur pour l'envoie des donnees:
            socket = new Socket("127.0.0.1", SOCKET_PORT);
        } catch (Exception e) {
            System.err.println("Erreur " + e + " lors de l'initialisation");
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
                
                
                System.out.println("["+ address +"] time: " + nowTime +" temp: "+ temperature + " ;accel: "+ accel+ " ;light: "+ light);
                
                // On envoie les donnees à l'adresse :
                PrintWriter pred = new PrintWriter(
                         new BufferedWriter(
                            new OutputStreamWriter(socket.getOutputStream())),
                         true);
                
                pred.print(address);
                pred.print("|");
                pred.print(nowTime);
                pred.print("|");
                pred.print(temperature);
                pred.print("|");
                pred.print(accel);
                pred.print("|");
                pred.println(light);
                
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
