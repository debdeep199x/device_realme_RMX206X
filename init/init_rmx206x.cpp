/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <android-base/logging.h>
#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

#include "property_service.h"
#include "vendor_init.h"

#include <fstream>

void property_override(char const prop[], char const value[]) {
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_multifp(char const buildfp[], char const systemfp[],
        char const bootimagefp[], char const vendorfp[], char const value[]) {
    property_override(buildfp, value);
    property_override(systemfp, value);
    property_override(bootimagefp, value);
    property_override(vendorfp, value);
}

void load_rmx2061() {
    property_override("ro.product.name", "RMX2061");
    property_override("ro.product.model", "RMX2061");
    property_override("ro.product.system.model", "RMX2061");
    property_override("ro.build.product", "RMX2061");
    property_override("ro.product.device", "RMX2061L1");
}

void load_rmx2063() {
    property_override("ro.product.name", "RMX2063");
    property_override("ro.product.model", "RMX2063");
    property_override("ro.product.system.model", "RMX2063");
    property_override("ro.build.product", "RMX2063");
    property_override("ro.product.device", "RMX2063L1");
    
    //NFC PROPS
    property_override("persist.sys.nfc.disPowerSave", "1");
    property_override("persist.sys.nfc.aid_overflow", "true");
    property_override("persist.nfc.smartcard.recorder.enable", "true");
}

void set_var()
{
    // Check NFC
    std::ifstream infile("/proc/oppo_nfc/chipset");
    std::string check;
    getline(infile, check);
    if (!check.compare("NULL")) {
    	load_rmx2061();
    } else {
    	load_rmx2063();
    }

}

void vendor_load_properties() {

    set_var();

    property_override("ro.build.description", "redfin-user 11 RQ3A.210805.001.A1 7474174 release-keys");
    property_override_multifp("ro.build.fingerprint", "ro.system.build.fingerprint", "ro.bootimage.build.fingerprint",
        "ro.vendor.build.fingerprint", "google/redfin/redfin:11/RQ3A.210805.001.A1/7474174:user/release-keys");

    property_override("ro.apex.updatable", "true");
    property_override("ro.oem_unlock_supported", "0");

}
