#ifndef Fluohtml_h
#define Fluohtml_h

//HTML/CSS

const char HTTP_HEAD[] PROGMEM            = 
"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html lang='en'>\
<head>{h}<meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=no'/><title>{v}</title>";

const char HTTP_STYLE[] PROGMEM           = 
"<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;}\
input{width:95%;} body{text-align: center;font-family:verdana;}\
button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}\
.q{float: right;width: 64px;text-align: right;}"; 

const char HTTP_ENCR[] PROGMEM            = ".l{background: url(\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==\") no-repeat left center;background-size: 1.1em; display: inline-block; width: 50px; height: 20px;}";
const char HTTP_1BAR[] PROGMEM            = ".bd{background: url(\"data:image/png;base64, iVBORw0KGgoAAAANSUhEUgAAACgAAAAoCAYAAACM/rhtAAADyElEQVRYhe3XW4jUVRwH8M/MTtvusisGbpe1m1SLFltsdi+ooHqpELKNIordih7SljKphwgpuz200UshRTYklWahZhEVSNL9oawVk1JJVxdxq7VRQhRnpofzH3b885/dmTWDYL5wmDm/yznfOb/LOUMdddRRxzFFCjZu3Fir33RcjW6cE81PQFOkP4A/MYxf8QPWY6SWTbq6umRqsD8N96IH51Zhf3aCbANW4A1Vkk1XYXMhPsMQFlVJrhK68Tz2YDVmHg3BUyJi3+O6CdbJYQt+wiC2Yv8EPnOwGe9haiWjSiFegIFxFv8RH+GraJNdOByzaRTS4jxchZswK2GtudHoQzaujBdJg3Bq1yYs9DdejsbQOOTHQyf6cT+OS9C/j1tLk66uriNCPB07K5B7ElPw2FGQI1T0fLThpQT9XPwc7YWxEN+G54S8K8cXQq7srbDhTFwefXagNZLvE1rMZnyNbTG/g3gYL+JDnF+mm4V1eAHLSwRX4ni8WWb4OJ5NIHUqHsQdQo5Vg614S0iP38vkO3GBkO8LyuTPYC1jVVzEMqHHwZ0J5NqFHrYTj9ZAjtATFwm97zVjJ13CI3go+n4DVomKLl4kKUzDHxHpEh4Qfv2/haJwCO+UyRqivfeUBEk3SdGRISA01DkVNvpSCMUGoXj2Cz9yCs7A7Mj34phfCm/jetwTyfLl5MoNx7uLPxfu3DhewdPYXckxhjPxFO5K0K3CLUlO8TaThGWx+Xc4GfNqIAfbcbeQi5tjuhXjOU70WHhdOPa1Qg7Or2A3TajGE4U02S1ce3/F7LYJd/m7QkFeI7xyJk2Q0Kc6heqNozciPTtBV8Q3QkNeGdPdhyfwy0SbV/vc2hKbX4o1OGkcnxSuiMY23GwsvPuiMSGqeW7FsQjfTkAujrOEK2xerZvV8mAtIak4tqRSqQ/S6fRvSOXz+U6hvZwesxv9Lwi+KlTlJ8Vi8UChUJjb3t7+cWtrq1wuJ51Oa2trk8vl+kdHR29vaGgoNeMrhXv5mBOETwuFwo2ZTGbXjBkzBgcHB2WzWZs2bZJKpXR3d+vr69PZ2bl8x44d2/P5/NR0Ol0zOSb5p6lQKGhubtbR0WHp0qX6+/tLqiaheg9CNpvV09NjaGjIoUOHpNO1pXw1jToRjY2NMpmMhQsXlshdJDTxvUKercPM3t5eixcv1tLSIpOZXLAmRbC5udnw8LAlS5aURNNxiXCCLcKjtwMGBgaMjIxoampKXOuYEEzAGuFWKOEy4RSPGpMtkiSsFx6xh4Vw11FHHXX8H/APbB/x7p3vHwMAAAAASUVORK5CYII=\") no-repeat left center;background-size: 1.8em; display: inline-block; width: 50px; height: 20px;}";
const char HTTP_2BAR[] PROGMEM            = ".bc{background: url(\"data:image/png;base64, iVBORw0KGgoAAAANSUhEUgAAACgAAAAoCAYAAACM/rhtAAAEO0lEQVRYhe3XXWjVZRwH8M/ZTk2Hkwm+bGoZLEWLU5i9rqSS5U2KkBlGFGXQRS0pg7oIEbM3pKIbu6iLMql0lmb2QgWSVMtdlKWglI4j09g8S8uG5sb+ni6ec9hx/Hd25tZFsC/8Oef/e37P8/s+z/N7+zOKUYxiFP8pErB///6hzpuGWzEXM3PvEzAmN/4PTuB3/IafsBuZoRhJpVKSQ9C/BA9jGa4oQf/yGNlebMHbSiRbVoLONfgabVhTIrmBMBcv4zg+xuzhEKzNEfsRDYOscwqH8Av24TC6BpmzBAfxIaoHUhroilfh1SKL/4zP8H3OyDH09tO5WHCLK3ELFmFOzFpLc89DeKf/YP8gKRdO7faYhU5jQ+5pK0K+GGZhJR7BRTHjH+Hu/EsqlTrviqfh6ADk1mI8nhkGOUJEN6IKr8eML8WBnC30XfE9eEnwu0J8K/jKnwMYnI2bcr9TMS4n/1tIMQfRjNZ+87rxJF7Dp7iqYGwOduEVbM4T3IoKvFug+CxejCE1HY/jXsHHSsFhvCe4R2eB/CiuFvx9VYH8BeykL4qz2CTkOLgvhtwkIYcdxdNDIEfIiWuE3PeWvpPO4yk8kfu/ENvlgq5/kCQwEX/kSOfxqLD7kUJWOIQPCmTlOdvH84K4SpJ1/hUQEuqSWCvZ7HeJRGJnRUXF3oqKirZkMtmFRG9v7/izZ8/O6OnpmZfNZpckEonr+k1N4H3cgRU5WVRIrlCxWC3+Rqi55yGKojfGjh37/JQpU9qjKJLJZHR2djp9+rREImHcuHEmTZpk8uTJstmsTCZzWXd393NlZWX3x9jYjrvijJdSizcVEjx37lxLMplcMmPGjOMnTpzQ1NRk165dWlpapNPpvl0nEurq6tTX11uwYIGGhoYjNTU1Dxw7dmxtFEU7y8rKChP2lmIESulmFmFnFEUbJkyY0FhdXa2pqcnq1at1dHTkdSYK0ThZcJN2oez9BXV1ddatW2fx4sUymYyurq6m8vLyZbhN6HJikUqlSmu3oiiaOX369KM9PT1nGxsbbdu2LT/0oJB458VMy+IHISFvhRUrVli/fr3e3t7x7e3ttclk8tdidksiGEWRmpoamUzG8uXLHThwAG7ADkwpurM+tGIxDtbX19u4caPKykqdnZ3Ky8uLEhy03aqurtba2mr+/Pl5cmuwZwjkoE4oYY81NzdbuHChjo4OVVVVg04ctGGtrKyUTqedOnUqL2qPUTuET5AW/HqWkJou7ad3EtLptLa2NrW1tc6cOTM8gjF4E0fwpdDaL8UXMXorsVxfMr5ZqMtDwoUQhK9wp9AH7iuit1nYTLULIMeFE4TPY2RjhOjtLpDtGYaNkr5JSsG1aBHaspNCuzTo90YpGCmC03C9cIKVQtM7dSQWHimCO4SqkMeNwikOG8Pxwf7YLTSxvcJ1j2IUoxjF/wH/ArzEPkPr6URoAAAAAElFTkSuQmCC\") no-repeat left center;background-size: 1.8em; display: inline-block; width: 50px; height: 20px;}";
const char HTTP_3BAR[] PROGMEM            = ".bb{background: url(\"data:image/png;base64, iVBORw0KGgoAAAANSUhEUgAAACgAAAAoCAYAAACM/rhtAAAEaUlEQVRYhe2XXUybVRjHf6ev2lIgQahKVwoGlMyZVzI1OrWAJmoiwyxx0/gVopF4oTLNbrxQs8iFcuESLyAhGsVoZJtf2bqpqImxqR8zZlppAkUgmgFpAGuxllAIfV8vTt9Y3rxdW2AXJv0nJ+05z/Oc8+/zcc5TKKGEEkq4oBAA4XC4WDsP0A7sBq7OzC8FHBn5ChAD5oDfgJ+BALBQzCGqqnJREfpe4AngfmBXAfpXWaz9AhwHhiiQrK0AneuBr4BzwOECyeXCbqAPmAdOADu3QtCdIXYWuDPPPn8Dk8CvwCgwBfyTx2YfMA58BFTlUsoV4kPAkVxGuq6HbDbbp3a7/Tun0zlut9tnFUVZz5Kjadolq6ur3uXl5WvX1tZ8mqZ1CiGusdhuf2Y8DrxjFpqLREF67Q4LUsu6rg9UVlYO1NTUnFtfXycajTI7O0s0GmVpaYmVlRWEEJSVlVFdXY3b7aauro7a2lqEEMRiseZkMnlQCPGkEOJiC7IfAweMiaqqGwh6gJ+Qoc0mhqZpL7tcrt6qqiptamqKYDBIIBAgEAiwuLiYy9EAeDwe2traaG9vp7W1lYaGBmKxmD0ej/cpivKchck4sAdIZBN8AHgVaMzWTKfTwfLy8n0ejyc+NjbG0NAQg4ODpNNpQ2UncEvmcwdQkVlPIK+YceB7YBrA4XDQ09NDV1cXjY2NzMzMeFOp1GlFUa4zkTwLvKaq6jGDoAAeBd7NIveC2+1+RQhBf38/vb29hqgO6AEeQl49hWAKeB8YABZtNht9fX10d3eTSqVYWFg4oijKoSz9+4BTqqrKvA6Hw8Y4MDo6qodCoYcTiQShUAhVVQ2jy5B3mL7F8abhaZ/Px8TEBPF4nFAo9Gw4HNbD4fBdBh8wFYmu6wJwNTU1/RkIBPTOzk40TQN4KvPrtws68AhwtKKigpGREVpaWpTp6WmXzWabF0IAskg23IOapuler3fR7/frHR0dBrkT5yH3LfA8cDcyDz3IFNgF3AO8iCw8MwQwDLydTCbx+XwEg8F0fX39fObMjTBcGo1GGR4ezhZ9g3WYBjBVex5cicxvq70+MZT8fj9zc3Nkh3iDBx0OB5FIJHvpPdNBPwK1wNNAtAiCfwBdyPd53CQ7bnyJRCI4nc4NwnzNwlvId/MU0mvP5NBzAS3A5UivRJHP3pJJbxoZ/g+QTcftyC4nJwrpZk4DzcCMheyxDOkbLGQ68APwOvChSdYNvARM5Du80HZr0jS/GTgJXHEeGwHcmhnTwL38F95EZuRFIe2WGYeBM3nImdEEjCFztygU07AasCqOScAP/I70XDOynao36f1V7GGbIfgGsiq/QLb2+4HPLfQOAg8CRzPz25Dv8gUnCPAlsBeYRTaouXAM+WOq2AQ52DxBgM8s1hzI6l3NWjuzhTM2VSRWuBF5iceRefY1BfzfKATbRdAD3IT0oBPZke/Yjo23i+BJ5KtgYA/Si1vGVnLQjACyiV1HhruEEkoo4f+AfwG3H5TDR4rBdAAAAABJRU5ErkJggg==\") no-repeat left center;background-size: 1.8em; display: inline-block; width: 50px; height: 20px;}";
const char HTTP_4BAR[] PROGMEM            = ".ba{background: url(\"data:image/png;base64, iVBORw0KGgoAAAANSUhEUgAAACgAAAAoCAYAAACM/rhtAAACVUlEQVRYhe3XS4iOURzH8Y9LWGiiDLlPJoONcmuwmSJCIuUylBI7FspG2ZiFEpENKwtlhSRhp0QuUQwWKENqyiXl0riVBRbnmeb1vM95L/PMuNT7rX9v73nO/39+5/L8z/+hRo0aNfqVAb30G48WzMLU5P9IDEuef8M7vMRTtOMa3uYRW46JaMMj/OyltWM3RvelsNm4nENUzM5jeh5hY6sQ9lHYygd4iA50Veh7FiOqFberTND72IflaMDgjBhD0IhVOIjHZWJuqUTYIFyJBPiMA5hUzUxTNOEovkfGOFvKeTxeRRzbMDCHsDRDcSQy1mPUdXfsTjPrsR9TUoGuYzU+RAaajgXJ7zgMT9q7hBTzBLfwPOI/EZcwM9V+D4dwqlDo5tRM9kSCThC2ulPpM1VoHcIu1EdiHk71XyP7XFubdNiU8awep6sQFbPjela6kJ3J8yWRSSCsZL3iG2Z7HwgrtB/YmBpjEMZkCSrHeeEcZnEDF4W004lPScw6TMacxHdexP8EtlagIcpV2StwTEjkldKAk5FY5/II3JYKdlvGNlRBo+KEvSGPQFiZBDpaos8oLBbOVatQ6ZS6vs4kMVvyiutmqp5SqpAtuCv+ItzEugy/OkzrK3FZNONNRFiWPcOM/hRUyN4qhKVtR7WDZWbrMrzOaOvABbwQ0kyTkF7ShcX7XozXK5YKK/JVKLlitOpZvYV/QNdvrFB8yWcxH8v6WUvFDBNKqX+OubgjfM19EYreXN8bfc1qxW/sor+qKIMWPeKa/7KWKK1CTVmjRo0a/wu/AOBqGPObxxinAAAAAElFTkSuQmCC\") no-repeat left center;background-size: 1.8em; display: inline-block; width: 50px; height: 20px;}";

