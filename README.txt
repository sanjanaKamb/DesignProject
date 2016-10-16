Read 'Final Project Report' for the detailed design and implementation of the application.
Read 'Quick Overview' for a brief powerpoint presentation of the project.

Current security monitoring systems available on the market rely heavily on human attention. A simple example of this can be found in security rooms with a single security guard tasked with monitoring several dozens of camera feeds at once. If the guard were to fall asleep or simply leave the room, there would be serious security implications. The goal of our ECE496 project is to develop software for a semi-autonomous security monitoring system to reduce the risk of human error while finding a good balance between machine and human.

Ultimately, this proposed system must be able to detect and outline objects in motion (i.e. objects of interest) and allow users to select and de-select their own objects. Once detected, these objects must be tracked and users must be notified of potential security threats in real-time. In this case, potential threats are assumed to be objects of interest entering within close proximity to each other.

The final application employed the use of a Raspberry Pi and a RaspiCam to remotely stream and process the video feed. This backend system would be in charge of filtering, detecting and tracking objects of interest and alerting a remote user on his/her Android mobile application over WiFi. Alerts would only be generated if these objects came in proximity of each other. In this way, the monitoring system would only require the user’s attention for short periods of time.

Upon completion, several of the team’s objectives were met, which included the ability to select and outline objects of interest, and notify users of movement within 7 seconds of receiving the image. Although communication speeds were subpar, achieving only 0.2 frames per second, the team deemed this an area for improvement for future work as it did not significantly hinder the project’s overall success.

1) Objects in a controlled location image outlined by the canny edge detection on the raspberry pi, seen against the original image
![alt tag](Picture1.jpg)
![alt tag](https://github.com/sanjanaKamb/DesignProject/blob/master/Picture2.jpg)
2) Screenshots of the video feed from Raspberry Pi with different objects clearly outlined 
![alt tag](https://github.com/sanjanaKamb/DesignProject/blob/master/Picture3.png)
![alt tag](https://github.com/sanjanaKamb/DesignProject/blob/master/Picture4.png)
3) The above screenshot compared with a regular photo of the same location
![alt tag](https://github.com/sanjanaKamb/DesignProject/blob/master/Picture5.png)
![alt tag](https://github.com/sanjanaKamb/DesignProject/blob/master/Picture6.jpg)
4) Screenshots of camera feed from Raspberry Pi being streamed on Android application at 0.2fps, where the user can select an object by touching
![alt tag](https://github.com/sanjanaKamb/DesignProject/blob/master/Picture8.png)
![alt tag](https://github.com/sanjanaKamb/DesignProject/blob/master/Picture9.png)
5) Point Coordinates of the touches on the Android app received by the C++ backend listening.
![alt tag](https://github.com/sanjanaKamb/DesignProject/blob/master/Picture7.png)
6) Notification appears on notification bar of user’s phone, when triggered by backend.
![alt tag](https://github.com/sanjanaKamb/DesignProject/blob/master/Picture10.png)
7) End to end delay between backend and frontend is 7 seconds such that when a selected object moves, the user is sent a notification within 10 seconds

- Below is a timestamp from the Raspberry Pi of the first frame captured by the camera in UTC, which is 2:07:00 EST. 
![alt tag](https://github.com/sanjanaKamb/DesignProject/blob/master/Picture11.png)
- Below is the timestamp when the frame is displayed in the Android app, which is 2:07:07 EST.
![alt tag](https://github.com/sanjanaKamb/DesignProject/blob/master/Picture12.png)
