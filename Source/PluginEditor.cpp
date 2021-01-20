/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <stdio.h>
#include <fstream>
#include <iostream>


//==============================================================================
SmartAmpProAudioProcessorEditor::SmartAmpProAudioProcessorEditor (SmartAmpProAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to

    addAndMakeVisible(modelSelect);
    modelSelect.setColour(juce::Label::textColourId, juce::Colours::black);
    int c = 1;
    for (const auto& jsonFile : processor.jsonFiles) {
        modelSelect.addItem(jsonFile.getFileNameWithoutExtension(), c);
        c += 1;
    }
    modelSelect.onChange = [this] {modelSelectChanged(); };
    modelSelect.setSelectedItemIndex(processor.current_model_index, juce::NotificationType::sendNotification);
    modelSelect.setScrollWheelEnabled(true);

    // Set Widget Graphics
    ampSilverKnobLAF.setLookAndFeel(ImageCache::getFromMemory(BinaryData::Vintage_Knob_png, BinaryData::Vintage_Knob_pngSize));

    ampOnButton.setImages(true, true, true,
        ImageCache::getFromMemory(BinaryData::Power_switch_on_png, BinaryData::Power_switch_on_pngSize), 1.0, Colours::transparentWhite,
        Image(), 1.0, Colours::transparentWhite,
        ImageCache::getFromMemory(BinaryData::Power_switch_on_png, BinaryData::Power_switch_on_pngSize), 1.0, Colours::transparentWhite,
        0.0);
    addAndMakeVisible(ampOnButton);
    ampOnButton.addListener(this);

    addAndMakeVisible(loadButton);
    loadButton.setButtonText("Add Tone");
    loadButton.addListener(this);

    addAndMakeVisible(recordButton);
    recordButton.setButtonText("Start Capture");
    recordButton.addListener(this);

    addAndMakeVisible(trainButton);
    trainButton.setButtonText("Train Model");
    trainButton.addListener(this);
    
    addAndMakeVisible(timerLabel);
    timerLabel.setText(minutes + ":" + seconds, juce::NotificationType::dontSendNotification);
    timerLabel.setJustificationType(juce::Justification::horizontallyCentred);
    timerLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    timerLabel.setFont(juce::Font(32.0f, juce::Font::bold));
    timerLabel.setVisible(0);

    addAndMakeVisible(helpLabel);
    helpLabel.setText("", juce::NotificationType::dontSendNotification);
    //helpLabel.setJustificationType(juce::Justification::horizontallyCentred);
    helpLabel.setJustificationType(juce::Justification::centredTop);
    helpLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    helpLabel.setFont(juce::Font(18.0f, juce::Font::bold));
    helpLabel.setVisible(1);


    ampLED.setImages(true, true, true,
        ImageCache::getFromMemory(BinaryData::led_blue_on_png, BinaryData::led_blue_on_pngSize), 1.0, Colours::transparentWhite,
        Image(), 1.0, Colours::transparentWhite,
        ImageCache::getFromMemory(BinaryData::led_blue_on_png, BinaryData::led_blue_on_pngSize), 1.0, Colours::transparentWhite,
        0.0);
    addAndMakeVisible(ampLED);

    addAndMakeVisible(ampPresenceKnob);
    ampPresenceKnob.setLookAndFeel(&ampSilverKnobLAF);
    ampPresenceKnob.addListener(this);
    //ampPresenceKnob.setSkewFactorFromMidPoint(1000.0); // Not working because of custom lookAndFeel class
    ampPresenceKnob.setRange(-12.0, 12.0);
    ampPresenceKnob.setValue(processor.ampPresenceKnobState);
    ampPresenceKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampPresenceKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 75, 20);
    ampPresenceKnob.setNumDecimalPlacesToDisplay(1);
    ampPresenceKnob.setDoubleClickReturnValue(true, 0.0);

    addAndMakeVisible(ampBassKnob);
    ampBassKnob.setLookAndFeel(&ampSilverKnobLAF);
    ampBassKnob.addListener(this);
    ampBassKnob.setRange(-10.0, 10.0);
    ampBassKnob.setValue(processor.ampBassKnobState);
    ampBassKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampBassKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampBassKnob.setNumDecimalPlacesToDisplay(1);
    ampBassKnob.setDoubleClickReturnValue(true, 0.0);

    addAndMakeVisible(ampMidKnob);
    ampMidKnob.setLookAndFeel(&ampSilverKnobLAF);
    ampMidKnob.addListener(this);
    ampMidKnob.setRange(-10.0, 10.0);
    ampMidKnob.setValue(processor.ampMidKnobState);
    ampMidKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampMidKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampMidKnob.setNumDecimalPlacesToDisplay(1);
    ampMidKnob.setDoubleClickReturnValue(true, 0.0);

    addAndMakeVisible(ampTrebleKnob);
    ampTrebleKnob.setLookAndFeel(&ampSilverKnobLAF);
    ampTrebleKnob.addListener(this);
    ampTrebleKnob.setRange(-10.0, 10.0);
    ampTrebleKnob.setValue(processor.ampTrebleKnobState);
    ampTrebleKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampTrebleKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampTrebleKnob.setNumDecimalPlacesToDisplay(1);
    ampTrebleKnob.setDoubleClickReturnValue(true, 0.0);

    addAndMakeVisible(ampGainKnob);
    ampGainKnob.setLookAndFeel(&ampSilverKnobLAF);
    ampGainKnob.addListener(this);
    ampGainKnob.setRange(-15.0, 15.0);
    ampGainKnob.setValue(processor.ampGainKnobState);
    ampGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampGainKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampGainKnob.setNumDecimalPlacesToDisplay(1);
    ampGainKnob.setDoubleClickReturnValue(true, 0.0);

    addAndMakeVisible(ampMasterKnob);
    ampMasterKnob.setLookAndFeel(&ampSilverKnobLAF);
    ampMasterKnob.addListener(this);
    ampMasterKnob.setRange(-36.0, 12.0);
    ampMasterKnob.setValue(processor.ampMasterKnobState);
    ampMasterKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampMasterKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20 );
    ampMasterKnob.setNumDecimalPlacesToDisplay(1);
    ampMasterKnob.setDoubleClickReturnValue(true, -12.0);

    // Size of plugin GUI
    setSize(694, 376);
}

