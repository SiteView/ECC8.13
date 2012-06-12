@echo off

set Classpath=.;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar
set Path=.;%JAVA_HOME%\bin

set SV65_LIB_EXT=%cd%\lib\ext
set SV65_LIB_missed_IBMWebAS35=%cd%\lib\missed\IBMWebAS35
set SV65_LIB_missed_WebSphere5=%cd%\lib\missed\WebSphere5

set Classpath=.;.\monitor.jar;%cd%\lib\deprecated\epm.jar;%SV65_LIB_EXT%\ant.jar;%SV65_LIB_EXT%\commons-httpclient-2.0-final.jar;%SV65_LIB_EXT%\commons-logging.jar;%SV65_LIB_EXT%\datachannel.jar;%SV65_LIB_EXT%\j2ee.jar;%SV65_LIB_EXT%\JDHCP.jar;%SV65_LIB_EXT%\jgl.jar;%SV65_LIB_EXT%\jimi.jar;%SV65_LIB_EXT%\jmf.jar;%SV65_LIB_EXT%\lucene-1.2.jar;%SV65_LIB_EXT%\manager.jar;%SV65_LIB_EXT%\MIBCompiler.jar;%SV65_LIB_EXT%\mindterm.jar;%SV65_LIB_EXT%\oroinc.jar;%SV65_LIB_EXT%\rjmf.jar;%SV65_LIB_EXT%\smtp.jar;%SV65_LIB_EXT%\Snmp.jar;%SV65_LIB_EXT%\wsdl4j.jar;%SV65_LIB_EXT%\xercesImpl.jar;%SV65_LIB_missed_IBMWebAS35%\ejs.jar;%SV65_LIB_missed_IBMWebAS35%\repository.jar;%SV65_LIB_missed_IBMWebAS35%\ujc.jar;%SV65_LIB_missed_WebSphere5%\ibmorb.jar;%SV65_LIB_missed_WebSphere5%\pmi.jar;%SV65_LIB_missed_WebSphere5%\pmiclient.jar;%SV65_LIB_missed_WebSphere5%\wssec.jar;%SV65_LIB_EXT%\crimson.jar

echo Using JAVA_HOME:       %JAVA_HOME%
echo Using Classpath:       %Classpath%
echo Using Path:            %Path%
@echo off


java TestHttp

PAUSE