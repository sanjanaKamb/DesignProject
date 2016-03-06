package com.example.ece496.ece496;

import android.os.AsyncTask;
import android.util.Log;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;


public  class NetworkSend extends AsyncTask<String, Void, String> {


    Socket socket = null;
    DataOutputStream outToPi = null;
    private static final String TAG = "NetworkSend";
    String serverAddr = "192.168.0.17";
    int portNumber = 5001;




    @Override
    protected String doInBackground(String... params) {
        try {
            socket = new Socket(serverAddr, portNumber);
        }catch(Exception e){
            Log.e(TAG, "" + e.getMessage());
        }
        PointsList.getInstance().socket = socket;

        try{
            outToPi = new DataOutputStream(socket.getOutputStream());
        }catch (IOException e) {
            Log.e(TAG, e.getMessage());
        }


        while(true){
            if(PointsList.getInstance().points.size()>0){
               Point point = PointsList.getInstance().points.remove();
                Log.d(TAG, "point: " + point.toString());
                try{
                    outToPi.writeBytes(point.toString()+"\n");
                }catch (IOException e) {
                    Log.d(TAG, e.getMessage());
                }
            }

        }

    }


}