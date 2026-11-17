# Proyecto 7 - Restaurante

Esta es una pequeña demostracion de como se compilara todo el proyecto, para esto, tome la decision de usar un archivo [Makefile](/Makefile), el cual nos ayuda a automatizar el proceso de no tener que introducir uno por uno los archivos que se vayan generando.

## Indice

- [Requisitos](#requisitos)
- [Instalacion de requisitos](#instalacion-de-requisitos)
- [Instalacion del proyecto](#instalacion-del-proyecto)
- [Compilacion](#compilacion)

#

### Requisitos
- Compilador `gcc` (std c99).
- `make`

#

### Instalacion de requisitos

Para sistemas tipo Linux:
``` bash
    Ubuntu:
        sudo apt update && sudo apt upgrade
        sudo apt install gcc make git
    
    Fedora:
        sudo dnf upgrade
        sudo dnf install gcc make git
    
    ArchLinux:
        sudo pacman -Syu
        sudo pacman -S gcc make git
```

Para sistemas operativos Windows:
- Instalar [mingw](https://sourceforge.net/projects/mingw/) de su pagina oficial.
- Poner en las variables del sistema el path de tu C:\mingw y C:\mingw\bin

Para sistemas operativos MacOS:
- Abrir una terminal y descargar las herramientas de desarrollo de apple:
``` bash
xcode-select --install       # Esto instala tanto el compilador gcc y make.
```

#

### Instalacion del proyecto
Para instalar el proyecto, unicamente sera necesaria la herramienta git, es tan sencillo como instalar un ejecutable en [Windows](https://git-scm.com/) o una linea de comandos en [Linux](#instalacion-de-requisitos), si instalaste xcode-select en Apple, git ya viene instalado.

#### Instalacion:
``` bash
git clone https://github.com/WhosNoah/2026-2_Proyecto-Restaurante
```

#

### Compilacion
Para este paso es necesario el comando `make`, en windows normalmente viene como `mingw32-make` si lo instalaste con [mingw](https://sourceforge.net/projects/mingw/), si quieres adecuarlo al de otros sistemas (MacOS o Linux) solo crea una copia del archivo y renombralo como `make`.

#### Como compilar:
``` bash

```