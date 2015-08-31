
//
//  HTML PAGE
//
const char PAGE_NetworkConfiguration[] PROGMEM = R"=====(
 <!DOCTYPE html>
<html>
<head>
  
</head> 
<body>
  hello!
</body>

</html> 
)=====";

const char PAGE_ModuleName[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
module{
  type:relay
}
</html>
)=====";

const char PAGE_Index[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
<a href="/modulename">nome e scopo del modulo</a><br>
<a href="/gpio/1">spegni pin 1</a><br>
<a href="/gpio/0">accendi pin 1</a><br>
<a href="/image">mostra un immagine</a><br>
</html> 
)=====;

const char PAGE_Image[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
<img src=\"https://siluxmedia.files.wordpress.com/2014/04/img_20140409_165718.jpg\" alt=\"arduino\" height=\"612\" width=\"816\">
</html> 
)=====;

const char PAGE_Button[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
<form formaction="button" formmethod="get">
nome rete: <input type= "text" name="fname"><br>
password: <input type="password" name="lname"><br>
<input type="submit" value="Submit">
</form>
</html>
)=====";

const char PAGE_Slider[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
<form method="get"><br>Red:  <input type='range' min='1' max='100' name=redVal value=redTemp oninput='showValue(this.value)'>
<span id='range'>0</span>
<script type='text/javascript'>
function showValue(newValue)
{
  document.getElementById('range').innerHTML=newValue;
  }
  </script>
  
<br><br>Green:  <input type='range' min='1' max='100' name=greVal value=greTemp oninput='showValue1(this.value)'>
<span id='range1'>0</span>");
<script type='text/javascript'>
function showValue1(newValue)
{
  document.getElementById('range1').innerHTML=newValue;
  }
  </script>
<br><br>Blue:  <input type='range' min='1' max='100' name=bluVal value=bluTemp oninput='showValue2(this.value)'>
<span id='range2'>0</span>");
<script type='text/javascript'>
function showValue2(newValue)
{
  document.getElementById('range2').innerHTML=newValue;
  }
  </script>
  
&nbsp;<br><br><input name=H type=submit value=submit><br><br> 
</form>");
<script type='text/javascript'></script>
</html>
)=====";
