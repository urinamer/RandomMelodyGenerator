#include <iostream>
#include "Melody.h"
#include <map>
#include <random>

std::map<std::string, double> Melody::noteFrequencyMap = 
{
    {"A0", 27.50}, {"A#0", 29.14}, {"B0", 30.87},

    {"C1", 32.70}, {"C#1", 34.65}, {"D1", 36.71}, {"D#1", 38.89}, {"E1", 41.20}, {"F1", 43.65}, {"F#1", 46.25}, {"G1", 49.00}, {"G#1", 51.91}, {"A1", 55.00}, {"A#1", 58.27}, {"B1", 61.74},

    {"C2", 65.41}, {"C#2", 69.30}, {"D2", 73.42}, {"D#2", 77.78}, {"E2", 82.41}, {"F2", 87.31}, {"F#2", 92.50}, {"G2", 98.00}, {"G#2", 103.83}, {"A2", 110.00}, {"A#2", 116.54}, {"B2", 123.47},

    {"C3", 130.81}, {"C#3", 138.59}, {"D3", 146.83}, {"D#3", 155.56}, {"E3", 164.81}, {"F3", 174.61}, {"F#3", 185.00}, {"G3", 196.00}, {"G#3", 207.65}, {"A3", 220.00}, {"A#3", 233.08}, {"B3", 246.94},

    {"C4", 261.63}, {"C#4", 277.18}, {"D4", 293.66}, {"D#4", 311.13}, {"E4", 329.63}, {"F4", 349.23}, {"F#4", 369.99}, {"G4", 392.00}, {"G#4", 415.30}, {"A4", 440.00}, {"A#4", 466.16}, {"B4", 493.88},

    {"C5", 523.25}, {"C#5", 554.37}, {"D5", 587.33}, {"D#5", 622.25}, {"E5", 659.25}, {"F5", 698.46}, {"F#5", 739.99}, {"G5", 783.99}, {"G#5", 830.61}, {"A5", 880.00}, {"A#5", 932.33}, {"B5", 987.77},

    {"C6", 1046.50}, {"C#6", 1108.73}, {"D6", 1174.66}, {"D#6", 1244.51}, {"E6", 1318.51}, {"F6", 1396.91}, {"F#6", 1479.98}, {"G6", 1567.98}, {"G#6", 1661.22}, {"A6", 1760.00}, {"A#6", 1864.66}, {"B6", 1975.53},

    {"C7", 2093.00}, {"C#7", 2217.46}, {"D7", 2349.32}, {"D#7", 2489.02}, {"E7", 2637.02}, {"F7", 2793.83}, {"F#7", 2959.96}, {"G7", 3135.96}, {"G#7", 3322.44}, {"A7", 3520.00}, {"A#7", 3729.31}, {"B7", 3951.07},

    {"C8", 4186.01}
};

Melody::Melody(int bpm, std::string scale,std::string mode, int duration) {
    this->bpm = bpm;
    this->scale = scale;
    this->mode = mode;
    this->duration = duration;

}

void Melody::playMelody() const {
    for (int i = 0; i < melodyVector.size(); i++) {
        melodyVector.at(i).playNote();//Beep waits until the note duration is finished
    }
}

void Melody::generateMelody() {
    std::vector<std::string> scaleNotes = getScaleVector(this->scale, this->mode);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> noteDist(0, 6);


    int noteNum = noteDist(gen);
    std::uniform_int_distribution<> octaveDist(1, 7);
    int octave = octaveDist(gen);
    std::string note = scaleNotes.at(noteNum);
    Note firstNote(getRhythmMeasure(), note, octave, 120,noteNum);
    Melody::melodyVector.push_back(firstNote);

}




Note generateNextNote(Note currentNote, std::vector<std::string> scaleNotes) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> weighted({25,25,30,10});
    

    int newIndex;


    int dist = weighted(gen);
    switch (dist) {
        case 0:
            return Note(getRhythmMeasure(), scaleNotes.at((currentNote.getIndex() + 1) % scaleNotes.size()), currentNote.getOctave(), 120, currentNote.getIndex());
    }

}




std::vector<std::string> getScaleVector(std::string scale, std::string mode) {
    std::vector<std::string> chromaticScale = {
        "A","A#","B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"
    };

    std::map<std::string, std::vector<int>> modeMap = {
        {"major",{2,2,1,2,2,2,1}},
        {"minor",{2,1,2,2,1,2,2}}
    };

    std::vector<int> intervals = modeMap.at(mode);
    std::vector<std::string> scaleVector;

    int i = 0;
    while (chromaticScale.at(i) != scale) {
        i++;
    }
    
    for (int j = 0; j < intervals.size(); j++) {
        scaleVector.push_back(chromaticScale.at(i));
        i = (i + intervals.at(j)) % chromaticScale.size();
    }

    return scaleVector;
}

double getRhythmMeasure()
 {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> weighted({30,50,10});
    double rhythm = weighted(gen);
    if (rhythm == 0) {
        return 0.5;
    }
    if (rhythm == 1) {
        return 0.25;
    }

    if (rhythm == 2) {
        return 0.125;
    }
}

void Melody::setMelodyVector(const std::vector<Note>& melody) {
    this->melodyVector = melody;
}
