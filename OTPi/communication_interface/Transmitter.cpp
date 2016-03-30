#include "Transmitter.h"
#include "controllers/Controller.h"

Transmitter::Transmitter(int fd) {
	connfd= fd;
}

Transmitter::~Transmitter() {
	close(connfd);
}

void Transmitter::send(cv::Mat message) {
	logger->info("pushing into buff");
	//pthread_mutex_lock(&mutex);
	buffer.push(message);
	//pthread_mutex_unlock(&mutex);
}

void Transmitter::start() {
	pthread_create(&thread, NULL, &Transmitter::runEntry, this);
}

void* Transmitter::run() {
	logger->info("Starting Receiver Thread execution loop");
	int i =0;
	//while (Controller::isRunning()){
bool once = true;
while (true){

		if(dataProcessor->isSendNotification && dataProcessor->isRegionDefined){


            if(dataProcessor->isSendNotification==true&&once==true){
            	logger->info("sendNotification is true");
            	dataProcessor->isSendNotification=false;
            	dataProcessor->isRegionDefined = false;
            	dataProcessor->isOoiDefined = false;
            	dataProcessor->isFirstFrameDefined = false;
            	once=false;
            	continue;
            }else{
            	logger->info("sendNotification is false");
            }
			dataProcessor->isSendNotification = false;
			const char *notify = "notification\r\n";
			write(connfd, notify, strlen(notify ));
			continue;
		}
		
                if(buffer.empty()){
                    continue;
                }

		logger->info("getting from buffer");
                cv::Mat img = buffer.front();                             
                
                buffer.pop();          
		                
                vector<uchar> buf;
                vector<int> params = vector<int>(2);
                params.push_back(IMWRITE_PNG_COMPRESSION);
    		params.push_back(1);
                
              
                 bool encodeImage = imencode(".png", img, buf, params);
                 if(!encodeImage){
                     logger->error("Failed to encode video frame");
                }

		//cv::Mat dImg = imdecode(Mat(buf),1);

		/*vector<int> compression_params;
    		compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    		compression_params.push_back(1);
		std::string name2 = "alpha"+std::to_string (i)+".png";
		i++;
try {
        imwrite(name2, img, compression_params);
    }
    catch (cv::Exception& ex) {
        logger->error("Exception converting image to PNG format");
        
    }
              */  
                int imgSize = buf.size();
                 uchar* bufArr = &buf[0];

                 std::string name = "sending string: "+std::to_string(imgSize);
                 logger->info(name);
		std::string isize = std::to_string(imgSize);
		const char *cstr = isize.c_str();
		write(connfd, cstr, strlen(cstr));
		const char *carriageReturn = "\r\n";
               write(connfd, carriageReturn, strlen(carriageReturn));

               write(connfd, bufArr, imgSize);
		
		//delete img;


	
	}
	

	//pthread_exit(NULL);
}

void* Transmitter::runEntry(void* self) {
	return static_cast<Transmitter*>(self)->run();
}

