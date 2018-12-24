<?php

echo ("Thank you for visiting RegmagiK."); 

echo ("<br>Before Name2SN..."); 
function Name2SN($name)
{
echo ("Inside Name2SN()..."); 
	$sn = getenv('KEYSECRET');
	$len = mb_strlen($name);
	for ($i = 0; $i < $len; $i++)
	{
	  $letter = mb_substr($name, $i, 1);
	  echo($i . ":" . $letter);
	  if($letter == " ") continue;
	  $value = mb_convert_encoding($letter, 'UTF-16');
	  $b = ord($value[1])&0xff;
//    echo $b . " " . $letter."<br>";
	  $sn += (int)($sn/$b); 
	}
	return $sn;
}
echo ("mb_internal_encoding. UTF-8..."); 
mb_internal_encoding("UTF-8");
$name = $_GET["initals"] ." ". $_GET["name"] ." ". $_GET["email"];
//$name = "Cédric GEORGEOT cgeorgeot@e-novatic.fr";
echo $name. "<br>";

$x = log(Name2SN($name));

$binarydata = pack("d", $x);
$count = strlen($binarydata);
$hex = bin2hex($binarydata);

if($name == "  ") 
{
echo " <ul>
<li><a href=\"/\" >Home.</a>
<li><a href=\"/readme.htm\" >Order license.</a>
</ul>";
}
else
{
echo "<SOFTSHOP>".chunk_split($hex, 2, " ") . "." . $name . "</SOFTSHOP>";
}
?>

