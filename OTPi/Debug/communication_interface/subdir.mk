################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../communication_interface/Receiver.cpp \
../communication_interface/Transmitter.cpp 

OBJS += \
./communication_interface/Receiver.o \
./communication_interface/Transmitter.o 

CPP_DEPS += \
./communication_interface/Receiver.d \
./communication_interface/Transmitter.d 


# Each subdirectory must supply rules for building sources it contributes
communication_interface/%.o: ../communication_interface/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv2 -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


