####################################################################################################
#  ─────────────────────────────────────────────────────────────────
#   ■■ dumpTool ■■
#  ─────────────────────────────────────────────────────────────────
#   [Abstract] File dump tool
#     DUMP TOOL for ROMs and other files
#     Dumps in decimal, binary, and hexadecimal
#
#  ─────────────────────────────────────────────────────────────────
#   ■■ Usage ■■
#  ─────────────────────────────────────────────────────────────────
#
#     dumptool -f <FILENAME>
#
####################################################################################################
# Add Source File
add_executable (
	dumpTool 
"dumpTool.cpp"
"framework.h" 
"getopt.c"
"getopt.h"
"getoptCMD.cpp"
"getoptCMD.h"
)
####################################################################################################
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET dumpTool PROPERTY CXX_STANDARD 20)
endif()
####################################################################################################
# Copy the Sample file
#add_custom_command(
#    TARGET dumpTool POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#        "${CMAKE_SOURCE_DIR}/dumpTool/TanchouTsuru.png"
#        "$<TARGET_FILE_DIR:dumpTool>/TanchouTsuru.png"
#)
add_custom_command(
    #
    TARGET dumpTool POST_BUILD
    #
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/dumpTool/TanchouTsuru.png"
        "$<TARGET_FILE_DIR:dumpTool>/TanchouTsuru.png"
    #
    COMMAND ${CMAKE_COMMAND} -E echo "RUN dumpTool"
    #
    COMMAND "$<TARGET_FILE:dumpTool>"
            -f
            TanchouTsuru.png
    #
    WORKING_DIRECTORY "$<TARGET_FILE_DIR:dumpTool>"
)
####################################################################################################
