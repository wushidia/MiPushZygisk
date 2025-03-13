#include "hook.h"
#include "logging.h"
#include <string>

using namespace std;

jstring (*orig_native_get)(JNIEnv *env, jclass clazz, jstring keyJ, jstring defJ);

jstring my_native_get(JNIEnv *env, jclass clazz, jstring keyJ, jstring defJ) {
    const char *key = env->GetStringUTFChars(keyJ, nullptr);
    const char *def = env->GetStringUTFChars(defJ, nullptr);

    jstring hooked_result = nullptr;

    // MIUI
    if (strcmp(key, "ro.product.brand") == 0) { // ro.product.brand=Xiaomi
        hooked_result = env->NewStringUTF("Xiaomi");
    } else if (strcmp(key, "ro.product.manufacturer") == 0) { // ro.product.manufacturer=Xiaomi
        hooked_result = env->NewStringUTF("Xiaomi");
    } else if (strcmp(key, "ro.miui.ui.version.name") == 0) { // ro.miui.ui.version.name=V130
        hooked_result = env->NewStringUTF("V130");
    } else if (strcmp(key, "ro.miui.ui.version.code") == 0) { // ro.miui.ui.version.code=13
        hooked_result = env->NewStringUTF("13");
    } else if (strcmp(key, "ro.miui.internal.storage") == 0) { // ro.miui.internal.storage=/sdcard/
        hooked_result = env->NewStringUTF("/sdcard/");
    } else if (strcmp(key, "ro.miui.region") == 0) { // ro.miui.region=CN
        hooked_result = env->NewStringUTF("CN");
    } else if (strcmp(key, "ro.miui.cust_variant") == 0) { // ro.miui.cust_variant=cn
        hooked_result = env->NewStringUTF("cn");
    } else if (strcmp(key, "ro.vendor.miui.region") == 0) { // ro.vendor.miui.region=CN
        hooked_result = env->NewStringUTF("CN");
    } else if (strcmp(key, "ro.product.locale.region") == 0) { // ro.product.locale.region=cn
        hooked_result = env->NewStringUTF("CN");
    } else if (strcmp(key, "ro.product.country.region") == 0) { // ro.product.country.region=CN
        hooked_result = env->NewStringUTF("CN");
    } else if (strcmp(key, "persist.sys.country") == 0) { // persist.sys.country=CN
        hooked_result = env->NewStringUTF("CN");
    // 为所有设备伪装小米15Ultra
    }else if (strcmp(key, "ro.product.vendor.manufacturer") == 0) { // ro.product.vendor.manufacturer=Xiaomi
        hooked_result = env->NewStringUTF("Xiaomi");
    }else if (strcmp(key, "ro.product.name") == 0) { // ro.product.name=Xiaomi
        hooked_result = env->NewStringUTF("Xiaomi");
    }else if (strcmp(key, "ro.product.vendor.brand") == 0) { // ro.product.vendor.brand=Xiaomi
        hooked_result = env->NewStringUTF("Xiaomi");
    }else if (strcmp(key, "ro.product.model") == 0) { // ro.product.model=25010PN30C
        hooked_result = env->NewStringUTF("25010PN30C");
    }else if (strcmp(key, "ro.product.device") == 0) { // ro.product.device=xuanyuan
        hooked_result = env->NewStringUTF("xuanyuan");
    }else if (strcmp(key, "ro.product.marketname") == 0) { // ro.product.marketname=Xiaomi 15 Ultra
        hooked_result = env->NewStringUTF("Xiaomi 15 Ultra");
    //屏蔽华为特征
     } else if (strcmp(key, "ro.build.hw_emui_api_level") == 0) { // ro.build.hw_emui_api_level=
        hooked_result = env->NewStringUTF("");
    } else if (strcmp(key, "ro.build.version.emui") == 0) { // ro.build.version.emui=
        hooked_result = env->NewStringUTF("");
    //屏蔽flyme特征
    } else if (strcmp(key, "ro.build.flyme.version") == 0) { // ro.build.flyme.version=
        hooked_result = env->NewStringUTF("");
    } else if (strcmp(key, "ro.flyme.version.id") == 0) { // ro.flyme.version.id=
        hooked_result = env->NewStringUTF("");
    //屏蔽OPPO特征
    } else if (strcmp(key, "ro.build.version.opporom") == 0) { // ro.build.version.opporom=
        hooked_result = env->NewStringUTF("");
    } else if (strcmp(key, "ro.build.version.oplusrom") == 0) { // ro.build.version.oplusrom=
        hooked_result = env->NewStringUTF("");
}

    env->ReleaseStringUTFChars(keyJ, key);
    env->ReleaseStringUTFChars(defJ, def);

    if (hooked_result != nullptr) {
        return hooked_result;
    } else {
        return orig_native_get(env, clazz, keyJ, defJ);
    }
}

void hookBuild(JNIEnv *env) {
    LOGD("hook Build\n");
    jclass build_class = env->FindClass("android/os/Build");
    jstring new_brand = env->NewStringUTF("Xiaomi");
    jstring new_manufacturer = env->NewStringUTF("Xiaomi");
    jstring new_model = env->NewStringUTF("25010PN30C");
    jstring new_device = env->NewStringUTF("xuanyuan");
    jstring new_product = env->NewStringUTF("xuanyuan");

    // Hook BRAND
    jfieldID brand_id = env->GetStaticFieldID(build_class, "BRAND", "Ljava/lang/String;");
    if (brand_id != nullptr) {
        env->SetStaticObjectField(build_class, brand_id, new_brand);
    }

    // Hook MANUFACTURER
    jfieldID manufacturer_id = env->GetStaticFieldID(build_class, "MANUFACTURER", "Ljava/lang/String;");
    if (manufacturer_id != nullptr) {
        env->SetStaticObjectField(build_class, manufacturer_id, new_manufacturer);
    }

    // Hook MODEL
    jfieldID model_id = env->GetStaticFieldID(build_class, "MODEL", "Ljava/lang/String;");
    if (model_id != nullptr) {
        env->SetStaticObjectField(build_class, model_id, new_model);
    }

    // Hook DEVICE
    jfieldID device_id = env->GetStaticFieldID(build_class, "DEVICE", "Ljava/lang/String;");
    if (device_id != nullptr) {
        env->SetStaticObjectField(build_class, device_id, new_device);
    }

    // Hook PRODUCT
    jfieldID product_id = env->GetStaticFieldID(build_class, "PRODUCT", "Ljava/lang/String;");
    if (product_id != nullptr) {
        env->SetStaticObjectField(build_class, product_id, new_product);
    }

    env->DeleteLocalRef(new_brand);
    env->DeleteLocalRef(new_manufacturer);
    env->DeleteLocalRef(new_model);
    env->DeleteLocalRef(new_device);
    env->DeleteLocalRef(new_product);

    LOGD("hook Build done");
}

void hookSystemProperties(JNIEnv *env, zygisk::Api *api) {
    LOGD("hook SystemProperties\n");

    JNINativeMethod targetHookMethods[] = {
            {"native_get", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;",
             (void *) my_native_get},
    };

    api->hookJniNativeMethods(env, "android/os/SystemProperties", targetHookMethods, 1);

    *(void **) &orig_native_get = targetHookMethods[0].fnPtr;

    LOGD("hook SystemProperties done: %p\n", orig_native_get);
}

void Hook::hook() {
    hookBuild(env);
    hookSystemProperties(env, api);
}
