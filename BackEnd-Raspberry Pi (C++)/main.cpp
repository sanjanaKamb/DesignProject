/**
 * main.cpp
 *
 * This file starts the program by initializing all of the necessary components.
 * It must be compiled using C++11 and uses the OpenCV 3.0 library and POSIX pthread library.
 */

#include "communication_interface/controllers/Controller.h"
#include "util/PropertyReader.h"
#include "util/Logger.h"
#include "data_processing/DataProcessor.h"

int main(int argc, char** argv) {

	// Initialize global timer and logger
	Timer* logTimer = new Timer();
	Logger logger("Main");
	Logger::initialize(Logger::Level::TRACE, true, true, logTimer);
	logger.trace("Logger initialized.");


	// Read property file and initialize accordingly
	PropertyReader* propReader;
	Properties* settings;

	if (argc > 1) {
		propReader = new PropertyReader(argv[1]);
	} else {
		propReader = new PropertyReader("settings/settings.txt");
	}
	// Set logging level
	settings = propReader->load();
	std::string loggingLevel = settings->getProperty("LOGGING_LEVEL");

	if (loggingLevel == "OFF") {
		Logger::setLoggingLevel(Logger::Level::OFF);
	} else if (loggingLevel == "TRACE") {
		Logger::setLoggingLevel(Logger::Level::TRACE);
	} else if (loggingLevel == "INFO") {
		Logger::setLoggingLevel(Logger::Level::INFO);
	} else if (loggingLevel == "DEBUG") {
		Logger::setLoggingLevel(Logger::Level::DEBUG);
	} else if (loggingLevel == "WARN") {
		Logger::setLoggingLevel(Logger::Level::WARN);
	} else if (loggingLevel == "ERROR") {
		Logger::setLoggingLevel(Logger::Level::ERROR);
	}

	// Start controller
	Controller* controller = new Controller();
	logger.trace("intializing controller");
	controller->initialize();

	//TODO: Startup TX/RX modules


	//TODO: Initialize storage


	//TODO: Start camera/processor
	DataProcessor* dataProcessor = new DataProcessor(settings);
	logger.trace("initializing dataprocessor");
	dataProcessor->initialize();
	controller->setDataProcessor(dataProcessor);
	logger.trace("running controller");

	controller->run();
	
	//dataProcessor->run();

	delete propReader;
	delete controller;
	delete dataProcessor;

	return 0;
}
