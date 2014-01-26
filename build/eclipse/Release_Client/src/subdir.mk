################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/spiricn/prog/workspace/TCPBD/src/Client.cpp \
/home/spiricn/prog/workspace/TCPBD/src/ClientProgram.cpp \
/home/spiricn/prog/workspace/TCPBD/src/ClientServerTest.cpp \
/home/spiricn/prog/workspace/TCPBD/src/ClientSession.cpp \
/home/spiricn/prog/workspace/TCPBD/src/ConditionVar.cpp \
/home/spiricn/prog/workspace/TCPBD/src/Exception.cpp \
/home/spiricn/prog/workspace/TCPBD/src/Mutex.cpp \
/home/spiricn/prog/workspace/TCPBD/src/Packet.cpp \
/home/spiricn/prog/workspace/TCPBD/src/Server.cpp \
/home/spiricn/prog/workspace/TCPBD/src/ServerProgram.cpp \
/home/spiricn/prog/workspace/TCPBD/src/ServerSession.cpp \
/home/spiricn/prog/workspace/TCPBD/src/Socket.cpp \
/home/spiricn/prog/workspace/TCPBD/src/SocketProxy.cpp \
/home/spiricn/prog/workspace/TCPBD/src/TCPServer.cpp \
/home/spiricn/prog/workspace/TCPBD/src/Thread.cpp \
/home/spiricn/prog/workspace/TCPBD/src/main.cpp 

OBJS += \
./src/Client.o \
./src/ClientProgram.o \
./src/ClientServerTest.o \
./src/ClientSession.o \
./src/ConditionVar.o \
./src/Exception.o \
./src/Mutex.o \
./src/Packet.o \
./src/Server.o \
./src/ServerProgram.o \
./src/ServerSession.o \
./src/Socket.o \
./src/SocketProxy.o \
./src/TCPServer.o \
./src/Thread.o \
./src/main.o 

CPP_DEPS += \
./src/Client.d \
./src/ClientProgram.d \
./src/ClientServerTest.d \
./src/ClientSession.d \
./src/ConditionVar.d \
./src/Exception.d \
./src/Mutex.d \
./src/Packet.d \
./src/Server.d \
./src/ServerProgram.d \
./src/ServerSession.d \
./src/Socket.d \
./src/SocketProxy.d \
./src/TCPServer.d \
./src/Thread.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/Client.o: /home/spiricn/prog/workspace/TCPBD/src/Client.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ClientProgram.o: /home/spiricn/prog/workspace/TCPBD/src/ClientProgram.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ClientServerTest.o: /home/spiricn/prog/workspace/TCPBD/src/ClientServerTest.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ClientSession.o: /home/spiricn/prog/workspace/TCPBD/src/ClientSession.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ConditionVar.o: /home/spiricn/prog/workspace/TCPBD/src/ConditionVar.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Exception.o: /home/spiricn/prog/workspace/TCPBD/src/Exception.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Mutex.o: /home/spiricn/prog/workspace/TCPBD/src/Mutex.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Packet.o: /home/spiricn/prog/workspace/TCPBD/src/Packet.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Server.o: /home/spiricn/prog/workspace/TCPBD/src/Server.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ServerProgram.o: /home/spiricn/prog/workspace/TCPBD/src/ServerProgram.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ServerSession.o: /home/spiricn/prog/workspace/TCPBD/src/ServerSession.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Socket.o: /home/spiricn/prog/workspace/TCPBD/src/Socket.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/SocketProxy.o: /home/spiricn/prog/workspace/TCPBD/src/SocketProxy.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/TCPServer.o: /home/spiricn/prog/workspace/TCPBD/src/TCPServer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Thread.o: /home/spiricn/prog/workspace/TCPBD/src/Thread.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: /home/spiricn/prog/workspace/TCPBD/src/main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTCPBD_CLIENT_PROGRAM=1 -I"/home/spiricn/prog/workspace/TCPBD/include" -I/home/spiricn/prog/workspace/TraceDog/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


