#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_felix_jnidemo_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "hello world from 函数命名规范方式";
    return env->NewStringUTF(hello.c_str());
}


jstring stringFromJNI2(JNIEnv *env, jobject) {
    std::string hello = "hello world from 函数注册方式";
    return env->NewStringUTF(hello.c_str());
}

static int registerNativeMethods(JNIEnv *, const char *, JNINativeMethod *, int);
static int registerNatives(JNIEnv *);

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    jint result = -1;
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4)) {
        goto fail;
    }
    if (registerNatives(env) != JNI_TRUE) {
        goto fail;
    }
    result = JNI_VERSION_1_4;
    fail:
    return result;
}

static JNINativeMethod gMethods[] = {{"stringFromJNI2", "()Ljava/lang/String;", (void *) stringFromJNI2}};

static int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods, int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

static int registerNatives(JNIEnv *env) {
    if (!registerNativeMethods(env, "com/felix/jnidemo/MainActivity", gMethods, sizeof(gMethods) / sizeof(gMethods[0]))) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}