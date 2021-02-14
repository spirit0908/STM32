<?xml version="1.0"?>
<!DOCTYPE html>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="span">

<html>
    <head>
        <meta charset='UTF-8'/>
        <title>Test report</title>
    </head>
    <body>
        <h1 align='center'>Software Test Report</h1>

        <h2>Test Execution details</h2>
        <ul>
          <li>Date: <xsl:value-of select="execinfo/date"/></li>
          <li>Time: <xsl:value-of select="execinfo/time"/></li>
        </ul>

        <h2>Summary</h2>
        <table border='1'>
            <thead>
                <tr>
                    <th>Module name</th>
                    <th>Passed</th>
                    <th>Not run</th>
                    <th>Failed</th>
                    <th>Total</th>
                </tr>
            </thead>
            <tbody>
              <xsl:for-each select="testModule">
                <tr>
                    <td><xsl:value-of select="moduleName"/></td>
                    <td align='center'><xsl:value-of select="nbPass"/></td>
                    <td align='center'><xsl:value-of select="nbNotrun"/></td>
                    <td align='center'><xsl:value-of select="nbFail"/></td>
                    <td align='center'><xsl:value-of select="nbTotal"/></td>
                </tr>
              </xsl:for-each>
            </tbody>
        </table>
  
        <h2>Test execution</h2>
        <table border='1'>
            <thead>
                <tr>
                    <th>Module name</th>
                    <th>Test name</th>
                    <th>Test status</th>
                </tr>
            </thead>
            <tbody>
              <xsl:for-each select="testModule/testResult">
                <tr>
                    <td><xsl:value-of select="../moduleName"/></td>
                    <td><xsl:value-of select="testname"/></td>

                    <xsl:if test="teststatus = 'passed'">
                    <td align='center' bgcolor="green"><xsl:value-of select="teststatus"/></td>
                    </xsl:if> 
                    <xsl:if test="teststatus = 'failed'">
                    <td align='center' bgcolor="red"><xsl:value-of select="teststatus"/></td>
                    </xsl:if> 
                    <xsl:if test="teststatus = 'notrun'">
                    <td align='center' bgcolor="yellow"><xsl:value-of select="teststatus"/></td>
                    </xsl:if> 
                </tr>
              </xsl:for-each>
            </tbody>
        </table>
    </body>
</html>


</xsl:template>
</xsl:stylesheet>