SmartAmpProAudioProcessorEditor::~SmartAmpProAudioProcessorEditor()
{
}

//==============================================================================
void SmartAmpProAudioProcessorEditor::paint (Graphics& g)
{
    if ( current_background == 1 && processor.amp_state == 1) {
        background = ImageCache::getFromMemory(BinaryData::smp_on_png, BinaryData::smp_on_pngSize);
    } else if (current_background == 1 && processor.amp_state == 1) {
        background = ImageCache::getFromMemory(BinaryData::smp_on_png, BinaryData::smp_on_pngSize);
    } else {
        background = ImageCache::getFromMemory(BinaryData::smp_off_png, BinaryData::smp_off_pngSize);
    }
    g.drawImageAt(background, 0, 0);

    g.setColour (Colours::white);
    g.setFont (15.0f);

    // Set On/Off amp graphic
    if (processor.amp_state == 0) {
        ampOnButton.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::Power_switch_off_png, BinaryData::Power_switch_off_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::Power_switch_off_png, BinaryData::Power_switch_off_pngSize), 1.0, Colours::transparentWhite,
            0.0);
        ampLED.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::led_blue_off_png, BinaryData::led_blue_off_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::led_blue_off_png, BinaryData::led_blue_off_pngSize), 1.0, Colours::transparentWhite,
            0.0);
    }
    else {
        ampOnButton.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::Power_switch_on_png, BinaryData::Power_switch_on_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::Power_switch_on_png, BinaryData::Power_switch_on_pngSize), 1.0, Colours::transparentWhite,
            0.0);
        ampLED.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::led_blue_on_png, BinaryData::led_blue_on_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::led_blue_on_png, BinaryData::led_blue_on_pngSize), 1.0, Colours::transparentWhite,
            0.0);
    }

}

void SmartAmpProAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    modelSelect.setBounds(15, 10, 225, 25);
    recordButton.setBounds(540, 10, 125, 25);
    trainButton.setBounds(540, 42, 125, 25);
    timerLabel.setBounds(300, 10, 70, 25);
    helpLabel.setBounds(190, 36, 300, 65);
    loadButton.setBounds(15, 42, 100, 25);
    // Amp Widgets
    ampPresenceKnob.setBounds(445, 242, 55, 75);
    ampBassKnob.setBounds(203, 242, 55, 75);
    ampMidKnob.setBounds(283, 242, 55, 75);
    ampTrebleKnob.setBounds(368, 242, 55, 75);
    ampGainKnob.setBounds(100, 225, 75, 95);
    ampMasterKnob.setBounds(542, 225, 75, 95);

    ampOnButton.setBounds(54, 259, 15, 25);
    ampLED.setBounds(636, 240, 15, 25);
}

void SmartAmpProAudioProcessorEditor::modelSelectChanged()
{
    const int selectedFileIndex = modelSelect.getSelectedItemIndex();
    if (selectedFileIndex >= 0 && selectedFileIndex < processor.jsonFiles.size()) {
        processor.loadConfig(processor.jsonFiles[selectedFileIndex]);
        processor.current_model_index = modelSelect.getSelectedItemIndex();
    }
}

void SmartAmpProAudioProcessorEditor::loadButtonClicked()
{
    FileChooser chooser("Select one or more .json tone files to import",
        {},
        "*.json");
    if (chooser.browseForMultipleFilesToOpen())
    {
        Array<File> files = chooser.getResults();
        for (auto file : files) {
            File fullpath = processor.userAppDataDirectory.getFullPathName() + "/" + file.getFileName();
            bool b = fullpath.existsAsFile();
            if (b == false) {

                processor.loadConfig(file);
                fname = file.getFileName();
                processor.loaded_tone = file;
                processor.loaded_tone_name = fname;
                processor.custom_tone = 1;

                // Copy selected file to model directory and load into dropdown menu
                bool a = file.copyFileTo(fullpath);
                if (a == true) {
                    modelSelect.addItem(file.getFileNameWithoutExtension(), processor.jsonFiles.size() + 1);
                    modelSelect.setSelectedItemIndex(processor.jsonFiles.size(), juce::NotificationType::sendNotification);
                    processor.jsonFiles.push_back(file);
                }
            }
        }
    }
}

void SmartAmpProAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &ampOnButton) {
        ampOnButtonClicked();
        helpLabel.setText("", juce::NotificationType::dontSendNotification);
    } else if (button == &loadButton) {
        loadButtonClicked();
    } else if (button == &recordButton) {
        recordButtonClicked();
    } else if (button == &trainButton) {
        trainButtonClicked();
    }
}


void SmartAmpProAudioProcessorEditor::ampOnButtonClicked() {
    if (processor.amp_state == 0) {
        processor.amp_state = 1;
        // Reset the directory in case user is manually adding or removing models from the SmartAmpPro directory
        processor.resetDirectory(processor.userAppDataDirectory);
    }
    else {
        processor.amp_state = 0;
        // Also acts as failsafe to stop training timer (TODO change how this is handled)
        if (training == 1) {
            timer_stop();
            training = 0;
            helpLabel.setText("Training halted.", juce::NotificationType::dontSendNotification);
        }
    }
    repaint();
}

void SmartAmpProAudioProcessorEditor::recordButtonClicked() {
    if (training == 1) {
        helpLabel.setText("Can't record while training.", juce::NotificationType::dontSendNotification);
        return;
    }
    File userAppDataDirectory2 = File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile(JucePlugin_Manufacturer).getChildFile(JucePlugin_Name);
    if (processor.recording == 0) {
        FileChooser chooser("Enter a descriptive tone name (NO SPACES IN NAME)",
            userAppDataDirectory2,
            "*.wav");
        if (chooser.browseForFileToSave(false))  // TODO Overwriting existing file seems to lock up the plugin - fix
        {
            File file = chooser.getResult(); // TODO: Fix to handle spaces in filename
            record_file = file.getFileName();

            processor.recording = 1;
            recordButton.setColour(TextButton::buttonColourId, Colours::red);
            recordButton.setButtonText("Stop Capture");
            timerLabel.setText(minutes + ":0" + seconds, juce::NotificationType::sendNotification);
            timerLabel.setVisible(1);
            timer_start();
            helpLabel.setText("Get Ready for Tone Capture..\nEnsure input is on Channel 1 and target is on Channel 2", juce::NotificationType::sendNotification);
        }

    }
    else {
        processor.audio_recorder.stopRecording();
        processor.recording = 0;
        recordButton.setColour(TextButton::buttonColourId, Colours::black);
        recordButton.setButtonText("Start Capture");
        timerLabel.setText(minutes + ":" + seconds, juce::NotificationType::sendNotification);
        timer_stop();
        timerLabel.setVisible(0);
        minutes = "";
        seconds = "10";
        helpLabel.setText("Capture ended.", juce::NotificationType::dontSendNotification);
    }

}

