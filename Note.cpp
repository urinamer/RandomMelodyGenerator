#include <iostream>
#include "Note.h"
#include "Melody.h"
#include <Windows.h>
#include <string>


Note::Note(double musicalDuration,std::string name,int octave, int bpm,int freqIndex) {
    double barDuration = 60.0 / bpm * 4; //in seconds
    this->duration = barDuration * musicalDuration * 1000;
    this->name = name + std::to_string(octave);
    if (this->name == "REST")
        this->frequency = 0.0;
    else
        this->frequency = Melody::noteFrequencyMap.at(this->name);
    this->octave = octave;
    this->freqIndex = freqIndex;
}

void Note::playNote() const {
    Beep(this->frequency, this->duration);
}

std::string Note::getName() {
    return this->name;
}

int Note::getOctave() {
    return this->octave;
}

int Note::getIndex() {
    return this->freqIndex;
}


