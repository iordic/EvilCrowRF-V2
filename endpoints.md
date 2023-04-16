endpoints
=========
| Request                 | Response                      | Parameters       |
|:------------------------|:------------------------------|:-----------------|
| GET /                   | /HTML/index.html              | cambiar: https://github.com/me-no-dev/ESPAsyncWebServer#serving-static-files
| GET /rxconfig           | /HTML/rxconfig.html           |
| GET /txconfig           | /HTML/txconfig.html
| GET /txprotocol         | /HTML/txprotocol.html
| GET /txbinary           | /HTML/txbinary.html
| GET /btnconfig          | /HTML/btn3.html
| GET /wificonfig         | /HTML/wificonfig.html
| GET /btnconfigtesla     | /HTML/btnconfigtesla.html |
| GET /txprotocol         | /HTML/txprotocol.html
| GET /listxmlfiles       | /URH/dir.txt
| GET /updatesd           | /HTML/updatesd.html
| GET /jammer             | /HTML/jammer.html
| GET /txtesla            | /HTML/txtesla.html
| GET /lib.js             | /HTML/javascript.js

| POST /upload            |                                  -> (estandar...)
| POST /uploadsd          | 
| POST /stopjammer        | alert(...)                                  ->
| POST /stopbtntesla      |
| POST /setjammer         |
| POST /settx             |
| POST /settxtesla        |
| POST /settxbinary       |
| POST /settxprotocol     |
| POST /setrx             |
| POST /setbtn            |
| POST /setbtntesla       |
| GET /viewlog            |
| GET /cleanspiffs        |
| GET /downloadlog        |
| GET /delete             | (esto debería cambiarse por un DELETE)
| POST /setwificonfig     |         
| POST /deletewificonfig  |
    
Cambios pensados:
* todos los GET a ficheros usar el serve static.
* que los POST devuelvan un header de OK o ERROR si ha ido bien o mal en el header y ya
* se puede hacer OTA con la misma librería que todo esto, igual esta bien reemplazar la otra para liberar espacio

Cambios:
POST /upload -> en parámetros decidir si a la SD o a SPIFFS.
POST /jammer -> en parámetros decidir si parar, encender y los parámetros de configuración (json).
POST /tx -> en parámetros la config que puede ser tesla o binario.
GET /files -> devolver listado con ficheros, además que se puedan leer o ejecutar desde esta lista
DELETE /files -> borrar un fichero (o lista, ya veremos...)

Apartado config:
    POST /config/button -> args: n_button, tesla (bool), transmission config...
    POST /config/wifi ->
    DELETE /logs
    DELETE /config/wifi
    POST /config/rx
    POST /config/tx