void SmartAmpProAudioProcessorEditor::trainButtonClicked() 
{
    if (processor.recording == 1) {
        helpLabel.setText("Can't train while recording.", juce::NotificationType::dontSendNotification);
        return;
    } else if (training == 1) {
        helpLabel.setText("Training already in progress.", juce::NotificationType::dontSendNotification);
        return;
    }

    File userAppDataDirectory2 = File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile(JucePlugin_Manufacturer).getChildFile(JucePlugin_Name);
    FileChooser chooser("Select recorded .wav sample for model training",
        userAppDataDirectory2,
        "*.wav");
    if (chooser.browseForMultipleFilesToOpen())
    {
        Array<File> files = chooser.getResults();
   
        File fullpath = processor.userAppDataDirectory.getFullPathName();
        File train_script = processor.userAppDataDirectory.getFullPathName() + "/train.py";

        bool b = train_script.existsAsFile();
        if (b == true) {
            File file = files[0]; // TODO: Fix to handle spaces in filename
            File file2 = "";
            
            std::string string_command = "";

            // Generate run script based on platform
            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
            //Windows (32-bit and 64-bit)
            if (files.size() > 1) {
                file2 = files[1];
                // TODO: Currently the two selected files will be in alphabetical order, so the first will be input, second is output. Better way to handle?
                model_folder = processor.userAppDataDirectory.getFullPathName().toStdString() + "/models/" + file2.getFileNameWithoutExtension().toStdString();
                test_file = processor.userAppDataDirectory.getFullPathName().toStdString() + "/" + file2.getFileNameWithoutExtension().toStdString() + ".json";
                string_command = "cd " + fullpath.getFullPathName().toStdString() + " && " + "echo python train.py " + file.getFullPathName().toStdString() + " " + file2.getFileNameWithoutExtension().toStdString() + " --out_file=" + file2.getFullPathName().toStdString() + " > run.bat && start /min run.bat && exit";
            }
            else {
                model_folder = processor.userAppDataDirectory.getFullPathName().toStdString() + "/models/" + file.getFileNameWithoutExtension().toStdString();
                test_file = processor.userAppDataDirectory.getFullPathName().toStdString() + "/" + file.getFileNameWithoutExtension().toStdString() + ".json";
                string_command = "cd " + fullpath.getFullPathName().toStdString() + " && " + "echo python train.py " + file.getFullPathName().toStdString() + " " + file.getFileNameWithoutExtension().toStdString() + " > run.bat && start /min run.bat && exit";
            }

            #elif __APPLE__
            if (files.size() > 1) {
                file2 = files[1];
                // TODO: Currently the two selected files will be in alphabetical order, so the first will be input, second is output. Better way to handle?
                model_folder = processor.userAppDataDirectory.getFullPathName().toStdString() + "/models/" + file2.getFileNameWithoutExtension().toStdString();
                test_file = processor.userAppDataDirectory.getFullPathName().toStdString() + "/" + file2.getFileNameWithoutExtension().toStdString() + ".json";
                string_command = "cd " + fullpath.getFullPathName().toStdString() + " && " + "echo python train.py " + file.getFullPathName().toStdString() + " " + file2.getFileNameWithoutExtension().toStdString() + " --out_file=" + file2.getFullPathName().toStdString() + " > run.sh && chmod 775 *  && ./run.sh";
            }
            else {
                model_folder = processor.userAppDataDirectory.getFullPathName().toStdString() + "/models/" + file.getFileNameWithoutExtension().toStdString();
                test_file = processor.userAppDataDirectory.getFullPathName().toStdString() + "/" + file.getFileNameWithoutExtension().toStdString() + ".json";
                string_command = "cd " + fullpath.getFullPathName().toStdString() + " && " + "echo python train.py " + file.getFullPathName().toStdString() + " " + file.getFileNameWithoutExtension().toStdString() + " > run.sh && chmod 775 * && ./run.sh";
            }
            #elif __linux__
            if (files.size() > 1) {
                file2 = files[1];
                // TODO: Currently the two selected files will be in alphabetical order, so the first will be input, second is output. Better way to handle?
                model_folder = processor.userAppDataDirectory.getFullPathName().toStdString() + "/models/" + file2.getFileNameWithoutExtension().toStdString();
                test_file = processor.userAppDataDirectory.getFullPathName().toStdString() + "/" + file2.getFileNameWithoutExtension().toStdString() + ".json";
                string_command = "cd " + fullpath.getFullPathName().toStdString() + " && " + "echo python train.py " + file.getFullPathName().toStdString() + " " + file2.getFileNameWithoutExtension().toStdString() + " --out_file=" + file2.getFullPathName().toStdString() + " > run.sh && chmod 775 *  && ./run.sh";
            }
            else {
                model_folder = processor.userAppDataDirectory.getFullPathName().toStdString() + "/models/" + file.getFileNameWithoutExtension().toStdString();
                test_file = processor.userAppDataDirectory.getFullPathName().toStdString() + "/" + file.getFileNameWithoutExtension().toStdString() + ".json";
                string_command = "cd " + fullpath.getFullPathName().toStdString() + " && " + "echo python train.py " + file.getFullPathName().toStdString() + " " + file.getFileNameWithoutExtension().toStdString() + " > run.sh && chmod 775 * && ./run.sh";
            }
            #else
            #   error "Unknown compiler"
            #endif


            if (test_file.existsAsFile()) {
                helpLabel.setText(test_file.getFileNameWithoutExtension().toStdString() + " tone already exists.", juce::NotificationType::dontSendNotification);
            } else if (model_folder.exists()) {
                helpLabel.setText("\""+ test_file.getFileNameWithoutExtension().toStdString() + "\" model folder already exists. Remove folder or choose a new name.", juce::NotificationType::dontSendNotification);
            } else {
                // Attempt to run train.py
                setTrainingStatus(0);
                const char* char_command = &string_command[0];
                system(char_command); // call to training program
                training = 1;
                timer_start();
            }
        } else {
            helpLabel.setText("Error: Could not locate training script.", juce::NotificationType::dontSendNotification);
        }
    }
}

void SmartAmpProAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    // Amp
    if (slider == &ampGainKnob)
        processor.set_ampDrive(slider->getValue());
    else if (slider == &ampMasterKnob)
        processor.set_ampMaster(slider->getValue());
    else if (slider == &ampBassKnob || slider == &ampMidKnob || slider == &ampTrebleKnob) {
        processor.set_ampEQ(ampBassKnob.getValue(), ampMidKnob.getValue(), ampTrebleKnob.getValue(), ampPresenceKnob.getValue());
        // Set knob states for saving positions when closing/reopening GUI
        processor.ampBassKnobState = ampBassKnob.getValue();
        processor.ampMidKnobState = ampMidKnob.getValue();
        processor.ampTrebleKnobState = ampTrebleKnob.getValue();
    }
    else if (slider == &ampPresenceKnob) {
            processor.set_ampEQ(ampBassKnob.getValue(), ampMidKnob.getValue(), ampTrebleKnob.getValue(), ampPresenceKnob.getValue());
    }
}


void SmartAmpProAudioProcessorEditor::timer_start()
{
    startTimer(1000);
}

void SmartAmpProAudioProcessorEditor::timer_stop()
{
    stopTimer();
    t = 190;
}

void SmartAmpProAudioProcessorEditor::setTrainingStatus(int status) {
    std::ifstream infile(processor.userAppDataDirectory.getFullPathName().toStdString() + "/status.txt");
    int a = 0;
    int b = 0;
    int accuracy = 0.0;
    while (infile >> a >> b)
    {
        accuracy = b;
    }
    std::ofstream outfile;
    outfile.open(processor.userAppDataDirectory.getFullPathName().toStdString() + "/status.txt", std::ofstream::trunc);
    outfile << std::to_string(status) + " " + std::to_string(accuracy);
    outfile.close();
}

