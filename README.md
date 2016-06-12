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
