################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../storage/ObjectMetaData.cpp \
../storage/ObjectStorage.cpp 

OBJS += \
./storage/ObjectMetaData.o \
./storage/ObjectStorage.o 

CPP_DEPS += \
./storage/ObjectMetaData.d \
./storage/ObjectStorage.d 


# Each subdirectory must supply rules for building sources it contributes
storage/%.o: ../storage/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv2 -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


