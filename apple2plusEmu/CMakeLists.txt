####################################################################################################
# 
#   apple2plusEmu
#   [Abstract] Apple II Plus emulator
#     Runs BASIC programs
#
#   Usage
#
#     apple2plusEmu <FILENAME>
#
####################################################################################################
# Add Source File
add_executable (
	apple2plusEmu 
"fake6502.h" 
"fake6502.c"
"libRun.h"
"libRun.c"
"main.c"
"main.h"
)
####################################################################################################
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET apple2plusEmu PROPERTY CXX_STANDARD 20)
endif()
####################################################################################################
# Copy the Sample file And Execute
add_custom_command(
    #
    TARGET apple2plusEmu POST_BUILD
    #
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/apple2plusEmu/codeTest.bas"
        "$<TARGET_FILE_DIR:apple2plusEmu>/codeTest.bas"
    #
    #COMMAND ${CMAKE_COMMAND} -E echo "RUN apple2plusEmu"
    #
    #COMMAND "$<TARGET_FILE:apple2plusEmu>"
    #        codeTest.bas
    #
    #WORKING_DIRECTORY "$<TARGET_FILE_DIR:apple2plusEmu>"
    #
)
####################################################################################################
# ROM COPY : basic.bin AND monitor.bin (only if the files exist)
####################################################################################################
 if(EXISTS "${CMAKE_SOURCE_DIR}/apple2plusEmu/basic.bin")
    add_custom_command(
        TARGET apple2plusEmu POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_SOURCE_DIR}/apple2plusEmu/basic.bin"
            "$<TARGET_FILE_DIR:apple2plusEmu>/basic.bin"
    )
    message(STATUS "Found: basic.bin")
else()
    message(WARNING "Not found: basic.bin")
endif()
#
if(EXISTS "${CMAKE_SOURCE_DIR}/apple2plusEmu/monitor.bin")
    add_custom_command(
        TARGET apple2plusEmu POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_SOURCE_DIR}/apple2plusEmu/monitor.bin"
            "$<TARGET_FILE_DIR:apple2plusEmu>/monitor.bin"
    )
    message(STATUS "Found: monitor.bin")
else()
    message(WARNING "Not found: monitor.bin")
endif()
####################################################################################################
