################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/infineon_libraries/iLLD/TC36A/Tricore/Gtm/Atom/Timer/IfxGtm_Atom_Timer.c 

OBJS += \
./Libraries/infineon_libraries/iLLD/TC36A/Tricore/Gtm/Atom/Timer/IfxGtm_Atom_Timer.o 

COMPILED_SRCS += \
./Libraries/infineon_libraries/iLLD/TC36A/Tricore/Gtm/Atom/Timer/IfxGtm_Atom_Timer.src 

C_DEPS += \
./Libraries/infineon_libraries/iLLD/TC36A/Tricore/Gtm/Atom/Timer/IfxGtm_Atom_Timer.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/infineon_libraries/iLLD/TC36A/Tricore/Gtm/Atom/Timer/%.src: ../Libraries/infineon_libraries/iLLD/TC36A/Tricore/Gtm/Atom/Timer/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc36x -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\CODE" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\doc" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Configurations" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\_Build" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\_Impl" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\_Lib" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\_Lib\DataHandling" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\_Lib\InternalMux" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\_PinMap" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Asclin" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Asclin\Asc" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Asclin\Lin" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Asclin\Spi" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Asclin\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Can" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Can\Can" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Can\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Ccu6" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Ccu6\Icu" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Ccu6\PwmBc" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Ccu6\PwmHl" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Ccu6\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Ccu6\Timer" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Ccu6\TimerWithTrigger" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Ccu6\TPwm" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Convctrl" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Convctrl\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Cpu" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Cpu\Irq" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Cpu\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Cpu\Trap" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Dma" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Dma\Dma" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Dma\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Dts" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Dts\Dts" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Dts\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Edsadc" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Edsadc\Edsadc" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Edsadc\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Eray" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Eray\Eray" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Eray\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Evadc" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Evadc\Adc" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Evadc\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Fce" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Fce\Crc" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Fce\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Flash" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Flash\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Geth" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Geth\Eth" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Geth\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gpt12" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gpt12\IncrEnc" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gpt12\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Atom" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Atom\Pwm" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Atom\PwmHl" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Atom\Timer" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Tim" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Tim\In" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Tim\Timer" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Tom" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Tom\Pwm" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Tom\PwmHl" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Tom\Timer" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Gtm\Trig" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Hssl" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Hssl\Hssl" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Hssl\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\I2c" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\I2c\I2c" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\I2c\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Iom" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Iom\Driver" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Iom\Iom" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Iom\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Msc" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Msc\Msc" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Msc\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Mtu" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Mtu\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Pms" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Pms\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Port" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Port\Io" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Port\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Psi5" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Psi5\Psi5" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Psi5\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Psi5s" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Psi5s\Psi5s" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Psi5s\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Qspi" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Qspi\SpiMaster" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Qspi\SpiSlave" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Qspi\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Scu" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Scu\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Sent" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Sent\Sent" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Sent\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Smu" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Smu\Smu" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Smu\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Src" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Src\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Stm" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Stm\Std" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\iLLD\TC36A\Tricore\Stm\Timer" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Infra" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Infra\Platform" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Infra\Platform\Tricore" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Infra\Platform\Tricore\Compilers" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Infra\Sfr" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Infra\Sfr\TC36A" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Infra\Sfr\TC36A\_Reg" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Infra\Ssw" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Infra\Ssw\TC36A" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Infra\Ssw\TC36A\Tricore" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Service" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Service\CpuGeneric" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Service\CpuGeneric\_Utilities" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Service\CpuGeneric\If" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Service\CpuGeneric\If\Ccu6If" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Service\CpuGeneric\StdIf" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Service\CpuGeneric\SysSe" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\Bsp" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\Comm" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\General" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\Math" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\Time" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\seekfree_libraries" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\seekfree_libraries\common" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\Libraries\seekfree_peripheral" -I"D:\TC364CAR\Car\Seekfree_TC364_Opensource_Library\USER" --iso=99 --c++14 --language=+volatile --anachronisms --fp-model=3 --fp-model=c --fp-model=f --fp-model=l --fp-model=n --fp-model=r --fp-model=z -O0 --tradeoff=0 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc36x -o "$@"  "$<"  -cs --dep-file=$(@:.src=.d) --misrac-version=2012 -N0 -Z0 -Y0 2>&1; sed -i -e '/ctc\\include/d' -e '/Libraries\\iLLD/d' -e '/Libraries\\Infra/d' -e 's/\(.*\)".*\\Seekfree_TC364_Opensource_Library\(\\.*\)"/\1\.\.\2/g' -e 's/\\/\//g' $(@:.src=.d) && \
	echo $(@:.src=.d) generated
	@echo 'Finished building: $<'
	@echo ' '

Libraries/infineon_libraries/iLLD/TC36A/Tricore/Gtm/Atom/Timer/%.o: ./Libraries/infineon_libraries/iLLD/TC36A/Tricore/Gtm/Atom/Timer/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


