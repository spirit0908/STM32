<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="text"/>

<xsl:template match="span">

//General configuration:
#define mcUid    <xsl:value-of select="generatorConfig/mcUid"/>
#define mcAddr   <xsl:value-of select="generatorConfig/mcAddress"/>


/* Generate Light configuration: */
T_LightConfig LightConfig[MAX_LIGHT_NUM]=
{
  /* Port | Pin | type */
  <xsl:for-each select="Lights/light">{ <xsl:value-of select="port"/>, <xsl:value-of select="pin"/>, {0} },
  </xsl:for-each>
};

T_LightState LightState[MAX_LIGHT_NUM]=
{
  /* state | order */
  <xsl:for-each select="Lights/light">{0, 0},
  </xsl:for-each>
};


/* Generate PushButton configuration: */
PB_Config_T PushButtonConfig[PB_CONFIG_NB] =
{
  <xsl:for-each select="Switch/pushButton">{/* "<xsl:value-of select="name"/>"*/ <xsl:value-of select="port"/>, <xsl:value-of select="pin"/>, &amp;<xsl:value-of select="pushConfig/shortPush/action"/>, &amp;<xsl:value-of select="pushConfig/longPush/action"/>, &amp;<xsl:value-of select="pushConfig/configPush/action"/>, PB_IDLE, 0},
  </xsl:for-each>
};


/* Generate PushButton configuration: */
PB_Config_T hHeating[MAX_HEATING_CONFIG_NB] =
{
  <xsl:for-each select="Heating/heater">{/* "<xsl:value-of select="name"/>"*/ <xsl:value-of select="port"/>, <xsl:value-of select="pin"/>, <xsl:value-of select="type"/>, <xsl:value-of select="temp_default"/>, <xsl:value-of select="temp_confort"/>, <xsl:value-of select="mode_gestion"/>, <xsl:value-of select="zone"/>},
  </xsl:for-each>
};



</xsl:template>

</xsl:stylesheet> 
