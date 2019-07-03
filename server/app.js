const http = require('http');
const renderview = require('./renderview.js');

const port = 40001;

const server = http.createServer((req, res) => {
    renderview.process(req, res);
}).listen(port, () => {
    console.log('Server running');
});
