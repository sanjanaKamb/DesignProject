package com.example.ece496.ece496;

import java.net.Socket;
import java.util.LinkedList;
import java.util.Queue;


 public class PointsList {
    private static PointsList instance = null;


    public Queue<Point> points = new LinkedList<Point>();
    private static final String TAG = "PointsList";
    Socket socket;

    private PointsList(){

    }

    public static PointsList getInstance(){
        if(instance==null){
            instance = new PointsList();

        }
        return instance;
    }
}
