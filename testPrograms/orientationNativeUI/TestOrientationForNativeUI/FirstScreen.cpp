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

/**
 * @file FirstScreen.cpp
 * @author Bogdan Iusco
 *
 * @brief Screen used for setting supported screen orientations.
 */

#define SCREEN_TITLE "Set orientation"

#define PORTRAIT_LABEL_TEXT "Portrait(SENSOR based)"
#define PORTRAIT_UP_LABEL_TEXT "Portrait Up"
#define PORTRAIT_UPSIDE_DOWN_LABEL_TEXT "Portrait upside down"
#define LANDSCAPE_LEFT_LABEL_TEXT "Landscape left"
#define LANDSCAPE_RIGHT_LABEL_TEXT "Landscape right"
#define LANDSCAPE_LABEL_TEXT "Landscape(SENSOR based)"
#define DYNAMIC_LABEL_TEXT "Dynamic(SENSOR based)"
#define ORIENTATION_LABEL "Orientation:"
#define ORIENTATION_PORTRAIT "Portrait"
#define ORIENTATION_PORTRAIT_UPSIDE_DOWN "Portrait upside down"
#define ORIENTATION_LANDSCAPE_LEFT "Landscape left"
#define ORIENTATION_LANDSCAPE_RIGHT "Landscape right"

#define SCREEN_ORIENTATION_LANDSCAPE_STRING "Landscape"
#define SCREEN_ORIENTATION_PORTRAIT_STRING "Portrait"
#define SCREEN_ORIENTATION_DYNAMIC_STRING "Dynamic (sensor based)"

#define SCREEN_ORIENTATION_ERROR "Event received invalid orientation value!!!"

#include <conprint.h>
#include <maapi.h>

#include "FirstScreen.h"

namespace OrientationTest
{
	/**
	 * Constructor.
	 */
	FirstScreen::FirstScreen() :
		Screen(),
		mSetOrientationBtn(NULL),
		mListView(NULL),
		mPortraitCheckBox(NULL),
		mPortraitUpsideDownCheckBox(NULL),
		mLandscapeLeftCheckBox(NULL),
		mLandscapeRightCheckBox(NULL),
		mPortraitUpCheckBox(NULL),
		mLandscapeCheckBox(NULL),
		mDynamicCheckBox(NULL),
		mOrientationLabel(NULL),
		mSetOrientationDescriptionLabel(NULL),
		mSupportedOrientations(0)
	{
		this->setTitle(SCREEN_TITLE);

		createMainLayout();

		mPortraitUpCheckBox->setState(true);
		addScreenListener(this);
		mSetOrientationBtn->addButtonListener(this);

		// By default it's portrait.
		mOrientationLabel->setText(PORTRAIT_UP_LABEL_TEXT);
	}

	/**
	 * Destructor.
	 */
	FirstScreen::~FirstScreen()
	{
		removeScreenListener(this);
		mSetOrientationBtn->removeButtonListener(this);
	}

	/**
	 * Create a new horizontal layout.
	 * Will contain a label and a check box.
	 * @param label The given label.
	 * @param checkBox The given check box.
	 * @return The new created horizontal layout.
	 */
	HorizontalLayout* FirstScreen::createRow(Label* label, CheckBox* checkBox)
	{
		HorizontalLayout* hLayout = new HorizontalLayout();
		hLayout->wrapContentVertically();
		hLayout->addChild(label);
		if (checkBox)
		{
			HorizontalLayout* space = new HorizontalLayout();
			space->setWidth(10);
			hLayout->addChild(space);
			hLayout->addChild(checkBox);
		}
		return hLayout;
	}

	ListViewItem* FirstScreen::createItem(Label* label, CheckBox* checkBox)
	{
		HorizontalLayout* hLayout = new HorizontalLayout();
		hLayout->wrapContentVertically();
		hLayout->addChild(label);
		if (checkBox)
		{
			HorizontalLayout* space = new HorizontalLayout();
			space->setWidth(10);
			hLayout->addChild(space);
			hLayout->addChild(checkBox);
		}
		ListViewItem* item = new ListViewItem();
		item->addChild(hLayout);
		return item;
	}

