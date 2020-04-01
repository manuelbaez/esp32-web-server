var requestReadyCallback = function() {
    if (this.readyState == 4 && this.status == 200) {
        console.log("Done");
    }
};

var turnOn = function() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = requestReadyCallback;
    xhttp.open("POST", "/switch/turnOn", true);
    xhttp.send();
};

var turnOff = function() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = requestReadyCallback;
    xhttp.open("POST", "/switch/turnOff", true);
    xhttp.send();
};


var coonectWifiOnClick = function($event) {
    $event.preventDefault();
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = () => {
        alert(xhttp.responseText);
    };
    xhttp.open("POST", "/wifiSetup", true);
    var ssid = document.getElementById("ssid").value;
    var password = document.getElementById("password").value;
    xhttp.send(JSON.stringify({
        ssid: ssid,
        password: password
    }));
};


(function() {
    document.getElementById("turn-on-button").onclick = turnOn;
    document.getElementById("turn-off-button").onclick = turnOff;
    document.getElementById("wifi-setup-form").onsubmit = coonectWifiOnClick;
})();