#include "Transmitter.h"
#include "controllers/Controller.h"

Transmitter::Transmitter(int port) {
	int listenfd = 0;
        connfd = 0;
        struct sockaddr_in serv_addr;
        
        listenfd = socket(AF_INET, SOCK_STREAM, 0);
        if(listenfd == -1){
            logger->error("Could not create socket");
            return;
        }
        logger->info("socket retrieve success");
        
        memset(&serv_addr, '0', sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;    
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
        serv_addr.sin_port = htons(port);  
        
        bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
	logger->info("binding done");
        
        if(listen(listenfd, 10) == -1){
            logger->error("Failed to listen");
            return;
        }
        logger->info("done listening");
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
	logger->info("accepting");
        if (connfd<0){
            logger->error("Accept Failed");
        }

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
while (true){

		logger->info("running");
		//pthread_mutex_lock(&mutex);
                if(buffer.empty()){
                  // pthread_mutex_unlock(&mutex);
                    continue;
                }

		logger->info("getting from buffer");
                cv::Mat img = buffer.front();
                //std::vector<uchar> sendString = buffer.front();
                
                //uchar* frameBuf = &sendString[0];
                //std::string frameString(reinterpret_cast<char*>(frameBuf)); 
                
                //logger->info(frameString);
              
                
                buffer.pop();          
		//pthread_mutex_unlock(&mutex);
                

                //decode
                /*Mat image = imdecode(Mat(sendString),CV_LOAD_IMAGE_COLOR);
                ImgData* new_data;
                new_data = new ImgData("raw", image);
                new_data->showImg("test");*/
                /*std::string fString(reinterpret_cast<char*>(frameBuf));
                const char *cstr = fString.c_str();
                write(connfd, cstr, strlen(cstr));*/
                
                /*img = (img.reshape(0,1)); // to make it continuous
                int  imgSize = img.total()*img.elemSize();
                 byte * imgBytes = new byte[imgSize]; 
                 std::memcpy(imgBytes,img.data,imgSize * sizeof(byte));*/
                
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

