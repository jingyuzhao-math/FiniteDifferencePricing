################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tests/TestBlackScholes.cpp \
../tests/TestEvolutionOperator.cpp \
../tests/TestGrid.cpp 

OBJS += \
./tests/TestBlackScholes.o \
./tests/TestEvolutionOperator.o \
./tests/TestGrid.o 

CPP_DEPS += \
./tests/TestBlackScholes.d \
./tests/TestEvolutionOperator.d \
./tests/TestGrid.d 


# Each subdirectory must supply rules for building sources it contributes
tests/%.o: ../tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++-7 -std=c++1y -I"/home/raiden/workspace/FiniteDifferencePricing/include" -I/usr/include/gtest -O3 -pedantic -pedantic-errors -Wall -Wextra -Werror -c -fmessage-length=0 -fstrict-aliasing -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


