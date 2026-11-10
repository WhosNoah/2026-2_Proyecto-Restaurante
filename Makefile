#=====================================================
# Estructura esperada:
# 	src/		-> archivos .c
#   include/	-> archivos .h
# 	build/		-> objetos .o (se crea solo)
#=====================================================

CC 	   := gcc
TARGET := restaurante

SRC_DIR := src
INC_DIR := include
BUILD   := build

# Banderas: estándar C99 y todas las advertencias activadas
CFLAGS  := -std=c99 -Wall -Wextra -Wpedantic -I$(INC_DIR) -I$(SRC_DIR)
LDFLAGS :=
LDLIBS  :=

# Detecta automáticamente todos los .c (no hay que editar al agregar archivos)
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all debug release run clean help

# ---------- Modos de compilación ----------
all: CFLAGS += -g -O0
all: $(TARGET)

debug: CFLAGS  += -g -O0 -fsanitize=address,undefined
debug: LDFLAGS += -fsanitize=address,undefined
debug: $(TARGET)

release: CFLAGS += -O2 -DNDEBUG
release: $(TARGET)

# ---------- Enlazado ----------
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# ---------- Compilación de cada .c ----------
# -MMD -MP genera dependencias: si cambias un .h se recompila lo necesario
$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

# ---------- Utilidades ----------
run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD) $(TARGET)

help:
	@echo "Uso: make [objetivo]"
	@echo "  all      Compila con símbolos de depuración (por defecto)"
	@echo "  debug    Compila con sanitizers (detecta errores de memoria)"
	@echo "  release  Compila optimizado"
	@echo "  run      Compila y ejecuta"
	@echo "  clean    Borra objetos y ejecutable"
	@echo "Nota: al cambiar de modo, haz 'make clean' primero."

-include $(DEPS)
