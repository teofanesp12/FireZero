<!--<iframe width="560" height="315" src="https://www.youtube.com/embed/0FQejtsq-qQ" frameborder="0" allowfullscreen></iframe>-->
[![ScreenShot](http://img.youtube.com/vi/0FQejtsq-qQ/0.jpg)](https://www.youtube.com/watch?v=0FQejtsq-qQ)
# FireZero
**Software for Firefighter**

INSTALL
-------
   Dep:

      libpq-fe, gtk-+3
   Debian Install:

      apt-get install libpq-dev libgtk-3-dev debhelper autotools-dev
   Ubuntu Install:

   * [`PostgreSQL`](apt:libpq-dev)
   * [`GTK v3.0`](apt:libgtk-3-dev)
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

PACKING
-------
   Para empacotar precisamos Instalar:

    apt-get install blhc devscripts dh-make debhelper autotools-dev
   Troque o Nome do Arquivo Baixado para o Padrão abaixo:

    nome_do_pacote-versão.tar.{bz2,gz,xz}
   Logo depois precisamos Ativar o AutoTools:

    autoreconf --install
   Agora comprimir as Alterações e concluir:

    tar -cvzf ../firezero-0.01.tar.gz .
    dh_make --f ../firezero-0.01.tar.gz -c gpl3
   Logo depois Creamos o Pacote:

    debuild
