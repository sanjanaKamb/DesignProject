package com.example.ece496.ece496;

import android.app.Activity;
import android.content.res.AssetFileDescriptor;
import android.graphics.Bitmap;
import android.graphics.SurfaceTexture;
import android.media.MediaPlayer;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Surface;
import android.view.TextureView;
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
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class MainActivity extends Activity  implements TextureView.SurfaceTextureListener{

    static {
        if (!OpenCVLoader.initDebug()) {
            // Handle initialization error
        }
    }
    // Log tag
    private static final String TAG = MainActivity.class.getName();

    // MediaPlayer instance to control playback of video file.
    private MediaPlayer mMediaPlayer;
    private TextureView mTextureView;
    int l =0;
    DrawView drawView;
    Queue<Bitmap> bitmapsQ = new LinkedList<Bitmap>();
    Lock queue = new ReentrantLock();





    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //play video on TextureView
        setContentView(R.layout.activity_main);


        //start network threads
      new NetworkSend().execute("");
      //new NetworkListen().execute("");


        ImageView iv = (ImageView) findViewById(R.id.imageView1);

            //Get image from bitmap and display on screen
            iv.post(new Runnable() {
                ImageView iv = (ImageView) findViewById(R.id.imageView1);

                @Override
                public void run() {

                    if (!bitmapsQ.isEmpty()) {
                        Bitmap getBm = bitmapsQ.remove();

                        iv.setImageBitmap(getBm);
                        Log.e(TAG, "height: " + getBm.getHeight() + " width: " + getBm.getWidth());

                    }
                    iv.postDelayed(this, 1000);

                }
            });

       // initView();

        //add drawView to layout
        ViewGroup mainView = (ViewGroup) findViewById(R.id.rootView);
        drawView = new DrawView(this);

        drawView.requestFocus();
        mainView.addView(drawView);
    }

    private void initView() {
       // mTextureView = (TextureView) findViewById(R.id.textureView);
        // SurfaceTexture is available only after the TextureView
        // is attached to a window and onAttachedToWindow() has been invoked.
        // We need to use SurfaceTextureListener to be notified when the SurfaceTexture
        // becomes available.
        //mTextureView.setSurfaceTextureListener(this);

    }




    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (mMediaPlayer != null) {
            // Make sure we stop video and release resources when activity is destroyed.
            mMediaPlayer.stop();
            mMediaPlayer.release();
            mMediaPlayer = null;
        }
    }

    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surfaceTexture, int i, int i2) {
        Surface surface = new Surface(surfaceTexture);

        try {
            AssetFileDescriptor afd = getResources().openRawResourceFd(R.raw.video);
                    //getAssets().openFd(FILE_NAME);
            mMediaPlayer = new MediaPlayer();
           /* mMediaPlayer
                    .setDataSource("https://archive.org/download/ksnn_compilation_master_the_internet/ksnn_compilation_master_the_internet_512kb.mp4");
           */
            mMediaPlayer.setDataSource(afd.getFileDescriptor(), afd.getStartOffset(), afd.getLength());
            mMediaPlayer.setSurface(surface);
            mMediaPlayer.setLooping(true);


            // don't forget to call MediaPlayer.prepareAsync() method when you use constructor for
            // creating MediaPlayer
            mMediaPlayer.prepareAsync();

            // Play video when the media source is ready for playback.
            mMediaPlayer.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
                @Override
                public void onPrepared(MediaPlayer mediaPlayer) {
                    mediaPlayer.start();
                }
            });

        } catch (IllegalArgumentException e) {
            Log.d(TAG, e.getMessage());
        } catch (SecurityException e) {
            Log.d(TAG, e.getMessage());
        } catch (IllegalStateException e) {
            Log.d(TAG, e.getMessage());
        } catch (IOException e) {
            Log.d(TAG, e.getMessage());
        }
    }

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surfaceTexture, int i, int i2) {
    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surfaceTexture) {
        return true;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surfaceTexture) {
    }



    private class NetworkListen extends AsyncTask<String, Void, String> {

        @Override
        protected String doInBackground(String... params) {


            BufferedReader br = null;
            PrintWriter pw = null;
            InputStream is = null;
            Socket socket;
            Log.e(TAG, "starting");
            try{
                while((socket = PointsList.getInstance().socket)==null){

                }


                is = socket.getInputStream();

                Log.e(TAG, "here");
                byte[] data = new byte[1300000];
                byte[] finalArr= new byte[0];
                int count = is.read(data);
                boolean first = false;
                boolean getSize = true;
                int total = 0;


                while(count>0){
                    Log.e(TAG,"count: "+count);
                    byte[] data2 = Arrays.copyOfRange(data,0,count);
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
                     //   SaveImage(decodedImg);
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

        @Override
        protected void onPostExecute(String result) {
            Log.d(TAG, "Execute");
            // might want to change "executed" for the returned string passed
            // into onPostExecute() but that is upto you
        }

        @Override
        protected void onPreExecute() {}

        @Override
        protected void onProgressUpdate(Void... values) {}
    }
}

//Extra code


 /*    Bitmap bmp = BitmapFactory.decodeByteArray(receivedBytes, 0, receivedBytes.length);
                    Mat imgMat = new Mat(bmp.getHeight(),bmp.getWidth(), CvType.CV_8UC3);
                    Bitmap myBitmap32 = bmp.copy(Bitmap.Config.ARGB_8888, true);
                    Utils.bitmapToMat(myBitmap32, imgMat);
                    Imgproc.cvtColor(imgMat, imgMat, Imgproc.COLOR_BGR2RGB, 4);*/


  /*  int rows = 960;
                    int cols = 1280;
                    Mat imgMat=Mat.zeros(rows, cols, CvType.CV_8UC3);


                    byte[][] modifiedBytes = new byte[receivedBytes.length/3][3];
                    int j =0;
                    for (int i = 0; i < receivedBytes.length; i+=3){
                       try {
                           modifiedBytes[j][0] = receivedBytes[i + 0];
                           modifiedBytes[j][1] = receivedBytes[i + 1];
                           modifiedBytes[j][2] = receivedBytes[i + 2];
                           j++;
                       }catch(ArrayIndexOutOfBoundsException e){
                           Log.e(TAG,e.getMessage());
                       }
                    }

                    int ptr=0;
                    for(int i=0; i < rows; i++){
                        for(int k =0; k<cols; k++){
                            try{imgMat.put(i,k,modifiedBytes[ptr]);}
                            catch(ArrayIndexOutOfBoundsException e){
                                Log.e(TAG,e.getMessage());
                            }
                            ptr++;
                        }
                    }
*/