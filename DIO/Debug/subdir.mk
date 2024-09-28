################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_prg.c \
../DIO_prg.c \
../EEPROM_prg.c \
../EXTI_prg.c \
../GIE_prg.c \
../KPD_prg.c \
../LCD_prg.c \
../OS_prg.c \
../SPI_prg.c \
../Seg7_prg.c \
../TWI_prg.c \
../Timer_prg.c \
../UART_prg.c \
../WDG_prg.c \
../commented.c \
../main.c \
../timers1Assi.c 

OBJS += \
./ADC_prg.o \
./DIO_prg.o \
./EEPROM_prg.o \
./EXTI_prg.o \
./GIE_prg.o \
./KPD_prg.o \
./LCD_prg.o \
./OS_prg.o \
./SPI_prg.o \
./Seg7_prg.o \
./TWI_prg.o \
./Timer_prg.o \
./UART_prg.o \
./WDG_prg.o \
./commented.o \
./main.o \
./timers1Assi.o 

C_DEPS += \
./ADC_prg.d \
./DIO_prg.d \
./EEPROM_prg.d \
./EXTI_prg.d \
./GIE_prg.d \
./KPD_prg.d \
./LCD_prg.d \
./OS_prg.d \
./SPI_prg.d \
./Seg7_prg.d \
./TWI_prg.d \
./Timer_prg.d \
./UART_prg.d \
./WDG_prg.d \
./commented.d \
./main.d \
./timers1Assi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


