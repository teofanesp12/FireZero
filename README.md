# FireZero
**Software for Firefighter**

INSTALL
-------
   Dep:

      libpq-fe, gtk-+3
   Debian Install:

      apt-get install libpq-dev libgtk-3-dev debhelper autotools-dev
BUILDING
--------
   Primeiro devemos instalar o autotools:

    autoreconf --install
   Depois Teremos que configurar o MakeFile:

    ./configure
   Agora Compilamos:

    make

RUN
---
   Você Pode Usar o Comando:
   
   ./src/init/firezero
