#ifndef WAV_READER_HPP
#define WAV_READER_HPP

#include <cstdint>
#include <fstream>
#include <string>

class WavReader
{
public:
    WavReader();
    ~WavReader();

    bool LoadWavFile(const std::string & wavString);

private:
    bool Deserialize(void);
    std::uint32_t Serialize(void);

    std::uint16_t LitteToBigEndian(const std::uint16_t * buffer);
    std::uint32_t LittleToBigEndian(const std::uint32_t * buffer);

    std::ifstream   mInputFileStream;
    std::uint8_t*   mWavFileBuffer;
    std::uint32_t   mBufferOffset;

    // Wave structure fields
	// Chunk 1
    std::uint32_t mChunkSize;		// 32 + subChunk2Size
	// Subchunk 1 size
    std::uint32_t mSubchunk1Size;	// 16 for PCM
    std::uint16_t mAudioFormat;		// PCM = 1, Anything else has compression
    std::uint16_t mNumberOfChannels;	// 1 = mono, 2 = stereo, etc...
    std::uint32_t mSampleRate;		// Common values: 8000, 44100
    std::uint32_t mByteRate;		// = SampleRate * NumChannels * BitsPerSample / 8;
    std::uint32_t mBlockAlign;		// = NumChannels * BitsPerSample / 8
    std::uint16_t mBitsPerSample;	
	// Subchunk 2 size
    std::uint32_t mSubchunk2Size;	// = NumSamples * NumChannels * BitsPerSample / 8
    
    static const std::uint16_t UPPER_EIGHT_BITS_MASK;
    static const std::uint16_t LOWER_EIGHT_BITS_MASK;
    static const std::uint32_t FIRST_BYTE_INT_32;
    static const std::uint32_t SECOND_BYTE_INT_32;
    static const std::uint32_t THIRD_BYTE_INT_32;
    static const std::uint32_t FOURTH_BYTE_INT_32;

    static const std::uint16_t ONE_BYTE_SHIFT;
    static const std::uint16_t TWO_BYTE_SHIFT;
    static const std::uint16_t THREE_BYTE_SHIFT;
}; // WavReader

#endif /* WAV_READER_HPP */