const char HTTP_SCRIPT[] PROGMEM          = 
"<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();}</script>";

// qui nel mezzo trovi il favicon
const char HTTP_HEAD_END[] PROGMEM        = 
"</style><link rel='shortcut icon' href='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAADeUlEQVQ4jWXST0xbBQAG8O+91z5aoLRIhbL+XV+BTR6gbrrgkiXESFw0WeIIjg6Yihp1OiEmOsJ20KgnTw4y9GDYEplFnccZ8TAvi9GEllrKv5WiAwZ2LSzA2r7y+DzoPOjv/iXfl3xCciEJq82Gn2/cQDQahdVmReJm4qH41FTr/NxcLQD4FWW26eGmH2pr66Z1XUf23j3YKyuxs7MDgyAIIAmrzQZBFPD9tWsfRyOTb2SzWWtxcTEAIBqJYG52duPAwYNDT7W2nrOUlUHTNJCEMD83D7+i4Kfr18u6gsFf1jOZugq7HbIs4z5BEJDP55G+cwdOt3umf2DgMYfDsbW6ugohEomAJHpOvbA4Mz3tdbpcIIlCoQBRFCFJEgBA13UIgoDV27dRr6oLoW+/UQRRhGg2m/H58GcfTUQnvW6PBwCQy+Vw9+4Gtre3IYoiACCdTiOVSsHpduHX8IR/8NMLH0iiCIx+ORrw7HHSUWHnXreHPqeLZrmIk5EI+999jwZJIgCOfRXij+PjFAE6qxz0OV365ZFL+9EVPHnWCIGlRSaWFJkIgO/09pIkM+kMAfDxRw/wvjolQAA0G2V2tD9/HuWWsi/anjvOpT9uMZFIsPnQIabTaYYnJkiSpzq7ePq11xmLxahpGlOpFIcuDPLJlhZWVdhHpIry8mOyLD+S/H0RHR0daG5uhq7vouXIEQRqanAiGITa2IBz/f24PHIJjU2N2NraQiQcxtra2iS6T3aeLf2net+Zt0mSY6EQAfDYM8/+PSWTYYnJTJPBSAA0QqDFZGb78bbzGAuFAj6Xm/YyG6vtlYz9FuOJ9nZaiktYZDDyu6tX+cpLPTRKBtbs9VPx+uiwP0jF49OvjF7Zj/hUHK/2vPwhAPqcblpLSln1QAX3KQEqXh8FgNaSUu4L1FDx+ljrVwiAb51+8/3EzQSEcDgMSZTwYnd3Mj4V91Xvqf73ff8liiKWl5ZQr6oLg8MXFV3fhWiz2qCqDRgavthYWVU5s7KygkKh8L+wpmlYXl6G0+2Kn+nrbdTyBSzdWoLU19sHTdOQy+c1t8czJEqi/OfaWkM+nzcZjUYAQDabhSzLG08cPvxJsLOzzWwyF3K5HHZ3dRhIQhRFbKyvQwDw9NGjA2635+upWKx1MZkMkES9qs6rqjru8/sjJLC5uYlSiwUk8Rd/HLDR1pg0+QAAAABJRU5ErkJggg==' type='image/x-png'/></head><body><div style='text-align:left;display:inline-block;min-width:260px;'>";

