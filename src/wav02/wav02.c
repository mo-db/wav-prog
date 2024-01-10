#include "stdio.h"
#include "string.h"
#include "math.h"

struct wav_header {
    // RIFF chunk
    char chunkID[4];            // big
    int32_t chunkSize;          // little
    char format[4];             // big
    // fmt chunk
    char subChunk1ID[4];        // big
    int32_t subchunk1Size;      // little
    int16_t audioFormat;        // little
    int16_t numChannels;        // little
    int32_t sampleRate;         // little
    int32_t bytesPerSecond;     // little
    int16_t blockAlign;     // little
    int16_t bitsPerSample;      // little
    // data chunk
    char subchunk2ID[4];        // big
    int32_t subchunk2Size;      // little
};

int main()
{
    const int SampleRate = 44100;
    const int DurationSec = 10;
    const int NumSamples = SampleRate * DurationSec;

    struct wav_header wavh;

    strncpy(wavh.chunkID, "RIFF", 4);
    strncpy(wavh.format, "WAVE", 4);
    strncpy(wavh.subChunk1ID, "fmt ", 4);
    strncpy(wavh.subchunk2ID, "data", 4);

    wavh.audioFormat = 1;
    wavh.numChannels = 1;
    wavh.sampleRate = SampleRate;
    wavh.bitsPerSample = 16;
    wavh.blockAlign = wavh.numChannels *wavh.bitsPerSample/8;
    wavh.bytesPerSecond = SampleRate * wavh.numChannels * wavh.bitsPerSample/8;

    wavh.subchunk1Size = 16;
    wavh.subchunk2Size = NumSamples * wavh.numChannels * wavh.bitsPerSample/8;
    wavh.chunkSize = 36 + wavh.subchunk2Size;

    int data[NumSamples];

    // oscillator
    const int freq = 8800;
    const int amp = 10000;
    for (int i = 0; i < NumSamples; i++) {
        data[i] = (short int)(sin((2 * M_PI * freq * i) / SampleRate) * amp);
    }

    FILE *fp = fopen("test2.wav", "w");
    fwrite(&wavh, 1, sizeof(wavh), fp);
    fwrite(data, 2, NumSamples, fp);

    for (int i = 0; i < NumSamples; i++) {
        printf("%d\n", data[i]);
    }

}