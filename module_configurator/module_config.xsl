<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="text"/>
<xsl:template match="span">

/* General configuration: */
#define mcUid    <xsl:value-of select="generatorConfig/mcUid"/>
#define mcAddr   <xsl:value-of select="generatorConfig/mcAddress"/>

#define MAX_LIGHT_NUM <xsl:value-of select="count(lights/light)"/>
#define MAX_PB_CONFIG_NB <xsl:value-of select="count(switch/pushButton)"/>
#define MAX_HEATING_CONFIG_NB <xsl:value-of select="count(heating/heater)"/>


/* Generate Light configuration: */
T_LightConfig LightConfig[MAX_LIGHT_NUM]=
{
  /* Port | Pin | type */
  <xsl:for-each select="lights/light">{<xsl:value-of select="port"/>, <xsl:value-of select="pin"/>, {0} }, /* <xsl:value-of select="name"/> */
  </xsl:for-each>
};

T_LightState LightState[MAX_LIGHT_NUM]=
{
  /* state | order */
  <xsl:for-each select="lights/light">{0, 0}, /* <xsl:value-of select="name"/> */
  </xsl:for-each>
};


/* Generate PushButton configuration: */
PB_Config_T PushButtonConfig[MAX_PB_CONFIG_NB] =
{
  <xsl:for-each select="switch/pushButton">{<xsl:value-of select="port"/>, <xsl:value-of select="pin"/>, &amp;<xsl:value-of select="pushConfig/shortPush/action"/>, &amp;<xsl:value-of select="pushConfig/longPush/action"/>, &amp;<xsl:value-of select="pushConfig/configPush/action"/>, PB_IDLE, 0}, /* "<xsl:value-of select="name"/>"*/
  </xsl:for-each>
};


/* Generate PushButton configuration: */
PB_Config_T hHeating[MAX_HEATING_CONFIG_NB] =
{
  <xsl:for-each select="heating/heater">{<xsl:value-of select="port"/>, <xsl:value-of select="pin"/>, <xsl:value-of select="type"/>, <xsl:value-of select="temp_default"/>, <xsl:value-of select="temp_confort"/>, <xsl:value-of select="mode_gestion"/>, <xsl:value-of select="zone"/>}, /* "<xsl:value-of select="name"/>"*/
  </xsl:for-each>
};

</xsl:template>
</xsl:stylesheet> 
