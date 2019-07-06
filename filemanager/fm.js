function compressurlfile(source) {
  document.getElementById('msg').innerHTML = "Fetching file...";
  var request = new XMLHttpRequest();
  request.onreadystatechange = function () {
    var DONE = this.DONE || 4;
    if (this.readyState === DONE) {
      var data = this.responseText;
      var gzip = require('gzip-js'), options = { level: 9, name: source, timestamp: parseInt(Date.now() / 1000, 10) };
      var out = gzip.zip(data, options);
      var bout = new Uint8Array(out); // out is 16 bits...

      document.getElementById('msg').innerHTML = "Sending compressed file...";
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
  var request = new XMLHttpRequest();
  request.onreadystatechange = function () {
    var DONE = this.DONE || 4;
    if (this.readyState === DONE) {
      var res = this.responseText.split("##");
      document.getElementById('fi').innerHTML = res[0];
      document.getElementById("o3").innerHTML = res[1];
      document.getElementById('msg').innerHTML = "";
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
    document.getElementById('msg').innerHTML = "Please wait. Delete in progress...";
    executecommand("del=" + filename);
  }
}

function renamefile(filename) {
  var newname = prompt("new name for " + filename, filename);
  if (newname != null) {
    document.getElementById('msg').innerHTML = "Please wait. Rename in progress...";
    executecommand("ren=" + filename + "&new=" + newname);
  }
}

var editxhr;

function editfile(filename) {
  document.getElementById('msg').innerHTML = "Please wait. Creating editor...";

  editxhr = new XMLHttpRequest();
  editxhr.onreadystatechange = function () {
    var DONE = this.DONE || 4;
    if (this.readyState === DONE) {
      document.getElementById('fi').innerHTML = editxhr.responseText;
      document.getElementById("o3").innerHTML = "Edit " + filename;
      document.getElementById('msg').innerHTML = "";
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

function uploadFile(file) {
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function () {
    var DONE = this.DONE || 4;
    if (this.readyState === DONE) {
      getfileinsert();
    }
  };
  xhr.open('POST', '/r');
  var formdata = new FormData();
  formdata.append('uploadfile', file);
  xhr.send(formdata);
}

function dropHandler(ev) {
  console.log('File(s) dropped');

  document.getElementById('msg').innerHTML = "Please wait. Transferring file...";

  // Prevent default behavior (Prevent file from being opened)
  ev.preventDefault();

  if (ev.dataTransfer.items) {
    // Use DataTransferItemList interface to access the file(s)
    for (var i = 0; i < ev.dataTransfer.items.length; i++) {
      // If dropped items aren't files, reject them
      if (ev.dataTransfer.items[i].kind === 'file') {
        var file = ev.dataTransfer.items[i].getAsFile();
        uploadFile(file);
        console.log('.1. file[' + i + '].name = ' + file.name);
      }
    }
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

function downloadall() {
  document.getElementById('msg').innerHTML = "Sending all files in one zip.";
  window.location.href = "/c?za=all";
  document.getElementById('msg').innerHTML = "";
}

//->
window.onload = getfileinsert;