const char HTTP_PORTAL_OPTIONS[] PROGMEM  = 
"<form action='/wifi' method='post'><button>Configure Wi-Fi</button></form><br/><form action='/i' method='post'>\
<button>Info</button></form><br/><form action='/r' method='post'><button>Reset</button></form>";

const char HTTP_ITEM[] PROGMEM            = 
"<div><a style='color:#0000EE; display:inline-block; width:220px;white-space: nowrap;overflow:hidden !important;\
text-overflow: ellipsis;' href='#p' onclick='c(this)'>{v}</a>&nbsp;<span class='q {b}'></span><span class='q {i}'>\
</span></div>";

const char HTTP_FORM_START[] PROGMEM      = 
"<form method='get' action='wifisave'><input maxlength='32' id='s' name='s' placeholder='SSID'><br/>\
<input maxlength='64' id='p' name='p' type='password' placeholder='Password'><br/><br/><input maxlength='16'\
id='g' name='g' placeholder='Name your FLUO Board'><br/>";

const char HTTP_FORM_PARAM[] PROGMEM      = 
"<br/><input maxlength='32' id='{i}' name='{n}' maxlength='{l}' placeholder='{p}' value='{v}' {c}>";

const char HTTP_FORM_END[] PROGMEM        = 
"<br/><button type='submit'>save</button></form>";

const char HTTP_SCAN_LINK[] PROGMEM       = 
"<br/><div class='c'><a href='/wifi'>Scan</a></div>";

const char HTTP_SAVED_WAIT[] PROGMEM      = 
"<div>Trying to connect, please wait... <br/><br/><br/><progress value={bar} max='7'></progress></div>";

const char HTTP_SAVED_FAILED[] PROGMEM    = 
"<div>Oops! Connection failed.<br/><br/><a>{x}</a> <br/><br/>Click <a href='/wifi'>here</a></div> \
to return to the configuration page.";

const char HTTP_SAVED_SUCCESS[] PROGMEM   = 
"<div>Your FLUO WI-FI is connected to <a>{a}</a><br/><br/>The Internet connection is <a>{b}</a><br/>\
<br/>Press the IoT button to activate the Internet of Things mode</div></form><br/>\
<form action='/iot' method='post'> <button style='height:40px;width:200px'>IoT</button></form>\
</br><span style='font-size: 12px;'>If you want to connect your FLUO WI-FI to a different network,\
you can restore it to Access Point Configuration mode if you press the AP-RST button for 5 seconds</span>";

const char HTTP_SAVED_IOT[] PROGMEM       = 
"<div>FLUO WI-FI is connected to <a>{a}</a><br/><br/>The Internet connection is <a>{b}</a><br/><br/>\
<strong>Before you continue, please restart your FLUO WI-FI by pressing the RESET button for 5 seconds or disconnect it \
from the power supply and connect it back again.</strong>\
<br/><br/>You can access your FLUO WI-FI from your network with <a href='http://{c}.local/'>http://{c}.local/</a> or \
<a href='http://{d}/'>http://{d}/</a> (for special network configurations)</div>";

const char HTTP_END[] PROGMEM             = 
"</div></body></html>";

const char HTTP_NOTFOUND[] PROGMEM        = 
"HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><title>Error 404 \
(Not Found)!!1</title><p><b>404.</b><br/><ins>Page not found.</ins>\r\n\r\n";

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const char HTTP_IOT_HEADER[] PROGMEM      = 
"<html lang='en'><head><meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1 shrink-to-fit=no'/>\
<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootswatch/4.0.0-beta.3/minty/bootstrap.min.css'>\
<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/sweetalert/1.1.3/sweetalert.css'>\
<script src='https://code.jquery.com/jquery-3.2.1.slim.min.js'></script>\
<script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js'> </script>\
<script src='https://cdnjs.cloudflare.com/ajax/libs/sweetalert/1.1.3/sweetalert.min.js'></script>\
<script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js'> </script>\
";

const char HTTP_IOT_SCRIPT[] PROGMEM      = 
"<script>\
function setMODE(x , y, z)\
{\
    var o = '#D' + String(x) + 'O';\
    var i = '#D' + String(x) + 'I';\
    var s = '#D' + String(x) + 'S';\
    var p = '#D' + String(x) + 'P';\
\
    if (y == 0){ $(o).show();$(i).hide();$(s).hide();$(p).hide();}\
    if (y == 1){ $(o).hide();$(i).show();$(s).hide();$(p).hide();}\
    if (y == 2){ $(o).hide();$(i).hide();$(s).show();$(p).hide();}\
    if (y == 3){ $(o).hide();$(i).hide();$(s).hide();$(p).show();}\
}\
\
function myFunc()\
{\
swal({\
          title: 'Function N/A',\
          text: 'This function is not available for this PIN',\
          type: 'warning',\
          confirmButtonClass: 'btn-info',\
          confirmButtonText:  'Continue',\
          closeOnConfirm: false\
        });\
}\
\
function Scheck(x)\
{\
    if (isNaN(x) || x < 0 || x > 180){\
        swal({\
          title: 'Value not valid for Servo',\
          text: 'Enter number between 0 and 180',\
          type: 'warning',\
          confirmButtonClass: 'btn-info',\
          confirmButtonText:  'Continue',\
          closeOnConfirm: false\
        });\
        return false;\
 } }\
\
function Pcheck(x)\
{\
    if (isNaN(x) || x < 0 || x > 255){\
        swal({\
          title: 'Value not valid for PWM',\
          text: 'Enter number between 0 and 255',\
          type: 'warning',\
          confirmButtonClass: 'btn-info',\
          confirmButtonText:  'Continue',\
          closeOnConfirm: false\
        });\
        return false;\
 } }\
\
function checkServo(el){ \
\
        var res = el.name.substring(1, 3);\
        var o = 'D' + res + 'SL';\
\
        var x = document.getElementById(o).value;\
        return Scheck(x);\
}\
function checkPWM(el){ \
\
        var res = el.name.substring(1, 3);\
        var o = 'D' + res + 'PL';\
\
        var x = document.getElementById(o).value;\
        return Pcheck(x);\
}\
\
$(document).ready(function(){\
{D13set}{D12set}{D11set}{D10set}{D9set}{D8set}{D7set}{D6set}{D5set}{D4set}{D3set}{D2set}{D1set}{D0set}\
});\
\
function Fsub()\
{\
    for (i = 0; i < 14; i++) {\
        var x = String(i);\
        var Otext = 'D' + x + 'output';\
        var Itext = 'D' + x + 'input';\
        var Stext = 'D' + x + 'servo';\
        var Ptext = 'D' + x + 'pwm';\
        var TOntext = 'D' + x + 'on';\
        var TOfftext = 'D' + x + 'off';\
        var s = 'D' + x + 'Form';\
        var t = 'D' + x + 'OnOffForm';\
\
        if (document.getElementById(Otext).checked ){ document.getElementById(s).submit(); }\
        if (document.getElementById(Itext).checked ){ document.getElementById(s).submit(); }\
        if (document.getElementById(Stext).checked ){ document.getElementById(s).submit(); }\
\
        if (x == 3 || x == 5 || x == 6 || x == 9 || x == 10 || x == 11){\
        if (document.getElementById(Ptext).checked ){ document.getElementById(s).submit(); } }\
\
        if (document.getElementById(TOntext).checked ){ document.getElementById(t).submit(); }\
        if (document.getElementById(TOfftext).checked ){ document.getElementById(t).submit(); }\
    }\
}\
\
$(document).change(function(){\
    Fsub();\
});\
</script>\
";

