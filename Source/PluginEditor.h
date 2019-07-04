/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WavePoolAudioProcessorEditor : public AudioProcessorEditor, private Slider::Listener, private TextButton::Listener, private ComboBox::Listener
{
public:
	WavePoolAudioProcessorEditor(WavePoolAudioProcessor&);
	~WavePoolAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	void recordPressed(TextButton* button);

private:
	void sliderValueChanged(Slider* slider) override;
	void buttonClicked(Button* button) override;
	void comboBoxChanged(ComboBox* changedBox) override;
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	WavePoolAudioProcessor& processor;

	Slider midiVolume;
	TextButton recordButton;
	ComboBox mode;
	Slider Threshold;
	Slider Mix;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavePoolAudioProcessorEditor)
};
