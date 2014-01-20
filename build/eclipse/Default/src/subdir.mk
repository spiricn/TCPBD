################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/spiricn/prog/workspace/TCPBD/src/ClientServerTest.cpp \
/home/spiricn/prog/workspace/TCPBD/src/Exception.cpp \
/home/spiricn/prog/workspace/TCPBD/src/Packet.cpp \
/home/spiricn/prog/workspace/TCPBD/src/Socket.cpp \
/home/spiricn/prog/workspace/TCPBD/src/TCPServer.cpp \
/home/spiricn/prog/workspace/TCPBD/src/Thread.cpp \
/home/spiricn/prog/workspace/TCPBD/src/main.cpp 

OBJS += \
./src/ClientServerTest.o \
./src/Exception.o \
./src/Packet.o \
./src/Socket.o \
./src/TCPServer.o \
./src/Thread.o \
./src/main.o 

CPP_DEPS += \
./src/ClientServerTest.d \
./src/Exception.d \
./src/Packet.d \
./src/Socket.d \
./src/TCPServer.d \
./src/Thread.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/ClientServerTest.o: /home/spiricn/prog/workspace/TCPBD/src/ClientServerTest.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Exception.o: /home/spiricn/prog/workspace/TCPBD/src/Exception.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Packet.o: /home/spiricn/prog/workspace/TCPBD/src/Packet.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Socket.o: /home/spiricn/prog/workspace/TCPBD/src/Socket.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/TCPServer.o: /home/spiricn/prog/workspace/TCPBD/src/TCPServer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Thread.o: /home/spiricn/prog/workspace/TCPBD/src/Thread.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: /home/spiricn/prog/workspace/TCPBD/src/main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


