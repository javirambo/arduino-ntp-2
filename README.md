# arduino-ntp-2
_Otra forma de conectarte a un servidor NTP desde Arduino_

## Comenzando 🚀

_En esta entrada https://micro57.wordpress.com/2020/04/11/la-hora-en-arduino-con-servidor-ntp te mostré como conectarse a un servidor NTP por medio del protocolo UDP y obtener la hora de Internet, para poder usarla dentro de tu proyecto con Arduino._

Esta es otra forma de hacerlo, pero con protocolo TCP/HTTP

Podés hacer una prueba desde tu consola Linux así:

```
curl  time.nist.gov:13  -v

* Rebuilt URL to: time.nist.gov:13/
*   Trying 132.163.97.4...
* TCP_NODELAY set
* Connected to time.nist.gov (132.163.97.4) port 13 (#0)
> GET / HTTP/1.1
> Host: time.nist.gov:13
> User-Agent: curl/7.58.0
> Accept: */*
> 
* Recv failure: Conexión reinicializada por la máquina remota
* stopped the pause stream!
* Closing connection 0
curl: (56) Recv failure: Conexión reinicializada por la máquina remota
```

Ahí vemos como nos conectamos a un servidor NTP (time.nist.gov) al puerto 13, y nos responde una cadena de caracteres con datos, y dentro de ellos se ve la fecha y la hora.
  
Podemos usar esto para extraer fecha y hora, y setear nuestro reloj del Arduino.

