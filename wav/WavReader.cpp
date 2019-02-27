#include "WavReader.hpp"

const std::uint16_t WavReader::UPPER_EIGHT_BITS_MASK = 0xFF00;
const std::uint16_t WavReader::LOWER_EIGHT_BITS_MASK = 0x00FF;
const std::uint32_t WavReader::FIRST_BYTE_INT_32 = 0xFF000000;
const std::uint32_t WavReader::SECOND_BYTE_INT_32 = 0x00FF0000;
const std::uint32_t WavReader::THIRD_BYTE_INT_32 = 0x0000FF00;
const std::uint32_t WavReader::FOURTH_BYTE_INT_32 = 0x000000FF;

const std::uint16_t WavReader::ONE_BYTE_SHIFT = 8;
const std::uint16_t WavReader::TWO_BYTE_SHIFT = 16;
const std::uint16_t WavReader::THREE_BYTE_SHIFT = 24;

const std::uint16_t WavReader::FOUR_BYTES = 4;
const std::uint16_t WavReader::TWO_BYTES = 2;

WavReader::WavReader():
    mInputFileStream(),
    mWavFileBuffer(),
    mBufferOffset(0),
    mSubchunk1(),
    mSubchunk2()
{
} // WavReader

WavReader::~WavReader()
{
} // ~WavReader

bool WavReader::Read(const std::string & wavfileName)
{
    bool return_value = true;
    std::uint32_t length_of_file;
    mInputFileStream.open(wavfileName);
    if (mInputFileStream.is_open() == true)
    {
        // Move to the end of the file to get length
        mInputFileStream.seekg(0, std::ios::end);
        length_of_file = mInputFileStream.tellg();
        // Return to beginning of file to read
        mInputFileStream.seekg(0, std::ios::beg);
        mWavFileBuffer = static_cast<uint8_t *>(malloc(length_of_file));
        mInputFileStream.read(reinterpret_cast<char *>(mWavFileBuffer), length_of_file);
    } // else
    mInputFileStream.close();

    // Deserialize wav file
    return_value = Deserialize();
    
    return return_value;
} // WavReader

bool WavReader::Write(const std::string & wavfileName)
{
    bool return_value = true;
    std::uint32_t length_of_file;
    mInputFileStream.open(wavfileName);
    if (mInputFileStream.is_open() == true)
    {
        // Move to the end of the file to get length
        mInputFileStream.seekg(0, std::ios::end);
        length_of_file = mInputFileStream.tellg();
        // Return to beginning of file to read
        mInputFileStream.seekg(0, std::ios::beg);
        mWavFileBuffer = static_cast<uint8_t *>(malloc(length_of_file));
        mInputFileStream.read(reinterpret_cast<char *>(mWavFileBuffer), length_of_file);
    } // else
    mInputFileStream.close();

    // Deserialize wav file
    return_value = Deserialize();
    
    return return_value;
} // WavReader

bool WavReader::Deserialize(void)
{
    // Reset offset at beginning
    mBufferOffset = 0;

    // Wave file header
    std::memcpy ( mWaveHeader.RIFF, mWavFileBuffer+mBufferOffset, FOUR_BYTES); 
    mBufferOffset+=FOUR_BYTES;
    mWaveHeader.mChunkSize = LittleToBigEndian((std::uint16_t *) mWavFileBuffer+mBufferOffset);
    mBufferOffset+=TWO_BYTES;
    std::memcpy( mWaveHeader.WAVE, mWavFileBuffer+mBufferOffset, FOUR_BYTES);
    mBufferOffset+=FOUR_BYTES;

    // Subchunk 1: Format
    std::memcpy ( mSubchunk1.mSubchunk1Id, mWavFileBuffer+mBufferOffset, FOUR_BYTES);
    mBufferOffset+=FOUR_BYTES;
    mSubchunk1.mSubchunk1Size = LittleToBigEndian((std::uint16_t *) mWavFileBuffer+mBufferOffset);
    mBufferOffset+=TWO_BYTES;
    mSubchunk1.mAudioFormat = LittleToBigEndian((std::uint16_t *) mWavFileBuffer+mBufferOffset);
    mBufferOffset+=TWO_BYTES;
    mSubchunk1.mNumChannels = LittleToBigEndian((std::uint16_t *) mWavFileBuffer+mBufferOffset);
    mBufferOffset+=TWO_BYTES;
    mSubchunk1.mSampleRate = LittleToBigEndian((std::uint32_t *) mWavFileBuffer+mBufferOffset);
    mBufferOffset+=FOUR_BYTES;
    mSubchunk1.mByteRate = LittleToBigEndian((std::uint32_t *) mWavFileBuffer+mBufferOffset);
    mBufferOffset+=FOUR_BYTES;
    mSubchunk1.mBlockAlign = LittleToBigEndian((std::uint16_t *) mWavFileBuffer+mBufferOffset);
    mBufferOffset+=TWO_BYTES;
    mSubchunk1.mBitsPerSample = LittleToBigEndian((std::uint16_t *) mWavFileBuffer+mBufferOffset);
    mBufferOffset+=TWO_BYTES;

    // Subchunk 2: Data
    std::memcpy ( mSubchunk2.DATA, mWavFileBuffer+mBufferOffset, FOUR_BYTES);
    mBufferOffset+=FOUR_BYTES;
    mSubchunk2.mSubchunk2Size = LittleToBigEndian((std::uint32_t *) mWavFileBuffer+mBufferOffset);
    mBufferOffset+=FOUR_BYTES;
    std::memcpy( mSubchunk2.mData, mWavFileBuffer+mBufferOffset, mSubchunk2.mSubchunk2Size);

    return false;
} // Deserialize

bool WavReader::Validate(void)
{
    return false;
} // Validate

std::uint16_t WavReader::LittleToBigEndian(const std::uint16_t * buffer)
{
    return ((buffer[0] << ONE_BYTE_SHIFT) & UPPER_EIGHT_BITS_MASK) || ((buffer[0] & LOWER_EIGHT_BITS_MASK));
} // LittleToBigEndian
std::uint32_t WavReader::LittleToBigEndian(const std::uint32_t * buffer)
{
    return ((buffer[0] << THREE_BYTE_SHIFT) & FIRST_BYTE_INT_32)   &
           ((buffer[0] << TWO_BYTE_SHIFT)   & SECOND_BYTE_INT_32)  &
           ((buffer[0] << ONE_BYTE_SHIFT)   & THIRD_BYTE_INT_32)   &
	       ((buffer[0])			            & FOURTH_BYTE_INT_32);
} // LittleToBigEndian

std::uint16_t WavReader::GetSample(std::uint32_t sampleNumber, WavReader::Channel_e channel)
{
    if (mSubchunk1.mBitsPerSample == SIXTEEN_BITS_PER_SAMPLE)
    {
        return static_cast<std::uint16_t>(reinterpret_cast<std::uint16_t *>(mSubchunk2.mData)[sampleNumber*mSubchunk1.mNumChannels+channel]);
    } // if
    else if (mSubchunk1.mBitsPerSample == EIGHT_BITS_PER_SAMPLE)
    {
        return static_cast<std::uint16_t>(reinterpret_cast<std::uint8_t *>(mSubchunk2.mData)[sampleNumber*mSubchunk1.mNumChannels+channel]);
    } // else if
    else
    {
        return 0;
    } // else

} // GetSample

std::uint16_t WavReader::GetSample(std::uint32_t sampleNumber)
{
    return GetSample(sampleNumber, WavReader::Channel_e::CHANNEL_ONE); // Get channel 1 sample
} // GetSample


