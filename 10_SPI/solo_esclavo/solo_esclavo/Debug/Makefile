################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../src/ \
../src/ASF/ \
../src/ASF/common/ \
../src/ASF/common/boards/ \
../src/ASF/common/boards/user_board/ \
../src/ASF/common/services/ \
../src/ASF/common/services/clock/ \
../src/ASF/common/services/clock/xmega/ \
../src/ASF/common/utils/ \
../src/ASF/common/utils/interrupt/ \
../src/ASF/common/utils/make/ \
../src/ASF/xmega/ \
../src/ASF/xmega/drivers/ \
../src/ASF/xmega/drivers/cpu/ \
../src/ASF/xmega/drivers/nvm/ \
../src/ASF/xmega/utils/ \
../src/ASF/xmega/utils/assembler/ \
../src/ASF/xmega/utils/bit_handling/ \
../src/ASF/xmega/utils/preprocessor/ \
../src/config/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../src/config/spi_driver.c \
../src/ASF/common/services/clock/xmega/sysclk.c \
../src/ASF/xmega/drivers/nvm/nvm.c \
../src/ASF/common/boards/user_board/init.c \
../src/main.c


PREPROCESSING_SRCS +=  \
../src/ASF/xmega/drivers/nvm/nvm_asm.s \
../src/ASF/xmega/drivers/cpu/ccp.s


ASM_SRCS += 


OBJS +=  \
src/config/spi_driver.o \
src/ASF/common/services/clock/xmega/sysclk.o \
src/ASF/xmega/drivers/nvm/nvm.o \
src/ASF/xmega/drivers/nvm/nvm_asm.o \
src/ASF/xmega/drivers/cpu/ccp.o \
src/ASF/common/boards/user_board/init.o \
src/main.o

OBJS_AS_ARGS +=  \
src/config/spi_driver.o \
src/ASF/common/services/clock/xmega/sysclk.o \
src/ASF/xmega/drivers/nvm/nvm.o \
src/ASF/xmega/drivers/nvm/nvm_asm.o \
src/ASF/xmega/drivers/cpu/ccp.o \
src/ASF/common/boards/user_board/init.o \
src/main.o

C_DEPS +=  \
src/config/spi_driver.d \
src/ASF/common/services/clock/xmega/sysclk.d \
src/ASF/xmega/drivers/nvm/nvm.d \
src/ASF/xmega/drivers/nvm/nvm_asm.d \
src/ASF/xmega/drivers/cpu/ccp.d \
src/ASF/common/boards/user_board/init.d \
src/main.d

C_DEPS_AS_ARGS +=  \
src/config/spi_driver.d \
src/ASF/common/services/clock/xmega/sysclk.d \
src/ASF/xmega/drivers/nvm/nvm.d \
src/ASF/xmega/drivers/nvm/nvm_asm.d \
src/ASF/xmega/drivers/cpu/ccp.d \
src/ASF/common/boards/user_board/init.d \
src/main.d

OUTPUT_FILE_PATH +=solo_esclavo.elf

OUTPUT_FILE_PATH_AS_ARGS +=solo_esclavo.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler











