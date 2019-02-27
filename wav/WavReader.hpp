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
    bool Validate(void);
    std::uint32_t Serialize(void);

    std::uint16_t LittleToBigEndian(const std::uint16_t * buffer);
    std::uint32_t LittleToBigEndian(const std::uint32_t * buffer);

    // Wave structure fields
    struct WavHeader_s
    {
        char            RIFF[4];
        std::uint32_t   mChunkSize;
        char            WAVE[4];
    }; // WavHeader_s

    struct SubChunk1_s
    {
        char            mSubchunk1Id[4];
        std::uint16_t   mSubchunk1Size;
        std::uint16_t   mAudioFormat;
        std::uint16_t   mNumChannels;
        std::uint32_t   mSampleRate;
        std::uint32_t   mByteRate;
        std::uint16_t   mBlockAlign;
        std::uint16_t   mBitsPerSample;
    }; // SubChunk1

    struct SubChunk2_s
    {
        char            DATA[4];
        std::uint32_t   mSubchunk2Size;

#warning NEED TO IMPLEMENT DATA

    }; // SubChunk2

    std::ifstream   mInputFileStream;
    std::uint8_t*   mWavFileBuffer;
    std::uint32_t   mBufferOffset;

    WavHeader_s mWaveHeader;
    SubChunk1_s mSubchunk1;
    SubChunk2_s mSubchunk2;

    static const std::uint16_t UPPER_EIGHT_BITS_MASK;
    static const std::uint16_t LOWER_EIGHT_BITS_MASK;
    static const std::uint32_t FIRST_BYTE_INT_32;
    static const std::uint32_t SECOND_BYTE_INT_32;
    static const std::uint32_t THIRD_BYTE_INT_32;
    static const std::uint32_t FOURTH_BYTE_INT_32;

    static const std::uint16_t ONE_BYTE_SHIFT;
    static const std::uint16_t TWO_BYTE_SHIFT;
    static const std::uint16_t THREE_BYTE_SHIFT;

    static const std::uint16_t FOUR_BYTES;
    static const std::uint16_t TWO_BYTES;
}; // WavReader

#endif /* WAV_READER_HPP */
