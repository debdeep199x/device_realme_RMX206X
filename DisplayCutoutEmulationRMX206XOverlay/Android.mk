LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_RRO_THEME := DisplayCutoutEmulationRMX206X
LOCAL_PACKAGE_NAME := DisplayCutoutEmulationRMX206XOverlay
LOCAL_SDK_VERSION := current
LOCAL_PRODUCT_MODULE := true
LOCAL_RESOURCE_DIR := $(LOCAL_PATH)/res

include $(BUILD_RRO_PACKAGE)
