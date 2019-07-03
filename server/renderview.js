var commonHeader = { 'Content-Type': 'html' };

// process - append output to res, and return to calling function
function process()
{
    res.writeHead(200, commonHeader);
} // process


// API
module.exports.process = process
