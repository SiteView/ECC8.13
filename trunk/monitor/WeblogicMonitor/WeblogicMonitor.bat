@if NOT "%1"=="" set strUsername=%1
@if     "%1"=="" set strUsername=weblogic
@if NOT "%2"=="" set strPwd=%2
@if     "%2"=="" set strPwd=weblogic
@if NOT "%3"=="" set strServerIp=%3
@if     "%3"=="" set strServerIp=t3://localhost:7001
@if NOT "%4"=="" set strTaskType=%4
@if     "%4"=="" set strTaskType=ConnectionPoolInfo
@if NOT "%5"=="" set strTaskParam=%5
@if     "%5"=="" set strTaskParam=null
cd C:\SiteView\SiteView ECC\fcgi-bin\
set classpath=C:\SiteView\SiteView ECC\fcgi-bin\weblogic.jar;C:\j2sdk1.4.2_05\lib\dt.jar;C:\j2sdk1.4.2_05\lib\htmlconverter.jar;C:\j2sdk1.4.2_05\lib\tools.jar;C:\j2sdk1.4.2_05\lib;C:\j2sdk1.4.2_05\jre\lib\charsets.jar;C:\j2sdk1.4.2_05\jre\lib\jce.jar;C:\j2sdk1.4.2_05\jre\lib\jsse.jar;C:\j2sdk1.4.2_05\jre\lib\plugin.jar;C:\j2sdk1.4.2_05\jre\lib\jsse.jar;C:\j2sdk1.4.2_05\jre\lib\rt.jar;C:\j2sdk1.4.2_05\jre\lib\sunrsasign.jar;C:\j2sdk1.4.2_05\jre\lib\ext\dnsns.jar;C:\j2sdk1.4.2_05\jre\lib\ext\ldapsec.jar;C:\j2sdk1.4.2_05\jre\lib\ext\localedata.jar;C:\j2sdk1.4.2_05\jre\lib\ext\sunjce_provider.jar;
java getActiveDomainAndServers -U %strUsername% -P %strPwd% -I %strServerIp% -T %strTaskType%  -C %strTaskParam%