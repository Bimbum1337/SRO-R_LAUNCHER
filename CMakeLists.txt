cmake_minimum_required(VERSION 3.25)
project(SilkroadLauncher)

set(CMAKE_CXX_STANDARD 98)

# Define source files
set(SR_SOURCES
        DLLMain.cpp
        Lib.cpp
        Lib.h
        memory/hook.cpp
        memory/hook.h
        BSClientDlg.cpp
        BSClientDlg.h
        BSClientApp.cpp
        BSClientApp.h
        Controls/Agreement.cpp
        Controls/Agreement.h
        TextStringManager.cpp
        TextStringManager.h
        DivisonManager.cpp
        DivisonManager.h
        Controls/DivisionWindow.cpp
        Controls/DivisionWindow.h
        )

# Define GFX Library source files
set(GFX_SOURCES
        libs/JMX_Library/GFX/src/IFileManager.cpp
        )

# Define GFX Library header files
set(GFX_HEADERS
        libs/JMX_Library/GFX/include/GFXFM/CJArchiveFm.h
        libs/JMX_Library/GFX/include/GFXFM/DialogData.h
        libs/JMX_Library/GFX/include/GFXFM/eCallbackState.h
        libs/JMX_Library/GFX/include/GFXFM/IFileManager.h
        libs/JMX_Library/GFX/include/GFXFM/result_entry_t.h
        libs/JMX_Library/GFX/include/GFXFM/searchresult.h
        libs/JMX_Library/GFX/include/GFXFM/shit_t.h
        Controls/ImgScrollBar.cpp Controls/ImgScrollBar.h Controls/ImgStaticWnd.cpp Controls/ImgStaticWnd.h Controls/DlgHoverButton.cpp Controls/DlgHoverButton.h afxmsg_custom.h AfxStringMgr.cpp AfxStringMgr.h)

# Add the main library
add_library(SilkroadLauncher SHARED ${SR_SOURCES} ${GFX_SOURCES} ${GFX_HEADERS})

# Set the output directory for the library
set_target_properties(SilkroadLauncher PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        )

target_link_libraries(SilkroadLauncher PUBLIC ClientNet)

# Include directories
target_include_directories(SilkroadLauncher
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/memory
        ${CMAKE_CURRENT_SOURCE_DIR}/Controls
        ${CMAKE_CURRENT_SOURCE_DIR}/TextStringManager
        ${CMAKE_CURRENT_SOURCE_DIR}/DivisonManager
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/JMX_Library/GFX/include
        )


# Add subdirectory for external libraries
add_subdirectory(libs)
