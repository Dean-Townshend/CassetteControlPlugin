#pragma once
#include <JuceHeader.h>

class CustLookFeel : public juce::LookAndFeel_V4
{
public:
    CustLookFeel()
    {
        setColour (juce::Slider::thumbColourId, juce::Colours::red);
    }

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
    {
        auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
        auto centreX = (float) x + (float) width  * 0.5f;
        auto centreY = (float) y + (float) height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        //Inner fill
        g.setColour (juce::Colours::ghostwhite);
        g.fillEllipse (rx, ry, rw, rw);

        //Outline
        g.setColour (juce::Colours::darkgrey);
        g.drawEllipse (rx, ry, rw, rw, 2.0f);

        juce::Path p;
        auto pointerLength = radius * 0.50f;
        auto pointerThickness = 2.5f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));

        // pointer
        g.setColour (juce::Colours::black);
        g.fillPath (p);
    }
};