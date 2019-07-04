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

//==============================================================================
WavePoolAudioProcessorEditor::WavePoolAudioProcessorEditor(WavePoolAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p), 
	
	// Initialize handling MIDI Events  
	keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard),
	startTime(Time::getMillisecondCounterHiRes() * 0.001)

	// Start
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
	
	// Get list of MIDI inputs
	setOpaque(true);

	addAndMakeVisible(midiInputListLabel);
	midiInputListLabel.setText("MIDI Input:", dontSendNotification);
	midiInputListLabel.attachToComponent(&midiInputList, true);

	addAndMakeVisible(midiInputList);
	midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
	auto midiInputs = MidiInput::getDevices();
	midiInputList.addItemList(midiInputs, 1);
	midiInputList.onChange = [this] { setMidiInput(midiInputList.getSelectedItemIndex()); };

	// find the first enabled device and use that by default
	for (auto midiInput : midiInputs)
	{
		if (deviceManager.isMidiInputEnabled(midiInput))
		{
			setMidiInput(midiInputs.indexOf(midiInput));
			break;
		}
	}

	// if no enabled devices were found just use the first one in the list
	if (midiInputList.getSelectedId() == 0)
		setMidiInput(0);

	addAndMakeVisible(keyboardComponent);
	keyboardState.addListener(this);

	addAndMakeVisible(midiMessagesBox);
	midiMessagesBox.setMultiLine(true);
	midiMessagesBox.setReturnKeyStartsNewLine(true);
	midiMessagesBox.setReadOnly(true);
	midiMessagesBox.setScrollbarsShown(true);
	midiMessagesBox.setCaretVisible(false);
	midiMessagesBox.setPopupMenuEnabled(true);
	midiMessagesBox.setColour(TextEditor::backgroundColourId, Colour(0x32ffffff));
	midiMessagesBox.setColour(TextEditor::outlineColourId, Colour(0x1c000000));
	midiMessagesBox.setColour(TextEditor::shadowColourId, Colour(0x16000000));
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
	g.setColour(Colours::black);
	// set the font size and draw text to the screen
	g.setFont(15.0f);
	g.drawFittedText("WavePool", 0, 0, getWidth(), 30, Justification::centred, 1);
	g.setColour(Colours::darkblue);
	g.setFont(14.0f);
	g.drawText("Knob lmao", getLocalBounds(), Justification::centredRight, true);
	/*File f = "Logo.png";
	Image img = ImageFileFormat::loadFrom(f);
	g.drawImageAt(img, 0, 100, false);*/
}

void WavePoolAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..

	// sets the position and size of the slider with arguments (x, y, width, height)
	midiVolume.setBounds(40, 30, 20, getHeight() - 60);

	recordButton.setBounds(100, 100, 100, 100);

	auto area = getLocalBounds();

	midiInputList.setBounds(area.removeFromTop(36).removeFromRight(getWidth() - 150).reduced(8));
	keyboardComponent.setBounds(area.removeFromTop(80).reduced(8));
	midiMessagesBox.setBounds(area.reduced(8));
}

void WavePoolAudioProcessorEditor::buttonClicked(Button* button) {
	std::cout << "reached";
	recordButton.setButtonText("Clicked");
	if (SP->IsConnected()) {
		Sleep(1000);
		for (int i = 0; i < 17; i++) {
			readResult = SP->ReadData(incomingData, dataLength);
			// printf("Bytes read: (0 means no data available) %i\n", readResult);
			incomingData[readResult] = 0;
			printf("%s\n", incomingData);
			int row = 0;
			int z = 0;
			while (z < 65) {
				if (incomingData[i] != ',') {
					raw[row][i] += incomingData[z];
				}
				else {
					z++;
					raw[row][i] += incomingData[z];
				}
				z++;
			}
			Sleep(500);
		}
		recordButton.setButtonText("Record");
	}
	else {
		recordButton.setButtonText("N/A");
	}
}

void WavePoolAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	processor.noteOnVel = midiVolume.getValue();
}

