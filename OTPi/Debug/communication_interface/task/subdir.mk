################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../communication_interface/task/Task.cpp \
../communication_interface/task/TaskFactory.cpp \
../communication_interface/task/TurnTask.cpp 

OBJS += \
./communication_interface/task/Task.o \
./communication_interface/task/TaskFactory.o \
./communication_interface/task/TurnTask.o 

CPP_DEPS += \
./communication_interface/task/Task.d \
./communication_interface/task/TaskFactory.d \
./communication_interface/task/TurnTask.d 


# Each subdirectory must supply rules for building sources it contributes
communication_interface/task/%.o: ../communication_interface/task/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv2 -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


