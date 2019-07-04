const http = require('http');
const renderview = require('./renderview.js');
const readline = require('readline');
const fs = require('fs');

const port = 40001;
const configFileArgNum = 2; // With respect to 0 index

if (process.argv.length < configFileArgNum + 1)
{
    console.log("ERROR: Incorrect number of arguments supplied");
    console.log("Usage: node app.js [config/file/name]");
} // if
else
{
    // Configuration file name from command line arguments
    var configFile = process.argv[configFileArgNum]

    // parseConfigFile - reads config file and returns map parameter->value
    function parseConfigFile(configFileName)
    {
        // Array to convert to map
        var configArray = [];
        var lines = fs.readFileSync(configFileName, 'utf-8').split('\n');
        for (var index = 0; index < lines.length; ++index)
        {
            if (lines[index].includes('#') == false)
            {
                if (lines[index].includes('=') == true)
                {
                    var splitLine = lines[index].split('=');
                    if (splitLine.length == 2)
                    {
                        configArray.push([splitLine[0], splitLine[1]]);
                    } // if
                } // if
            } // if
        } // for
        var map = new Map(configArray);
        return map;
    } // parseConfigFile

    var config = parseConfigFile(configFile);

    var imageFileDirectory = config.get('ImageSaveDirectory');
    renderview.SetImageFileDirectory(imageFileDirectory);

    const server = http.createServer((req, res) => {
        renderview.process(req, res);
    }).listen(port, () => {
        console.log('Server running');
    });
} // else
