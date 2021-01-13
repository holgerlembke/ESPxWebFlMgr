function compressurlfile(source) {
  msgline("Fetching file...");
  var request = new XMLHttpRequest();
  request.onreadystatechange = function () {
    var DONE = this.DONE || 4;
    if (this.readyState === DONE) {
      var data = this.responseText;
      var gzip = require('gzip-js'), options = { level: 9, name: source, timestamp: parseInt(Date.now() / 1000, 10) };
      var out = gzip.zip(data, options);
      var bout = new Uint8Array(out); // out is 16 bits...

      msgline("Sending compressed file...");
      var sendback = new XMLHttpRequest();
      sendback.onreadystatechange = function () {
        var DONE = this.DONE || 4;
        if (this.readyState === DONE) {
          getfileinsert();
        }
      };
      sendback.open('POST', '/r');
      var formdata = new FormData();
      var blob = new Blob([bout], { type: "application/octet-binary" });
      formdata.append(source + '.gz', blob, source + '.gz');
      sendback.send(formdata);
    }
  };
  request.open('GET', source, true);
  request.send(null);
}

function getfileinsert() {
  msgline("Fetching files infos...");
  var request = new XMLHttpRequest();
  request.onreadystatechange = function () {
    var DONE = this.DONE || 4;
    if (this.readyState === DONE) {
      var res = this.responseText.split("##");
      document.getElementById('fi').innerHTML = res[0];
      document.getElementById("o3").innerHTML = res[1];
      msgline("");
    }
  };
  request.open('GET', '/i', true);
  request.send(null);
}

function executecommand(command) {
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function () {
    var DONE = this.DONE || 4;
    if (this.readyState === DONE) {
      getfileinsert();
    }
  };
  xhr.open('GET', '/c?' + command, true);
  xhr.send(null);
}

function downloadfile(filename) {
  window.location.href = "/c?dwn=" + filename;
}

function deletefile(filename) {
  if (confirm("Really delete " + filename)) {
    msgline("Please wait. Delete in progress...");
    executecommand("del=" + filename);
  }
}

function renamefile(filename) {
  var newname = prompt("new name for " + filename, filename);
  if (newname != null) {
    msgline("Please wait. Rename in progress...");
    executecommand("ren=" + filename + "&new=" + newname);
  }
}

var editxhr;

function editfile(filename) {
  msgline("Please wait. Creating editor...");

  editxhr = new XMLHttpRequest();
  editxhr.onreadystatechange = function () {
    var DONE = this.DONE || 4;
    if (this.readyState === DONE) {
      document.getElementById('fi').innerHTML = editxhr.responseText;
      document.getElementById("o3").innerHTML = "Edit " + filename;
      msgline("");
    }
  };
  editxhr.open('GET', '/e?edit=' + filename, true);
  editxhr.send(null);
}

function sved(filename) {
  var content = document.getElementById('tect').value;
  // utf-8
  content = unescape(encodeURIComponent(content));

  var xhr = new XMLHttpRequest();

  xhr.open("POST", "/r", true);

  var boundary = '-----whatever';
  xhr.setRequestHeader("Content-Type", "multipart/form-data; boundary=" + boundary);

  var body = "" +
    '--' + boundary + '\r\n' +
    'Content-Disposition: form-data; name="uploadfile"; filename="' + filename + '"' + '\r\n' +
    'Content-Type: text/plain' + '\r\n' +
    '' + '\r\n' +
    content + '\r\n' +
    '--' + boundary + '--\r\n' +        // \r\n fixes upload delay in ESP8266WebServer
    '';

  // ajax does not do xhr.setRequestHeader("Content-length", body.length);

  xhr.onreadystatechange = function () {
    var DONE = this.DONE || 4;
    if (this.readyState === DONE) {
      getfileinsert();
    }
  }

  xhr.send(body);
}

function abed() {
  getfileinsert();
}

var uploaddone = true; // hlpr for multiple file uploads

function uploadFile(file, islast) {
  uploaddone = false;
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function () {
    // console.log(xhr.status);
    var DONE = this.DONE || 4;
    if (this.readyState === DONE) {
      if (islast) {
        getfileinsert();
        console.log('last file');
      }
      uploaddone = true;
    }
  };
  xhr.open('POST', '/r');
  var formdata = new FormData();
  formdata.append('uploadfile', file);
  // not sure why, but with that the upload to esp32 is stable.
  formdata.append('dummy', 'dummy');
  xhr.send(formdata);
}

var globaldropfilelisthlpr = null; // read-only-list, no shift()
var transferitem = 0;
var uploadFileProzessorhndlr = null;

function uploadFileProzessor() {
    if (uploaddone) {
        if (transferitem==globaldropfilelisthlpr.length) {
            clearInterval(uploadFileProzessorhndlr);
        } else {
            var file = globaldropfilelisthlpr[transferitem];
            msgline("Please wait. Transferring file "+file.name+"...");
            console.log('process file ' + file.name);
            transferitem++;
            uploadFile(file,transferitem==globaldropfilelisthlpr.length);
        }
    }
}

function dropHandler(ev) {
  console.log('File(s) dropped');
  
  globaldropfilelisthlpr = ev.dataTransfer;
  transferitem = 0;

  msgline("Please wait. Transferring file...");

  // Prevent default behavior (Prevent file from being opened)
  ev.preventDefault();

  if (ev.dataTransfer.items) {
      var data = ev.dataTransfer;
      globaldropfilelisthlpr = data.files;
      uploadFileProzessorhndlr = setInterval(uploadFileProzessor,1000);
      console.log('Init upload list.');
  } else {
    // Use DataTransfer interface to access the file(s)
    for (var i = 0; i < ev.dataTransfer.files.length; i++) {
      console.log('.2. file[' + i + '].name = ' + ev.dataTransfer.files[i].name);
    }
  }
}

function dragOverHandler(ev) {
  console.log('File(s) in drop zone');

  // Prevent default behavior (Prevent file from being opened)
  ev.preventDefault();
}

function msgline(msg) {
  document.getElementById('msg').innerHTML = msg;
}

function downloadall() {
  msgline("Sending all files in one zip.");
  window.location.href = "/c?za=all";
  msgline("");
}

//->
window.onload = getfileinsert;

