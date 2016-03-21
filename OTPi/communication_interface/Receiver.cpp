#include "Receiver.h"

Receiver::Receiver(int fd) {
	connfd= fd;
}

Receiver::~Receiver() {
	// TODO Auto-generated destructor stub
}

std::string Receiver::removespace(string line) {
 while (1){
   int letter = line.find(' ');
   if (letter == -1 ){
     break;
   }
   line = line.erase(letter, 1);
 }
 return line;
}

std::string Receiver::poll() {
	//pthread_mutex_lock(&mutex);
	std::string str = "";
	if(!buffer.empty()){
		str = buffer.front();
		logger->trace("New input received");
		buffer.pop();
	}
	//pthread_mutex_unlock(&mutex);
	return str;
}

void Receiver::start() {
	pthread_create(&thread, NULL, &Receiver::runEntry, this);
}

void* Receiver::run() {
	logger->info("Starting Receiver Thread execution loop");
	char buf[30];
	int byte_count;
	int repeat =3;
	std::string str = "";
	while (true){
		if(repeat==0){
			repeat = 3;
		}
		byte_count = recv(connfd, buf, sizeof buf, 0);
		if(repeat==3){
			str = std::string(buf);
			logger->info(str);
			str = removespace(str);
			logger->info("erase space "+str);
		
			std::istringstream ss(str);
			std::string token;
			std::string token2;
			string arr[5];
			int i=0; 
			int once =1;
			while(std::getline(ss, token, ',')) {
				std::istringstream ss2(token);				
				while(once==1&&std::getline(ss2, token2, '.')){
					once=0;
					logger->info("token2 "+token2);
					arr[i] = token2; 
				}
    				once=1;
				i++;
			}
			int x = atoi(arr[0].c_str());
			int y = atoi(arr[1].c_str());
			dataProcessor->ooi.x =x;
			dataProcessor->ooi.y=y;
			dataProcessor->isOoiDefined = true;	

		}
		repeat--;
	}

	pthread_exit(NULL);
}

void* Receiver::runEntry(void* self) {
	return static_cast<Receiver*>(self)->run();
}