void SmartAmpProAudioProcessorEditor::timerCallback()
{
    // Check if timer is for training or for recording
    if (training == 1) {
        std::ifstream infile(processor.userAppDataDirectory.getFullPathName().toStdString() + "/status.txt");
        int a;
        int b;
        while (infile >> a >> b)
        {
            helpLabel.setText(std::to_string(a) + " status", juce::NotificationType::dontSendNotification);
            if (a < 100) {
                helpLabel.setText("Training: " + std::to_string(a) + "% complete\n" + test_file.getFileNameWithoutExtension().toStdString(), juce::NotificationType::dontSendNotification);
                return;
            }
            else {
                timer_stop();
                training = 0;
                // Run this after model has been generated
                processor.resetDirectory(processor.userAppDataDirectory);
                modelSelect.clear();
                int c = 1;
                for (const auto& jsonFile : processor.jsonFiles) {
                    modelSelect.addItem(jsonFile.getFileName(), c);
                    c += 1;
                }
                modelSelect.setSelectedItemIndex(0, juce::NotificationType::sendNotification);

                // Check that a .json tone was generated, and if not, notify user through helpLabel
                if (test_file.existsAsFile() == false) {
                    helpLabel.setText("Failed to create new tone.", juce::NotificationType::dontSendNotification);
                }
                else {
                    helpLabel.setText("New Tone Created:\n" + test_file.getFileNameWithoutExtension().toStdString() + "\nAccuracy: " + std::to_string(b) + "%", juce::NotificationType::dontSendNotification);
                }
            }
        }
        if (training == 0) {
            setTrainingStatus(0);
        }

    } else {


        //std::cout << "time tick" << std::endl;
        t -= 1;
        seconds = std::to_string(t % 60);
        minutes = std::to_string(t / 60);
        //t_label = std::to_string(t);
        if (t > 180) {
            minutes = "";
            seconds = std::to_string(std::abs(t - 180));
        }
        else if (t == 180) {
            processor.audio_recorder.setRecordName(record_file);
            processor.audio_recorder.startRecording();
            helpLabel.setText("Begin 3 minutes of guitar playing!", juce::NotificationType::sendNotification);
        }

        if (t % 60 < 10) {
            seconds = "0" + seconds;
        }

        timerLabel.setText(minutes + ":" + seconds, juce::NotificationType::sendNotification);
        if (t < 1) {
            timer_stop();
            processor.audio_recorder.stopRecording();
            processor.recording = 0;
            recordButton.setColour(TextButton::buttonColourId, Colours::black);
            recordButton.setButtonText("Start Capture");
            timer_stop();
            timerLabel.setText(":10", juce::NotificationType::sendNotification);
            t = 190;
            timerLabel.setVisible(0);
            helpLabel.setText("Tone Capture Complete.\nClick \"Train Model\"", juce::NotificationType::sendNotification);
            minutes = "";
            seconds = "10";

        }
        else if (t == 170) {
            helpLabel.setText("Play some chords", juce::NotificationType::sendNotification);
        }
        else if (t == 150) {
            helpLabel.setText("Play some notes", juce::NotificationType::sendNotification);
        }
        else if (t == 130) {
            helpLabel.setText("Play your favorite song", juce::NotificationType::sendNotification);
        }
        else if (t == 100) {
            helpLabel.setText("Play quiet", juce::NotificationType::sendNotification);
        }
        else if (t == 80) {
            helpLabel.setText("Play loud!", juce::NotificationType::sendNotification);
        }
        else if (t == 60) {
            helpLabel.setText("Make some mistakes", juce::NotificationType::sendNotification);
        }
        else if (t == 50) {
            helpLabel.setText("Play some high notes", juce::NotificationType::sendNotification);
        }
        else if (t == 30) {
            helpLabel.setText("Play some low notes", juce::NotificationType::sendNotification);
        }
        else if (t == 10) {
            helpLabel.setText("Almost done.. Let it ring out!", juce::NotificationType::sendNotification);
        }
    }
}
