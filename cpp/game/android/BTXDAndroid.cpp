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

// Include bt::assert
#ifndef BT_CFG_ASSERT_HPP
#include <bt/cfg/bt_assert.hpp>
#endif // !BT_CFG_ASSERT_HPP

// Include Android Log
#include <android/log.h>

// Include bt::android::AndroidLogger
#ifndef BT_ANDROID_LOGGER_HPP
#include <bt/android/metrics/AndroidLogger.hpp>
#endif // !BT_ANDROID_LOGGER_HPP

// Include bt::string
#ifndef BT_STRING_HPP
#include <bt/cfg/bt_string.hpp>
#endif // !BT_STRING_HPP

#endif
// DEBUG

// ===========================================================
// CONSTANTS & FIELDS
// ===========================================================

/** JNI 'NativeUtil' Class-Name **/
static constexpr const char *const JNI_CLASS_NAME = const_cast<char*>( "com/lowiq/android/btxd/jni/NativeUtil" );

/** Global Variables Limit. **/
static constexpr const unsigned char GLOBALS_LIMIT = 8;

/** Java/Kotlin Method Name for Stop-Request. **/
static constexpr const char *const JNI_STOP_METHOD = const_cast<char*>( "onStopRequest" );

/** Render-Thread (main, in case of multi-thread rendering) Name in JVM. **/
static constexpr const char *const RENDER_THREAD_NAME = const_cast<char*>( "render_thread" );

/** AndroidGraphics insatnce. User every frame draw. **/
bt_sptr<bt_AndroidGraphics> mAndroidGraphics(nullptr);

// ===========================================================
// IMPLEMENTATIONS
// ===========================================================

