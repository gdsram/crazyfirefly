LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
	../../Classes/app_delegate.cpp \
	../../Classes/items/item.cpp \
	../../Classes/scenes/main_menu_scene.cpp \
	../../Classes/award_container.cpp \
	../../Classes/scenes/game_layer.cpp \
	../../Classes/scenes/awards_wall.cpp \
	../../Classes/scenes/how_to_play.cpp \
	../../Classes/scenes/game_over_scene.cpp \
	../../Classes/scenes/pause_scene.cpp \
	../../Classes/scenes/credits.cpp \
	../../Classes/global_colaboration.cpp \
	../../Classes/items/horizontal_bar.cpp \
	../../Classes/items/health.cpp \
	../../Classes/app_macros.h \
	../../Classes/items/player.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
