/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

package com.mosync.nativeui.ui.factories;

import android.app.Activity;
import android.widget.ImageButton;

import com.mosync.nativeui.ui.widgets.ImageButtonWidget;
import com.mosync.nativeui.ui.widgets.Widget;
import com.mosync.nativeui.util.MoSyncSendOnClick;

/**
 * A factory that creates button that is represented by an image, and sets up
 * the default behavior for sending events when clicked.
 *
 * @author fmattias
 */
public class ImageButtonFactory implements AbstractViewFactory
{
	/**
	 * @see AbstractViewFactory.create.
	 */
	@Override
	public Widget create(Activity activity, final int handle)
	{
		ImageButton b = new ImageButton( activity );
		b.setOnClickListener( new MoSyncSendOnClick( handle ) );

		return new ImageButtonWidget( handle, b );
	}
}
