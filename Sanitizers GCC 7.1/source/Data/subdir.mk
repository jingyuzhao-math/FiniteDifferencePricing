################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/Data/CDividend.cpp \
../source/Data/CInputData.cpp \
../source/Data/COutputData.cpp 

OBJS += \
./source/Data/CDividend.o \
./source/Data/CInputData.o \
./source/Data/COutputData.o 

CPP_DEPS += \
./source/Data/CDividend.d \
./source/Data/CInputData.d \
./source/Data/COutputData.d 


# Each subdirectory must supply rules for building sources it contributes
source/Data/%.o: ../source/Data/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++-7 -std=c++1y -I"/home/raiden/workspace/FiniteDifferencePricing/include" -I/usr/include/gtest -O0 -g3 -p -pg -ftest-coverage -fprofile-arcs -pedantic -pedantic-errors -Wall -Wextra -Werror -c -fmessage-length=0 -fstrict-aliasing sanitize-address-use-after-scope -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

