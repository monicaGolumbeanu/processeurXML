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
Schedule for <xsl:value-of select="TVSCHEDULE/@NAME"/>

<xsl:value-of select="TVSCHEDULE/@NAME"/>

<xsl:apply-templates match="TVSCHEDULE"/>

</xsl:template>

<xsl:template match="TVSCHEDULE">
<xsl:apply-templates/>
</xsl:template>

<xsl:template match="CHANNEL">
<xsl:value-of select="/TVSCHEDULE/@NAME"/> Channel <xsl:value-of select="@CHAN"/>
<xsl:apply-templates/>
</xsl:template>

<xsl:template match="BANNER">
<xsl:value-of select="."/>
</xsl:template>

<xsl:template match="DAY">
<!-- Match all programming DAYs
 -->
<xsl:apply-templates/>

</xsl:template>

<xsl:template match="DATE">
<xsl:value-of select="."/>
</xsl:template>

<!--Test for HOLIDAY and print out its associated message -->
<xsl:template match="HOLIDAY">
<xsl:value-of select="."/>
</xsl:template>

<xsl:template match="DAY/PROGRAMSLOT">
<!--Output time and program title -->
<xsl:value-of select="TIME"/>: <xsl:value-of select="TITLE"/>

</xsl:template>
</xsl:stylesheet>
