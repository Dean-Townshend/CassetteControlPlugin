#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
CassetteControlProcessorEditor::CassetteControlProcessorEditor(CassetteControlProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), keyboard(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)

{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(960, 600);

    for (int i = 0; i < 12; i++)
    {
        //Tuning sliders
        noteTuneSlider[i].addListener(this);
        noteTuneSlider[i].setLookAndFeel(&custLookFeel1);
        noteTuneSlider[i].setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        noteTuneSlider[i].setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
        //noteTuneSlider[i].setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::slategrey);
        noteTuneSlider[i].setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::ghostwhite);
        noteTuneSlider[i].setRange(0, 127, 1);
        noteTuneSlider[i].setValue(0.0);
        
        
        //noteTuneSliderLabel[i].setJustificationType(juce::Justification::centred);
        //Tuning slider labels
        //noteTuneSliderLabel[i].setText("Note " + (juce::String)(i + 1), juce::dontSendNotification);
        //noteTuneSliderLabel[i].setColour(juce::Label::textColourId, juce::Colours::black);

        addAndMakeVisible(noteTuneSlider[i]);
        //addAndMakeVisible(noteTuneSliderLabel[i]);
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

    juce::Rectangle<int> upperSliderArea = sliderArea.removeFromTop(sliderArea.getHeight() / 2);

    juce::Rectangle<int> lowerSliderArea = sliderArea;

    int cellWidth = lowerSliderArea.getWidth()/12;

    //lower
    std::array < juce::Rectangle<int>, 12> lowerSliderAreas;
    std::array < juce::Rectangle<int>, 12> lowerSliderTxtAreas;

    //upper
    std::array < juce::Rectangle<int>, 12> upperSliderAreas;
    std::array < juce::Rectangle<int>, 12> upperSliderTxtAreas;

    for (int i = 0; i < 12; i++)
    {
        upperSliderAreas[i] = upperSliderArea.removeFromLeft(cellWidth);
        lowerSliderAreas[i] = lowerSliderArea.removeFromLeft(cellWidth);
        upperSliderTxtAreas[i] = upperSliderAreas[i].removeFromBottom(upperSliderAreas[i].getHeight() * 0.2);
        lowerSliderTxtAreas[i] = lowerSliderAreas[i].removeFromBottom(lowerSliderAreas[i].getHeight() * 0.2);
    }

    for (int i = 0; i < 12; i++)
    {
        if (i <= 4)
        {
            if (i == 0 || i % 2 == 0)
            {
                noteTuneSlider[i].setBounds(lowerSliderAreas[i]);
                noteTuneSlider[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, lowerSliderTxtAreas[i].getWidth(), lowerSliderTxtAreas[i].getHeight());
            }
            else if (i % 2 != 0)
            {
                noteTuneSlider[i].setBounds(upperSliderAreas[i]);
                noteTuneSlider[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, upperSliderTxtAreas[i].getWidth(), upperSliderTxtAreas[i].getHeight());
            }
        }
        else if(i > 4)
        {
            if (i % 2 != 0)
            {
                noteTuneSlider[i].setBounds(lowerSliderAreas[i]);
                noteTuneSlider[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, lowerSliderTxtAreas[i].getWidth(), lowerSliderTxtAreas[i].getHeight());
            }
            else if (i % 2 == 0)
            {
                noteTuneSlider[i].setBounds(upperSliderAreas[i]);
                noteTuneSlider[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, upperSliderTxtAreas[i].getWidth(), upperSliderTxtAreas[i].getHeight());
            }

        }
    }

    juce::Rectangle<int> keyboardArea = area.removeFromTop(area.getHeight() /4);    
    
    //keyboard.setSize(keyboardArea.getWidth(), keyboardArea.getHeight());
    //keyboard.setBoundsToFit(keyboardArea, juce::Justification::centred, true);
    //keyboard.setBoundsRelative(keyAreaFloat);
    keyboard.setKeyWidth(keyboardArea.getWidth() / 7);
    keyboard.setBounds(keyboardArea);
    keyboard.setAvailableRange(60, 72);
    

    //keyboard.setBoundsRelative(1, 1, keyAreaFloat.getWidth(), keyAreaFloat.getHeight());

    addAndMakeVisible(keyboard);
    
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