src/config/%.o: ../src/config/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -DDEBUG -DBOARD=USER_BOARD  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\include" -I"../common/applications/user_application/user_board/config" -I"../src/ASF/xmega/utils" -I"../src/config" -I"../src/ASF/common/boards" -I"../src/ASF/xmega/utils/preprocessor" -I"../src/ASF/common/utils" -I"../src" -I"../src/ASF/common/boards/user_board" -I"../src/ASF/xmega/drivers/cpu" -I"../src/ASF/xmega/drivers/nvm" -I"../src/ASF/common/services/clock"  -O1 -fdata-sections -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g3 -Wall -mmcu=atxmega32a4u -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\gcc\dev\atxmega32a4u" -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/common/services/clock/xmega/%.o: ../src/ASF/common/services/clock/xmega/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -DDEBUG -DBOARD=USER_BOARD  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\include" -I"../common/applications/user_application/user_board/config" -I"../src/ASF/xmega/utils" -I"../src/config" -I"../src/ASF/common/boards" -I"../src/ASF/xmega/utils/preprocessor" -I"../src/ASF/common/utils" -I"../src" -I"../src/ASF/common/boards/user_board" -I"../src/ASF/xmega/drivers/cpu" -I"../src/ASF/xmega/drivers/nvm" -I"../src/ASF/common/services/clock"  -O1 -fdata-sections -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g3 -Wall -mmcu=atxmega32a4u -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\gcc\dev\atxmega32a4u" -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/xmega/drivers/nvm/%.o: ../src/ASF/xmega/drivers/nvm/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -DDEBUG -DBOARD=USER_BOARD  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\include" -I"../common/applications/user_application/user_board/config" -I"../src/ASF/xmega/utils" -I"../src/config" -I"../src/ASF/common/boards" -I"../src/ASF/xmega/utils/preprocessor" -I"../src/ASF/common/utils" -I"../src" -I"../src/ASF/common/boards/user_board" -I"../src/ASF/xmega/drivers/cpu" -I"../src/ASF/xmega/drivers/nvm" -I"../src/ASF/common/services/clock"  -O1 -fdata-sections -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g3 -Wall -mmcu=atxmega32a4u -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\gcc\dev\atxmega32a4u" -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/common/boards/user_board/%.o: ../src/ASF/common/boards/user_board/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -DDEBUG -DBOARD=USER_BOARD  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\include" -I"../common/applications/user_application/user_board/config" -I"../src/ASF/xmega/utils" -I"../src/config" -I"../src/ASF/common/boards" -I"../src/ASF/xmega/utils/preprocessor" -I"../src/ASF/common/utils" -I"../src" -I"../src/ASF/common/boards/user_board" -I"../src/ASF/xmega/drivers/cpu" -I"../src/ASF/xmega/drivers/nvm" -I"../src/ASF/common/services/clock"  -O1 -fdata-sections -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g3 -Wall -mmcu=atxmega32a4u -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\gcc\dev\atxmega32a4u" -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -DDEBUG -DBOARD=USER_BOARD  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\include" -I"../common/applications/user_application/user_board/config" -I"../src/ASF/xmega/utils" -I"../src/config" -I"../src/ASF/common/boards" -I"../src/ASF/xmega/utils/preprocessor" -I"../src/ASF/common/utils" -I"../src" -I"../src/ASF/common/boards/user_board" -I"../src/ASF/xmega/drivers/cpu" -I"../src/ASF/xmega/drivers/nvm" -I"../src/ASF/common/services/clock"  -O1 -fdata-sections -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g3 -Wall -mmcu=atxmega32a4u -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\gcc\dev\atxmega32a4u" -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler
src/ASF/xmega/drivers/nvm/nvm_asm.o: ../src/ASF/xmega/drivers/nvm/nvm_asm.s
	@echo Building file: $<
	@echo Invoking: AVR/GNU Assembler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -mmcu=atxmega32a4u -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\gcc\dev\atxmega32a4u" -mrelax -DBOARD=USER_BOARD -I "../common/applications/user_application/user_board/config" -I "../src/ASF/xmega/utils" -I "../src/config" -I "../src/ASF/common/boards" -I "../src/ASF/xmega/utils/preprocessor" -I "../src/ASF/common/utils" -I "../src" -I "../src/ASF/common/boards/user_board" -I "../src/ASF/xmega/drivers/cpu" -I "../src/ASF/xmega/drivers/nvm" -I "../src/ASF/common/services/clock"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/xmega/drivers/cpu/ccp.o: ../src/ASF/xmega/drivers/cpu/ccp.s
	@echo Building file: $<
	@echo Invoking: AVR/GNU Assembler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -mmcu=atxmega32a4u -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\gcc\dev\atxmega32a4u" -mrelax -DBOARD=USER_BOARD -I "../common/applications/user_application/user_board/config" -I "../src/ASF/xmega/utils" -I "../src/config" -I "../src/ASF/common/boards" -I "../src/ASF/xmega/utils/preprocessor" -I "../src/ASF/common/utils" -I "../src" -I "../src/ASF/common/boards/user_board" -I "../src/ASF/xmega/drivers/cpu" -I "../src/ASF/xmega/drivers/nvm" -I "../src/ASF/common/services/clock"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	


src/ASF/xmega/drivers/nvm/%.o: ../src/ASF/xmega/drivers/nvm/%.s
	@echo Building file: $<
	@echo Invoking: AVR/GNU Assembler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -mmcu=atxmega32a4u -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\gcc\dev\atxmega32a4u" -mrelax -DBOARD=USER_BOARD -I "../common/applications/user_application/user_board/config" -I "../src/ASF/xmega/utils" -I "../src/config" -I "../src/ASF/common/boards" -I "../src/ASF/xmega/utils/preprocessor" -I "../src/ASF/common/utils" -I "../src" -I "../src/ASF/common/boards/user_board" -I "../src/ASF/xmega/drivers/cpu" -I "../src/ASF/xmega/drivers/nvm" -I "../src/ASF/common/services/clock"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/xmega/drivers/cpu/%.o: ../src/ASF/xmega/drivers/cpu/%.s
	@echo Building file: $<
	@echo Invoking: AVR/GNU Assembler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -mmcu=atxmega32a4u -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\gcc\dev\atxmega32a4u" -mrelax -DBOARD=USER_BOARD -I "../common/applications/user_application/user_board/config" -I "../src/ASF/xmega/utils" -I "../src/config" -I "../src/ASF/common/boards" -I "../src/ASF/xmega/utils/preprocessor" -I "../src/ASF/common/utils" -I "../src" -I "../src/ASF/common/boards/user_board" -I "../src/ASF/xmega/drivers/cpu" -I "../src/ASF/xmega/drivers/nvm" -I "../src/ASF/common/services/clock"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="solo_esclavo.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atxmega32a4u -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAA_DFP\1.0.36\gcc\dev\atxmega32a4u" -Wl,--relax  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "solo_esclavo.elf" "solo_esclavo.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "solo_esclavo.elf" "solo_esclavo.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "solo_esclavo.elf" > "solo_esclavo.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "solo_esclavo.elf" "solo_esclavo.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "solo_esclavo.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "solo_esclavo.elf" "solo_esclavo.a" "solo_esclavo.hex" "solo_esclavo.lss" "solo_esclavo.eep" "solo_esclavo.map" "solo_esclavo.srec" "solo_esclavo.usersignatures"
	