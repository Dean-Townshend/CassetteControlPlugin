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
        setSliderStyle(noteTuneSlider[i], noteTuneSliderLabel[i]);
        addAndMakeVisible(noteTuneSlider[i]);
        //addAndMakeVisible(noteTuneSliderLabel[i]);
    }

    //Glide Slider
    setSliderStyle(glideSlider, glideSliderLabel);
    addAndMakeVisible(glideSlider);
    addAndMakeVisible(glideSliderLabel);

    //ADSR Sliders
    setSliderStyle(attackSlider, attackSliderLabel);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(attackSliderLabel);

    setSliderStyle(decaySlider, decaySliderLabel);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(decaySliderLabel);

    setSliderStyle(sustainSlider, sustainSliderLabel);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(sustainSliderLabel);
    
    setSliderStyle(releaseSlider, releaseSliderLabel);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(releaseSliderLabel);

    //Keyboard
    addAndMakeVisible(keyboard);
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

    //keyboard
    juce::Rectangle<int> keyboardArea = area.removeFromTop(area.getHeight() * 0.2);
    keyboard.setKeyWidth(keyboardArea.getWidth() / 7);
    keyboard.setBounds(keyboardArea);
    keyboard.setAvailableRange(60, 72);

    //Glide and ADSR
    std::array < juce::Rectangle<int>, 4 > ADSRSliderTxtAreas;
    juce::Rectangle<int> controlArea = area;

    //Glide
    juce::Rectangle<int> glideControlArea = controlArea.removeFromLeft(controlArea.getWidth() * 0.1);
    juce::Rectangle<int> glideControlTxtArea = glideControlArea.removeFromBottom(glideControlArea.getHeight() * 0.2);
    glideSlider.setBounds(glideControlArea);
    glideSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, glideControlTxtArea.getWidth(), glideControlTxtArea.getHeight());

    //ADSR
    juce::Rectangle<int> ADSRControlArea = controlArea;
    std::array < juce::Rectangle<int>, 4 > ADSRSliderAreas;
    std::array < juce::Rectangle<int>, 4 > ADSRSliderTxtAreas;

    int ADSRSliderIndivWidth = ADSRControlArea.getWidth() / 4;

    for (int i = 0; i < 4; i++)
    {
        ADSRSliderAreas[i]= ADSRControlArea.removeFromLeft(ADSRSliderIndivWidth);
        ADSRSliderTxtAreas[i] = ADSRSliderAreas[i].removeFromBottom(ADSRSliderAreas[i].getHeight() * 0.2);
    }

    attackSlider.setBounds(ADSRSliderAreas[0]);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, ADSRSliderTxtAreas[0].getWidth(), ADSRSliderTxtAreas[0].getHeight());
    decaySlider.setBounds(ADSRSliderAreas[1]);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, ADSRSliderTxtAreas[1].getWidth(), ADSRSliderTxtAreas[1].getHeight());
    sustainSlider.setBounds(ADSRSliderAreas[2]);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, ADSRSliderTxtAreas[2].getWidth(), ADSRSliderTxtAreas[2].getHeight());
    releaseSlider.setBounds(ADSRSliderAreas[3]);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, ADSRSliderTxtAreas[3].getWidth(), ADSRSliderTxtAreas[3].getHeight());
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

void CassetteControlProcessorEditor::setSliderStyle(juce::Slider& slider, juce::Label& label)
{
    slider.addListener(this);
    slider.setLookAndFeel(&custLookFeel1);
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    //slider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::slategrey);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::ghostwhite);
    slider.setRange(0, 127, 1);
    slider.setValue(0.0);

    label.setJustificationType(juce::Justification::centred);
    //label.setText("Note " + (juce::String)(i + 1), juce::dontSendNotification);
    label.setColour(juce::Label::textColourId, juce::Colours::black);
}
