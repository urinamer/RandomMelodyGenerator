#include <iostream>
#ifndef NOTE
#define NOTE

class Note {
public:
    Note(double musicalDuration,std::string name,int octave, int bpm,int freqIndex);
    void playNote() const;
    std::string getName();
    int getOctave();
    int getIndex();
private:
    double duration; //in ms
    double frequency;
    std::string name;
    int octave;
    int freqIndex;
};

#endif