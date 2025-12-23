# Nome do executável
EXECUTAVEL = andebol

# Compilador
CC = gcc

# Flags de compilaçao
CFLAGS = -Wall -Wextra -g -Iinclude -fstack-protector-strong -Wformat-security

# Diretórios
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Encontra todos os ficheiros .c na pasta "src"
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Gera os nomes dos ficheiros objeto (.o) correspondentes na pasta "obj"
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Deteção do Sistema Operativo
ifeq ($(OS),Windows_NT)
	SO := WINDOWS
else
	SO := UNIX
endif

# Comandos por Sistema Operativo
ifeq ($(SO),WINDOWS)

	MKDIR_BIN = @if not exist $(BINDIR) mkdir $(BINDIR)
	MKDIR_OBJ = @if not exist $(OBJDIR) mkdir $(OBJDIR)

	CLEAN_CMD = @if exist $(BINDIR) ( rmdir /s /q $(BINDIR) && echo Diretorio '$(BINDIR)' removido. ) else ( echo Diretorio '$(BINDIR)' nao existe. )
	CLEAN_CMD2 = @if exist $(OBJDIR) ( rmdir /s /q $(OBJDIR) && echo Diretorio '$(OBJDIR)' removido. ) else ( echo Diretorio '$(OBJDIR)' nao existe. )
	
	TARGET = $(BINDIR)\$(EXECUTAVEL)

	RUN_CMD = cmd /c start "" cmd /k

else  # UNIX (Linux / macOS)

	MKDIR_BIN = @mkdir -p $(BINDIR)
	MKDIR_OBJ = @mkdir -p $(OBJDIR)

	CLEAN_CMD = @rm -rf $(BINDIR)
	CLEAN_CMD2 = @rm -rf $(OBJDIR)

	TARGET = $(BINDIR)/$(EXECUTAVEL)

	RUN_CMD = x-terminal-emulator -e

endif

# Ajuste específico para macOS
ifeq ($(OS),Windows_NT)

# Caso seja Windows, não acontece nada

else
	ifeq ($(shell uname),Darwin)
		RUN_CMD = open -a Terminal
	endif
endif

# Regra principal: é executada por defeito com o comando 'make'
all: $(TARGET)

# Regra para ligar os ficheiros objeto e criar o executável final
$(TARGET): $(OBJECTS)
	$(MKDIR_BIN)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo Executavel '$(TARGET)' criado com sucesso.

# Regra para compilar cada ficheiro fonte (.c) num ficheiro objeto (.o)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(MKDIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para executar o programa
run: $(TARGET)
	@echo A executar o programa...
	$(RUN_CMD) "$(TARGET)"

# Regra para limpar os ficheiros gerados pela compilação
clean:
	$(CLEAN_CMD)
	$(CLEAN_CMD2)

# Targets que não são ficheiros
.PHONY: all clean run