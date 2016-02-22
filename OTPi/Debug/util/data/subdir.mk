################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../util/data/DataFactory.cpp \
../util/data/ImgData.cpp 

OBJS += \
./util/data/DataFactory.o \
./util/data/ImgData.o 

CPP_DEPS += \
./util/data/DataFactory.d \
./util/data/ImgData.d 


# Each subdirectory must supply rules for building sources it contributes
util/data/%.o: ../util/data/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv2 -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


