function LastUpdate(){
	document.write("<img src='GuznerConsultingS.gif'><FONT SIZE=-1>Updated on 1/23/2016</FONT><hr>");
}

function Header()
{
	LastUpdate();
}


function Hr(){
	document.write("<hr>");
}


function Link2Page(pPath, pLabel, bUpdated)
{
	document.write(' <A HREF="'+pPath+'" target=_blank>');
	if(bUpdated!=null)
		document.write('<B>');
	document.write(pLabel);
	if(bUpdated!=null)
		document.write('</B>');
	document.write('</A>');
}

function More(pAddress){
	Link2Page(pAddress, "More...");
}

function Email(pAddress){
	document.write('<A href="mailto:'+pAddress+
		'?Subject=RegmagiK&amp;body=RegmagiK web address is: http://www.regmagik.com">'+
		pAddress+'</A>');
}

function ContactMe(sSubject){
	document.write('<A href="/contact/">Contact us</A><br>');
}

function SendMessage(pText, pTip, pSubject, pMessage) 
{
	document.write('<A href=');
	document.write('"');
	document.write('mailto:?subject=');
	document.write(pSubject);
	document.write('&amp;body=');
	document.write(pMessage);
	document.write('"');
	document.write('title="'+pTip+'"');
	document.write('>');
	document.write('<IMG border=0 src="icoEmail.gif">');
	document.write(pText);
	document.write('</A>');
}

defaultText="Tell a friend";
defaultTip="e-mail friend(s)";

function TellAFriend(pAddress, pTitle)
{
	if(pAddress==null)
		pAddress=document.location;
	if(pTitle==null)
		pTitle=pAddress;
	SendMessage(defaultText, defaultTip, pTitle, "The address is: " + pAddress);
}


function Copyright(){
	document.write("<font size=-1><p><i>"+
		"Copyright &copy; 1999-2016 <a href='/contact/'>Boris Guzner</a>. All rights reserved."+
		"</i></p></font>");
}


function Footer(){
	Hr();
	Copyright();
}

