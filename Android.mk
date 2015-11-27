LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libdvbsi++

LOCAL_SDK_VERSION := 14
LOCAL_NDK_STL_VARIANT := c++_static
LOCAL_SHARED_LIBRARIES := libdl

include $(LOCAL_PATH)/src/Makefile.am
LOCAL_SRC_FILES := $(foreach file,$(libdvbsi___la_SOURCES),src/$(file))

include $(LOCAL_PATH)/include/dvbsi++/Makefile.am
LOCAL_COPY_HEADERS := $(foreach file,$(pkginclude_HEADERS),include/dvbsi++/$(file))
LOCAL_COPY_HEADERS_TO := dvbsi++

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_CPPFLAGS := -DHAVE_BYTESWAP_H -DHAVE_INTTYPES_H -DHAVE_STDINT_H -DHAVE_UNISTD_H

include $(BUILD_SHARED_LIBRARY)
