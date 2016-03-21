package com.example.ece496.ece496;

import android.annotation.TargetApi;
import android.app.Activity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.ViewGroup;
import android.widget.ImageView;

import org.opencv.android.OpenCVLoader;
import org.opencv.android.Utils;
import org.opencv.core.Mat;
import org.opencv.core.MatOfByte;
import org.opencv.imgcodecs.Imgcodecs;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Arrays;
import java.util.Date;
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class MainActivity extends Activity {

    static {
        if (!OpenCVLoader.initDebug()) {
            // Handle initialization error
        }
    }
    // Log tag
    private static final String TAG = MainActivity.class.getName();

    int l =0;
    DrawView drawView;
    Queue<Bitmap> bitmapsQ = new LinkedList<Bitmap>();
    Lock queue = new ReentrantLock();
    boolean createNotification = false;


    @TargetApi(Build.VERSION_CODES.HONEYCOMB) // API 11
    void startMyTask(AsyncTask asyncTask) {
        Void[] param = null;
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB)
            asyncTask.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, param);
        else
            asyncTask.execute(param);
    }



    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //play video on TextureView
        setContentView(R.layout.activity_main);


        //start network threads
        startMyTask(new NetworkSend());
        startMyTask(new NetworkListen());
        Log.e(TAG, "Started 2 threads");

        ImageView iv = (ImageView) findViewById(R.id.imageView1);
        final Intent resultIntent = new Intent(this, MainActivity.class);
        resultIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP|Intent.FLAG_ACTIVITY_SINGLE_TOP);
        final PendingIntent resultPendingIntent =PendingIntent.getActivity(this, 0, resultIntent, 0);
        long when = System.currentTimeMillis(); //now
        final Notification notification = new Notification(R.drawable.notification_template_icon_bg,"Object of interest has moved",when);
        notification.setLatestEventInfo(this,"Object of interest has moved","Press to view camera feed",resultPendingIntent);

            //Get image from bitmap and display on screen
            iv.post(new Runnable() {
                ImageView iv = (ImageView) findViewById(R.id.imageView1);

                @Override
                public void run() {

                    if(createNotification){

                        notification.flags|=Notification.FLAG_AUTO_CANCEL;
                        NotificationManager mNotificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

                        // notificationID allows you to update the notification later on.
                        mNotificationManager.notify(0, notification);

                        createNotification = false;
                    }

                    if (!bitmapsQ.isEmpty()) {
                        Bitmap getBm = bitmapsQ.remove();

                        iv.setImageBitmap(getBm);
                        Date date = new Date();
                        Log.e(TAG, "height: " + getBm.getHeight() + " width: " + getBm.getWidth());
                        Log.e(TAG, "TIME: " + date.toString());

                    }
                    iv.postDelayed(this, 1000);

                }
            });

        //add drawView to layout
        ViewGroup mainView = (ViewGroup) findViewById(R.id.rootView);
        drawView = new DrawView(this);

        drawView.requestFocus();
        mainView.addView(drawView);
    }


    public class NetworkListen extends AsyncTask<String, Void, String> {

        @Override
        protected String doInBackground(String... params) {


            BufferedReader br = null;
            PrintWriter pw = null;
            InputStream is = null;
            Socket socket;
            Log.e(TAG, "In NetworkListen");
            try{
                while((socket = PointsList.getInstance().socket)==null){

                }
                Log.e(TAG, "Exit loop");

                is = socket.getInputStream();

                byte[] data = new byte[1300000];
                byte[] finalArr= new byte[0];
                int count = is.read(data);
                boolean first = false;
                boolean getSize = true;
                int total = 0;
                byte[] data2 = null;

                while(count>0){
                    Log.e(TAG,"count: "+count);
                    data2 = Arrays.copyOfRange(data,0,count);
                    if(new String(data2).contains("notification")){
                        createNotification=true;
                        Log.e(TAG,"NOTIFICATION: "+new String(data2));
                        count = is.read(data);
                        continue;
                    }
                    Log.e(TAG,"recvData: "+new String(data2));

                    //first received bytes are length of the image
                    if(getSize){
                        first = true;
                        try {
                            total = Integer.parseInt(new String(data2));

                            //Catch exception if image size comes with the image data. Separate them
                        }catch (NumberFormatException ex){
                            Pattern pat = Pattern.compile("([0-9]+)");
                            Matcher m = pat.matcher(new String(data2));
                            m.find();
                            String integers = m.group(1);
                            total = Integer.parseInt(integers);
                            total -= (count - integers.length());
                            data2 = Arrays.copyOfRange(data,2+integers.length(),count);
                            byte[] temp = new byte[finalArr.length+data2.length];
                            System.arraycopy(finalArr,0,temp,0,finalArr.length);
                            System.arraycopy(data2,0,temp,finalArr.length,data2.length);
                            finalArr = temp;
                            first = false;

                            Log.e(TAG, "INTEGERS: "+integers);
                            Log.e(TAG, "RESTlength: "+finalArr.length);
                            Log.e(TAG, "REST: "+finalArr);
                        }
                        count = is.read(data);
                        getSize = false;

                        continue;
                    }
                    total-=count;

                    //remove first 2 characters /r/n for carriage return from image bytes
                    if(first){
                        data2 = Arrays.copyOfRange(data,2,count);
                        first = false;
                    }

                    //accumulate image bytes in finalArr
                    byte[] temp = new byte[finalArr.length+data2.length];
                    System.arraycopy(finalArr,0,temp,0,finalArr.length);
                    System.arraycopy(data2,0,temp,finalArr.length,data2.length);
                    finalArr = temp;
                    Log.e(TAG, "finalArr: "+finalArr.length);

                    //Once all image bytes are received, add to bitmap queue
                    if(total<1){
                        getSize = true;

                        Mat decodedImg = Imgcodecs.imdecode(new MatOfByte(finalArr), Imgcodecs.IMREAD_UNCHANGED);
                        Log.e(TAG, "height: "+decodedImg.size().height+ " columns: "+decodedImg.size().width);

                        Bitmap bm = Bitmap.createBitmap(decodedImg.cols(), decodedImg.rows(),Bitmap.Config.ARGB_8888);
                        Utils.matToBitmap(decodedImg, bm);

                       bitmapsQ.add(bm);

                        //save image to disk
                        //SaveImage(decodedImg);
                        Log.e(TAG, "wrote to file");
                        finalArr= new byte[0];

                    }

                    count = is.read(data);
                }

                br.close();
                pw.close();
                socket.close();
            } catch (IOException e) {
                Log.d(TAG, e.getMessage());
            }
        return "";
        }




        public void SaveImage (Mat mat) {

            File path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);
            String filename = "THISISAFILENAME"+l+".png";
            l++;
            File file = new File(path, filename);

            Boolean bool = null;
            filename = file.toString();
            bool = Imgcodecs.imwrite(filename, mat);

            if (bool == true)
                Log.e(TAG, "SUCCESS writing image to external storage "+filename);
            else
                Log.e(TAG, "Fail writing image to external storage "+filename);
        }


    }
}

