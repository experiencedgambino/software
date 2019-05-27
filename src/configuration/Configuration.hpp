#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <fstream>
#include <sstream>
#include <iostream>

class Configuration
{
public:
    // Constructor
    inline Configuration();

    // Parse configuration file
    inline bool parseConfig(const std::string & configPath);

    // Read configration parameter into vector of all instances
    template <typename T>
    inline bool readParameter(const std::string & configurationParameterName, std::vector<T> & configurationParameterStore);

    // Read configuration parameter into object
    template <typename T>
    inline bool readParameter(const std::string & configurationParameterName, T & configurationParameterStore);

private:
    std::vector<std::pair<std::string, std::string> > configurationParameterVector {};
    std::stringstream mParameterStringStream;
    static const char CONFIGURATION_DELIMITER = '=';
    static const char CONFIGURATION_COMMENT_DELIMITER = '#';

}; // Configuration

// Constructor
inline Configuration::Configuration()
{

} // Configuration

// Parse configuration file
inline bool Configuration::parseConfig(const std::string & configPath)
{
    bool return_value = true;
    std::string current_line;
    std::ifstream configuration_file_stream;
    configuration_file_stream.open(configPath);
    if (configuration_file_stream.good() == true)
    {
        while (std::getline(configuration_file_stream, current_line)) {
            if (current_line.size() == 0)
            {
                // Nothing in line, do nothing.
            }
            else if (current_line[0] == CONFIGURATION_COMMENT_DELIMITER)
            {
                // Found comment, do nothing.
            } // else if
            else
            {
                std::size_t delimiter_index = current_line.find(CONFIGURATION_DELIMITER);
                if (delimiter_index != std::string::npos)
                {
                    // Add completed configuration parameter to vector
                    configurationParameterVector.push_back(std::pair<std::string, std::string>(
                        current_line.substr(0, delimiter_index),
                        current_line.substr(delimiter_index+1, current_line.size()-delimiter_index) + " "
                    ));
                } // if
                else
                {
                    // Couldn't find delimiter, do nothing.
                } // else
            } // else
        } // while
    } // if
    else
    {
        // Failed to open file
        return_value = false;
    } // else

    return return_value;
} // parseConfig

// Read configration parameter into vector of all instances
template <typename T>
inline bool Configuration::readParameter(const std::string & configurationParameterName, std::vector<T> & configurationParameterStore)
{
    bool return_value = false;
    configurationParameterStore.clear();
    std::vector<std::pair<std::string, std::string>>::iterator parameter;
    for (parameter = configurationParameterVector.begin(); parameter != configurationParameterVector.end(); ++parameter)
    {
        if (parameter->first == configurationParameterName)
        {
            mParameterStringStream.str(parameter->second);
            configurationParameterStore.emplace_back();
            mParameterStringStream >> configurationParameterStore.back();
            return_value = true;
        } // if
        else
        {
            // Parameter not found, do nothing.
        } // else
    } // for
    return return_value;
} // readParameter

// Read configuration parameter into object
template <typename T>
inline bool Configuration::readParameter(const std::string & configurationParameterName, T & configurationParameterStore)
{
    bool return_value = false;
    std::vector<std::pair<std::string, std::string>>::iterator parameter;
    for (parameter = configurationParameterVector.begin(); parameter != configurationParameterVector.end(); ++parameter)
    {
        if (parameter->first == configurationParameterName)
        {
            mParameterStringStream.str(parameter->second);
            mParameterStringStream >> configurationParameterStore;
            return_value = true;
            break;
        } // if
        else
        {
            // Parameter not found, do nothing.
        } // else
    } // for
    return return_value;
} // readParameter

#endif // CONFIGURATION_HPP
