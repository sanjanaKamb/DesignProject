################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../camera/CameraInterface.cpp \
../camera/HwInterface.cpp 

OBJS += \
./camera/CameraInterface.o \
./camera/HwInterface.o 

CPP_DEPS += \
./camera/CameraInterface.d \
./camera/HwInterface.d 


# Each subdirectory must supply rules for building sources it contributes
camera/%.o: ../camera/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv2 -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


