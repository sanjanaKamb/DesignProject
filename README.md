Read 'Final Project Report' for the detailed design and implementation of the application.
Read 'Quick Overview' for a brief powerpoint presentation of the project.

Current security monitoring systems available on the market rely heavily on human attention. A simple example of this can be found in security rooms with a single security guard tasked with monitoring several dozens of camera feeds at once. If the guard were to fall asleep or simply leave the room, there would be serious security implications. The goal of our ECE496 project is to develop software for a semi-autonomous security monitoring system to reduce the risk of human error while finding a good balance between machine and human.

Ultimately, this proposed system must be able to detect and outline objects in motion (i.e. objects of interest) and allow users to select and de-select their own objects. Once detected, these objects must be tracked and users must be notified of potential security threats in real-time. In this case, potential threats are assumed to be objects of interest entering within close proximity to each other.

The final application employed the use of a Raspberry Pi and a RaspiCam to remotely stream and process the video feed. This backend system would be in charge of filtering, detecting and tracking objects of interest and alerting a remote user on his/her Android mobile application over WiFi. Alerts would only be generated if these objects came in proximity of each other. In this way, the monitoring system would only require the user’s attention for short periods of time.

Upon completion, several of the team’s objectives were met, which included the ability to select and outline objects of interest, and notify users of movement within 7 seconds of receiving the image. Although communication speeds were subpar, achieving only 0.2 frames per second, the team deemed this an area for improvement for future work as it did not significantly hinder the project’s overall success.
