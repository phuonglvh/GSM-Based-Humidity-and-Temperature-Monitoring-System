################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
include/uartstdio.obj: ../include/uartstdio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/anonymous/ti/ccsv7/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/mnt/anonymous/Academic/Google Drive BKU/Honor Program/Term 172/Embedded System Programming/Project/Code/TivaC" --include_path="/home/anonymous/ti/ccsv7/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="/media/anonymous/Software/SOFTWARES/STUDY SOFTWARES/CCSv7/TivaWare" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="include/uartstdio.d_raw" --obj_directory="include" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


