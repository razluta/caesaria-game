LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

STEAM_PATH     := ../steam
GAME_PATH := $(LOCAL_PATH)
DEP_PATH := ../dep
SDL_PATH := $(LOCAL_PATH)/$(DEP_PATH)/sdl2mini
SDL_MIXER_PATH := $(DEP_PATH)/mixer
SDL_NET_PATH := $(DEP_PATH)/SDL_net

LOCAL_C_INCLUDES := \
  $(LOCAL_PATH)/$(SDL_PATH)/include \
  $(LOCAL_PATH)/$(SDL_MIXER_PATH) \
  $(LOCAL_PATH)/$(SDL_NET_PATH)/include \
  $(LOCAL_PATH)/$(FREETYPE_PATH)/include \
  $(LOCAL_PATH)/$(GAME_PATH) \
  $(LOCAL_PATH)/$(DEP_PATH) \
  $(LOCAL_PATH)/$(DEP_PATH)/ttf \
  $(LOCAL_PATH)/$(DEP_PATH)/lzma \
  $(LOCAL_PATH)/$(DEP_PATH)/bzip2 \
  $(LOCAL_PATH)/$(DEP_PATH)/zlib \
  $(LOCAL_PATH)/$(DEP_PATH)/aes \
  $(LOCAL_PATH)/$(DEP_PATH)/smk \
  $(LOCAL_PATH)/$(STEAM_PATH) \
  $(LOCAL_PATH)/$(DEP_PATH)/litehtml/include \
  $(LOCAL_PATH)/$(DEP_PATH)/libpng

# Add your application source files here...
LOCAL_SRC_FILES := $(subst $(LOCAL_PATH)/,, \
  $(wildcard $(GAME_PATH)/*.cpp) \
  $(wildcard $(GAME_PATH)/core/*.cpp) \
  $(wildcard $(GAME_PATH)/vfs/*.cpp) \
  $(wildcard $(GAME_PATH)/objects/*.cpp) \
  $(wildcard $(GAME_PATH)/gui/*.cpp) \
  $(wildcard $(GAME_PATH)/city/*.cpp) \
  $(wildcard $(GAME_PATH)/font/*.cpp) \
  $(wildcard $(GAME_PATH)/gfx/*.cpp) \
  $(wildcard $(GAME_PATH)/events/*.cpp) \
  $(wildcard $(GAME_PATH)/world/*.cpp) \
  $(wildcard $(GAME_PATH)/pathway/*.cpp) \
  $(wildcard $(GAME_PATH)/walker/*.cpp) \
  $(wildcard $(GAME_PATH)/good/*.cpp) \
  $(wildcard $(GAME_PATH)/religion/*.cpp) \
  $(wildcard $(GAME_PATH)/scene/*.cpp) \
  $(wildcard $(GAME_PATH)/sound/*.cpp) \
  $(wildcard $(GAME_PATH)/game/*.cpp) \
  $(wildcard $(GAME_PATH)/thread/*.cpp) \
  $(wildcard $(GAME_PATH)/scripting/*.cpp) \
  $(wildcard $(LOCAL_PATH)/$(STEAM_PATH)/*.cpp) \
  $(wildcard $(GAME_PATH)/layers/*.cpp) \
  $(wildcard $(SDL_PATH)/src/main/android/SDL_android_main.c) )
  
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer SDL2_net sdl_ttf pnggo lzma bzip2 aes smk picoc
LOCAL_CPP_FEATURES += exceptions
LOCAL_CPP_FEATURES += rtti
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
