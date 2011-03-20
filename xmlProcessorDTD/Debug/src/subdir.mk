################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Attlist.cpp \
../src/Attribut.cpp \
../src/DTDContainer.cpp \
../src/Element.cpp \
../src/Info.cpp \
../src/Type.cpp \
../src/TypeAtomique.cpp \
../src/TypeChoice.cpp \
../src/TypeSequence.cpp \
../src/xmlprocessorDTD.cpp 

OBJS += \
./src/Attlist.o \
./src/Attribut.o \
./src/DTDContainer.o \
./src/Element.o \
./src/Info.o \
./src/Type.o \
./src/TypeAtomique.o \
./src/TypeChoice.o \
./src/TypeSequence.o \
./src/xmlprocessorDTD.o 

CPP_DEPS += \
./src/Attlist.d \
./src/Attribut.d \
./src/DTDContainer.d \
./src/Element.d \
./src/Info.d \
./src/Type.d \
./src/TypeAtomique.d \
./src/TypeChoice.d \
./src/TypeSequence.d \
./src/xmlprocessorDTD.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


