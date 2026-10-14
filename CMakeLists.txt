####################################################################################################
#  -------------------------------------------------------------------------------------------------
#   ■■ Apple 2 Plus Emulator ■■
#  -------------------------------------------------------------------------------------------------
#   [Abstract]
#     Emulator for running the Microsoft 6502 BASIC of the Apple 2 Plus
#     How to use
#       (1) Edit the BASIC code in an editor
#       (2) Run the BASIC Emulator with the BASIC code file as its argument
#       (3) The result is printed to the console
#
#
#  -------------------------------------------------------------------------------------------------
#   ■■ Example run -> final MONITOR output only ■■
#  -------------------------------------------------------------------------------------------------
#
#     ----------------------------------------
#     ]
#     
#     ]900 END
#     
#     ]RUN
#     PRINT ALL ASCII CODE :
#             CHECK OUTPUT CHARACTOR
#     ----------------------------------------
#      !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGH
#     IJKLMNOPQRSTUVWXYZ[\]^_@ABCDEFGHIJKLMNOP
#     QRSTUVWXYZ[\]^
#     ----------------------------------------
#     
#     PRINT CONTINUOUS ASCII CODE :
#             CHECK OUTPUT CHARACTOR
#     ----------------------------------------
#     #$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJ
#     KLMNOPQRSTUVWXYZ[\]^_
#     ----------------------------------------
#     
#     
#     ]
#     
#     ]`
#     ----------------------------------------
#
#  -------------------------------------------------------------------------------------------------
####################################################################################################
cmake_minimum_required (VERSION 3.10)
####################################################################################################
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
####################################################################################################
#   if (MSVC)
#       add_compile_options(/utf-8)
#   endif()
####################################################################################################
project ("APPLE2PLUS_EMULATOR")
####################################################################################################
# Include sub-projects.
add_subdirectory ("apple2plusEmu")
add_subdirectory ("dumpTool")
####################################################################################################
