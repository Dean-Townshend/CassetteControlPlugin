#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
CassetteControlProcessorEditor::CassetteControlProcessorEditor(CassetteControlProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), keyboard(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)

{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(1000, 300);

    for (int i = 0; i < numOfNotes; i++)
    {
        //Tuning sliders
        noteTuneSlider[i].addListener(this);
        noteTuneSlider[i].setLookAndFeel(&custLookFeel1);
        noteTuneSlider[i].setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        noteTuneSlider[i].setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
        noteTuneSlider[i].setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::slategrey);
        noteTuneSlider[i].setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::darkslategrey);
        noteTuneSlider[i].setRange(0, 127, 1);
        //tuningSlider.setTextValueSuffix(" ");
        noteTuneSlider[i].setValue(0.0);
        //custLookFeel1.hello = 1;

        //Tuning slider labels
        noteTuneSliderLabel[i].setText("Note " + (juce::String)(i + 1), juce::dontSendNotification);
        noteTuneSliderLabel[i].setColour(juce::Label::textColourId, juce::Colours::darkslategrey);

        addAndMakeVisible(noteTuneSlider[i]);
        addAndMakeVisible(noteTuneSliderLabel[i]);
    }

    //addAndMakeVisible(keyboard);
}

CassetteControlProcessorEditor::~CassetteControlProcessorEditor()
{
}

//==============================================================================
void CassetteControlProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
}

void CassetteControlProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();

    juce::Rectangle<int> sliderArea = area.removeFromTop(area.getHeight()*0.8);

    int numOfNoteSliders = sliderArea.getWidth()/numOfNotes;

    std::array < juce::Rectangle<int>, 8> sliderAreas;
    std::array < juce::Rectangle<int>, 8> sliderLabelAreas;
    std::array < juce::Rectangle<int>, 8> sliderTxtAreas;

    for (int i = 0; i < numOfNotes; i++)
    {
        sliderAreas[i] = sliderArea.removeFromLeft(numOfNoteSliders);
    }

    for (int i = 0; i < numOfNotes; i++)
    {
        sliderLabelAreas[i] = sliderAreas[i].removeFromTop(sliderAreas[i].getHeight() * 0.4);
    }

    for (int i = 0; i < numOfNotes; i++)
    {
        sliderTxtAreas[i] = sliderAreas[i].removeFromBottom(sliderAreas[i].getHeight() * 0.2);
    }


    for (int i = 0; i < numOfNotes; i++)
    {
        noteTuneSlider[i].setBounds(sliderAreas[i]);
        noteTuneSlider[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, sliderTxtAreas[i].getWidth(), sliderTxtAreas[i].getHeight() );
        noteTuneSliderLabel[i].setBounds(sliderLabelAreas[i]);
    }
    //Rectangle<int> keyboardArea = area);
    
    addAndMakeVisible(keyboard);
    keyboard.setBounds(area);
    
}

void CassetteControlProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    for (int i = 0; i < 12; i++)
    {
        if (slider == &noteTuneSlider[i])
        {
            DBG("slider " << i << ": " << noteTuneSlider[i].getValue());
            audioProcessor.noteTuneMidiVal[i] = noteTuneSlider[i].getValue();
        }
    }
}