extern "C"
{

    JNIEXPORT void JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_onRestoreState(JNIEnv *env, jobject thiz, jstring saved_data)
    {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
        bt_Log::Print( "BTXDAndroid::onRestoreState", static_cast<bt_uint8_t>( bt_ELogLevel::Info ) );
#endif // DEBUG
    }

    JNIEXPORT void JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_onPause(JNIEnv *env, jobject thiz)
    {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
        bt_Log::Print( "BTXDAndroid::onPause", static_cast<bt_uint8_t>( bt_ELogLevel::Info ) );
#endif // DEBUG

        // Pause Application
        bt_sptr<bt_App> gameApp( bt_App::getInstance() );
        if ( gameApp != nullptr )
            gameApp->Pause();
    }

    JNIEXPORT jstring JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_onSaveState(JNIEnv *env, jobject thiz)
    {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
        bt_Log::Print( "BTXDAndroid::onSaveState", static_cast<bt_uint8_t>( bt_ELogLevel::Info ) );
#endif // DEBUG
        // State Data
        jstring stateData = nullptr;

        // Save small game data

        // Return State Data
        return (stateData);
    }

    JNIEXPORT void JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_onResume(JNIEnv *env, jobject thiz)
    { // Not used, because Resume called from glInit.
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
        if ( !bt_Log::isInitialized() )
            bt_Log::Initialize( new bt_AndroidLogger( "BattleTanksXD" ) );

        bt_Log::Print( "BTXDAndroid::onResume", static_cast<bt_uint8_t>( bt_ELogLevel::Info ) );
#endif // DEBUG

        // Update AndroidGraphics
        bt_sptr<bt_Graphics> graphics = bt_Graphics::getInstance();
        if ( graphics != nullptr )
            mAndroidGraphics = bt_SharedCast<bt_AndroidGraphics, bt_Graphics>( graphics );
    }

    JNIEXPORT void JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_onStop(JNIEnv *env, jobject thiz)
    {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
        bt_Log::Print( "BTXDAndroid::onStop", static_cast<bt_uint8_t>( bt_ELogLevel::Info ) );
#endif // DEBUG

        // Reset AndroidGraphics.
        mAndroidGraphics = nullptr;

        // Stop & Terminate Application (& Game, Engine, Graphics)
        bt_App::Terminate();

#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
        bt_Log::Terminate();
#endif // DEBUG

    }

    JNIEXPORT void JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_glInit(JNIEnv *env, jobject thiz, jint pWidth, jint pHeight)
    {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
        if ( !bt_Log::isInitialized() )
            bt_Log::Initialize( new bt_AndroidLogger( "BattleTanksXD" ) );

        bt_Log::Print( "BTXDAndroid::glInit", static_cast<bt_uint8_t>( bt_ELogLevel::Info ) );
#endif // DEBUG

        try
        {
            // Get Game-Application
            bt_sptr<bt_App> gameApp = bt_App::getInstance();

            // Get JNICache
            bt_sptr<bt_IJNICache> jniCache = bt_JNICache::getInstance();

            // Initialize Game-App instance.
            if ( gameApp == nullptr )
            {

                // JNIAdapter
                if ( !bt_JNIAdapter::isInitialized() )
                {
                    // Initialize AndroidJNIAdapter
                    bt_sptr<bt_IJNIAdapter> jniAdapter = bt_SharedCast<bt_IJNIAdapter, bt_AndroidJNI>( bt_Shared<bt_AndroidJNI>() );
                    bt_JNIAdapter::Initialize( jniAdapter );
                }

                // JNICache
                if ( jniCache == nullptr )
                {
                    // Initialize AndroidJNICache
                    bt_AJNIParams jniParams;
                    jniParams.mGlobalsLimit = GLOBALS_LIMIT;
                    jniParams.mClassName = JNI_CLASS_NAME;
                    jniParams.mRenderThreadName = RENDER_THREAD_NAME;
                    jniParams.mStopMethod = JNI_STOP_METHOD;

                    jniCache = bt_SharedCast<bt_IJNICache, bt_AndroidJNICache>( bt_Shared<bt_AndroidJNICache>(jniParams) );
                    jniCache->addJNIEnv( jniParams.mRenderThreadName, env );
                    bt_JNICache::Initialize( jniCache );
                }

                // Setup AndroidApp params.
                bt_AndroidAppArgs appParams;

                // Create AndroidApp instance.
                gameApp = bt_SharedCast<bt_App, bt_AndroidApp>( bt_Shared<bt_AndroidApp>( appParams ) );
                bt_App::Initialize( gameApp );

#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
                bt_Log::Print( u8"BTXDAndroid::glInit - Application initialized", bt_ELogLevel::Debug );
#endif // DEBUG
            }
            else
            {
                // Update Android JNICache
                jniCache->addJNIEnv( bt_String(RENDER_THREAD_NAME), env ); // Update pointer to JNIEnv for Render-Thread
            }

            // Create new Graphics Settings
            bt_GraphicsSettings settings{ pWidth, pHeight, pWidth, pHeight, 8 };

            // Init Graphics
            bt_sptr<bt_Graphics> graphics = bt_Graphics::getInstance();
            if ( graphics == nullptr )
            {
                mAndroidGraphics = bt_Shared<bt_AndroidGraphics>( settings );
                graphics = bt_Memory::StaticCast<bt_Graphics, bt_AndroidGraphics>( mAndroidGraphics );
                bt_Graphics::Initialize( graphics );
            }

            // Init GLRenderManager
            bt_sptr<bt_RenderManager> renderer( bt_RenderManager::getInstance() );
            if ( renderer == nullptr )
            {
                renderer = bt_SharedCast<bt_RenderManager, bt_GLRenderManager>( bt_Shared<bt_GLRenderManager>() );
                bt_RenderManager ::Initialize( renderer );
            }

            // Init Game
            bt_sptr<bt_Game> game = bt_Game::getInstance();
            if ( game == nullptr )
            {
                game = bt_Memory::StaticCast<bt_Game, lowiq::BTXDGame>( bt_Shared<lowiq::BTXDGame>() );
                bt_Game::Initialize( game );
            }

            // Start/Resume Application
            if ( !gameApp->Start() )
            {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
                bt_Log::Print( u8"BTXDAndroid::glInit - failed to start Application", bt_ELogLevel::Error );
#endif // DEBUG
                // Stop & Terminate
                bt_App::Terminate(); // Calls ActivityStop
            }

            // Update Graphics
            if ( !mAndroidGraphics->onGLSurfaceReady(&settings) )
            {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
                bt_Log::Print( u8"BTXDAndroid::glInit - failed to update Graphics surface", bt_ELogLevel::Error );
#endif // DEBUG

                // Stop & Terminate
                bt_App::Terminate(); // Calls ActivityStop
            }
        }
        catch( const std::exception& pException )
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_String logMsg = u8"BTXDAndroid::glInit: ERROR: ";
            logMsg += pException.what();
            bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

            // Stop & Terminate
            bt_App::Terminate(); // Calls ActivityStop
        }

    }

    JNIEXPORT void JNICALL
    Java_com_lowiq_android_btxd_jni_NativeUtil_glStep(JNIEnv *env, jobject thiz)
    {
        // Guarded-Block
        try
        {
            // Draw Graphics
            if ( mAndroidGraphics != nullptr )
                mAndroidGraphics->onGLSurfaceDraw();
        }
        catch( const std::exception& pException )
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_String logMsg = u8"BTXDAndroid::glStep: ERROR: ";
            logMsg += pException.what();
            bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

            // Stop & Terminate
            bt_App::Terminate(); // Calls ActivityStop
        }
    }

};

// -----------------------------------------------------------
