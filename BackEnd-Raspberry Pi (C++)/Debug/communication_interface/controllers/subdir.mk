################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../communication_interface/controllers/Controller.cpp \
../communication_interface/controllers/ControllerThread.cpp 

OBJS += \
./communication_interface/controllers/Controller.o \
./communication_interface/controllers/ControllerThread.o 

CPP_DEPS += \
./communication_interface/controllers/Controller.d \
./communication_interface/controllers/ControllerThread.d 


# Each subdirectory must supply rules for building sources it contributes
communication_interface/controllers/%.o: ../communication_interface/controllers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv2 -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