const char HTTP_IOT_STYLE[] PROGMEM      =
"<style>\
.ico-in {\
    background-image: url(data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz48c3ZnIGVuYWJsZS1iYWNrZ3JvdW5kPSJuZXcgMCAwIDUxMiA1MTIiIHZlcnNpb249IjEuMSIgdmlld0JveD0iMCAwIDUxMiA1MTIiIHhtbDpzcGFjZT0icHJlc2VydmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHN0eWxlIHR5cGU9InRleHQvY3NzIj4uc3Qwe2ZpbGw6I0ZGRkZGRjt9PC9zdHlsZT48cGF0aCBkPSJtNDY0LjQgMjY2LjFoLTMwMS44Yy01LjUgMC0xMC00LjUtMTAtMTBzNC41LTEwIDEwLTEwaDMwMS44YzUuNSAwIDEwIDQuNSAxMCAxMHMtNC41IDEwLTEwIDEweiIvPjxwYXRoIGNsYXNzPSJzdDAiIGQ9Im0xMDEuMyAzMTcuM2MtMzMuOCAwLTYxLjMtMjcuNS02MS4zLTYxLjNzMjcuNS02MS4zIDYxLjMtNjEuMyA2MS4zIDI3LjQgNjEuMyA2MS4zYzAgMzMuOC0yNy40IDYxLjMtNjEuMyA2MS4zIi8+PHBhdGggZD0ibTM3LjYgMjU2YzAtMzUuMSAyOC42LTYzLjcgNjMuNy02My43czYzLjggMjguNiA2My44IDYzLjctMjguNiA2My43LTYzLjggNjMuN2MtMzUuMSAwLTYzLjctMjguNi02My43LTYzLjd6bTEyMi4yIDBjMC0zMi4yLTI2LjItNTguNC01OC40LTU4LjRzLTU4LjQgMjYuMi01OC40IDU4LjQgMjYuMiA1OC40IDU4LjQgNTguNGMzMi4xIDAgNTguNC0yNi4yIDU4LjQtNTguNHoiLz48cGF0aCBkPSJtMTAxLjQgMjgyLjFjLTE0LjQgMC0yNi4xLTExLjctMjYuMS0yNi4xczExLjctMjYuMSAyNi4xLTI2LjEgMjYuMSAxMS43IDI2LjEgMjYuMWMtMC4xIDE0LjQtMTEuNyAyNi4xLTI2LjEgMjYuMSIvPjxwYXRoIGQ9Im01NiAyNDIuOWMwLTAuMiAwLTAuNSAwLjEtMC43IDUuNy0xOC41IDIyLjUtMzAuOSA0MS44LTMwLjkgMTUuOCAwIDMwLjUgOC42IDM4LjIgMjIuNSAwLjcgMS4yIDAuMiAyLjctMSAzLjRzLTIuNyAwLjMtMy40LTFjLTYuOS0xMi4zLTE5LjgtMjAtMzMuOS0yMC0xNy4xIDAtMzIgMTEtMzcuMSAyNy40LTAuNCAxLjMtMS44IDItMy4xIDEuNi0xLTAuMy0xLjYtMS4yLTEuNi0yLjN6Ii8+PHBhdGggZD0ibTQ1LjcgMjU2YzAtMzAuNyAyNS01NS42IDU1LjYtNTUuNiAzMC43IDAgNTUuNiAyNC45IDU1LjYgNTUuNiAwIDEuNC0xLjEgMi41LTIuNSAyLjVzLTIuNS0xLjEtMi41LTIuNWMwLTI4LTIyLjctNTAuNy01MC43LTUwLjctMjcuOSAwLTUwLjcgMjIuNy01MC43IDUwLjcgMCAxLjQtMS4xIDIuNS0yLjUgMi41LTEuMiAwLTIuMy0xLjEtMi4zLTIuNXoiLz48cGF0aCBkPSJtMzUyLjMgMjU2LjFsMjEuOSAzNi0xLjIgMC44LTU4LjgtMjMuM2MtMjAuNS00LjUtNDAuOS05LTYxLjQtMTMuNSAyMC41LTQuNSA0MC45LTkgNjEuNC0xMy41bDU4LjgtMjMuMyAxLjIgMC42LTIxLjkgMzYuMnoiLz48L3N2Zz4=);\
    display: block;\
    width: 35px;\
    height: 35px;\
}\
.ico-out {\
    background-image: url(data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz48c3ZnIGVuYWJsZS1iYWNrZ3JvdW5kPSJuZXcgMCAwIDUxMiA1MTIiIHZlcnNpb249IjEuMSIgdmlld0JveD0iMCAwIDUxMiA1MTIiIHhtbDpzcGFjZT0icHJlc2VydmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHN0eWxlIHR5cGU9InRleHQvY3NzIj4uc3Qwe2ZpbGw6I0ZGRkZGRjt9PC9zdHlsZT48cGF0aCBkPSJtNDY0LjQgMjY2LjFoLTMwMS44Yy01LjUgMC0xMC00LjUtMTAtMTBzNC41LTEwIDEwLTEwaDMwMS44YzUuNSAwIDEwIDQuNSAxMCAxMHMtNC41IDEwLTEwIDEweiIvPjxwYXRoIGNsYXNzPSJzdDAiIGQ9Im0xMDEuMyAzMTcuM2MtMzMuOCAwLTYxLjMtMjcuNS02MS4zLTYxLjNzMjcuNS02MS4zIDYxLjMtNjEuMyA2MS4zIDI3LjQgNjEuMyA2MS4zYzAgMzMuOC0yNy40IDYxLjMtNjEuMyA2MS4zIi8+PHBhdGggZD0ibTM3LjYgMjU2YzAtMzUuMSAyOC42LTYzLjcgNjMuNy02My43czYzLjggMjguNiA2My44IDYzLjctMjguNiA2My43LTYzLjggNjMuN2MtMzUuMSAwLTYzLjctMjguNi02My43LTYzLjd6bTEyMi4yIDBjMC0zMi4yLTI2LjItNTguNC01OC40LTU4LjRzLTU4LjQgMjYuMi01OC40IDU4LjQgMjYuMiA1OC40IDU4LjQgNTguNGMzMi4xIDAgNTguNC0yNi4yIDU4LjQtNTguNHoiLz48cGF0aCBkPSJtMTAxLjQgMjgyLjFjLTE0LjQgMC0yNi4xLTExLjctMjYuMS0yNi4xczExLjctMjYuMSAyNi4xLTI2LjEgMjYuMSAxMS43IDI2LjEgMjYuMWMtMC4xIDE0LjQtMTEuNyAyNi4xLTI2LjEgMjYuMSIvPjxwYXRoIGQ9Im01NiAyNDIuOWMwLTAuMiAwLTAuNSAwLjEtMC43IDUuNy0xOC41IDIyLjUtMzAuOSA0MS44LTMwLjkgMTUuOCAwIDMwLjUgOC42IDM4LjIgMjIuNSAwLjcgMS4yIDAuMiAyLjctMSAzLjRzLTIuNyAwLjMtMy40LTFjLTYuOS0xMi4zLTE5LjgtMjAtMzMuOS0yMC0xNy4xIDAtMzIgMTEtMzcuMSAyNy40LTAuNCAxLjMtMS44IDItMy4xIDEuNi0xLTAuMy0xLjYtMS4yLTEuNi0yLjN6Ii8+PHBhdGggZD0ibTQ1LjcgMjU2YzAtMzAuNyAyNS01NS42IDU1LjYtNTUuNiAzMC43IDAgNTUuNiAyNC45IDU1LjYgNTUuNiAwIDEuNC0xLjEgMi41LTIuNSAyLjVzLTIuNS0xLjEtMi41LTIuNWMwLTI4LTIyLjctNTAuNy01MC43LTUwLjctMjcuOSAwLTUwLjcgMjIuNy01MC43IDUwLjcgMCAxLjQtMS4xIDIuNS0yLjUgMi41LTEuMiAwLTIuMy0xLjEtMi4zLTIuNXoiLz48cGF0aCBkPSJtMjc0LjcgMjU2LjFsLTIxLjktMzYgMS4yLTAuOCA1OC43IDIzLjNjMjAuNSA0LjUgNDAuOSA5IDYxLjQgMTMuNS0yMC41IDQuNS00MC45IDktNjEuNCAxMy41bC01OC43IDIzLjMtMS4yLTAuNiAyMS45LTM2LjJ6Ii8+PC9zdmc+);\
    display: block;\
    width: 35px;\
    height: 35px;\
}\
.ico-pwm {\
    background-image: url(data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz48c3ZnIGVuYWJsZS1iYWNrZ3JvdW5kPSJuZXcgMCAwIDUxMiA1MTIiIHZlcnNpb249IjEuMSIgdmlld0JveD0iMCAwIDUxMiA1MTIiIHhtbDpzcGFjZT0icHJlc2VydmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHN0eWxlIHR5cGU9InRleHQvY3NzIj4uc3Qwe2ZpbGw6I0ZGRkZGRjt9PC9zdHlsZT48cGF0aCBkPSJtMzI0LjEgMzI0Yy0yMy4zIDAtMzUtNDEuMS0zOC4xLTUzLjdsLTUuOC0yMy45Yy00LjgtMTkuOS0xNC4zLTM3LjctMTguNy0zOC40LTQuMyAwLjctMTMuOCAxOC42LTE4LjYgMzguNC0yLjYgMTEtMTMuNiAxOS42LTI0LjkgMTkuNmgtMTM2LjZ2LTIwaDEzNi44YzIuMSAwIDQuOS0yLjIgNS40LTQuMyAzLTEyLjYgMTQuOC01My43IDM4LjEtNTMuN3MzNSA0MS4xIDM4LjEgNTMuN2w1LjcgMjMuOWM0LjggMTkuOSAxNC4zIDM3LjcgMTguNyAzOC40IDQuMy0wLjcgMTMuOC0xOC42IDE4LjYtMzguNCAyLjYtMTEgMTMuNi0xOS42IDI0LjktMTkuNmgzOS42djIwaC0zOS42Yy0yLjEgMC00LjkgMi4yLTUuNCA0LjMtMy4xIDEyLjYtMTQuOSA1My43LTM4LjIgNTMuN3oiLz48cGF0aCBjbGFzcz0ic3QwIiBkPSJtMTAxLjMgMzE3LjNjLTMzLjggMC02MS4zLTI3LjUtNjEuMy02MS4zczI3LjUtNjEuMyA2MS4zLTYxLjMgNjEuMyAyNy40IDYxLjMgNjEuM2MwIDMzLjgtMjcuNCA2MS4zLTYxLjMgNjEuMyIvPjxwYXRoIGQ9Im0zNy42IDI1NmMwLTM1LjEgMjguNi02My43IDYzLjctNjMuN3M2My44IDI4LjYgNjMuOCA2My43LTI4LjYgNjMuNy02My44IDYzLjdjLTM1LjEgMC4xLTYzLjctMjguNS02My43LTYzLjd6bTEyMi4yIDBjMC0zMi4yLTI2LjItNTguNC01OC40LTU4LjRzLTU4LjQgMjYuMi01OC40IDU4LjQgMjYuMiA1OC40IDU4LjQgNTguNGMzMi4xIDAgNTguNC0yNi4yIDU4LjQtNTguNHoiLz48cGF0aCBkPSJtMTAxLjQgMjgyLjFjLTE0LjQgMC0yNi4xLTExLjctMjYuMS0yNi4xczExLjctMjYuMSAyNi4xLTI2LjEgMjYuMSAxMS43IDI2LjEgMjYuMWMtMC4xIDE0LjQtMTEuNyAyNi4xLTI2LjEgMjYuMSIvPjxwYXRoIGQ9Im01NiAyNDIuOWMwLTAuMiAwLTAuNSAwLjEtMC43IDUuNy0xOC41IDIyLjUtMzAuOSA0MS44LTMwLjkgMTUuOCAwIDMwLjUgOC42IDM4LjIgMjIuNSAwLjcgMS4yIDAuMiAyLjctMSAzLjRzLTIuNyAwLjMtMy40LTFjLTYuOS0xMi4zLTE5LjgtMjAtMzMuOS0yMC0xNy4xIDAtMzIgMTEtMzcuMSAyNy40LTAuNCAxLjMtMS44IDItMy4xIDEuNi0xLTAuMy0xLjYtMS4yLTEuNi0yLjN6Ii8+PHBhdGggZD0ibTQ1LjcgMjU2YzAtMzAuNyAyNS01NS42IDU1LjYtNTUuNiAzMC43IDAgNTUuNiAyNC45IDU1LjYgNTUuNiAwIDEuNC0xLjEgMi41LTIuNSAyLjVzLTIuNS0xLjEtMi41LTIuNWMwLTI4LTIyLjctNTAuNy01MC43LTUwLjctMjcuOSAwLTUwLjcgMjIuNy01MC43IDUwLjcgMCAxLjQtMS4xIDIuNS0yLjUgMi41LTEuMiAwLTIuMy0xLjEtMi4zLTIuNXoiLz48cGF0aCBkPSJtNDY0LjQgMjY2aC01Ny4xYy01LjUgMC0xMC00LjUtMTAtMTBzNC41LTEwIDEwLTEwaDU3LjFjNS41IDAgMTAgNC41IDEwIDEwcy00LjUgMTAtMTAgMTB6Ii8+PC9zdmc+);\
    display: block;\
    width: 35px;\
    height: 35px;\
}\
.ico-servo {\
    background-image: url(data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz48c3ZnIGVuYWJsZS1iYWNrZ3JvdW5kPSJuZXcgMCAwIDUxMiA1MTIiIHZlcnNpb249IjEuMSIgdmlld0JveD0iMCAwIDUxMiA1MTIiIHhtbDpzcGFjZT0icHJlc2VydmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHN0eWxlIHR5cGU9InRleHQvY3NzIj4uc3Qwe2ZpbGw6I0ZGRkZGRjt9PC9zdHlsZT48cGF0aCBkPSJtMzIxLjQgMjcyLjloLTE1MC45Yy01LjUgMC0xMC00LjUtMTAtMTBzNC41LTEwIDEwLTEwaDE1MC45YzUuNSAwIDEwIDQuNSAxMCAxMHMtNC40IDEwLTEwIDEweiIvPjxwYXRoIGNsYXNzPSJzdDAiIGQ9Im0xMDkuMyAzMjQuMWMtMzMuOCAwLTYxLjMtMjcuNC02MS4zLTYxLjMgMC0zMy44IDI3LjUtNjEuMyA2MS4zLTYxLjNzNjEuMyAyNy40IDYxLjMgNjEuM2MtMC4xIDMzLjgtMjcuNSA2MS4zLTYxLjMgNjEuMyIvPjxwYXRoIGQ9Im00NS41IDI2Mi44YzAtMzUuMSAyOC42LTYzLjcgNjMuNy02My43czYzLjggMjguNiA2My44IDYzLjctMjguNiA2My43LTYzLjggNjMuN2MtMzUuMSAwLTYzLjctMjguNi02My43LTYzLjd6bTEyMi4yIDBjMC0zMi4yLTI2LjItNTguNC01OC40LTU4LjRzLTU4LjQgMjYuMi01OC40IDU4LjQgMjYuMiA1OC40IDU4LjQgNTguNCA1OC40LTI2LjIgNTguNC01OC40eiIvPjxwYXRoIGQ9Im0xMDkuMyAyODguOWMtMTQuNCAwLTI2LjEtMTEuNy0yNi4xLTI2LjFzMTEuNy0yNi4xIDI2LjEtMjYuMSAyNi4xIDExLjcgMjYuMSAyNi4xLTExLjcgMjYuMS0yNi4xIDI2LjEiLz48cGF0aCBkPSJtMzIxLjQgMjg4LjljLTE0LjQgMC0yNi4xLTExLjctMjYuMS0yNi4xczExLjctMjYuMSAyNi4xLTI2LjEgMjYuMSAxMS43IDI2LjEgMjYuMS0xMS43IDI2LjEtMjYuMSAyNi4xIi8+PHBhdGggZD0ibTYzLjkgMjQ5LjdjMC0wLjIgMC0wLjUgMC4xLTAuNyA1LjctMTguNSAyMi41LTMwLjkgNDEuOC0zMC45IDE1LjggMCAzMC41IDguNiAzOC4yIDIyLjUgMC43IDEuMiAwLjIgMi43LTEgMy40cy0yLjcgMC4zLTMuNC0xYy02LjktMTIuMy0xOS44LTIwLTMzLjktMjAtMTcuMSAwLTMyIDExLTM3LjEgMjcuNC0wLjQgMS4zLTEuOCAyLTMuMSAxLjYtMC45LTAuMy0xLjYtMS4yLTEuNi0yLjN6Ii8+PHBhdGggZD0ibTUzLjYgMjYyLjhjMC0zMC43IDI1LTU1LjYgNTUuNi01NS42IDMwLjcgMCA1NS42IDI0LjkgNTUuNiA1NS42IDAgMS40LTEuMSAyLjUtMi41IDIuNXMtMi41LTEuMS0yLjUtMi41YzAtMjgtMjIuNy01MC43LTUwLjctNTAuNy0yNy45IDAtNTAuNyAyMi43LTUwLjcgNTAuNyAwIDEuNC0xLjEgMi41LTIuNSAyLjUtMS4yIDAtMi4zLTEuMS0yLjMtMi41eiIvPjxwYXRoIGQ9Im0zMjEuNCAyNzIuOGMtMy43IDAtNy4yLTItOS01LjUtMi41LTQuOS0wLjUtMTAuOSA0LjUtMTMuNGwxMzUtNjcuM2M1LTIuNSAxMS0wLjQgMTMuNCA0LjUgMi41IDQuOSAwLjUgMTAuOS00LjUgMTMuNGwtMTM1IDY3LjNjLTEuMyAwLjYtMi45IDEtNC40IDF6Ii8+PC9zdmc+);\
    display: block;\
    width: 35px;\
    height: 35px;\
}\
</style>\
";

