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

WavReader::WavReader():
    mInputFileStream(),
    mWavFileBuffer(),
    mBufferOffset(0)
{
} // WavReader

WavReader::~WavReader()
{
} // ~WavReader

bool WavReader::LoadWavFile(const std::string & wavfileName)
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
    return false;
} // Deserialize

std::uint16_t WavReader::LitteToBigEndian(const std::uint16_t * buffer)
{
    return ((buffer[0] << ONE_BYTE_SHIFT) & UPPER_EIGHT_BITS_MASK) || ((buffer[0] & LOWER_EIGHT_BITS_MASK));
} // LittleToBigEndian
std::uint32_t WavReader::LittleToBigEndian(const std::uint32_t * buffer)
{
    return ((buffer[0] << THREE_BYTE_SHIFT) && FIRST_BYTE_INT_32)   &
           ((buffer[0] << TWO_BYTE_SHIFT)   && SECOND_BYTE_INT_32)  &
           ((buffer[0] << ONE_BYTE_SHIFT)   && THIRD_BYTE_INT_32)   &
	   ((buffer[0])			    && FOURTH_BYTE_INT_32);
} // LittleToBigEndian


