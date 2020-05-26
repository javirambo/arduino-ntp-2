/*
  Prueba de un servidor horario NTP.
  Javier Rambaldo / Abril-2020
*/
#include <SPI.h>
#include <Ethernet.h>
#include <time.h>

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};
char serverName[] = "time.nist.gov";
EthernetClient client;

void setup()
{
    // inicializo mi Ethernet Shield W5100:
    Ethernet.init(10);

    Serial.begin(9600);

    // start the Ethernet connection:
    if (Ethernet.begin(mac) == 0)
    {
        Serial.println("Failed to configure Ethernet using DHCP");
        while (true)
            ; // no puedo hacer nada sin la IP....
    }
    Serial.print("IP number assigned by DHCP is ");
    Serial.println(Ethernet.localIP());
}

// se conecta al servidor y hace la peticion (solo un GET en /)
// ejemplo:
// curl time.nist.gov:13
// 58949 20-04-10 22:57:19 50 0 0 931.0 UTC(NIST) *
bool NtpRequest()
{
    if (client.connect(serverName, 13))
    {
        client.println("GET / HTTP/1.1");
        client.println();
        return true;
    }
    else
    {
        Serial.println("falló la conexión");
        return false;
    }
}

// Espera la trama de respuesta y hace un parseo completo de la linea
// "\n58949 20-04-10 22:57:19 50 0 0 931.0 UTC(NIST) * "
void NtpResponse(struct tm *time)
{
    char buffer[55];
    char *p = buffer;
    while (client.connected())
    {
        if (client.available())
            *p++ = client.read();
    }
    client.stop();

    time->tm_year = 100 + atoi(buffer + 7);
    time->tm_mon = atoi(buffer + 10) - 1;
    time->tm_mday = atoi(buffer + 13);
    time->tm_hour = atoi(buffer + 16);
    time->tm_min = atoi(buffer + 19);
    time->tm_sec = atoi(buffer + 22);
    time->tm_isdst = 0;
}

void loop()
{
    // me conecto al servcer NTP y hago la petición:
    if (NtpRequest())
    {
        struct tm ntp_time;
        // espero la respuesta y la muestro:
        NtpResponse(&ntp_time);

        set_system_time(mktime(&ntp_time));
        set_zone(-3 * ONE_HOUR);

        // tomo la hora, la convierto a formato legible y la muestro:
        Serial.println(asctime(&ntp_time));

        delay(6000);
    }
}

