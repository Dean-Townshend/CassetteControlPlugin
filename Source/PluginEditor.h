#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookFeel.h"

#define NUMOFNOTES 

class CassetteControlProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    CassetteControlProcessorEditor (CassetteControlProcessor&);
    ~CassetteControlProcessorEditor() override;


    const int numOfNotes = 12;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


private:

    void sliderValueChanged(juce::Slider* slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboard;
    CassetteControlProcessor& audioProcessor;
    CustLookFeel custLookFeel1;

    std::array<juce::Slider, 12> noteTuneSlider;
    std::array<juce::Label, 12> noteTuneSliderLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CassetteControlProcessorEditor)
};
