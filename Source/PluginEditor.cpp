#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
CassetteControlProcessorEditor::CassetteControlProcessorEditor(CassetteControlProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), keyboard(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)

{
    setSize(960, 600);
    setResizable(true, true);
    

    for (int i = 0; i < 12; i++)
    {
        //Tuning sliders
        setSliderStyle(noteTuneSlider[i], noteTuneSliderLabel[i]);
        addAndMakeVisible(noteTuneSlider[i]);
        noteTuneSliderLabel[i].setText("Note " + (juce::String)(i + 1), juce::dontSendNotification);
        addAndMakeVisible(noteTuneSliderLabel[i]);
    }

    //Glide Slider
    setSliderStyle(glideSlider, glideSliderLabel);
    glideSliderLabel.setText("Glide", juce::dontSendNotification);
    addAndMakeVisible(glideSlider);
    addAndMakeVisible(glideSliderLabel);

    //flutter Slider
    setSliderStyle(flutterSlider, flutterSliderLabel);
    flutterSliderLabel.setText("Flutter", juce::dontSendNotification);
    addAndMakeVisible(flutterSlider);
    addAndMakeVisible(flutterSliderLabel);

    //ADSR Sliders
    setSliderStyle(attackSlider, attackSliderLabel);
    attackSlider.setSliderStyle(juce::Slider::LinearVertical);
    attackSlider.setColour(juce::Slider::thumbColourId, juce::Colours::ghostwhite);
    attackSliderLabel.setText("Attack", juce::dontSendNotification);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(attackSliderLabel);

    setSliderStyle(decaySlider, decaySliderLabel);
    decaySlider.setSliderStyle(juce::Slider::LinearVertical);
    decaySlider.setColour(juce::Slider::thumbColourId, juce::Colours::ghostwhite);
    decaySliderLabel.setText("Decay", juce::dontSendNotification);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(decaySliderLabel);

    setSliderStyle(sustainSlider, sustainSliderLabel);
    sustainSlider.setSliderStyle(juce::Slider::LinearVertical);
    sustainSlider.setColour(juce::Slider::thumbColourId, juce::Colours::ghostwhite);
    sustainSliderLabel.setText("Sustain", juce::dontSendNotification);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(sustainSliderLabel);
    
    setSliderStyle(releaseSlider, releaseSliderLabel);
    releaseSlider.setSliderStyle(juce::Slider::LinearVertical);
    releaseSlider.setColour(juce::Slider::thumbColourId, juce::Colours::ghostwhite);
    releaseSliderLabel.setText("Release", juce::dontSendNotification);
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

    setResizeLimits(getWidth()/getWidth(), getWidth() / 1.6, getHeight() * 2, getWidth() / 1.6);
    juce::Rectangle<int> area = getLocalBounds();

    juce::Rectangle<int> sliderArea = area.removeFromTop(area.getHeight() * 0.4);

    juce::Rectangle<int> upperSliderArea = sliderArea.removeFromTop(sliderArea.getHeight() / 2);

    juce::Rectangle<int> lowerSliderArea = sliderArea;

    int cellWidth = lowerSliderArea.getWidth()/12;

    //lower
    std::array < juce::Rectangle<int>, 12> lowerSliderAreas;
    std::array < juce::Rectangle<int>, 12> lowerSliderTxtAreas;
    std::array < juce::Rectangle<int>, 12> lowerSliderLabelAreas;

    //upper
    std::array < juce::Rectangle<int>, 12> upperSliderAreas;
    std::array < juce::Rectangle<int>, 12> upperSliderTxtAreas;
    std::array < juce::Rectangle<int>, 12> upperSliderLabelAreas;

    for (int i = 0; i < 12; i++)
    {
        upperSliderAreas[i] = upperSliderArea.removeFromLeft(cellWidth);
        lowerSliderAreas[i] = lowerSliderArea.removeFromLeft(cellWidth);


        upperSliderLabelAreas[i] = upperSliderAreas[i].removeFromTop(upperSliderAreas[i].getHeight() * 0.1);
        lowerSliderLabelAreas[i] = lowerSliderAreas[i].removeFromTop(lowerSliderAreas[i].getHeight() * 0.1);
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
                noteTuneSliderLabel[i].setBounds(lowerSliderLabelAreas[i]);
                noteTuneSlider[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, lowerSliderTxtAreas[i].getWidth(), lowerSliderTxtAreas[i].getHeight());
            }
            else if (i % 2 != 0)
            {
                noteTuneSlider[i].setBounds(upperSliderAreas[i]);
                noteTuneSliderLabel[i].setBounds(upperSliderLabelAreas[i]);
                noteTuneSlider[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, upperSliderTxtAreas[i].getWidth(), upperSliderTxtAreas[i].getHeight());
            }
        }
        else if(i > 4)
        {
            if (i % 2 != 0)
            {
                noteTuneSlider[i].setBounds(lowerSliderAreas[i]);
                noteTuneSliderLabel[i].setBounds(lowerSliderLabelAreas[i]);
                noteTuneSlider[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, lowerSliderTxtAreas[i].getWidth(), lowerSliderTxtAreas[i].getHeight());
            }
            else if (i % 2 == 0)
            {
                noteTuneSlider[i].setBounds(upperSliderAreas[i]);
                noteTuneSliderLabel[i].setBounds(upperSliderLabelAreas[i]);
                noteTuneSlider[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, upperSliderTxtAreas[i].getWidth(), upperSliderTxtAreas[i].getHeight());
                
            }

        }
        noteTuneSliderLabel[i].setFont(juce::Font(float(noteTuneSliderLabel[i].getHeight()) * 1.5));
        
    }

    //keyboard
    juce::Rectangle<int> keyboardArea = area.removeFromTop(area.getHeight() * 0.15);
    keyboard.setKeyWidth(keyboardArea.getWidth() / 7);
    keyboard.setBounds(keyboardArea);
    keyboard.setAvailableRange(60, 72);

    //Glide and ADSR
    //std::array < juce::Rectangle<int>, 4 > ADSRSliderTxtAreas;
    juce::Rectangle<int> controlArea = area;

    //Glide
    juce::Rectangle<int> adjControlArea = controlArea.removeFromLeft(controlArea.getWidth() * 0.2);
    juce::Rectangle<int> glideControlArea = adjControlArea.removeFromLeft(adjControlArea.getWidth()/2);
    juce::Rectangle<int> glideControlLabelArea = glideControlArea.removeFromTop(glideControlArea.getHeight() * 0.2);
    juce::Rectangle<int> glideControlTxtArea = glideControlArea.removeFromBottom(glideControlArea.getHeight() * 0.2);
    glideSlider.setBounds(glideControlArea);
    glideSliderLabel.setBounds(glideControlLabelArea);
    glideSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, glideControlTxtArea.getWidth(), glideControlTxtArea.getHeight());
    glideSliderLabel.setFont(juce::Font(float(glideControlLabelArea.getHeight())/2));

    //Flutter
    juce::Rectangle<int> flutterControlArea = adjControlArea;
    juce::Rectangle<int> flutterControlLabelArea = flutterControlArea.removeFromTop(flutterControlArea.getHeight() * 0.2);
    juce::Rectangle<int> flutterControlTxtArea = flutterControlArea.removeFromBottom(flutterControlArea.getHeight() * 0.2);
    flutterSlider.setBounds(flutterControlArea);
    flutterSliderLabel.setBounds(flutterControlLabelArea);
    flutterSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, flutterControlTxtArea.getWidth(), flutterControlTxtArea.getHeight());
    flutterSliderLabel.setFont(juce::Font(float(flutterSliderLabel.getHeight()/2)));

    //ADSR
    juce::Rectangle<int> ADSRControlArea = controlArea;
    std::array < juce::Rectangle<int>, 4 > ADSRSliderAreas;
    std::array < juce::Rectangle<int>, 4 > ADSRSliderTxtAreas;
    std::array < juce::Rectangle<int>, 4> ADSRSliderLabelAreas;

    int ADSRSliderIndivWidth = ADSRControlArea.getWidth() / 4;

    for (int i = 0; i < 4; i++)
    {
        ADSRSliderAreas[i]= ADSRControlArea.removeFromLeft(ADSRSliderIndivWidth);
        ADSRSliderLabelAreas[i] = ADSRSliderAreas[i].removeFromTop(ADSRSliderAreas[i].getHeight() * 0.2);
        ADSRSliderTxtAreas[i] = ADSRSliderAreas[i].removeFromBottom(ADSRSliderAreas[i].getHeight() * 0.2);
    }

    attackSlider.setBounds(ADSRSliderAreas[0]);
    attackSliderLabel.setBounds(ADSRSliderLabelAreas[0]);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, ADSRSliderTxtAreas[0].getWidth(), ADSRSliderTxtAreas[0].getHeight());
    attackSliderLabel.setFont(juce::Font(float(attackSliderLabel.getHeight()) /2));
    decaySlider.setBounds(ADSRSliderAreas[1]);
    decaySliderLabel.setBounds(ADSRSliderLabelAreas[1]);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, ADSRSliderTxtAreas[1].getWidth(), ADSRSliderTxtAreas[1].getHeight());
    decaySliderLabel.setFont(juce::Font(float(decaySliderLabel.getHeight()) /2));
    sustainSlider.setBounds(ADSRSliderAreas[2]);
    sustainSliderLabel.setBounds(ADSRSliderLabelAreas[2]);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, ADSRSliderTxtAreas[2].getWidth(), ADSRSliderTxtAreas[2].getHeight());
    sustainSliderLabel.setFont(juce::Font(float(sustainSliderLabel.getHeight())/2));
    releaseSlider.setBounds(ADSRSliderAreas[3]);
    releaseSliderLabel.setBounds(ADSRSliderLabelAreas[3]);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, ADSRSliderTxtAreas[3].getWidth(), ADSRSliderTxtAreas[3].getHeight());
    releaseSliderLabel.setFont(juce::Font(float(releaseSliderLabel.getHeight()) /2));
}


void CassetteControlProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &glideSlider)
    {
        audioProcessor.glideMidiVal = glideSlider.getValue();
    }
    else if (slider == &flutterSlider)
    {
        audioProcessor.flutterMidiVal = flutterSlider.getValue();
    }
    else
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
