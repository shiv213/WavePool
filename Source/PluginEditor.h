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

class WavePoolAudioProcessorEditor : public AudioProcessorEditor, private Slider::Listener, private TextButton::Listener, private ComboBox::Listener, 	public MidiInputCallback, public MidiKeyboardStateListener//, public Component
{
public:
	WavePoolAudioProcessorEditor(WavePoolAudioProcessor&);
	~WavePoolAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	void recordPressed(TextButton* button);

	// Start listening to MIDI Device 
	

	// Handling external MIDI input
	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
	{
		const ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, true);
		keyboardState.processNextMidiEvent(message);
		//postMessageToList(message, source->getName());
	}

	void logMessage(const String& m)
	{
		midiMessagesBox.moveCaretToEnd();
		midiMessagesBox.insertTextAtCaret(m + newLine);
	}
	void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override
	{
		if (!isAddingFromMidiInput)
		{
			auto m = MidiMessage::noteOn(midiChannel, midiNoteNumber, velocity);
			m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
			postMessageToList(m, "On-Screen Keyboard");
		}
	}
	void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override
	{
		if (!isAddingFromMidiInput)
		{
			auto m = MidiMessage::noteOff(midiChannel, midiNoteNumber);
			m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
			postMessageToList(m, "On-Screen Keyboard");
		}
	}
	// This is used to dispach an incoming message to the message thread
	class IncomingMessageCallback : public CallbackMessage
	{
	public:
		IncomingMessageCallback(WavePoolAudioProcessorEditor* o, const MidiMessage& m, const String& s)
			: owner(o), message(m), source(s)
		{}

		void messageCallback() override
		{
			if (owner != nullptr)
				owner->addMessageToList(message, source);
		}

		Component::SafePointer<WavePoolAudioProcessorEditor> owner;
		MidiMessage message;
		String source;
	};
	///* maybe unnecessary, lots of errors
	// Post  Message to list
	void postMessageToList(const MidiMessage& message, const String& source)
	{
		(new IncomingMessageCallback(this, message, source))->post();
	}

	// Display Messages
	void addMessageToList(const MidiMessage& message, const String& source)
	{
		auto time = message.getTimeStamp() - startTime;
		auto hours = ((int)(time / 3600.0)) % 24;
		auto minutes = ((int)(time / 60.0)) % 60;
		auto seconds = ((int)time) % 60;
		auto millis = ((int)(time * 1000.0)) % 1000;
		auto timecode = String::formatted("%02d:%02d:%02d.%03d",
			hours,
			minutes,
			seconds,
			millis);
		auto description = getMidiMessageDescription(message);
		String midiMessageString(timecode + "  -  " + description + " (" + source + ")"); // [7]
		logMessage(midiMessageString);
		//*/
	}
	static String getMidiMessageDescription(const MidiMessage& m)
	{
		if (m.isNoteOn())           return "Note on " + MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3);
		if (m.isNoteOff())          return "Note off " + MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3);
		if (m.isProgramChange())    return "Program change " + String(m.getProgramChangeNumber());
		if (m.isPitchWheel())       return "Pitch wheel " + String(m.getPitchWheelValue());
		if (m.isAftertouch())       return "After touch " + MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3) + ": " + String(m.getAfterTouchValue());
		if (m.isChannelPressure())  return "Channel pressure " + String(m.getChannelPressureValue());
		if (m.isAllNotesOff())      return "All notes off";
		if (m.isAllSoundOff())      return "All sound off";
		if (m.isMetaEvent())        return "Meta event";

		if (m.isController())
		{
			String name(MidiMessage::getControllerName(m.getControllerNumber()));

			if (name.isEmpty())
				name = "[" + String(m.getControllerNumber()) + "]";

			return "Controller " + name + ": " + String(m.getControllerValue());
		}

		return String::toHexString(m.getRawData(), m.getRawDataSize());
	}
	void setMidiInput(int index)
	{
		auto list = MidiInput::getDevices();
		deviceManager.removeMidiInputCallback(list[lastInputIndex], this);
		auto newInput = list[index];
		if (!deviceManager.isMidiInputEnabled(newInput))
			deviceManager.setMidiInputEnabled(newInput, true);
		deviceManager.addMidiInputCallback(newInput, this);
		midiInputList.setSelectedId(index + 1, dontSendNotification);
		lastInputIndex = index;
	}

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

	// Handling MIDI Events Variables
	AudioDeviceManager deviceManager;           // [1] 
	ComboBox midiInputList;                     // [2]
	Label midiInputListLabel;
	int lastInputIndex = 0;                     // [3]
	bool isAddingFromMidiInput = false;         // [4]
	MidiKeyboardState keyboardState;            // [5]
	MidiKeyboardComponent keyboardComponent;    // [6]
	TextEditor midiMessagesBox;
	double startTime;/**
	[1]: We use the AudioDeviceManager class to find which MIDI input devices are enabled.
	[2]: We display the names of the MIDI input devices in this combo-box for the user to select.
	[3]: This is used to de-register a previously selected MIDI input when the user selects a different input.
	[4]: This flag is used to indicate that MIDI data is arriving from an external source, rather than mouse-clicks on the on-screen keyboard.
	[5]: The MidiKeyboardState class keeps track of which MIDI keys are currently held down.
	[6]: This is the on-screen keyboard component.*/

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavePoolAudioProcessorEditor)
};

