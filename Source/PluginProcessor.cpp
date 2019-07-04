/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//juce::StringArray modes = { "Auto", "Sine Wave" };
//==============================================================================
WavePoolAudioProcessor::WavePoolAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	)
#endif
{
	//addParameter(gain = new AudioParameterFloat("gain", "Gain", 0.0f, 1.0f, 0.5f));
	//addParameter(mode = new AudioParameterChoice("mode", "Mode", modes, 0));
}

WavePoolAudioProcessor::~WavePoolAudioProcessor()
{
}

//==============================================================================
const String WavePoolAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool WavePoolAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool WavePoolAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool WavePoolAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double WavePoolAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int WavePoolAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int WavePoolAudioProcessor::getCurrentProgram()
{
	return 0;
}

void WavePoolAudioProcessor::setCurrentProgram(int index)
{
}

const String WavePoolAudioProcessor::getProgramName(int index)
{
	return {};
}

void WavePoolAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void WavePoolAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
}

void WavePoolAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WavePoolAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void WavePoolAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) {
	// FOR GENERIC UI
	/*
	auto* channeldataL = buffer.getWritePointer(0);
	auto* channeldataR = buffer.getWritePointer(1);

	float gSlider = gain->get();

	for (int i = 0; i < buffer.getNumSamples(); i++) {
		auto inputL = channeldataL[i];
		auto inputR = channeldataR[i];

		inputL = inputL * gSlider;
		inputR = inputR * gSlider;

		channeldataL[i] = inputL;
		channeldataR[i] = inputR;
	}
	*/
	for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
		auto* channelData = buffer.getWritePointer(channel);

		for (int i = 0; i < buffer.getNumSamples(); ++i) {
			auto input = channelData[i];
			auto cleanOut = channelData[i];

			// Default (Auto)
			if (menuChoice == 1) {
				input = input;
			}

			// Sine Wave
			if (menuChoice == 2) {
				if (input > thresh) {
					input = 1.0f - expf(-input);
				}
				else {
					input = -1.0f + expf(input);
				}
			}

			// Custom Option?
			if (menuChoice == 3) {
				if (input > thresh) {
					input = input;
				}
				else {
					input = 0;
				}
			}

			channelData[i] = ((1 - mix) * cleanOut) + (mix * input);
		}
	}
}

//==============================================================================
bool WavePoolAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* WavePoolAudioProcessor::createEditor()
{
	return new WavePoolAudioProcessorEditor(*this);
	// return new GenericAudioProcessorEditor(this);
}

//==============================================================================
void WavePoolAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void WavePoolAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new WavePoolAudioProcessor();
}
