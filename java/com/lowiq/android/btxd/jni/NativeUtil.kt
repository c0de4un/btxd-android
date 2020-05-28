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
// PACKAGE
// ===========================================================

package com.lowiq.android.btxd.jni

// ===========================================================
// IMPORTS
// ===========================================================

import android.content.res.AssetManager
import androidx.annotation.Keep
import com.lowiq.android.btxd.activity.MainActivity
import java.io.File

// ===========================================================
// TYPES
// ===========================================================

/**
 * NativeUtil - interactс with Native (NDK, C++) APIs.
 *
 * @version 0.1
 **/
object NativeUtil
{

    // -----------------------------------------------------------

    // ===========================================================
    // FIELDS
    // ===========================================================

    /** MainActivity **/
    private var mActivity: MainActivity? = null

    /** Native Library Loaded Flag **/
    private var LIB_LOADED: Boolean = false

    // ===========================================================
    // GETTERS & SETTERS
    // ===========================================================

    /**
     * Initialize by setting Activity instance.
     **/
    fun Init( pActivity: MainActivity? )
    { mActivity = pActivity }

    // ===========================================================
    // METHODS
    // ===========================================================

    /**
     * Terminate/Stop
    **/
    fun Terminate()
    {  mActivity = null  }

    /**
     * Load Native Shared Library<br/>
     */
    init
    {
        //Load Native Library
        if ( !LIB_LOADED)
        {
            //Load Library
            System.loadLibrary( "btxdandroid-lib" )

            //Set Flag
            LIB_LOADED = true
        }

        //GC
        System.gc( )
    }

    /**
     * Called from Native Code to report about exception <br/>
     * <b>!</b> Not Thread-Safe <br/>
     * App should close using ui/main thread <br/>
     */
    @Keep
    @JvmStatic
    fun handleNativeError( errMsg: String )
    {
        //Stop Activity
        mActivity?.onError( errMsg )
    }

    /**
     * Called when Native Code need instance of AssetManager
     *  for specific thread
     *  <b> Called from any thread </b>
     */
    @Keep
    @JvmStatic
    fun getAssetManager( ) : AssetManager?
    {
        //Return AssetManager
        return( mActivity!!.applicationContext.assets )
    }

    /**
     * Called from Native Code to retrieve
     *  path/uri to external storage for files
     * Can be called from any thread
     */
    @Keep
    @JvmStatic
    fun getExternalStoragePath( ) : String?
    {
        //Get File for external storage path for this app
        val externalDir: File? = mActivity?.getExternalFilesDir( null )

        //If external storage not available (removed, not mounted etc)
        if ( externalDir == null || !externalDir.exists( ) )
        {//Can't get external storage device path
            //Local Storage with private access
            val dataDir: File? = mActivity?.getDir( "data", 0 )

            //Return path to local storage dir
            return if ( dataDir != null && dataDir.exists( ) )
                ( dataDir.absolutePath )
            else
                ( "data" )
        }

        return( externalDir.absolutePath )
    }

    /**
     * Called from Native Code to retrieve
     *  path/uri to local (default data dir) storage for files
     * Can be called from any thread
     */
    @Keep
    @JvmStatic
    fun getStoragePath( ) : String?
    {
        //Local Storage with private access
        val dataDir: File? = mActivity?.getDir( "data", 0 )

        //Return path to local storage dir
        return if ( dataDir != null && dataDir.exists( ) )
            ( dataDir.absolutePath )
        else
            ( "data" )
    }

    /**
     * Called from Native Code to request application to stop/finish
     * ! Not Thread-Safe !
     * App should finish using UI-Thread
     */
    @Keep
    @JvmStatic
    fun onStopRequest( )
    {
        //Finish Activity
        if ( mActivity?.isFinishing == false )
            mActivity?.finish( )
    }

    /**
     * Sending restore state signal to Native Code
     * Useful to restore small amount of data from string,
     *  called fom UI (main) Thread
     */
    @Keep
    external fun onRestoreState( savedData : String )

    /**
     * Sending Pause-Signal to Native Code
     * Used to inform Native Code that app is paused
     * Not Thread-Safe, No guarantee that called only from ui/main thread
     */
    @Keep
    external fun onPause( )

    /**
     * Sending save state signal to Native Code
     * Useful to save small amount of data in string-format,
     *  called from activity #onSaveInstanceState()
     *  from UI (main) Thread
     */
    @Keep
    external fun onSaveState( ) : String

    /**
     * Sending Resume-Signal to Native Code
     * Used to inform Native Code that app is resumed from pause-state
     * Not Thread-Safe, No guarantee that called only from ui/main thread
     */
    @Keep
    external fun onResume( )

    /**
     * Sending Stop-Signal to Native Code
     * Used to inform Native Code that app is closing/stopping
     * Not Thread-Safe, No guarantee that called only from ui/main thread
     */
    @Keep
    external fun onStop( )

    /**
     * Initializing engine<br/>
     * Native-C++ Library Method<br/>
     * Called when OpenGL ES Surface is ready and matching EGL-Configuration found<br/>
     * Called every time when OpenGL ES-Context created/restored<br/>
     * Called from Android GL-Thread<br/>
     * @param pWidth View Width
     * @param pHeight View Height
     */
    @Keep
    external fun glInit( pWidth: Int, pHeight: Int )

    /**
     * Draw with OpenGL ES<br/>
     * Native-C++ Library Method<br/>
     * Called every time OpenGL ES draws<br/>
     * Called from Android GL-Thread<br/>
     */
    @Keep
    external fun glStep( )

    // -----------------------------------------------------------

}

// -----------------------------------------------------------
