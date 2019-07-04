/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "windows.h"
#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"
#include <string>
#include <iostream>

Serial* SP = new Serial("\\\\.\\COM6");

char incomingData[64] = "";
int dataLength = 64;
int readResult = 0;
std::string raw[16][16];
int row = 0;
int col = 0;

//==============================================================================
WavePoolAudioProcessorEditor::WavePoolAudioProcessorEditor(WavePoolAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(600, 400);

	// these define the parameters of our slider object
	midiVolume.setSliderStyle(Slider::LinearBarVertical);
	midiVolume.setRange(0.0, 127.0, 1.0);
	midiVolume.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	midiVolume.setPopupDisplayEnabled(true, false, this);
	midiVolume.setTextValueSuffix(" Volume");
	midiVolume.setValue(1.0);
	// this function adds the slider to the editor
	addAndMakeVisible(&midiVolume);
	// add the listener to the slider
	midiVolume.addListener(this);

	recordButton.setTriggeredOnMouseDown(true);
	recordButton.setButtonText("Record");
	recordButton.addListener(this);
	addAndMakeVisible(&recordButton);

	addAndMakeVisible(&Threshold);
	Threshold.setRange(0.0f, 1.0f, 0.001);
	Threshold.addListener(this);

	addAndMakeVisible(&Mix);
	Mix.setRange(0.0f, 1.0f, 0.001);
	Mix.addListener(this);

	addAndMakeVisible(&mode);
	mode.addItem("Default (Auto)", 1);
	mode.addItem("Sine Wave", 2);
	mode.addItem("Custom Wave", 3);
	mode.setSelectedId(1);
	mode.addListener(this);

}

WavePoolAudioProcessorEditor::~WavePoolAudioProcessorEditor()
{
}

//==============================================================================
void WavePoolAudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	// fill the whole window white
	//g.fillAll(Colours::white);
	// set the current drawing colour to black
	g.setColour(Colours::lightblue);
	// set the font size and draw text to the screen
	g.setFont(15.0f);
	g.drawFittedText("WavePool", 0, 0, getWidth(), 30, Justification::centred, 1);
	//g.setColour(Colours::darkblue);
	//g.setFont(14.0f);
	//g.drawText("Knob lmao", getLocalBounds(), Justification::centredRight, true);
	/*File f = "Logo.png";
	Image img = ImageFileFormat::loadFrom(f);
	g.drawImageAt(img, 0, 100, false);*/
}

void WavePoolAudioProcessorEditor::resized() {
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..

	//FlexBox fb;                                          // [1]
	//fb.flexWrap = FlexBox::Wrap::wrap;                   // [2]
	//fb.justifyContent = FlexBox::JustifyContent::center; // [3]
	//fb.alignContent = FlexBox::AlignContent::center;     // [4]
	//for (auto* b : buttons)                              // [5]
	//	fb.items.add(FlexItem(*b).withMinWidth(50.0f).withMinHeight(50.0f));
	//fb.performLayout(getLocalBounds().toFloat());       // [6]


	// sets the position and size of the slider with arguments (x, y, width, height)
	midiVolume.setBounds(getWidth() - 50, 30, 20, getHeight() - 60);
	recordButton.setBounds(getWidth() / 2 + 75, getHeight() / 2 - 150, 75, 75);
	mode.setBounds(50, 50, 200, 50);
	Threshold.setBounds(50, 100, 200, 50);
	Mix.setBounds(50, 150, 200, 50);

}

void WavePoolAudioProcessorEditor::buttonClicked(Button* button) {
	std::cout << "reached";
	recordButton.setButtonText("Clicked");
	//if (SP->IsConnected()) {
	//	Sleep(1000);
	//	for (int i = 0; i < 17; i++) {
	//		readResult = SP->ReadData(incomingData, dataLength);
	//		// printf("Bytes read: (0 means no data available) %i\n", readResult);
	//		incomingData[readResult] = 0;
	//		printf("%s\n", incomingData);
	//		char* pch;
	//		pch = strtok(incomingData, ",;");
	//		while (pch != NULL) {
	//			printf("\n%s", pch);
	//			raw[row][col] = pch;
	//			row++;
	//			pch = strtok(NULL, ",;");
	//		}
	//		col++;

	//		Sleep(500);
	//	}
	//	recordButton.setButtonText("Record");
	//}
	//else {
	//	recordButton.setButtonText("N/A");
	//}
}

void WavePoolAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	if (&Mix == slider) {
		processor.mix = Mix.getValue();
	}
	if (&Threshold == slider) {
		processor.thresh = Threshold.getValue();
	}
	if (&midiVolume == slider) {
		processor.noteOnVel = midiVolume.getValue();
	}
}

void WavePoolAudioProcessorEditor::comboBoxChanged(ComboBox* changedBox) {
	processor.menuChoice = changedBox->getSelectedId();
}
