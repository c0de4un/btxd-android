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

package com.lowiq.android.btxd.activity

// ===========================================================
// IMPORTS
// ===========================================================

import android.os.Bundle
import android.view.View
import android.view.Window
import android.view.WindowManager
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.lowiq.android.btxd.jni.NativeUtil
import com.lowiq.android.btxd.view.GLESView

// ===========================================================
// TYPES
// ===========================================================

/**
 * MainActivity - entry point to launch game.
 *
 * Uses surface view to display content.
 * **/
class MainActivity : AppCompatActivity()
{

    // -----------------------------------------------------------

    // ===========================================================
    // FIELDS
    // ===========================================================

    /** GLESView **/
    private var mGLESView: GLESView? = null

    // ===========================================================
    // METHODS
    // ===========================================================

    /**
     * Called when activity creates/restores view.
     *
     * @param savedInstanceState - saved state data.
     * @throws - can throw exception.
     **/
    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate( savedInstanceState )

        //Set Link to this Activity in NativeUtil
        NativeUtil.Init( this )

        //requestWindowFeature( Window.FEATURE_NO_TITLE )
        //window.setFlags( WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN )

        //Create GLRender with Application Context
        if ( mGLESView == null ) mGLESView = GLESView( application )

        //Set ContentView
        setContentView( mGLESView )

        // Get Top-Level Decor-View & Set FullScreen Mode: Immersive (for Games)
        window.decorView.systemUiVisibility =
            View.SYSTEM_UI_FLAG_IMMERSIVE or
            View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY or
            View.SYSTEM_UI_FLAG_LAYOUT_STABLE or
            View.SYSTEM_UI_FLAG_LOW_PROFILE or
            View.SYSTEM_UI_FLAG_FULLSCREEN or
            View.SYSTEM_UI_FLAG_HIDE_NAVIGATION or
            View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
    }

    override fun onPause( )
    {
        super.onPause( )

        //Send Pause-Signal to Native Game
        NativeUtil.onPause( )

        //Pause GL-Thread
        mGLESView?.onPause( )
    }

    override fun onSaveInstanceState( outState: Bundle )
    {
        //Get Data from Native Code
        val nativeState : String = NativeUtil.onSaveState( )

        //Put State Data from Native to Bundle
        outState.putString( "bg_game_native.state", nativeState )

        //Call Super
        super.onSaveInstanceState( outState )
    }

    override fun onResume( )
    {
        super.onResume( )

        //Set Link to this Activity in NativeUtil
        NativeUtil.Init( this )

        //Send Resume-Signal to Native Game
        NativeUtil.onResume( )

        //Resume GL-Thread
        mGLESView?.onResume( )
    }

    override fun onStop( )
    {

        super.onStop( )

        //Set Stop-Signal to Native Game
        NativeUtil.onStop( )

        //Release link to this Activity from NativeUtil
        NativeUtil.Terminate( )

    }

    /**
     * Handles error callback from Native-Code</br>
     * @param errMsg String description of error
     *
     */
    fun onError( errMsg: String )
    {
        //Show Toast
        runOnUiThread {
            Toast.makeText( this, "Game Error ! Sorry\nDetails: $errMsg", Toast.LENGTH_LONG ).show( )

            //Finish Activity
            if ( !isFinishing )
                finish( )
        }
    }

    // -----------------------------------------------------------

}

// -----------------------------------------------------------