	/**
	 * Creates and adds main layout to the screen.
	 */
	void FirstScreen::createMainLayout()
	{
		// Create and add the main layout to the screen.
		VerticalLayout* mainLayout = new VerticalLayout();
		Screen::setMainWidget(mainLayout);

		// Add widgets for displaying the current orientation.
		HorizontalLayout* hLayout = new HorizontalLayout();
		hLayout->wrapContentVertically();
		Label* label = new Label();
		label->setText(ORIENTATION_LABEL);
		hLayout->addChild(label);
		mOrientationLabel = new Label();
		hLayout->addChild(mOrientationLabel);
		mainLayout->addChild(hLayout);

		mListView = new ListView();
		mainLayout->addChild(mListView);
		// Add widgets for enabling/disabling sensor portrait mode.
		label = new Label();
		label->setText(PORTRAIT_LABEL_TEXT);
		mPortraitCheckBox = new CheckBox();
		mListView->addChild(createItem(label, mPortraitCheckBox));

		HorizontalLayout* pLayout = new HorizontalLayout();
		pLayout->wrapContentVertically();
		// Add widgets for enabling/disabling portrait Up mode.
		label = new Label();
		label->setText(PORTRAIT_UP_LABEL_TEXT);
		mPortraitUpCheckBox = new CheckBox();
		mListView->addChild(createItem(label, mPortraitUpCheckBox));

		// Add widgets for enabling/disabling portrait upside down mode.
		label = new Label();
		label->setText(PORTRAIT_UPSIDE_DOWN_LABEL_TEXT);
		mPortraitUpsideDownCheckBox = new CheckBox();
		mListView->addChild(createItem(label, mPortraitUpsideDownCheckBox));

		// Add widgets for enabling/disabling sensor landscape mode.
		label = new Label();
		label->setText(LANDSCAPE_LABEL_TEXT);
		mLandscapeCheckBox = new CheckBox();
		mListView->addChild(createItem(label, mLandscapeCheckBox));

		HorizontalLayout* lLayout = new HorizontalLayout();
		lLayout->wrapContentVertically();
		// Add widgets for enabling/disabling landscape left mode.
		label = new Label();
		label->setText(LANDSCAPE_LEFT_LABEL_TEXT);
		mLandscapeLeftCheckBox = new CheckBox();
		mListView->addChild(createItem(label, mLandscapeLeftCheckBox));

		// Add widgets for enabling/disabling landscape right mode.
		label = new Label();
		label->setText(LANDSCAPE_RIGHT_LABEL_TEXT);
		mLandscapeRightCheckBox = new CheckBox();
		mListView->addChild(createItem(label, mLandscapeRightCheckBox));

		// Add widgets for enabling/disabling sensor mode.
		label = new Label();
		label->setText(DYNAMIC_LABEL_TEXT);
		mDynamicCheckBox = new CheckBox();
		mListView->addChild(createItem(label, mDynamicCheckBox));

		mSetOrientationBtn = new Button();
		mSetOrientationBtn->setText("Apply selected supported orientations");
		mSetOrientationBtn->setFontColor(0xFF0000);
		mainLayout->addChild(mSetOrientationBtn);
	}

	void FirstScreen::addOrientationFlag(int orientation)
	{
		if (mSupportedOrientations == 0)
		{
			mSupportedOrientations = orientation;
		}
		else
		{
			mSupportedOrientations |= orientation;
		}
	}

