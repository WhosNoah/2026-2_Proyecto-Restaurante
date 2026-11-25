# ============================================================
# Makefile multiplataforma (Linux / macOS / Windows)
# Estructura esperada:
#   src/*.c                 -> main.c
#   src/restaurante/*.c     -> modulos del proyecto
#   src/include/*.h         -> cabeceras
#   lib/ y lib/restaurante/ -> .o y .d (se crean solos)
#   bin/                    -> ejecutable (se crea solo)
# ============================================================

# ---------- Deteccion de sistema ----------
EXE :=
WIN_CMD :=

ifeq ($(OS),Windows_NT)
    EXE := .exe
    # Si make usa cmd.exe (sin sh), se usan comandos de cmd.
    # Si usa sh/bash (MSYS2, Git Bash, Cygwin), se usan comandos Unix.
    ifeq ($(findstring sh,$(notdir $(SHELL))),)
        WIN_CMD := 1
    endif
endif

ifdef WIN_CMD
    # mkdir -p equivalente en cmd (crea carpetas intermedias si no existen)
    mkdir_p = @if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))"
    RM_ALL  = if exist lib rmdir /S /Q lib & if exist bin rmdir /S /Q bin
    RUN_CMD = $(subst /,\,$(TARGET))
else
    mkdir_p = @mkdir -p "$(1)"
    RM_ALL  = rm -rf lib bin
    RUN_CMD = ./$(TARGET)
endif

# ---------- Variables ----------
CC       ?= gcc
CFLAGS   = -Wall -Werror -std=gnu99 -O2 -MMD -MP
# Con -I src/include las cabeceras funcionan con <> y con ""
INCLUDES = -I src/include -I src
LDFLAGS  =
LDLIBS   = -lm

SRC_DIR  = src
OBJ_DIR  = lib
BIN_DIR  = bin
NAME     = restaurante
TARGET   = $(BIN_DIR)/$(NAME)$(EXE)

# ---------- Fuentes y objetos ----------
SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/restaurante/*.c)

# src/x.c -> lib/x.o  |  src/restaurante/y.c -> lib/restaurante/y.o
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
DEPS    = $(OBJECTS:.o=.d)

# ---------- Targets ----------
.PHONY: all build link run clean

all: link

# Compila cada .c a su .o (crea lib/ y lib/restaurante/ si hace falta)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(call mkdir_p,$(@D))
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Solo compilar, sin enlazar
build: $(OBJECTS)
	@echo Compilado Exitosamente

# Enlaza los .o y genera el ejecutable en bin/ (se crea si no existe)
link: $(TARGET)

$(TARGET): $(OBJECTS)
	$(call mkdir_p,$(BIN_DIR))
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)
	@echo Enlazado Exitosamente

run: $(TARGET)
	$(RUN_CMD)

clean:
	$(RM_ALL)

# Dependencias de cabeceras generadas por -MMD
-include $(DEPS)