FSC          = fsharpc --nologo
FSC_ASM_FLAG = -r:
FSC_OUT_FLAG = -o

COPY  = cp -r -n
DEL   = rm -rf
MKDIR = mkdir -p

BUILD_DIR = bin/
OBJ_DIR   = obj/
APPNAME   = PlatformerGame.exe

MG_ASM_DIR        = /opt/MonoGameSDK/Assemblies/DesktopGL/
MG_ASM_LIDGRENNET = $(MG_ASM_DIR)Lidgren.Network.dll
MG_ASM_FRAMEWORK  = $(MG_ASM_DIR)MonoGame.Framework.dll
MG_ASM_NET        = $(MG_ASM_DIR)MonoGame.Framework.Net.dll
MG_ASM_NVORBIS    = $(MG_ASM_DIR)NVorbis.dll
MG_ASM_OPENTK     = $(MG_ASM_DIR)OpenTK.dll
MG_ASM_ALL        = $(MG_ASM_LIDGRENNET) $(MG_ASM_FRAMEWORK) $(MG_ASM_NET) \
                    $(MG_ASM_NVORBIS) $(MG_ASM_OPENTK)
MG_ASM_REF        = $(FSC_ASM_FLAG)$(MG_ASM_LIDGRENNET) \
                    $(FSC_ASM_FLAG)$(MG_ASM_FRAMEWORK) \
                    $(FSC_ASM_FLAG)$(MG_ASM_NET) \
                    $(FSC_ASM_FLAG)$(MG_ASM_NVORBIS) \
                    $(FSC_ASM_FLAG)$(MG_ASM_OPENTK)

FSC_SRC = AssemblyInfo.fs GameManager.fs LevelScreen.fs PlatformerGame.fs Program.fs

.PHONY: prepare clean delete

all: prepare
	$(FSC) $(MG_ASM_REF) $(FSC_SRC) $(FSC_OUT_FLAG) $(BUILD_DIR)$(APPNAME)
	@echo End of compilation task.

prepare:
	@echo Creating directories
	@$(MKDIR) $(BUILD_DIR) $(OBJ_DIR)
	@echo Copying necessary assemblies
	@$(COPY) $(MG_ASM_ALL) $(BUILD_DIR)
    
clean:
	$(DEL) $(OBJ_DIR)

delete:
	$(DEL) $(BUILD_DIR)