const char HTTP_IOT_TITLE[] PROGMEM      =
"<title>Fluo IoT web page - fluotechnology.co.uk</title></head><body>\
<div class='container-fluid'>\
<div class='row'>\
<div class='col'>\
<img src='http://0-1.es/fluoIOT' class='rounded float-left' style='opacity:0.7;filter:alpha(opacity=70); padding-left: 50px; padding-right: 40px; padding-top: 10px; padding-bottom: 5px;'>\
<h1 style='padding-left: 50px; padding-right: 50px; padding-top: 10px; padding-bottom: 5px;'>IoT web page</h1>\
</div></div>\
";

const char HTTP_IOT_ITEM_D0[] PROGMEM      =
"<h3 style='padding-left: 5px; padding-right: 5px; padding-top: 10px; padding-bottom: 15px;'>GPIO Map</h3>\
<div class='row'><div class='col'>\
<form id='D0Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D0outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D0' value='OFF' id='D0output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D0incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D0' value='INPUT' id='D0input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D0servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D0' value='SERVO' id='D0servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-light btn-sm {D0pwmcheck}' style='border:none;' onclick='myFunc();' disabled><span class='ico-pwm'/>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D0 <span class='badge badge-pill badge-secondary'>{D0label}</span></h4></div>\
\
<div id='D0O' class='col'><form id='D0OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D0off}'>OFF\
    <input type='radio' name='D0' value='OFF' id='D0on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D0on}'>ON\
    <input type='radio' name='D0' value='ON' id='D0off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D0I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group'>\
<button type='button submit' name='D0' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D0Input}</div></div>\
</div></form></div>\
\
<div id='D0S' class='col'><form name='D00servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group'>\
<button type='button submit' name='D0' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D0Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D00SL'  aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D1[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D1Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D1outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D1' value='OFF' id='D1output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D1incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D1' value='INPUT' id='D1input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D1servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D1' value='SERVO' id='D1servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-light btn-sm {D1pwmcheck}' style='border:none;' onclick='myFunc();' disabled><span class='ico-pwm'/>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D1 <span class='badge badge-pill badge-secondary'> {D1label}</span></h4></div>\
\
<div id='D1O' class='col'><form id='D1OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D1off}'>OFF\
    <input type='radio' name='D1' value='OFF' id='D1on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D1on}'>ON\
    <input type='radio' name='D1' value='ON' id='D1off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D1I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group'>\
<button type='button submit' name='D1' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D1Input}</div></div>\
</div></form></div>\
\
<div id='D1S' class='col'><form name='D01servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group'>\
<button type='button submit' name='D1' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D1Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D01SL' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D2[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D2Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D2outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D2' value='OFF' id='D2output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D2incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D2' value='INPUT' id='D2input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D2servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D2' value='SERVO' id='D2servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-light btn-sm {D2pwmcheck}' style='border:none;' onclick='myFunc();' disabled><span class='ico-pwm'/>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D2 <span class='badge badge-pill badge-secondary'>{D2label}</span></h4></div>\
\
<div id='D2O' class='col'><form id='D2OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D2off}'>OFF\
    <input type='radio' name='D2' value='OFF' id='D2on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D2on}'>ON\
    <input type='radio' name='D2' value='ON' id='D2off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D2I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group'>\
<button type='button submit' name='D2' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D2Input}</div></div>\
</div></form></div>\
\
<div id='D2S' class='col'><form name='D02servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group'>\
<button type='button submit' name='D2' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D2Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D02SL' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D3[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D3Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D3outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D3' value='OFF' id='D3output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D3incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D3' value='INPUT' id='D3input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D3servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D3' value='SERVO' id='D3servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-info btn-sm {D3pwmcheck}' style='border:none;'><span class='ico-pwm'/>\
    <input type='radio' name='D3' value='PWM' id='D3pwm' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D3 <span class='badge badge-pill badge-secondary'>{D3label}</span></h4></div>\
\
<div id='D3O' class='col'><form id='D3OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D3off}'>OFF\
    <input type='radio' name='D3' value='OFF' id='D3on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D3on}'>ON\
    <input type='radio' name='D3' value='ON' id='D3off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D3I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group'>\
<button type='button submit' name='D3' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D3Input}</div></div>\
</div></form></div>\
\
<div id='D3S' class='col'><form name='D03servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group'>\
<button type='button submit' name='D3' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D3Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D03SL' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
\
<div id='D3P' class='col'><form name='D03pwminput' action='/' onsubmit='return checkPWM(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group'>\
<button type='button submit' name='D3' value='PWM' class='btn btn-info'>PWM</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D3Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Value' size='3' name='P' id='D03PL' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D4[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D4Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D4outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D4' value='OFF' id='D4output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D4incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D4' value='INPUT' id='D4input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D4servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D4' value='SERVO' id='D4servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-light btn-sm {D4pwmcheck}' style='border:none; onclick='myFunc();' disabled'><span class='ico-pwm'/>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D4 <span class='badge badge-pill badge-secondary'>{D4label}</span></h4></div>\
\
<div id='D4O' class='col'><form id='D4OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D4off}'>OFF\
    <input type='radio' name='D4' value='OFF' id='D4on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D4on}'>ON\
    <input type='radio' name='D4' value='ON' id='D4off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D4I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group'>\
