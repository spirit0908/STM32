<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method='text'/>

<xsl:template match="STM32F103C8T6">
# Pinout

<xsl:text>
Pin |  Name  | Port/Pin | AName | Dig IN | dig OUT | Analog | USB |CAN | Serial | SPI | I2C| PWM
----|--------|----------|-------|--------|---------|--------|-----|-----|--------|-----|----|-----
</xsl:text>
  <xsl:for-each select="pin">
    <xsl:text> </xsl:text>
    <xsl:value-of select='format-number(./@id, "00")'/>
    <xsl:text> | </xsl:text>
    <xsl:value-of select="name"/>
    <xsl:text> | </xsl:text>
    <xsl:value-of select="portPin"/>
    <xsl:text> | </xsl:text>
    <xsl:value-of select="aName"/>
    <xsl:text> | </xsl:text>
    <xsl:value-of select="digIn"/>
    <xsl:text> | </xsl:text>
    <xsl:value-of select="digOut"/>
    <xsl:text> | </xsl:text>
    <xsl:value-of select="analog"/>
    <xsl:text> | </xsl:text>
    <xsl:value-of select="usb"/>
    <xsl:text> | </xsl:text>
    <xsl:value-of select="can"/>
    <xsl:text> | </xsl:text>
    <xsl:value-of select="serial"/>
    <xsl:text> | </xsl:text>
    <xsl:value-of select="spi"/>
    <xsl:text> | </xsl:text>
    <xsl:value-of select="i2c"/>
    <xsl:text> | </xsl:text>
    <xsl:value-of select="pwm"/>
    <xsl:text> |
</xsl:text>
  </xsl:for-each>
</xsl:template>


</xsl:stylesheet> 
