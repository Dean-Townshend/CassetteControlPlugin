#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
CassetteControlProcessorEditor::CassetteControlProcessorEditor(CassetteControlProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), keyboard(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)

{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 400);

    for (int i = 0; i < numOfNotes; i++)
    {
        //Tuning sliders
        noteTuneSlider[i].addListener(this);
        noteTuneSlider[i].setLookAndFeel(&custLookFeel1);
        noteTuneSlider[i].setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        noteTuneSlider[i].setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
        //noteTuneSlider[i].setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::slategrey);
        noteTuneSlider[i].setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::ghostwhite);
        noteTuneSlider[i].setRange(0, 127, 1);
        noteTuneSliderLabel[i].setJustificationType(juce::Justification::centred);
        noteTuneSlider[i].setValue(0.0);
        //custLookFeel1.hello = 1;

        //Tuning slider labels
        noteTuneSliderLabel[i].setText("Note " + (juce::String)(i + 1), juce::dontSendNotification);
        noteTuneSliderLabel[i].setColour(juce::Label::textColourId, juce::Colours::black);

        addAndMakeVisible(noteTuneSlider[i]);
        addAndMakeVisible(noteTuneSliderLabel[i]);
    }
}

CassetteControlProcessorEditor::~CassetteControlProcessorEditor()
{
}

//==============================================================================
void CassetteControlProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::dimgrey);
}

void CassetteControlProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();

    juce::Rectangle<int> sliderArea = area.removeFromTop(area.getHeight() * 0.4);

    juce::Rectangle<int> upperSliderArea = sliderArea.removeFromTop(sliderArea.getHeight() * 0.5);

    juce::Rectangle<int> lowerSliderArea = sliderArea;

    int numOfLowerNoteSliders = lowerSliderArea.getWidth()/13;

    std::array < juce::Rectangle<int>, 13> lowerSliderAreas;
    //std::array < juce::Rectangle<int>, 13> lowerSliderLabelAreas;
    std::array < juce::Rectangle<int>, 13> lowerSliderTxtAreas;

    for (int i = 0; i < 13; i++)
    {
        lowerSliderAreas[i] = lowerSliderArea.removeFromLeft(numOfLowerNoteSliders);
    }


    for (int i = 0; i < 13; i++)
    {
        lowerSliderTxtAreas[i] = lowerSliderAreas[i].removeFromBottom(lowerSliderAreas[i].getHeight() * 0.2);
    }

    for (int i = 0, ii = 0; i < 7; i++, ii+=2)
    {
        noteTuneSlider[i].setBounds(lowerSliderAreas[ii]);
        noteTuneSlider[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, lowerSliderTxtAreas[ii].getWidth(), lowerSliderTxtAreas[ii].getHeight());
        //noteTuneSliderLabel[i].setBounds(lowerSliderLabelAreas[ii]);
    }

    std::array < juce::Rectangle<int>, 13> upperSliderAreas;
    std::array < juce::Rectangle<int>, 13> upperSliderLabelAreas;
    std::array < juce::Rectangle<int>, 13> upperSliderTxtAreas;

    for (int i = 0; i < 13; i++)
    {
        upperSliderAreas[i] = upperSliderArea.removeFromLeft(numOfLowerNoteSliders);
    }


    for (int i = 0; i < 13; i++)
    {
        upperSliderTxtAreas[i] = upperSliderAreas[i].removeFromBottom(upperSliderAreas[i].getHeight() * 0.2);
    }

    for (int i = 7, ii = 1, iii = 3; i < 12; i++, ii += 2, iii +=2)
    {
        if (i <=8)
        {
            noteTuneSlider[i].setBounds(upperSliderAreas[ii]);
            noteTuneSlider[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, upperSliderTxtAreas[ii].getWidth(), upperSliderTxtAreas[ii].getHeight());
            //noteTuneSliderLabel[i].setBounds(upperSliderLabelAreas[ii]);
        }
        else if (i > 8)
        {
            noteTuneSlider[i].setBounds(upperSliderAreas[iii]);
            noteTuneSlider[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, upperSliderTxtAreas[iii].getWidth(), upperSliderTxtAreas[iii].getHeight());
            //noteTuneSliderLabel[i].setBounds(upperSliderLabelAreas[iii]);
        }
    }


    juce::Rectangle<int> keyboardArea = area.removeFromTop(area.getHeight() * 0.4);
        
    juce::Rectangle<float> keyAreaFloat =  keyboardArea.toFloat();
    keyboard.setAvailableRange(60, 72);
    
    //keyboard.setSize(keyboardArea.getWidth(), keyboardArea.getHeight());
    //keyboard.setBoundsToFit(keyboardArea, juce::Justification::centred, true);


    //keyboard.setBoundsRelative(keyAreaFloat);
    //keyboard.setBounds(keyAreaFloat);

    addAndMakeVisible(keyboard);
    keyboard.setBoundsRelative(1, 1, keyAreaFloat.getWidth(), keyAreaFloat.getHeight());
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
