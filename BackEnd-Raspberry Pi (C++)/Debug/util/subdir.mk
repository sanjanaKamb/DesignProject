################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../util/Logger.cpp \
../util/Properties.cpp \
../util/PropertyReader.cpp \
../util/Timer.cpp \
../util/Util.cpp 

OBJS += \
./util/Logger.o \
./util/Properties.o \
./util/PropertyReader.o \
./util/Timer.o \
./util/Util.o 

CPP_DEPS += \
./util/Logger.d \
./util/Properties.d \
./util/PropertyReader.d \
./util/Timer.d \
./util/Util.d 


# Each subdirectory must supply rules for building sources it contributes
util/%.o: ../util/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv2 -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


