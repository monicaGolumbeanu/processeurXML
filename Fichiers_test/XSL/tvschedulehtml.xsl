<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">

<!--TVSCHEDULEHTML.XSL:  Stylesheet to transform 
TVSCHEDULE XML files into HTML suitable for posting on a website

Version 1.02

David Moisan
20 May 1999

Revisions:  
-->

<xsl:template match="/">
<html>
<head>

<link rel="stylesheet" href="/~dmoisan/styles/satv.css"
type="text/css" title="Salem Access TV Stylesheet"/>

<title>Schedule for <xsl:value-of select="TVSCHEDULE/@NAME"/></title>
</head>
<body>
<h1><xsl:value-of select="TVSCHEDULE/@NAME"/></h1>

<xsl:apply-templates match="TVSCHEDULE"/>
<hr/>
<p><strong>IMPORTANT!</strong>  This schedule page is provided as an experimental service.
<em>It is not affiliated with Salem Access Television in any way.</em>
Accuracy is not guaranteed.</p>
<p>For information about Salem Access Television, visit the <a HREF="http://www.satvonline.org/">SATV Online</a> website.
For information about this web page and XML in general, contact <a HREF="mailto:dmoisan@shore.net">Dave Moisan</a>.</p>

<div class="gennav">
<hr/>
[<a href="/~dmoisan/comp/videoxml.html">Video for XML</a>]<br/>
[<a href="/~dmoisan/computer.html">Wakko's Computer Page</a>]
<br/>[<a HREF="/~dmoisan/welcome.html">Dave Moisan's Home Page</a>]
<hr/>
</div>

<address class="pageinfo">
David Moisan
<br/><a href="mailto:dmoisan@shore.net">dmoisan@shore.net</a>
<br/>
</address>
</body>
</html>
</xsl:template>

<xsl:template match="TVSCHEDULE">
<xsl:apply-templates/>
</xsl:template>

<xsl:template match="CHANNEL">
<H2><xsl:value-of select="/TVSCHEDULE/@NAME"/> Channel <xsl:value-of select="@CHAN"/></H2>
<xsl:apply-templates/>
</xsl:template>

<xsl:template match="BANNER">
<H3><xsl:value-of select="."/></H3>
</xsl:template>

<xsl:template match="DAY">
<!-- Match all programming DAYs
 -->
<xsl:apply-templates/>

</xsl:template>

<xsl:template match="DATE">
<H4><xsl:value-of select="."/></H4>
</xsl:template>


<!--Test for HOLIDAY and print out its associated message -->
<xsl:template match="HOLIDAY">
<xsl:value-of select="."/><BR/>
</xsl:template>

<xsl:template match="DAY/PROGRAMSLOT">
<!--Output time and program title -->
<xsl:value-of select="TIME"/>: <xsl:value-of select="TITLE"/>
<!-- Include optional DESCRIPTION and RATING items -->
<xsl:if test="DESCRIPTION">
<EM><STRONG><xsl:value-of select="DESCRIPTION"/></STRONG></EM>
</xsl:if>
<BR/>
<xsl:if test="TITLE/@RATING">
<EM>Rating: <xsl:value-of select="TITLE/@RATING"/></EM><BR/>
</xsl:if>
</xsl:template>
</xsl:stylesheet>