    /**
     * This method is called if the touch-up event was inside the
     * bounds of the button.
     * Platform: iOS, Android, Windows Phone.
     * @param button The button object that generated the event.
     */
    void FirstScreen::buttonClicked(Widget* button)
    {
		if (mSetOrientationBtn == button)
		{
			if( (mDynamicCheckBox->isChecked() ) ||
				( mLandscapeCheckBox->isChecked() && mPortraitCheckBox->isChecked() ))
			{
				mSupportedOrientations = MA_SCREEN_ORIENTATION_DYNAMIC;
			}
			if (mPortraitCheckBox->isChecked())
			{
				addOrientationFlag(MA_SCREEN_ORIENTATION_PORTRAIT);
			}
			if (mLandscapeCheckBox->isChecked())
			{
				addOrientationFlag(MA_SCREEN_ORIENTATION_LANDSCAPE);
			}
			if (mPortraitUpCheckBox->isChecked())
			{
				addOrientationFlag(MA_SCREEN_ORIENTATION_PORTRAIT_UP);
			}
			if (mPortraitUpsideDownCheckBox->isChecked())
			{
				addOrientationFlag(MA_SCREEN_ORIENTATION_PORTRAIT_UPSIDE_DOWN);
			}
			if (mLandscapeLeftCheckBox->isChecked())
			{
				addOrientationFlag(MA_SCREEN_ORIENTATION_LANDSCAPE_LEFT);
			}
			if(mLandscapeRightCheckBox->isChecked())
			{
				addOrientationFlag(MA_SCREEN_ORIENTATION_LANDSCAPE_RIGHT);
			}

			int result = maScreenSetSupportedOrientations(mSupportedOrientations);
			printf("FirstScreen: result maScreenSetSupportedOrientations = %d",
				result);
			mSupportedOrientations = 0;
		}

    }

	/**
	 * Changes the screen orientation bit mask.
	 * @param cond If true, the orientation flag will be added to the screen
	 * orientation bit mask, otherwise the flag is removed.
	 * @param orientation Orientation value that is needed to be add/removed from
	 * bit mask. Must be one of the MA_SCREEN_ORIENTATION constants.
	 * @param checkBox If the bit mask value will be zero after removing the
	 * orientation value than the checkBox will be set to checked.
	 */
	void FirstScreen::changeOrientationBitmask(const bool cond,
		const int orientation,
		CheckBox* checkBox)
	{
		if (cond)
		{
			mSupportedOrientations = mSupportedOrientations | orientation;
		}
		else
		{
			mSupportedOrientations = mSupportedOrientations & ~orientation;
		}

		if (0 == mSupportedOrientations)
		{
			mSupportedOrientations = orientation;
			checkBox->setState(true);
		}
	}

	/**
	 * @deprecated: Use addScreenListener(ScreenListener*) instead.
	 * Called after the screen has finished rotating.
	 * Subclasses may override this method to perform additional actions
	 * after the rotation.
	 */
	void FirstScreen::orientationDidChange()
	{
		printf("FIRST Screen: orientation DID Changed event came from TabScreen ");
	}

	/**
	 * Called after the screen has finished rotating.
	 * Subclasses may override this method to perform additional actions
	 * after the rotation.
	 * @param screenOrientation The new screen orientation.
	 */
	void FirstScreen::orientationChanged(Screen* screen, int screenOrientation)
	{
		printf("FIRST Screen: orientationChanged to: %d", screenOrientation);
		MAUtil::String orientationText;
		switch (screenOrientation)
		{
			case MA_SCREEN_ORIENTATION_PORTRAIT_UP:
				orientationText = PORTRAIT_UP_LABEL_TEXT;
				break;
			case MA_SCREEN_ORIENTATION_PORTRAIT_UPSIDE_DOWN:
				orientationText = ORIENTATION_PORTRAIT_UPSIDE_DOWN;
				break;
			case MA_SCREEN_ORIENTATION_LANDSCAPE_LEFT:
				orientationText = ORIENTATION_LANDSCAPE_LEFT;
				break;
			case MA_SCREEN_ORIENTATION_LANDSCAPE_RIGHT:
				orientationText = ORIENTATION_LANDSCAPE_RIGHT;
				break;
		}

		int currentOrientation = maScreenGetCurrentOrientation();
		printf("FirstScreen::maScreenGetCurrentOrientation result = %d",
				currentOrientation);
		if (currentOrientation == screenOrientation )
		{
			mOrientationLabel->setText(orientationText);
		}
		else
		{
			mOrientationLabel->setText(SCREEN_ORIENTATION_ERROR);
		}
	}

} // namespace OrientationTest