<button type='button submit' name='D4' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D4Input}</div></div>\
</div></form></div>\
\
<div id='D4S' class='col'><form name='D04servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group'>\
<button type='button submit' name='D4' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D4Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D04SL' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D5[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D5Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D5outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D5' value='OFF' id='D5output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D5incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D5' value='INPUT' id='D5input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D5servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D5' value='SERVO' id='D5servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-info btn-sm {D5pwmcheck}' style='border:none;'><span class='ico-pwm'/>\
    <input type='radio' name='D5' value='PWM' id='D5pwm' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D5 <span class='badge badge-pill badge-secondary'>{D5label}</span></h4></div>\
\
<div id='D5O' class='col'><form id='D5OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D5off}'>OFF\
    <input type='radio' name='D5' value='OFF' id='D5on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D5on}'>ON\
    <input type='radio' name='D5' value='ON' id='D5off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D5I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group'>\
<button type='button submit' name='D5' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D5Input}</div></div>\
</div></form></div>\
\
<div id='D5S' class='col'><form name='D05servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group'>\
<button type='button submit' name='D5' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D5Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D05SL' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
\
<div id='D5P' class='col'><form name='D05pwminput' action='/' onsubmit='return checkPWM(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group'>\
<button type='button submit' name='D5' value='PWM' class='btn btn-info'>PWM</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D5Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Value' size='3' name='P' id='D05PL' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D6[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D6Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D6outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D6' value='OFF' id='D6output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D6incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D6' value='INPUT' id='D6input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D6servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D6' value='SERVO' id='D6servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-info btn-sm {D6pwmcheck}' style='border:none;'><span class='ico-pwm'/>\
    <input type='radio' name='D6' value='PWM' id='D6pwm' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D6 <span class='badge badge-pill badge-secondary'>{D6label}</span></h4></div>\
