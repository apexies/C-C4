
var sensorVal1;

var aiokey = "117d6eda7a35489ba5fd780ded9df06b";
var feedName = "Microphone";
function setup() {
  
createCanvas(600,600);
setInterval(askAIO,800);
}

function draw() {

background(255);  
textSize(25);
textFont("Helvetica");
  text("How loud is the DF Lounge right now?", 10, 30) 
  //fill(255,0,0);
 noStroke();
 ellipse(canvas.width/4,canvas.height/4,sensorVal1/2,sensorVal1/2);
if (sensorVal1>500){
  fill(255,0,0);
  textSize(25);
  textFont("Helvetica");
  text("Noisy", width/2, 70);
//  fill(255,0,0);
  }
else if (sensorVal1>200){
  fill(244,155,66);
  textSize(25);
  textFont("Helvetica");
  text("Average noise", width/2, 70);
}
else {
  fill(134,244,66);
  textSize(25);
  textFont("Helvetica");
  text("Quiet", width/2, 70);
}
}

function receivedData(data)
{

sensorVal1 = parseInt(data.value); 
println(sensorVal1);
}




function askAIO()
{
    loadJSON("https://io.adafruit.com/api/feeds/"+feedName+"/data/last.json?x-aio-key="+aiokey, receivedData);
   
}
  

