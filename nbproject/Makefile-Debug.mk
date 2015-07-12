#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Game.o \
	${OBJECTDIR}/Gfx.o \
	${OBJECTDIR}/graphics/CheckBox.o \
	${OBJECTDIR}/graphics/Component.o \
	${OBJECTDIR}/graphics/Container.o \
	${OBJECTDIR}/graphics/Font.o \
	${OBJECTDIR}/graphics/Input.o \
	${OBJECTDIR}/graphics/Text.o \
	${OBJECTDIR}/graphics/Window.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/states/AbstractGameState.o \
	${OBJECTDIR}/states/MainMenuState.o \
	${OBJECTDIR}/states/PiskvorkyState.o \
	${OBJECTDIR}/states/SettingsState.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs SDL2_ttf` `pkg-config --libs sdl2` `pkg-config --libs SDL2_image`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/piskvorky

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/piskvorky: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/piskvorky ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Game.o: Game.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Game.o Game.cpp

${OBJECTDIR}/Gfx.o: Gfx.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gfx.o Gfx.cpp

${OBJECTDIR}/graphics/CheckBox.o: graphics/CheckBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/graphics/CheckBox.o graphics/CheckBox.cpp

${OBJECTDIR}/graphics/Component.o: graphics/Component.cpp 
	${MKDIR} -p ${OBJECTDIR}/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/graphics/Component.o graphics/Component.cpp

${OBJECTDIR}/graphics/Container.o: graphics/Container.cpp 
	${MKDIR} -p ${OBJECTDIR}/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/graphics/Container.o graphics/Container.cpp

${OBJECTDIR}/graphics/Font.o: graphics/Font.cpp 
	${MKDIR} -p ${OBJECTDIR}/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/graphics/Font.o graphics/Font.cpp

${OBJECTDIR}/graphics/Input.o: graphics/Input.cpp 
	${MKDIR} -p ${OBJECTDIR}/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/graphics/Input.o graphics/Input.cpp

${OBJECTDIR}/graphics/Text.o: graphics/Text.cpp 
	${MKDIR} -p ${OBJECTDIR}/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/graphics/Text.o graphics/Text.cpp

${OBJECTDIR}/graphics/Window.o: graphics/Window.cpp 
	${MKDIR} -p ${OBJECTDIR}/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/graphics/Window.o graphics/Window.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/states/AbstractGameState.o: states/AbstractGameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/states
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/AbstractGameState.o states/AbstractGameState.cpp

${OBJECTDIR}/states/MainMenuState.o: states/MainMenuState.cpp 
	${MKDIR} -p ${OBJECTDIR}/states
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/MainMenuState.o states/MainMenuState.cpp

${OBJECTDIR}/states/PiskvorkyState.o: states/PiskvorkyState.cpp 
	${MKDIR} -p ${OBJECTDIR}/states
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/PiskvorkyState.o states/PiskvorkyState.cpp

${OBJECTDIR}/states/SettingsState.o: states/SettingsState.cpp 
	${MKDIR} -p ${OBJECTDIR}/states
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags SDL2_ttf` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_image` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/SettingsState.o states/SettingsState.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/piskvorky

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
