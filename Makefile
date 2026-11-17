# Primero definimos las variables para el compilador.

CC	   := gcc
TARGET := restaurante

BUILD = build
BIN = bin

TARGET = $(BIN)/restaurante.exe

# Fuentes y Objetos
INC_DIR = src/include
SOURCES = $(SOURCES_1) $(SOURCES_2)

# Definimos las banderas a usar para el compilador
CFLAGS  := -std=c99 -Wall -Wextra -Wpedantic -I$(INC_DIR) -I$(SOURCES_2)
LDFLAGS :=
LDLIBS  :=

# Este detectara automaticamente todos los .c (no hay que editar nada al agregar nuevos archivos)
SOURCES_1 := $(wildcard src/*.c)
SOURCES_2 := $(wildcard src/restaurante/*.c)
OBJS      := $(SRCS:$(SOURCES_2)/%.c=$(BUILD)/%.o)
DEPS	  := $(OBJS:.o=.d)

.PHONY: all debug release run clean help

# Modo para compilar.
all: CFLAGS += -g -O0
all: $(TARGET)

# Enlazamos los .c y los .o
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# Identificamos si se usa un sistema Windows o UNIX based
ifeq ($(OS),Windows_NT)
	MKDIR = if not exist "$(BUILD)" mkdir "$(BUILD)"
else
	MKDIR = mkdir -p "$(BUILD)"
endif