/**
 * Copyright © 2020 Denis Z. (code4un@yandex.ru) All rights reserved.
 * Authors: Denis Z. (code4un@yandex.ru)
 * All rights reserved.
 * License: see LICENSE.txt
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must display the names 'Denis Zyamaev' and
 * in the credits of the application, if such credits exist.
 * The authors of this work must be notified via email (code4un@yandex.ru) in
 * this case of redistribution.
 * 3. Neither the name of copyright holders nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// HEADER
#ifndef BT_XD_ANDROID_HPP
#include "BTXDAndroid.hpp"
#endif // !BT_XD_ANDROID_HPP

// DEBUG
#if defined( BT_DEBUG ) || defined( DEBUG )

// Inlude Android Log
#include <android/log.h>

// Include bt::android::AndroidLogger
#ifndef BT_ANDROID_LOGGER_HPP
#include <bt/android/metrics/AndroidLogger.hpp>
#endif // !BT_ANDROID_LOGGER_HPP
#include <bt/android/metrics/AndroidLogger.hpp>
#endif
// DEBUG

// ===========================================================
// IMPLEMENTATIONS
// ===========================================================

extern "C"
{

    JNIEXPORT void JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_onRestoreState(JNIEnv *env, jobject thiz, jstring saved_data)
    {// @TODO BTXDAndroid::onRestoreState
#ifdef DEBUG
        bt_Log::Print( "BTXDAndroid::onRestoreState", bt_ELogLevel::Info );
#endif
    }

    JNIEXPORT void JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_onPause(JNIEnv *env, jobject thiz)
    {// @TODO BTXDAndroid::onPause
#ifdef DEBUG
        bt_Log::Print( "BTXDAndroid::onPause", bt_ELogLevel::Info );
#endif
    }

    JNIEXPORT jstring JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_onSaveState(JNIEnv *env, jobject thiz)
    {// @TODO BTXDAndroid::onSaveState
#ifdef DEBUG
        bt_Log::Print( "BTXDAndroid::onSaveState", bt_ELogLevel::Info );
#endif
        // State Data
        jstring stateData = nullptr;

        // Save small game data

        // Return State Data
        return (stateData);
    }

    JNIEXPORT void JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_onResume(JNIEnv *env, jobject thiz)
    {// @TODO BTXDAndroid::onResume
#ifdef DEBUG
        if ( !bt_Log::isInitialized() )
            bt_Log::Initialize( new bt_AndroidLogger( "BattleTanksXD" ) );

        bt_Log::Print( "BTXDAndroid::onResume", bt_ELogLevel::Info );
#endif
    }

    JNIEXPORT void JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_onStop(JNIEnv *env, jobject thiz)
    {// @TODO BTXDAndroid::onStop
#ifdef DEBUG
        bt_Log::Print( "BTXDAndroid::onStop", bt_ELogLevel::Info );

        bt_Log::Terminate();
#endif

    }

    JNIEXPORT void JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_glInit(JNIEnv *env, jobject thiz, jint pWidth, jint pHeight)
    {// @TODO BTXDAndroid::glInit
#ifdef DEBUG
        if ( !bt_Log::isInitialized() )
            bt_Log::Initialize( new bt_AndroidLogger( "BattleTanksXD" ) );

        bt_Log::Print( "BTXDAndroid::glInit", bt_ELogLevel::Info );
#endif
    }

    JNIEXPORT void JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_glStep(JNIEnv *env, jobject thiz)
    {// @TODO BTXDAndroid::glStep

    }

};

// -----------------------------------------------------------
