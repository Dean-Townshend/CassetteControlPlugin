#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookFeel.h"

class CassetteControlProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    CassetteControlProcessorEditor (CassetteControlProcessor&);
    ~CassetteControlProcessorEditor() override;

    juce::ComponentBoundsConstrainer constrain;

    const int numOfNotes = 12;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


private:

    void setSliderStyle(juce::Slider &slider, juce::Label& label);

    void sliderValueChanged(juce::Slider* slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboard;
    CassetteControlProcessor& audioProcessor;
    CustLookFeel custLookFeel1;

    //Tuning Sliders
    std::array<juce::Slider, 12> noteTuneSlider;
    std::array<juce::Label, 12> noteTuneSliderLabel;

    //Glider Slider
    juce::Slider glideSlider;
    juce::Label glideSliderLabel;

    //Flutter Slider
    juce::Slider minSpeedSlider;
    juce::Label minSpeedSliderLabel;

    //ADSR Sliders
    juce::Slider attackSlider;
    juce::Label attackSliderLabel;
    juce::Slider decaySlider;
    juce::Label decaySliderLabel;
    juce::Slider sustainSlider;
    juce::Label sustainSliderLabel;
    juce::Slider releaseSlider;
    juce::Label releaseSliderLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CassetteControlProcessorEditor)
};
