// Requires
var fs = require("fs");
var path = require('path');

// Variables
var htmlHeader = { 'Content-Type': 'html' };
var jpgHeader = { 'Content-Type': 'image/jpg' }
var mImageFileDirectory = "."

// mergeValues - replace string content with values from key/value Object
function mergeValues(values, content) {
  for (var key in values) {
    var reg = new RegExp("{{" + key + "}}", "g");
    content = content.replace(reg, values[key])
  }
  return content;
} // mergeValues

function SetImageFileDirectory(imageFileDirectory)
{
    mImageFileDirectory = imageFileDirectory
} // SetImageFileDirectory

// view - get templateName.html,
function view(templateName, values, res) {
  var fileContent = fs.readFileSync('./views/' + templateName + '.html', 'utf8');
  fileContent = mergeValues(values, fileContent);
  res.write(fileContent);
} // view

// process - append output to res, and return to calling function
function process(req, res)
{
    if (req.url === "/")
    {
        res.writeHead(200, htmlHeader);
        view('header', {}, res);
        view('intro', {}, res);

        // Read files in image directory
        var files = fs.readdirSync(mImageFileDirectory);
        //listing all files using forEach

        for (var i = 0; i < files.length; ++i)
        {
            var timestampString = files[i].split('.');
            var timestampIntMillis = parseInt(timestampString) * 1000;
            var dateRepresentation = new Date(timestampIntMillis);

            view('detection', {'imagename': dateRepresentation, 'imagelink': mImageFileDirectory + "/" + files[i]}, res);
        } // for

        view('footer', {}, res);
        res.end();
    } // if
    else if (req.url.match("\.jpg"))
    {
        var imagePath = req.url;
        var fileStream = fs.createReadStream(imagePath);
        res.writeHead(200, jpgHeader);
        fileStream.pipe(res);
    } // if
    else{
        res.writeHead(404, {"Content-Type": "text/html"});
        res.end("No Page Found");
    } // else

} // process

// API
module.exports.process = process
module.exports.SetImageFileDirectory = SetImageFileDirectory