\
<div id='D6O' class='col'><form id='D6OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D6off}'>OFF\
    <input type='radio' name='D6' value='OFF' id='D6on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D6on}'>ON\
    <input type='radio' name='D6' value='ON' id='D6off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D6I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group'>\
<button type='button submit' name='D6' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D6Input}</div></div>\
</div></form></div>\
\
<div id='D6S' class='col'><form name='D06servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group'>\
<button type='button submit' name='D6' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D6Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D06SL' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
\
<div id='D6P' class='col'><form name='D06pwminput' action='/' onsubmit='return checkPWM(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group'>\
<button type='button submit' name='D6' value='PWM' class='btn btn-info'>PWM</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D6Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Value' size='3' name='P' id='D06PL' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D7[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D7Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D7outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D7' value='OFF' id='D7output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D7incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D7' value='INPUT' id='D7input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D7servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D7' value='SERVO' id='D7servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-light btn-sm {D7pwmcheck}' style='border:none;' onclick='myFunc();' disabled><span class='ico-pwm'/>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D7 <span class='badge badge-pill badge-secondary'>{D7label}</span></h4></div>\
\
<div id='D7O' class='col'><form id='D7OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D7off}'>OFF\
    <input type='radio' name='D7' value='OFF' id='D7on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D7on}'>ON\
    <input type='radio' name='D7' value='ON' id='D7off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D7I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group' aria-label='BasicTwo'>\
<button type='button submit' name='D7' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D7Input}</div></div>\
</div></form></div>\
\
<div id='D7S' class='col'><form name='D07servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group' aria-label='BasicThree'>\
<button type='button submit' name='D7' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D7Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D07SL' aria-label='BasicThree' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D8[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D8Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D8outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D8' value='OFF' id='D8output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D8incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D8' value='INPUT' id='D8input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D8servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D8' value='SERVO' id='D8servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-light btn-sm {D8pwmcheck}' style='border:none;' onclick='myFunc();' disabled><span class='ico-pwm'/>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D8 <span class='badge badge-pill badge-secondary'>{D8label}</span></h4></div>\
\
<div id='D8O' class='col'><form id='D8OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D8off}'>OFF\
    <input type='radio' name='D8' value='OFF' id='D8on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D8on}'>ON\
    <input type='radio' name='D8' value='ON' id='D8off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D8I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group' aria-label='BasicTwo'>\
<button type='button submit' name='D8' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D8Input}</div></div>\
</div></form></div>\
\
<div id='D8S' class='col'><form name='D08servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group' aria-label='BasicThree'>\
<button type='button submit' name='D8' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D8Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D08SL' aria-label='BasicThree' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D9[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D9Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D9outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D9' value='OFF' id='D9output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D9incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D9' value='INPUT' id='D9input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D9servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D9' value='SERVO' id='D9servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-info btn-sm {D9pwmcheck}' style='border:none;'><span class='ico-pwm'/>\
    <input type='radio' name='D9' value='PWM' id='D9pwm' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D9 <span class='badge badge-pill badge-secondary'>{D9label}</span></h4></div>\
\
<div id='D9O' class='col'><form id='D9OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D9off}'>OFF\
    <input type='radio' name='D9' value='OFF' id='D9on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D9on}'>ON\
    <input type='radio' name='D9' value='ON' id='D9off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D9I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group' aria-label='BasicTwo'>\
<button type='button submit' name='D9' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D9Input}</div></div>\
</div></form></div>\
\
<div id='D9S' class='col'><form name='D09servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group' aria-label='BasicThree'>\
<button type='button submit' name='D9' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D9Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D09SL' aria-label='BasicThree' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
\
<div id='D9P' class='col'><form name='D09pwminput' action='/' onsubmit='return checkPWM(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group' aria-label='BasicThree'>\
<button type='button submit' name='D9' value='PWM' class='btn btn-info'>PWM</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D9Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Value' size='3' name='P' id='D09PL' aria-label='BasicThree' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D10[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D10Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D10outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D10' value='OFF' id='D10output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D10incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D10' value='INPUT' id='D10input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D10servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D10' value='SERVO' id='D10servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-info btn-sm {D10pwmcheck}' style='border:none;'><span class='ico-pwm'/>\
    <input type='radio' name='D10' value='PWM' id='D10pwm' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D10 <span class='badge badge-pill badge-secondary'>{D10label}</span></h4></div>\
\
<div id='D10O' class='col'><form id='D10OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D10off}'>OFF\
    <input type='radio' name='D10' value='OFF' id='D10on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D10on}'>ON\
    <input type='radio' name='D10' value='ON' id='D10off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D10I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group' aria-label='BasicTwo'>\
<button type='button submit' name='D10' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D10Input}</div></div>\
</div></form></div>\
\
<div id='D10S' class='col'><form name='D10servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group' aria-label='BasicThree'>\
<button type='button submit' name='D10' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D10Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D10SL' aria-label='BasicThree' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
\
<div id='D10P' class='col'><form name='D10pwminput' action='/' onsubmit='return checkPWM(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group' aria-label='BasicThree'>\
<button type='button submit' name='D10' value='PWM' class='btn btn-info'>PWM</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D10Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Value' size='3' name='P' id='D10PL' aria-label='BasicThree' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D11[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D11Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D11outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D11' value='OFF' id='D11output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D11incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D11' value='INPUT' id='D11input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D11servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D11' value='SERVO' id='D11servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-info btn-sm {D11pwmcheck}' style='border:none;'><span class='ico-pwm'/>\
    <input type='radio' name='D11' value='PWM' id='D11pwm' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D11 <span class='badge badge-pill badge-secondary'> {D11label}</span></h4></div>\
\
<div id='D11O' class='col'><form id='D11OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D11off}'>OFF\
    <input type='radio' name='D11' value='OFF' id='D11on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D11on}'>ON\
    <input type='radio' name='D11' value='ON' id='D11off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D11I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group' aria-label='BasicTwo'>\
