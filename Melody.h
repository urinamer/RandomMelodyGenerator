#include <iostream>
#include "Note.h"
#include <vector>
#include <map>
#ifndef MELODY
#define MELODY




class Melody {
public:
    Melody(int bmp, std::string scale,std::string mode, int duration);
    void playMelody() const;
    void setMelodyVector(const std::vector<Note>& melody);
    static std::map<std::string, double> noteFrequencyMap;
private:
    int bpm;
    std::string scale;
    std::string mode;
    int duration; //in bars
    std::vector<Note> melodyVector;
    void generateMelody();
};

#endif