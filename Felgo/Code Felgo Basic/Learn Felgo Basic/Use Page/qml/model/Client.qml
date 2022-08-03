import QtQuick 2.0
import Felgo 3.0

Item {
    QtObject{
        id: _
        property string serverUrl: "https://lovehands.vn/wp-json/wp/v2/"
        function solveUrlProduct(paramUrl){
            return serverUrl + paramUrl
        }

        function getData(callback){
            const data = null;

            const xhr = new XMLHttpRequest();
            xhr.withCredentials = true;

            xhr.onreadystatechange = function () {
                if (this.readyState === this.DONE) {
                    console.log("ádfas")
                    console.log(this.responseText.toString());
                    callback("a");
                }//this có còn như js k???
                else{
                    console.log("else nhé")
                }
            };

            xhr.open("GET", "https://voicerss-text-to-speech.p.rapidapi.com/?key=87633a58ad034b3a85334a307182361b&hl=vi-vn&src=Xin%20ch%C3%A0o&f=8khz_8bit_mono&c=mp3&r=0");
            xhr.setRequestHeader("x-rapidapi-host", "voicerss-text-to-speech.p.rapidapi.com");
            xhr.setRequestHeader("x-rapidapi-key", "fe74521ca2msh88eabf1caca8903p1fa436jsn7531238bc68e");

            xhr.send(data);
        }
    }
    function getVoice(callback){
        _.getData(callback);
    }
}