<button type='button submit' name='D11' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D11Input}</div></div>\
</div></form></div>\
\
<div id='D11S' class='col'><form name='D11servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group' aria-label='BasicThree'>\
<button type='button submit' name='D11' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D11Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D11SL' aria-label='BasicThree' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
\
<div id='D11P' class='col'><form name='D11pwminput' action='/' onsubmit='return checkPWM(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group' aria-label='BasicThree'>\
<button type='button submit' name='D11' value='PWM' class='btn btn-info'>PWM</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D11Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Value' size='3' name='P' id='D11PL' aria-label='BasicThree' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D12[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D12Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D12outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D12' value='OFF' id='D12output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D12incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D12' value='INPUT' id='D12input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D12servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D12' value='SERVO' id='D12servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-light btn-sm {D12pwmcheck}' style='border:none;' onclick='myFunc();' disabled><span class='ico-pwm'/>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D12 <span class='badge badge-pill badge-secondary'>{D12label}</span></h4></div>\
\
<div id='D12O' class='col'><form id='D12OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D12off}'>OFF\
    <input type='radio' name='D12' value='OFF' id='D12on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D12on}'>ON\
    <input type='radio' name='D12' value='ON' id='D12off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D12I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group' aria-label='BasicTwo'>\
<button type='button submit' name='D12' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D12Input}</div></div>\
</div></form></div>\
\
<div id='D12S' class='col'><form name='D12servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group' aria-label='BasicThree'>\
<button type='button submit' name='D12' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D12Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D12SL' aria-label='BasicThree' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ITEM_D13[] PROGMEM      =
"<div class='row'><div class='col'>\
<form id='D13Form' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-success btn-sm {D13outcheck}' style='border:none;'><span class='ico-out'/>\
    <input type='radio' name='D13' value='OFF' id='D13output' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-primary btn-sm {D13incheck}' style='border:none;'><span class='ico-in'/>\
    <input type='radio' name='D13' value='INPUT' id='D13input' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-warning btn-sm {D13servocheck}' style='border:none;'><span class='ico-servo'/>\
    <input type='radio' name='D13' value='SERVO' id='D13servo' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-light btn-sm {D13pwmcheck}' style='border:none;' onclick='myFunc();' disabled><span class='ico-pwm'/>\
  </label>\
</div></form></div>\
\
<div class='col'><h4 class ='text-left'>D13 <span class='badge badge-pill badge-secondary'>{D13label}</span></h4></div>\
\
<div id='D13O' class='col'><form id='D13OnOffForm' action='/' method='POST'>\
<div class='btn-group btn-group-toggle' data-toggle='buttons'>\
  <label class='btn btn-outline-danger {D13off}'>OFF\
    <input type='radio' name='D13' value='OFF' id='D13on' autocomplete='off'>\
  </label>\
  <label class='btn btn-outline-success {D13on}'>ON\
    <input type='radio' name='D13' value='ON' id='D13off' autocomplete='off'>\
  </label>\
</div></form></div>\
\
<div id='D13I' class='col'><form action='/' method='POST'> <div class='btn-group btn-group-sm' role='group' aria-label='BasicTwo'>\
<button type='button submit' name='D13' value='INPUT' class='btn btn-primary'>INPUT</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D13Input}</div></div>\
</div></form></div>\
\
<div id='D13S' class='col'><form name='D13servoinput' action='/' onsubmit='return checkServo(this)' method='POST'>\
<div class='btn-group mr-4 btn-group-sm' role='group' aria-label='BasicThree'>\
<button type='button submit' name='D13' value='SERVO' class='btn btn-warning'>SERVO</button>\
<div class='input-group-prepend'><div style='background-color: lightgrey;' class='input-group-text' id='btnGroupAddon'>{D13Input}</div>\
<input type='text submit' class='input-group-text' placeholder='Angle' size='3' name='S' id='D13SL' aria-label='BasicThree' aria-describedby='btnGroupAddon'></div>\
</div></form></div>\
</div><!--ROW-->\
";

const char HTTP_IOT_ANALOG_ITEM[] PROGMEM      =
"<h3 style='padding-left: 5px; padding-right: 0px; padding-top: 30px; padding-bottom: 15px;' >Analog Input</h3>\
<div class='btn-group mr-4 btn-group-sm' role='group' aria-label='BasicThree'>\
<button  type='button' class='btn btn-primary'>{A0label} <span class='badge badge-pill badge-light'>{A0value}</span></button>\
<button  type='button' class='btn btn-primary'>{A1label} <span class='badge badge-pill badge-light'>{A1value}</span></button>\
<button  type='button' class='btn btn-primary'>{A2label} <span class='badge badge-pill badge-light'>{A2value}</span></button>\
<button  type='button' class='btn btn-primary'>{A3label} <span class='badge badge-pill badge-light'>{A3value}</span></button>\
<button  type='button' class='btn btn-primary'>{A4label} <span class='badge badge-pill badge-light'>{A4value}</span></button>\
<button  type='button' class='btn btn-primary'>{A5label} <span class='badge badge-pill badge-light'>{A5value}</span></button>\
</div>";

const char HTTP_IOT_ANALOG_TABLE[] PROGMEM      =
"<table class='table'>\
<thead><tr><th>Label</th><th>Voltage Measure</th></tr></thead>\
<tbody>\
<tr><td>{A0label}</td>\
<td>{A0voltage} Volt</td></tr>\
<tr class='active'><td>{A1label}</td>\
<td>{A1voltage} Volt</td></tr>\
<tr><td>{A2label}</td>\
<td>{A2voltage} Volt</td></tr>\
<tr class='active'><td>{A3label}</td>\
<td>{A3voltage} Volt</td></tr>\
<tr><td>{A4label}</td>\
<td>{A4voltage} Volt</td></tr>\
<tr class='active'><td>{A5label}</td>\
<td>{A5voltage} Volt</td></tr>\
</tbody>\
</table>";

const char HTTP_IOT_CLOSE[] PROGMEM      =
"</div></div></div></body></html>";

//----------------- WebSocket HTML-CSS-JAVASCRIPT----------------------//

const char HTTP_WEBSOCKET_HEAD[] PROGMEM        =
"<html> <head> <title>FluoTech</title>";

const char HTTP_WEBSOCKET_STYLE[] PROGMEM       =
"<style>\
    #fluo {\
        font: bold 15px arial;\
        margin: auto;\
        padding: 10px;\
        text-align: left;\
      }\
</style>";

const char HTTP_WEBSOCKET_ENDHEAD[] PROGMEM     =
"</head>";

const char HTTP_WEBSOCKET_BODY[] PROGMEM        =
"<body>\
<div id='fluo'>\
  <p id = 'conn'>Mi connetto...</p>\
  <table>\
    <tr><td>URI: </td><td id = 'URI'></td></tr>\
    <tr><td>Method: </td><td id = 'Method'></td></tr>\
    <tr><td>Arguments: </td><td id = 'Arguments'></td></tr>\
    <tr><td>AVR Messaggio: </td><td id = 'sms'></td></tr>\
  </table>\
</div>";

const char HTTP_WEBSOCKET_INITSCRIPT[] PROGMEM  =
"<script>var ws = new WebSocket('";

const char HTTP_WEBSOCKET_SCRIPT[] PROGMEM      =
"');\
  ws.onopen = function(){\
    document.body.style.backgroundColor = '#cfc';\
    document.getElementById('conn').innerHTML = 'Connesso';\
  };\
   ws.onclose = function() {\
    document.body.style.backgroundColor = null;\
  };\
  ws.onmessage = function(event) {\
    var res = event.data.split(':');\
    if(res[0] == 'URI') document.getElementById('URI').innerHTML = res[1];\
    if(res[0] == 'Method') document.getElementById('Method').innerHTML = res[1];\
    if(res[0] == 'Arguments') document.getElementById('Arguments').innerHTML = res[1];\
    if(res[0] == 'sms') document.getElementById('sms').innerHTML = res[1];\
  };\
  ws.onerror = function(){\
    document.getElementById('conn').innerHTML = 'Refresh della pagina';\
  };\
</script>";

const char HTTP_WEBSOCKET_ENDBODY[] PROGMEM     =
"</body></html>";

#endif