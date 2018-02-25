#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
extern "C"
JNIEXPORT jstring
JNICALL
Java_com_lyh_nkddemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



extern "C"
JNIEXPORT jstring JNICALL
//在C里更新java参数
Java_com_lyh_nkddemo_MainActivity_upDateName(JNIEnv *env, jobject instance) {
    //获取MainActivity
    jclass objectClass = env->GetObjectClass(instance);
    //获取id  
    jfieldID name_id = env->GetFieldID(objectClass, "name", "Ljava/lang/String;");

    //获得字段 
    jstring name = (jstring)env->GetObjectField(instance, name_id);

    char  *char_name = (char *) env->GetStringUTFChars(name, NULL);
    
    char text[20]="lisi";
    //拼接 
    char *string = strcat(char_name, text);

    return env->NewStringUTF(string);
}

extern "C"
JNIEXPORT jstring JNICALL
    //调用 java方法
    Java_com_lyh_nkddemo_MainActivity_getMethod(JNIEnv *env, jobject instance) {

    jclass objectClass = env->GetObjectClass(instance);

    //如果是静态方法 用env->GetStaticMethodID()+env->CallStaticObjectMethod()
    jmethodID methodID = env->GetMethodID(objectClass, "getName", "()Ljava/lang/String;");

    jstring string = (jstring)env->CallObjectMethod(instance, methodID);

    char  *char_name = (char *) env->GetStringUTFChars(string, NULL);

    return env->NewStringUTF(char_name);
}
//首先将a强制转换成指向整数的指针，读取指针对应的整数（数据）
int compare(const void* a, const void* b){
    return (*(int *)a-*(int *)b) ;
};

extern "C"
JNIEXPORT void JNICALL
Java_com_lyh_nkddemo_MainActivity_getArray(JNIEnv *env, jobject instance, jintArray array_) {
    jint *array = env->GetIntArrayElements(array_, NULL);
    //获取数组长度
    jsize size = env->GetArrayLength(array_);
    //需要 <stdlib.h> 头文件
    //void qsort(void* __base, size_t __nmemb, size_t __size, int (*__comparator)(const void* __lhs, const void* __rhs));
    // sizeof(int) 数组所用字节数
    qsort(array,size,sizeof(int),compare);
    //释放掉array
    env->ReleaseIntArrayElements(array_, array, 0);
}
//在JNI里面规范了三种引用：局部引用（local Reference）,全局引用 （Global reference）,
//弱全局引用（（Weak Global Reference）相当于java里的弱引用,更容易被回收的对象，
// 在使用的时候才去获取，解决android内存泄露问题，bitmap优化等..）

// 局部引用；通过 NewLocalRef和各种jni接口创建的 （FindClass,NewObject,GetObjectClass,和NewCharArray等）。
//会阻止GC回收所引用的对象，不在本地函数中跨函数使用，不能跨线程使用，函数返回后局部引用的对象会被jvm虚拟机自动释放，
// 或者手动调用DeleteLocalRef释放掉


//全局引用：多个方法之间 “共存”变量
//创建—》访问—》释放 手动控制内存使用
//调用NewGlobalRef基于局部引用创建，会阻止GC回收所引用的对象，可以跨方法，夸线程使用
//JVM虚拟机不会自动释放，必须调用DeleteLocalRef 手动释放

//弱全局引用：调用NewWeakGlobalRef基于局部引用或全局引用创建，不会阻止GC回收所引用的对象，
// 可以跨方法、跨线程使用。引用不会自动释放，在JVM认为应该回收它的时候（比如内存紧张的时候）
// 进行回收而被释放。或调用DeleteWeakGlobalRef手动释放。
extern "C"
JNIEXPORT void JNICALL
Java_com_lyh_nkddemo_MainActivity_getlocalReference(JNIEnv *env, jobject instance) {
    //模拟循环 
    for(int i=0;i<100;i++){
        jclass jclass = env->FindClass("java/util/Data"); 

        jobject object = env->NewObject(jclass, env->GetMethodID(jclass, "<init>", "()V"));

        env->DeleteLocalRef(object);
    }

}