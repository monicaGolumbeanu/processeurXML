<!DOCTYPE xsl:stylesheet SYSTEM "rap1_xsl.dtd">
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">	
	<html>
	<body>
		<marquee><h2>Title:: Rrrrrr</h2></marquee>
		<p>		
		<xsl:apply-templates />	
		</p>
	</body>
	</html>
</xsl:template>

<xsl:template match="titre">
	<p>
	Title: <span style="color:#ff0000">
		<xsl:apply-templates />  
	</span>	
	</p>
</xsl:template>
	

<xsl:template match="auteur">
	<p>
		Auteur: <span style="color:#0000ff">
			<blink><xsl:apply-templates /></blink>  
		</span>	
	</p>
</xsl:template>
<xsl:template match="resume">
	<p>
		Resumé: <span style="color:#0000ff">
			<i><xsl:apply-templates /></i>  
		</span>	
	</p>
</xsl:template>
</xsl:stylesheet>