#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookFeel.h"

#define NUMOFNOTES 

class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;


    const int numOfNotes = 8;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


private:

    void sliderValueChanged(juce::Slider* slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;
    CustLookFeel custLookFeel1;

    std::array<juce::Slider, 12> noteTuneSlider;
    std::array<juce::Label, 12> noteTuneSliderLabel;

    juce::Slider tuningSlider1;
    juce::Label tuningSlider2Label;

    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
