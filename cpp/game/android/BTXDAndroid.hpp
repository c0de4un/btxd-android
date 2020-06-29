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

#ifndef BT_XD_ANDROID_HPP
#define BT_XD_ANDROID_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Debug
#define BT_DEBUG

// Include JNI
#include <jni.h>

// Android AssetManager
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

// Include ECS
#ifndef BT_ECS_HPP
#include <bt/ecs/ecs.hpp>
#endif // !BT_ECS_HPP

// Include bt::core::ArcadeEngine
#ifndef BT_CORE_ARCADE_ENGINE_HPP
#include <bt/core/engine/ArcadeEngine.hpp>
#endif // !BT_CORE_ARCADE_ENGINE_HPP

// Include lowiq::BTXDGame
#ifndef LOW_IQ_BTXD_CORE_GAME_HPP
#include "../core/game/BTXDGame.hpp"
#endif // !LOW_IQ_BTXD_CORE_GAME_HPP

// Include bt::android::AndroidApplication
#ifndef BT_ANDROID_APPLICATION_HPP
#include <bt/android/app/AndroidApp.hpp>
#endif // !BT_ANDROID_APPLICATION_HPP

// Include bt::android::AndroidJNIAdapter
#ifndef BT_ANDROID_JNI_ADAPTER_HPP
#include <bt/android/jni/AndroidJNIAdapter.hpp>
#endif // !BT_ANDROID_JNI_ADAPTER_HPP

// Include bt::android::AndroidJNICache
#ifndef BT_ANDROID_JNI_CACHE_HPP
#include <bt/android/jni/AndroidJNICache.hpp>
#endif // !BT_ANDROID_JNI_CACHE_HPP

// Include bt::java::JNICache
#ifndef BT_JAVA_JNI_CACHE_HPP
#include <bt/java/jni/JNICache.hpp>
#endif // !BT_JAVA_JNI_CACHE_HPP

// Include bt::java::JNIAdapter
#ifndef BT_JAVA_JNI_ADAPTER_HPP
#include <bt/java/jni/JNIAdapter.hpp>
#endif // !BT_JAVA_JNI_ADAPTER_HPP

// Include bt::android::AndroidGraphics
#ifndef BT_ANDROID_GRAPHICS_HPP
#include <bt/android/graphics/AndroidGraphics.hpp>
#endif // !BT_ANDROID_GRAPHICS_HPP

// Include bt::gl::GLRenderManager
#ifndef BT_GL_RENDER_MANAGER_HPP
#include <bt/gl/render/GLRendererManager.hpp>
#endif // !BT_GL_RENDER_MANAGER_HPP

// DEBUG
#if defined( BT_DEBUG ) || defined( DEBUG )

// Include Android Log
#include <android/log.h>

// Include bt::android::AndroidLogger
#ifndef BT_ANDROID_LOGGER_HPP
#include <bt/android/metrics/AndroidLogger.hpp>
#endif // !BT_ANDROID_LOGGER_HPP

#endif
// DEBUG

// ===========================================================
// TYPES
// ===========================================================


// -----------------------------------------------------------

#endif // !BT_XD_ANDROID_HPP
