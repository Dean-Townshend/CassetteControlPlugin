#pragma once

#include <JuceHeader.h>
//#include <juce_core/maths/juce_MathsFunctions.h>
//#include <pluginterfaces/base/ftypes.h>

//==============================================================================
/**
*/
class CassetteControlProcessor  : public juce::AudioProcessor
{
public:  
    //==============================================================================
    CassetteControlProcessor();
    ~CassetteControlProcessor() override;

    //Public Variables
    std::array<int, 12> noteTuneMidiVal;
    std::array<int, 12> tempNoteTuneMidiVal;
    juce::ADSR adsr;

    int glideMidiVal, tempGlideMidiVal, flutterMidiVal, tempFlutterMidiVal;


    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CassetteControlProcessor)
};
